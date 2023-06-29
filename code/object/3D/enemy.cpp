//========================================
// 
// �G�l�~�[����
// 
//========================================
// *** enemy.cpp ***
//========================================
#include "enemy.h"
#include "../../manager.h"
#include "../../renderer.h"
#include "../../sound.h"
#include "../2D/score.h"


// �ÓI�ϐ�
CEnemy::SetInfo *CEnemy::pSet = NULL;
int CEnemy::nNumSet = 0;

//========================================
// �R���X�g���N�^
//========================================
CEnemy::CEnemy(int nPriority) : CObjectX(nPriority)
{
	// �l���N���A
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.move = INIT_D3DXVECTOR3;
	m_Info.nType = 0;
	m_Info.nLife = 0;
}

//========================================
// �f�X�g���N�^
//========================================
CEnemy::~CEnemy()
{

}

//========================================
// ����
//========================================
CEnemy *CEnemy::Create(void)
{
	CEnemy *pEnemy = new CEnemy;

	pEnemy->SetModel(9);

	// ����������
	pEnemy->Init();

	return pEnemy;
}

//========================================
// ������
//========================================
HRESULT CEnemy::Init(void)
{
	CObjectX::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_ENEMY);

	m_Info.pos = D3DXVECTOR3(0.0f, -20.0f, -150.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nLife = 1;
	m_Info.nType = 0;

	// ����
	SetPos(m_Info.pos);
	SetRot(m_Info.rot);
	SetColor(m_Info.col);

	return S_OK;
}

//========================================
// �I��
//========================================
void CEnemy::Uninit(void)
{
	CObjectX::Uninit();
}

//========================================
// �X�V
//========================================
void CEnemy::Update(void)
{
	// �ʒu����
	m_Info.posOld = m_Info.pos;

	CObjectX::Update();
}

//========================================
// �`��
//========================================
void CEnemy::Draw(void)
{
	CObjectX::Draw();
}

//========================================
// �q�b�g����
//========================================
void CEnemy::HitLife(int nDamage)
{
	CSound *pSound = CManager::GetSound();

	m_Info.nLife -= nDamage;

	if (m_Info.nLife >= 0)
	{
		//for (int nCntPtcl = 0; nCntPtcl < 16; nCntPtcl++) 
		//{
		//	// �G�t�F�N�g2D����
		//	CParticle2D *pObj = CParticle2D::Create();
		//	// �ʒu�ݒ�
		//	pObj->SetPos(GetPos());
		//	// �����ݒ�
		//	pObj->SetRot(D3DXVECTOR3(0.0f, 0.0f, ((float)rand() / RAND_MAX) * D3DX_PI * 2.0f));
		//	// �ړ��ʐݒ�
		//	pObj->SetMove(5.0f + (5.0f * ((float)rand() / RAND_MAX)));
		//	// �����ݒ�
		//	pObj->SetLife(8 + (rand() % 24));
		//}

		// �G�̔j��
		Uninit();

		// �X�R�A�ݒ�
		CScore::SetScore(300);

		pSound->PlaySound(3);

		return;
	}
	else
	{
		pSound->PlaySound(2);
	}
}

//========================================
// �ǂݍ���
//========================================

//void CEnemy::Load(void)
//{
//	CSVFILE<int> data;
//
//	// �ǂݍ���
//	data.csv_read("data\\GAMEDATA\\BLOCK\\BLOCK_DATA.csv", true, true, ',');
//
//	// ���I�m��
//	int nLineMax = data.cell.size() - 1;
//	pSet = new SetInfo[nLineMax];
//
//	for (int nLine = 0; nLine < data.cell.size(); nLine++)
//	{
//		int nRowMax = data.cell.at(nLine).size();
//
//		for (int nRow = 0; nRow < data.cell.at(nLine).size(); nRow++)
//		{
//			switch (nRow)
//			{
//				// ���
//			case SET_TYPE:
//			{
//				pSet[nLine].nType = (int)data.cell.at(nLine).at(nRow);
//			}
//			break;
//
//			// �ʒu
//			case SET_POS:
//			{
//				pSet[nLine].pos.x = (int)data.cell.at(nLine).at(nRow); nRow++;
//				pSet[nLine].pos.y = (int)data.cell.at(nLine).at(nRow); nRow++;
//				pSet[nLine].pos.z = (int)data.cell.at(nLine).at(nRow);
//			}
//			break;
//
//			// �ړ���
//			case SET_SPEED:
//			{
//				pSet[nLine].nSpeed = data.cell.at(nLine).at(nRow);
//			}
//			break;
//
//			// ����ID
//			case SET_UNIT:
//			{
//				pSet[nLine].nStage = (int)data.cell.at(nLine).at(nRow);
//			}
//			break;
//
//			// �X�e�[�WID
//			case SET_STAGE:
//			{
//				pSet[nLine].nStage = (int)data.cell.at(nLine).at(nRow);
//			}
//			break;
//			}
//		}
//	}
//}

//========================================
// �z�u
//========================================
void CEnemy::SetEnemy(int nStage, int nUnit)
{
	for (int nCntSet = 0; nCntSet < nNumSet; nCntSet++, pSet++)
	{
		if (!pSet->bSet && pSet->nStage == nStage && pSet->nUnit == nUnit)
		{


			pSet->bSet = true;
		}
	}
}