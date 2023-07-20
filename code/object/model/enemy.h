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

	// ***** �񋓌^ *****

	// ���
	enum STATE
	{
		STATE_NORMAL,	// �ʏ�
		STATE_DAMAGE,	// �_���[�W
		STATE_MAX,
	};

	// ***** �\���� *****

	// �G���
	struct Info
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 posOld;	// �ʒu(�ߋ�)
		D3DXVECTOR3 rot;	// ����
		D3DXVECTOR3 rotOld;	// ����(�ߋ�)
		D3DXVECTOR3 move;	// �ړ���
		D3DCOLOR col;		// ���_�J���[
		int nType;			// ���
		int nMove;			// �ړ����
		int nLife;			// ����
		STATE state;		// ���
		int nCntState;		// ��ԊǗ��J�E���^�[
		int nCntTime;		// �s���J�E���^�[
	};

	// ***** �֐� *****
	CEnemy(int nPriority = PRIO_OBJECT);
	virtual~CEnemy();

	/* ���C�� */

	// ����
	static CEnemy *Create(int nType,int nMove,D3DXVECTOR3 pos);

	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��

	void HitLife(int nDamage);						// Hit����

	/* �擾 */
	Info GetInfo(void) { return m_Info; }					// �G�l�~�[���
	D3DXVECTOR3 GetPos(void) { return m_Info.pos; }			// �ʒu
	D3DXVECTOR3 GetPosOld(void) { return m_Info.posOld; }	// �ʒu(�ߋ�)
	static int GetEnemyAll(void) { return m_nNumAll; }

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
	void SetState(STATE state);	// ��Ԑݒ�
	void StateShift(void);		// ��Ԑ���
	bool Collsion(VECTOR vector, D3DXVECTOR3 pos);	// �����蔻��

	// ***** �ϐ� *****
	Info m_Info;			// ���
	static SetInfo *pSet;	// �z�u

	static int m_nNumAll;		// �G�̑���
};
#endif