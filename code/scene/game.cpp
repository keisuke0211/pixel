//========================================
// 
// ゲーム
// 
//========================================
// *** game.cpp ***
//========================================
#include "game.h"
#include "../system/csv_file.h"
#include "../object\UI\score.h"
#include "../object\UI\time.h"
#include "../object\model\block.h"
#include "../object\model\player.h"
#include "../object\model\enemy.h"
#include "../object\BG\bg_side.h"
#include "../object\BG\bg_ceiling.h"
#include "../object\UI\text2D.h"
#include "../system/input.h"
//#include "fade.h"

//========================================
// コンストラクタ
//========================================
CGame::CGame()
{

}

//========================================
// デストラクタ
//========================================
CGame::~CGame()
{

}

//========================================
// 初期化
//========================================
HRESULT CGame::Init(void)
{
	// 背景(側面)の生成
	CBgSide *pBgsky = CBgSide::Create();

	// 背景(天井)の生成
	CBgCeiling *pBgCeiling = CBgCeiling::Create();

	// ブロックの生成
	LoodBlock();

	CPlayer *pPlayer = CPlayer::Create();
	pPlayer->SetMotion("data\\GAMEDATA\\MODEL\\Player\\PLAYER_DATA.txt");

	// 敵の生成
	LoodEnemy();

	{
		// タイム生成
		CTime *pObj = CTime::Create();

		// サイズ設定
		pObj->SetSize(20.0f, 20.0f);

		// 位置設定
		pObj->SetPos(D3DXVECTOR3(SCREEN_WIDTH - 260.0f, 32.0f, 0.0f));

		// タイム設定
		pObj->SetTime(99);
	}

	{
		// スコア生成
		CScore *pObj = CScore::Create();

		// サイズ設定
		pObj->SetSize(20.0f, 20.0f);

		// 位置設定
		pObj->SetPos(D3DXVECTOR3(SCREEN_WIDTH - 260.0f, 52.0f, 0.0f));

		// スコア設定
		CScore::SetScore();
	}

	{
		{// 移動方法テキスト
			CText2D *pObj = CText2D::Create();

			pObj->SetPos(D3DXVECTOR3(32.0f, 32.0f, 0.0f));
			pObj->SetSize(16.0f, 16.0f);
			pObj->SetString("MOVE : W A D S");
		}

		{// ジャンプ方法テキスト
			CText2D *pObj = CText2D::Create();

			pObj->SetPos(D3DXVECTOR3(32.0f, 48.0f, 0.0f));
			pObj->SetSize(16.0f, 16.0f);
			pObj->SetString("JUMP : SPACE");
		}

		{// 射撃方法テキスト
			CText2D *pObj = CText2D::Create();

			pObj->SetPos(D3DXVECTOR3(32.0f, 64.0f, 0.0f));
			pObj->SetSize(16.0f, 16.0f);
			pObj->SetString("SHOT : ENTER & MOUSE_LEFT");
		}

		{// 配置テキスト
			CText2D *pObj = CText2D::Create();

			pObj->SetPos(D3DXVECTOR3(32.0f, 80.0f, 0.0f));
			pObj->SetSize(16.0f, 16.0f);
			pObj->SetString("SET_CUBE : E");
		}

		{// カメラ切り替えテキスト
			CText2D *pObj = CText2D::Create();

			pObj->SetPos(D3DXVECTOR3(32.0f, 128.0f, 0.0f));
			pObj->SetSize(16.0f, 16.0f);
			pObj->SetString("CAMERA_MODE : Q");
		}

		{// カメラ移動方法テキスト
			CText2D *pObj = CText2D::Create();

			pObj->SetPos(D3DXVECTOR3(32.0f, 144.0f, 0.0f));
			pObj->SetSize(16.0f, 16.0f);
			pObj->SetString("CAMERA_MOVE : MOUSE_RIGHT");
		}

		{// リセット方法テキスト
			CText2D *pObj = CText2D::Create();

			pObj->SetPos(D3DXVECTOR3(32.0f, 176.0f, 0.0f));
			pObj->SetSize(16.0f, 16.0f);
			pObj->SetString("RESET:R");
		}
	}

	return S_OK;
}

//========================================
// 終了
//========================================
void CGame::Uninit(void)
{
	CObject::ReleaseAll(CObject::TYPE_BLOCK);
	CObject::ReleaseAll(CObject::TYPE_CUBE);
	CObject::ReleaseAll(CObject::TYPE_PLAYER);
	CObject::ReleaseAll(CObject::TYPE_ENEMY);
	CObject::ReleaseAll(CObject::TYPE_EFFECT);
	CObject::ReleaseAll(CObject::TYPE_PARTICLE);
	CObject::ReleaseAll(CObject::TYPE_TIME);
	CObject::ReleaseAll(CObject::TYPE_SCORE);

}

//========================================
// 更新
//========================================
void CGame::Update(void)
{
	// エネミーの全滅
	if (CEnemy::GetEnemyAll() <= 0)
	{
		//CManager::GetFade()->SetFade(MODE_RESULT);
		CManager::SetMode(MODE_RESULT);
	}
}

//========================================
// 描画
//========================================
void CGame::Draw(void)
{

}
//========================================
// セットエネミー
//========================================
void CGame::SetEnemy(void)
{
	// 敵を全て破棄
	CObject::ReleaseAll(CObject::TYPE_ENEMY);

	// 敵の生成
	LoodEnemy();
}

//========================================
// ブロックの読み込み
//========================================
void CGame::LoodBlock(void)
{
	CSVFILE *pFile = new CSVFILE;

	// 読み込み
	pFile->FileLood("data\\GAMEDATA\\BLOCK\\STAGE_DATA.csv", true, true, ',');

	// 行数の取得
	int nRowMax = pFile->GetRowSize();

	// 各データに代入
	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		// 配置情報の生成
		int nType;				// 種類
		D3DXVECTOR3 pos;		// 位置

								// 列数の取得
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0:	pFile->ToValue(nType, sData); break;	// 種類
			case 1:	pFile->ToValue(pos.x, sData); break;	// 位置 X
			case 2:	pFile->ToValue(pos.y, sData); break;	// 位置 Y
			case 3:	pFile->ToValue(pos.z, sData); break;	// 位置 Z
			}
		}

		// 最大数に達したら返す
		if (nRow == nRowMax - 1)	// (列数 - 列の最大数 - ヘッダーの列数)
		{
			return;
		}

		// 配置
		CBlock *pObj = CBlock::Create(nType, pos);
	}

	// メモリ開放
	delete pFile;
	pFile = NULL;
}

//========================================
// エネミーの読み込み
//========================================
void CGame::LoodEnemy(void)
{
	CSVFILE *pFile = new CSVFILE;

	pFile->FileLood("data\\GAMEDATA\\ENEMY\\STAGE_DATA1.csv", true, true, ',');

	// 行数の取得
	int nRowMax = pFile->GetRowSize();

	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		int nType, nMove;
		D3DXVECTOR3 pos;

		// 列数の取得
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0:	pFile->ToValue(nType, sData); break;	// 種類
			case 1:	pFile->ToValue(nMove, sData); break;	// 移動種類
			case 2:	pFile->ToValue(pos.x, sData); break;	// 位置 X
			case 3:	pFile->ToValue(pos.y, sData); break;	// 位置 Y
			case 4:	pFile->ToValue(pos.z, sData); break;	// 位置 Z
			}
		}

		// 最大数に達したら返す
		if (nRow == nRowMax - 1)	// (列数 - 列の最大数 - ヘッダーの列数)
		{
			return;
		}

		CEnemy *pObj = CEnemy::Create(nType, nMove, pos);
	}

	delete pFile;
	pFile = NULL;
}