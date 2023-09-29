
//================================================
//=
//=	タイマー処理[timer.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "timer.h"

#include "renderer.h"

#include "number.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	静的変数宣言
//=======================================

//-------------------------------------
//-	タイマーのコンストラクタ
//-------------------------------------
CTimer::CTimer()
{
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_intervalValue = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_intervalDigits = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nSecond = 0;
	m_nCommaSecond = 0;

	m_nCntTime = 0;

	// 値のクリア
	for (int nCount = 0; nCount < SECOND_DIGITS; nCount++)
	{
		m_apSecondNumber[nCount] = NULL;
	}

	for (int nCount = 0; nCount < COMMA_DIGITS; nCount++)
	{
		m_apCommaNumber[nCount] = NULL;
	}
}

//-------------------------------------
//-	タイマーのデストラクタ
//-------------------------------------
CTimer::~CTimer()
{

}

//-------------------------------------
//- タイマーの初期化処理
//-------------------------------------
HRESULT CTimer::Init(void)
{
	// 値のクリア
	for (int nCount = 0; nCount < SECOND_DIGITS; nCount++)
	{
		if (m_apSecondNumber[nCount] == NULL)
		{
			m_apSecondNumber[nCount] = CNumber::Create(CNumber::TEX_GOLD_000, 7);

			if (m_apSecondNumber[nCount] == NULL)
			{
				return E_FAIL;
			}
		}
		else
		{
			return E_FAIL;
		}
	}

	for (int nCount = 0; nCount < COMMA_DIGITS; nCount++)
	{
		if (m_apCommaNumber[nCount] == NULL)
		{
			m_apCommaNumber[nCount] = CNumber::Create(CNumber::TEX_GOLD_000, 7);

			if (m_apCommaNumber[nCount] == NULL)
			{
				return E_FAIL;
			}
		}
		else
		{
			return E_FAIL;
		}
	}


	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- タイマーの終了処理
//-------------------------------------
void CTimer::Uninit(void)
{
	for (int nCount = 0; nCount < SECOND_DIGITS; nCount++)
	{
		if (m_apSecondNumber[nCount] != NULL)
		{
			// 数字の初期化
			m_apSecondNumber[nCount] = NULL;
		}
	}

	for (int nCount = 0; nCount < COMMA_DIGITS; nCount++)
	{
		if (m_apCommaNumber[nCount] != NULL)
		{
			// 数字の初期化
			m_apCommaNumber[nCount] = NULL;
		}
	}
}

//-------------------------------------
//- タイマーの更新処理
//-------------------------------------
void CTimer::Update(void)
{
	// 加算処理
	Add();

	// テクスチャの桁ごと設定処理
	NumberTex();
}

//-------------------------------------
//- タイマーの描画処理
//-------------------------------------
void CTimer::Draw(void)
{

}

//-------------------------------------
//- タイマーの生成処理
//-------------------------------------
CTimer *CTimer::Create(void)
{
	// タイマーの生成
	CTimer *pTimer = DBG_NEW CTimer;

	// 生成の成功の有無を判定
	if (pTimer != NULL)
	{
		// 初期化処理
		if (FAILED(pTimer->Init()))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pTimer == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	return pTimer;
}

//-------------------------------------
//-	タイマーの値設定処理
//-------------------------------------
void CTimer::SetData(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 intervalValue, D3DXVECTOR3 intervalDigits)
{
	m_pos = pos;
	m_size = size;
	m_intervalValue = intervalValue;
	m_intervalDigits = intervalDigits;

	// 数字の設定処理
	SetNumber();
}

//-------------------------------------
//-	タイマーの時間経過処理
//-------------------------------------
void CTimer::Add(void)
{
	// 時間カウントの加算
	m_nCntTime++;
}

//-------------------------------------
//-	タイマーの桁ごとテクスチャの設定処理
//-------------------------------------
void CTimer::NumberTex(void)
{
	// 変数宣言
	int nDigitsScond[SECOND_DIGITS];	// 秒数の桁を格納
	int nDigitsComma[COMMA_DIGITS];		// コンマ秒数の桁を格納

	m_nSecond = (m_nCntTime / 60);
	m_nCommaSecond = (int)((m_nCntTime % 60) * 1.2f);

	// 桁ごとの数値を代入
	nDigitsScond[0] = ((m_nSecond % 1000) / 100);
	nDigitsScond[1] = ((m_nSecond % 100) / 10);
	nDigitsScond[2] = ((m_nSecond % 10));

	nDigitsComma[0] = ((m_nCommaSecond % 100) / 10);
	nDigitsComma[1] = (m_nCommaSecond % 10);

	for (int nCount = 0; nCount < SECOND_DIGITS; nCount++)
	{
		// 数字の設定処理
		m_apSecondNumber[nCount]->SetValue(nDigitsScond[nCount]);
	}

	for (int nCount = 0; nCount < COMMA_DIGITS; nCount++)
	{
		// 数字の設定処理
		m_apCommaNumber[nCount]->SetValue(nDigitsComma[nCount]);
	}
}

//-------------------------------------
//- タイマーの位置情報の設定
//-------------------------------------
void CTimer::SetNumber(void)
{
	for (int nCount = 0; nCount < SECOND_DIGITS; nCount++)
	{
		// 数字の有無を判定
		if (m_apSecondNumber[nCount] != NULL)
		{
			// 数字の位置情報を代入
			m_apSecondNumber[nCount]->SetData(
				D3DXVECTOR3(
				m_pos.x + (m_intervalValue.x * nCount),
				m_pos.y + (m_intervalValue.y * nCount),
				m_pos.z + (m_intervalValue.z * nCount)),
				m_size,
				D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
		}
	}

	for (int nCount = 0; nCount < COMMA_DIGITS; nCount++)
	{
		// 数字の有無を判定
		if (m_apCommaNumber[nCount] != NULL)
		{
			// 数字の位置情報を代入
			m_apSecondNumber[nCount]->SetData(
				D3DXVECTOR3(
					m_pos.x + (m_intervalValue.x * nCount) + m_intervalDigits.x,
					m_pos.y + (m_intervalValue.y * nCount) + m_intervalDigits.y,
					m_pos.z + (m_intervalValue.z * nCount) + m_intervalDigits.z),
				m_size,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
		}
	}
}