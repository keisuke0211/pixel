//========================================
// 
// ���͏���
// 
//========================================
// *** input.cpp ***
//========================================
#include "input.h"

// �ÓI�����o�ϐ�
LPDIRECTINPUT8 CInput::m_pInput = NULL;
LPDIRECTINPUT8 CInput::m_pMouswInput = NULL;

//========================================
// �R���X�g���N�^
//========================================
CInput::CInput()
{
	
}

//========================================
// �f�X�g���N�^
//========================================
CInput::~CInput()
{

}

//========================================
// ������
//========================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	// �L�[�{�[�h
	if (m_pInput == NULL)
	{
		// DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	// �}�E�X
	if (m_pMouswInput == NULL)
	{
		//DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&m_pMouswInput, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

//========================================
// �I��
//========================================
void CInput::Uninit(void)
{

	return;
	// �L�[�{�[�h
	{
		// ���̓f�o�C�X�̕���
		if (m_pDevice != NULL)
		{
			m_pDevice->Unacquire();
			m_pDevice->Release();
			m_pDevice = NULL;
		}

		// DirectInput�I�u�W�F�N�g�̔j��
		if (m_pInput != NULL)
		{
			m_pInput->Release();
			m_pInput = NULL;
		}
	}

	// �}�E�X
	{
		// ���̓f�o�C�X�̕���
		if (m_pDeviceMouse != NULL)
		{
			m_pDeviceMouse->Unacquire();
			m_pDeviceMouse->Release();
			m_pDeviceMouse = NULL;
		}

		// DirectInput�I�u�W�F�N�g�̔j��
		if (m_pMouswInput != NULL)
		{
			m_pMouswInput->Release();
			m_pMouswInput = NULL;
		}
	}
}

//========================================
//----------------------------------------
// �L�[�{�[�h �N���X
//----------------------------------------
//========================================

// �R���X�g���N�^
CInputKeyboard::CInputKeyboard()
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		// �L�[���̃N���A
		m_aKeyState[nCntKey] = false;
		m_aKeyStateTrigger[nCntKey] = false;
		m_aKeyStateRelease[nCntKey] = false;
		m_aKeyStateRepeat[nCntKey] = false;
		m_aKeyCurrentTime[nCntKey] = false;
		m_aKeyExecLastTime[nCntKey] = false;
	}
}

// �f�X�g���N�^
CInputKeyboard::~CInputKeyboard()
{

}

//========================================
// ������
//========================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//�@�f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}

//========================================
// �I��
//========================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//========================================
// �X�V
//========================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			// �L�[�{�[�h�̃g���K�[����ۑ�
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];

			// �L�[�{�[�h�̃����[�X����ۑ�
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey])&~aKeyState[nCntKey];

			// ���݂̎��Ԃ��擾
			m_aKeyCurrentTime[nCntKey] = timeGetTime();

			if (aKeyState[nCntKey] && ((m_aKeyCurrentTime[nCntKey] - m_aKeyExecLastTime[nCntKey]) > REPEATE_INTERVAL))
			{// �L�[�����͂���Ă��āA�����݂̎��ԂƍŌ�ɐ^��Ԃ������Ԃ̍������s�[�g�̊Ԋu���z���Ă������A
			 // �Ō�ɐ^��Ԃ������Ԃ�ۑ�
				m_aKeyExecLastTime[nCntKey] = m_aKeyCurrentTime[nCntKey];

				// �L�[�{�[�h�̃��s�[�g����ۑ�
				m_aKeyStateRepeat[nCntKey] = aKeyState[nCntKey];
			}
			else
			{
				// �L�[�{�[�h�̃��s�[�g����ۑ�
				m_aKeyStateRepeat[nCntKey] = 0;
			}

			// �L�[�{�[�h�̃v���X����ۑ�
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{// ���̓f�o�C�X����f�[�^���擾�ł��Ȃ��������A
	 // �L�[�{�[�h�ւ̃A�N�Z�X�����擾
		m_pDevice->Acquire();
	}
}

//========================================
// �v���X�̎擾
//========================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}
//========================================
// �g���K�[�����擾
//========================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//========================================
// ���s�[�g�����擾 -
//========================================
bool CInputKeyboard::GetRepeat(int nKey)
{
	return (m_aKeyStateRepeat[nKey] & 0x80) ? true : false;
}

//========================================
// �����[�X�����擾
//========================================
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//========================================
//----------------------------------------
// �}�E�X �N���X
//----------------------------------------
//========================================

// �R���X�g���N�^
CInputMouse::CInputMouse()
{
	for (int nCntKey = 0; nCntKey < MOUSE_KEY_MAX; nCntKey++)
	{
		// �L�[���̃N���A
		m_aMouseState.rgbButtons[nCntKey] = false;
		m_aMouseStateTrigger.rgbButtons[nCntKey] = false;
		m_aMouseStateRelease.rgbButtons[nCntKey] = false;
		m_aMouseStateRepeat.rgbButtons[nCntKey] = false;
		m_aMouseCurrentTime.rgbButtons[nCntKey] = false;
		m_aMouseExecLastTime.rgbButtons[nCntKey] = false;
	}
	g_MousePosTemp = INIT_D3DXVECTOR3;	// �ʒu�ۑ�
	m_MouseMove = INIT_D3DXVECTOR3;		// �ړ���
}

// �f�X�g���N�^
CInputMouse::~CInputMouse()
{

}

//========================================
// ������
//========================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//���̓f�o�C�X�̐���
	if (FAILED(m_pMouswInput->CreateDevice(GUID_SysMouse, &m_pDeviceMouse, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDeviceMouse->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(m_pDeviceMouse->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�E�B���h�E�n���h���̕ۊ�
	m_hMouseWnd = hWnd;

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDeviceMouse->Acquire();

	return S_OK;
}

//========================================
// �I��
//========================================
void CInputMouse::Uninit(void)
{
	CInput::Uninit();
}

//========================================
// �X�V
//========================================
void CInputMouse::Update(void)
{
	DIMOUSESTATE2 aKeyState;	// ���͏��

	if (SUCCEEDED(m_pDeviceMouse->GetDeviceState(sizeof(aKeyState), &aKeyState)))
	{// ���̓f�o�C�X����f�[�^���擾
		for (int nCntKey = 0; nCntKey < MOUSE_KEY_MAX; nCntKey++)
		{
			WORD wButtons = m_aMouseState.rgbButtons[nCntKey];
			WORD wOldButtons = aKeyState.rgbButtons[nCntKey];
			m_aMouseStateTrigger.rgbButtons[nCntKey] = ~wButtons & wOldButtons; // �g���K�[����ۑ�
			m_aMouseStateRelease.rgbButtons[nCntKey] = wButtons & ~wOldButtons; // �����[�X����ۑ�

			// ���݂̎��Ԃ��擾
			m_aMouseCurrentTime.rgbButtons[nCntKey] = timeGetTime();

			if (aKeyState.rgbButtons[nCntKey] && ((m_aMouseCurrentTime.rgbButtons[nCntKey] - m_aMouseExecLastTime.rgbButtons[nCntKey]) > REPEATE_INTERVAL))
			{// �L�[�����͂���Ă��āA�����݂̎��ԂƍŌ�ɐ^��Ԃ������Ԃ̍������s�[�g�̊Ԋu���z���Ă������A
			 // �Ō�ɐ^��Ԃ������Ԃ�ۑ�
				m_aMouseExecLastTime.rgbButtons[nCntKey] = m_aMouseCurrentTime.rgbButtons[nCntKey];

				// �}�E�X�̃��s�[�g����ۑ�
				m_aMouseStateRepeat.rgbButtons[nCntKey] = aKeyState.rgbButtons[nCntKey];
			}
			else
			{// �L�[�����͂���Ă��Ȃ��A�������͌��݂̎��ԂƍŌ�ɐ^��Ԃ������Ԃ̍������s�[�g�̊Ԋu���z���Ă��Ȃ����A
			 // �}�E�X�̃��s�[�g����ۑ�
				m_aMouseStateRepeat.rgbButtons[nCntKey] = 0;
			}
		}
		m_aMouseState = aKeyState;		// �v���X����ۑ�
	}
	else
	{
		m_pDeviceMouse->Acquire();			// �A�N�Z�X�����l��
	}

	// �J�[�\���̈ړ��ʂ�ݒ�
	m_MouseMove = GetPos() - g_MousePosTemp;

	// �J�[�\���̈ʒu�ۑ�
	g_MousePosTemp = GetPos();
}

//========================================
// �v���X�̎擾
//========================================
bool CInputMouse::GetPress(MOUSE Mouse)
{
	return (m_aMouseState.rgbButtons[Mouse] & 0x80) ? true : false;
}

//========================================
// �g���K�[�����擾
//========================================
bool CInputMouse::GetTrigger(MOUSE Mouse)
{
	return (m_aMouseStateTrigger.rgbButtons[Mouse] & 0x80) ? true : false;
}

//========================================
// ���s�[�g�����擾 -
//========================================
bool CInputMouse::GetRepeat(MOUSE Mouse)
{
	return (m_aMouseStateRepeat.rgbButtons[Mouse] & 0x80) ? true : false;
}

//========================================
// �����[�X�����擾
//========================================
bool CInputMouse::GetRelease(MOUSE Mouse)
{
	return (m_aMouseStateRelease.rgbButtons[Mouse] & 0x80) ? true : false;
}

//========================================
//�@�}�E�X�|�C���^�[�̈ʒu
//========================================
D3DXVECTOR3 CInputMouse::GetPos(void)
{
	POINT MousePos;		// �J�[�\���p

	//��ʏ�̃}�E�X�|�C���^�[�̈ʒu
	GetCursorPos(&MousePos);

	//�E�B���h�E��̃}�E�X�|�C���^�[�̈ʒu
	ScreenToClient(m_hMouseWnd, &MousePos);

	return D3DXVECTOR3((float)MousePos.x, (float)MousePos.y, 0.0f);
}

//========================================
// �}�E�X�̃z�C�[���̓������m
//========================================
int CInputMouse::GetWheel(void)
{
	return (int)m_aMouseState.lZ;
}

//========================================
//----------------------------------------
// �W���C�p�b�g �N���X
//----------------------------------------
//========================================

// �R���X�g���N�^
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

// �f�X�g���N�^
CInputJoypad::~CInputJoypad()
{

}

//========================================
// ������
//========================================
HRESULT CInputJoypad::Init(void)
{
	//XInput�̃X�e�[�g��ݒ�i�L���ɂ���j
	XInputEnable(true);

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		//�������[�̃N���A
		memset(&m_JoyKeyState[nCnt], 0, sizeof(XINPUT_STATE));
		memset(&m_JoyKeyStateTrigger[nCnt], 0, sizeof(XINPUT_STATE));

		//�W���C�p�b�h�̐U������̂O�N���A
		ZeroMemory(&m_JoyMoter[nCnt], sizeof(XINPUT_VIBRATION));

		//�U������p�̏�����
		m_nStrength[nCnt] = 0;
		m_nTime[nCnt] = 0;
	}
	return S_OK;
}

//========================================
// �I��
//========================================
void CInputJoypad::Uninit(void)
{
	//XInput�̃X�e�[�g��ݒ�i�����ɂ���j
	XInputEnable(false);
}

//========================================
// �X�V
//========================================
void CInputJoypad::Update(void)
{
	XINPUT_STATE JoyKeyState[PLAYER_MAX];		//�W���C�p�b�h���͏��

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		//�W���C�p�b�h�̏�Ԃ��擾
		if (XInputGetState(nCnt, &JoyKeyState[nCnt]) == ERROR_SUCCESS)
		{
			WORD wButtons = m_JoyKeyState[nCnt].Gamepad.wButtons;
			WORD wOldButtons = m_JoyKeyState[nCnt].Gamepad.wButtons;
			m_JoyKeyStateTrigger[nCnt].Gamepad.wButtons = ~wButtons & wOldButtons; //�g���K�[����ۑ�
			m_JoyKeyStateRelease[nCnt].Gamepad.wButtons = wButtons & ~wOldButtons; //�����[�X����ۑ�
			m_JoyKeyState[nCnt] = JoyKeyState[nCnt];  //�v���X����

			// ���݂̎��Ԃ��擾
			m_aJoyKeyCurrentTime[nCnt].Gamepad.wButtons = timeGetTime();

			if (JoyKeyState[nCnt].Gamepad.wButtons && ((m_aJoyKeyCurrentTime[nCnt].Gamepad.wButtons - m_aJoyKeyExecLastTime[nCnt].Gamepad.wButtons) > REPEATE_INTERVAL))
			{// �L�[�����͂���Ă��āA�����݂̎��ԂƍŌ�ɐ^��Ԃ������Ԃ̍������s�[�g�̊Ԋu���z���Ă������A
			 // �Ō�ɐ^��Ԃ������Ԃ�ۑ�
				m_aJoyKeyExecLastTime[nCnt].Gamepad.wButtons = m_aJoyKeyCurrentTime[nCnt].Gamepad.wButtons;

				// ���s�[�g����ۑ�
				m_aJoyKeyStateRepeat[nCnt] = JoyKeyState[nCnt];
			}
			else
			{
				// ���s�[�g����ۑ�
				m_aJoyKeyStateRepeat[nCnt].Gamepad.wButtons = 0;
			}
		}

		// �U��
		m_JoyMoter[nCnt].wLeftMotorSpeed = m_nStrength[nCnt];
		m_JoyMoter[nCnt].wRightMotorSpeed = m_nStrength[nCnt];
		XInputSetState(nCnt, &m_JoyMoter[nCnt]);

		// �U�����Ԃ̌��Z
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
		// �X�e�B�b�N�̓��͏��
		GetStick(nCntStick);
	}
}

//========================================
// �v���X���
//========================================
bool CInputJoypad::GetJoypadPress(JOYKEY Key, int nPlayer)
{
	return (m_JoyKeyState[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//========================================
// �g���K�[���
//========================================
bool CInputJoypad::GetJoypadTrigger(JOYKEY Key, int nPlayer)
{
	return (m_JoyKeyStateTrigger[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//========================================
// �����[�X���
//========================================
bool CInputJoypad::GetJoypadRelese(JOYKEY Key, int nPlayer)
{
	return (m_JoyKeyStateRelease[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//========================================
// ���s�[�g���
//========================================
bool CInputJoypad::GetJoypadRepeat(JOYKEY Key, int nPlayer)
{
	return (m_aJoyKeyStateRepeat[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//========================================
// �X�e�B�b�N�v���X����
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
// �g���K�[�y�_������
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
// �R���g���[���[�̐U������
//========================================
void CInputJoypad::JoypadVibration(int nTime, WORD nStrength, int nPlayer)
{
	m_nTime[nPlayer] = nTime;			//�U����������
	m_nStrength[nPlayer] = nStrength;	//�U���̋���
}

//========================================
// �X�e�B�b�N�̓��͏����擾
//========================================
void CInputJoypad::GetStick(int type)
{
	STICK_INPUT stick;	// �X�e�B�b�N�̓��͏��
	float X = 0;		// �X�e�B�b�N��X��
	float Y = 0;		// �X�e�B�b�N��Y��
						// ��ނɉ������X�e�B�b�N�̎��̒l���擾
	switch (type)
	{
		//========== *** ���X�e�B�b�N ***
	case STICK_TYPE_LEFT:
		X = GetXInputState()->Gamepad.sThumbLX;
		Y = GetXInputState()->Gamepad.sThumbLY;
		break;
		//========== *** �E�X�e�B�b�N ***
	case STICK_TYPE_RIGHT:
		X = GetXInputState()->Gamepad.sThumbRX;
		Y = GetXInputState()->Gamepad.sThumbRY;
		break;
	}
	// �p�x���擾

	stick.fAngle = atan2f(-Y, -X);
	stick.fAngle -= (D3DX_PI * 0.5f);

	// �X�e�B�b�N�̓|������擾
	stick.fTplDiameter = fabsf(X);
	if (stick.fTplDiameter < fabsf(Y))
	{
		stick.fTplDiameter = fabsf(Y);
	}
	stick.fTplDiameter /= 32768.0f;
}

//========================================
// �X�e�B�b�N�̓��͏����擾
//========================================
XINPUT_STATE *CInputJoypad::GetXInputState(void)
{
	return &m_xInput;
}