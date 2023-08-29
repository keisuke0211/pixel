//========================================
// 
// �`���[�g���A��
// 
//========================================
// *** tutorial.h ***
//========================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "../main.h"
#include "../manager.h"

//****************************************
// �O���錾
//****************************************
class CText;
class CPlayer;
class CEnemy;

//****************************************
// �N���X
//****************************************
class CTutorial : public CScene
{
	// ***** ��` *****
	static const char* FILE_PATH;		// �ǂݍ��ރt�@�C���p�X
	static const int MAX_TIME = 99;		// ��������
	static const int NUM_TEXT = 10;		// �e�L�X�g��

	static const char* CEILING_FILE;	// �V��̃t�@�C���p�X
	static const char* SIDE_FILE;		// ���ʂ̃t�@�C���p�X
	static const char* FLOOR_FILE;		// ���̃t�@�C���p�X
	static const char* BLOCK_FILE1;		// �u���b�N�̃t�@�C���p�X
	static const char* ENEMY_FILE1;		// �G�l�~�[�̃t�@�C���p�X
public:

	// ***** �񋓌^ *****

	// �s��
	enum ACTION
	{
		ACTION_MOVE = 0,	// �ړ�
		ACTION_CAMERA,		// ���_�ړ�
		ACTION_SHOT,		// ����
		ACTION_SET,			// �z�u(��)
		ACTION_SET1,		// �z�u(�C��)
		ACTION_ENEMY,		// �G
		ACTION_CLEAR,		// �o��
		ACTION_FREE,		// ���R
		ACTION_MAX
	};

	// ***** �֐� *****
	CTutorial();
	~CTutorial();

	// -- ���C�� ------------------------------------------
	/* ������			*/HRESULT Init(void);
	/* �I��				*/void Uninit(void);
	/* �X�V				*/void Update(void);
	/* �`��				*/void Draw(void);
	/* ����				*/static CTutorial *Create(void);
	/* �ǂݍ���			*/void TextLoad(void);

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

	// ***** �\���� *****

	// �e�L�X�g���
	struct TEXT_INFO
	{
		D3DXVECTOR3 pos;			// �ʒu
		D3DXVECTOR2 size;			// �T�C�Y
		int nType;					// ���
		int nStartTime;				// �J�n����
		int nStandTime;				// �ҋ@����
		int nDisapTime;				// �����鎞��
		char *ActionTex[TXT_MAX];	// �s���e�L�X�g
		int nTextSize;				// �e�L�X�g�T�C�Y
		int nEndTime;				// �I������
		bool bCreate;				// �����t���O
		bool bEnd;					// �I���t���O
		bool bAction;				// �e�L�X�g�ɏ����ꂽ�s�����s������

		bool bTextBok;				// �e�L�X�g�{�b�N�X�̕\���t���O

	};

	// ***** �֐� *****
	/* �e�L�X�g��񏉊���	*/void TextInit(int nIdx);
	/* �e�L�X�g����			*/void TexCreate(int nIdx);
	/* �`���[�g���A��		*/void TutorialTex(void);

	// ***** �ÓI�ϐ� *****
	/* �e�L�X�g���	*/static TEXT_INFO	*m_TextInfo;
	/* �v���C���[	*/static CPlayer *m_pPlayer;
	/* �^�C��		*/static CTime *m_pTime;
	/* �X�R�A		*/static CScore *m_pScore;

	// ***** �ϐ� *****
	CText *m_Text;				// �e�L�X�g
	ACTION Action;				// �s�����
	int m_nTextMax;				// �e�L�X�g���̍ő吔
	int m_nNumText;				// ���������e�L�X�g��
	int m_nTextType;			// ���݂̕\���e�L�X�g���
	int m_nTextCreate;			// ���̃e�L�X�g�̐�������܂ł̎���

	int m_nStartTime;			// �J�n����
	int m_nEndTime;				// �I������
	bool m_bEnd;				// �I���t���O

	int m_nTypeMax[ACTION_MAX];	// ��ނ��Ƃ̍ŏI�ʒu

};

#endif