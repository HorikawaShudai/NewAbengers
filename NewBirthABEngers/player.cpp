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
	// 値をクリア
	m_state = STATE_NONE;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}

//===============================================
// コンストラクタ（オーバーロード）
//===============================================
CPlayer::CPlayer(int nPriority) : CObject2D(nPriority)
{
	// 値をクリア
	m_state = STATE_NONE;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
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
	// 状態を初期化
	m_state = STATE_NONE;

	// テクスチャの設定
	m_nIdxTexture = CManager::GetTexture()->Regist("data\\TEXTURE\\Player.png");

	// オブジェクト2Dの初期化処理
	CObject2D::Init(D3DXVECTOR3(150.0f, 600.0f, 0.0f));

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CPlayer::Uninit(void)
{
	// オブジェクト2Dの終了処理
	CObject2D::Uninit();
}

//===============================================
// 更新処理
//===============================================
void CPlayer::Update(void)
{
	if (CManager::GetKeyboardInput()->GetRelease(DIK_SPACE) == true)
	{
		m_state = STATE_KICK;	// 状態を変更
	}

	if (m_nPatternAnim <= 4)
	{// 総パターン数を超えてない
		if ((m_nCounterAnim % 10) == 0)
		{// カウンターが設定した速さの数値に達した
			m_nCounterAnim = 0;		// カウンターを初期値に戻す

			if (m_state == STATE_NONE)
			{
				CObject2D::UpdateAnim(m_nPatternAnim, 0);
			}
			else if (m_state == STATE_KICK)
			{
				CObject2D::UpdateAnim(m_nPatternAnim, 1);
			}

			m_nPatternAnim++;     // パターンNo.を更新する
		}

		m_nCounterAnim++;   // カウンターを加算
	}
	else if(m_nPatternAnim > 4)
	{
		if (m_state == STATE_KICK)
		{
			m_state = STATE_NONE;		// 走っている状態に戻す
		}

		m_nPatternAnim = 0;		// パターン数を戻す
		m_nCounterAnim = 0;
	}
}

//===============================================
// 描画処理
//===============================================
void CPlayer::Draw(void)
{
	// オブジェクト2Dの描画処理
	CObject2D::Draw();
}