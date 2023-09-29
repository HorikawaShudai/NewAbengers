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
	// �l���N���A
	m_state = STATE_NONE;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}

//===============================================
// �R���X�g���N�^�i�I�[�o�[���[�h�j
//===============================================
CPlayer::CPlayer(int nPriority) : CObject2D(nPriority)
{
	// �l���N���A
	m_state = STATE_NONE;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
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
	// ��Ԃ�������
	m_state = STATE_NONE;

	// �e�N�X�`���̐ݒ�
	m_nIdxTexture = CManager::GetTexture()->Regist("data\\TEXTURE\\Player.png");

	// �I�u�W�F�N�g2D�̏���������
	CObject2D::Init(D3DXVECTOR3(150.0f, 600.0f, 0.0f));

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CPlayer::Uninit(void)
{
	// �I�u�W�F�N�g2D�̏I������
	CObject2D::Uninit();
}

//===============================================
// �X�V����
//===============================================
void CPlayer::Update(void)
{
	if (CManager::GetKeyboardInput()->GetRelease(DIK_SPACE) == true)
	{
		m_state = STATE_KICK;	// ��Ԃ�ύX
	}

	if (m_nPatternAnim <= 4)
	{// ���p�^�[�����𒴂��ĂȂ�
		if ((m_nCounterAnim % 10) == 0)
		{// �J�E���^�[���ݒ肵�������̐��l�ɒB����
			m_nCounterAnim = 0;		// �J�E���^�[�������l�ɖ߂�

			if (m_state == STATE_NONE)
			{
				CObject2D::UpdateAnim(m_nPatternAnim, 0);
			}
			else if (m_state == STATE_KICK)
			{
				CObject2D::UpdateAnim(m_nPatternAnim, 1);
			}

			m_nPatternAnim++;     // �p�^�[��No.���X�V����
		}

		m_nCounterAnim++;   // �J�E���^�[�����Z
	}
	else if(m_nPatternAnim > 4)
	{
		if (m_state == STATE_KICK)
		{
			m_state = STATE_NONE;		// �����Ă����Ԃɖ߂�
		}

		m_nPatternAnim = 0;		// �p�^�[������߂�
		m_nCounterAnim = 0;
	}
}

//===============================================
// �`�揈��
//===============================================
void CPlayer::Draw(void)
{
	// �I�u�W�F�N�g2D�̕`�揈��
	CObject2D::Draw();
}