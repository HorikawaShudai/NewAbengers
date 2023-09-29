
//=========================================================
//
// 酒井の数字処理 [number_sakai.cpp]
// Author = 酒井南勝
//
//=========================================================

#include "number_sakai.h"

#include "manager.h"
#include "renderer.h"
#include "texture.h"

//===============================================
// マクロ定義
//===============================================

//===============================================
// 静的メンバ変数
//===============================================

int CNumberSakai::m_aIdxTexture[TEX_MAX] = {};				// 使用するテクスチャの番号

//===============================================
// テクスチャファイル名
//===============================================
const char *CNumberSakai::m_apTextureData[TEX_MAX] =
{
	{ "data\\TEXTURE\\number_000.png" },		// ゲーム
};

//===============================================
// コンストラクタ
//===============================================
CNumberSakai::CNumberSakai() : CObject2D(5)
{
	// 値のクリア
	m_nTypeTex = 0;

	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	m_nValue = 0;
}

//===============================================
// コンストラクタ（オーバーロード）
//===============================================
CNumberSakai::CNumberSakai(int nPriority) : CObject2D(nPriority)
{
	// 値のクリア
	m_nTypeTex = 0;

	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	m_nValue = 0;
}

//===============================================
// デストラクタ
//===============================================
CNumberSakai::~CNumberSakai()
{

}

//===============================================
// 生成処理
//===============================================
CNumberSakai *CNumberSakai::Create(int nTex, int nPriority)
{
	CNumberSakai *pBg;

	// 背景の生成
	pBg = new CNumberSakai(nPriority);

	// 種類の設定
	pBg->SetType(TYPE_BULLET);

	// サイズの設定
	pBg->SetSize(0.0f, 0.0f);

	// 初期化処理
	pBg->Init(D3DXVECTOR3(650.0f, 600.0f, 0.0f), nTex, nPriority);

	// 設定処理
	pBg->Set(nTex);

	return pBg;
}

//===============================================
// 初期化処理
//===============================================
HRESULT CNumberSakai::Init(D3DXVECTOR3 pos, int nTex, int nPriority)
{
	// オブジェクト2Dの初期化処理
	CObject2D::Init(pos);

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CNumberSakai::Uninit(void)
{
	// オブジェクト2Dの終了処理
	CObject2D::Uninit();
}

//===============================================
// 更新処理
//===============================================
void CNumberSakai::Update(void)
{
	// 頂点情報の設定
	SetVtx();
}

//===============================================
// 描画処理
//===============================================
void CNumberSakai::Draw(void)
{
	// オブジェクト2Dの描画処理
	CObject2D::Draw();
}

//===============================================
// 設定処理
//===============================================
void CNumberSakai::Set(const int nType)
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
void CNumberSakai::SetData(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	m_pos = pos;
	m_size = size;
	m_color = color;

	// 頂点情報の設定
	SetVtx();
}

//-------------------------------------
//- 数字の値を設定処理
//-------------------------------------
void CNumberSakai::SetValue(int nValue)
{
	m_nValue = nValue;
}

//-------------------------------------
//- 数字の頂点情報設定
//-------------------------------------
void CNumberSakai::SetVtx(void)
{
	// 頂点バッファをポインタを宣言
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
	pVtx[0].tex = D3DXVECTOR2(0.1f * (m_nValue + 0), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f * (m_nValue + 1), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f * (m_nValue + 0), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f * (m_nValue + 1), 1.0f);

	// 頂点バッファをアンロックする
	vtxBuff->Unlock();
}

