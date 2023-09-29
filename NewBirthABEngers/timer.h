
//-===============================================
//-
//-	時間の処理のヘッダー[timer.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _TIMER_H_		// このマクロが定義されなかったら
#define _TIMER_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

//-======================================
//-	マクロ定義
//-======================================

#define SECOND_DIGITS	(3)		// 秒の桁数
#define COMMA_DIGITS	(2)		// コンマ秒の桁数

//===============================================
// 前方宣言
//===============================================

class CNumber;

//-======================================
//-	クラス定義
//-======================================

class CTimer
{
public:

	CTimer();
	~CTimer();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTimer *Create(void);

	void SetData(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 intervalValue, D3DXVECTOR3 intervalDigits);

private:

	void Add(void);
	void NumberTex(void);

	void SetNumber(void);

	D3DXVECTOR3 m_pos;				// 位置
	D3DXVECTOR3 m_size;				// 大きさ
	D3DXVECTOR3 m_intervalValue;	// 値の間隔
	D3DXVECTOR3 m_intervalDigits;	// 桁の間隔

	int m_nSecond;			// 秒数
	int m_nCommaSecond;		// コンマ秒

	int m_nCntTime;			// 時間のカウント
	
	CNumber *m_apSecondNumber[SECOND_DIGITS];	// 秒の数字のポインタ
	CNumber *m_apCommaNumber[COMMA_DIGITS];		// コンマ秒の数字のポインタ

};

#endif	// 二重インクルード防止の終了
