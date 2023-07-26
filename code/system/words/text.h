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
	/* ������	*/HRESULT Init(void)override;
	/* �I��		*/void Uninit(void)override;
	/* �X�V		*/void Update(void)override;
	/* �`��		*/void Draw(void)override;

	//--------------------------------------------------
	// �e�L�X�g����
	// ����1  : Box type			/ �e�L�X�g�{�b�N�X�̉摜
	// ����2  : int EraseTime		/ ������܂ł̎���
	// ����3  : int DispText		/ �P�����ڂ��\�������܂ł̎���
	// ����4  : const char *Text	/ �e�L�X�g
	//--------------------------------------------------
	static CText *CText::Create(Box type, int EraseTime, int DispText, const char *Text);

private:

	// ***** �\���� *****

	// �e�L�X�g���
	struct Info
	{
		D3DXCOLOR col;
		int nDesapTimar;		// �����鎞��
		int nDesapTimarMax;		// ������ő厞��
		int nTextSize;			// �����̃T�C�Y
		int nAddTime;			// 1�̕��������Z�����܂ł̎���
		int nAddCount;			// ���������Z�����܂ł̃J�E���g
		int nAddLetter;			// �������ړ���邩�w��
		int nLetterPopCount;	// �������o�����ő吔
		int nLetterPopCountX;	// ���ɕ������o������
		int nNiCount;			// ���s�̐�
		bool bRelease;			// �����t���O
		string sText;			// �\������e�L�X�g
		string sALLText;		// �e�L�X�g�̑S��
		CWords** words;			// 
	};

	// ***** �֐� *****

	// -- �ݒ� ------------------------------------------
	/* �����̏�������	*/void EraseTime(int time);
	/* �����̏o������	*/void TextLetter(const char *Text, int DispText);
	bool CheckLeadByte(int nLetter);
	// ***** �ϐ� *****
	Info m_Info;

};

#endif