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

	/* ���C�� */
	HRESULT Init(HINSTANCE hinstance, HWND hWnd, BOOL bWindow);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��

	/* �擾 */
	static CRenderer *GetRenderer() { return m_pRenderer; }					// �����_���[
	static CCamera *GetCamera() { return m_pCamera; }						// �J����
	static CLight *GetLight() { return m_pLight; }							// ���C�g
	static CSound *GetSound() { return m_pSound; }							// �T�E���h
	static CTexture* GetTexture(){ return m_pTexture; }						// �e�N�X�`��
	static CInputKeyboard* GetInputKeyboard() { return m_InputKeyboard; }	// �L�[�{�[�h
	static CInputMouse* GetInputMouse() { return m_InputMouse; }			// �}�E�X
	static CInputJoypad* GetInputJoypad() { return m_InputJoypad; }			// �W���C�p�b�g
	static CBg* GetBg() { return m_pBg; }									// �w�i
	static CPlayer* GetPlayer() { return m_pPlayer; }						// �v���C���[
	static CEnemy* GetEnemy() { return m_pEnemy; }							// �G�l�~�[
	static CBullet* GetCBullet() { return m_pBullet; }						// �o���b�g

private:
	static CRenderer *m_pRenderer;			// �����_���[
	static CCamera *m_pCamera;				// �J����
	static CLight *m_pLight;				// ���C�g
	static CSound *m_pSound;				// �T�E���h
	static CTexture *m_pTexture;			// �e�N�X�`��
	static CInputKeyboard *m_InputKeyboard;	// �L�[�{�[�h
	static CInputMouse* m_InputMouse;		// �}�E�X
	static CInputJoypad* m_InputJoypad;		// �W���C�p�b�g
	static CBg *m_pBg;						// �w�i
	static CPlayer *m_pPlayer;				// �v���C���[
	static CEnemy *m_pEnemy;				// �G�l�~�[
	static CBullet *m_pBullet;				// �o���b�g
};
#endif