
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
// 数字クラス
//===============================================
class CNumber : public CObject2D
{
public:		// 誰でもアクセス可能 [アクセス指定子]
	CNumber();					// デフォルトコンストラクタ
	CNumber(int nPriority = 5);	// オーバーロードされたコンストラクタ
	~CNumber();					// デストラクタ

	// 数字のテクスチャ
	enum TEX
	{
		TEX_GOLD_000 = 0,	// 金文字000
		TEX_MAX
	};

	static CNumber *Create(int nTex, int nPriority = 3);

	HRESULT Init(D3DXVECTOR3 pos, int nTex, int nPriority);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(const int nType);

	void SetData(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);

	void SetValue(int nValue);

private:	// 自分のみアクセス可能 [アクセス指定子]

	void SetVtx(void);

	static const char *m_apTextureData[TEX_MAX];	// テクスチャファイル名
	static int m_aIdxTexture[TEX_MAX];				// 使用するテクスチャの番号

	int m_nTypeTex;									// テクスチャの種類

	D3DXVECTOR3 m_size;								// サイズ
	D3DXCOLOR m_color;								// 色
	int m_nValue;									// 数値
};

#endif
