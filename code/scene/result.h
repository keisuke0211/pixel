//========================================
// 
// ���U���g
// 
//========================================
// *** result.h ***
//========================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "../main.h"
#include "../manager.h"

//****************************************
// �N���X
//****************************************
class CResult : public CScene
{
public:

	// 
	enum VERDICT
	{
		VERDICT_GAMECLEAR = 0,	// �Q�[���N���A
		VERDICT_GAMEOVER,		// �Q�[���I�[�o�[
		VERDICT_MAX,
	};

	// ***** �֐� *****
	CResult();
	virtual~CResult();

	// -- ���C�� ------------------------------------------
	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);
	/* ����		*/static CResult *Create(void);

	/* ����		*/static void SetVerdict(VERDICT nVerdict) { verdict = nVerdict; }

private:

	// ***** �ϐ� *****
	static VERDICT verdict;	// ����
};

#endif