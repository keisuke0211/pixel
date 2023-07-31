//========================================
// 
// �Q�[��
// 
//========================================
// *** game.h ***
//========================================
#ifndef _GAME_H_
#define _GAME_H_

#include "../main.h"
#include "../manager.h"

//****************************************
// �O���錾
//****************************************
class CTime;			// �^�C��
class CScore;			// �X�R�A

//****************************************
// �N���X
//****************************************
class CGame : public CScene
{
	static const int MAX_TIME = 99;	// ��������
public:

	// ***** �֐� *****
	CGame();
	virtual~CGame();

	// -- ���C�� ------------------------------------------
	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);
	/* ����		*/static CGame *Create(void);
	/* �G�l�~�[	*/void SetEnemy(void);

	// -- �ǂݍ��� ----------
	/* �G�l�~�[	*/static void LoodEnemy(void);
	/* �u���b�N */static void LoodBlock(void);

	// -- �ݒ� ------------------------
	/* �o��		*/static void SetExit(bool bExit) { m_bExit = bExit; }
	/* �N���A	*/static void SetClear(bool bClear) { m_bClear = bClear; }

	// -- �擾 ------------------------
	/* �^�C��		*/static CTime *GetTime() { return m_pTime; }
	/* �X�R�A		*/static CScore *GetScore() { return m_pScore; };
	/* �J�n			*/static bool IsStart() { return m_bStart; }
	/* �o��			*/static bool IsExit() { return m_bExit; }
	/* �N���A		*/static bool IsClear() { return m_bClear; }

private:

	// ***** �ϐ� *****
	/* �^�C��		*/static CTime *m_pTime;
	/* �X�R�A		*/static CScore *m_pScore;

	D3DXVECTOR3 posV;			// ���_�̕ۑ�
	D3DXVECTOR3 posR;			// �����_�̕ۑ�

	int m_nStartTime;		// �J�n����
	int m_nEndTime;			// �I������

	bool m_bEnd;			// �I���t���O
	static bool m_bStart;	// �J�n�t���O
	static bool m_bExit;	// �o���@�i�o�����J�����̃t���N�j
	static bool m_bClear;	// �N���A�t���O
};

#endif