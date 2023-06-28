//========================================
// 
// マネージャー処理
// 
//========================================
// *** manager.cpp ***
//========================================
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "light.h"
#include "sound.h"
#include "texture.h"
#include "input.h"
#include "object\model.h"
#include "object\object.h"
#include "object\2D\score.h"
#include "object\2D\time.h"
#include "object\2D\text2D.h"
#include "object\2D\bg2D.h"
#include "object\2D\bg_Multi2D.h"
#include "object\3D\floor.h"
#include "object\3D\block.h"
#include "object\3D\player.h"
#include "object\3D\enemy.h"
#include "object\3D\effectX.h"

// 静的メンバ変数
CRenderer *CManager::m_pRenderer = NULL;
CCamera *CManager::m_pCamera = NULL;	// カメラ
CLight *CManager::m_pLight = NULL;		// ライト
CSound *CManager::m_pSound = NULL;
CTexture *CManager::m_pTexture = NULL;
CInputKeyboard *CManager::m_InputKeyboard = NULL;
CInputMouse *CManager::m_InputMouse = NULL;
CInputJoypad *CManager::m_InputJoypad = NULL;
CBg *CManager::m_pBg = NULL;
CPlayer *CManager::m_pPlayer = NULL;
CBlock *CManager::m_pBlock = NULL;
CEnemy *CManager::m_pEnemy = NULL;
CBullet *CManager::m_pBullet = NULL;


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
	if (m_pRenderer == NULL)
	{
		// レンダラーの生成
		m_pRenderer = new CRenderer;

		// レンダラーの初期化
		m_pRenderer->Init(hWnd, bWindow);
	}

	if (m_InputKeyboard == NULL)
	{
		// キーボードの生成
		m_InputKeyboard = new CInputKeyboard;

		// キーボードの初期化
		m_InputKeyboard->Init(hinstance, hWnd);
	}

	if (m_InputMouse == NULL)
	{
		// マウスの生成
		m_InputMouse = new CInputMouse;

		// マウスの初期化
		m_InputMouse->Init(hinstance, hWnd);
	}

	if (m_InputJoypad == NULL)
	{
		// ジョイパットの生成
		m_InputJoypad = new CInputJoypad;

		// ジョイパットの初期化
		m_InputJoypad->Init();
	}

	if (m_pCamera == NULL)
	{
		// カメラの生成
		m_pCamera = new CCamera;

		// カメラの初期化
		m_pCamera->lnit();
	}

	if (m_pLight == NULL)
	{
		// ライトの生成
		m_pLight = new CLight;

		// ライトの初期化
		m_pLight->lnit();
	}

	if (m_pSound == NULL)
	{
		// サウンドの生成
		m_pSound = new CSound;

		// サウンドの読み込み
		m_pSound->Load();

		// サウンドの初期化
		m_pSound->Init(hWnd);
	}
	
	if (m_pTexture == NULL)
	{
		// テクスチャの生成
		m_pTexture = new CTexture;

		// テクスチャ
		m_pTexture->Load();
	}

	// モデルの初期化
	CModel::InitModel();

	// 背景の生成
	//for (int nCntBg = 0; nCntBg < 3; nCntBg++)
	//{
	//	/*CBgMulti::Create(D3DXVECTOR3((nCntBg + 1)* 0.0005f, 0.0f, 0.0f), nCntBg);*/
	//}
	
	//CFloor::Create();

	// ブロックの生成
	CBlock::Load();

	CPlayer::Create();

	// 敵の生成

	for (int nCnt = 0; nCnt < 11; nCnt++)
	{
		CEnemy::Create(D3DXVECTOR3(400.0f + (nCnt * -75), -20.0f, -150.0f));
	}

	/*CEffectX *pObj = CEffectX::Create();
	pObj->Eff_SetPos(D3DXVECTOR3(0.0f, 20.0f, 0.0f));
	pObj->Eff_SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pObj->Eff_SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pObj->Eff_SetType(1);
	pObj->Eff_SetLife(1000);
	pObj->Eff_SetCol(D3DXCOLOR(0.1f, 0.f, 0.8f, 1.0f));
	pObj->Eff_SetRadius(1.0f);*/

	{
		// タイム生成
		CTime *pObj = CTime::Create();

		// サイズ設定
		pObj->SetSize(20.0f, 20.0f);

		// 位置設定
		pObj->SetPos(D3DXVECTOR3(SCREEN_WIDTH - 260.0f, 32.0f, 0.0f));

		// タイム設定
		pObj->SetTime(99);
	}

	{
		// スコア生成
		CScore *pObj = CScore::Create();

		// サイズ設定
		pObj->SetSize(20.0f, 20.0f);

		// 位置設定
		pObj->SetPos(D3DXVECTOR3(SCREEN_WIDTH - 260.0f, 52.0f, 0.0f));

		// スコア設定
		CScore::SetScore();
	}
	return S_OK;
}

//========================================
// 終了
//========================================
void CManager::Uninit(void)
{
	// キーボードの破棄
	if (m_InputKeyboard != NULL)
	{
		m_InputKeyboard->Uninit();

		delete m_InputKeyboard;
		m_InputKeyboard = NULL;
	}

	// マウスの破棄
	if (m_InputMouse != NULL)
	{
		m_InputMouse->Uninit();

		delete m_InputMouse;
		m_InputMouse = NULL;
	}

	// ジョイパットの破棄
	if (m_InputJoypad != NULL)
	{
		m_InputJoypad->Uninit();

		delete m_InputJoypad;
		m_InputJoypad = NULL;
	}

	// モデルの終了
	CModel::UninitModel();

	// レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		// レンダラー
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	// ライトの破棄
	if (m_pLight != NULL)
	{
		// ライト
		m_pLight->Uninit();

		delete m_pLight;
		m_pLight = NULL;
	}

	// カメラの破棄
	if (m_pCamera != NULL)
	{
		// カメラ
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = NULL;
	}

	// サウンドの破棄
	if (m_pSound != NULL)
	{
		// サウンド
		m_pSound->StopSound();
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = NULL;
	}

	// テクスチャの破棄
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
	m_InputKeyboard->Update();	// キーボード
	m_InputMouse->Update();		// マウス
	m_InputJoypad->Update();	// ジョイパット
	m_pCamera->Update();		// カメラ
	m_pLight->Update();			// ライト
	m_pRenderer->Update();		// レンダラー
}

//========================================
// 描画
//========================================
void CManager::Draw(void)
{
	m_pRenderer->Draw();	// レンダラー
}
