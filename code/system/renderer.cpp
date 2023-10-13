//========================================
// 
// 描画処理
// 
//========================================
// *** renderer.cpp ***
//========================================
#include "renderer.h"
#include "../object\object.h"
#include "../manager.h"
#include "../object/BG/test.h"
#include "../system/camera.h"

// 静的変数
LPD3DXFONT CRenderer::m_pFont = NULL;	// フォント

//========================================
// コンストラクタ
//========================================
CRenderer::CRenderer()
{
	// 値をクリアする
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
}

//========================================
// デストラクタ
//========================================
CRenderer::~CRenderer()
{

}

//========================================
// 描画の初期化処理
//========================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;        //ディスプレイモード

	//Direct3Dオブジェクトの生成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}
	//現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));   //パラメータのゼロクリア

	m_d3dpp.BackBufferWidth = SCREEN_WIDTH;								//ゲーム画面サイズ(幅)
	m_d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//ゲーム画面サイズ(高さ)
	m_d3dpp.BackBufferFormat = d3ddm.Format;							//バックバッファの形式
	m_d3dpp.BackBufferCount = 1;										//バックバッファの数
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;							//ダブルバッファの切り替え(映像信号に同期)
	m_d3dpp.EnableAutoDepthStencil = TRUE;								//デプスバッファとステンシルバッファを作成
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//デプスバッファとして16bitを使う
	m_d3dpp.Windowed = bWindow;											//ウインドウモード
	m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//リフレッシュレート
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;			//インターバル

																		//Direct3Dデバイスも生成
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,                     //描画処理
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,//頂点処理
		&m_d3dpp,
		&m_pD3DDevice)))                    //描画処理と頂点処理をハードウェアで行う
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,//描画処理
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,//頂点処理
			&m_d3dpp,
			&m_pD3DDevice)))
		{
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,                     //描画処理
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,//頂点処理
				&m_d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//デバック表示用フォントの生成
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PALETTE,
		"Terminal", &m_pFont);

	//レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//D3DCULL_NONE　カリング無し D3DCULL_CW 表面カリング　D3DCULL_CCW　裏面カリング
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステート設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステート設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	LPDIRECT3DSURFACE9 pRenderDef, pZBuffDef;

	// レンダリングターゲット用テクスチャの作成
	m_pD3DDevice->CreateTexture(SCREEN_HEIGHT,
		SCREEN_HEIGHT,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&m_apTextureMT[0],
		NULL);

	m_pD3DDevice->CreateTexture(SCREEN_HEIGHT,
		SCREEN_HEIGHT,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&m_apTextureMT[1],
		NULL);

	// テクスチャレンダリング用インターフェースの生成
	m_apTextureMT[0]->GetSurfaceLevel(0, &m_apRenderMT[0]);
	m_apTextureMT[1]->GetSurfaceLevel(0, &m_apRenderMT[1]);

	// テクスチャレンダリング用Zバッファの生成
	m_pD3DDevice->CreateDepthStencilSurface(SCREEN_WIDTH,
		SCREEN_HEIGHT,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&m_pZBuffMT,
		NULL);
	
	// 現在のレンダリングターゲットを取得（保存）
	m_pD3DDevice->GetRenderTarget(0, &pRenderDef);

	// 現在のZバッファを取得（保存）
	m_pD3DDevice->GetDepthStencilSurface(&pZBuffDef);

	// レンダリングターゲットを生成したテクスチャに設定
	m_pD3DDevice->SetRenderTarget(0, m_apRenderMT[0]);
	m_pD3DDevice->SetRenderTarget(0, m_apRenderMT[1]);

	// Zバッファを生成したZバッファに設定
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

	// レンダリングターゲット用のテクスチャクリア
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// レンダリングターゲットを元に戻す
	m_pD3DDevice->SetRenderTarget(0, pRenderDef);

	// Zバッファを元に戻す
	m_pD3DDevice->SetDepthStencilSurface(pZBuffDef);

	// テクスチャレンダリング用ビューポートの設定
	m_viewportMT.X = 0;
	m_viewportMT.Y = 0;
	m_viewportMT.Width = SCREEN_WIDTH;
	m_viewportMT.Height = SCREEN_HEIGHT;
	m_viewportMT.MinZ = 0.0f;
	m_viewportMT.MaxZ = 1.0f;

	{
		// 頂点バッファの生成
		m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&m_pVtxBuffMT,
			NULL);

		// 設定用ポインタ
		VERTEX_2D *pVtx;

		// 頂点バッファのロックと頂点情報へのポインタを取得
		m_pVtxBuffMT->Lock(0, 0, (void **)&pVtx, 0);

		D3DXVECTOR3 m_pos = D3DXVECTOR3(620.0f,320.0f,0.0f);	// 位置
		D3DXVECTOR3 m_rot = INIT_D3DXVECTOR3;	// 向き
		D3DXCOLOR m_color = INIT_D3DXCOLOR;	// 色
		float m_fWidth = 1280.0f;			// 幅
		float m_fHeight = 720.0f;			// 高さ

		// 対角線の長さ
		float fLength = sqrtf((m_fWidth * m_fWidth) + (m_fHeight * m_fHeight)) * 0.5f;
		// 対角線の角度
		float fAngle = atan2f(m_fWidth, m_fHeight);

		// 頂点座標を設定
		pVtx[0].pos.x = m_pos.x + sinf(m_rot.y - (D3DX_PI - fAngle)) * fLength;
		pVtx[0].pos.y = m_pos.y + cosf(m_rot.y - (D3DX_PI - fAngle)) * fLength;
		pVtx[1].pos.x = m_pos.x + sinf(m_rot.y + (D3DX_PI - fAngle)) * fLength;
		pVtx[1].pos.y = m_pos.y + cosf(m_rot.y + (D3DX_PI - fAngle)) * fLength;
		pVtx[2].pos.x = m_pos.x + sinf(m_rot.y - fAngle) * fLength;
		pVtx[2].pos.y = m_pos.y + cosf(m_rot.y - fAngle) * fLength;
		pVtx[3].pos.x = m_pos.x + sinf(m_rot.y + fAngle) * fLength;
		pVtx[3].pos.y = m_pos.y + cosf(m_rot.y + fAngle) * fLength;

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラー
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

		// 頂点バッファの破棄
		m_pVtxBuffMT->Unlock();
	}
	return S_OK;
}

//========================================
// 描画の終了処理
//========================================
void CRenderer::Uninit(void)
{
	// オブジェクトの全体の破棄
	CObject::ReleaseAll();

	//デバック表示用フォントの破棄
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}

	// デバイスの破棄
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}


	// オブジェクトの破棄
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//========================================
// 描画の更新処理
//========================================
void CRenderer::Update(void)
{
	CObject::UpdateAll();		// オブジェクト全体
}

//========================================
// 描画の描画処理
//========================================
void CRenderer::Draw(void)
{
	//画面クリア(バックバッファ&Zバッファのクリア)
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	CCamera *pCamera = CManager::GetCamera();		// カメラの取得
	D3DXVECTOR3 posV = pCamera->GetInfo().posV;		// 視点
	D3DXVECTOR3 posR = pCamera->GetInfo().posR;		// 注視点
	D3DXVECTOR3 vecU = pCamera->GetInfo().vecU;		// 上方向ベクトル

	// レンタリングターゲットをテクスチャ[0]に設定
	ChangeTarget(posV, posR, vecU);

	// テクスチャ[0]をクリア
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合

		// オブジェクト全体の描画処理
		CObject::DrawAll();

		// フィードバック用ポリゴンにテクスチャ[1]を張り付けて描画
		m_pD3DDevice->SetStreamSource(0, m_pVtxBuffMT, 0, sizeof(VERTEX_2D));
		m_pD3DDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャ設定
		m_pD3DDevice->SetTexture(0, m_apTextureMT[1]);

		// ポリゴンの描画
		m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		// レンダリングターゲットを元に戻す
		m_pD3DDevice->SetRenderTarget(0, m_apRenderMT[0]);

		// フィードバック用ポリゴンにテクスチャ[0]を張り付けて描画

		// テクスチャ設定
		m_pD3DDevice->SetTexture(0, m_apTextureMT[0]);

		// ポリゴンの描画
		m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		// テクスチャ[0] と テクスチャ[1] を入れ替える
		LPDIRECT3DSURFACE9 pRenderWk;
		LPDIRECT3DTEXTURE9 pTextureWk;

		pRenderWk = m_apRenderMT[0];
		m_apRenderMT[0] = m_apRenderMT[1];
		m_apRenderMT[1] = pRenderWk;

		pTextureWk = m_apTextureMT[0];
		m_apTextureMT[0] = m_apTextureMT[1];
		m_apTextureMT[1] = pTextureWk;

		//描画終了
		m_pD3DDevice->EndScene();

#ifdef _DEBUG
		
		//FPSの表示
		DrawFPS();

#endif // _DEBUG
	}
	//バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//========================================
// レンダリングターゲットの変更
//========================================
void CRenderer::ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU)
{
	D3DXMATRIX mtxView, mtxProjection;
	float fAspect;

	// レンダリングターゲットを生成したテクスチャに設定
	m_pD3DDevice->SetRenderTarget(0, m_apRenderMT[0]);

	// Zバッファを生成したZバッファに設定
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

	// テクスチャレンダリング用のビューポートを設定
	m_pD3DDevice->SetViewport(&m_viewportMT);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&mtxView,
		&posV,		/*視点*/
		&posR,		/*注視点*/
		&vecU);		/*上方向ベクトル*/

	// ビューマトリックスの設定
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &mtxView);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&mtxProjection,
		D3DXToRadian(45.0f),							/* 視野角 */
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		/*画面のアスペクト比*/
		10.0f,											/*Z値の最小値*/
		2000.0f);										/*Z値の最大値*/

	// プロジェクションマトリックスの設定
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}

//========================================
//	テクスチャレンダリングの取得
//========================================
LPDIRECT3DTEXTURE9 CRenderer::GetTextureMT(void)
{
	return m_apTextureMT[0];
}

//========================================
// FPS処理
//========================================
void CRenderer::DrawFPS(void)
{
	//テキストの描画処理
	RECT rect = { 0,230,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[521];

	//文字列に代入
	sprintf(&aStr[0], "FPS:%d\n", GetFps());

	//テキストの描画
	m_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}