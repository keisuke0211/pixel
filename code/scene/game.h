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
class CTime;	// �^�C��
class CScore;	// �X�R�A
class CPlayer;	// �v���C���[
class CText;	// �e�L�X�g

//****************************************
// �N���X
//****************************************
class CGame : public CScene
{
	static const int GAME_TIME = 90;				// ��������
	static const int ADDTIME_MAX = 120;				// �{�[�i�X���X�R�A�ɉ��Z���鎞��
	static const int MAX_CUBE = 30;					// �X�e�[�W�Ŕz�u�o����L���[�u�̐���
	static const char* STAGE_INFO_FILE;				// �X�e�[�W���̃t�@�C���p�X
	static const char* SIDE_STAGE_FILE;				// ���ʂ̃t�@�C��
	static const char* FLOOR_STAGE_FILE;			// ���̃t�@�C��

	static const int TIME_SCORE = 100;	// �P�b�̃X�R�A�̉��Z�l
	static const int CUBE_SCORE = 10;	// �P�̃X�R�A�̉��Z�l

public:

	// ***** �񋓌^ *****

	// �X�e�[�W
	enum Stage
	{
		Stage_EASY = 0,		// ����
		Stage_NORMAL,		// ����
		Stage_DIFFICULT,	// ���
		Stage_MAX
	};

	// ***** �֐� *****
	CGame();
	virtual~CGame();

	// -- ���C�� ------------------------------------------
	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);
	/* ����		*/static CGame *Create(void);
	
	// -- �ǂݍ��� ------------------------------------------
	/* �X�e�[�W���	*/static void LoodStage(void);
	/* �w�i�@�V��	*/static void LoodCeiling(void);
	/* �w�i�@����	*/static void LoodSide(void);
	/* ��			*/static void LoodFloor(void);
	/* �u���b�N		*/static void LoodBlock(void);
	/* �G�l�~�[		*/static void LoodEnemy(void);

	// -- �ݒ� ------------------------------------------
	/* �X�e�[�W�I��	*/static void SetStage(int nStage);
	/* ���Z�b�g		*/static void Reset(void);

	// -- �擾 ------------------------------------------
	/* �v���C���[	*/static CPlayer *GetPlayer() { return m_pPlayer; }
	/* �^�C��		*/static CTime *GetTime() { return m_pTime; }
	/* �X�R�A		*/static CScore *GetScore() { return m_pScore; };
	/* ���ԃt���O	*/static bool IsTime() { return m_bTime; }
	
	static int m_nStage;							// ���݂̃X�e�[�W 

	// �X�e�[�W���
	struct StageInfo
	{
		int nTime[Stage_MAX];
		char aBlockFile[Stage_MAX][TXT_MAX];
		char aEnemyFile[TXT_MAX];
	};

	static StageInfo m_aStageInfo;

private:

	// ***** �񋓌^ *****

	// ���U���g���o
	enum Rst
	{
		RST_TIME = 0,	// �^�C���{�[�i�X(�e�L�X�g)
		RST_TIME_CALC,	// �^�C���{�[�i�X(�v�Z)
		RST_CUBE,		// �L���[�u�{�[�i�X(�e�L�X�g)
		RST_CUBE_CALC,	// �L���[�u�{�[�i�X(����)
		RST_BONUS,		// �{�[�i�X�̍��v(�e�L�X�g)
		RST_BONUS_CALC,	// �{�[�i�X�̍��v(�v�Z)
		RST_ADD_SCORE,	// �X�R�A���Z
		RST_STAND,		// �ҋ@
		RST_END,		// �����L���O��ʂɈړ�
		RST_MAX
	};

	// ***** �֐� *****
	/* ���U���g	*/void  Result(void);

	// ***** �ϐ� *****
	/* �v���C���[	*/static CPlayer *m_pPlayer;
	/* �^�C��		*/static CTime *m_pTime;
	/* �X�R�A		*/static CScore *m_pScore;

	D3DXVECTOR3 m_rot;					// ����
	float m_nMoveRot;					// �����̉����x
	int m_nStartTime;					// �J�n����
	int m_nEndTime;						// �I������
	int m_nRstStgType;					// ���U���g���o�̎��
	int m_nTextCreate;					// ���̃e�L�X�g�̐�������܂ł̎���

	bool m_bEnd;						// �I���t���O

	int m_nTimeTotal;					// �^�C���{�[�i�X�̍��v�l
	int m_nCubeTotal;					// �L���[�u�{�[�i�X�̍��v�l
	int m_nTotal;						// �S�Ă̍��v�l
	int m_nAddTime;						// �X�R�A�̉��Z����
	int m_nStandTime;					// �ҋ@����(���U���g���o�I����)
	CText *m_RstText[RST_ADD_SCORE];	// �e�L�X�g�\��
	bool m_bAddScore;					// �X�R�A�̉��Z�t���O
	static bool m_bTime;				// ���ԃt���O
	static int m_nScore;				// �X�R�A�̕ۑ��p
	static int m_nSelectStage;			// ���ݑI�����Ă���X�e�[�W 
};

#endif