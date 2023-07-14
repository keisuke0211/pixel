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
	CFloor(int nPriority = PRIO_OBJECT);	// コンストラクタ
	~CFloor();								// デストラクタ

	// 生成
	static CFloor *Create(void);

	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画

	/* 取得 */
	Info GetInfo() { return m_Info; }	// プレイヤー情報
private:

	// ***** 変数 *****
	Info m_Info;	// プレイヤー情報

};
#endif