//=========================================================
//
// �u���b�N���� [block.cpp]
// Author = �����đ�Y
//
//=========================================================
#include "block.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "texture.h"

//===============================================
// �ÓI�����o�ϐ�
//===============================================
int CBlock::m_nIdxTexture = NULL;		// �g�p����e�N�X�`���̔ԍ�

//===============================================
// �R���X�g���N�^
//===============================================
CBlock::CBlock() : CObject2D(5)
{
	// �l���N���A
	m_fPower = 0.0f;
	m_bLifting = false;
}

//===============================================
// �R���X�g���N�^�i�I�[�o�[���[�h�j
//===============================================
CBlock::CBlock(int nPriority) : CObject2D(nPriority)
{
	// �l���N���A
	m_fPower = 0.0f;
	m_bLifting = false;
}

//===============================================
// �f�X�g���N�^
//===============================================
CBlock::~CBlock()
{

}

//===============================================
// ��������
//===============================================
CBlock *CBlock::Create(int nPriority)
{
	CBlock *pBall;

	//�G�̐���
	pBall = new CBlock(nPriority);

	//��ނ̐ݒ�
	pBall->SetType(TYPE_BLOCK);

	// �T�C�Y�̐ݒ�
	pBall->SetSize(BLOCK_SIZEX, BLOCK_SIZEY);

	//����������
	pBall->Init();

	//�e�N�X�`���̊��蓖��
	pBall->BindTexture(m_nIdxTexture);

	return pBall;
}

//===============================================
// ����������
//===============================================
HRESULT CBlock::Init(void)
{
	// �e�N�X�`���̐ݒ�
	m_nIdxTexture = CManager::GetTexture()->Regist("");

	// �I�u�W�F�N�g2D�̏���������
	CObject2D::Init(D3DXVECTOR3(200.0f, 400.0f, 0.0f));

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CBlock::Uninit(void)
{
	// �I�u�W�F�N�g2D�̏I������
	CObject2D::Uninit();
}

//===============================================
// �X�V����
//===============================================
void CBlock::Update(void)
{
	// �ʒu���X�V
	CObject2D::SetPos(D3DXVECTOR3(m_pos.x += 0.01f, m_pos.y, 0.0f));

	if (CObject2D::GetPos().x <= -BLOCK_SIZEX)
	{
		// �I������
		Uninit();
	}
}

//===============================================
// �`�揈��
//===============================================
void CBlock::Draw(void)
{
	// �I�u�W�F�N�g2D�̕`�揈��
	CObject2D::Draw();
}