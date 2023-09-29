
//=========================================================
//
// 背景処理 [bg.h]
// Author = 酒井南勝
//
//=========================================================
#ifndef _BG_H_     // このマクロ定義がされてなかったら
#define _BG_H_     // 2重インクルード防止のマクロ定義する

#include "object2D.h"

//===============================================
// マクロ定義
//===============================================

//===============================================
// 背景クラス
//===============================================
class CBg : public CObject2D
{
public:		// 誰でもアクセス可能 [アクセス指定子]
	CBg();					// デフォルトコンストラクタ
	CBg(int nPriority = 5);	// オーバーロードされたコンストラクタ
	~CBg();					// デストラクタ

	// 背景のテクスチャ
	enum TEX
	{
		TEX_GAME = 0,	// ゲーム
		TEX_TITLE,		// タイトル
		TEX_RESULT,		// リザルト
		TEX_TUTORIAL,	// チュートリアル
		TEX_MAX
	};

	static CBg *Create(int nTex, int nPriority = 3);

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