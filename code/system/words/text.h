//========================================
// 
// �e�L�X�g�\��
// 
//========================================
// *** text.h ***
//========================================
#ifndef _TEXT_H_
#define _TEXT_H_

#include "../../object/object2D.h"
#include "words.h"

//****************************************
// �O���錾
//****************************************
class CFont;

//****************************************
// �N���X
//****************************************
class CText : public CObject2D
{
public:

	// ***** �񋓌^ *****

	// �e�L�X�g�{�b�N�X�̎��
	enum Box
	{
		BOX_NORMAL = 0,	// �V���v��
		BOX_MAX
	};

	// ***** �֐� *****
	CText(int nPriority = PRIO_TEXT);
	~CText();

	// -- ���C�� ------------------------------------------
	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);

	//--------------------------------------------------
	// �e�L�X�g����
	// ����1  : Box type            / ���b�Z�[�W�{�b�N�X�̉摜
	// ����2  : D3DXVECTOR3 pos     / ���b�Z�[�W�{�b�N�X�̈ʒu
	// ����3  : D3DXVECTOR2 size    / ���b�Z�[�W�{�b�N�X�̃T�C�Y
	// ����4  : CFont::FONT Type�@�@/ �t�H���g���
	// ����5  : const char *Text�@�@/ �e�L�X�g
	// ����6  : float TextSize�@�@�@/ �T�C�Y (�����l 20)
	// ����7  : int AppearTime�@�@�@/ �P�����ڂ��\�������܂ł̎��� (�����l 1)
	// ����8  : int StandTime�@�@�@ / �ҋ@���� (�����l 10)
	// ����9  : int EraseTime�@�@�@ / ������܂ł̎��� (�����l 1) �� 0 �͏����Ȃ�
	// ����10  : bool bTextBok�@�@�@ / ���b�Z�[�W�{�b�N�X�̕\���E��\�� (�����l true)
	//--------------------------------------------------
	static CText *CText::Create(Box type, D3DXVECTOR3 pos, D3DXVECTOR2 size, const char *Text, CFont::FONT FontType, float TextSize = 20, int AppearTime = 1, int StandTime = 10, int EraseTime = 1, bool bTextBok = true);

	/* �폜 */void Disap(bool bDisap);

	// -- �ݒ� ------------------------------------------
	/* �|�[�Y���̐���	*/void SetTetPause(bool bPause);
	/* �{�b�N�X�̐F		*/void SetBoxColor(D3DXCOLOR col);
	/* �e�L�X�g�̐F		*/void SetTextColor(D3DXCOLOR col);

private:

	// ***** �\���� *****

	// �e�L�X�g���
	struct Info
	{
		D3DXCOLOR col;
		float fTextSize;		// �����̃T�C�Y
		int nTextLength;		// �����̒���
		int nAppearTime;		// 1�̕��������Z�����܂ł̎���
		int nAddCount;			// ���������Z�����܂ł̃J�E���g
		int nAddLetter;			// �������ړ���邩�w��
		int nLetterPopCount;	// �������o�����ő吔
		int nLetterPopCountX;	// ���ɕ������o������
		int nNiCount;			// ���s�̐�

		int nStandTime;			// �ҋ@����
		bool bStand;			// �ҋ@�t���O

		int nDisapTime;			// �����鎞��
		int nDisapTimeMax;		// ������ő厞��
		bool bRelease;			// �����t���O

		bool bTextBok;			// �e�L�X�g�{�b�N�X�̕\���t���O
		bool bPause;			// �|�[�Y���ł��������ifalse�F�����Ȃ��j
		string sText;			// �\������e�L�X�g
		string sALLText;		// �e�L�X�g�̑S��
		CWords** words;			// ����
		CFont::FONT FontType;	// �t�H���g���
	};

	// ***** �֐� *****
	/* ��������	*/void LetterForm(void);
	/* �ҋ@		*/void StandTime(void);
	/* �폜		*/void DisapTime(void);
	/* ��������	*/bool CheckLeadByte(int nLetter);

	// -- �ݒ� ------------------------------------------
	/* �e�L�X�g �T�C�Y	*/void SetTextSize(float TextSize);
	/* �ҋ@����			*/void SetStandTime(int StandTime);
	/* �����̏�������	*/void EraseTime(int time);
	/* �����̏o������	*/void TextLetter(const char *Text, int DispText);

	// ***** �ϐ� *****
	Info m_Info;

};

#endif