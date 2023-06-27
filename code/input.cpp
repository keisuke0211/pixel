//========================================
// 
// 入力処理
// 
//========================================
// *** input.cpp ***
//========================================
#include "input.h"

// 静的メンバ変数
LPDIRECTINPUT8 CInput::m_pInput = NULL;
LPDIRECTINPUT8 CInput::m_pMouswInput = NULL;

//========================================
// コンストラクタ
//========================================
CInput::CInput()
{
	
}

//========================================
// デストラクタ
//========================================
CInput::~CInput()
{

}

//========================================
// 初期化
//========================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	// キーボード
	if (m_pInput == NULL)
	{
		// DirectInputオブジェクトの生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	// マウス
	if (m_pMouswInput == NULL)
	{
		//DirectInputオブジェクトの生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&m_pMouswInput, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

//========================================
// 終了
//========================================
void CInput::Uninit(void)
{

	return;
	// キーボード
	{
		// 入力デバイスの放棄
		if (m_pDevice != NULL)
		{
			m_pDevice->Unacquire();
			m_pDevice->Release();
			m_pDevice = NULL;
		}

		// DirectInputオブジェクトの破壊
		if (m_pInput != NULL)
		{
			m_pInput->Release();
			m_pInput = NULL;
		}
	}

	// マウス
	{
		// 入力デバイスの放棄
		if (m_pDeviceMouse != NULL)
		{
			m_pDeviceMouse->Unacquire();
			m_pDeviceMouse->Release();
			m_pDeviceMouse = NULL;
		}

		// DirectInputオブジェクトの破壊
		if (m_pMouswInput != NULL)
		{
			m_pMouswInput->Release();
			m_pMouswInput = NULL;
		}
	}
}

//========================================
//----------------------------------------
// キーボード クラス
//----------------------------------------
//========================================

// コンストラクタ
CInputKeyboard::CInputKeyboard()
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		// キー情報のクリア
		m_aKeyState[nCntKey] = false;
		m_aKeyStateTrigger[nCntKey] = false;
		m_aKeyStateRelease[nCntKey] = false;
		m_aKeyStateRepeat[nCntKey] = false;
		m_aKeyCurrentTime[nCntKey] = false;
		m_aKeyExecLastTime[nCntKey] = false;
	}
}

// デストラクタ
CInputKeyboard::~CInputKeyboard()
{

}

//========================================
// 初期化
//========================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//　デバイスの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}

//========================================
// 終了
//========================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//========================================
// 更新
//========================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			// キーボードのトリガー情報を保存
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];

			// キーボードのリリース情報を保存
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey])&~aKeyState[nCntKey];

			// 現在の時間を取得
			m_aKeyCurrentTime[nCntKey] = timeGetTime();

			if (aKeyState[nCntKey] && ((m_aKeyCurrentTime[nCntKey] - m_aKeyExecLastTime[nCntKey]) > REPEATE_INTERVAL))
			{// キーが入力されていて、かつ現在の時間と最後に真を返した時間の差がリピートの間隔を越えていた時、
			 // 最後に真を返した時間を保存
				m_aKeyExecLastTime[nCntKey] = m_aKeyCurrentTime[nCntKey];

				// キーボードのリピート情報を保存
				m_aKeyStateRepeat[nCntKey] = aKeyState[nCntKey];
			}
			else
			{
				// キーボードのリピート情報を保存
				m_aKeyStateRepeat[nCntKey] = 0;
			}

			// キーボードのプレス情報を保存
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{// 入力デバイスからデータを取得できなかった時、
	 // キーボードへのアクセス権を取得
		m_pDevice->Acquire();
	}
}

//========================================
// プレスの取得
//========================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}
//========================================
// トリガー情報を取得
//========================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//========================================
// リピート情報を取得 -
//========================================
bool CInputKeyboard::GetRepeat(int nKey)
{
	return (m_aKeyStateRepeat[nKey] & 0x80) ? true : false;
}

//========================================
// リリース情報を取得
//========================================
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//========================================
//----------------------------------------
// マウス クラス
//----------------------------------------
//========================================

// コンストラクタ
CInputMouse::CInputMouse()
{
	for (int nCntKey = 0; nCntKey < MOUSE_KEY_MAX; nCntKey++)
	{
		// キー情報のクリア
		m_aMouseState.rgbButtons[nCntKey] = false;
		m_aMouseStateTrigger.rgbButtons[nCntKey] = false;
		m_aMouseStateRelease.rgbButtons[nCntKey] = false;
		m_aMouseStateRepeat.rgbButtons[nCntKey] = false;
		m_aMouseCurrentTime.rgbButtons[nCntKey] = false;
		m_aMouseExecLastTime.rgbButtons[nCntKey] = false;
	}
	g_MousePosTemp = INIT_D3DXVECTOR3;	// 位置保存
	m_MouseMove = INIT_D3DXVECTOR3;		// 移動量
}

// デストラクタ
CInputMouse::~CInputMouse()
{

}

//========================================
// 初期化
//========================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//入力デバイスの生成
	if (FAILED(m_pMouswInput->CreateDevice(GUID_SysMouse, &m_pDeviceMouse, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(m_pDeviceMouse->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(m_pDeviceMouse->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//ウィンドウハンドルの保管
	m_hMouseWnd = hWnd;

	//キーボードへのアクセス権を獲得
	m_pDeviceMouse->Acquire();

	return S_OK;
}

//========================================
// 終了
//========================================
void CInputMouse::Uninit(void)
{
	CInput::Uninit();
}

//========================================
// 更新
//========================================
void CInputMouse::Update(void)
{
	DIMOUSESTATE2 aKeyState;	// 入力情報

	if (SUCCEEDED(m_pDeviceMouse->GetDeviceState(sizeof(aKeyState), &aKeyState)))
	{// 入力デバイスからデータを取得
		for (int nCntKey = 0; nCntKey < MOUSE_KEY_MAX; nCntKey++)
		{
			WORD wButtons = m_aMouseState.rgbButtons[nCntKey];
			WORD wOldButtons = aKeyState.rgbButtons[nCntKey];
			m_aMouseStateTrigger.rgbButtons[nCntKey] = ~wButtons & wOldButtons; // トリガー情報を保存
			m_aMouseStateRelease.rgbButtons[nCntKey] = wButtons & ~wOldButtons; // リリース情報を保存

			// 現在の時間を取得
			m_aMouseCurrentTime.rgbButtons[nCntKey] = timeGetTime();

			if (aKeyState.rgbButtons[nCntKey] && ((m_aMouseCurrentTime.rgbButtons[nCntKey] - m_aMouseExecLastTime.rgbButtons[nCntKey]) > REPEATE_INTERVAL))
			{// キーが入力されていて、かつ現在の時間と最後に真を返した時間の差がリピートの間隔を越えていた時、
			 // 最後に真を返した時間を保存
				m_aMouseExecLastTime.rgbButtons[nCntKey] = m_aMouseCurrentTime.rgbButtons[nCntKey];

				// マウスのリピート情報を保存
				m_aMouseStateRepeat.rgbButtons[nCntKey] = aKeyState.rgbButtons[nCntKey];
			}
			else
			{// キーが入力されていない、もしくは現在の時間と最後に真を返した時間の差がリピートの間隔を越えていない時、
			 // マウスのリピート情報を保存
				m_aMouseStateRepeat.rgbButtons[nCntKey] = 0;
			}
		}
		m_aMouseState = aKeyState;		// プレス情報を保存
	}
	else
	{
		m_pDeviceMouse->Acquire();			// アクセス権を獲得
	}

	// カーソルの移動量を設定
	m_MouseMove = GetPos() - g_MousePosTemp;

	// カーソルの位置保存
	g_MousePosTemp = GetPos();
}

//========================================
// プレスの取得
//========================================
bool CInputMouse::GetPress(MOUSE Mouse)
{
	return (m_aMouseState.rgbButtons[Mouse] & 0x80) ? true : false;
}

//========================================
// トリガー情報を取得
//========================================
bool CInputMouse::GetTrigger(MOUSE Mouse)
{
	return (m_aMouseStateTrigger.rgbButtons[Mouse] & 0x80) ? true : false;
}

//========================================
// リピート情報を取得 -
//========================================
bool CInputMouse::GetRepeat(MOUSE Mouse)
{
	return (m_aMouseStateRepeat.rgbButtons[Mouse] & 0x80) ? true : false;
}

//========================================
// リリース情報を取得
//========================================
bool CInputMouse::GetRelease(MOUSE Mouse)
{
	return (m_aMouseStateRelease.rgbButtons[Mouse] & 0x80) ? true : false;
}

//========================================
//　マウスポインターの位置
//========================================
D3DXVECTOR3 CInputMouse::GetPos(void)
{
	POINT MousePos;		// カーソル用

	//画面上のマウスポインターの位置
	GetCursorPos(&MousePos);

	//ウィンドウ上のマウスポインターの位置
	ScreenToClient(m_hMouseWnd, &MousePos);

	return D3DXVECTOR3((float)MousePos.x, (float)MousePos.y, 0.0f);
}

//========================================
// マウスのホイールの動き感知
//========================================
int CInputMouse::GetWheel(void)
{
	return (int)m_aMouseState.lZ;
}

//========================================
//----------------------------------------
// ジョイパット クラス
//----------------------------------------
//========================================

// コンストラクタ
CInputJoypad::CInputJoypad()
{
	for (int nCntPat = 0; nCntPat < PLAYER_MAX; nCntPat++)
	{
		m_JoyKeyState[nCntPat].Gamepad.wButtons = false;
		m_JoyKeyStateTrigger[nCntPat].Gamepad.wButtons = false;
		m_JoyKeyStateRelease[nCntPat].Gamepad.wButtons = false;
		m_JoyKeyStateRelease[nCntPat].Gamepad.wButtons = false;
		m_aJoyKeyStateRepeat[nCntPat].Gamepad.wButtons = false;
		m_aJoyKeyCurrentTime[nCntPat].Gamepad.wButtons = false;
		m_aJoyKeyExecLastTime[nCntPat].Gamepad.wButtons = false;
	}
}

// デストラクタ
CInputJoypad::~CInputJoypad()
{

}

//========================================
// 初期化
//========================================
HRESULT CInputJoypad::Init(void)
{
	//XInputのステートを設定（有効にする）
	XInputEnable(true);

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		//メモリーのクリア
		memset(&m_JoyKeyState[nCnt], 0, sizeof(XINPUT_STATE));
		memset(&m_JoyKeyStateTrigger[nCnt], 0, sizeof(XINPUT_STATE));

		//ジョイパッドの振動制御の０クリア
		ZeroMemory(&m_JoyMoter[nCnt], sizeof(XINPUT_VIBRATION));

		//振動制御用の初期化
		m_nStrength[nCnt] = 0;
		m_nTime[nCnt] = 0;
	}
	return S_OK;
}

//========================================
// 終了
//========================================
void CInputJoypad::Uninit(void)
{
	//XInputのステートを設定（無効にする）
	XInputEnable(false);
}

//========================================
// 更新
//========================================
void CInputJoypad::Update(void)
{
	XINPUT_STATE JoyKeyState[PLAYER_MAX];		//ジョイパッド入力情報

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		//ジョイパッドの状態を取得
		if (XInputGetState(nCnt, &JoyKeyState[nCnt]) == ERROR_SUCCESS)
		{
			WORD wButtons = m_JoyKeyState[nCnt].Gamepad.wButtons;
			WORD wOldButtons = m_JoyKeyState[nCnt].Gamepad.wButtons;
			m_JoyKeyStateTrigger[nCnt].Gamepad.wButtons = ~wButtons & wOldButtons; //トリガー情報を保存
			m_JoyKeyStateRelease[nCnt].Gamepad.wButtons = wButtons & ~wOldButtons; //リリース情報を保存
			m_JoyKeyState[nCnt] = JoyKeyState[nCnt];  //プレス処理

			// 現在の時間を取得
			m_aJoyKeyCurrentTime[nCnt].Gamepad.wButtons = timeGetTime();

			if (JoyKeyState[nCnt].Gamepad.wButtons && ((m_aJoyKeyCurrentTime[nCnt].Gamepad.wButtons - m_aJoyKeyExecLastTime[nCnt].Gamepad.wButtons) > REPEATE_INTERVAL))
			{// キーが入力されていて、かつ現在の時間と最後に真を返した時間の差がリピートの間隔を越えていた時、
			 // 最後に真を返した時間を保存
				m_aJoyKeyExecLastTime[nCnt].Gamepad.wButtons = m_aJoyKeyCurrentTime[nCnt].Gamepad.wButtons;

				// リピート情報を保存
				m_aJoyKeyStateRepeat[nCnt] = JoyKeyState[nCnt];
			}
			else
			{
				// リピート情報を保存
				m_aJoyKeyStateRepeat[nCnt].Gamepad.wButtons = 0;
			}
		}

		// 振動
		m_JoyMoter[nCnt].wLeftMotorSpeed = m_nStrength[nCnt];
		m_JoyMoter[nCnt].wRightMotorSpeed = m_nStrength[nCnt];
		XInputSetState(nCnt, &m_JoyMoter[nCnt]);

		// 振動時間の減算
		if (m_nTime[nCnt] > 0)
		{
			m_nTime[nCnt]--;
		}
		else
		{
			m_nStrength[nCnt] = 0;
			m_nTime[nCnt] = 0;
		}
	}

	for (int nCntStick = 0; nCntStick < STICK_TYPE_MAX; nCntStick++)
	{
		// スティックの入力情報
		GetStick(nCntStick);
	}
}

//========================================
// プレス情報
//========================================
bool CInputJoypad::GetJoypadPress(JOYKEY Key, int nPlayer)
{
	return (m_JoyKeyState[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//========================================
// トリガー情報
//========================================
bool CInputJoypad::GetJoypadTrigger(JOYKEY Key, int nPlayer)
{
	return (m_JoyKeyStateTrigger[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//========================================
// リリース情報
//========================================
bool CInputJoypad::GetJoypadRelese(JOYKEY Key, int nPlayer)
{
	return (m_JoyKeyStateRelease[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//========================================
// リピート情報
//========================================
bool CInputJoypad::GetJoypadRepeat(JOYKEY Key, int nPlayer)
{
	return (m_aJoyKeyStateRepeat[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//========================================
// スティックプレス処理
//========================================
D3DXVECTOR3 CInputJoypad::GetJoypadStick(JOYKEY Key, int nPlayer)
{
	switch (Key)
	{
	case JOYKEY_LEFT_STICK:
		m_JoyStickPos[nPlayer] = D3DXVECTOR3(m_JoyKeyState[nPlayer].Gamepad.sThumbLX / 32767.0f, -m_JoyKeyState[nPlayer].Gamepad.sThumbLY / 32767.0f, 0.0f);
		break;
	case JOYKEY_RIGHT_STICK:
		m_JoyStickPos[nPlayer] = D3DXVECTOR3(m_JoyKeyState[nPlayer].Gamepad.sThumbRX / 32767.0f, -m_JoyKeyState[nPlayer].Gamepad.sThumbRY / 32767.0f, 0.0f);
		break;
	}

	return m_JoyStickPos[nPlayer];
}

//========================================
// トリガーペダル処理
//========================================
int CInputJoypad::GetJoypadTriggerPedal(JOYKEY Key, int nPlayer)
{
	int nJoypadTriggerPedal = 0;
	switch (Key)
	{
	case JOYKEY_LEFT_TRIGGER:
		nJoypadTriggerPedal = m_JoyKeyState[nPlayer].Gamepad.bLeftTrigger;
		break;
	case JOYKEY_RIGHT_TRIGGER:
		nJoypadTriggerPedal = m_JoyKeyState[nPlayer].Gamepad.bRightTrigger;
		break;
	}

	return nJoypadTriggerPedal;
}

//========================================
// コントローラーの振動制御
//========================================
void CInputJoypad::JoypadVibration(int nTime, WORD nStrength, int nPlayer)
{
	m_nTime[nPlayer] = nTime;			//振動持続時間
	m_nStrength[nPlayer] = nStrength;	//振動の強さ
}

//========================================
// スティックの入力情報を取得
//========================================
void CInputJoypad::GetStick(int type)
{
	STICK_INPUT stick;	// スティックの入力情報
	float X = 0;		// スティックのX軸
	float Y = 0;		// スティックのY軸
						// 種類に応じたスティックの軸の値を取得
	switch (type)
	{
		//========== *** 左スティック ***
	case STICK_TYPE_LEFT:
		X = GetXInputState()->Gamepad.sThumbLX;
		Y = GetXInputState()->Gamepad.sThumbLY;
		break;
		//========== *** 右スティック ***
	case STICK_TYPE_RIGHT:
		X = GetXInputState()->Gamepad.sThumbRX;
		Y = GetXInputState()->Gamepad.sThumbRY;
		break;
	}
	// 角度を取得

	stick.fAngle = atan2f(-Y, -X);
	stick.fAngle -= (D3DX_PI * 0.5f);

	// スティックの倒し具合を取得
	stick.fTplDiameter = fabsf(X);
	if (stick.fTplDiameter < fabsf(Y))
	{
		stick.fTplDiameter = fabsf(Y);
	}
	stick.fTplDiameter /= 32768.0f;
}

//========================================
// スティックの入力情報を取得
//========================================
XINPUT_STATE *CInputJoypad::GetXInputState(void)
{
	return &m_xInput;
}