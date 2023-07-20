//========================================
// 
// 背景(側面)【 3D_MULTI 】処理
// 
//========================================
// *** bg_side.h ***
//========================================
#ifndef _BG_SIDE_H_
#define _BG_SIDE_H_

#include "../../main.h"
#include "../object.h"

//****************************************
// クラス
//****************************************
class CBgSide : public CObject
{
public:
	// ***** 構造体 *****

	// 頂点情報[3D_MULTI]の構造体を定義
	struct VERTEX_3D_MULTI
	{
		D3DXVECTOR3 pos;	// 頂点座標
		D3DXVECTOR3 nor;	// 法線ベクトル
		D3DCOLOR	col;	// 頂点カラー
		D3DXVECTOR2 tex1;	// テクスチャ座標1
		D3DXVECTOR2 texM;	// テクスチャ座標2
		D3DXVECTOR2 texM2;	// テクスチャ座標3
	};

	// ***** 関数 *****
	CBgSide(int nPriority = PRIO_OBJECT);
	~CBgSide();

	/* メイン */
	HRESULT Init(void);				// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	static CBgSide *Create(void);	// 生成

	/* 設定 */
	/* 位置			*/void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }	
	/* 向き			*/void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	/* 色			*/void SetColor(const D3DXCOLOR& color) { m_color = color; }

private:
	// ***** 変数 *****
	LPDIRECT3DTEXTURE9 m_pTextureMeshfield1;		// テクスチャへのポインタ
	LPDIRECT3DTEXTURE9 m_pTextureMeshfield2;		// テクスチャへのポインタ
	LPDIRECT3DTEXTURE9 m_pTextureMeshfield3;		// テクスチャへのポインタ
	D3DXMATRIX mtxWorld;							// ワールドマトリックス

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点情報を格納
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuf;	//インデックス情報を格納

	D3DXVECTOR3 m_pos;					// 位置
	D3DXVECTOR3 m_rot;					// 向き
	D3DXCOLOR m_color;					// 色
	static float m_aTexV[3];			// テクスチャ座標の開始位置(X軸)
};
#endif