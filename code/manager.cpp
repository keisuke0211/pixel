//========================================
// 
// マネージャー処理
// 
//========================================
// *** manager.cpp ***
//========================================
#include "manager.h"
#include "system/renderer.h"
#include "system/camera.h"
#include "system/light.h"
#include "system/sound.h"
#include "system/texture.h"
#include "system/input.h"
#include "object\object.h"
#include "scene\title.h"
#include "scene\game.h"
#include "scene\result.h"
#include "scene\fade.h"

// 静的メンバ変数
CRenderer *CManager::m_pRenderer = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CSound *CManager::m_pSound = NULL;
CTexture *CManager::m_pTexture = NULL;
CInputKeyboard *CManager::m_InputKeyboard = NULL;
CInputMouse *CManager::m_InputMouse = NULL;
CInputJoypad *CManager::m_InputJoypad = NULL;
CScene *CManager::m_pScene = NULL;
CScene::MODE CScene::m_mode = MODE_TITLE;
CTitle *CScene::m_pTitle = NULL;
CGame *CScene::m_pGame = NULL;
CResult *CScene::m_pResult = NULL;
CFade *CManager::m_pFade = NULL;

//========================================
// コンストラクタ
//========================================
CManager::CManager()
{
	
}

//========================================
// デストラクタ
//========================================
CManager::~CManager()
{

}

//========================================
// 初期化
//========================================
HRESULT CManager::Init(HINSTANCE hinstance, HWND hWnd, BOOL bWindow)
{
	// レンダラー
	m_pRenderer = new CRenderer;

	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return E_FAIL;
	}

	// キーボード
	m_InputKeyboard = new CInputKeyboard;

	if (FAILED(m_InputKeyboard->Init(hinstance, hWnd)))
	{
		return E_FAIL;
	}

	// マウス
	m_InputMouse = new CInputMouse;

	if (FAILED(m_InputMouse->Init(hinstance, hWnd)))
	{
		return E_FAIL;
	}

	// ジョイパット
	m_InputJoypad = new CInputJoypad;

	if (FAILED(m_InputJoypad->Init()))
	{
		return E_FAIL;
	}

	// カメラ
	m_pCamera = new CCamera;

	if (FAILED(m_pCamera->Init()))
	{
		return E_FAIL;
	}

	// ライト
	m_pLight = new CLight;

	if (FAILED(m_pLight->Init()))
	{
		return E_FAIL;
	}

	// サウンド
	m_pSound = new CSound;
	m_pSound->Load();

	if (FAILED(m_pSound->Init(hWnd)))
	{
		return E_FAIL;
	}
	
	// テクスチャ
	if (m_pTexture == NULL)
	{
		m_pTexture = new CTexture;
		m_pTexture->Load();
	}


	// フェード
	if (m_pFade == NULL)
	{
		m_pFade = new CFade;
		m_pFade->Init();
	}

	return S_OK;
}

//========================================
// 終了
//========================================
void CManager::Uninit(void)
{
	// シーン
	if (m_pScene != NULL)
	{
		m_pScene->Uninit();

		delete m_pScene;
		m_pScene = NULL;
	}

	// キーボード
	if (m_InputKeyboard != NULL)
	{
		m_InputKeyboard->Uninit();

		delete m_InputKeyboard;
		m_InputKeyboard = NULL;
	}

	// マウス
	if (m_InputMouse != NULL)
	{
		m_InputMouse->Uninit();

		delete m_InputMouse;
		m_InputMouse = NULL;
	}

	// ジョイパット
	if (m_InputJoypad != NULL)
	{
		m_InputJoypad->Uninit();

		delete m_InputJoypad;
		m_InputJoypad = NULL;
	}

	// レンダラー
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	// ライト
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();

		delete m_pLight;
		m_pLight = NULL;
	}

	// カメラ
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = NULL;
	}

	// サウンド
	if (m_pSound != NULL)
	{
		m_pSound->StopSound();
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = NULL;
	}

	// テクスチャ
	if (m_pTexture != NULL)
	{
		m_pTexture->Unload();

		delete m_pTexture;
		m_pTexture = NULL;
	}
}

//========================================
// 更新
//========================================
void CManager::Update(void)
{
	m_pScene->Update();				// シーン
	m_InputKeyboard->Update();		// キーボード
	m_InputMouse->Update();			// マウス
	m_InputJoypad->Update();		// ジョイパット(ボタン)
	m_InputJoypad->UpdateStick();	// ジョイパット(スティック)	
	m_pCamera->Update();			// カメラ
	m_pLight->Update();				// ライト
	m_pRenderer->Update();			// レンダラー
}

//========================================
// 描画
//========================================
void CManager::Draw(void)
{
	m_pScene->Draw();		// シーン
	m_pRenderer->Draw();	// レンダラー
}

//========================================
//----------------------------------------
// scene クラス
//----------------------------------------
//========================================

//========================================
// コンストラクタ
//========================================
CScene::CScene()
{

}

//========================================
// デストラクタ
//========================================
CScene::~CScene()
{

}

//========================================
// シーン生成
//========================================
CScene *CScene::Create(MODE mode)
{
	CScene *pScene = new CScene;
	m_mode = mode;

	pScene->Init();

	return pScene;
}

//========================================
// 初期化
//========================================
HRESULT CScene::Init()
{
	// 現在のモードの破棄
	switch (m_mode)
	{
	case CScene::MODE_TITLE:
	{
		// タイトル
		m_pTitle->Init();
		break;
	}
	case CScene::MODE_GAME:
	{
		// ゲーム 
		m_pGame->Init();
		break;
	}
	case CScene::MODE_RESULT:
	{
		// リザルト
		m_pResult->Init();
		break;
	}
	}

	return S_OK;
}

//========================================
// 終了
//========================================
void CScene::Uninit(void)
{
	// 現在のモードの破棄
	switch (m_mode)
	{
	case CScene::MODE_TITLE:
	{
		m_pTitle->Uninit();

		delete m_pTitle;
		m_pTitle = NULL;

		break;
	}
	case CScene::MODE_GAME:
	{
		m_pGame->Uninit();

		delete m_pGame;
		m_pGame = NULL;

		break;
	}
	case CScene::MODE_RESULT:
	{
		m_pResult->Uninit();

		delete m_pResult;
		m_pResult = NULL;
		break;
	}
	}
}

//========================================
// 更新
//========================================
void CScene::Update(void)
{
	// 現在のモードの破棄
	switch (m_mode)
	{
	case CScene::MODE_TITLE:
	{
		m_pTitle->Update();
		break;
	}
	case CScene::MODE_GAME:
	{
		m_pGame->Update();
		break;
	}
	case CScene::MODE_RESULT:
	{
		m_pResult->Update();
		break;
	}
	}
}

//========================================
// 描画
//========================================
void CScene::Draw(void)
{
	// 現在のモードの破棄
	switch (m_mode)
	{
	case CScene::MODE_TITLE:
	{
		m_pTitle->Draw();
		break;
	}
	case CScene::MODE_GAME:
	{
		m_pGame->Draw();
		break;
	}
	case CScene::MODE_RESULT:
	{
		m_pResult->Draw();
		break;
	}
	}
}

//========================================
// モード設定
//========================================
void CManager::SetMode(CScene::MODE mode)
{
	// サウンド停止
	m_pSound->StopSound();

	if (m_pScene != NULL)
	{
		// 現在のモードの破棄
		m_pScene->Uninit();

		delete m_pScene;
		m_pScene = NULL;
	}

	// 新しいモードの生成
	m_pScene = CScene::Create(mode);
}

//========================================
// モード取得
//========================================
CScene::MODE CScene::GetMode(void)
{
	return m_mode;
}