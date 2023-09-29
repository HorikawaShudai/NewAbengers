
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

#include "manager.h"
#include "renderer.h"

#include "texture.h"
#include "number_sakai.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

CObject2D *CTimer::m_apObject2D[TEX_MAX] = {};
int CTimer::m_aIdxTexture[TEX_MAX] = {};
const char *CTimer::m_apTextureData[TEX_MAX] = {};	// �e�N�X�`���t�@�C����

//-------------------------------------
//-	�^�C�}�[�̃R���X�g���N�^
//-------------------------------------
CTimer::CTimer()
{
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		m_aPos2d[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aSize2d[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

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
	// �e�N�X�`���t�@�C����
	const char *m_apTextureData[TEX_MAX] =
	{
		{ "data\\TEXTURE\\Comma000.png" },		// �w�i
		{ "data\\TEXTURE\\Metre000.png" },		// �Q�[���ɖ߂�
	};

	for (int nCount = 0; nCount < SECOND_DIGITS; nCount++)
	{
		if (m_apSecondNumber[nCount] == NULL)
		{
			m_apSecondNumber[nCount] = CNumberSakai::Create(CNumberSakai::TEX_GOLD_000, 7);

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
			m_apCommaNumber[nCount] = CNumberSakai::Create(CNumberSakai::TEX_GOLD_000, 7);

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

	for (int nCntObj = 0; nCntObj < TEX_MAX; nCntObj++)
	{
		m_apObject2D[nCntObj] = new CObject2D(7);

		// �e�N�X�`���̐ݒ�
		m_aIdxTexture[nCntObj] = CManager::GetTexture()->Regist(m_apTextureData[nCntObj]);

		// �e�N�X�`���̊��蓖��
		m_apObject2D[nCntObj]->BindTexture(m_aIdxTexture[nCntObj]);
	}

	m_aSize2d[TEX_COMMA] = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	m_aSize2d[TEX_METRE] = D3DXVECTOR3(100.0f, 100.0f, 0.0f);

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

	m_aPos2d[TEX_COMMA] = D3DXVECTOR3(pos.x + 300.0f , pos.y - 50.0f , pos.z);
	m_aPos2d[TEX_METRE] = D3DXVECTOR3(pos.x + 600.0f , pos.y - 50.0f , pos.z);

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
	m_nCommaSecond = (int)((m_nCntTime % 60) * 1.67f);

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
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	for (int nCount = 0; nCount < COMMA_DIGITS; nCount++)
	{
		// �����̗L���𔻒�
		if (m_apCommaNumber[nCount] != NULL)
		{
			// �����̈ʒu������
			m_apCommaNumber[nCount]->SetData(
				D3DXVECTOR3(
					m_pos.x + (m_intervalValue.x * nCount) + m_intervalDigits.x + 300.0f,
					m_pos.y + (m_intervalValue.y * nCount) + m_intervalDigits.y,
					m_pos.z + (m_intervalValue.z * nCount) + m_intervalDigits.z),
				m_size,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
		}
	}

	if (m_apObject2D[TEX_COMMA] != NULL)
	{
		// �T�C�Y�ݒ菈��
		m_apObject2D[TEX_COMMA]->SetSize(m_aSize2d[TEX_COMMA].x, m_aSize2d[TEX_COMMA].y);

		// �I�u�W�F�N�g2D�̏���������
		m_apObject2D[TEX_COMMA]->Init(m_aPos2d[TEX_COMMA]);
	}

	if (m_apObject2D[TEX_METRE] != NULL)
	{
		// �T�C�Y�ݒ菈��
		m_apObject2D[TEX_METRE]->SetSize(m_aSize2d[TEX_METRE].x, m_aSize2d[TEX_METRE].y);

		// �I�u�W�F�N�g2D�̏���������
		m_apObject2D[TEX_METRE]->Init(m_aPos2d[TEX_METRE]);
	}
}

//-------------------------------------
//- �^�C�}�[�̎擾
//-------------------------------------
int CTimer::Get(void)
{
	int nScore = 0;

	m_nSecond = (m_nCntTime / 60);
	m_nCommaSecond = (int)((m_nCntTime % 60) * 1.67f);

	nScore = m_nSecond * 100 + m_nCommaSecond;

	return nScore;
}