//=========================================================
//
// �{�[������ [ball.cpp]
// Author = �����đ�Y
//
//=========================================================
#include "ball.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "texture.h"

//===============================================
// �ÓI�����o�ϐ�
//===============================================
int CBall::m_nIdxTexture = NULL;		// �g�p����e�N�X�`���̔ԍ�

//===============================================
// �R���X�g���N�^
//===============================================
CBall::CBall() : CObject2D(5)
{

}

//===============================================
// �R���X�g���N�^�i�I�[�o�[���[�h�j
//===============================================
CBall::CBall(int nPriority) : CObject2D(nPriority)
{

}

//===============================================
// �f�X�g���N�^
//===============================================
CBall::~CBall()
{

}

//===============================================
// ��������
//===============================================
CBall *CBall::Create(int nPriority)
{
	CBall *pBall;

	//�G�̐���
	pBall = new CBall(nPriority);

	//��ނ̐ݒ�
	pBall->SetType(TYPE_BULLET);

	// �T�C�Y�̐ݒ�
	pBall->SetSize(BALL_SIZEX, BALL_SIZEY);

	//����������
	pBall->Init();

	//�e�N�X�`���̊��蓖��
	pBall->BindTexture(m_nIdxTexture);

	return pBall;
}

//===============================================
// ����������
//===============================================
HRESULT CBall::Init(void)
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
void CBall::Uninit(void)
{
	// �I�u�W�F�N�g2D�̏I������
	CObject2D::Uninit();
}

//===============================================
// �X�V����
//===============================================
void CBall::Update(void)
{
	// ���t�e�B���O
	if (CManager::GetKeyboardInput()->GetPress(DIK_SPACE) == true)
	{
		m_move.y = MOVE_LIFTING;
	}

	// �ʒu���X�V
	CObject2D::SetPos(D3DXVECTOR3(m_pos.x, m_pos.y += m_move.y, 0.0f));

	// �d�͏���
	m_move.y += MOVE_GRAVITY;
}

//===============================================
// �`�揈��
//===============================================
void CBall::Draw(void)
{
	// �I�u�W�F�N�g2D�̕`�揈��
	CObject2D::Draw();
}