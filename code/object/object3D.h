//========================================
// 
// �I�u�W�F�N�g�y 3D �z����
// 
//========================================
// *** object3D.h ***
//========================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "../main.h"
#include "object.h"

//****************************************
// �}�N��
//****************************************
#define INIT_POSITIONVEC4	PositionVec4(0.0f,1.0f,0.0f,1.0f)	// PositionVec4�̏����l

//****************************************
// �\����
//****************************************
struct PositionVec4
{
	float     P0, P1, P2, P3;
	constexpr PositionVec4() : P0(0.0f), P1(0.0f), P2(0.0f), P3(0.0f) { }
	constexpr PositionVec4(float _P0, float _P1, float _P2, float _P3) : P0(_P0), P1(_P1), P2(_P2), P3(_P3) { }
};

//****************************************
// �N���X
//****************************************
class CObject3D : public CObject
{
public:

	// ***** ��` *****
	const DWORD  FVF_VERTEX_3D	= (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);		// ���_�t�H�[�}�b�g�y2D�z

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
	CObject3D();
	~CObject3D();

	/* ���C�� */
	HRESULT Init(void);				// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	static CObject3D *Create(void);	// ����

	/* �ݒ� */
	virtual void SetPos(const D3DXVECTOR3& pos);		// �ʒu
	virtual void SetRot(const float& rotY);				// ����
	virtual void SetSize(const D3DXVECTOR2& size);		// �T�C�Y
	virtual void SetColor(const D3DXCOLOR& color);		// �F
	virtual void SetTex(PositionVec4 tex);				// �e�N�X�`�����W
	void BindTexture(LPDIRECT3DTEXTURE9 m_pTexture);	// �e�N�X�`���w��

private:
	// ***** �ϐ� *****
	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	D3DXMATRIX mtxWorld;				// ���[���h�}�g���b�N�X

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�����i�[

	D3DXVECTOR3 m_pos;	// ���S�ʒu
	D3DXVECTOR2 m_size;	// �傫��
	D3DXCOLOR m_color;	// �F
	int m_nTexture;		// �e�N�X�`���ԍ�
	float m_fRotY;		// ��]
	float m_fLength;	// ����
	float m_fAngle;		// �p�x

};
#endif