//========================================
// 
// ブロック処理
// 
//========================================
// *** block.cpp ***
//========================================
#include "block.h"
#include "bullet_cube.h"
#include "../../scene/game.h"
#include "../../scene/title.h"
#include "../../scene/tutorial.h"
#include "model.h"
#include "../EFFECT/particleX.h"
#include "../../system/sound.h"
#include "../../system/csv_file.h"
#include "../../system/camera.h"
#include "../../system/words/font.h"
#include "../../system/words/text.h"

// 静的変数
CBlock::TypeInfo *CBlock::m_TypeInfo = NULL;
int CBlock::m_nCntExit = 0;
bool CBlock::m_bExit = false;
bool CBlock::m_bExitCamera = false;
D3DXVECTOR3 CBlock::m_CameraRot = INIT_D3DXVECTOR3;
float CBlock::m_CameraHeigth = 0.0f;

//========================================
// マクロ定義
//========================================
#define TNT_COLLSION		(3.0f)	// TNTの爆発の判定
#define FILE_PATH	("data/GAMEDATA/BLOCK/BLOCK_DATA.txt")	// ファイルパス

//========================================
// コンストラクタ
//========================================
CBlock::CBlock(int nPriority) : CObjectX(nPriority)
{
	// 値をクリア
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.posOld = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.rotOld = INIT_D3DXVECTOR3;
	m_Info.size = INIT_D3DXVECTOR3;
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nModelID = 0;
	m_Info.fRadius = 0.0f;
	m_Info.nCntRadius = 0;
	m_Info.fRadiusRate = 0.0f;
	m_Info.bSet = false;
	m_Info.nEraseTime = 0;
	m_Info.bErase = false;
}

//========================================
// デストラクタ
//========================================
CBlock::~CBlock()
{

}

//========================================
// 生成
//========================================
CBlock *CBlock::Create(int nType, D3DXVECTOR3 pos, int nState)
{
	CBlock *pBlock = NULL;

	if (pBlock != NULL)
	{
		return pBlock;
	}

	// オブジェクト2Dの生成
	pBlock = new CBlock;

	pBlock->m_Info.state = STATE_MAX;
	pBlock->SetModel(nType);
	pBlock->m_Info.nModelID = nType;

	switch (nState)
	{
	case STATE_NORMAL:
	{
		pBlock->m_Info.state = STATE_NORMAL;
	}
	break;
	case STATE_BREAK:
	{
		pBlock->m_Info.state = STATE_BREAK;
	}
	break;
	case STATE_INVISIBLE:
	{
		pBlock->m_Info.state = STATE_INVISIBLE;
	}
	break;
	}

	// 初期化処理
	pBlock->Init();

	pBlock->SetBlockPos(pos);

	return pBlock;
}

//========================================
// 初期化
//========================================
HRESULT CBlock::Init(void)
{
	CObjectX::Init();

	// 種類の設定
	SetType(TYPE_BLOCK);

	m_Info.pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.size = D3DXVECTOR3(1.0f,1.0f,1.0f);
	m_Info.fRadius = 1.0f;

	if(m_Info.state == STATE_MAX)
	{
	switch (m_TypeInfo[m_Info.nModelID].nState)
	{
	case STATE_NORMAL:
		m_Info.state = STATE_NORMAL;
		break;
	case STATE_BREAK:
		m_Info.state = STATE_BREAK;
		break;
	case STATE_INVISIBLE:
		m_Info.state = STATE_INVISIBLE;
		break;
	}
	}


	if (m_Info.state != STATE_INVISIBLE)
	{
		m_Info.col = INIT_D3DXCOLOR;
	}
	else
	{
		m_Info.col = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
	}

	// 生成
	SetPos(m_Info.pos);
	//SetRot(m_Info.rot);
	SetScale(m_Info.size);
	SetColor(m_Info.col);

	return S_OK;
}

//========================================
// 終了
//========================================
void CBlock::Uninit(void)
{
	CObjectX::Uninit();
}

//========================================
// 更新
//========================================
void CBlock::Update(void)
{
	// -- 取得 -------------------------------------------
	CCamera *pCamera = CManager::GetCamera();		// カメラ

	// 過去の位置・向きの更新
	m_Info.posOld = m_Info.pos;
	m_Info.rotOld = m_Info.rot;

	SetPos(m_Info.pos);
	SetScale(m_Info.size);

	if (m_Info.bErase)
	{// フラグが真の時、

		if (--m_Info.nEraseTime <= 0)
		{
			switch (m_Info.nModelID)
			{
			case MODEL_TNT:
			{
				TntBlock();
			}
				break;
			case MODEL_CRACK_ROCK:
			{
				CrackRock();
			}
				break;
			default:
			{
				ExitOpen();
			}
			break;
			}

			// 破棄
			Uninit();

			return;
		}
	}

	bool bExit = CTitle::IsExit();
	if (bExit)
	{
		if (m_Info.state == STATE_BREAK && !m_Info.bErase)
		{
			if (m_Info.nModelID != MODEL_TNT && m_Info.nModelID != MODEL_CRACK_ROCK)
			{
				m_Info.nEraseTime = 60;
				m_Info.bErase = true;
			}
		}

		if (m_Info.nModelID == MODEL_GOAL && !m_bExit)
		{
			m_CameraRot = pCamera->GetInfo().rot;
			m_CameraHeigth = pCamera->GetInfo().fHeight;

			pCamera->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			pCamera->SetHeigth(0.0f);
			pCamera->SetPosR(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 5, m_Info.pos.z + 100));

			m_nCntExit = 90;
			m_bExit = true;
			m_bExitCamera = true;

		}
		else if (m_Info.nModelID == MODEL_GOAL && m_bExit)
		{
			if (--m_nCntExit <= 0 && m_bExitCamera)
			{
				pCamera->SetRot(m_CameraRot);
				pCamera->SetHeigth(m_CameraHeigth);

				m_nCntExit = 0;
				m_bExitCamera = false;

				if (CScene::GetMode() == CScene::MODE_GAME)
				{
					FormFont pFont = { INIT_D3DXCOLOR,20.0f,10,10,30 };
					FormShadow pShadow = { D3DXCOLOR(0.0f,0.0f,0.0f,1.0f),true,D3DXVECTOR3(2.0f,2.0f,0.0f),D3DXVECTOR2(1.0f,1.0f) };

					CText::Create(CText::BOX_NORMAL_RECT, D3DXVECTOR3(640.0f, 300.0f, 0.0f), D3DXVECTOR2(280.0f, 100.0f),
						"出口が開いた！", CFont::FONT_BESTTEN, &pFont, false, &pShadow);
				}
			}
		}
	}

	CObjectX::Update();
}

//========================================
// 描画
//========================================
void CBlock::Draw(void)
{
	if (m_Info.state != STATE_INVISIBLE)
	{
		CObjectX::Draw();
	}
}

//========================================
// Hit処理
//========================================
void CBlock::HitBlock(void)
{
	if (m_Info.state == STATE_BREAK)
	{
		switch (m_Info.nModelID)
		{
		case MODEL_TNT:
		{
			m_Info.nEraseTime = 20;
			m_Info.bErase = true;
		}
		break;
		case MODEL_CRACK_ROCK:
		{
			m_Info.nEraseTime = 10;
			m_Info.bErase = true;
		}
		break;
		}
	}
}

//========================================
// ひび割れ岩
//========================================
void CBlock::CrackRock(void)
{
	// パーティクル生成
	CParticleX *pObj = CParticleX::Create();
	pObj->Par_SetPos(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y, m_Info.pos.z));
	pObj->Par_SetRot(INIT_D3DXVECTOR3);
	pObj->Par_SetMove(D3DXVECTOR3(35.0f, 15.0f, 35.0f));
	pObj->Par_SetType(0);
	pObj->Par_SetLife(100);
	pObj->Par_SetCol(D3DXCOLOR(0.49f, 0.49f, 0.49f, 1.0f));
	pObj->Par_SetForm(20);
}

//========================================
// TNTブロック
//========================================
void CBlock::TntBlock(void)
{
	// パーティクル生成
	CParticleX *pObj = CParticleX::Create();
	pObj->Par_SetPos(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y, m_Info.pos.z));
	pObj->Par_SetRot(INIT_D3DXVECTOR3);
	pObj->Par_SetMove(D3DXVECTOR3(25.0f, 15.0f, 25.0f));
	pObj->Par_SetType(0);
	pObj->Par_SetLife(100);
	pObj->Par_SetCol(D3DXCOLOR(0.9f, 0.0f, 0.0f, 1.0f));
	pObj->Par_SetForm(10);

	// キューブとの当たり判定
	ModelCollsion(PRIO_CUBE, TYPE_CUBE,m_Info.pos);
}

//========================================
// 出口解放
//========================================
void CBlock::ExitOpen(void)
{
	// パーティクル生成
	CParticleX *pObj = CParticleX::Create();
	pObj->Par_SetPos(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y, m_Info.pos.z));
	pObj->Par_SetRot(INIT_D3DXVECTOR3);
	pObj->Par_SetMove(D3DXVECTOR3(25.0f, 5.0f, 25.0f));
	pObj->Par_SetType(0);
	pObj->Par_SetLife(100);
	pObj->Par_SetCol(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	pObj->Par_SetForm(10);
}

//========================================
// オブジェクトの当たり判定
//========================================
void CBlock::ModelCollsion(PRIO nPrio, TYPE nType, D3DXVECTOR3 pos)
{
	// 先頭オブジェクトを取得
	CObject *pObj = CObject::GetTop(nPrio);

	while (pObj != NULL)
	{// 使用されている時、

		 // 次のオブジェクト
		CObject *pObjNext = pObj->GetNext();

		TYPE type;

		// 種類を取得
		type = pObj->GetType();

		if (type == nType)
		{// 選択した種類の時、

			 // ブロックの取得
			int nBlockType = GetBlockType();	// 種類
			float fWidth = GetWidth();			// 幅
			float fHeight = GetHeight();		// 高さ
			float fDepth = GetDepth();			// 奥行き

			if (nBlockType == MODEL_TNT)
			{
				// サイズ調整
				fWidth *= TNT_COLLSION;	// 幅
				fHeight *= TNT_COLLSION;// 高さ
				fDepth *= TNT_COLLSION;	// 奥行き
			}

			// 相手の取得
			D3DXVECTOR3 PairPos = pObj->GetPos();		// 位置
			D3DXVECTOR3 PairPosOld = pObj->GetPosOld();	// 位置(過去)
			float fPairWidth = pObj->GetWidth();		// 幅
			float fPairHeight = pObj->GetHeight();		// 高さ
			float fPairDepth = pObj->GetDepth();		// 奥行き

			// 当たり判定
			if (Collsion(pos, PairPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
			{// 当たったら

				switch (nType)
				{
				case TYPE_CUBE:
				{
					// ダイナミックキャストする
					CCube *pCube = dynamic_cast<CCube*>(pObj);

					// HIT処理
					pCube->SetCubeLife(20);
				}
				break;
				}
			}
		}

		pObj = pObjNext;	// 次のオブジェクトを代入
	}
}

//========================================
// 読み込み
//========================================
void CBlock::Load(void)
{
	int nCntModel = 0;
	char aDataSearch[TXT_MAX];	// データ検索用

	// ファイルの読み込み
	FILE *pFile = fopen(FILE_PATH, "r");

	if (pFile == NULL)
	{// 種類毎の情報のデータファイルが開けなかった場合、
	 //処理を終了する
		return;
	}

	// ENDが見つかるまで読み込みを繰り返す
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch);	// 検索

		if (!strcmp(aDataSearch, "END"))
		{// 読み込みを終了
			fclose(pFile);
			break;
		}
		if (aDataSearch[0] == '#')
		{// 折り返す
			continue;
		}

		if (!strcmp(aDataSearch, "NUM_BLOCK"))
		{
			int nMaxBlock = 0;

			fscanf(pFile, "%s", &aDataSearch[0]);
			fscanf(pFile, "%d", &nMaxBlock);			// 最大数
			m_TypeInfo = new CBlock::TypeInfo[nMaxBlock];
			assert(m_TypeInfo != NULL);
		}
		else if (!strcmp(aDataSearch, "BLOCK"))
		{
			fscanf(pFile, "%s", &aDataSearch[0]);
			m_TypeInfo[nCntModel].nModelID = nCntModel;			// モデルID
			fscanf(pFile, "%d", &m_TypeInfo[nCntModel].nState);	// 状態
			nCntModel++;
		}
	}
}

//========================================
// リセット
//========================================
void CBlock::Reset(void)
{
	m_nCntExit = 0;
	m_bExit = false;
	m_bExitCamera = false;
	m_CameraRot = INIT_D3DXVECTOR3;
	m_CameraHeigth = 0.0f;
}