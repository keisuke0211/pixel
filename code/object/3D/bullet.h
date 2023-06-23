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
#include "../objectX.h"

//****************************************
// クラス
//****************************************
class CBullet : public CObjectX
{
public:

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

	// ***** 関数 *****
	CBullet(int nPriority = PRIO_OBJX);
	~CBullet();

	/* メイン */

	// 生成
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	HRESULT Init(void);				// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画

	/* 取得 */
	Info GetInfo() { return m_Info; }				// プレイヤー情報

private:

	// ***** 関数 *****
	bool Collsion(D3DXVECTOR3 pos);					// 当たり判定

	// ***** 変数 *****
	Info m_Info;	// 情報


};
#endif