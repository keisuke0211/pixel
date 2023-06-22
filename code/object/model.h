//========================================
// 
// ���f������
// 
//========================================
// *** model.h ***
//========================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "../main.h"
#include "../physics.h"
#include "object.h"

//****************************************
// �N���X
//****************************************
class CModel
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


	typedef struct
	{
		LPD3DXMESH		pMesh;				// ���b�V�����ւ̃|�C���^
		LPD3DXBUFFER	pBuffer;			// �}�e���A�����ւ̃|�C���^
		DWORD			nNumMat;			// �}�e���A�����̐�
		D3DXVECTOR3		size;				// ���f���̑傫��
		int				*pIdxTex;			// �e�N�X�`���ԍ�
		char			aFileName[0xff];	// X�t�@�C���̃p�X

		float fWidth;
		float fHeight;
		float fDepth;
	} MODEL_MATERIAL;

	// ***** �ÓI�֐� *****
	static CModel *Create(void);									// ����
	static void InitModel(void);									// ������
	static void UninitModel(void);									// �I��
	static void LoadModel(const char *pFileName);					// �ǂݍ���
	static void CalcSize(int nCntModel);							// ���_���W�̍ŏ��l�E�ő�l�̎Z�o
	static MODEL_MATERIAL *GetMaterial() { return m_material; }		// �}�e���A�����̎擾
	static int GetMaxModel(void) { return m_nMaxModel; }			// ���f���� 

	// ***** �֐� *****
	CModel();
	~CModel();

	/* ���C�� */
	HRESULT Init(void);								// ������
	void Uninit(void);								// �I��
	void Update(void);								// �X�V
	void Draw(bool Color);							// �`��
	void Draw(D3DXMATRIX mtxParent, bool Color);	// �`��(�I�[�o�[���[�h)

	/* �ݒ� */
	virtual void SetPos(const D3DXVECTOR3 pos) { m_pos = m_posOld = pos; }	// �ʒu
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }						// ����
	void SetColor(const D3DXCOLOR color) { m_color = color; }				// �F
	void SetScale(const D3DXVECTOR3 &scale) { m_scale = scale; }			// �X�P�[��
	void SetMtxWorld(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }		// ���[���h�}�g���b�N�X
	void SetParent(CModel *pParent) { m_pParent = pParent; }				// �e���f��
	void SetModelID(const int nModelID) { m_nModelID = nModelID; }			// ���f��ID

	/* �擾 */
	D3DXVECTOR3 GetPos(void) { return m_pos; }								// �ʒu
	D3DXVECTOR3 GetRot(void) { return m_rot; }								// ����
	D3DXCOLOR GetColor(void) { return m_color; }							// �F
	D3DXVECTOR3 GetSize(const int nModelID);								// �傫��
	D3DXVECTOR3 GetScale(void) { return m_scale; }							// �T�C�Y
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }						// ���[���h�}�g���b�N�X
	CModel *GetParent(void) { return m_pParent; }							// �e���f��
	int GetModelID(void) { return m_nModelID; }								// ���f��ID

	float GetWidth(const int nModelID);	// ��
	float GetHeight(const int nModelID);// ����
	float GetDepth(const int nModelID);	// ���s��

private:

	// ***** �ÓI�ϐ� *****
	static MODEL_MATERIAL	*m_material;		// �}�e���A�����
	static int				m_nMaxModel;		// ���f����

	// ***** �ϐ� *****
	LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���ւ̃|�C���^
	D3DXMATRIX  m_mtxWorld;					//���[���h�}�g���b�N�X


	CModel	*m_pParent;		// �e���f���̏��
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_posOld;	// �ʒu(�ߋ�)
	D3DXVECTOR3 m_rot;		// ����
	D3DXVECTOR3	m_size;		// �傫��
	D3DXVECTOR3	m_scale;	// �X�P�[��
	D3DXCOLOR m_color;		// �F
	int	m_nModelID;			// ���f��ID

	float m_Width;
	float m_Height;
	float m_Depth;
};
#endif