
//=========================================================
//
// ����̐������� [number_sakai.cpp]
// Author = ����쏟
//
//=========================================================

#include "number_sakai.h"

#include "manager.h"
#include "renderer.h"
#include "texture.h"

//===============================================
// �}�N����`
//===============================================

//===============================================
// �ÓI�����o�ϐ�
//===============================================

int CNumberSakai::m_aIdxTexture[TEX_MAX] = {};				// �g�p����e�N�X�`���̔ԍ�

//===============================================
// �e�N�X�`���t�@�C����
//===============================================
const char *CNumberSakai::m_apTextureData[TEX_MAX] =
{
	{ "data\\TEXTURE\\number_000.png" },		// �Q�[��
};

//===============================================
// �R���X�g���N�^
//===============================================
CNumberSakai::CNumberSakai() : CObject2D(5)
{
	// �l�̃N���A
	m_nTypeTex = 0;

	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	m_nValue = 0;
}

//===============================================
// �R���X�g���N�^�i�I�[�o�[���[�h�j
//===============================================
CNumberSakai::CNumberSakai(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
	m_nTypeTex = 0;

	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	m_nValue = 0;
}

//===============================================
// �f�X�g���N�^
//===============================================
CNumberSakai::~CNumberSakai()
{

}

//===============================================
// ��������
//===============================================
CNumberSakai *CNumberSakai::Create(int nTex, int nPriority)
{
	CNumberSakai *pBg;

	// �w�i�̐���
	pBg = new CNumberSakai(nPriority);

	// ��ނ̐ݒ�
	pBg->SetType(TYPE_BULLET);

	// �T�C�Y�̐ݒ�
	pBg->SetSize(0.0f, 0.0f);

	// ����������
	pBg->Init(D3DXVECTOR3(650.0f, 600.0f, 0.0f), nTex, nPriority);

	// �ݒ菈��
	pBg->Set(nTex);

	return pBg;
}

//===============================================
// ����������
//===============================================
HRESULT CNumberSakai::Init(D3DXVECTOR3 pos, int nTex, int nPriority)
{
	// �I�u�W�F�N�g2D�̏���������
	CObject2D::Init(pos);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CNumberSakai::Uninit(void)
{
	// �I�u�W�F�N�g2D�̏I������
	CObject2D::Uninit();
}

//===============================================
// �X�V����
//===============================================
void CNumberSakai::Update(void)
{
	// ���_���̐ݒ�
	SetVtx();
}

//===============================================
// �`�揈��
//===============================================
void CNumberSakai::Draw(void)
{
	// �I�u�W�F�N�g2D�̕`�揈��
	CObject2D::Draw();
}

//===============================================
// �ݒ菈��
//===============================================
void CNumberSakai::Set(const int nType)
{
	m_nTypeTex = nType;

	// �e�N�X�`���̐ݒ�
	m_aIdxTexture[m_nTypeTex] = CManager::GetTexture()->Regist(m_apTextureData[m_nTypeTex]);

	// �e�N�X�`���̊��蓖��
	CObject2D::BindTexture(m_aIdxTexture[m_nTypeTex]);
}

//===============================================
// �l�̐ݒ菈��
//===============================================
void CNumberSakai::SetData(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	m_pos = pos;
	m_size = size;
	m_color = color;

	// ���_���̐ݒ�
	SetVtx();
}

//-------------------------------------
//- �����̒l��ݒ菈��
//-------------------------------------
void CNumberSakai::SetValue(int nValue)
{
	m_nValue = nValue;
}

//-------------------------------------
//- �����̒��_���ݒ�
//-------------------------------------
void CNumberSakai::SetVtx(void)
{
	// ���_�o�b�t�@���|�C���^��錾
	LPDIRECT3DVERTEXBUFFER9 vtxBuff = GetVtxBuff();

	// ���_�o�b�t�@�擾�����̗L���𔻒�
	if (vtxBuff == NULL)
	{// ���s��

		// ���_���ݒ�𔲂���
		return;
	}

	// 2D���_���̃|�C���^��錾
	VERTEX_2D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	vtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	// ���_���W��ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[��ݒ�
	pVtx[0].col = m_color;
	pVtx[1].col = m_color;
	pVtx[2].col = m_color;
	pVtx[3].col = m_color;

	// �e�N�X�`���̍��W��ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.1f * (m_nValue + 0), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f * (m_nValue + 1), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f * (m_nValue + 0), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f * (m_nValue + 1), 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	vtxBuff->Unlock();
}
