//========================================
// 
// �e�N�X�`���Ǘ�
// 
//========================================
// *** texture.h ***
//========================================
#ifndef _TEXTURE_H_	//���̃}�N����`������ĂȂ�������
#define _TEXTURE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"

//==================================================
// ��`
//==================================================
class CTexture
{
public:

	// ***** ��` *****
	static const int MAX_TEXTURE = 64;	// �e�N�X�`���̍ő吔
	static const char* FILE_PATH;		// �ǂݍ��ރt�@�C���p�X

	// ***** �֐� *****
	CTexture();		// �f�t�H���g�R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

	HRESULT Load(void);			// �ǂݍ���
	void Unload(void);			// �j��

	/* �ݒ� */
	int Regist(const char* pFilename);	// �e�N�X�`���ԍ�

	/* �擾 */
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);	// �e�N�X�`���|�C���^

private:
	// ***** �ϐ� *****
	LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE];	// �e�N�X�`���|�C���^
	static int m_NumAll;							// �e�N�X�`������

	static char m_FileName[MAX_TEXTURE][TXT_MAX];	// �t�@�C���p�X
};

#endif // !_TEXTURE_H_
