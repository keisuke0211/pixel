//========================================
// 
// �����L���O
// 
//========================================
// *** ranking.h ***
//========================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "../main.h"
#include "../manager.h"

//****************************************
// �O���錾
//****************************************
class CWords;

//****************************************
// �N���X
//****************************************
class CRanking : public CScene
{
public:

	// ***** �֐� *****
	CRanking();
	~CRanking();

	// -- ���C�� ------------------------------------------
	/* ������		*/HRESULT Init(void);
	/* �I��			*/void Uninit(void);
	/* �X�V			*/void Update(void);
	/* �`��			*/void Draw(void);
	/* ����			*/static CRanking *Create(void);

private:

	// ***** �ϐ� *****
};

#endif