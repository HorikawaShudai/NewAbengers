//=========================================================
//
// ゲージ処理 [uigage.cpp]
// Author = 阿部翔大郎
//
//=========================================================
#include "gage.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "object2D.h"
#include "input.h"

//===============================================
// マクロ定義
//===============================================
#define SIZE_X				(50.0f)			// 横サイズ
#define SIZE_Y				(100.0f)			// 縦サイズ
#define POSITION_X			(50.0f)			// 位置X
#define POSITION_Y			(600.0f)			// 位置Y

#define SIZE_REGULATION		(0.05f)					// サイズ調整

//===============================================
// 静的メンバ変数
//===============================================
CObject2D *CUiGage::m_apObject2D[TEX_MAX];				// オブジェクト2Dクラスのポインタ
const char *CUiGage::m_apTextureData[TEX_MAX] = {};		// テクスチャファイル名
int CUiGage::m_aIdxTexture[TEX_MAX] = {};				// 使用するテクスチャの番号

//===============================================
// コンストラクタ
//===============================================
CUiGage::CUiGage()
{
	// 値のクリア
	m_fTexU = 0.0f;
	m_fTexV = 0.0f;
	m_nGarbage = 0;
	m_fMoveShake = 0.0f;
	m_bVMoveShake = false;
}

//===============================================
// コンストラクタ（オーバーロード）
//===============================================
CUiGage::CUiGage(int nPriority)
{
	// 値のクリア
	m_fTexU = 0.0f;
	m_fTexV = 0.0f;
	m_nGarbage = 0;
	m_fMoveShake = 0.0f;
	m_bVMoveShake = false;
}

//===============================================
// デストラクタ
//===============================================
CUiGage::~CUiGage()
{
	
}

//===============================================
// 生成処理
//===============================================
CUiGage *CUiGage::Create(int nPriority)
{
	CUiGage *pUi;

	// 背景の生成
	pUi = new CUiGage(nPriority);

	// 初期化処理
	pUi->Init(D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f), nPriority);

	return pUi;
}

//===============================================
// 初期化処理
//===============================================
HRESULT CUiGage::Init(D3DXVECTOR3 pos, int nPriority)
{
	// テクスチャファイル名
	const char *m_apTextureData[TEX_MAX] =
	{
		{ "data\\TEXTURE\\key_bar.png" },	// 外側
		{ "data\\TEXTURE\\kick_bar.png" }	// 内側
	};

	for (int nCntObj = 0; nCntObj < TEX_MAX; nCntObj++)
	{
		m_apObject2D[nCntObj] = new CObject2D(nPriority);

		// サイズ設定
		m_apObject2D[nCntObj]->SetSize(SIZE_X, SIZE_Y);

		// オブジェクト2Dの初期化処理
		m_apObject2D[nCntObj]->Init(pos);

		// テクスチャの設定
		m_aIdxTexture[nCntObj] = CManager::GetTexture()->Regist(m_apTextureData[nCntObj]);

		// テクスチャの割り当て
		m_apObject2D[nCntObj]->BindTexture(m_aIdxTexture[nCntObj]);
	}

	// テクスチャ座標の更新処理
	m_apObject2D[TEX_INSIDE]->UpdateTex(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CUiGage::Uninit(void)
{
	
}

//===============================================
// 更新処理
//===============================================
void CUiGage::Update(void)
{
	if (CManager::GetKeyboardInput()->GetPress(DIK_SPACE) == true)
	{// 1キー
		// 設定処理
		Set(AMOUNT_OF_RISE_NORMAL);
	}
	else if (CManager::GetKeyboardInput()->GetRelease(DIK_SPACE) == true)
	{// 1キー
	 // 設定処理
		Set(-20);
	}


	if (m_nGarbage >= 20)
	{// ゲージが最大値になった
		// 振動処理
		//Vibration(MOVE_SHAKE, MAX_MOVESHAKE);
	}
	else
	{
		// 位置をリセット
		m_apObject2D[TEX_OUTSIDE]->SetPos(D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f));
		m_apObject2D[TEX_INSIDE]->UpdatePos(D3DXVECTOR3(POSITION_X, 700.0f - m_nGarbage * SIZE_REGULATION * SIZE_Y, 0.0f), SIZE_X, m_nGarbage * SIZE_REGULATION * SIZE_Y);
	}
}

//===============================================
// 描画処理
//===============================================
void CUiGage::Draw(void)
{
	if (m_nGarbage >= 20)
	{// ゴミの量が最大
		// 色の更新処理（赤）
		m_apObject2D[TEX_INSIDE]->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else
	{
		// 色の更新処理（白）
		m_apObject2D[TEX_INSIDE]->SetCol(D3DXCOLOR(m_nGarbage * SIZE_REGULATION, 1.0f - m_nGarbage * SIZE_REGULATION * 0.5f, 1.0f - m_nGarbage * SIZE_REGULATION, 1.0f));
	}
}

//===============================================
// 振動処理
//===============================================
void CUiGage::Vibration(float fMove, float fMaxMove)
{
	if (m_bVMoveShake == false)
	{
		m_fMoveShake += fMove;		// 移動量を加算

		if (m_fMoveShake >= fMaxMove)
		{// 一定の位置まで動いたら
			m_bVMoveShake = true;	// 移動の向き切り替え
		}
	}
	else
	{
		m_fMoveShake -= fMove;		// 移動量を減算

		if (m_fMoveShake <= 0)
		{// 一定の位置まで動いたら
			m_bVMoveShake = false;	// 移動の向き切り替え
		}
	}

	// オブジェクト2Dの位置の設定処理
	m_apObject2D[TEX_INSIDE]->UpdatePos(D3DXVECTOR3(POSITION_X + m_fMoveShake, 700.0f - m_nGarbage * SIZE_REGULATION * SIZE_Y, 0.0f), SIZE_X, m_nGarbage * SIZE_REGULATION * SIZE_Y);
	m_apObject2D[TEX_OUTSIDE]->SetPos(D3DXVECTOR3(POSITION_X + m_fMoveShake, POSITION_Y, 0.0f));
}

//===============================================
// 設定処理
//===============================================
void CUiGage::Set(int fGarbage)
{
	m_nGarbage += fGarbage;

	if (m_nGarbage > 20)
	{// 最大量を超えた
		m_nGarbage = 20;
	}
	else if (m_nGarbage < 0)
	{// 最少量を超えた
		m_nGarbage = 0;
	}
	
	// 位置の更新処理
	m_apObject2D[TEX_INSIDE]->UpdatePos(D3DXVECTOR3(POSITION_X, 700.0f - m_nGarbage * SIZE_REGULATION * SIZE_Y, 0.0f), SIZE_X, m_nGarbage * SIZE_REGULATION * SIZE_Y);

	// テクスチャ座標の更新処理
	m_apObject2D[TEX_INSIDE]->UpdateTex(0.0f, 0.0f, 1.0f, 1.0f, m_nGarbage * SIZE_REGULATION, 0.0f);
}