
//=========================================================
//
// 背景処理 [ground.h]
// Author = 酒井南勝
//
//=========================================================
#ifndef _GROUND_H_     // このマクロ定義がされてなかったら
#define _GROUND_H_     // 2重インクルード防止のマクロ定義する

#include "object2D.h"

//===============================================
// マクロ定義
//===============================================

//===============================================
// 背景クラス
//===============================================
class CGround : public CObject2D
{
public:		// 誰でもアクセス可能 [アクセス指定子]
	CGround();					// デフォルトコンストラクタ
	CGround(int nPriority = 5);	// オーバーロードされたコンストラクタ
	~CGround();					// デストラクタ

	// 背景のテクスチャ
	enum TEX
	{
		TEX_GROUND_000 = 0,	// 地面000
		TEX_MAX
	};

	static CGround *Create(int nTex, int nPriority = 3);

	HRESULT Init(D3DXVECTOR3 pos, int nTex, int nPriority);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(const int nType);

	void SetData(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color, D3DXVECTOR2 texMove);

	void SetVtx(void);

	void DestTexPos(void);

private:	// 自分のみアクセス可能 [アクセス指定子]
	static const char *m_apTextureData[TEX_MAX];	// テクスチャファイル名
	static int m_aIdxTexture[TEX_MAX];				// 使用するテクスチャの番号

	int m_nTypeTex;									// テクスチャの種類

	D3DXVECTOR3 m_size;								// サイズ
	D3DXCOLOR m_color;								// 色

	D3DXVECTOR2 m_texPos;							// テクスチャの位置
	D3DXVECTOR2 m_texMove;							// テクスチャの移動量
};

#endif