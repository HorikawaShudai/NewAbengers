//=========================================================
//
// カメラ処理 [camera.cpp]
// Author = 阿部翔大郎
//
//=========================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "game.h"
#include "debugproc.h"

//===============================================
// マクロ定義
//===============================================
#define MOVE_CAMERA			(2.0f)		// 移動量
#define RAD_CAMERA			(60.0f)		// 基本軸からの回転角度
#define SLANTING			(0.25f)		// 斜めの角度
#define MOVE_X				(0.5f)		// X方向への移動
#define PI_SLASH			(100.0f)	// IPを割る数
#define LENGTH_CAMERA		(-300.0f)	// 視点の距離
#define HIGHT_CAMERA		(250.0f)	// カメラの高さ
#define MOVEV_MINUS			(0.3f)		// 視点の移動量の減衰
#define MOVER_MINUS			(0.2f)		// 注視点の移動量の減衰
#define POSR_DEST			(-300.0f)	// 注視点の少し前に設定
#define CAMERA_ROT_SPEED	(0.7f)		// カメラがプレイヤーの背後に回り込むまでのスピード
#define CAMERA_ROT_MOVE		(70)		// 向きが変わるタイミング
#define POS_DIFF			(0.15f)		// 位置の値の補正
#define MAPVIEW_TIME		(80)		// 上空カメラになっている時間

//===============================================
// コンストラクタ
//===============================================
CCamera::CCamera()
{
	// 値のクリア
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nViewMapCounter = 0;
	m_bMapCamera = false;
}

//===============================================
// デストラクタ
//===============================================
CCamera::~CCamera()
{
	
}

//===============================================
// 初期化処理
//===============================================
HRESULT CCamera::Init(void)
{
	// 値を初期化
	m_posV = D3DXVECTOR3(-2500.0f, 7400.0f, -1800.0f);
	m_posR = D3DXVECTOR3(-2500.0f, 0.0f, -2500.0f);

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CCamera::Uninit(void)
{
	
}

//===============================================
// 更新処理
//===============================================
void CCamera::Update(void)
{

}

//===============================================
// 設定処理
//===============================================
void CCamera::Set(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		8000.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
						&m_posV,
						&m_posR,
						&m_vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}