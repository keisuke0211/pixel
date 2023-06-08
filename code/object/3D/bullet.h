//========================================
// 
// 弾処理
// 
//========================================
// *** bullet.h ***
//========================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "../../main.h"
#include "../object2D.h"

//****************************************
// クラス
//****************************************
class CBullet : public CObject2D
{
public:

	// ***** 定義 *****
	static const int MAX_TEXTURE = 50;	// テクスチャの最大数

	// ***** 構造体 *****

	// 弾情報
	typedef struct
	{
		D3DXVECTOR3 pos;	// 位置
		D3DXVECTOR3 rot;	// 向き
		D3DXVECTOR3 move;	// 移動量
		int nType;			// 種類
		int nLife;			// 寿命
		float fWidth;		// 幅
		float fHeight;		// 高さ
		bool bShot;			// 位置切り替え
	} Info;

	// ***** 関数 *****
	CBullet(int nPriority = TYPE_BULLET);
	~CBullet();

	/* メイン */
	static HRESULT Load(char *pPath);			// テクスチャの生成 
	static void Unload(void);					// テクスチャの破棄

	// 生成
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,bool bShot);

	HRESULT Init(void);				// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画

	/* 取得 */
	Info GetInfo() { return m_Info; }				// プレイヤー情報

private:

	// ***** 関数 *****
	bool CollsionEnemy(D3DXVECTOR3 pos);					// 敵との当たり判定

	// ***** 変数 *****
	Info m_Info;	// 情報

	// ***** 静的変数 *****
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	// 共有テクスチャ
	static int m_nTexture;								// テクスチャの数

};
#endif