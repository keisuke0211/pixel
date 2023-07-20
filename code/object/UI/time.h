//========================================
//
// ����
//
//========================================
// *** time.h ***
//========================================
#ifndef _TIME_H_
#define _TIME_H_

#include "../object.h"
#include "text2D.h"

//****************************************
// �N���X
//****************************************
class CTime : public CText2D
{
public:

	CTime(int nPriority = PRIO_UI);
	~CTime();

	// *****  �֐� *****

	/* ���C�� */
	HRESULT Init(void);				// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetTime(int nTime = 0);	// �ݒ�

	// ����
	static CTime *Create(void);

private:
	// ***** �ϐ� *****
	int m_nTime;		// �^�C��
	int m_nCounter;		// �J�E���^�[
};
#endif 