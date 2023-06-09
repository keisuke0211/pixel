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
#include "csv_file.h"
#include "object\model\model.h"
#include "object\object.h"
#include "object\2D\score.h"
#include "object\2D\time.h"
#include "object\2D\text2D.h"
#include "object\3D\floor.h"
#include "object\model\block.h"
#include "object\model\player.h"
#include "object\model\enemy.h"
#include "object\model\effectX.h"

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
	// レンダラーの生成
	m_pRenderer = new CRenderer;

	// レンダラーの初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{// 初期化処理が失敗した場合
		return E_FAIL;
	}

	// キーボードの生成
	m_InputKeyboard = new CInputKeyboard;

	// キーボードの初期化
	if (FAILED(m_InputKeyboard->Init(hinstance, hWnd)))
	{
		return E_FAIL;
	}

	// マウスの生成
	m_InputMouse = new CInputMouse;

	// マウスの初期化
	if (FAILED(m_InputMouse->Init(hinstance, hWnd)))
	{
		return E_FAIL;
	}

	// ジョイパットの生成
	m_InputJoypad = new CInputJoypad;

	// ジョイパットの初期化
	if (FAILED(m_InputJoypad->Init()))
	{
		return E_FAIL;
	}

	// カメラの生成
	m_pCamera = new CCamera;

	// カメラの初期化
	if (FAILED(m_pCamera->Init()))
	{
		return E_FAIL;
	}

	// ライトの生成
	m_pLight = new CLight;

	// ライトの初期化
	if (FAILED(m_pLight->Init()))
	{
		return E_FAIL;
	}

	// サウンドの生成
	m_pSound = new CSound;

	// サウンドの読み込み
	m_pSound->Load();

	// サウンドの初期化
	if (FAILED(m_pSound->Init(hWnd)))
	{
		return E_FAIL;
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
	

	// ブロックの生成
	SetBlock();

	CPlayer *pPlayer = CPlayer::Create();
	pPlayer->SetMotion("data\\GAMEDATA\\MODEL\\Player\\PLAYER_DATA.txt");

	// 敵の生成

	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		CEnemy *pObj = CEnemy::Create(D3DXVECTOR3(330.0f + (nCnt * -75), -20.0f, -150.0f));
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

	{
		{// 移動方法テキスト
		 // テキスト2D生成
			CText2D *pObj = CText2D::Create();

			// 位置設定
			pObj->SetPos(D3DXVECTOR3(32.0f, 32.0f, 0.0f));
			// サイズ設定
			pObj->SetSize(16.0f, 16.0f);
			// 文字列設定
			pObj->SetString("MOVE : W A D S");
		}

		{// ジャンプ方法テキスト
		 // テキスト2D生成
			CText2D *pObj = CText2D::Create();

			// 位置設定
			pObj->SetPos(D3DXVECTOR3(32.0f, 48.0f, 0.0f));
			// サイズ設定
			pObj->SetSize(16.0f, 16.0f);
			// 文字列設定
			pObj->SetString("JUMP : SPACE");
		}

		{// 射撃方法テキスト
		 // テキスト2D生成
			CText2D *pObj = CText2D::Create();

			// 位置設定
			pObj->SetPos(D3DXVECTOR3(32.0f, 64.0f, 0.0f));
			// サイズ設定
			pObj->SetSize(16.0f, 16.0f);
			// 文字列設定
			pObj->SetString("SHOT : ENTER & MOUSE_LEFT");
		}

		{// カメラ切り替えテキスト
		 // テキスト2D生成
			CText2D *pObj = CText2D::Create();

			// 位置設定
			pObj->SetPos(D3DXVECTOR3(32.0f, 96.0f, 0.0f));
			// サイズ設定
			pObj->SetSize(16.0f, 16.0f);
			// 文字列設定
			pObj->SetString("CAMERA_MODE : Q");
		}

		{// カメラ移動方法テキスト
		 // テキスト2D生成
			CText2D *pObj = CText2D::Create();

			// 位置設定
			pObj->SetPos(D3DXVECTOR3(32.0f, 112.0f, 0.0f));
			// サイズ設定
			pObj->SetSize(16.0f, 16.0f);
			// 文字列設定
			pObj->SetString("CAMERA_MOVE : MOUSE_RIGHT");
		}

		{// リセット方法テキスト
		 // テキスト2D生成
			CText2D *pObj = CText2D::Create();

			// 位置設定
			pObj->SetPos(D3DXVECTOR3(32.0f, 144.0f, 0.0f));
			// サイズ設定
			pObj->SetSize(16.0f, 16.0f);
			// 文字列設定
			pObj->SetString("RESET:R");
		}
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
	m_InputKeyboard->Update();		// キーボード
	m_InputMouse->Update();			// マウス
	m_InputJoypad->Update();		// ジョイパット(ボタン)
	m_InputJoypad->UpdateStick();	// ジョイパット(スティック)	
	m_pCamera->Update();			// カメラ
	m_pLight->Update();				// ライト
	m_pRenderer->Update();			// レンダラー

	// リセットボタン
	if (m_InputKeyboard->GetTrigger(DIK_R))
	{
		SetEnemy();
	}

}

//========================================
// 描画
//========================================
void CManager::Draw(void)
{
	m_pRenderer->Draw();	// レンダラー
}

//========================================
// セットエネミー
//========================================
void CManager::SetEnemy(void)
{
	// 敵を全て破棄
	CObject::ReleaseAll(CObject::TYPE_ENEMY);

	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		CEnemy::Create(D3DXVECTOR3(330.0f + (nCnt * -75), -20.0f, -150.0f));
	}
}

//========================================
// セットブロック
//========================================
void CManager::SetBlock(void)
{
	CSVFILE *pFile = new CSVFILE;

	// 読み込み
	pFile->FileLood("data\\GAMEDATA\\BLOCK\\STAGE_DATA1.csv", true, true, ',');

	// 行数の取得
	int nRowMax = pFile->GetRowSize();

	// 各データに代入
	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		// 配置情報の生成
		int nType;				// 種類
		D3DXVECTOR3 pos;		// 位置

		// 列数の取得
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0:	pFile->ToValue(nType, sData); break;	// 種類
			case 1:	pFile->ToValue(pos.x, sData); break;	// 位置 X
			case 2:	pFile->ToValue(pos.y, sData); break;	// 位置 Y
			case 3:	pFile->ToValue(pos.z, sData); break;	// 位置 Z
			}
		}

		// 最大数に達したら返す
		if (nRow == nRowMax - 1)	// (列数 - 列の最大数 - ヘッダーの列数)
		{
			return;
		}

		// 配置
		CBlock *pObj = CBlock::Create(nType, pos);
	}

	// メモリ開放
	delete pFile;
	pFile = NULL;
}