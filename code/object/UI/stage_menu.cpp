//========================================
// 
// ステージ選択
// 
//========================================
// *** stage_menu.cpp ***
//========================================
#include "stage_menu.h"
#include "../../manager.h"
#include "../../system/renderer.h"
#include "../../system/texture.h"
#include "../../system/words/text.h"
#include "../../system/words/font.h"

//========================================
// マクロ定義
//========================================
#define POS_RANGE_WIDE	(3.5f)	// 判定の拡張 (現在の位置 > 目標位置 - RANGE_WIDE && 現在位置 < 目標位置 + RANGE_WIDE)
#define SIZE_RANGE_WIDE	(3.5f)	// 判定の拡張(サイズ用)

//========================================
// コンストラクタ
//========================================
CStage::CStage(int nPriority) : CObject2D(nPriority)
{
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.TargetPos = INIT_D3DXVECTOR3;
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nType = 0;
	m_Info.size = INIT_D3DXVECTOR2;
	m_Info.TargetSize = INIT_D3DXVECTOR2;
	m_Info.bMove = false;
}

//========================================
// デストラクタ
//========================================
CStage::~CStage()
{

}

//========================================
// 生成
//========================================
CStage *CStage::Create(int nType, int nPlace)
{
	CStage *pStage = new CStage;

	pStage->m_Info.nType = nType;
	pStage->m_Info.nPlace = nPlace;
	pStage->m_Info.pos = pStage->m_Place[nPlace];

	if (nPlace == PLACE_CENTER)
	{
		pStage->m_Info.size = D3DXVECTOR2(300.0f, 300.0f);
		pStage->m_Info.TargetSize = D3DXVECTOR2(300.0f, 300.0f);
	}
	else
	{
		pStage->m_Info.size = D3DXVECTOR2(150.0f, 150.0f);
		pStage->m_Info.TargetSize = D3DXVECTOR2(150.0f, 150.0f);
	}

	pStage->Init();

	return pStage;
}

//========================================
// 初期化
//========================================
HRESULT CStage::Init(void)
{
	CObject2D::Init();

	// 種類の設定
	SetType(TYPE_BG);

	// 設定
	SetPos(m_Info.pos);
	SetSize(m_Info.size.x, m_Info.size.y);
	SetColar(INIT_D3DXCOLOR);


	switch (m_Info.nType)
	{
	case CGame::Stage_EASY:
		BindTexture(CTexture::TEX_STAGE_EASY);
		break;
	case CGame::Stage_NORMAL:
		BindTexture(CTexture::TEX_STAGE_NORMAL);
		break;
	case CGame::Stage_DIFFICULT:
		BindTexture(CTexture::TEX_STAGE_DIFFICULT);
		break;
	default:
		BindTexture(CTexture::TEX_SEA01);
		break;
	}

	return S_OK;
}

//========================================
// 終了
//========================================
void CStage::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================
// 更新
//========================================
void CStage::Update(void)
{
	bool bPos = false;
	bool bSize = false;
	bool bTextPos = false;
	bool bTextSize = false;

	if (m_Info.bMove)
	{
		// 位置の推移
		if (m_Info.nPlace == PLACE_LEFT_EDGE || m_Info.nPlace == PLACE_VACANT)
		{
			m_Info.pos = m_Info.TargetPos;
		}
		else
		{
			m_Info.pos.x += (m_Info.TargetPos.x - m_Info.pos.x) * 0.12f;
			m_Info.pos.y += (m_Info.TargetPos.y - m_Info.pos.y) * 0.12f;
		}

		// サイズの推移
		m_Info.size.x += (m_Info.TargetSize.x - m_Info.size.x) * 0.12f;
		m_Info.size.y += (m_Info.TargetSize.y - m_Info.size.y) * 0.12f;

		// 位置・サイズの再設定
		SetPos(m_Info.pos);
		SetSize(m_Info.size.x, m_Info.size.y);

		// 範囲に入ったら移動をやめる
		if (m_Info.pos.x > m_Info.TargetPos.x - POS_RANGE_WIDE && m_Info.pos.x < m_Info.TargetPos.x + POS_RANGE_WIDE)
		{
			m_Info.pos = m_Info.TargetPos;
			bPos = true;
		}

		if ((m_Info.size.x > m_Info.TargetSize.x - SIZE_RANGE_WIDE && m_Info.size.x < m_Info.TargetSize.x + SIZE_RANGE_WIDE) &&
			(m_Info.size.y > m_Info.TargetSize.y - SIZE_RANGE_WIDE && m_Info.size.y < m_Info.TargetSize.y + SIZE_RANGE_WIDE))
		{
			m_Info.size = m_Info.TargetSize;
			bSize = true;
		}

		if (bPos && bSize)
		{
			m_Info.bMove = false;
		}
	}

	CObject2D::Update();
}

//========================================
// 描画
//========================================
void CStage::Draw(void)
{
	CObject2D::Draw();
}

//========================================
// 位置設定
//========================================
void CStage::SetStageInfo(int nType, int nPlace)
{
	if (!m_Info.bMove)
	{
		// 位置
		m_Info.nPlace += nPlace;
		IntLoopControl(&m_Info.nPlace, PLACE_MAX, 0);

		m_Info.TargetPos = m_Place[m_Info.nPlace];
		m_Info.bMove = true;

		// 画像
		m_Info.nType += nType;
		IntLoopControl(&m_Info.nType, CGame::Stage_MAX, 0);

		if (m_Info.nPlace == PLACE_CENTER)
		{
			m_Info.TargetSize = D3DXVECTOR2(300.0f, 300.0f);
		}
		else
		{
			m_Info.TargetSize = D3DXVECTOR2(150.0f, 150.0f);
		}

		switch (m_Info.nType)
		{
		case CGame::Stage_EASY:
			BindTexture(CTexture::TEX_STAGE_EASY);
			break;
		case CGame::Stage_NORMAL:
			BindTexture(CTexture::TEX_STAGE_NORMAL);
			break;
		case CGame::Stage_DIFFICULT:
			BindTexture(CTexture::TEX_STAGE_DIFFICULT);
			break;
		}
	}
}