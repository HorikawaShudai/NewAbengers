//=========================================================
//
// プレイヤー処理 [player.h]
// Author = 阿部翔大郎
//
//=========================================================
#ifndef _PLAYER_H_     // このマクロ定義がされてなかったら
#define _PLAYER_H_     // 2重インクルード防止のマクロ定義する

#include "main.h"
#include "object2D.h"

//===============================================
// マクロ定義
//===============================================
#define PLAYER_SIZEX		(60)		// 幅（半分）
#define PLAYER_SIZEY		(90)		// 高さ（半分）

//===============================================
// プレイヤークラス
//===============================================
class CPlayer : public CObject2D
{
public:		//誰でもアクセス可能[アクセス指定子]

	// 状態
	enum STATE
	{
		STATE_NONE = 0,		//プレイヤー歩き状態
		STATE_KICK,			//プレイヤーキック状態
		STATE_MAX
	};

	CPlayer();						// デフォルトコンストラクタ
	CPlayer(int nPriority = 5);		// オーバーロードされたコンストラクタ
	~CPlayer();						// デストラクタ

	static CPlayer *Create(int nPriority = 5);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:	//自分のみアクセス可能[アクセス指定子]
	static int m_nIdxTexture;		// 使用するテクスチャの番号

	STATE m_state;		// 状態
	int m_nCounterAnim;			// アニメーションカウンター
	int m_nPatternAnim;			// アニメーションパターンNo.
};

#endif