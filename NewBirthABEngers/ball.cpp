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
#include "debugproc.h"

//===============================================
// �ÓI�����o�ϐ�
//===============================================
int CBall::m_nIdxTexture = NULL;		// �g�p����e�N�X�`���̔ԍ�

//===============================================
// �R���X�g���N�^
//===============================================
CBall::CBall() : CObject2D(5)
{
	// �l���N���A
	m_fPower = 0.0f;
	m_bLifting = false;
	m_bDeath = false;
}

//===============================================
// �R���X�g���N�^�i�I�[�o�[���[�h�j
//===============================================
CBall::CBall(int nPriority) : CObject2D(nPriority)
{
	// �l���N���A
	m_fPower = 0.0f;
	m_bLifting = false;
	m_bDeath = false;
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
	pBall->SetType(TYPE_BALL);

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
	// �R�鋭���ύX
	if (CManager::GetKeyboardInput()->GetPress(DIK_SPACE) == true)
	{
		m_fPower -= LIFTING_POWER;

		if (m_fPower <= MAX_POWER)
		{// �����̏���𒴂�����߂�
			m_fPower = MAX_POWER;
		}
	}

	if (CollisionObj(TYPE_PLAYER) == true)
	{// �I�u�W�F�N�g�͈͓̔�
		// ���t�e�B���O
		if (CManager::GetKeyboardInput()->GetRelease(DIK_SPACE) == true && m_bLifting == false)
		{
			m_move.y = m_fPower;
			m_bLifting = true;
		}
	}
	else if (CollisionObj(TYPE_BLOCK) == true)
	{// ��Q���ɐڐG
		m_bDeath = true;	// ���S�t���O
	}

	if (CManager::GetKeyboardInput()->GetPress(DIK_SPACE) == false)
	{
		m_fPower = MOVE_LIFTING;
	}

	// �ʒu���X�V
	CObject2D::SetPos(D3DXVECTOR3(m_pos.x, m_pos.y += m_move.y, 0.0f));

	// �d�͏���
	m_move.y += MOVE_GRAVITY;

	// �f�o�b�O�\��
	CManager::GetDebugProc()->Print(" �R�鋭���F%f\n", m_fPower);

}

//===============================================
// �`�揈��
//===============================================
void CBall::Draw(void)
{
	// �I�u�W�F�N�g2D�̕`�揈��
	CObject2D::Draw();
}

//===============================================
// �I�u�W�F�N�g�Ƃ̓����蔻��
//===============================================
bool CBall::CollisionObj(const CObject::TYPE type)
{
	bool bLand = false;

	for (int nCntPriorityObj = 0; nCntPriorityObj < PRIORITY_MAX; nCntPriorityObj++)
	{
		CObject *pObj = CObject::GetTop(nCntPriorityObj);	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^���擾

		while (pObj != NULL)
		{// �g�p����Ă���
			CObject *pObjNext = pObj->GetNext();	// ���̃I�u�W�F�N�g�ւ̃|�C���^���擾
			CObject::TYPE typeObj = pObj->GetType();			// ��ނ��擾

			if (typeObj == type)
			{// ��ނ��ݒ肳�ꂽ���̂Ɠ����ꍇ
				D3DXVECTOR3 posObj = pObj->GetPos();		// �ʒu���擾
				D3DXVECTOR3 posOldObj = pObj->GetPosOld();	// �O��̈ʒu���擾
				D3DXVECTOR3 sizeObj = pObj->GetSize();		// �T�C�Y���擾

				for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
				{
					CObject *pBall = CObject::GetTop(nCntPriority);	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^���擾

					while (pBall != NULL)
					{// �g�p����Ă���
						CObject *pBallNext = pBall->GetNext();				// ���̃I�u�W�F�N�g�ւ̃|�C���^���擾
						CObject::TYPE typeBall = pBall->GetType();			// ��ނ��擾

						if (typeBall == TYPE_BALL)
						{// ��ނ��ݒ肳�ꂽ���̂Ɠ����ꍇ
							D3DXVECTOR3 posBall = pBall->GetPos();			// �ʒu���擾
							D3DXVECTOR3 posOldBall = pBall->GetPosOld();	// �O��̈ʒu���擾

							if (posBall.x >= posObj.x - BALL_SIZEX - sizeObj.x
								&& posBall.x <= posObj.x + BALL_SIZEX + sizeObj.x
								&& posBall.y <= posObj.y + BALL_SIZEY + sizeObj.y
								&& posBall.y >= posObj.y - BALL_SIZEY)
							{//	���݂̈ʒu���I�u�W�F�N�g�͈͓̔�
								return true;
							}
							else
							{
								m_bLifting = false;	// ���t�e�B���O���\�ɂ���
								return false;
							}
						}
						pBall = pBallNext;		// ���̃I�u�W�F�N�g����
					}
				}
			}
			pObj = pObjNext;		// ���̃I�u�W�F�N�g����
		}
	}

	return bLand;
}