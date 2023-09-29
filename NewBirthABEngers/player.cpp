//=========================================================
//
// プレイヤー処理 [player.cpp]
// Author = 阿部翔大郎
//
//=========================================================
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "sound.h"
#include "texture.h"

//===============================================
// 静的メンバ変数
//===============================================
int CPlayer::m_nIdxTexture = NULL;		// 使用するテクスチャの番号

//===============================================
// コンストラクタ
//===============================================
CPlayer::CPlayer() : CObject2D(5)
{

}

//===============================================
// コンストラクタ（オーバーロード）
//===============================================
CPlayer::CPlayer(int nPriority) : CObject2D(nPriority)
{

}

//===============================================
// デストラクタ
//===============================================
CPlayer::~CPlayer()
{

}

//===============================================
// 生成処理
//===============================================
CPlayer *CPlayer::Create(int nPriority)
{
	CPlayer *pPlayer;

	//敵の生成
	pPlayer = new CPlayer(nPriority);

	//種類の設定
	pPlayer->SetType(TYPE_PLAYER);

	// サイズの設定
	pPlayer->SetSize(PLAYER_SIZEX, PLAYER_SIZEY);

	//初期化処理
	pPlayer->Init();

	//テクスチャの割り当て
	pPlayer->BindTexture(m_nIdxTexture);

	return pPlayer;
}

//===============================================
// 初期化処理
//===============================================
HRESULT CPlayer::Init(void)
{
	// テクスチャの設定
	m_nIdxTexture = CManager::GetTexture()->Regist("");

	// オブジェクト2Dの初期化処理
	CObject2D::Init(D3DXVECTOR3(150.0f, 600.0f, 0.0f));

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CPlayer::Uninit(void)
{
	CObject2D::Uninit();
}

//===============================================
// 更新処理
//===============================================
void CPlayer::Update(void)
{
	
}

//===============================================
// 描画処理
//===============================================
void CPlayer::Draw(void)
{
	CObject2D::Draw();
}