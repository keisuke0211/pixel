//========================================
// 
// �f�o�b�N����
// 
//========================================
// *** debug.h ***
//========================================
#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "main.h"

class CDebug
{
public:

	// ***** �֐� *****
	/* ������	*/static void Init(void);
	/* �I��		*/static void Uninit(void);
	/* �X�V		*/static void Update(void);
	/* �`��		*/static void Draw(void);
	/* �f�o�b�N�\�� */static void DebugPrint(const char *text, ...);
	/*  */static void ReleasePrint(const char *text, ...);
};

#endif