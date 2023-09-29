//=========================================================
//
// �Q�[�W���� [uigage.cpp]
// Author = �����đ�Y
//
//=========================================================
#include "gage.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "object2D.h"
#include "input.h"

//===============================================
// �}�N����`
//===============================================
#define SIZE_X				(50.0f)			// ���T�C�Y
#define SIZE_Y				(100.0f)			// �c�T�C�Y
#define POSITION_X			(50.0f)			// �ʒuX
#define POSITION_Y			(600.0f)			// �ʒuY

#define SIZE_REGULATION		(0.05f)					// �T�C�Y����

//===============================================
// �ÓI�����o�ϐ�
//===============================================
CObject2D *CUiGage::m_apObject2D[TEX_MAX];				// �I�u�W�F�N�g2D�N���X�̃|�C���^
const char *CUiGage::m_apTextureData[TEX_MAX] = {};		// �e�N�X�`���t�@�C����
int CUiGage::m_aIdxTexture[TEX_MAX] = {};				// �g�p����e�N�X�`���̔ԍ�

//===============================================
// �R���X�g���N�^
//===============================================
CUiGage::CUiGage()
{
	// �l�̃N���A
	m_fTexU = 0.0f;
	m_fTexV = 0.0f;
	m_nGarbage = 0;
	m_fMoveShake = 0.0f;
	m_bVMoveShake = false;
}

//===============================================
// �R���X�g���N�^�i�I�[�o�[���[�h�j
//===============================================
CUiGage::CUiGage(int nPriority)
{
	// �l�̃N���A
	m_fTexU = 0.0f;
	m_fTexV = 0.0f;
	m_nGarbage = 0;
	m_fMoveShake = 0.0f;
	m_bVMoveShake = false;
}

//===============================================
// �f�X�g���N�^
//===============================================
CUiGage::~CUiGage()
{
	
}

//===============================================
// ��������
//===============================================
CUiGage *CUiGage::Create(int nPriority)
{
	CUiGage *pUi;

	// �w�i�̐���
	pUi = new CUiGage(nPriority);

	// ����������
	pUi->Init(D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f), nPriority);

	return pUi;
}

//===============================================
// ����������
//===============================================
HRESULT CUiGage::Init(D3DXVECTOR3 pos, int nPriority)
{
	// �e�N�X�`���t�@�C����
	const char *m_apTextureData[TEX_MAX] =
	{
		{ "data\\TEXTURE\\key_bar.png" },	// �O��
		{ "data\\TEXTURE\\kick_bar.png" }	// ����
	};

	for (int nCntObj = 0; nCntObj < TEX_MAX; nCntObj++)
	{
		m_apObject2D[nCntObj] = new CObject2D(nPriority);

		// �T�C�Y�ݒ�
		m_apObject2D[nCntObj]->SetSize(SIZE_X, SIZE_Y);

		// �I�u�W�F�N�g2D�̏���������
		m_apObject2D[nCntObj]->Init(pos);

		// �e�N�X�`���̐ݒ�
		m_aIdxTexture[nCntObj] = CManager::GetTexture()->Regist(m_apTextureData[nCntObj]);

		// �e�N�X�`���̊��蓖��
		m_apObject2D[nCntObj]->BindTexture(m_aIdxTexture[nCntObj]);
	}

	// �e�N�X�`�����W�̍X�V����
	m_apObject2D[TEX_INSIDE]->UpdateTex(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CUiGage::Uninit(void)
{
	
}

//===============================================
// �X�V����
//===============================================
void CUiGage::Update(void)
{
	if (CManager::GetKeyboardInput()->GetPress(DIK_SPACE) == true)
	{// 1�L�[
		// �ݒ菈��
		Set(AMOUNT_OF_RISE_NORMAL);
	}
	else if (CManager::GetKeyboardInput()->GetRelease(DIK_SPACE) == true)
	{// 1�L�[
	 // �ݒ菈��
		Set(-20);
	}


	if (m_nGarbage >= 20)
	{// �Q�[�W���ő�l�ɂȂ���
		// �U������
		//Vibration(MOVE_SHAKE, MAX_MOVESHAKE);
	}
	else
	{
		// �ʒu�����Z�b�g
		m_apObject2D[TEX_OUTSIDE]->SetPos(D3DXVECTOR3(POSITION_X, POSITION_Y, 0.0f));
		m_apObject2D[TEX_INSIDE]->UpdatePos(D3DXVECTOR3(POSITION_X, 700.0f - m_nGarbage * SIZE_REGULATION * SIZE_Y, 0.0f), SIZE_X, m_nGarbage * SIZE_REGULATION * SIZE_Y);
	}
}

//===============================================
// �`�揈��
//===============================================
void CUiGage::Draw(void)
{
	if (m_nGarbage >= 20)
	{// �S�~�̗ʂ��ő�
		// �F�̍X�V�����i�ԁj
		m_apObject2D[TEX_INSIDE]->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else
	{
		// �F�̍X�V�����i���j
		m_apObject2D[TEX_INSIDE]->SetCol(D3DXCOLOR(m_nGarbage * SIZE_REGULATION, 1.0f - m_nGarbage * SIZE_REGULATION * 0.5f, 1.0f - m_nGarbage * SIZE_REGULATION, 1.0f));
	}
}

//===============================================
// �U������
//===============================================
void CUiGage::Vibration(float fMove, float fMaxMove)
{
	if (m_bVMoveShake == false)
	{
		m_fMoveShake += fMove;		// �ړ��ʂ����Z

		if (m_fMoveShake >= fMaxMove)
		{// ���̈ʒu�܂œ�������
			m_bVMoveShake = true;	// �ړ��̌����؂�ւ�
		}
	}
	else
	{
		m_fMoveShake -= fMove;		// �ړ��ʂ����Z

		if (m_fMoveShake <= 0)
		{// ���̈ʒu�܂œ�������
			m_bVMoveShake = false;	// �ړ��̌����؂�ւ�
		}
	}

	// �I�u�W�F�N�g2D�̈ʒu�̐ݒ菈��
	m_apObject2D[TEX_INSIDE]->UpdatePos(D3DXVECTOR3(POSITION_X + m_fMoveShake, 700.0f - m_nGarbage * SIZE_REGULATION * SIZE_Y, 0.0f), SIZE_X, m_nGarbage * SIZE_REGULATION * SIZE_Y);
	m_apObject2D[TEX_OUTSIDE]->SetPos(D3DXVECTOR3(POSITION_X + m_fMoveShake, POSITION_Y, 0.0f));
}

//===============================================
// �ݒ菈��
//===============================================
void CUiGage::Set(int fGarbage)
{
	m_nGarbage += fGarbage;

	if (m_nGarbage > 20)
	{// �ő�ʂ𒴂���
		m_nGarbage = 20;
	}
	else if (m_nGarbage < 0)
	{// �ŏ��ʂ𒴂���
		m_nGarbage = 0;
	}
	
	// �ʒu�̍X�V����
	m_apObject2D[TEX_INSIDE]->UpdatePos(D3DXVECTOR3(POSITION_X, 700.0f - m_nGarbage * SIZE_REGULATION * SIZE_Y, 0.0f), SIZE_X, m_nGarbage * SIZE_REGULATION * SIZE_Y);

	// �e�N�X�`�����W�̍X�V����
	m_apObject2D[TEX_INSIDE]->UpdateTex(0.0f, 0.0f, 1.0f, 1.0f, m_nGarbage * SIZE_REGULATION, 0.0f);
}