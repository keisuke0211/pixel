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
class CSound;			// �T�E���h
class CTexture;			// �e�N�X�`��
class CInputKeyboard;	// �L�[�{�[�h
class CInputMouse;		// �}�E�X
class CInputJoypad;		// �W���C�p�b�g
class CNumber;			// ����
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
	void Load(void);	// �ǂݍ���

	/* �擾 */
	static CRenderer *GetRenderer() { return m_pRenderer; }
	static CSound *GetSound() { return m_pSound; }
	static CTexture* GetTexture(){ return m_pTexture; }
	static CInputKeyboard* GetInputKeyboard() { return m_InputKeyboard; }
	static CInputMouse* GetInputMouse() { return m_InputMouse; }
	static CInputJoypad* GetInputJoypad() { return m_InputJoypad; }
	static CNumber* GetNumber() { return m_Number; }
	static CBg* GetBg() { return m_pBg; }
	static CPlayer* GetPlayer() { return m_pPlayer; }
	static CEnemy* GetEnemy() { return m_pEnemy; }
	static CBullet* GetCBullet() { return m_pBullet; }

private:
	static CRenderer *m_pRenderer;
	static CSound *m_pSound;
	static CTexture *m_pTexture;
	static CInputKeyboard *m_InputKeyboard;
	static CInputMouse* m_InputMouse;
	static CInputJoypad* m_InputJoypad;
	static CNumber* m_Number;
	static CBg *m_pBg;
	static CPlayer *m_pPlayer;
	static CEnemy *m_pEnemy;
	static CBullet *m_pBullet;
};
#endif