//========================================
// 
// �e�X�g
// 
//========================================
// *** corown.h ***
//========================================
#include "test.h"
#include "../../manager.h"
#include "../../system/renderer.h"
#include "../../system/texture.h"

LPDIRECT3DTEXTURE9 CTest::m_pTexture = NULL;

//========================================
// �R���X�g���N�^
//========================================
CTest::CTest(int nPriority) : CObject2D(nPriority)
{
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.size = INIT_D3DXVECTOR2;
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nLife = 0;
	m_Info.nLifeMax = 0;
}

//========================================
// �f�X�g���N�^
//========================================
CTest::~CTest()
{

}

//========================================
// ����
//========================================
CTest *CTest::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CTest *pObj = new CTest;

	pObj->m_Info.pos = pos;
	pObj->m_Info.rot = rot;
	pObj->m_Info.size = D3DXVECTOR2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	pObj->m_Info.nLife = 330;
	pObj->m_Info.nLifeMax = 330;
	pObj->Init();

	return pObj;
}

//========================================
// ������
//========================================
HRESULT CTest::Init(void)
{
	CObject2D::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_BG);

	// �ݒ�
	SetPos(m_Info.pos);
	SetRot(m_Info.rot);
	SetSize(m_Info.size.x, m_Info.size.y);
	SetColar(D3DXCOLOR(1, 1, 1, 1));

	return S_OK;
}

//========================================
// �I��
//========================================
void CTest::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================
// �X�V
//========================================
void CTest::Update(void)
{
	/*if (--m_Info.nLife <= 0 || m_Info.col.a <= 0.1f)
	{
		Uninit();
		return;
	}

	m_Info.col.a *= ((float)m_Info.nLife / m_Info.nLifeMax);*/
	CObject2D::SetColar(m_Info.col);

	CObject2D::Update();
}

//========================================
// �`��
//========================================
void CTest::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();

	//LPDIRECT3DTEXTURE9 pTexture = pRenderer->GetTextureMT();

	SetTexture(m_pTexture);

	CObject2D::Draw();
}

//========================================
// �e�N�X�`���ݒ�
//========================================
void CTest::TextSetTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}