//========================================
// 
// 入力処理
// 
//========================================
// *** input.h ***
//========================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//****************************************
// 構造体
//****************************************

// スティックの入力情報構造体
typedef struct
{
	float fTplDiameter;	// スティックの倒し具合
	float fAngle;		// スティックの角度
}STICK_INPUT;

//****************************************
// クラス
//****************************************

// 入力
class CInput
{
public:
	// ***** 定義 *****
	static const int REPEATE_INTERVAL = 160;	// リピート間隔

	// ***** 関数 *****
	CInput();
	virtual~CInput();

	/* メイン */
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化
	virtual void Uninit(void);								// 終了
	virtual void Update(void) = 0;							// 更新

protected:
	// キーボード
	static LPDIRECTINPUT8 m_pInput;		// DirectInoutオブジェクトへのポインタ
	LPDIRECTINPUTDEVICE8 m_pDevice;		// 入力デバイスへのポインタ

	// マウス
	static LPDIRECTINPUT8 m_pMouswInput;
	LPDIRECTINPUTDEVICE8 m_pDeviceMouse;

private:

};

// キーボード
class CInputKeyboard : public CInput
{
public:

	// ***** 関数 *****
	CInputKeyboard();
	~CInputKeyboard();

	/* メイン */
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化
	void Uninit(void);								// 終了
	void Update(void);								// 更新
	bool GetPress(int nKey);						// プレス情報
	bool GetTrigger(int nKey);						// トリガー情報を取得
	bool GetRepeat(int nKey);						// リピート情報を取得
	bool GetRelease(int nKey);						// リリース情報を取得

private:
	// ***** 定義 *****
	static const int NUM_KEY_MAX = 256;		// キーの最大数

	// ***** 変数 *****
	BYTE  m_aKeyState[NUM_KEY_MAX];
	BYTE  m_aKeyStateTrigger[NUM_KEY_MAX];			// キーボードのトリガー情報
	BYTE  m_aKeyStateRepeat[NUM_KEY_MAX];			// キーボードのリピート情報
	BYTE  m_aKeyStateRelease[NUM_KEY_MAX];			// キーボードのリリース情報
	DWORD m_aKeyCurrentTime[NUM_KEY_MAX];			// キーボードの現在の時間
	DWORD m_aKeyExecLastTime[NUM_KEY_MAX];			// キーボードの最後に真を返した時間
};

// マウス
class CInputMouse : public CInput
{
public:
	// ***** 列挙型 *****

	//キー種類
	typedef enum
	{
		MOUSE_LEFT = 0,		//マウス左ボタン
		MOUSE_RIGHT,		//マウス右ボタン
		MOUSE_MIDDLE,		//マウス中央ボタン
		MOUSE_4,			//マウスボタン4
		MOUSE_5,			//マウスボタン5
		MOUSE_6,			//マウスボタン6
		MOUSE_7,			//マウスボタン7
		MOUSE_8,			//マウスボタン8
		MOUSE_MAX
	}MOUSE;

	// ***** 関数 *****
	CInputMouse();
	~CInputMouse();

	/* メイン */
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);				// 初期化
	void Uninit(void);											// 終了
	void Update(void);											// 更新
	bool GetPress(MOUSE Mouse);									// プレス情報を取得
	bool GetTrigger(MOUSE Mouse);								// トリガー情報を取得
	bool GetRepeat(MOUSE Mouse);								// リピート情報を取得
	bool GetRelease(MOUSE Mouse);								// リリース情報を取得
	D3DXVECTOR3 GetPos(void);									// 画面内の位置
	D3DXVECTOR3 GetCursorMove(void) { return m_MouseMove; }		// カーソルの移動量
	int GetWheel(void);											// ホイールの動き処理

private:
	// ***** 定義 *****
	static const int MOUSE_KEY_MAX = 8;		// キーの最大数

	// ***** 変数 *****
	DIMOUSESTATE2	m_aMouseState;					// プレス情報
	DIMOUSESTATE2	m_aMouseStateTrigger;			// トリガー情報
	DIMOUSESTATE2	m_aMouseStateRelease;			// リリース情報
	DIMOUSESTATE2	m_aMouseStateRepeat;			// リピート情報
	DIMOUSESTATE2	m_aMouseCurrentTime;			// 現在の時間
	DIMOUSESTATE2	m_aMouseExecLastTime;			// 最後に真を返した時間
	HWND m_hMouseWnd;								// ウィンドウハンドル

	D3DXVECTOR3 g_MousePosTemp;		// 位置保存用
	D3DXVECTOR3 m_MouseMove;
};

// ジョイパット
class CInputJoypad : public CInput
{
public:	

	// ***** 列挙型 *****

	//キー種類
	typedef enum
	{
		JOYKEY_UP = 0,				//十字ボタン上
		JOYKEY_DOWN,				//十字ボタン下
		JOYKEY_LEFT,				//十字ボタン左
		JOYKEY_RIGHT,				//十字ボタン右
		JOYKEY_START,				//スタートボタン
		JOYKEY_BACK,				//バックボタン
		JOYKEY_LEFT_THUMB,			//左スティック押込み
		JOYKEY_RIGHT_THUMB,			//右スティック押込み
		JOYKEY_LEFT_SHOULDER,		//L１ボタン
		JOYKEY_RIGHT_SHOULDER,		//R１ボタン
		JOYKEY_LEFT_TRIGGER,		//L２トリガー
		JOYKEY_RIGHT_TRIGGER,		//R２トリガー
		JOYKEY_A,					//Aボタン
		JOYKEY_B,					//Bボタン
		JOYKEY_X,					//Xボタン
		JOYKEY_Y,					//Yボタン
		JOYKEY_LEFT_STICK,			//左スティック
		JOYKEY_RIGHT_STICK,			//右スティック
		JOYKEY_MAX
	}JOYKEY;

	// ステック番号
	typedef enum
	{
		STICK_TYPE_LEFT = 0,
		STICK_TYPE_RIGHT,
		STICK_TYPE_MAX
	}STICK_TYPE;

	// ***** 関数 *****
	CInputJoypad();
	~CInputJoypad();

	/* メイン */
	HRESULT Init(void);												// 初期化
	void Uninit(void);												// 終了
	void Update(void);												// 更新
	bool GetJoypadPress(JOYKEY Key, int nPlayer = 0);				// プレス情報を取得
	bool GetJoypadTrigger(JOYKEY Key, int nPlayer = 0);				// トリガー情報を取得
	bool GetJoypadRelese(JOYKEY Key, int nPlayer = 0);				// リリース情報を取得
	bool GetJoypadRepeat(JOYKEY Key, int nPlayer = 0);				// リピート情報を取得

	D3DXVECTOR3 GetJoypadStick(JOYKEY Key, int nPlayer = 0);			// スティックプレス情報を取得
	int GetJoypadTriggerPedal(JOYKEY Key, int nPlayer = 0);				// トリガーペダル情報を取得
	void JoypadVibration(int nTime, WORD nStrength, int nPlayer = 0);	// コントローラーの振動制御
	void GetStick(int type);											// スティックの入力情報を取得
	XINPUT_STATE *GetXInputState(void);									// ジョイパットの入力情報の取得

private:
	// ***** 定義 *****
	static const int PLAYER_MAX = 4;		// プレイヤーの最大数

	// ***** 変数 *****
	XINPUT_STATE m_JoyKeyState[PLAYER_MAX];			// プレス情報
	XINPUT_STATE m_JoyKeyStateTrigger[PLAYER_MAX];	// トリガー情報
	XINPUT_STATE m_JoyKeyStateRelease[PLAYER_MAX];	// リリース情報
	XINPUT_STATE m_aJoyKeyStateRepeat[PLAYER_MAX];	// リピート情報
	XINPUT_STATE m_aJoyKeyCurrentTime[PLAYER_MAX];	// 現在の時間
	XINPUT_STATE m_aJoyKeyExecLastTime[PLAYER_MAX];	// 最後に真を返した時間
	D3DXVECTOR3 m_JoyStickPos[PLAYER_MAX];			// ジョイスティックの傾き
	XINPUT_VIBRATION m_JoyMoter[PLAYER_MAX];		// ジョイパッドのモーター
	int m_nTime[PLAYER_MAX];						// 振動持続時間
	WORD m_nStrength[PLAYER_MAX];					// 振動の強さ (0 - 65535)
	XINPUT_STATE m_xInput;							// 入力情報

};
#endif