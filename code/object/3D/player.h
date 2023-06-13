//========================================
// 
// プレイヤー処理
// 
//========================================
// *** player.h ***
//========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "../../main.h"
#include "../objectX.h"

//****************************************
// クラス
//****************************************
class CPlayer : public CObjectX
{
public:

	// ***** 定義 *****
	static const int MAX_TEXTURE = 50;	// テクスチャの最大数

	static const int PLAYER_MAX = 1;	// プレイヤーの最大数
	static const float PLAYER_SPEED;	// プレイヤーの移動量

	// ***** 構造体 *****

	// プレイヤー情報
	typedef struct
	{
		D3DXVECTOR3 pos;		// 位置
		D3DXVECTOR3 rot;		// 向き
		D3DXVECTOR3 moveRot;	// 移動向き
		D3DXVECTOR3 targetRot;	// 目標向き
		D3DXVECTOR3 move;		// 移動量
		D3DCOLOR col;			//　頂点カラー
		float fWidth;			// 幅
		float fHeight;			// 高さ
		float fDepth;			// 奥行き
	} Info;

	// ***** 関数 *****
	CPlayer(int nPriority = TYPE_PLAYER);
	~CPlayer();

	/* メイン */

	// 生成
	static CPlayer *Create(void);

	HRESULT Init(void);				// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画

	/* 取得 */
	D3DXVECTOR3 GetPos() { return m_Info.pos; }

private:
	// ***** 関数 *****
	void MovePos(void);		// 移動
	void UpdatePos(void);	// 位置更新

	// ***** 変数 *****
	Info m_Info;		// プレイヤー情報
};
#endif