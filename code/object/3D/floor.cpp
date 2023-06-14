//========================================
// 
// 床処理
// 
//========================================
// *** floor.cpp ***
//========================================
#include "floor.h"

//========================================
// コンストラクタ
//========================================
CFloor::CFloor(int nPriority) : CObject3D(nPriority)
{
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.fHeight = INIT_FLOAT;
	m_Info.fWidth = INIT_FLOAT;
}

//========================================
// デストラクタ
//========================================
CFloor::~CFloor()
{

}

//========================================
// 生成
//========================================
CFloor *CFloor::Create(void)
{
	CFloor *pFloor = NULL;

	if (pFloor != NULL)
	{
		return pFloor;
	}

	// オブジェクト2Dの生成
	pFloor = new CFloor;

	// 初期化処理
	pFloor->Init();

	return pFloor;
}

//========================================
// 初期化
//========================================
HRESULT CFloor::Init(void)
{
	CObject3D::Init();

	// 種類の設定
	SetType(TYPE_FLOOR);

	m_Info.pos = D3DXVECTOR3(0.0f,60.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 3.141592f);
	m_Info.fWidth = 250.0f;
	m_Info.fHeight = 250.0f;

	// 生成
	SetPos(m_Info.pos);
	SetRot(m_Info.rot);
	SetSize(m_Info.fWidth, m_Info.fHeight);
	SetColor(INIT_D3DXCOLOR);

	// テクスチャの割り当て
	BindTexture(10);

	return S_OK;
}

//========================================
// 終了
//========================================
void CFloor::Uninit(void)
{
	CObject3D::Uninit();
}

//========================================
// 更新
//========================================
void CFloor::Update(void)
{	
	CObject3D::Update();
}

//========================================
// 描画
//========================================
void CFloor::Draw(void)
{
	CObject3D::Draw();
}
