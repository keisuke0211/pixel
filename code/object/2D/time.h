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
// �}�N����`
//****************************************
#define	MAX_TIME	(2)

//****************************************
// �O���錾
//****************************************
class CText2D;

//****************************************
// �N���X
//****************************************
class CTime : public CText2D
{
public:

	CTime(int nPriority = PRIO_TEXT);
	~CTime();

	// *****  �֐� *****

	/* ���C�� */
	HRESULT Init(void);		// ������
	void Uninit(void);		// �I��
	void Update(void);		// �X�V
	void Draw(void);		// �`��
	static void SetTime(int nTime = 0);	// �ݒ�

	// ����
	static CTime *Create(void);

private:
	// ***** �ϐ� *****
	static int m_nTime;
};
#endif 