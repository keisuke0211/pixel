//========================================
// 
// オブジェクト【 3D 】処理
// 
//========================================
// *** object3D.h ***
//========================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "../main.h"
#include "object.h"

//****************************************
// マクロ
//****************************************
#define INIT_POSITIONVEC4	PositionVec4(0.0f,1.0f,0.0f,1.0f)	// PositionVec4の初期値

//****************************************
// 構造体
//****************************************
struct PositionVec4
{
	float     P0, P1, P2, P3;
	constexpr PositionVec4() : P0(0.0f), P1(0.0f), P2(0.0f), P3(0.0f) { }
	constexpr PositionVec4(float _P0, float _P1, float _P2, float _P3) : P0(_P0), P1(_P1), P2(_P2), P3(_P3) { }
};

//****************************************
// クラス
//****************************************
class CObject3D : public CObject
{
public:

	// ***** 定義 *****
	const DWORD  FVF_VERTEX_3D	= (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);		// 頂点フォーマット【2D】

	// ***** 構造体 *****

	//頂点情報【 3D 】
	typedef struct
	{
		D3DXVECTOR3 pos;	//頂点座標
		D3DXVECTOR3 nor;	//法線ベクトル
		D3DCOLOR col;		//頂点カラー
		D3DXVECTOR2 tex;	//テクスチャ座標
	} VERTEX_3D;

	// ***** 関数 *****
	CObject3D();
	~CObject3D();

	/* メイン */
	HRESULT Init(void);				// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	static CObject3D *Create(void);	// 生成

	/* 設定 */
	virtual void SetPos(const D3DXVECTOR3& pos);		// 位置
	virtual void SetRot(const float& rotY);				// 向き
	virtual void SetSize(const D3DXVECTOR2& size);		// サイズ
	virtual void SetColor(const D3DXCOLOR& color);		// 色
	virtual void SetTex(PositionVec4 tex);				// テクスチャ座標
	void BindTexture(LPDIRECT3DTEXTURE9 m_pTexture);	// テクスチャ指定

private:
	// ***** 変数 *****
	LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャへのポインタ
	D3DXMATRIX mtxWorld;				// ワールドマトリックス

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点情報を格納

	D3DXVECTOR3 m_pos;	// 中心位置
	D3DXVECTOR2 m_size;	// 大きさ
	D3DXCOLOR m_color;	// 色
	int m_nTexture;		// テクスチャ番号
	float m_fRotY;		// 回転
	float m_fLength;	// 長さ
	float m_fAngle;		// 角度

};
#endif