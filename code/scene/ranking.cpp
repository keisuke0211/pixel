//========================================
// 
// �����L���O
// 
//========================================
// *** ranking.h ***
//========================================
#include "ranking.h"

//========================================
// �R���X�g���N�^
//========================================
CRanking::CRanking()
{

}

//========================================
// �f�X�g���N�^
//========================================
CRanking::~CRanking()
{

}

//========================================
// ������
//========================================
HRESULT CRanking::Init(void)
{

	return S_OK;
}

//========================================
// �I��
//========================================
void CRanking::Uninit(void)
{

}

//========================================
// �X�V
//========================================
void CRanking::Update(void)
{

}

//========================================
// �`��
//========================================
void CRanking::Draw(void)
{

}

//========================================
// ����
//========================================
CRanking *CRanking::Create(void)
{
	CRanking *pRanking = new CRanking;

	pRanking->Init();

	return pRanking;
}