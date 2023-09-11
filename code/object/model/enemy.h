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
	static const int STAND_TIME = 30;	// 待機時間の最大値

	// ***** 列挙型 *****

	// 状態
	enum STATE
	{
		STATE_NORMAL,	// 通常
		STATE_STAND,	// 待機
		STATE_DAMAGE,	// ダメージ
		STATE_MAX,
	};

	// ***** 構造体 *****

	// 敵情報
	struct Info
	{
		D3DXVECTOR3 pos;		// 位置
		D3DXVECTOR3 posOld;		// 位置(過去)
		D3DXVECTOR3 rot;		// 向き
		D3DXVECTOR3 moveRot;	// 移動向き
		D3DXVECTOR3 targetRot;	// 目標向き
		D3DXVECTOR3 move;		// 移動量
		D3DCOLOR col;			// 頂点カラー
		int nType;				// 種類
		int nMove;				// 移動種類
		int nLife;				// 寿命
		int nLifeMax;			// 寿命の最大値
		STATE state;			// 状態
		int nCntState;			// 状態管理カウンター
		int nCntTime;			// 行動カウンター
		int nTimeMax;			// 行動時間の最大値
		int nStandTime;			// 待機時間
		bool bRotMove;			// 向きの推移フラグ
		bool bCube;				// キューブに当たったか
	};

	// ***** 関数 *****
	CEnemy(int nPriority = PRIO_OBJECT);
	virtual~CEnemy();

	/* メイン */

	// 生成
	static CEnemy *Create(int nType,int nMove,D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nCntTime);

	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画

	void HitLife(int nDamage);								// Hit処理

	/* 取得 */
	Info GetInfo(void) { return m_Info; }					// エネミー情報
	D3DXVECTOR3 GetPos(void) { return m_Info.pos; }			// 位置
	D3DXVECTOR3 GetPosOld(void) { return m_Info.posOld; }	// 位置(過去)
	static int GetEnemyAll(void) { return m_nNumAll; }

private:

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
	bool Collision(PRIO nPrio, TYPE nType, VECTOR vector, D3DXVECTOR3 pos);	// 当たり判定

	// ***** 変数 *****
	Info m_Info;			// 情報
	static SetInfo *pSet;	// 配置

	static int m_nNumAll;		// 敵の総数
};
#endif