//========================================
// 
// �|�[�Y
// 
//========================================
// *** pause.h ***
//========================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "../main.h"
#include "../manager.h"

//****************************************
// �O���錾
//****************************************
class CWords;

//****************************************
// �N���X
//****************************************
class CPause : public CScene
{
public:

	// ***** �֐� *****
	CPause();
	~CPause();

	// -- ���C�� ------------------------------------------
	/* ������		*/HRESULT Init(void);
	/* �I��			*/void Uninit(void);
	/* �X�V			*/void Update(void);
	/* �`��			*/void Draw(void);
	/* ����			*/static CPause *Create(void);

	// -- �ݒ� --------------------------------------------
	/* �|�[�Y */static void SetPause(bool bPause) { m_bPause = bPause; }

	// -- �擾 --------------------------------------------
	/* �|�[�Y	*/static bool IsPause(void) { return m_bPause; }

private:

	// ***** �ϐ� *****
	static bool m_bPause;
};

#endif