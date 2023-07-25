//========================================
//
// �X�R�A
//
//========================================
// *** score.h ***
//========================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "../../main.h"
#include "text2D.h"

//****************************************
// �}�N����`
//****************************************
#define	MAX_SCORE	(8)

//****************************************
// �O���錾
//****************************************
class CText2D;

//****************************************
// �N���X
//****************************************
class CScore : public CText2D
{
public:

	CScore(int nPriority = PRIO_UI);
	~CScore();

	// *****  �֐� *****

	// -- ���C�� ---------------------------------
	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);
	/* ����		*/static CScore *Create(void);

	// -- �ݒ� ---------------------------------
	/* �X�R�A	*/static void SetScore(int nScore = 0);

	// -- �擾 ---------------------------------
	/* �X�R�A	*/int GetScore(void) { return m_nScore; }

private:
	// ***** �ϐ� *****
	static int m_nScore;
};
#endif 