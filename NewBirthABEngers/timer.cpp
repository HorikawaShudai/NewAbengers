
//================================================
//=
//=	�^�C�}�[����[timer.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "timer.h"

#include "renderer.h"

#include "number.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

//-------------------------------------
//-	�^�C�}�[�̃R���X�g���N�^
//-------------------------------------
CTimer::CTimer()
{
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_intervalValue = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_intervalDigits = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nSecond = 0;
	m_nCommaSecond = 0;

	m_nCntTime = 0;

	// �l�̃N���A
	for (int nCount = 0; nCount < SECOND_DIGITS; nCount++)
	{
		m_apSecondNumber[nCount] = NULL;
	}

	for (int nCount = 0; nCount < COMMA_DIGITS; nCount++)
	{
		m_apCommaNumber[nCount] = NULL;
	}
}

//-------------------------------------
//-	�^�C�}�[�̃f�X�g���N�^
//-------------------------------------
CTimer::~CTimer()
{

}

//-------------------------------------
//- �^�C�}�[�̏���������
//-------------------------------------
HRESULT CTimer::Init(void)
{
	// �l�̃N���A
	for (int nCount = 0; nCount < SECOND_DIGITS; nCount++)
	{
		if (m_apSecondNumber[nCount] == NULL)
		{
			m_apSecondNumber[nCount] = CNumber::Create(CNumber::TEX_GOLD_000, 7);

			if (m_apSecondNumber[nCount] == NULL)
			{
				return E_FAIL;
			}
		}
		else
		{
			return E_FAIL;
		}
	}

	for (int nCount = 0; nCount < COMMA_DIGITS; nCount++)
	{
		if (m_apCommaNumber[nCount] == NULL)
		{
			m_apCommaNumber[nCount] = CNumber::Create(CNumber::TEX_GOLD_000, 7);

			if (m_apCommaNumber[nCount] == NULL)
			{
				return E_FAIL;
			}
		}
		else
		{
			return E_FAIL;
		}
	}


	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �^�C�}�[�̏I������
//-------------------------------------
void CTimer::Uninit(void)
{
	for (int nCount = 0; nCount < SECOND_DIGITS; nCount++)
	{
		if (m_apSecondNumber[nCount] != NULL)
		{
			// �����̏�����
			m_apSecondNumber[nCount] = NULL;
		}
	}

	for (int nCount = 0; nCount < COMMA_DIGITS; nCount++)
	{
		if (m_apCommaNumber[nCount] != NULL)
		{
			// �����̏�����
			m_apCommaNumber[nCount] = NULL;
		}
	}
}

//-------------------------------------
//- �^�C�}�[�̍X�V����
//-------------------------------------
void CTimer::Update(void)
{
	// ���Z����
	Add();

	// �e�N�X�`���̌����Ɛݒ菈��
	NumberTex();
}

//-------------------------------------
//- �^�C�}�[�̕`�揈��
//-------------------------------------
void CTimer::Draw(void)
{

}

//-------------------------------------
//- �^�C�}�[�̐�������
//-------------------------------------
CTimer *CTimer::Create(void)
{
	// �^�C�}�[�̐���
	CTimer *pTimer = DBG_NEW CTimer;

	// �����̐����̗L���𔻒�
	if (pTimer != NULL)
	{
		// ����������
		if (FAILED(pTimer->Init()))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pTimer == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	return pTimer;
}

//-------------------------------------
//-	�^�C�}�[�̒l�ݒ菈��
//-------------------------------------
void CTimer::SetData(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 intervalValue, D3DXVECTOR3 intervalDigits)
{
	m_pos = pos;
	m_size = size;
	m_intervalValue = intervalValue;
	m_intervalDigits = intervalDigits;

	// �����̐ݒ菈��
	SetNumber();
}

//-------------------------------------
//-	�^�C�}�[�̎��Ԍo�ߏ���
//-------------------------------------
void CTimer::Add(void)
{
	// ���ԃJ�E���g�̉��Z
	m_nCntTime++;
}

//-------------------------------------
//-	�^�C�}�[�̌����ƃe�N�X�`���̐ݒ菈��
//-------------------------------------
void CTimer::NumberTex(void)
{
	// �ϐ��錾
	int nDigitsScond[SECOND_DIGITS];	// �b���̌����i�[
	int nDigitsComma[COMMA_DIGITS];		// �R���}�b���̌����i�[

	m_nSecond = (m_nCntTime / 60);
	m_nCommaSecond = (int)((m_nCntTime % 60) * 1.2f);

	// �����Ƃ̐��l����
	nDigitsScond[0] = ((m_nSecond % 1000) / 100);
	nDigitsScond[1] = ((m_nSecond % 100) / 10);
	nDigitsScond[2] = ((m_nSecond % 10));

	nDigitsComma[0] = ((m_nCommaSecond % 100) / 10);
	nDigitsComma[1] = (m_nCommaSecond % 10);

	for (int nCount = 0; nCount < SECOND_DIGITS; nCount++)
	{
		// �����̐ݒ菈��
		m_apSecondNumber[nCount]->SetValue(nDigitsScond[nCount]);
	}

	for (int nCount = 0; nCount < COMMA_DIGITS; nCount++)
	{
		// �����̐ݒ菈��
		m_apCommaNumber[nCount]->SetValue(nDigitsComma[nCount]);
	}
}

//-------------------------------------
//- �^�C�}�[�̈ʒu���̐ݒ�
//-------------------------------------
void CTimer::SetNumber(void)
{
	for (int nCount = 0; nCount < SECOND_DIGITS; nCount++)
	{
		// �����̗L���𔻒�
		if (m_apSecondNumber[nCount] != NULL)
		{
			// �����̈ʒu������
			m_apSecondNumber[nCount]->SetData(
				D3DXVECTOR3(
				m_pos.x + (m_intervalValue.x * nCount),
				m_pos.y + (m_intervalValue.y * nCount),
				m_pos.z + (m_intervalValue.z * nCount)),
				m_size,
				D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
		}
	}

	for (int nCount = 0; nCount < COMMA_DIGITS; nCount++)
	{
		// �����̗L���𔻒�
		if (m_apCommaNumber[nCount] != NULL)
		{
			// �����̈ʒu������
			m_apSecondNumber[nCount]->SetData(
				D3DXVECTOR3(
					m_pos.x + (m_intervalValue.x * nCount) + m_intervalDigits.x,
					m_pos.y + (m_intervalValue.y * nCount) + m_intervalDigits.y,
					m_pos.z + (m_intervalValue.z * nCount) + m_intervalDigits.z),
				m_size,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
		}
	}
}