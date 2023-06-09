//========================================
// 
// プレイヤー処理
// 
//========================================
// *** player.h ***
//========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "../../main.h"
#include "../object2D.h"

//****************************************
// クラス
//****************************************
class CPlayer : public CObject2D
{
public:

	// ***** 定義 *****
	static const int MAX_TEXTURE = 50;	// テクスチャの最大数

	static const int PLAYER_MAX = 1;	// プレイヤーの最大数
	static const float PLAYER_SPEED;	// プレイヤーの移動量

	// ***** 構造体 *****

	// プレイヤー情報
	typedef struct
	{
		D3DXVECTOR3 pos;			// 位置
		D3DXVECTOR3 rot;			// 向き
		D3DXVECTOR3 move;			// 移動量
		float fWidth;				// 幅
		float fHeight;				// 高さ
		float fJump;				// ジャンプ力
		bool bJump;					// ジャンプフラグ
	} Info;

	// ***** 関数 *****
	CPlayer(int nPriority = TYPE_PLAYER);
	~CPlayer();

	/* メイン */
	static HRESULT Load(char *pPath);			// テクスチャの生成 
	static void Unload(void);					// テクスチャの破棄

	// 生成
	static CPlayer *Create(void);

	HRESULT Init(void);				// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画

	/* 取得 */
	Info GetInfo() { return m_Info; }	// プレイヤー情報

private:
	// ***** 関数 *****
	void AddMove(float fRoty);				// 移動量の更新
	void Physics(void);						// 移動・物理処理
	D3DXVECTOR3 Collision(D3DXVECTOR3 pos);	// ブロックの当たり判定

	// ***** 変数 *****
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];		// 共有テクスチャ
	static int m_nTexture;									// テクスチャの数

	Info m_Info;	// プレイヤー情報
	bool bShot;
};
#endif