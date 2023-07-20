//========================================
// 
// �w�i(����)�y 3D_MULTI �z����
// 
//========================================
// *** bg_side.h ***
//========================================
#ifndef _BG_SIDE_H_
#define _BG_SIDE_H_

#include "../../main.h"
#include "../object.h"

//****************************************
// �N���X
//****************************************
class CBgSide : public CObject
{
public:
	// ***** �\���� *****

	// ���_���[3D_MULTI]�̍\���̂��`
	struct VERTEX_3D_MULTI
	{
		D3DXVECTOR3 pos;	// ���_���W
		D3DXVECTOR3 nor;	// �@���x�N�g��
		D3DCOLOR	col;	// ���_�J���[
		D3DXVECTOR2 tex1;	// �e�N�X�`�����W1
		D3DXVECTOR2 texM;	// �e�N�X�`�����W2
		D3DXVECTOR2 texM2;	// �e�N�X�`�����W3
	};

	// ***** �֐� *****
	CBgSide(int nPriority = PRIO_OBJECT);
	~CBgSide();

	/* ���C�� */
	HRESULT Init(void);				// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	static CBgSide *Create(void);	// ����

	/* �ݒ� */
	/* �ʒu			*/void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }	
	/* ����			*/void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	/* �F			*/void SetColor(const D3DXCOLOR& color) { m_color = color; }

private:
	// ***** �ϐ� *****
	LPDIRECT3DTEXTURE9 m_pTextureMeshfield1;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTextureMeshfield2;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTextureMeshfield3;		// �e�N�X�`���ւ̃|�C���^
	D3DXMATRIX mtxWorld;							// ���[���h�}�g���b�N�X

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�����i�[
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuf;	//�C���f�b�N�X�����i�[

	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// ����
	D3DXCOLOR m_color;					// �F
	static float m_aTexV[3];			// �e�N�X�`�����W�̊J�n�ʒu(X��)
};
#endif