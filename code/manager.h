//========================================
// 
// マネージャー処理
// 
//========================================
// *** manager.h ***
//========================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"

//****************************************
// 前方宣言
//****************************************
class CRenderer;		// レンダラー
class CSound;			// サウンド
class CTexture;			// テクスチャ
class CInputKeyboard;	// キーボード
class CInputMouse;		// マウス
class CInputJoypad;		// ジョイパット
class CNumber;			// 数字
class CBg;				// 背景
class CPlayer;			// プレイヤー
class CEnemy;			// 敵
class CBullet;			// 弾

//****************************************
// クラス
//****************************************
class CManager
{
public:

	// ***** 関数 *****
	CManager();
	virtual~CManager();

	/* メイン */
	HRESULT Init(HINSTANCE hinstance, HWND hWnd, BOOL bWindow);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	void Load(void);	// 読み込み

	/* 取得 */
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