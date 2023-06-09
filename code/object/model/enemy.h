//========================================
// 
// エネミー処理
// 
//========================================
// *** enemy.h ***
//========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "../../main.h"
#include "../objectX.h"

//****************************************
// クラス
//****************************************
class CEnemy : public CObjectX
{
public:

	// ***** 定義 *****
	static const int MAX_ENEMY = 30;	// 敵の最大数

	// ***** 列挙型 *****

	// 状態
	typedef enum
	{
		STATE_NORMAL,	// 通常
		STATE_DAMAGE,	// ダメージ
		STATE_MAX,
	}STATE;

	// ***** 構造体 *****

	// 敵情報
	typedef struct
	{
		D3DXVECTOR3 pos;	// 位置
		D3DXVECTOR3 posOld;	// 位置(過去)
		D3DXVECTOR3 rot;	// 向き
		D3DXVECTOR3 rotOld;	// 向き(過去)
		D3DXVECTOR3 move;	// 移動量
		D3DCOLOR col;		// 頂点カラー
		int nType;			// 種類
		int nLife;			// 寿命
		STATE state;		//状態
		int nCntState;	//状態管理カウンター
	} Info;

	// ***** 関数 *****
	CEnemy(int nPriority = PRIO_OBJECT);
	virtual~CEnemy();

	/* メイン */

	// 生成
	static CEnemy *Create(D3DXVECTOR3 pos);

	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画

	static void SetEnemy(int nStage, int nUnit);	// 配置
	void HitLife(int nDamage);						// Hit処理

	/* 取得 */
	Info GetInfo() { return m_Info; }					// エネミー情報
	D3DXVECTOR3 GetPos() { return m_Info.pos; }			// 位置
	D3DXVECTOR3 GetPosOld() { return m_Info.posOld; }	// 位置(過去)

private:

	// ***** 列挙型 *****

	// 設定項目
	typedef enum
	{
		SET_TYPE,	// 種類
		SET_POS,	// 位置
		SET_POS_Y,	// 位置 Y
		SET_POS_Z,	// 位置 Z
		SET_SPEED,	// 移動量
		SET_STAGE,	// ステージID
		SET_UNIT,	// 部隊ID
		SET_MAX,
	}SET;

	// ***** 構造体 *****

	// 配置情報
	typedef struct
	{
		D3DXVECTOR3 pos;	// 位置
		D3DXVECTOR3 rot;	// 向き
		int nType;			// 種類
		int nSpeed;			// 移動量
		int nStage;			// ステージID
		int nUnit;			// 部隊ID
		bool bSet;			// 配置したかどうか

	} SetInfo;

	// ***** 関数 *****
	void SetState(STATE state);	// 状態設定
	void StateShift(void);		// 状態推移
	static void Load(void);		// 読み込み

	// ***** 変数 *****
	Info m_Info;			// 情報
	static SetInfo *pSet;	// 配置

	static int nNumSet;		// 敵の配置数
};
#endif