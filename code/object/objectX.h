//========================================
// 
// �I�u�W�F�N�g�y X�t�@�C�� �z����
// 
//========================================
// *** objectX.h ***
//========================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "../main.h"
#include "object.h"

//****************************************
// �N���X
//****************************************
class CObjectX : public CObject
{
public:

	// ***** ��` *****
	const DWORD  FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);		// ���_�t�H�[�}�b�g�y2D�z

	// ***** �\���� *****

	//���_���y 3D �z
	typedef struct
	{
		D3DXVECTOR3 pos;	//���_���W
		D3DXVECTOR3 nor;	//�@���x�N�g��
		D3DCOLOR col;		//���_�J���[
		D3DXVECTOR2 tex;	//�e�N�X�`�����W
	} VERTEX_3D;

	// ***** �֐� *****
	CObjectX(int nPriority = 0);
	~CObjectX();

	/* ���C�� */
	HRESULT Init(void);				// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	static CObjectX *Create(void);	// ����

	/* �ݒ� */
	virtual void SetPos(D3DXVECTOR3 pos) { m_pos = m_posOld = pos; }		// �ʒu
	virtual void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }					// ����
	virtual void SetSize(float fWidth = 1, float fHeight = 1,float m_fDepth = 1) { m_fWidth = fWidth, m_fHeight = fHeight; };		// �T�C�Y
	virtual void SetColor(D3DXCOLOR color) { m_color = color; }				// �F

private:
	// ***** �ϐ� *****
	LPD3DXMESH m_pMesh = NULL;				//���b�V���i���_���j�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat = NULL;;		//�}�e���A���ւ̃|�C���^
	LPDIRECT3DTEXTURE9 *m_pTexture;			//�e�N�X�`���ւ̃|�C���^
	DWORD m_dwNumMat = 0;					//�}�e���A���̐�
	D3DXMATRIX  m_mtxWorld;					//���[���h�}�g���b�N�X

	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_posOld;	// �ʒu(�ߋ�)
	D3DXVECTOR3 m_rot;		// ����
	D3DXCOLOR m_color;		// �F
	float m_fHeight;		// ����
	float m_fWidth;			// ��
	float m_fDepth;			// ���s��
	char m_aModelPath[TXT_MAX];

};
#endif