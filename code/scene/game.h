//========================================
// 
// �Q�[��
// 
//========================================
// *** game.h ***
//========================================
#ifndef _GAME_H_
#define _GAME_H_

#include "../main.h"
#include "../manager.h"

//****************************************
// �N���X
//****************************************
class CGame : public CScene
{
public:

	// ***** �֐� *****
	CGame();
	virtual~CGame();

	// -- ���C�� ------------------------------------------
	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);
	/* �G�l�~�[	*/void SetEnemy(void);

	// -- �ǂݍ��� ----------
	/* �G�l�~�[	*/static void LoodEnemy(void);
	/* �u���b�N */static void LoodBlock(void);

private:

	// ***** �ϐ� *****

};

#endif