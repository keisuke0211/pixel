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

	// ***** �֐� *****
	CResult();
	virtual~CResult();

	// -- ���C�� ------------------------------------------
	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);
private:

	// ***** �ϐ� *****

};

#endif