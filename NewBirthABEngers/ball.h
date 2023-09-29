//=========================================================
//
// ボール処理 [ball.h]
// Author = 阿部翔大郎
//
//=========================================================
#ifndef _BALL_H_     // このマクロ定義がされてなかったら
#define _BALL_H_     // 2重インクルード防止のマクロ定義する

#include "main.h"
#include "object2D.h"

//===============================================
// マクロ定義
//===============================================
#define BALL_SIZEX		(40)					// 幅（半分）
#define BALL_SIZEY		(40)					// 高さ（半分）
#define MOVE_GRAVITY	(0.75f)					// 重力
#define MOVE_LIFTING	(-20.85f)				// リフティング時の移動量
#define LIFTING_POWER	(0.2f)					// 蹴る強さ
#define MAX_POWER		(-29.0f)				// 最大リフティング力

//===============================================
// ボールクラス
//===============================================
class CBall : public CObject2D
{
public:		//誰でもアクセス可能[アクセス指定子]
	CBall();						// デフォルトコンストラクタ
	CBall(int nPriority = 5);		// オーバーロードされたコンストラクタ
	~CBall();						// デストラクタ

	static CBall *Create(int nPriority = 5);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool CollisionObj(const CObject::TYPE type);
	bool GetDeath(void) { return m_bDeath; }

private:	//自分のみアクセス可能[アクセス指定子]
	static int m_nIdxTexture;		// 使用するテクスチャの番号
	float m_fPower;					// 蹴る強さ
	bool m_bLifting;				// リフティングができるか
	bool m_bDeath;					// 死亡フラグ
};

#endif