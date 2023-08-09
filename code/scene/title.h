//========================================
// 
// �^�C�g��
// 
//========================================
// *** title.h ***
//========================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "../main.h"
#include "../manager.h"

//****************************************
// �O���錾
//****************************************
class CWords;
class CText;

//****************************************
// �N���X
//****************************************
class CTitle : public CScene
{
	// ***** ��` *****
	static const int STAND_MAX = 20;	// �e�L�X�g�̑ҋ@����
	static const int TEXT_TIME = 150;	// �e�L�X�g�̕\������
	static const int WORDS_MAX = 4;		// �����̍ő吔
	static const int TEXT_MAX = 3;		// �e�L�X�g�̍ő吔

public:

	// ***** �񋓌^ *****

	// �^�C�g�����[�h
	enum TITLE
	{
		TITLE_OUTSET = 0,	// �^�C�g��
		TITLE_MENU,			// ���j���[
		TITLE_NEXT,			// ���̉�ʂɈړ� 
		TITLE_MAX
	};

	// ���j���[
	enum MENU
	{
		MENU_GAME = 0,	// �Q�[��
		MENU_TUTORIAL,	// �`���[�g���A��
		MENU_RANKING,	// �����L���O
		MENU_END,		// �I��
		MENU_MAX
	};

	// ***** �֐� *****
	CTitle();
	~CTitle();

	// -- ���C�� ------------------------------------------
	/* ������		*/HRESULT Init(void);
	/* �I��			*/void Uninit(void);
	/* �X�V			*/void Update(void);
	/* �`��			*/void Draw(void);
	/* ����			*/static CTitle *Create(void);
	/* �^�C�g��		*/void TitleAnime(void);
	/* ���j���[���� */void MenuCreate(void);
	/* ���j���[		*/void Menu(void);
	/* �e�L�X�g�폜 */void TextClear(int nWords,int nText, TITLE aTitle);

	// -- �ݒ� ------------------------------------------
	/* �J�n		*/static void SetStart(bool bStart) { m_bStart = bStart; }
	/* �o��		*/static void SetExit(bool bExit) { m_bExit = bExit; }
	/* �N���A	*/static void SetClear(bool bClear) { m_bClear = bClear; }

	// -- �擾 ------------------------------------------
	/* �J�n			*/static bool IsStart() { return m_bStart; }
	/* �o��			*/static bool IsExit() { return m_bExit; }
	/* �N���A		*/static bool IsClear() { return m_bClear; }

private:

	// ***** �ÓI�ϐ� *****
	static bool m_bStart;	// �J�n�t���O
	static bool m_bExit;	// �o���@�i�o�����J�����̃t���N�j
	static bool m_bClear;	// �N���A�t���O

	// ***** �ϐ� *****
	TITLE Title;	// ���݂̃��[�h
	CWords *m_Words[4]; // �^�C�g��
	bool m_bMove[4];
	CText *m_Text[MENU_MAX];
	int m_nTextTime;	// �e�L�X�g�̕\������
	int m_nStandTime;	// �ҋ@����
	int m_nSelectMenu;	// ���ݑI�����Ă��郁�j���[
};

#endif