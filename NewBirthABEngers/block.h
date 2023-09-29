//=========================================================
//
// ブロック処理 [block.h]
// Author = 阿部翔大郎
//
//=========================================================
#ifndef _BLOCK_H_     // このマクロ定義がされてなかったら
#define _BLOCK_H_     // 2重インクルード防止のマクロ定義する

#include "main.h"
#include "object2D.h"

//===============================================
// マクロ定義
//===============================================
#define BLOCK_SIZEX		(40)					// 幅（半分）
#define BLOCK_SIZEY		(40)					// 高さ（半分）
#define MOVE_GRAVITY	(0.75f)					// 重力
#define MOVE_LIFTING	(-20.85f)				// リフティング時の移動量
#define LIFTING_POWER	(0.2f)					// 蹴る強さ
#define MAX_POWER		(-29.0f)				// 最大リフティング力

//===============================================
// ブロッククラス
//===============================================
class CBlock : public CObject2D
{
public:		//誰でもアクセス可能[アクセス指定子]
	CBlock();						// デフォルトコンストラクタ
	CBlock(int nPriority = 5);		// オーバーロードされたコンストラクタ
	~CBlock();						// デストラクタ

	static CBlock *Create(int nPriority = 5);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:	//自分のみアクセス可能[アクセス指定子]
	static int m_nIdxTexture;		// 使用するテクスチャの番号
	float m_fPower;					// 蹴る強さ
	bool m_bLifting;				// リフティングができるか
};

#endif