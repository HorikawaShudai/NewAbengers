//=========================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author = �����đ�Y
//
//=========================================================
#include "game.h"
#include "object3D.h"
#include "objectX.h"
#include "pause.h"
#include "input.h"
#include "renderer.h"
#include "fade.h"
#include "sound.h"
#include "player.h"
#include "ball.h"
#include "bg.h"

//===============================================
// �ÓI�����o�ϐ�
//===============================================
CObject3D *CGame::m_pObject3D = NULL;					// �I�u�W�F�N�g3D�N���X�̃|�C���^
CPause *CGame::m_pPause = NULL;							// �|�[�Y�N���X�̃|�C���^
CPlayer *CGame::m_pPlayer = NULL;						// �v���C���[�N���X�̃|�C���^
CBall *CGame::m_pBall = NULL;							// �{�[���N���X�̃|�C���^
CBg *CGame::m_pBg = NULL;								// �w�i�̃|�C���^

bool CGame::m_bPause = false;				// �|�[�Y���
bool CGame::m_bStateReady = false;			// GAMSESTATE_READY���ǂ���

//===============================================
// �R���X�g���N�^
//===============================================
CGame::CGame() : CScene()
{
	// �l�̃N���A
	m_state = STATE_NONE;
	m_nCounterState = 0;
}

//===============================================
// �f�X�g���N�^
//===============================================
CGame::~CGame()
{
	
}

//===============================================
// ����������
//===============================================
HRESULT CGame::Init(HWND hWnd)
{
	m_bPause = false;
	m_bStateReady = true;		// �ҋ@��Ԃɂ���

	// �v���C���[�̐���
	m_pPlayer = CPlayer::Create();

	// �{�[���̐���
	m_pBall = CBall::Create();

	// �|�[�Y�̐���
	m_pPause = CPause::Create(6);

	// �ʏ��Ԃɐݒ�
	m_state = STATE_NORMAL;
	m_nCounterState = 0;

	// �w�i�̐���
	m_pBg = CBg::Create(CBg::TEX_GAME, 1);

	// �w�i�X�N���[��
	m_pBg->SetData(
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		D3DXVECTOR2(0.0001f, 0.0f));

	// �T�E���h�̍Đ�
	CManager::GetSound()->Play(CSound::LABEL_BGM_GAME);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CGame::Uninit(void)
{
	// �|�[�Y�̏I������
	m_pPause->Uninit();
	delete m_pPause;
	m_pPause = NULL;

	// �S�ẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();
}

//===============================================
// �X�V����
//===============================================
void CGame::Update(void)
{
	if (CManager::GetKeyboardInput()->GetTrigger(DIK_P) == true
		|| CManager::GetInputGamePad()->GetTrigger(CInputGamePad::BUTTON_START, 0) == true)
	{// �|�[�Y����
		m_bPause = m_bPause ? false : true;		// �|�[�Y��Ԑ؂�ւ�

		if (m_bPause == true)
		{
			// �T�E���h�̍Đ�
			CManager::GetSound()->Play(CSound::LABEL_SE_PAUSE);
		}
		else
		{
			// �T�E���h�̍Đ�
			CManager::GetSound()->Play(CSound::LABEL_SE_PAUSE_CANCEL);
		}
	}

//#if _DEBUG
	if (CManager::GetKeyboardInput()->GetTrigger(DIK_BACKSPACE) == true
		|| CManager::GetInputGamePad()->GetTrigger(CInputGamePad::BUTTON_BACK, 0) == true)
	{// BackSpace
		CRenderer::GetFade()->Set(CScene::MODE_RESULT);		// ���U���g��ʂֈړ�
	}
//#endif

	if (m_bStateReady == false)
	{// �ҋ@��Ԃ���Ȃ�
		if (m_bPause == false)
		{// �|�[�Y��Ԃ���Ȃ�

		}
	}
	else if (m_bStateReady == true)
	{// �ҋ@��Ԃ̃t���O�������Ă���
		if (m_state == STATE_NORMAL)
		{
			// �ҋ@��Ԃ֐؂�ւ���
			m_state = STATE_READY;
			m_nCounterState = TIME_STATEREADY;
		}
	}

	if (m_bPause == true)
	{// �|�[�Y���
		// �|�[�Y�̍X�V����
		m_pPause->Update();
	}

	switch (m_state)
	{
	case STATE_NORMAL:  // �ʏ���
		m_nCounterState--;
		break;

	case STATE_READY:	// �J�n�ҋ@���
		if (m_bPause == false)
		{// �|�[�Y��Ԃ���Ȃ�
			m_nCounterState--;

			if (m_nCounterState <= 0)
			{
				m_state = STATE_NORMAL;				// �ʏ��Ԃɐݒ�
				m_bStateReady = false;
			}
		}
		break;

	case STATE_END:     // �I�����
		if (m_bPause == false)
		{// �|�[�Y��Ԃ���Ȃ�
			m_nCounterState--;

			if (m_nCounterState <= 0)
			{
				m_state = STATE_NONE;  // �������Ă��Ȃ���Ԃɐݒ�
			}
		}
		break;
	}
}

//===============================================
// �`�揈��
//===============================================
void CGame::Draw(void)
{
	
}

//===============================================
// �|�[�Y��Ԃ̐ݒ�
//===============================================
void CGame::SetEnablePause(const bool bPause)
{
	m_bPause = bPause;
}