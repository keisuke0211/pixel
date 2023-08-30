//========================================
// 
// ステージ選択
// 
//========================================
// *** stage_menu.h ***
//========================================
#ifndef _STAGE_MANU_H_	//このマクロ定義がされてなかったら
#define _STAGE_MANU_H_	//２重インクルード防止のマクロ定義

#include "../../main.h"
#include "../object2D.h"
#include "../../scene/game.h"

//****************************************
// 前方宣言
//****************************************
class CText;

//****************************************
//　クラス
//****************************************
class CStage : public CObject2D
{
public:

	// 場所
	enum PLACE
	{
		PLACE_LEFT_EDGE = 0,	// 左端
		PLACE_LEFT,				// 左
		PLACE_CENTER,			// 中央
		PLACE_RIGHT,			// 右
		PLACE_RIGHT_EDGE,		// 右端
		PLACE_VACANT,			// 空
		PLACE_MAX
	};

	// ***** 構造体 *****

	// 共通情報
	struct Info
	{
		D3DXVECTOR3 pos;		// 位置
		D3DXVECTOR3 TargetPos;	// 目標位置
		D3DXCOLOR col;			// 色
		int nType;				// 種類
		int nPlace;				// 場所
		D3DXVECTOR2 size;		// 大きさ
		D3DXVECTOR2 TargetSize;	// 目標の大きさ
		bool bMove;				// 移動フラグ
	};
	
	// ***** 関数 *****
	CStage(int nPriority = PRIO_OBJECT);
	~CStage();

	// -- メイン ------------------------------------------
	/* 初期化		*/HRESULT Init(void);
	/* 終了			*/void Uninit(void);
	/* 更新			*/void Update(void);
	/* 描画			*/void Draw(void);
	/* 生成			*/static CStage *Create(int nType, int nPlace);

	// -- 設定 ------------------------------------------
	/* 位置・画像 */void SetStageInfo(int nType,int nPlace);


	// -- 取得 ------------------------------------------
	/* 種類 */int GetStageType(void) { return m_Info.nType; }
	/* 移動	*/bool IsMove(void) { return m_Info.bMove; }

private:
	// ***** 変数 *****
	Info m_Info;		// 情報

	// 各場所の位置
	D3DXVECTOR3 m_Place[PLACE_MAX] = {
		D3DXVECTOR3(-200.0f,360.0f,0.0f),
		D3DXVECTOR3(220.0f,360.0f,0.0f),
		D3DXVECTOR3(640.0f,360.0f,0.0f),
		D3DXVECTOR3(1060.0f,360.0f,0.0f),
		D3DXVECTOR3(1480.0f,360.0f,0.0f),
		D3DXVECTOR3(1900.0f,360.0f,0.0f),
	};

	// ***** 静的変数 *****
	static LPDIRECT3DTEXTURE9 m_pTexture[CGame::Stage_MAX];	// 共有テクスチャ

	static int m_nSelectStage;	// 現在選択しているステージ
};

#endif // !_TEXTURE_H_

