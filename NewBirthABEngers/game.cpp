//=========================================================
//
// ゲーム画面処理 [game.cpp]
// Author = 阿部翔大郎
//
//=========================================================
#include "game.h"
#include "object3D.h"
#include "objectX.h"
#include "pause.h"
#include "input.h"
#include "renderer.h"
#include "fade.h"
#include "sound.h"
#include "player.h"
#include "ball.h"
#include "bg.h"
#include "ground.h"
#include "timer.h"
#include "block.h"

//===============================================
// 静的メンバ変数
//===============================================
CObject3D *CGame::m_pObject3D = NULL;		// オブジェクト3Dクラスのポインタ
CPause *CGame::m_pPause = NULL;				// ポーズクラスのポインタ
CPlayer *CGame::m_pPlayer = NULL;			// プレイヤークラスのポインタ
CBall *CGame::m_pBall = NULL;				// ボールクラスのポインタ
CBg *CGame::m_pBg = NULL;					// 背景のポインタ
CGround *CGame::m_pGround = NULL;			// 地面のポインタ
CTimer *CGame::m_pTimer = NULL;				// 時間のポインタ
CBlock *CGame::m_pBlock = NULL;				// ブロックのポインタ

bool CGame::m_bPause = false;				// ポーズ状態
bool CGame::m_bStateReady = false;			// GAMSESTATE_READYかどうか

//===============================================
// コンストラクタ
//===============================================
CGame::CGame() : CScene()
{
	// 値のクリア
	m_state = STATE_NONE;
	m_nCounterState = 0;
	m_nTimeCounter = 0;
}

//===============================================
// デストラクタ
//===============================================
CGame::~CGame()
{
	
}

//===============================================
// 初期化処理
//===============================================
HRESULT CGame::Init(HWND hWnd)
{
	m_bPause = false;
	m_bStateReady = true;		// 待機状態にする

	// プレイヤーの生成
	m_pPlayer = CPlayer::Create();

	// ボールの生成
	m_pBall = CBall::Create();

	// ポーズの生成
	m_pPause = CPause::Create(6);

	// 通常状態に設定
	m_state = STATE_NORMAL;
	m_nCounterState = 0;

	// 背景の生成
	m_pBg = CBg::Create(CBg::TEX_GAME, 1);

	// 背景スクロール
	m_pBg->SetData(
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		D3DXVECTOR2(0.001f, 0.0f));

	// 背景の生成
	m_pGround = CGround::Create(CGround::TEX_GROUND_000, 2);

	// 背景スクロール
	m_pGround->SetData(
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.9f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.1f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		D3DXVECTOR2(0.001f, 0.0f));

	// 時間の生成
	m_pTimer = m_pTimer->Create();

	// 時間の設定処理
	m_pTimer->SetData(
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.1f, 0.0f),
		D3DXVECTOR3(50.0f, 50.0f, 0.0f),
		D3DXVECTOR3(100.0f, 0.0f, 0.0f),
		D3DXVECTOR3(100.0f, 0.0f, 0.0f));

	// サウンドの再生
	CManager::GetSound()->Play(CSound::LABEL_BGM_GAME);

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CGame::Uninit(void)
{
	// ポーズの終了処理
	m_pPause->Uninit();
	delete m_pPause;
	m_pPause = NULL;

	// 全てのオブジェクトの破棄
	CObject::ReleaseAll();
}

//===============================================
// 更新処理
//===============================================
void CGame::Update(void)
{
	m_nTimeCounter++;	// 時間をカウント

	if (CManager::GetKeyboardInput()->GetTrigger(DIK_P) == true
		|| CManager::GetInputGamePad()->GetTrigger(CInputGamePad::BUTTON_START, 0) == true)
	{// ポーズ入力
		m_bPause = m_bPause ? false : true;		// ポーズ状態切り替え

		if (m_bPause == true)
		{
			// サウンドの再生
			CManager::GetSound()->Play(CSound::LABEL_SE_PAUSE);
		}
		else
		{
			// サウンドの再生
			CManager::GetSound()->Play(CSound::LABEL_SE_PAUSE_CANCEL);
		}
	}

//#if _DEBUG
	if (CManager::GetKeyboardInput()->GetTrigger(DIK_BACKSPACE) == true
		|| CManager::GetInputGamePad()->GetTrigger(CInputGamePad::BUTTON_BACK, 0) == true)
	{// BackSpace
		CRenderer::GetFade()->Set(CScene::MODE_RESULT);		// リザルト画面へ移動
	}
//#endif

	srand(timeGetTime());	// randの値を初期化
	int nTypeRand = 0;		// randの値

	if ((m_nTimeCounter % 30) == 0)
	{// 一定時間経過
		nTypeRand = rand() % 8;		// randの値を取得

		if (nTypeRand == 1)
		{
			// ブロックの生成
			m_pBlock = CBlock::Create();
		}
	}

	if (m_bStateReady == false)
	{// 待機状態じゃない
		if (m_bPause == false)
		{// ポーズ状態じゃない

		}
	}
	else if (m_bStateReady == true)
	{// 待機状態のフラグが立っている
		if (m_state == STATE_NORMAL)
		{
			// 待機状態へ切り替える
			m_state = STATE_READY;
			m_nCounterState = TIME_STATEREADY;
		}
	}

	if (m_bPause == true)
	{// ポーズ状態
		// ポーズの更新処理
		m_pPause->Update();
	}

	switch (m_state)
	{
	case STATE_NORMAL:  // 通常状態
		m_nCounterState--;
		break;

	case STATE_READY:	// 開始待機状態
		if (m_bPause == false)
		{// ポーズ状態じゃない
			m_nCounterState--;

			if (m_nCounterState <= 0)
			{
				m_state = STATE_NORMAL;				// 通常状態に設定
				m_bStateReady = false;
			}
		}
		break;

	case STATE_END:     // 終了状態
		if (m_bPause == false)
		{// ポーズ状態じゃない
			m_nCounterState--;

			if (m_nCounterState <= 0)
			{
				m_state = STATE_NONE;  // 何もしていない状態に設定
			}
		}
		break;
	}

	if (m_pTimer != NULL)
	{
		m_pTimer->Update();
	}
}

//===============================================
// 描画処理
//===============================================
void CGame::Draw(void)
{
	
}

//===============================================
// ポーズ状態の設定
//===============================================
void CGame::SetEnablePause(const bool bPause)
{
	m_bPause = bPause;
}