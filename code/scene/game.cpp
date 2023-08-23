//========================================
// 
// �Q�[��
// 
//========================================
// *** game.cpp ***
//========================================
#include "title.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
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
#include "../system/words/text.h"
#include "../system/words/font.h"
#include "../system/camera.h"
#include "../scene/pause.h"
#include "fade.h"

// �ÓI�ϐ�
CPlayer *CGame::m_pPlayer = NULL;
CTime *CGame::m_pTime = NULL;
CScore *CGame::m_pScore = NULL;

//========================================
// �R���X�g���N�^
//========================================
CGame::CGame()
{
	m_rot = INIT_D3DXVECTOR3;
	m_nStartTime = 0;
	m_nEndTime = 0;
	m_bEnd = false;
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
	CTitle::SetStart(false);
	CTitle::SetExit(false);
	CTitle::SetClear(false);

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
		m_pTime = CTime::Create();

		// �T�C�Y�ݒ�
		m_pTime->SetSize(20.0f, 20.0f);

		// �ʒu�ݒ�
		m_pTime->SetPos(D3DXVECTOR3(SCREEN_WIDTH - 260.0f, 32.0f, 0.0f));

		// �^�C���ݒ�
		m_pTime->SetTime(GAME_TIME*2);
	}

	{
		// �X�R�A����
		m_pScore = CScore::Create();

		// �T�C�Y�ݒ�
		m_pScore->SetSize(20.0f, 20.0f);

		// �ʒu�ݒ�
		m_pScore->SetPos(D3DXVECTOR3(SCREEN_WIDTH - 260.0f, 52.0f, 0.0f));

		// �X�R�A�ݒ�
		CScore::SetScore();
	}

	CText::Create(CText::BOX_NORMAL,
		D3DXVECTOR3(640.0f, 300.0f, 0.0f),
		D3DXVECTOR2(440.0f, 100.0f),
		"�����X�e�[�W�I\n�U�O�b�ȓ��ōU������I",
		CFont::FONT_DOTGOTHIC,
		20.0f,
		15, 10, 30, false);
	m_nStartTime = (15 * 18) + 10 + 25;
	m_nMoveRot = ((D3DX_PI * 2) / m_nStartTime);

	return S_OK;
}

//========================================
// �I��
//========================================
void CGame::Uninit(void)
{
	CObject::ReleaseAll(CObject::TYPE_BG);
	CObject::ReleaseAll(CObject::TYPE_BLOCK);
	CObject::ReleaseAll(CObject::TYPE_CUBE);
	CObject::ReleaseAll(CObject::TYPE_PLAYER);
	CObject::ReleaseAll(CObject::TYPE_ENEMY);
	CObject::ReleaseAll(CObject::TYPE_EFFECT);
	CObject::ReleaseAll(CObject::TYPE_PARTICLE);
	CObject::ReleaseAll(CObject::TYPE_TIME);
	CObject::ReleaseAll(CObject::TYPE_SCORE);
	CObject::ReleaseAll(CObject::TYPE_TEXT2D);
	CObject::ReleaseAll(CObject::TYPE_FONT);
}

//========================================
// �X�V
//========================================
void CGame::Update(void)
{
	// -- �擾 -------------------------------------------
	CCamera *pCamera = CManager::GetCamera();					// �J����
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// �W���C�p�b�g

	// �|�[�Y
	if (pInputKeyboard->GetTrigger(DIK_P) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_START))
	{
		CPause::SetPause(true);
	}

	// �J�n�t���O
	{
		bool bStart = CTitle::IsStart();
		if (!bStart)
		{
			pCamera->SetRot(m_rot);
			m_rot.y += m_nMoveRot;

			if (--m_nStartTime <= 0)
			{
				pCamera->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				pCamera->SetHeigth(0.4f);
				pCamera->SetDistance(500.0f);
				CTitle::SetStart(true);
			}
		}
	}

	// �G�l�~�[�̑S��
	{
		bool bExit = CTitle::IsExit();
		if (!bExit && CEnemy::GetEnemyAll() <= 0)
		{
			CTitle::SetExit(true);
		}
	}

	if (CFade::GetFade() == CFade::FADE_NONE)
	{
		// CLEAR
		{
			bool bClear = CTitle::IsClear();

			if (bClear)
			{
				if (!m_bEnd)
				{
					CText::Create(CText::BOX_NORMAL,
						D3DXVECTOR3(640.0f, 300.0f, 0.0f),
						D3DXVECTOR2(440.0f, 100.0f),
						"GAME CLEAR",
						CFont::FONT_DOTGOTHIC,
						20.0f,
						12, 10, 30, false);

					m_nEndTime = (12 * 10) + 10 + 25;
					m_bEnd = true;
				}
				else
				{
					if (--m_nEndTime <= 0)
					{
						CResult::SetVerdict(CResult::VERDICT_GAMECLEAR);
						CManager::GetFade()->SetFade(MODE_RANKING);

						CRanking::SetScore11(m_pScore->GetScore());
					}
				}
			}
		}

		// ���Ԑ؂�
		if (m_pTime->GetTime() <= 0)
		{
			if (!m_bEnd)
			{
				CText::Create(CText::BOX_NORMAL,
					D3DXVECTOR3(640.0f, 300.0f, 0.0f),
					D3DXVECTOR2(440.0f, 100.0f),
					"TIME UP",
					CFont::FONT_DOTGOTHIC,
					20.0f,
					12, 10, 30, false);

				m_nEndTime = (12 * 7) + 10 + 25;
				m_bEnd = true;
			}
			else
			{
				if (--m_nEndTime <= 0)
				{
					CResult::SetVerdict(CResult::VERDICT_GAMEOVER);
					CManager::GetFade()->SetFade(MODE_RANKING);
				}
			}
		}
	}
}

//========================================
// �`��
//========================================
void CGame::Draw(void)
{

}

//========================================
// ����
//========================================
CGame *CGame::Create(void)
{
	CGame *pGame = new CGame;

	pGame->Init();

	return pGame;
}

//========================================
// �u���b�N�̓ǂݍ���
//========================================
void CGame::LoodBlock(void)
{
	CSVFILE *pFile = new CSVFILE;

	// �ǂݍ���
	pFile->FileLood("data\\GAMEDATA\\BLOCK\\STAGE_DATA1.csv", true, true, ',');

	// �s���̎擾
	int nRowMax = pFile->GetRowSize();

	// �e�f�[�^�ɑ��
	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		// �z�u���̐���
		int nType;				// ���
		int nState;				// ���
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
			case 4: pFile->ToValue(nState, sData); break;	// ���
			}
		}

		// �ő吔�ɒB������Ԃ�
		if (nRow == nRowMax - 1)	// (�� - ��̍ő吔 - �w�b�_�[�̗�)
		{
			return;
		}

		// �z�u
		CBlock *pObj = CBlock::Create(nType, pos,nState);
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

	pFile->FileLood("data\\GAMEDATA\\ENEMY\\STAGE_ENEMY1.csv", true, true, ',');

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