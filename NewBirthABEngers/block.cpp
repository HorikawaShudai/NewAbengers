//=========================================================
//
// ブロック処理 [block.cpp]
// Author = 阿部翔大郎
//
//=========================================================
#include "block.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "texture.h"

//===============================================
// 静的メンバ変数
//===============================================
int CBlock::m_nIdxTexture = NULL;		// 使用するテクスチャの番号

//===============================================
// コンストラクタ
//===============================================
CBlock::CBlock() : CObject2D(5)
{
	// 値をクリア
	m_fPower = 0.0f;
	m_bLifting = false;
}

//===============================================
// コンストラクタ（オーバーロード）
//===============================================
CBlock::CBlock(int nPriority) : CObject2D(nPriority)
{
	// 値をクリア
	m_fPower = 0.0f;
	m_bLifting = false;
}

//===============================================
// デストラクタ
//===============================================
CBlock::~CBlock()
{

}

//===============================================
// 生成処理
//===============================================
CBlock *CBlock::Create(int nPriority)
{
	CBlock *pBall;

	//敵の生成
	pBall = new CBlock(nPriority);

	//種類の設定
	pBall->SetType(TYPE_BLOCK);

	// サイズの設定
	pBall->SetSize(BLOCK_SIZEX, BLOCK_SIZEY);

	//初期化処理
	pBall->Init();

	//テクスチャの割り当て
	pBall->BindTexture(m_nIdxTexture);

	return pBall;
}

//===============================================
// 初期化処理
//===============================================
HRESULT CBlock::Init(void)
{
	// テクスチャの設定
	m_nIdxTexture = CManager::GetTexture()->Regist("");

	// オブジェクト2Dの初期化処理
	CObject2D::Init(D3DXVECTOR3(200.0f, 400.0f, 0.0f));

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CBlock::Uninit(void)
{
	// オブジェクト2Dの終了処理
	CObject2D::Uninit();
}

//===============================================
// 更新処理
//===============================================
void CBlock::Update(void)
{
	// 位置を更新
	CObject2D::SetPos(D3DXVECTOR3(m_pos.x += 0.01f, m_pos.y, 0.0f));

	if (CObject2D::GetPos().x <= -BLOCK_SIZEX)
	{
		// 終了処理
		Uninit();
	}
}

//===============================================
// 描画処理
//===============================================
void CBlock::Draw(void)
{
	// オブジェクト2Dの描画処理
	CObject2D::Draw();
}