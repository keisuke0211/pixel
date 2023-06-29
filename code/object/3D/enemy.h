//========================================
// 
// �G�l�~�[����
// 
//========================================
// *** enemy.h ***
//========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "../../main.h"
#include "../objectX.h"

//****************************************
// �N���X
//****************************************
class CEnemy : public CObjectX
{
public:

	// ***** ��` *****
	static const int MAX_ENEMY = 30;	// �G�̍ő吔

	// ***** �֐� *****
	CEnemy(int nPriority = PRIO_OBJX);
	virtual~CEnemy();

	// ***** �\���� *****

	// �G���
	typedef struct
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 posOld;	// �ʒu(�ߋ�)
		D3DXVECTOR3 rot;	// ����
		D3DXVECTOR3 move;	// �ړ���
		D3DCOLOR col;		// ���_�J���[
		int nType;			// ���
		int nLife;			// ����
	} Info;

	/* ���C�� */

	// ����
	static CEnemy *Create(void);

	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��

	static void SetEnemy(int nStage, int nUnit);	// �z�u
	void HitLife(int nDamage);

	/* �擾 */
	Info GetInfo() { return m_Info; }					// �G�l�~�[���
	D3DXVECTOR3 GetPos() { return m_Info.pos; }			// �ʒu
	D3DXVECTOR3 GetPosOld() { return m_Info.posOld; }	// �ʒu(�ߋ�)

private:

	// ***** �񋓌^ *****

	// �ݒ荀��
	typedef enum
	{
		SET_TYPE,	// ���
		SET_POS,	// �ʒu
		SET_POS_Y,	// �ʒu Y
		SET_POS_Z,	// �ʒu Z
		SET_SPEED,	// �ړ���
		SET_STAGE,	// �X�e�[�WID
		SET_UNIT,	// ����ID
		SET_MAX,
	}SET;

	// ***** �\���� *****

	// �z�u���
	typedef struct
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 rot;	// ����
		int nType;			// ���
		int nSpeed;			// �ړ���
		int nStage;			// �X�e�[�WID
		int nUnit;			// ����ID
		bool bSet;			// �z�u�������ǂ���

	} SetInfo;

	// ***** �֐� *****
	static void Load(void);	// �ǂݍ���

	// ***** �ϐ� *****
	Info m_Info;			// ���
	static SetInfo *pSet;	// �z�u

	static int nNumSet;		// �G�̔z�u��
};
#endif