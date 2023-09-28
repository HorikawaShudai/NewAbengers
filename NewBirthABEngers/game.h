//=========================================================
//
// ゲーム画面処理 [game.h]
// Author = 阿部翔大郎
//
//=========================================================
#ifndef _GAME_H_     // このマクロ定義がされてなかったら
#define _GAME_H_     // 2重インクルード防止のマクロ定義する

#include "manager.h"

//===============================================
// マクロ定義
//===============================================
#define TIME_STATEREADY		(120)	// 待機状態へ画面が切り替わるまでの余韻

//===============================================
// 前方宣言
//===============================================
class CObjectX;
class CObject3D;
class CPause;

//===============================================
// ゲーム画面クラス
//===============================================
class CGame : public CScene
{
public:		// 誰でもアクセス可能 [アクセス指定子]
	CGame();						// デフォルトコンストラクタ
	~CGame();						// デストラクタ

	// ゲームの状態
	enum STATE
	{
		STATE_NONE = 0,	// 何もしていない状態
		STATE_READY,	// 開始待機状態
		STATE_NORMAL,	// 通常状態
		STATE_END,		// 終了状態
		STAET_MAX
	};

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObject3D *GetObject3D() { return m_pObject3D; }
	static CPause *GetPause() { return m_pPause; }

	static void SetEnablePause(const bool bPause);
	static bool GetPauseState(void) { return m_bPause; }
	static bool GetStateReady(void) { return m_bStateReady; }

	STATE GetState(void) { return m_state; }

private:	// 自分のみアクセス可能 [アクセス指定子]
	static CObject3D *m_pObject3D;					// オブジェクト3Dクラスのポインタ
	static CPause *m_pPause;						// ポーズクラスのポインタ

	static bool m_bStateReady;		// GAMSESTATE_READYかどうか
	static bool m_bPause;			// 現在のポーズの状態
	STATE m_state;					// ゲームの状態
	int m_nCounterState;			// 状態管理カウンター
};

#endif