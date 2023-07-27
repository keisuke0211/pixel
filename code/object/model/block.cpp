//========================================
// 
// ブロック処理
// 
//========================================
// *** block.cpp ***
//========================================
#include "block.h"
#include "bullet_cube.h"
#include "model.h"
#include "../EFFECT/particleX.h"
#include "../../system/sound.h"
#include "../../system/csv_file.h"

//========================================
// マクロ定義
//========================================
#define TNT_COLLSION		(3.0f)	// TNTの爆発の判定

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
	m_Info.nType = 0;
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
CBlock *CBlock::Create(int nType,D3DXVECTOR3 pos)
{
	CBlock *pBlock = NULL;

	if (pBlock != NULL)
	{
		return pBlock;
	}

	// オブジェクト2Dの生成
	pBlock = new CBlock;

	pBlock->SetModel(nType);

	// 初期化処理
	pBlock->Init();

	pBlock->m_Info.nType = nType;
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
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nType = 0;
	m_Info.fRadius = 1.0f;

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
	// 過去の位置・向きの更新
	m_Info.posOld = m_Info.pos;
	m_Info.rotOld = m_Info.rot;

	SetPos(m_Info.pos);
	//SetRot(m_Info.rot);
	SetScale(m_Info.size);

	if (m_Info.bErase)
	{// フラグが真の時、

		if (--m_Info.nEraseTime <= 0)
		{
			if (m_Info.nType == MODEL_TNT_00)
			{
				// TNTの処理
				TntBlock();
			}

			// 破棄
			Uninit();

			return;
		}
	}

	CObjectX::Update();
}

//========================================
// 描画
//========================================
void CBlock::Draw(void)
{
	CObjectX::Draw();
}

//========================================
// Hit処理
//========================================
void CBlock::HitBlock(void)
{
	if (m_Info.nType == MODEL_TNT_00)
	{
		m_Info.nEraseTime = 20;
		m_Info.bErase = true;
	}
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

			if (nBlockType == MODEL_TNT_00)
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