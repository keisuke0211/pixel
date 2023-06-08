//========================================
//
// パーティクル【 2D 】
//
//========================================
// *** particle2D.h ***
//========================================
#ifndef _PARTICLE2D_H_
#define _PARTICLE2D_H_

#include "../../main.h"
#include "../object.h"

//****************************************
// クラス
//****************************************
class CParticle2D : public CObject
{
public:

	CParticle2D(int nPriority = TYPE_PARTICLE);
	~CParticle2D();

	// *****  関数 *****

	/* メイン */
	HRESULT Init(void);		// 初期化
	void Uninit(void);		// 終了
	void Update(void);		// 更新
	void Draw(void);		// 描画

	// 生成
	static CParticle2D *Create(void);
	void SetEffect(void);

	/* 設定 */
	void SetMove(float fMove) { m_fMove = fMove; }				// 移動量
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }				// 位置
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }				// 向き
	void SetLife(int nLife) { m_nLife = m_nLifeMax = nLife; }	// 寿命
	void SetParColor(D3DXCOLOR col) { m_col = col; }			// 色

private:
	// ***** 変数 *****
	float m_fMove;		// 移動力
	int m_nLife;		// 寿命
	int m_nLifeMax;		// 寿命最大値
	D3DXCOLOR m_col;	// 色
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 向き
};
#endif 