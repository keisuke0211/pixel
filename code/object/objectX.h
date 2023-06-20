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
// �O���錾
//****************************************
class CModel;

//****************************************
// �N���X
//****************************************
class CObjectX : public CObject
{
public:

	// ***** ��` *****
	const DWORD  FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);		// ���_�t�H�[�}�b�g�y3D�z

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
	virtual void SetScale(D3DXVECTOR3 scale) { m_scale = scale; };			// �X�P�[��
	virtual void SetColor(D3DXCOLOR color) { m_color = color; }				// �F
	virtual void SetModel(int  nModelID) { m_nModelID = nModelID; }			// ���f��ID


private:
	// ***** �ϐ� *****
	D3DXMATRIX  m_mtxWorld;	//���[���h�}�g���b�N�X

	CModel		*m_pModel;	// ���f��
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_posOld;	// �ʒu(�ߋ�)
	D3DXVECTOR3 m_rot;		// ����
	D3DXVECTOR3	m_scale;	// �X�P�[��
	D3DXCOLOR m_color;		// �F
	int m_nModelID;			// ���f��ID
	char m_aModelPath[TXT_MAX];

};
#endif