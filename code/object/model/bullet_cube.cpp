//========================================
// 
// キューブ処理
// 
//========================================
// *** block.cpp ***
//========================================
#include "bullet_cube.h"
#include "model.h"
#include "../../sound.h"
#include "../../csv_file.h"

//========================================
// マクロ定義
//========================================
#define RADIUS_TIME			(20)	// 半径・推移時間
#define SIZE_DIAMETER		(2.0f)	// サイズの倍率
#define COLLSION_DIAMETER	(1.0f)	// 判定の倍率

//========================================
// コンストラクタ
//========================================
CCube::CCube(int nPriority) : CObjectX(nPriority)
{
	// 値をクリア
	m_Info.pos = INIT_D3DXVECTOR3;		// 位置
	m_Info.posOld = INIT_D3DXVECTOR3;	// 位置(過去)
	m_Info.movePos = INIT_D3DXVECTOR3;	// 移動位置
	m_Info.targetPos = INIT_D3DXVECTOR3;// 目的位置
	m_Info.rot = INIT_D3DXVECTOR3;		// 向き
	m_Info.rotOld = INIT_D3DXVECTOR3;	// 向き(過去)
	m_Info.size = INIT_D3DXVECTOR3;		// 大きさ
	m_Info.col = INIT_D3DXCOLOR;		// 色
	m_Info.nType = 0;					// 種類
	m_Info.nStandTime = 0;				// 待機時間
	m_Info.bContact = false;			// 接触フラグ
	m_Info.bActivation = false;			// 発動フラグ
	m_Info.nLife = 0;					// 寿命
	m_Info.nLifeMax = 0;				// 寿命の最大値
	m_Info.fRadius = 0.0f;				// 半径
	m_Info.nCntRadius = 0;				// 半径推移	
	m_Info.fRadiusRate = 0.0f;			// 半径の割合
	m_Info.bSet = false;				// 配置フラグ
	m_Info.nID = 0;						// 自分自身のID
}

//========================================
// デストラクタ
//========================================
CCube::~CCube()
{

}

//========================================
// 生成
//========================================
CCube *CCube::Create(int nType, D3DXVECTOR3 pos)
{
	CCube *pCube = NULL;

	if (pCube != NULL)
	{
		return pCube;
	}

	// オブジェクト2Dの生成
	pCube = new CCube;

	pCube->m_Info.nCntRadius = RADIUS_TIME;
	pCube->m_Info.fRadiusRate = 0.0f;
	pCube->m_Info.bSet = false;
	pCube->SetModel(MODEL_BULLET + nType);

	// 初期化処理
	pCube->Init();

	pCube->m_Info.nType = nType;
	pCube->m_Info.nLife = 300;
	pCube->m_Info.nLifeMax = 300;
	pCube->CubeSetPos(pos);
	pCube->SetPos(pos);

	// 位置補正
	/* X軸	*/if (pCube->Correction(VECTOR_X, pCube->m_Info.pos)) { return pCube; }
	/* Y軸	*/if (pCube->Correction(VECTOR_Y, pCube->m_Info.pos)) { return pCube; }
	/* Z軸	*/if (pCube->Correction(VECTOR_Z, pCube->m_Info.pos)) { return pCube; }

	
	return pCube;
}

//========================================
// 初期化
//========================================
HRESULT CCube::Init(void)
{
	CObjectX::Init();

	// 種類の設定
	SetType(TYPE_CUBE);

	m_Info.pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nType = 0;
	m_Info.fRadius = 1.0f;
	m_Info.nID = GetID();

	// 生成
	SetPos(m_Info.pos);
	//SetRot(m_Info.rot);
	SetScale(m_Info.size);
	SetColor(m_Info.col);

	return S_OK;
}

//========================================
// 終了
//========================================
void CCube::Uninit(void)
{
	CObjectX::Uninit();
}

//========================================
// 更新
//========================================
void CCube::Update(void)
{
	// 過去の位置・向きの更新
	m_Info.posOld = m_Info.pos;
	m_Info.rotOld = m_Info.rot;

	// 半径推移
	if (m_Info.bSet == false)
	{
		m_Info.fRadiusRate = (float)m_Info.nCntRadius / (float)RADIUS_TIME;
		m_Info.fRadius = 1 * (1.0f - m_Info.fRadiusRate);

		if (--m_Info.nCntRadius <= 0)
		{
			m_Info.bSet = true;
		}
	}

	if (m_Info.bSet && !m_Info.bContact)
	{
		// 寿命
		if (--m_Info.nLife <= 0)
		{
			Uninit();
			return;
		}
		else if (m_Info.nLife <= RADIUS_TIME)
		{
			m_Info.fRadius -= m_Info.fRadius / m_Info.nLife;
			m_Info.col.a *= ((float)m_Info.nLife / RADIUS_TIME);

			SetColor(m_Info.col);
		}
	}

	// サイズの更新
	m_Info.size = D3DXVECTOR3(m_Info.fRadius, m_Info.fRadius, m_Info.fRadius);

	SetPos(m_Info.pos);
	//SetRot(m_Info.rot);
	SetScale(m_Info.size);

	CObjectX::Update();
}

//========================================
// 描画
//========================================
void CCube::Draw(void)
{
	CObjectX::Draw();
}

//========================================
// 位置補正
//========================================
bool CCube::Correction(VECTOR vector, D3DXVECTOR3 pos)
{
	for (int nCntObj = 0; nCntObj < GetNumAll(); nCntObj++)
	{
		//　判定フラグ
		bool bHit = false;

		// オブジェクトのポインタ
		CObject *pObj;

		// オブジェクトを取得
		pObj = GetObjectPointer(PRIO_OBJX, nCntObj);

		if (pObj != NULL)
		{
			int ID;
			TYPE type;

			// IDを取得
			ID = pObj->GetID();

			// 種類を取得
			type = pObj->GetType();

			if (type == TYPE_CUBE && m_Info.nID != ID)
			{// 種類がキューブの場合

				// 自分自身の取得
				float fWidth = GetWidth();		// 幅
				float fHeight = GetHeight();	// 高さ
				float fDepth = GetDepth();		// 奥行き

				// 相手の取得
				D3DXVECTOR3 PairPos = pObj->GetPos();	// 位置
				float fPairWidth = pObj->GetWidth();	// 幅
				float fPairHeight = pObj->GetHeight();	// 高さ
				float fPairDepth = pObj->GetDepth();	// 奥行き

				//　中心点からの距離
				float fCubeWidth = fPairWidth * SIZE_DIAMETER;		// 幅
				float fCubeHeight = fPairHeight * SIZE_DIAMETER;	// 高さ
				float fCubeDepth = fPairDepth * SIZE_DIAMETER;		// 奥行き

				// 少し小さくする
				fPairWidth *= 0.75f;	// 幅
				fPairHeight *= 0.75f;	// 高さ
				fPairDepth *= 0.75f;	// 奥行き

				// 各方向の当たり判定
				D3DXVECTOR3 PairUpPos = D3DXVECTOR3(PairPos.x, PairPos.y + fCubeHeight, PairPos.z);		// 上
				D3DXVECTOR3 PairDownPos = D3DXVECTOR3(PairPos.x, PairPos.y - fCubeHeight, PairPos.z);	// 下
				D3DXVECTOR3 PairLeftPos = D3DXVECTOR3(PairPos.x + fCubeWidth, PairPos.y, PairPos.z);	// 左
				D3DXVECTOR3 PairRightPos = D3DXVECTOR3(PairPos.x - fCubeWidth, PairPos.y, PairPos.z);	// 右
				D3DXVECTOR3 PairBackPos = D3DXVECTOR3(PairPos.x, PairPos.y, PairPos.z + fCubeDepth);	// 奥
				D3DXVECTOR3 PairFrontPos = D3DXVECTOR3(PairPos.x, PairPos.y, PairPos.z - fCubeDepth);	// 手前

				switch (vector)
				{
				case VECTOR_X: {	/* X方向 */

					if (Collsion(pos, PairLeftPos, D3DXVECTOR3(fWidth, fHeight,fDepth), D3DXVECTOR3(fPairWidth,fPairHeight,fPairDepth)))
					{// 左側
						m_Info.pos = PairLeftPos;
						break;
					}

					if (Collsion(pos, PairRightPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
					{// 右側
						m_Info.pos = PairRightPos;
						break;
					}
				}
				   break;
				case VECTOR_Y: {	/* Y方向 */

					if (Collsion(pos, PairUpPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
					{// 上側
						m_Info.pos = PairUpPos;
						break;
					}

					if (Collsion(pos, PairDownPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
					{// 下側
						m_Info.pos = PairDownPos;
						break;
					}
				}
				   break;
				case VECTOR_Z: {	/* Z方向 */

					if (Collsion(pos, PairBackPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
					{// 奥側
						m_Info.pos = PairBackPos;
						break;
					}

					if (Collsion(pos, PairFrontPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
					{// 手前側
						m_Info.pos = PairFrontPos;
						break;
					}
				}
				   break;
				}

				// 判定が真なら TRUE を返す
				if (bHit)
				{
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

//========================================
// 接触判定
//========================================
bool CCube::Contact(VECTOR vector, D3DXVECTOR3 pos)
{
	for (int nCntObj = 0; nCntObj < GetNumAll(); nCntObj++)
	{
		bool bHit = false;

		CObject *pObj;

		// オブジェクトを取得
		pObj = GetObjectPointer(PRIO_OBJX, nCntObj);

		if (pObj != NULL)
		{
			int ID;
			TYPE type;

			// IDを取得
			ID = pObj->GetID();

			// 種類を取得
			type = pObj->GetType();

			if (type == TYPE_CUBE && m_Info.nID != ID)
			{// 種類がキューブの場合

				

				if (bHit)
				{
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

//========================================
// 当たり判定
//========================================
bool CCube::Collsion(D3DXVECTOR3 pos, D3DXVECTOR3 PairPos, D3DXVECTOR3 size, D3DXVECTOR3 PairSize)
{
	// 判定フラグ
	bool bHit = false;

	if ((pos.x + size.x) > (PairPos.x - PairSize.x) &&
		(pos.x - size.x) < (PairPos.x + PairSize.x) &&
		(pos.y + size.y) > (PairPos.y - PairSize.y) &&
		(pos.y - size.y) < (PairPos.y + PairSize.y) &&
		(pos.z + size.z) > (PairPos.z - PairSize.z) &&
		(pos.z - size.z) < (PairPos.z + PairSize.z))
	{// ブロックが判定内にある時、

		return TRUE;
	}

	return FALSE;
}