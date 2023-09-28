//=========================================================
//
// ���U���g��ʏ��� [result.cpp]
// Author = �����đ�Y
//
//=========================================================
#include "result.h"
#include "input.h"
#include "renderer.h"
#include "fade.h"
#include "manager.h"

//===============================================
// �}�N����`
//===============================================
#define TIME_FADE		(600)			// �����t�F�[�h����

//===============================================
// �ÓI�����o�ϐ�
//===============================================
CBg *CResult::m_pBg = NULL;						// �w�i�N���X�̃|�C���^
CRanking *CResult::m_pRanking = NULL;			// �����L���O�N���X�̃|�C���^
CRankIn *CResult::m_pRankIn = NULL;				// �����N�C���N���X�̃|�C���^

//===============================================
// �R���X�g���N�^
//===============================================
CResult::CResult() : CScene()
{
	// �l�̃N���A
	m_nTimeFade = 0;
	m_bFade = false;
}

//===============================================
// �f�X�g���N�^
//===============================================
CResult::~CResult()
{
	
}

//===============================================
// ����������
//===============================================
HRESULT CResult::Init(HWND hWnd)
{
	//// �w�i�̐���
	//m_pBg = CBg::Create(CBg::TYPE_RESULT);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CResult::Uninit(void)
{
	//// �S�ẴI�u�W�F�N�g�̔j��
	//CObject::ReleaseAll();
}

//===============================================
// �X�V����
//===============================================
void CResult::Update(void)
{
	m_nTimeFade++;		// ���Ԃ��J�E���g

	if (CManager::GetKeyboardInput()->GetTrigger(DIK_RETURN) == true
		|| CManager::GetInputGamePad()->GetTrigger(CInputGamePad::BUTTON_A, 0) == true
		|| m_nTimeFade > TIME_FADE)
	{// ENTER���͂���莞�Ԍo��
		if (m_bFade == false)
		{// �t�F�[�h�o�O�h�~
			CRenderer::GetFade()->Set(CScene::MODE_TITLE);	// �Q�[���^�C�g����ʂֈڍs

			m_bFade = true;
		}
	}
}

//===============================================
// �`�揈��
//===============================================
void CResult::Draw(void)
{

}