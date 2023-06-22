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
		PRIO_PARTICLE,	// パーティクル
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
	static void ReleaseAll(void);	// 全体の破棄
	static void UpdateAll(void);	// 全体の更新
	static void DrawAll(void);		// 全体の描画

	// ***** 関数 *****
	CObject(int nPriority = 0);
	virtual~CObject();

	/* メイン */
	virtual HRESULT Init(void) = 0;	// 初期化
	virtual void Uninit(void) = 0;	// 終了
	virtual void Update(void) = 0;	// 更新
	virtual void Draw(void) = 0;	// 描画

	/* 設定 */
	void SetType(TYPE type);		// 種類

	/* 取得 */
	virtual float GetWidth(void) { return 0.0f; }					// 幅
	virtual float GetHeight(void) { return 0.0f; }					// 高さ
	virtual float GetDepth(void) { return 0.0f; }					// 奥行き
	virtual D3DXVECTOR3 GetSize(void) { return INIT_D3DXVECTOR3; }	// サイズ
	virtual D3DXVECTOR3 GetPos(void) { return INIT_D3DXVECTOR3; }	// 位置

	TYPE GetType() { return m_type; }
	static int GetNumAll() { return m_nNumAll; };
	static CObject *GetObjectPointer(int nPriority,int nIdx) { return m_apObject[nPriority][nIdx]; }
	static CScore *GetScore(int nPriority,int nIdx);
	static CTime *GetTime(int nPriority, int nIdx);

protected:
	void Release(void);						// 破棄

private:
	static CObject *m_apObject[TYPE_MAX][MAX_OBJECT];
	static int m_nNumAll;								// オブジェクト総数
	int m_nPriority;									// 優先順位の位置
	int m_nID;											// 自分自身のID
	TYPE m_type;										// 自分自身の種類

};
#endif