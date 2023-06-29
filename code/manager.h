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
class CBlock;			// ブロック
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

	/* 初期化	*/HRESULT Init(HINSTANCE hinstance, HWND hWnd, BOOL bWindow);
	/* 終了		*/void Uninit(void);
	/* 更新		*/void Update(void);
	/* 描画		*/void Draw(void);
	/* エネミー	*/void SetEnemy(void);

	// -- 取得 --------------------------------------
	/* レンダラー	*/static CRenderer *GetRenderer() { return m_pRenderer; }
	/* カメラ		*/static CCamera *GetCamera() { return m_pCamera; }
	/* ライト		*/static CLight *GetLight() { return m_pLight; }
	/* サウンド		*/static CSound *GetSound() { return m_pSound; }
	/* テクスチャ	*/static CTexture* GetTexture(){ return m_pTexture; }
	/* キーボード	*/static CInputKeyboard* GetInputKeyboard() { return m_InputKeyboard; }
	/* マウス		*/static CInputMouse* GetInputMouse() { return m_InputMouse; }
	/* ジョイパット	*/static CInputJoypad* GetInputJoypad() { return m_InputJoypad; }
	/* 背景			*/static CBg* GetBg() { return m_pBg; }
	/* プレイヤー	*/static CPlayer* GetPlayer() { return m_pPlayer; }
	/* ブロック		*/static CBlock* GetBlock() { return m_pBlock; }
	/* エネミー		*/static CEnemy* GetEnemy() { return m_pEnemy; }
	/* バレット		*/static CBullet* GetCBullet() { return m_pBullet; }

private:
	/* レンダラー	*/static CRenderer *m_pRenderer;
	/* カメラ		*/static CCamera *m_pCamera;
	/* ライト		*/static CLight *m_pLight;
	/* サウンド		*/static CSound *m_pSound;
	/* テクスチャ	*/static CTexture *m_pTexture;
	/* キーボード	*/static CInputKeyboard *m_InputKeyboard;
	/* マウス		*/static CInputMouse* m_InputMouse;
	/* ジョイパット	*/static CInputJoypad* m_InputJoypad;
	/* 背景			*/static CBg *m_pBg;
	/* プレイヤー	*/static CPlayer *m_pPlayer;
	/* ブロック		*/static CBlock *m_pBlock;
	/* エネミー		*/static CEnemy *m_pEnemy;
	/* バレット		*/static CBullet *m_pBullet;
};
#endif