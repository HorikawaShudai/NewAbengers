//=========================================================
//
// ボール処理 [ball.cpp]
// Author = 阿部翔大郎
//
//=========================================================
#include "ball.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "texture.h"
#include "debugproc.h"

//===============================================
// 静的メンバ変数
//===============================================
int CBall::m_nIdxTexture = NULL;		// 使用するテクスチャの番号

//===============================================
// コンストラクタ
//===============================================
CBall::CBall() : CObject2D(5)
{
	// 値をクリア
	m_fPower = 0.0f;
	m_bLifting = false;
	m_bDeath = false;
}

//===============================================
// コンストラクタ（オーバーロード）
//===============================================
CBall::CBall(int nPriority) : CObject2D(nPriority)
{
	// 値をクリア
	m_fPower = 0.0f;
	m_bLifting = false;
	m_bDeath = false;
}

//===============================================
// デストラクタ
//===============================================
CBall::~CBall()
{

}

//===============================================
// 生成処理
//===============================================
CBall *CBall::Create(int nPriority)
{
	CBall *pBall;

	//敵の生成
	pBall = new CBall(nPriority);

	//種類の設定
	pBall->SetType(TYPE_BALL);

	// サイズの設定
	pBall->SetSize(BALL_SIZEX, BALL_SIZEY);

	//初期化処理
	pBall->Init();

	//テクスチャの割り当て
	pBall->BindTexture(m_nIdxTexture);

	return pBall;
}

//===============================================
// 初期化処理
//===============================================
HRESULT CBall::Init(void)
{
	// テクスチャの設定
	m_nIdxTexture = CManager::GetTexture()->Regist("");

	// オブジェクト2Dの初期化処理
	CObject2D::Init(D3DXVECTOR3(200.0f, 400.0f, 0.0f));

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CBall::Uninit(void)
{
	// オブジェクト2Dの終了処理
	CObject2D::Uninit();
}

//===============================================
// 更新処理
//===============================================
void CBall::Update(void)
{
	// 蹴る強さ変更
	if (CManager::GetKeyboardInput()->GetPress(DIK_SPACE) == true)
	{
		m_fPower -= LIFTING_POWER;

		if (m_fPower <= MAX_POWER)
		{// 強さの上限を超えたら戻す
			m_fPower = MAX_POWER;
		}
	}

	if (CollisionObj(TYPE_PLAYER) == true)
	{// オブジェクトの範囲内
		// リフティング
		if (CManager::GetKeyboardInput()->GetRelease(DIK_SPACE) == true && m_bLifting == false)
		{
			m_move.y = m_fPower;
			m_bLifting = true;
		}
	}
	else if (CollisionObj(TYPE_BLOCK) == true)
	{// 障害物に接触
		m_bDeath = true;	// 死亡フラグ
	}

	if (CManager::GetKeyboardInput()->GetPress(DIK_SPACE) == false)
	{
		m_fPower = MOVE_LIFTING;
	}

	// 位置を更新
	CObject2D::SetPos(D3DXVECTOR3(m_pos.x, m_pos.y += m_move.y, 0.0f));

	// 重力処理
	m_move.y += MOVE_GRAVITY;

	// デバッグ表示
	CManager::GetDebugProc()->Print(" 蹴る強さ：%f\n", m_fPower);

}

//===============================================
// 描画処理
//===============================================
void CBall::Draw(void)
{
	// オブジェクト2Dの描画処理
	CObject2D::Draw();
}

//===============================================
// オブジェクトとの当たり判定
//===============================================
bool CBall::CollisionObj(const CObject::TYPE type)
{
	bool bLand = false;

	for (int nCntPriorityObj = 0; nCntPriorityObj < PRIORITY_MAX; nCntPriorityObj++)
	{
		CObject *pObj = CObject::GetTop(nCntPriorityObj);	// 先頭のオブジェクトへのポインタを取得

		while (pObj != NULL)
		{// 使用されている
			CObject *pObjNext = pObj->GetNext();	// 次のオブジェクトへのポインタを取得
			CObject::TYPE typeObj = pObj->GetType();			// 種類を取得

			if (typeObj == type)
			{// 種類が設定されたものと同じ場合
				D3DXVECTOR3 posObj = pObj->GetPos();		// 位置を取得
				D3DXVECTOR3 posOldObj = pObj->GetPosOld();	// 前回の位置を取得
				D3DXVECTOR3 sizeObj = pObj->GetSize();		// サイズを取得

				for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
				{
					CObject *pBall = CObject::GetTop(nCntPriority);	// 先頭のオブジェクトへのポインタを取得

					while (pBall != NULL)
					{// 使用されている
						CObject *pBallNext = pBall->GetNext();				// 次のオブジェクトへのポインタを取得
						CObject::TYPE typeBall = pBall->GetType();			// 種類を取得

						if (typeBall == TYPE_BALL)
						{// 種類が設定されたものと同じ場合
							D3DXVECTOR3 posBall = pBall->GetPos();			// 位置を取得
							D3DXVECTOR3 posOldBall = pBall->GetPosOld();	// 前回の位置を取得

							if (posBall.x >= posObj.x - BALL_SIZEX - sizeObj.x
								&& posBall.x <= posObj.x + BALL_SIZEX + sizeObj.x
								&& posBall.y <= posObj.y + BALL_SIZEY + sizeObj.y
								&& posBall.y >= posObj.y - BALL_SIZEY)
							{//	現在の位置がオブジェクトの範囲内
								return true;
							}
							else
							{
								m_bLifting = false;	// リフティングを可能にする
								return false;
							}
						}
						pBall = pBallNext;		// 次のオブジェクトを代入
					}
				}
			}
			pObj = pObjNext;		// 次のオブジェクトを代入
		}
	}

	return bLand;
}