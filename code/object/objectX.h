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
// 前方宣言
//****************************************
class CModel;

//****************************************
// クラス
//****************************************
class CObjectX : public CObject
{
public:

	// ***** 定義 *****
	const DWORD  FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);		// 頂点フォーマット【3D】

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
	virtual void SetScale(D3DXVECTOR3 scale) { m_scale = scale; };			// スケール
	virtual void SetColor(D3DXCOLOR color) { m_color = color; }				// 色
	virtual void SetModel(int  nModelID) { m_nModelID = nModelID; }			// モデルID


private:
	// ***** 変数 *****
	D3DXMATRIX  m_mtxWorld;	//ワールドマトリックス

	CModel		*m_pModel;	// モデル
	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR3 m_posOld;	// 位置(過去)
	D3DXVECTOR3 m_rot;		// 向き
	D3DXVECTOR3	m_scale;	// スケール
	D3DXCOLOR m_color;		// 色
	int m_nModelID;			// モデルID
	char m_aModelPath[TXT_MAX];

};
#endif