//========================================
// 
// �X�e�[�W�I��
// 
//========================================
// *** stage_menu.h ***
//========================================
#ifndef _STAGE_MANU_H_	//���̃}�N����`������ĂȂ�������
#define _STAGE_MANU_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "../../main.h"
#include "../object2D.h"
#include "../../scene/game.h"

//****************************************
// �O���錾
//****************************************
class CText;

//****************************************
//�@�N���X
//****************************************
class CStage : public CObject2D
{
public:

	// �ꏊ
	enum PLACE
	{
		PLACE_LEFT_EDGE = 0,	// ���[
		PLACE_LEFT,				// ��
		PLACE_CENTER,			// ����
		PLACE_RIGHT,			// �E
		PLACE_RIGHT_EDGE,		// �E�[
		PLACE_VACANT,			// ��
		PLACE_MAX
	};

	// ***** �\���� *****

	// ���ʏ��
	struct Info
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 TargetPos;	// �ڕW�ʒu
		D3DXCOLOR col;			// �F
		int nType;				// ���
		int nPlace;				// �ꏊ
		D3DXVECTOR2 size;		// �傫��
		D3DXVECTOR2 TargetSize;	// �ڕW�̑傫��
		bool bMove;				// �ړ��t���O
	};
	
	// ***** �֐� *****
	CStage(int nPriority = PRIO_OBJECT);
	~CStage();

	// -- ���C�� ------------------------------------------
	/* ������		*/HRESULT Init(void);
	/* �I��			*/void Uninit(void);
	/* �X�V			*/void Update(void);
	/* �`��			*/void Draw(void);
	/* ����			*/static CStage *Create(int nType, int nPlace);

	// -- �ݒ� ------------------------------------------
	/* �ʒu�E�摜 */void SetStageInfo(int nType,int nPlace);


	// -- �擾 ------------------------------------------
	/* ��� */int GetStageType(void) { return m_Info.nType; }
	/* �ړ�	*/bool IsMove(void) { return m_Info.bMove; }

private:
	// ***** �ϐ� *****
	Info m_Info;		// ���

	// �e�ꏊ�̈ʒu
	D3DXVECTOR3 m_Place[PLACE_MAX] = {
		D3DXVECTOR3(-200.0f,360.0f,0.0f),
		D3DXVECTOR3(220.0f,360.0f,0.0f),
		D3DXVECTOR3(640.0f,360.0f,0.0f),
		D3DXVECTOR3(1060.0f,360.0f,0.0f),
		D3DXVECTOR3(1480.0f,360.0f,0.0f),
		D3DXVECTOR3(1900.0f,360.0f,0.0f),
	};

	// ***** �ÓI�ϐ� *****
	static LPDIRECT3DTEXTURE9 m_pTexture[CGame::Stage_MAX];	// ���L�e�N�X�`��

	static int m_nSelectStage;	// ���ݑI�����Ă���X�e�[�W
};

#endif // !_TEXTURE_H_

