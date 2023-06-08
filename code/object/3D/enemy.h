//========================================
// 
// エネミー処理
// 
//========================================
// *** enemy.h ***
//========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "../../main.h"
#include "../object2D.h"

//****************************************
// クラス
//****************************************
class CEnemy : public CObject2D
{
public:

	// ***** 定義 *****
	static const int MAX_TEXTURE = 50;	// テクスチャの最大数

	static const int MAX_ENEMY = 30;	// 敵の最大数

	// ***** 関数 *****
	CEnemy(int nPriority = TYPE_ENEMY);
	virtual~CEnemy();

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
	} Info;

	/* メイン */
	static HRESULT Load(char *pPath);			// テクスチャの生成 
	static void Unload(void);					// テクスチャの破棄

	// 生成
	static CEnemy *Create(D3DXVECTOR3 pos);

	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画

	void HitLife(int nDamage);

	/* 取得 */
	Info GetInfo() { return m_Info; }				// プレイヤー情報
	D3DXVECTOR3 GetPos() { return m_Info.pos; }		// 位置

private:

	// ***** 変数 *****
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];		// 共有テクスチャ
	static int m_nTexture;									// テクスチャの総数
	Info m_Info;	// 情報
};
#endif