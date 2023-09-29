//=========================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author = �����đ�Y
//
//=========================================================
#include "title.h"
#include "input.h"
#include "renderer.h"
#include "fade.h"
#include "sound.h"
#include "manager.h"

#include "bg.h"

//===============================================
// �}�N����`
//===============================================
#define TIME_FADERANKING		(800)			// �����t�F�[�h����

//===============================================
// �ÓI�����o�ϐ�
//===============================================

CBg *CTitle::m_pBg = NULL;

//===============================================
// �R���X�g���N�^
//===============================================
CTitle::CTitle() : CScene()
{
	// �l�̃N���A
	m_nTimeFade = 0;
	m_bFade = false;
}

//===============================================
// �f�X�g���N�^
//===============================================
CTitle::~CTitle()
{
	
}

//===============================================
// ����������
//===============================================
HRESULT CTitle::Init(HWND hWnd)
{
	// �w�i�̐���
	m_pBg = CBg::Create(CBg::TEX_TITLE,6);

	// �w�i�X�N���[��
	m_pBg->SetData(
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),
		D3DXVECTOR2(0.0f,0.0f));

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CTitle::Uninit(void)
{
	// �S�ẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();
}

//===============================================
// �X�V����
//===============================================
void CTitle::Update(void)
{
	m_nTimeFade++;		// ���Ԃ��J�E���g

	if (/*m_pLogo->GetEndAnim() == true &&*/ (CManager::GetKeyboardInput()->GetTrigger(DIK_RETURN) == true
		|| CManager::GetInputGamePad()->GetTrigger(CInputGamePad::BUTTON_A, 0) == true))
	{
		if (m_bFade == false)
		{// �t�F�[�h�o�O�h�~
			CRenderer::GetFade()->Set(CScene::MODE_TUTORIAL);	// �Q�[����ʂֈڍs
			m_bFade = true;

			//// �_�Őݒ�
			//m_pPressEnter->SetBrightnessFade(true);

			// �T�E���h�̍Đ�
			CManager::GetSound()->Play(CSound::LABEL_SE_TITLE_ENTER);
		}
	}
	else if(m_nTimeFade > TIME_FADERANKING)
	{// ��莞�Ԍo��
		if (m_bFade == false)
		{// �t�F�[�h�o�O�h�~
			CRenderer::GetFade()->Set(CScene::MODE_RESULT);	// �����L���O��ʂֈڍs
			m_bFade = true;
		}
	}
}

//===============================================
// �`�揈��
//===============================================
void CTitle::Draw(void)
{
	
}