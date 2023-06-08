//========================================
//
// �X�R�A
//
//========================================
// *** score.h ***
//========================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "../object.h"
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

	CScore(int nPriority = TYPE_SCORE);
	~CScore();

	// *****  �֐� *****

	/* ���C�� */
	HRESULT Init(void);		// ������
	void Uninit(void);		// �I��
	void Update(void);		// �X�V
	void Draw(void);		// �`��
	static void SetScore(int nScore = 0);	// �ݒ�

	// ����
	static CScore *Create(void);

private:
	// ***** �ϐ� *****
	static int m_nScore;
};
#endif 