//========================================
// 
// ブロック処理
// 
//========================================
// *** block.cpp ***
//========================================
#include "block.h"
#include "model.h"
#include "../../sound.h"
#include "../../csv_file.h"

//========================================
// マクロ定義
//========================================
#define RADIUS_TIME	(20)	// 半径・推移時間
#define BULLET_ID	(2)		// 弾ID

// 静的変数
CBlock::SetInfo *CBlock::pSetInfo = NULL;

//========================================
// コンストラクタ
//========================================
CBlock::CBlock(int nPriority) : CObjectX(nPriority)
{
	// 値をクリア
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.size = INIT_D3DXVECTOR3;
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nType = 0;
	m_Info.nLife = 0;
	m_Info.nLifeMax = 0;
	m_Info.fRadius = 0.0f;
	m_Info.nCntRadius = 0;
	m_Info.fRadiusRate = 0.0f;
	m_Info.Width = 0.0f;
	m_Info.Height = 0.0f;
	m_Info.Depth = 0.0f;
	m_Info.bSet = false;
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

	if (nType == MODEL_BULLET)
	{
		pBlock->m_Info.nCntRadius = RADIUS_TIME;
		pBlock->m_Info.fRadiusRate = 0.0f;
		pBlock->m_Info.bSet = false;
	}
	else
	{
		pBlock->m_Info.bSet = false;
	}

	pBlock->SetModel(nType);

	// 初期化処理
	pBlock->Init();

	pBlock->m_Info.nType = nType;
	pBlock->m_Info.nLife = 300;
	pBlock->m_Info.nLifeMax = 300;
	pBlock->BlockSetPos(pos);

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
	m_Info.size = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nType = 0;
	m_Info.fRadius = 1.0f;

	// 生成
	SetPos(m_Info.pos);
	SetRot(m_Info.rot);
	SetScale(m_Info.size);
	SetColor(m_Info.col);

	return S_OK;
}

//========================================
// 終了
//========================================
void CBlock::Uninit(void)
{
	/*if (pSetInfo != NULL)
	{
		delete[] pSetInfo;
		pSetInfo = NULL;
	}*/

	CObjectX::Uninit();
}

//========================================
// 更新
//========================================
void CBlock::Update(void)
{

	// 半径推移
	if (m_Info.bSet == false && m_Info.nType == MODEL_BULLET)
	{
		m_Info.fRadiusRate = (float)m_Info.nCntRadius / (float)RADIUS_TIME;
		m_Info.fRadius = 1 * (1.0f - m_Info.fRadiusRate);

		if (--m_Info.nCntRadius <= 0)
		{
			m_Info.bSet = true;
		}
	}

	// 寿命
	if (--m_Info.nLife <= 0 && m_Info.bSet == true)
	{
		Uninit();
		return;
	}
	else if (m_Info.nLife <= RADIUS_TIME && m_Info.bSet == true)
	{
		m_Info.fRadius -= m_Info.fRadius / m_Info.nLife;
		m_Info.col.a *= ((float)m_Info.nLife / RADIUS_TIME);

		SetColor(m_Info.col);
	}

	// サイズの更新
	m_Info.size = D3DXVECTOR3(m_Info.fRadius, m_Info.fRadius, m_Info.fRadius);

	SetPos(m_Info.pos);
	SetRot(m_Info.rot);
	SetScale(m_Info.size);

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
// 読み込み
//========================================
void CBlock::Load(void)
{
	CSVFILE<int> data;

	// 読み込み
	data.csv_read("data\\GAMEDATA\\BLOCK\\BLOCK_DATA.csv", true, true, ',');

	// 動的確保
	int nLineMax = data.cell.size() - 1;
	pSetInfo = new SetInfo[nLineMax];

	for (int nRow = 0; nRow < data.cell.size(); nRow++)
	{
		for (int nLine = 0; nLine < data.cell.at(nRow).size(); nLine++)
		{
			switch (nLine)
			{
				// 種類
			case SET_TYPE:
			{
				pSetInfo[nRow].nType = (int)data.cell.at(nRow).at(nLine);
			}
				break;

				// 位置
			case SET_POS:
			{
				pSetInfo[nRow].pos.x = (int)data.cell.at(nRow).at(nLine); nLine++;
				pSetInfo[nRow].pos.y = (int)data.cell.at(nRow).at(nLine); nLine++;
				pSetInfo[nRow].pos.z = (int)data.cell.at(nRow).at(nLine);
			}
				break;

				// ブロック数
			case SET_NUM:
			{
				pSetInfo[nRow].nNumX = data.cell.at(nRow).at(nLine); nLine++;
				pSetInfo[nRow].nNumY = data.cell.at(nRow).at(nLine); nLine++;
				pSetInfo[nRow].nNumZ = data.cell.at(nRow).at(nLine);
			}
				break;
			}
		}
	}

	// 配置
	SetBlock(nLineMax);
}

//========================================
// 配置
//========================================
void CBlock::SetBlock(int nNumSet)
{
	for (int nCntSet = 0; nCntSet < nNumSet; nCntSet++, pSetInfo++)
	{
		float fWidth = CModel::GetWidth(pSetInfo->nType);		// 幅
		float fHeight = CModel::GetHeight(pSetInfo->nType);		// 高さ
		float fDepth = CModel::GetDepth(pSetInfo->nType);		// 奥行き

		for (int nCntX = 0; nCntX < pSetInfo->nNumX; nCntX++)
		{
			for (int nCntY = 0; nCntY < pSetInfo->nNumY; nCntY++)
			{
				for (int nCntZ = 0; nCntZ < pSetInfo->nNumZ; nCntZ++)
				{
					CBlock::Create(pSetInfo->nType,
						D3DXVECTOR3((
							pSetInfo->pos.x + (nCntX * (fWidth * 2))),
							pSetInfo->pos.y + (nCntY * (fHeight * 2)),
							pSetInfo->pos.z + (nCntZ * (fDepth * 2))));
				}
			}
		}
	}
}