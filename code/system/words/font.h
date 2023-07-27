//========================================
// 
// �t�H���g
// 
//========================================
// *** font.h ***
//========================================
#ifndef _FONT_H_
#define _FONT_H_

#include "../../main.h"

//****************************************
// �N���X
//****************************************
class CFont
{

public:
	// ***** �񋓌^ *****

	// �t�H���g
	enum FONT // DotGothic
	{
		FONT_DOTGOTHIC = 0,
		FONT_MEIRIO,
		FONT_MAX,
	};

	// ***** �֐� *****
	CFont();
	virtual~CFont();

	// -- ���C�� ------------------------------------------
	/* �t�H���g�쐬		*/void FontCreate(FONT nFont);
	/* �e�N�X�`���쐬	*/void TextureCreate(string nWords, FONT nFont);
	/* �S�Ĕj��			*/void ReleaseAll(void);
	/* �w��̔j��		*/void Release(FONT nFont);

	// -- �擾 ------------------------------------------
	/* �e�N�X�`�����̎擾 */LPDIRECT3DTEXTURE9 GetFont(string words, FONT nFont);
private:

	// ***** �ÓI�ϐ� *****
	static int m_nMaxFont;				// �t�H���g��
	static const char* s_FileName[];	// �t�@�C���p�X
	static const char* s_FontName[];	// �t�@�C���p�X

										// ***** �ϐ� *****
	HFONT  m_hFont[FONT_MAX];
	LOGFONT m_logFont[FONT_MAX];
	LPDIRECT3DTEXTURE9 m_texFont[FONT_MAX];	// �e�N�X�`���̏��
};

#endif