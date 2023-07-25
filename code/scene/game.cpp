//========================================
// 
// �Q�[��
// 
//========================================
// *** game.cpp ***
//========================================
#include "game.h"
#include "../system/csv_file.h"
#include "../object\UI\score.h"
#include "../object\UI\time.h"
#include "../object\model\block.h"
#include "../object\model\player.h"
#include "../object\model\enemy.h"
#include "../object\BG\bg_side.h"
#include "../object\BG\bg_ceiling.h"
#include "../object\UI\text2D.h"
#include "../system/input.h"
//#include "fade.h"

//========================================
// �R���X�g���N�^
//========================================
CGame::CGame()
{

}

//========================================
// �f�X�g���N�^
//========================================
CGame::~CGame()
{

}

//========================================
// ������
//========================================
HRESULT CGame::Init(void)
{
	// �w�i(����)�̐���
	CBgSide *pBgsky = CBgSide::Create();

	// �w�i(�V��)�̐���
	CBgCeiling *pBgCeiling = CBgCeiling::Create();

	// �u���b�N�̐���
	LoodBlock();

	CPlayer *pPlayer = CPlayer::Create();
	pPlayer->SetMotion("data\\GAMEDATA\\MODEL\\Player\\PLAYER_DATA.txt");

	// �G�̐���
	LoodEnemy();

	{
		// �^�C������
		CTime *pObj = CTime::Create();

		// �T�C�Y�ݒ�
		pObj->SetSize(20.0f, 20.0f);

		// �ʒu�ݒ�
		pObj->SetPos(D3DXVECTOR3(SCREEN_WIDTH - 260.0f, 32.0f, 0.0f));

		// �^�C���ݒ�
		pObj->SetTime(99);
	}

	{
		// �X�R�A����
		CScore *pObj = CScore::Create();

		// �T�C�Y�ݒ�
		pObj->SetSize(20.0f, 20.0f);

		// �ʒu�ݒ�
		pObj->SetPos(D3DXVECTOR3(SCREEN_WIDTH - 260.0f, 52.0f, 0.0f));

		// �X�R�A�ݒ�
		CScore::SetScore();
	}

	{
		{// �ړ����@�e�L�X�g
			CText2D *pObj = CText2D::Create();

			pObj->SetPos(D3DXVECTOR3(32.0f, 32.0f, 0.0f));
			pObj->SetSize(16.0f, 16.0f);
			pObj->SetString("MOVE : W A D S");
		}

		{// �W�����v���@�e�L�X�g
			CText2D *pObj = CText2D::Create();

			pObj->SetPos(D3DXVECTOR3(32.0f, 48.0f, 0.0f));
			pObj->SetSize(16.0f, 16.0f);
			pObj->SetString("JUMP : SPACE");
		}

		{// �ˌ����@�e�L�X�g
			CText2D *pObj = CText2D::Create();

			pObj->SetPos(D3DXVECTOR3(32.0f, 64.0f, 0.0f));
			pObj->SetSize(16.0f, 16.0f);
			pObj->SetString("SHOT : ENTER & MOUSE_LEFT");
		}

		{// �z�u�e�L�X�g
			CText2D *pObj = CText2D::Create();

			pObj->SetPos(D3DXVECTOR3(32.0f, 80.0f, 0.0f));
			pObj->SetSize(16.0f, 16.0f);
			pObj->SetString("SET_CUBE : E");
		}

		{// �J�����؂�ւ��e�L�X�g
			CText2D *pObj = CText2D::Create();

			pObj->SetPos(D3DXVECTOR3(32.0f, 128.0f, 0.0f));
			pObj->SetSize(16.0f, 16.0f);
			pObj->SetString("CAMERA_MODE : Q");
		}

		{// �J�����ړ����@�e�L�X�g
			CText2D *pObj = CText2D::Create();

			pObj->SetPos(D3DXVECTOR3(32.0f, 144.0f, 0.0f));
			pObj->SetSize(16.0f, 16.0f);
			pObj->SetString("CAMERA_MOVE : MOUSE_RIGHT");
		}

		{// ���Z�b�g���@�e�L�X�g
			CText2D *pObj = CText2D::Create();

			pObj->SetPos(D3DXVECTOR3(32.0f, 176.0f, 0.0f));
			pObj->SetSize(16.0f, 16.0f);
			pObj->SetString("RESET:R");
		}
	}

	return S_OK;
}

//========================================
// �I��
//========================================
void CGame::Uninit(void)
{
	CObject::ReleaseAll(CObject::TYPE_BLOCK);
	CObject::ReleaseAll(CObject::TYPE_CUBE);
	CObject::ReleaseAll(CObject::TYPE_PLAYER);
	CObject::ReleaseAll(CObject::TYPE_ENEMY);
	CObject::ReleaseAll(CObject::TYPE_EFFECT);
	CObject::ReleaseAll(CObject::TYPE_PARTICLE);
	CObject::ReleaseAll(CObject::TYPE_TIME);
	CObject::ReleaseAll(CObject::TYPE_SCORE);

}

//========================================
// �X�V
//========================================
void CGame::Update(void)
{
	// �G�l�~�[�̑S��
	if (CEnemy::GetEnemyAll() <= 0)
	{
		//CManager::GetFade()->SetFade(MODE_RESULT);
		CManager::SetMode(MODE_RESULT);
	}
}

//========================================
// �`��
//========================================
void CGame::Draw(void)
{

}
//========================================
// �Z�b�g�G�l�~�[
//========================================
void CGame::SetEnemy(void)
{
	// �G��S�Ĕj��
	CObject::ReleaseAll(CObject::TYPE_ENEMY);

	// �G�̐���
	LoodEnemy();
}

//========================================
// �u���b�N�̓ǂݍ���
//========================================
void CGame::LoodBlock(void)
{
	CSVFILE *pFile = new CSVFILE;

	// �ǂݍ���
	pFile->FileLood("data\\GAMEDATA\\BLOCK\\STAGE_DATA.csv", true, true, ',');

	// �s���̎擾
	int nRowMax = pFile->GetRowSize();

	// �e�f�[�^�ɑ��
	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		// �z�u���̐���
		int nType;				// ���
		D3DXVECTOR3 pos;		// �ʒu

								// �񐔂̎擾
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0:	pFile->ToValue(nType, sData); break;	// ���
			case 1:	pFile->ToValue(pos.x, sData); break;	// �ʒu X
			case 2:	pFile->ToValue(pos.y, sData); break;	// �ʒu Y
			case 3:	pFile->ToValue(pos.z, sData); break;	// �ʒu Z
			}
		}

		// �ő吔�ɒB������Ԃ�
		if (nRow == nRowMax - 1)	// (�� - ��̍ő吔 - �w�b�_�[�̗�)
		{
			return;
		}

		// �z�u
		CBlock *pObj = CBlock::Create(nType, pos);
	}

	// �������J��
	delete pFile;
	pFile = NULL;
}

//========================================
// �G�l�~�[�̓ǂݍ���
//========================================
void CGame::LoodEnemy(void)
{
	CSVFILE *pFile = new CSVFILE;

	pFile->FileLood("data\\GAMEDATA\\ENEMY\\STAGE_DATA1.csv", true, true, ',');

	// �s���̎擾
	int nRowMax = pFile->GetRowSize();

	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		int nType, nMove;
		D3DXVECTOR3 pos;

		// �񐔂̎擾
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0:	pFile->ToValue(nType, sData); break;	// ���
			case 1:	pFile->ToValue(nMove, sData); break;	// �ړ����
			case 2:	pFile->ToValue(pos.x, sData); break;	// �ʒu X
			case 3:	pFile->ToValue(pos.y, sData); break;	// �ʒu Y
			case 4:	pFile->ToValue(pos.z, sData); break;	// �ʒu Z
			}
		}

		// �ő吔�ɒB������Ԃ�
		if (nRow == nRowMax - 1)	// (�� - ��̍ő吔 - �w�b�_�[�̗�)
		{
			return;
		}

		CEnemy *pObj = CEnemy::Create(nType, nMove, pos);
	}

	delete pFile;
	pFile = NULL;
}