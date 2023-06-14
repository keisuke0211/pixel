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
class CCamera;			// カメラ
class CLight;			// ライト
class CSound;			// サウンド
class CTexture;			// テクスチャ
class CInputKeyboard;	// キーボード
class CInputMouse;		// マウス
class CInputJoypad;		// ジョイパット
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

	/* 取得 */
	static CRenderer *GetRenderer() { return m_pRenderer; }					// レンダラー
	static CCamera *GetCamera() { return m_pCamera; }						// カメラ
	static CLight *GetLight() { return m_pLight; }							// ライト
	static CSound *GetSound() { return m_pSound; }							// サウンド
	static CTexture* GetTexture(){ return m_pTexture; }						// テクスチャ
	static CInputKeyboard* GetInputKeyboard() { return m_InputKeyboard; }	// キーボード
	static CInputMouse* GetInputMouse() { return m_InputMouse; }			// マウス
	static CInputJoypad* GetInputJoypad() { return m_InputJoypad; }			// ジョイパット
	static CBg* GetBg() { return m_pBg; }									// 背景
	static CPlayer* GetPlayer() { return m_pPlayer; }						// プレイヤー
	static CEnemy* GetEnemy() { return m_pEnemy; }							// エネミー
	static CBullet* GetCBullet() { return m_pBullet; }						// バレット

private:
	static CRenderer *m_pRenderer;			// レンダラー
	static CCamera *m_pCamera;				// カメラ
	static CLight *m_pLight;				// ライト
	static CSound *m_pSound;				// サウンド
	static CTexture *m_pTexture;			// テクスチャ
	static CInputKeyboard *m_InputKeyboard;	// キーボード
	static CInputMouse* m_InputMouse;		// マウス
	static CInputJoypad* m_InputJoypad;		// ジョイパット
	static CBg *m_pBg;						// 背景
	static CPlayer *m_pPlayer;				// プレイヤー
	static CEnemy *m_pEnemy;				// エネミー
	static CBullet *m_pBullet;				// バレット
};
#endif