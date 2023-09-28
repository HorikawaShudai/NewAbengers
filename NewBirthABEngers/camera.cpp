//=========================================================
//
// �J�������� [camera.cpp]
// Author = �����đ�Y
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
// �}�N����`
//===============================================
#define MOVE_CAMERA			(2.0f)		// �ړ���
#define RAD_CAMERA			(60.0f)		// ��{������̉�]�p�x
#define SLANTING			(0.25f)		// �΂߂̊p�x
#define MOVE_X				(0.5f)		// X�����ւ̈ړ�
#define PI_SLASH			(100.0f)	// IP�����鐔
#define LENGTH_CAMERA		(-300.0f)	// ���_�̋���
#define HIGHT_CAMERA		(250.0f)	// �J�����̍���
#define MOVEV_MINUS			(0.3f)		// ���_�̈ړ��ʂ̌���
#define MOVER_MINUS			(0.2f)		// �����_�̈ړ��ʂ̌���
#define POSR_DEST			(-300.0f)	// �����_�̏����O�ɐݒ�
#define CAMERA_ROT_SPEED	(0.7f)		// �J�������v���C���[�̔w��ɉ�荞�ނ܂ł̃X�s�[�h
#define CAMERA_ROT_MOVE		(70)		// �������ς��^�C�~���O
#define POS_DIFF			(0.15f)		// �ʒu�̒l�̕␳
#define MAPVIEW_TIME		(80)		// ���J�����ɂȂ��Ă��鎞��

//===============================================
// �R���X�g���N�^
//===============================================
CCamera::CCamera()
{
	// �l�̃N���A
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nViewMapCounter = 0;
	m_bMapCamera = false;
}

//===============================================
// �f�X�g���N�^
//===============================================
CCamera::~CCamera()
{
	
}

//===============================================
// ����������
//===============================================
HRESULT CCamera::Init(void)
{
	// �l��������
	m_posV = D3DXVECTOR3(-2500.0f, 7400.0f, -1800.0f);
	m_posR = D3DXVECTOR3(-2500.0f, 0.0f, -2500.0f);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CCamera::Uninit(void)
{
	
}

//===============================================
// �X�V����
//===============================================
void CCamera::Update(void)
{

}

//===============================================
// �ݒ菈��
//===============================================
void CCamera::Set(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		8000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
						&m_posV,
						&m_posR,
						&m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}