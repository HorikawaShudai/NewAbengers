//=========================================================
//
// チュートリアル画面処理 [tutorial.cpp]
// Author = 阿部翔大郎
//
//=========================================================
#include "tutorial.h"
#include "renderer.h"
#include "fade.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "bg.h"

//===============================================
// マクロ定義
//===============================================
#define FIRSTSET_FIELD			(10)			// 床の初期配置数
#define DISTANCE_FIELD			(-1000.0f)		// 床の配置間隔

#define TIME_CREATEFIELD		(116)			// 床の生成時間間隔
#define TIME_CREATEDUMPSTER		(1300)			// ゴミステーションの生成時間間隔
#define POS_CREATEOBJ			(-9120.0f)		// 生成位置間隔

//===============================================
// 静的メンバ変数
//===============================================

CBg *CTutorial::m_pBg = NULL;		// 背景のポインタ

//===============================================
// コンストラクタ
//===============================================
CTutorial::CTutorial() : CScene()
{
	// 値のクリア
	m_nTime = 0;
	m_bFade = false;
}

//===============================================
// デストラクタ
//===============================================
CTutorial::~CTutorial()
{
	
}

//===============================================
// 初期化処理
//===============================================
HRESULT CTutorial::Init(HWND hWnd)
{
	// 背景の生成
	m_pBg = CBg::Create(CBg::TEX_TUTORIAL, 1);

	// 背景スクロール
	m_pBg->SetData(
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		D3DXVECTOR2(0.0f, 0.0f));

	// サウンドの再生
	CManager::GetSound()->Play(CSound::LABEL_BGM_TUTORIAL);

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CTutorial::Uninit(void)
{
	// 全てのオブジェクトの破棄
	CObject::ReleaseAll();
}

//===============================================
// 更新処理
//===============================================
void CTutorial::Update(void)
{
	m_nTime++;	// 時間をカウント

	if (CManager::GetKeyboardInput()->GetTrigger(DIK_RETURN) == true
		|| CManager::GetInputGamePad()->GetTrigger(CInputGamePad::BUTTON_START, 0) == true)
	{
		if (m_bFade == false)
		{// フェードバグ防止
			CRenderer::GetFade()->Set(CScene::MODE_GAME);	// ゲーム画面へ移行
			m_bFade = true;
		}
	}
	else if (CManager::GetKeyboardInput()->GetTrigger(DIK_BACKSPACE) == true
		|| CManager::GetInputGamePad()->GetTrigger(CInputGamePad::BUTTON_BACK, 0) == true)
	{
		if (m_bFade == false)
		{// フェードバグ防止
			CRenderer::GetFade()->Set(CScene::MODE_TUTORIAL);	// チュートリアル画面へ移行
			m_bFade = true;
		}
	}
}

//===============================================
// 描画処理
//===============================================
void CTutorial::Draw(void)
{
	
}