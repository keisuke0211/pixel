//========================================
// 
// モデル処理
// 
//========================================
// *** model.h ***
//========================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "../main.h"
#include "../physics.h"
#include "object.h"

//****************************************
// クラス
//****************************************
class CModel
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


	typedef struct
	{
		LPD3DXMESH		pMesh;				// メッシュ情報へのポインタ
		LPD3DXBUFFER	pBuffer;			// マテリアル情報へのポインタ
		DWORD			nNumMat;			// マテリアル情報の数
		D3DXVECTOR3		size;				// モデルの大きさ
		int				*pIdxTex;			// テクスチャ番号
		char			aFileName[0xff];	// Xファイルのパス
	} MODEL_MATERIAL;

	// ***** 静的関数 *****
	static CModel *Create(void);									// 生成
	static void InitModel(void);									// 初期化
	static void UninitModel(void);									// 終了
	static void LoadModel(const char *pFileName);					// 読み込み
	static void CalcSize(int nCntModel);							// 頂点座標の最小値・最大値の算出
	static MODEL_MATERIAL *GetMaterial() { return m_material; }		// マテリアル情報の取得
	static int GetMaxModel() { return m_nMaxModel; }				// モデル数 

	// ***** 関数 *****
	CModel(int nPriority = 0);
	~CModel();

	/* メイン */
	HRESULT Init(void);								// 初期化
	void Uninit(void);								// 終了
	void Update(void);								// 更新
	void Draw(bool Color);							// 描画
	void Draw(D3DXMATRIX mtxParent, bool Color);	// 描画(オーバーロード)

	/* 設定 */
	virtual void SetPos(const D3DXVECTOR3 pos) { m_pos = m_posOld = pos; }	// 位置
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }						// 向き
	void SetColor(const D3DXCOLOR color) { m_color = color; }				// 色
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }				// 大きさ
	void SetMtxWorld(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }		// ワールドマトリックス
	void SetParent(CModel *pParent) { m_pParent = pParent; }				// 親モデル
	void SetModelID(const int nModelID) { m_nModelID = nModelID; }			// モデルID

	/* 取得 */
	D3DXVECTOR3 GetPos() { return m_pos; }									// 位置
	D3DXVECTOR3 GetRot() { return m_rot; }									// 向き
	D3DXCOLOR GetColor() { return m_color; }								// 色
	D3DXVECTOR3 GetSize() { return m_size; }								// 大きさ
	D3DXMATRIX GetMtxWorld() { return m_mtxWorld; }							// ワールドマトリックス
	CModel *GetParent() { return m_pParent; }								// 親モデル
	int GetModelID() { return m_nModelID; }									// モデルID

private:

	// ***** 静的変数 *****
	static MODEL_MATERIAL	*m_material;		// マテリアル情報
	static int				m_nMaxModel;		// モデル数

	// ***** 変数 *****
	LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャへのポインタ
	D3DXMATRIX  m_mtxWorld;					//ワールドマトリックス


	CModel	*m_pParent;		// 親モデルの情報
	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR3 m_posOld;	// 位置(過去)
	D3DXVECTOR3 m_rot;		// 向き
	D3DXVECTOR3	m_size;		// 大きさ
	D3DXCOLOR m_color;		// 色
	int	m_nModelID;			// モデルID
};
#endif