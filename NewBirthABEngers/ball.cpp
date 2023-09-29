//=========================================================
//
// ボール処理 [ball.cpp]
// Author = 阿部翔大郎
//
//=========================================================
#include "ball.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "texture.h"

//===============================================
// 静的メンバ変数
//===============================================
int CBall::m_nIdxTexture = NULL;		// 使用するテクスチャの番号

//===============================================
// コンストラクタ
//===============================================
CBall::CBall() : CObject2D(5)
{

}

//===============================================
// コンストラクタ（オーバーロード）
//===============================================
CBall::CBall(int nPriority) : CObject2D(nPriority)
{

}

//===============================================
// デストラクタ
//===============================================
CBall::~CBall()
{

}

//===============================================
// 生成処理
//===============================================
CBall *CBall::Create(int nPriority)
{
	CBall *pBall;

	//敵の生成
	pBall = new CBall(nPriority);

	//種類の設定
	pBall->SetType(TYPE_BULLET);

	// サイズの設定
	pBall->SetSize(BALL_SIZEX, BALL_SIZEY);

	//初期化処理
	pBall->Init();

	//テクスチャの割り当て
	pBall->BindTexture(m_nIdxTexture);

	return pBall;
}

//===============================================
// 初期化処理
//===============================================
HRESULT CBall::Init(void)
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
void CBall::Uninit(void)
{
	// オブジェクト2Dの終了処理
	CObject2D::Uninit();
}

//===============================================
// 更新処理
//===============================================
void CBall::Update(void)
{
	// リフティング
	if (CManager::GetKeyboardInput()->GetPress(DIK_SPACE) == true)
	{
		m_move.y = MOVE_LIFTING;
	}

	// 位置を更新
	CObject2D::SetPos(D3DXVECTOR3(m_pos.x, m_pos.y += m_move.y, 0.0f));

	// 重力処理
	m_move.y += MOVE_GRAVITY;
}

//===============================================
// 描画処理
//===============================================
void CBall::Draw(void)
{
	// オブジェクト2Dの描画処理
	CObject2D::Draw();
}