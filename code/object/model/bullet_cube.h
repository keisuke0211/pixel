//========================================
// 
// キューブ処理
// 
//========================================
// *** bullet_cube.h ***
//========================================
#ifndef _BULLET_CUBE_H_
#define _BULLET_CUBE_H_

#include "../../main.h"
#include "../objectX.h"

//****************************************
// クラス
//****************************************
class CCube : public CObjectX
{
public:

	// ***** 列挙型 *****

	// モデル種類
	enum SHAPE
	{
		SHAPE_LINE = 0,	// 直線
		SHAPE_SQUARE,	// 四角
		SHAPE_MAX
	};

	// ***** 構造体 *****

	// プレイヤー情報
	struct Info
	{
		D3DXVECTOR3 pos;		// 位置
		D3DXVECTOR3 posOld;		// 位置(過去)
		D3DXVECTOR3 movePos;	// 移動位置
		D3DXVECTOR3 targetPos;	// 目標位置	
		D3DXVECTOR3 rot;		// 向き
		D3DXVECTOR3 rotOld;		// 向き(過去)
		D3DXVECTOR3	size;		// サイズ
		D3DXCOLOR col;			// 頂点カラー
		int nShape;				// 形状
		int nStandTime;			// 待機時間
		bool bContact;			// 接触フラグ
		bool bActivation;		// 発動フラグ
		int nLife;				// 寿命
		int nLifeMax;			// 寿命の最大値
		float fRadius;			// 半径
		int nCntRadius;			// 半径・推移時間
		float fRadiusRate;		// 半径の割合
		bool bSet;				// 配置フラグ
		int nChain;				// 連鎖カウント
		bool bBom;				// 爆発フラグ
		int nID;				// 自身のID
	};

	// ***** 関数 *****
	/* コンストラクタ	*/CCube(int nPriority = PRIO_CUBE);
	/* デストラクタ		*/~CCube();

	// -- メイン -------------------------------
	/* 初期化	*/HRESULT Init(void);
	/* 終了		*/void Uninit(void);
	/* 更新		*/void Update(void);
	/* 描画		*/void Draw(void);
	/* 生成		*/static CCube *Create(int nType, D3DXVECTOR3 pos);

	// -- 設定 -------------------------------
	/* 位置			*/void CubeSetPos(const D3DXVECTOR3 pos) { m_Info.pos = m_Info.posOld = pos; }
	/* 向き			*/void CubeSetRot(const D3DXVECTOR3 rot) { m_Info.rot = rot; }
	/* 色			*/void CubeSetColor(const D3DXCOLOR col) { m_Info.col = col; }
	/* サイズ		*/void CubeSetSize(const D3DXVECTOR3 size) { m_Info.size = size; }
	/* 寿命			*/void CubeSetLife(const int nLife) { m_Info.nLife = nLife; }
	/* 種類			*/void CubeSetType(const int type) { m_Info.nShape = type; }
	/* 先頭フラグ	*/void CubeLeadSet(const bool bSet) { bLeadSet = bSet; }

	// -- 取得 -------------------------------
	/* 位置			*/D3DXVECTOR3 CubeGetPos(void) { return m_Info.pos; }
	/* 向き			*/D3DXVECTOR3 GetRot(void) { return m_Info.rot; }
	/* 色			*/D3DXCOLOR CubeGetColor(void) { return m_Info.col; }
	/* サイズ		*/D3DXVECTOR3 CubeGetSize(void) { return m_Info.size; }
	/* 配置フラグ	*/bool CubeGetSet(void) { return m_Info.bSet; }
	/* 先頭フラグ	*/static bool GetLeadSet(void) { return bLeadSet; }
	/* 連鎖カウント	*/int GetChain(void) { return m_Info.nChain; }
	/* ID			*/int GetID(void) { return m_Info.nID; }

private:

	// ***** 関数 ***** correction
	/* 位置補正			*/bool Correction(VECTOR vector, D3DXVECTOR3 pos);
	/* 接触判定			*/bool Contact(int mode,VECTOR vector, D3DXVECTOR3 pos);
	/* 当たり判定		*/bool Collsion(D3DXVECTOR3 pos, D3DXVECTOR3 PairPos, D3DXVECTOR3 size, D3DXVECTOR3	PairSize);
	/* 敵との当たり判定 */void EnemyCollsion(D3DXVECTOR3 pos);
	/* 当たり判定(方向)	*/bool Collsion(VECTOR vector,CObject *pObj,CObject *pPairObj);
	/* 破壊処理			*/void Destruction(CCube *pCube);


	// ***** 変数 *****
	static int m_nNumAll;	// キューブの総数
	static int m_nNumChain;	// 連爆の総数
	static bool bLeadSet;	// 先頭配置フラグ
	Info m_Info;			// プレイヤー情報

};
#endif