//========================================
// 
// ���f������
// 
//========================================
// *** model.h ***
//========================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "../../main.h"
#include "../../physics.h"
#include "../object.h"

//****************************************
// �N���X
//****************************************
class CModel
{
public:

	// ***** ��` *****
	const DWORD  FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);		// ���_�t�H�[�}�b�g�y3D�z

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

	/* ����			*/static CModel *Create(void);
	/* ������		*/static void InitModel(void);
	/* �I��			*/static void UninitModel(void);
	/* �ǂݍ���		*/static void LoadModel(const char *pFileName);
	/* �T�C�Y�̎Z�o */static void CalcSize(int nCntModel);

	/* �擾 */
	/* �}�e���A�����	*/static MODEL_MATERIAL *GetMaterial() { return m_material; }
	/* ���f����			*/static int GetMaxModel(void) { return m_nMaxModel; }

	// ***** �֐� *****
	CModel();
	~CModel();

	// -- ���C�� ------------------------------------------

	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(bool Color);
	/* �`��		*/void Draw(D3DXMATRIX mtxParent, bool Color);

	// -- �ݒ� ------------------------------------------

	/* �ʒu					*/virtual void SetPos(const D3DXVECTOR3 pos) { m_pos = m_posOld = pos; }
	/* ����					*/void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }
	/* �F					*/void SetColor(const D3DXCOLOR color) { m_color = color; }
	/* �X�P�[��				*/void SetScale(const D3DXVECTOR3 &scale) { m_scale = scale; }
	/* ���[���h�}�g���b�N�X	*/void SetMtxWorld(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }
	/* �e���f��				*/void SetParent(CModel *pParent) { m_pParent = pParent; }
	/* ���f��ID				*/void SetModelID(const int nModelID) { m_nModelID = nModelID; }

	// -- ���� ------------------------------------------

	/* �ʒu					*/D3DXVECTOR3 GetPos(void) { return m_pos; }
	/* ����					*/D3DXVECTOR3 GetRot(void) { return m_rot; }
	/* �F					*/D3DXCOLOR GetColor(void) { return m_color; }
	/* �T�C�Y				*/D3DXVECTOR3 GetSize(const int nModelID);
	/* �X�P�[��				*/D3DXVECTOR3 GetScale(void) { return m_scale; }
	/* ���[���h�}�g���b�N�X	*/D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }
	/* �e���f��				*/CModel *GetParent(void) { return m_pParent; }
	/* ���f��ID				*/int GetModelID(void) { return m_nModelID; }
	/* ��					*/static float GetWidth(const int nModelID);
	/* ����					*/static float GetHeight(const int nModelID);
	/* ���s��				*/static float GetDepth(const int nModelID);

private:

	// ***** �ÓI�ϐ� *****
	/* �}�e���A�����	*/static MODEL_MATERIAL	*m_material;
	/* ���f����			*/static int m_nMaxModel;

	// ***** �ϐ� *****
	/* �e�N�X�`���|�C���^	*/LPDIRECT3DTEXTURE9 m_pTexture;
	/* ���[���h�}�g���b�N�X	*/D3DXMATRIX  m_mtxWorld;


	/* �e���f���̏��		*/CModel	*m_pParent;
	/* �ʒu					*/D3DXVECTOR3 m_pos;
	/* �ʒu(�ߋ�)			*/D3DXVECTOR3 m_posOld;
	/* ����					*/D3DXVECTOR3 m_rot;
	/* �T�C�Y				*/D3DXVECTOR3	m_size;
	/* �X�P�[��				*/D3DXVECTOR3	m_scale;
	/* �F					*/D3DXCOLOR m_color;
	/* ���f��ID				*/int	m_nModelID;
	/* ��					*/static float m_Width;
	/* ����					*/static float m_Height;
	/* ���s��				*/static float m_Depth;
};
#endif