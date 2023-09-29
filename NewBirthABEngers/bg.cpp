//=========================================================
//
// 背景処理 [bg.cpp]
// Author = 酒井南勝
//
//=========================================================

#include "bg.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//===============================================
// マクロ定義
//===============================================
#define SIZE_X				(285.0f)		// 横サイズ
#define SIZE_Y				(90.0f)			// 縦サイズ
#define TIME_PROGRESS		(240)			// 進捗移行時間
#define TIME_PROGRESSTART	(1200)			// 進捗移行開始時間

//===============================================
// 静的メンバ変数
//===============================================

int CBg::m_aIdxTexture[TEX_MAX] = {};				// 使用するテクスチャの番号

//===============================================
// テクスチャファイル名
//===============================================
const char *CBg::m_apTextureData[TEX_MAX] =
{
	{ "data\\TEXTURE\\GameBg000.png" },		// ゲーム
	{ "data\\TEXTURE\\TitleBg000.png" },	// タイトル
	{ "data\\TEXTURE\\ResultBg000.png" },	// リザルト
	{ "data\\TEXTURE\\TutorialBg000.png" },	// チュートリアル
};

//===============================================
// コンストラクタ
//===============================================
CBg::CBg() : CObject2D(5)
{
	// 値のクリア
	m_nTypeTex = 0;

	m_texPos = D3DXVECTOR2(0.0f, 0.0f);
	m_texMove = D3DXVECTOR2(0.0f, 0.0f);
}

//===============================================
// コンストラクタ（オーバーロード）
//===============================================
CBg::CBg(int nPriority) : CObject2D(nPriority)
{
	// 値のクリア
	m_nTypeTex = 0;

	m_texPos = D3DXVECTOR2(0.0f, 0.0f);
	m_texMove = D3DXVECTOR2(0.0f, 0.0f);
}

//===============================================
// デストラクタ
//===============================================
CBg::~CBg()
{

}

//===============================================
// 生成処理
//===============================================
CBg *CBg::Create(int nTex, int nPriority)
{
	CBg *pBg;

	// 背景の生成
	pBg = new CBg(nPriority);

	// 種類の設定
	pBg->SetType(TYPE_BULLET);

	// サイズの設定
	pBg->SetSize(SIZE_X, SIZE_Y);

	// 初期化処理
	pBg->Init(D3DXVECTOR3(650.0f, 600.0f, 0.0f), nTex, nPriority);

	// 設定処理
	pBg->Set(nTex);

	return pBg;
}

//===============================================
// 初期化処理
//===============================================
HRESULT CBg::Init(D3DXVECTOR3 pos, int nTex, int nPriority)
{
	// オブジェクト2Dの初期化処理
	CObject2D::Init(pos);

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CBg::Uninit(void)
{
	// オブジェクト2Dの終了処理
	CObject2D::Uninit();
}

//===============================================
// 更新処理
//===============================================
void CBg::Update(void)
{
	// テクスチャの加算処理
	m_texPos += m_texMove;

	// テクスチャ位置の補正
	DestTexPos();

	// 頂点情報の設定
	SetVtx();
}

//===============================================
// 描画処理
//===============================================
void CBg::Draw(void)
{
	 // オブジェクト2Dの描画処理
	CObject2D::Draw();
}

//===============================================
// 設定処理
//===============================================
void CBg::Set(const int nType)
{
	m_nTypeTex = nType;

	// テクスチャの設定
	m_aIdxTexture[m_nTypeTex] = CManager::GetTexture()->Regist(m_apTextureData[m_nTypeTex]);

	// テクスチャの割り当て
	CObject2D::BindTexture(m_aIdxTexture[m_nTypeTex]);
}

//===============================================
// 値の設定処理
//===============================================
void CBg::SetData(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color, D3DXVECTOR2 texMove)
{
	m_pos = pos;
	m_size = size;
	m_color = color;

	m_texMove = texMove;

	// 頂点情報の設定
	SetVtx();
}

//-------------------------------------
//- 背景の頂点情報設定
//-------------------------------------
void CBg::SetVtx(void)
{
	// 頂点バッファの取得
	LPDIRECT3DVERTEXBUFFER9 vtxBuff = GetVtxBuff();

	// 頂点バッファ取得成功の有無を判定
	if (vtxBuff == NULL)
	{// 失敗時

	 // 頂点情報設定を抜ける
		return;
	}

	// 2D頂点情報のポインタを宣言
	VERTEX_2D *pVtx = NULL;

	// 頂点バッファをロックし、頂点情報のポインタを取得
	vtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	// 頂点座標を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーを設定
	pVtx[0].col = m_color;
	pVtx[1].col = m_color;
	pVtx[2].col = m_color;
	pVtx[3].col = m_color;

	// テクスチャの座標を設定
	pVtx[0].tex = D3DXVECTOR2(
		0.0f + m_texPos.x,
		0.0f + m_texPos.y);

	pVtx[1].tex = D3DXVECTOR2(
		1.0f + m_texPos.x,
		0.0f + m_texPos.y);

	pVtx[2].tex = D3DXVECTOR2(
		0.0f + m_texPos.x,
		1.0f + m_texPos.y);

	pVtx[3].tex = D3DXVECTOR2(
		1.0f + m_texPos.x,
		1.0f + m_texPos.y);

	// 頂点バッファをアンロックする
	vtxBuff->Unlock();
}

//-------------------------------------
//- 背景のテクスチャ座標の補正
//-------------------------------------
void CBg::DestTexPos(void)
{
	// 横のテクスチャ位置の判定
	if (m_texPos.x > 1.0f)
	{
		// 1.0fを超えた場合0.0fにする
		m_texPos.x = 0.0f;
	}
	else if (m_texPos.x < 0.0f)
	{
		// 0.0fを下回った場合1.0fにする
		m_texPos.x = 1.0f;
	}

	// 縦のテクスチャ位置の判定
	if (m_texPos.y > 1.0f)
	{
		// 1.0fを超えた場合0.0fにする
		m_texPos.y = 0.0f;
	}
	else if (m_texPos.y < 0.0f)
	{
		// 0.0fを下回った場合1.0fにする
		m_texPos.y = 1.0f;
	}
}

