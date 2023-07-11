//========================================
// 
// オブジェクト処理
// 
//========================================
// *** objext.h ***
//========================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "../main.h"
#include "../physics.h"

//****************************************
// 前方宣言
//****************************************
class CScore;	// スコア
class CTime;	// タイム

//****************************************
// クラス
//****************************************
class CObject : public CPhysics
{
public:
	/* 定義 */
	static const int MAX_OBJECT = 2048;	// オブジェクトの最大数

	// ***** 列挙型 *****

	// 優先順位種類
	typedef enum
	{
		PRIO_NONE = 0,	// 無し
		PRIO_OBJ2D,		// オブジェクト2D
		PRIO_OBJ3D,		// オブジェクト3D
		PRIO_OBJX,		// オブジェクトX
		PRIO_EFFECT,	// エフェクト
		PRIO_TEXT,		// テキスト
		PRIO_MAX
	}PRIO;

	// オブジェクト種類
	typedef enum
	{
		TYPE_NONE = 0,	// 無し
		TYPE_BG,		// 背景
		TYPE_BG_MULTI,	// マルチ背景
		TYPE_FLOOR,		// 床
		TYPE_BLOCK,		// ブロック
		TYPE_CUBE,		// キューブ
		TYPE_PLAYER,	// プレイヤー
		TYPE_ENEMY,		// エネミー
		TYPE_BULLET,	// バレット
		TYPE_EFFECT,	// エフェクト
		TYPE_PARTICLE,	// パーティクル
		TYPE_TEXT,		// テキスト
		TYPE_TIME,		// タイム
		TYPE_SCORE,		// スコア
		TYPE_MAX
	}TYPE;

	// ***** 静的関数 *****
	/* 全ての破棄			*/static void ReleaseAll(void);
	/* 全ての破棄(種類毎)	*/static void ReleaseAll(TYPE type);	// [オーバーロード]
	/* 全ての更新			*/static void UpdateAll(void);
	/* 全ての描画			*/static void DrawAll(void);

	// ***** 関数 *****
	CObject(int nPriority = 0);
	virtual~CObject();

	/* 初期化	*/virtual HRESULT Init(void) = 0;
	/* 終了		*/virtual void Uninit(void) = 0;
	/* 更新		*/virtual void Update(void) = 0;
	/* 描画		*/virtual void Draw(void) = 0;

	// -- 設定 ------------------------------------------
	/* 種類設定*/void SetType(TYPE type);

	// -- 取得 ------------------------------------------
	/* 幅				*/virtual float GetWidth(void) { return 0.0f; }
	/* 高さ				*/virtual float GetHeight(void) { return 0.0f; }
	/* 奥行き			*/virtual float GetDepth(void) { return 0.0f; }
	/* サイズ			*/virtual D3DXVECTOR3 GetSize(void) { return INIT_D3DXVECTOR3; }
	/* 位置				*/virtual D3DXVECTOR3 GetPos(void) { return INIT_D3DXVECTOR3; }
	/* 位置(過去)		*/virtual D3DXVECTOR3 GetPosOld(void) { return INIT_D3DXVECTOR3; }
	/* 向き				*/virtual D3DXVECTOR3 GetRot(void) { return INIT_D3DXVECTOR3; }
	/* 向き(過去)		*/virtual D3DXVECTOR3 GetRotOld(void) { return INIT_D3DXVECTOR3; }
	/* 種類				*/TYPE GetType(void) { return m_type; }
	/* 自分自身ID		*/int GetID(void) { return m_nID; }
	/* オブジェクト総数	*/static int GetNumAll(void) { return m_nNumAll; };
	/* オブジェクト情報	*/static CObject *GetObjectPointer(int nPriority,int nIdx) { return m_apObject[nPriority][nIdx]; }
	/* スコア情報		*/static CScore *GetScore(int nPriority,int nIdx);
	/* タイム情報		*/static CTime *GetTime(int nPriority, int nIdx);

protected:
	/* 解放処理 */void Release(void);

private:
	static CObject *m_apObject[PRIO_MAX][MAX_OBJECT];	// オブジェクトのポインタ配列
	static int m_nNumAll;								// オブジェクト総数
	int m_nPriority;									// 優先順位の位置
	int m_nID;											// 自分自身のID
	TYPE m_type;										// 自分自身の種類

};
#endif