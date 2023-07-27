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

//****************************************
// �N���X
//****************************************
class CTitle : public CScene
{
public:

	// ***** �֐� *****
	CTitle();
	~CTitle();

	// -- ���C�� ------------------------------------------
	/* ������		*/HRESULT Init(void);
	/* �I��			*/void Uninit(void);
	/* �X�V			*/void Update(void);
	/* �`��			*/void Draw(void);
	/* ����			*/static CTitle *Create(void);

private:

	// ***** �ϐ� *****
	CWords *m_Words[4]; // �s�N�p�Y
	bool m_bMove[4];
	int m_nTextTime;
	int m_nStandTime;
};

#endif