//=========================================================
//
// タイトル画面処理 [title.cpp]
// Author = 阿部翔大郎
//
//=========================================================
#include "title.h"
#include "input.h"
#include "renderer.h"
#include "fade.h"
#include "sound.h"
#include "manager.h"

#include "bg.h"

//===============================================
// マクロ定義
//===============================================
#define TIME_FADERANKING		(800)			// 自動フェード時間

//===============================================
// 静的メンバ変数
//===============================================

CBg *CTitle::m_pBg = NULL;

//===============================================
// コンストラクタ
//===============================================
CTitle::CTitle() : CScene()
{
	// 値のクリア
	m_nTimeFade = 0;
	m_bFade = false;
}

//===============================================
// デストラクタ
//===============================================
CTitle::~CTitle()
{
	
}

//===============================================
// 初期化処理
//===============================================
HRESULT CTitle::Init(HWND hWnd)
{
	// 背景の生成
	m_pBg = CBg::Create(CBg::TEX_TITLE,6);

	// 背景スクロール
	m_pBg->SetData(
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),
		D3DXVECTOR2(0.0f,0.0f));

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CTitle::Uninit(void)
{
	// 全てのオブジェクトの破棄
	CObject::ReleaseAll();
}

//===============================================
// 更新処理
//===============================================
void CTitle::Update(void)
{
	m_nTimeFade++;		// 時間をカウント

	if (/*m_pLogo->GetEndAnim() == true &&*/ (CManager::GetKeyboardInput()->GetTrigger(DIK_RETURN) == true
		|| CManager::GetInputGamePad()->GetTrigger(CInputGamePad::BUTTON_A, 0) == true))
	{
		if (m_bFade == false)
		{// フェードバグ防止
			CRenderer::GetFade()->Set(CScene::MODE_TUTORIAL);	// ゲーム画面へ移行
			m_bFade = true;

			//// 点滅設定
			//m_pPressEnter->SetBrightnessFade(true);

			// サウンドの再生
			CManager::GetSound()->Play(CSound::LABEL_SE_TITLE_ENTER);
		}
	}
	else if(m_nTimeFade > TIME_FADERANKING)
	{// 一定時間経過
		if (m_bFade == false)
		{// フェードバグ防止
			CRenderer::GetFade()->Set(CScene::MODE_RESULT);	// ランキング画面へ移行
			m_bFade = true;
		}
	}
}

//===============================================
// 描画処理
//===============================================
void CTitle::Draw(void)
{
	
}