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
	int nTextTime;
	int nStandTime;
};

#endif