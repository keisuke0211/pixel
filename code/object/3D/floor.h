//========================================
// 
// 床処理
// 
//========================================
// *** floor.h ***
//========================================
#ifndef _FLOOR_H_
#define _FLOOR_H_

#include "../../main.h"
#include "../object3D.h"

//****************************************
// クラス
//****************************************
class CFloor : public CObject3D
{
public:

	// ***** 定義 *****
	static const int MAX_TEXTURE = 50;	// テクスチャの最大数

	// ***** 構造体 *****

	// プレイヤー情報
	typedef struct
	{
		D3DXVECTOR3 pos;			// 位置
		D3DXVECTOR3 rot;			// 向き
		float fWidth;				// 幅
		float fHeight;				// 高さ
	} Info;

	// ***** 関数 *****
	CFloor(int nPriority = TYPE_FLOOR);	// コンストラクタ
	~CFloor();							// デストラクタ

	// 生成
	static CFloor *Create(void);

	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画

	static HRESULT Load(char *pPath);			// テクスチャの生成 
	static void Unload(void);					// テクスチャの破棄

	/* 取得 */
	Info GetInfo() { return m_Info; }	// プレイヤー情報
private:

	// ***** 変数 *****
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];		// 共有テクスチャ
	static int m_nTexture;									// テクスチャの数
	Info m_Info;	// プレイヤー情報

};
#endif