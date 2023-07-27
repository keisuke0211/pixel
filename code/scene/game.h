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
// �O���錾
//****************************************
class CTime;			// �^�C��
class CScore;			// �X�R�A

						//****************************************
						// �N���X
						//****************************************
class CGame : public CScene
{
	static const int MAX_TIME = 99;	// ��������
public:

	// ***** �֐� *****
	CGame();
	virtual~CGame();

	// -- ���C�� ------------------------------------------
	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);
	/* ����		*/static CGame *Create(void);
	/* �G�l�~�[	*/void SetEnemy(void);

	// -- �ǂݍ��� ----------
	/* �G�l�~�[	*/static void LoodEnemy(void);
	/* �u���b�N */static void LoodBlock(void);

	// -- �擾 ------------------------
	/* �^�C��		*/static CTime *GetTime() { return m_pTime; }
	/* �X�R�A		*/static CScore *GetScore() { return m_pScore; };
private:

	// ***** �ϐ� *****
	/* �^�C��		*/static CTime *m_pTime;
	/* �X�R�A		*/static CScore *m_pScore;

};

#endif