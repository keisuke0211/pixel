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
class CPlayer;			// �v���C���[

//****************************************
// �N���X
//****************************************
class CGame : public CScene
{
	static const int GAME_TIME = 60;	// ��������
	static const char* CEILING_FILE;	// �V��̃t�@�C���p�X
	static const char* SIDE_FILE;		// ���ʂ̃t�@�C���p�X
	static const char* FLOOR_FILE;		// ���̃t�@�C���p�X
	static const char* BLOCK_FILE1;		// �u���b�N�̃t�@�C���p�X
	static const char* ENEMY_FILE1;		// �G�l�~�[�̃t�@�C���p�X

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

	// -- �ǂݍ��� ----------
	/* �w�i�@�V��	*/static void LoodCeiling(void);
	/* �w�i�@����	*/static void LoodSide(void);
	/* ��			*/static void LoodFloor(void);
	/* �u���b�N		*/static void LoodBlock(void);
	/* �G�l�~�[		*/static void LoodEnemy(void);

	// -- �擾 ------------------------
	/* �v���C���[	*/static CPlayer *GetPlayer() { return m_pPlayer; }
	/* �^�C��		*/static CTime *GetTime() { return m_pTime; }
	/* �X�R�A		*/static CScore *GetScore() { return m_pScore; };
	
private:

	// ***** �ϐ� *****
	/* �v���C���[	*/static CPlayer *m_pPlayer;
	/* �^�C��		*/static CTime *m_pTime;
	/* �X�R�A		*/static CScore *m_pScore;

	D3DXVECTOR3 m_rot;		// ����
	float m_nMoveRot;		// �����̉����x
	int m_nStartTime;		// �J�n����
	int m_nEndTime;			// �I������

	bool m_bEnd;			// �I���t���O
};

#endif