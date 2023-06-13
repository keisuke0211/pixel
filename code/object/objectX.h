//========================================
// 
// オブジェクト【 Xファイル 】処理
// 
//========================================
// *** objectX.h ***
//========================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "../main.h"
#include "object.h"

//****************************************
// クラス
//****************************************
class CObjectX : public CObject
{
public:

	// ***** 定義 *****
	const DWORD  FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);		// 頂点フォーマット【2D】

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
	CObjectX(int nPriority = 0);
	~CObjectX();

	/* メイン */
	HRESULT Init(void);				// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	static CObjectX *Create(void);	// 生成

	/* 設定 */
	virtual void SetPos(D3DXVECTOR3 pos) { m_pos = m_posOld = pos; }		// 位置
	virtual void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }					// 向き
	virtual void SetSize(float fWidth = 1, float fHeight = 1,float m_fDepth = 1) { m_fWidth = fWidth, m_fHeight = fHeight; };		// サイズ
	virtual void SetColor(D3DXCOLOR color) { m_color = color; }				// 色

private:
	// ***** 変数 *****
	LPD3DXMESH m_pMesh = NULL;				//メッシュ（頂点情報）へのポインタ
	LPD3DXBUFFER m_pBuffMat = NULL;;		//マテリアルへのポインタ
	LPDIRECT3DTEXTURE9 *m_pTexture;			//テクスチャへのポインタ
	DWORD m_dwNumMat = 0;					//マテリアルの数
	D3DXMATRIX  m_mtxWorld;					//ワールドマトリックス

	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR3 m_posOld;	// 位置(過去)
	D3DXVECTOR3 m_rot;		// 向き
	D3DXCOLOR m_color;		// 色
	float m_fHeight;		// 高さ
	float m_fWidth;			// 幅
	float m_fDepth;			// 奥行き
	char m_aModelPath[TXT_MAX];

};
#endif