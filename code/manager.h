//========================================
// 
// �}�l�[�W���[����
// 
//========================================
// *** manager.h ***
//========================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"

//****************************************
// �O���錾
//****************************************
class CRenderer;		// �����_���[
class CCamera;			// �J����
class CLight;			// ���C�g
class CSound;			// �T�E���h
class CTexture;			// �e�N�X�`��
class CInputKeyboard;	// �L�[�{�[�h
class CInputMouse;		// �}�E�X
class CInputJoypad;		// �W���C�p�b�g
class CBg;				// �w�i
class CPlayer;			// �v���C���[
class CBlock;			// �u���b�N
class CEnemy;			// �G
class CBullet;			// �e

//****************************************
// �N���X
//****************************************
class CManager
{
public:

	// ***** �֐� *****
	CManager();
	virtual~CManager();

	/* ������	*/HRESULT Init(HINSTANCE hinstance, HWND hWnd, BOOL bWindow);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);
	/* �G�l�~�[	*/void SetEnemy(void);

	// -- �擾 --------------------------------------
	/* �����_���[	*/static CRenderer *GetRenderer() { return m_pRenderer; }
	/* �J����		*/static CCamera *GetCamera() { return m_pCamera; }
	/* ���C�g		*/static CLight *GetLight() { return m_pLight; }
	/* �T�E���h		*/static CSound *GetSound() { return m_pSound; }
	/* �e�N�X�`��	*/static CTexture* GetTexture(){ return m_pTexture; }
	/* �L�[�{�[�h	*/static CInputKeyboard* GetInputKeyboard() { return m_InputKeyboard; }
	/* �}�E�X		*/static CInputMouse* GetInputMouse() { return m_InputMouse; }
	/* �W���C�p�b�g	*/static CInputJoypad* GetInputJoypad() { return m_InputJoypad; }
	/* �w�i			*/static CBg* GetBg() { return m_pBg; }
	/* �v���C���[	*/static CPlayer* GetPlayer() { return m_pPlayer; }
	/* �u���b�N		*/static CBlock* GetBlock() { return m_pBlock; }
	/* �G�l�~�[		*/static CEnemy* GetEnemy() { return m_pEnemy; }
	/* �o���b�g		*/static CBullet* GetCBullet() { return m_pBullet; }

private:
	/* �����_���[	*/static CRenderer *m_pRenderer;
	/* �J����		*/static CCamera *m_pCamera;
	/* ���C�g		*/static CLight *m_pLight;
	/* �T�E���h		*/static CSound *m_pSound;
	/* �e�N�X�`��	*/static CTexture *m_pTexture;
	/* �L�[�{�[�h	*/static CInputKeyboard *m_InputKeyboard;
	/* �}�E�X		*/static CInputMouse* m_InputMouse;
	/* �W���C�p�b�g	*/static CInputJoypad* m_InputJoypad;
	/* �w�i			*/static CBg *m_pBg;
	/* �v���C���[	*/static CPlayer *m_pPlayer;
	/* �u���b�N		*/static CBlock *m_pBlock;
	/* �G�l�~�[		*/static CEnemy *m_pEnemy;
	/* �o���b�g		*/static CBullet *m_pBullet;
};
#endif