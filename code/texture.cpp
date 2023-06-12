//========================================
// 
// テクスチャ管理
// 
//========================================
// *** texture.cpp ***
//========================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"
#include "object\2D\bg2D.h"
#include "object\3D\floor.h"
#include "object\2D\block2D.h"
#include "object\3D\player.h"
#include "object\3D\enemy.h"
#include "object\3D\bullet.h"
#include "object\2D\effect2D.h"
#include "object\2D\text2D.h"

#include <assert.h>

// 定義
const char* CTexture::FILE_PATH = "data\\GAMEDATA\\TEXTURE\\TEXTURE_DATA.txt";

// 静的メンバ変数
int CTexture::m_nTextureAll = 0;
char CTexture::s_FileName[CTexture::MAX_TEXTURE][TXT_MAX] = { NULL };

// コンストラクタ
CTexture::CTexture()
{

}

// デストラクタ
CTexture::~CTexture()
{
}

//========================================
// 読み込み
//========================================
HRESULT CTexture::Load(void)
{

	FILE *pFile;				// ファイルポインタ
	char aDataSearch[TXT_MAX];	// データ検索用


	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();


	// 種類毎の情報のデータファイルを開く
	pFile = fopen(FILE_PATH, "r");

	if (pFile == NULL)
	{// 種類毎の情報のデータファイルが開けなかった場合、
	 //処理を終了する
		return S_OK;
	}

	// ENDが見つかるまで読み込みを繰り返す
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch);	// 検索

		if (!strcmp(aDataSearch, "END"))
		{// 読み込みを終了
			fclose(pFile);
			break;
		}
		if (aDataSearch[0] == '#')
		{// 折り返す
			continue;
		}

		if (m_nTextureAll == MAX_TEXTURE)
		{// 総数を上回った時
			return S_OK;
		}

		if (!strcmp(aDataSearch, "BG"))		// 背景
		{
			fscanf(pFile, "%s", &s_FileName[m_nTextureAll][0]);	// ファイル名

			// テクスチャ設定
			CBg::Load(&s_FileName[m_nTextureAll][0]);

			m_nTextureAll++;
		}
		else if (!strcmp(aDataSearch, "FLOOR")) // 床
		{
			fscanf(pFile, "%s", &s_FileName[m_nTextureAll][0]);

			CFloor::Load(&s_FileName[m_nTextureAll][0]);

			m_nTextureAll++;
		}
		else if (!strcmp(aDataSearch, "BLOCK")) // プレイヤー
		{
			fscanf(pFile, "%s", &s_FileName[m_nTextureAll][0]);

			CBlock2D::Load(&s_FileName[m_nTextureAll][0]);

			m_nTextureAll++;
		}
		else if (!strcmp(aDataSearch, "PLAYER")) // プレイヤー
		{
			fscanf(pFile, "%s", &s_FileName[m_nTextureAll][0]);

			CPlayer::Load(&s_FileName[m_nTextureAll][0]);

			m_nTextureAll++;
		}
		else if (!strcmp(aDataSearch, "ENEMY"))		// エネミー
		{
			fscanf(pFile, "%s", &s_FileName[m_nTextureAll][0]);

			CEnemy::Load(&s_FileName[m_nTextureAll][0]);

			m_nTextureAll++;
		}
		else if (!strcmp(aDataSearch, "BULLET"))	// 弾
		{
			fscanf(pFile, "%s", &s_FileName[m_nTextureAll][0]);

			CBullet::Load(&s_FileName[m_nTextureAll][0]);

			m_nTextureAll++;
		}
		else if (!strcmp(aDataSearch, "EFFECT")) // エフェクト
		{
			fscanf(pFile, "%s", &s_FileName[m_nTextureAll][0]);

			CEffect2D::Load(&s_FileName[m_nTextureAll][0]);

			m_nTextureAll++;
		}
		else if (!strcmp(aDataSearch, "TEXT")) // テキスト
		{
			fscanf(pFile, "%s", &s_FileName[m_nTextureAll][0]);

			CText2D::Load(&s_FileName[m_nTextureAll][0]);

			m_nTextureAll++;
		}
	}

	return S_OK;
}

//========================================
// 全ての解放
//========================================
void CTexture::Unload(void)
{
	CBg::Unload();			// 背景
	CFloor::Unload();		// 床
	CBlock2D::Unload();		// ブロック
	CPlayer::Unload();		// プレイヤー
	CEnemy::Unload();		// エネミー
	CBullet::Unload();		// バレット
	CEffect2D::Unload();	// エフェクト
	CText2D::Unload();		// テキスト
}