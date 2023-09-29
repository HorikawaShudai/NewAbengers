//=========================================================
//
// �v���C���[���� [player.cpp]
// Author = �����đ�Y
//
//=========================================================
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "sound.h"
#include "texture.h"

//===============================================
// �ÓI�����o�ϐ�
//===============================================
int CPlayer::m_nIdxTexture = NULL;		// �g�p����e�N�X�`���̔ԍ�

//===============================================
// �R���X�g���N�^
//===============================================
CPlayer::CPlayer() : CObject2D(5)
{

}

//===============================================
// �R���X�g���N�^�i�I�[�o�[���[�h�j
//===============================================
CPlayer::CPlayer(int nPriority) : CObject2D(nPriority)
{

}

//===============================================
// �f�X�g���N�^
//===============================================
CPlayer::~CPlayer()
{

}

//===============================================
// ��������
//===============================================
CPlayer *CPlayer::Create(int nPriority)
{
	CPlayer *pPlayer;

	//�G�̐���
	pPlayer = new CPlayer(nPriority);

	//��ނ̐ݒ�
	pPlayer->SetType(TYPE_PLAYER);

	// �T�C�Y�̐ݒ�
	pPlayer->SetSize(PLAYER_SIZEX, PLAYER_SIZEY);

	//����������
	pPlayer->Init();

	//�e�N�X�`���̊��蓖��
	pPlayer->BindTexture(m_nIdxTexture);

	return pPlayer;
}

//===============================================
// ����������
//===============================================
HRESULT CPlayer::Init(void)
{
	// �e�N�X�`���̐ݒ�
	m_nIdxTexture = CManager::GetTexture()->Regist("");

	// �I�u�W�F�N�g2D�̏���������
	CObject2D::Init(D3DXVECTOR3(150.0f, 600.0f, 0.0f));

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CPlayer::Uninit(void)
{
	CObject2D::Uninit();
}

//===============================================
// �X�V����
//===============================================
void CPlayer::Update(void)
{
	
}

//===============================================
// �`�揈��
//===============================================
void CPlayer::Draw(void)
{
	CObject2D::Draw();
}