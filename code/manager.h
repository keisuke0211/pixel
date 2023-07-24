//========================================
// 
// マネージャー処理
// 
//========================================
// *** manager.h ***
//========================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "object\object.h"

//****************************************
// 前方宣言
//****************************************
class CRenderer;		// レンダラー
class CCamera;			// カメラ
class CLight;			// ライト
class CSound;			// サウンド
class CTexture;			// テクスチャ
class CInputKeyboard;	// キーボード
class CInputMouse;		// マウス
class CInputJoypad;		// ジョイパット
class CTitle;			// タイトル
class CGame;			// ゲーム
class CResult;			// リザルト

//****************************************
// クラス
//****************************************

// 画面クラス
class CScene
{
public:

	// ***** 列挙型 *****

	// モード
	enum MODE
	{
		MODE_TITLE = 0,	// タイトル
		MODE_GAME,		// ゲーム
		MODE_RESULT,	// リザルト
		MODE_MAX
	};

	// ***** 関数 *****
	CScene();
	virtual~CScene();

	// -- メイン ------------------------------------------
	/* 生成			*/static CScene *Create(MODE mode);
	/* 初期化		*/HRESULT Init(void);
	/* 終了			*/void Uninit(void);
	/* 更新			*/void Update(void);
	/* 描画			*/void Draw(void);
	/* モード取得	*/static CScene::MODE GetMode(void);

	// -- 取得 ------------------------------------------
	/* タイトル		*/static CTitle *GetTitle() { return m_pTitle; }
	/* ゲーム		*/static CGame *GetGame() { return m_pGame; }
	/* リザルト		*/static CResult *GetResult() { return m_pResult; }
private:

	// ***** 変数 *****
	/* タイトル		*/static CTitle *m_pTitle;
	/* ゲーム		*/static CGame *m_pGame;
	/* リザルト		*/static CResult *m_pResult;
	static MODE m_mode;		// モード種類
};

// マネージャークラス
class CManager
{
public:

	// ***** 関数 *****
	CManager();
	virtual~CManager();

	/* 初期化	*/HRESULT Init(HINSTANCE hinstance, HWND hWnd, BOOL bWindow);
	/* 終了		*/void Uninit(void);
	/* 更新		*/void Update(void);
	/* 描画		*/void Draw(void);

	// -- 設定 ----------
	/* モード */static void SetMode(CScene::MODE mode);

	// -- 取得 --------------------------------------
	/* レンダラー	*/static CRenderer *GetRenderer() { return m_pRenderer; }
	/* カメラ		*/static CCamera *GetCamera() { return m_pCamera; }
	/* ライト		*/static CLight *GetLight() { return m_pLight; }
	/* サウンド		*/static CSound *GetSound() { return m_pSound; }
	/* テクスチャ	*/static CTexture* GetTexture(){ return m_pTexture; }
	/* キーボード	*/static CInputKeyboard* GetInputKeyboard() { return m_InputKeyboard; }
	/* マウス		*/static CInputMouse* GetInputMouse() { return m_InputMouse; }
	/* ジョイパット	*/static CInputJoypad* GetInputJoypad() { return m_InputJoypad; }
	

private:
	/* レンダラー	*/static CRenderer *m_pRenderer;
	/* カメラ		*/static CCamera *m_pCamera;
	/* ライト		*/static CLight *m_pLight;
	/* サウンド		*/static CSound *m_pSound;
	/* テクスチャ	*/static CTexture *m_pTexture;
	/* キーボード	*/static CInputKeyboard *m_InputKeyboard;
	/* マウス		*/static CInputMouse* m_InputMouse;
	/* ジョイパット	*/static CInputJoypad* m_InputJoypad;
	/* シーン		*/static CScene *m_pScene;

};

#endif