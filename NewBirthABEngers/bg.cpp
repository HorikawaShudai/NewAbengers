//=========================================================
//
// �w�i���� [bg.cpp]
// Author = ����쏟
//
//=========================================================

#include "bg.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//===============================================
// �}�N����`
//===============================================
#define SIZE_X				(285.0f)		// ���T�C�Y
#define SIZE_Y				(90.0f)			// �c�T�C�Y
#define TIME_PROGRESS		(240)			// �i���ڍs����
#define TIME_PROGRESSTART	(1200)			// �i���ڍs�J�n����

//===============================================
// �ÓI�����o�ϐ�
//===============================================

int CBg::m_aIdxTexture[TEX_MAX] = {};				// �g�p����e�N�X�`���̔ԍ�

//===============================================
// �e�N�X�`���t�@�C����
//===============================================
const char *CBg::m_apTextureData[TEX_MAX] =
{
	{ "data\\TEXTURE\\GameBg000.png" },		// �Q�[��
	{ "data\\TEXTURE\\TitleBg000.png" },	// �^�C�g��
	{ "data\\TEXTURE\\ResultBg000.png" },	// ���U���g
	{ "data\\TEXTURE\\TutorialBg000.png" },	// �`���[�g���A��
};

//===============================================
// �R���X�g���N�^
//===============================================
CBg::CBg() : CObject2D(5)
{
	// �l�̃N���A
	m_nTypeTex = 0;

	m_texPos = D3DXVECTOR2(0.0f, 0.0f);
	m_texMove = D3DXVECTOR2(0.0f, 0.0f);
}

//===============================================
// �R���X�g���N�^�i�I�[�o�[���[�h�j
//===============================================
CBg::CBg(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
	m_nTypeTex = 0;

	m_texPos = D3DXVECTOR2(0.0f, 0.0f);
	m_texMove = D3DXVECTOR2(0.0f, 0.0f);
}

//===============================================
// �f�X�g���N�^
//===============================================
CBg::~CBg()
{

}

//===============================================
// ��������
//===============================================
CBg *CBg::Create(int nTex, int nPriority)
{
	CBg *pBg;

	// �w�i�̐���
	pBg = new CBg(nPriority);

	// ��ނ̐ݒ�
	pBg->SetType(TYPE_BULLET);

	// �T�C�Y�̐ݒ�
	pBg->SetSize(SIZE_X, SIZE_Y);

	// ����������
	pBg->Init(D3DXVECTOR3(650.0f, 600.0f, 0.0f), nTex, nPriority);

	// �ݒ菈��
	pBg->Set(nTex);

	return pBg;
}

//===============================================
// ����������
//===============================================
HRESULT CBg::Init(D3DXVECTOR3 pos, int nTex, int nPriority)
{
	// �I�u�W�F�N�g2D�̏���������
	CObject2D::Init(pos);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CBg::Uninit(void)
{
	// �I�u�W�F�N�g2D�̏I������
	CObject2D::Uninit();
}

//===============================================
// �X�V����
//===============================================
void CBg::Update(void)
{
	// �e�N�X�`���̉��Z����
	m_texPos += m_texMove;

	// �e�N�X�`���ʒu�̕␳
	DestTexPos();

	// ���_���̐ݒ�
	SetVtx();
}

//===============================================
// �`�揈��
//===============================================
void CBg::Draw(void)
{
	 // �I�u�W�F�N�g2D�̕`�揈��
	CObject2D::Draw();
}

//===============================================
// �ݒ菈��
//===============================================
void CBg::Set(const int nType)
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
void CBg::SetData(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color, D3DXVECTOR2 texMove)
{
	m_pos = pos;
	m_size = size;
	m_color = color;

	m_texMove = texMove;

	// ���_���̐ݒ�
	SetVtx();
}

//-------------------------------------
//- �w�i�̒��_���ݒ�
//-------------------------------------
void CBg::SetVtx(void)
{
	// ���_�o�b�t�@�̎擾
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
	pVtx[0].tex = D3DXVECTOR2(
		0.0f + m_texPos.x,
		0.0f + m_texPos.y);

	pVtx[1].tex = D3DXVECTOR2(
		1.0f + m_texPos.x,
		0.0f + m_texPos.y);

	pVtx[2].tex = D3DXVECTOR2(
		0.0f + m_texPos.x,
		1.0f + m_texPos.y);

	pVtx[3].tex = D3DXVECTOR2(
		1.0f + m_texPos.x,
		1.0f + m_texPos.y);

	// ���_�o�b�t�@���A�����b�N����
	vtxBuff->Unlock();
}

//-------------------------------------
//- �w�i�̃e�N�X�`�����W�̕␳
//-------------------------------------
void CBg::DestTexPos(void)
{
	// ���̃e�N�X�`���ʒu�̔���
	if (m_texPos.x > 1.0f)
	{
		// 1.0f�𒴂����ꍇ0.0f�ɂ���
		m_texPos.x = 0.0f;
	}
	else if (m_texPos.x < 0.0f)
	{
		// 0.0f����������ꍇ1.0f�ɂ���
		m_texPos.x = 1.0f;
	}

	// �c�̃e�N�X�`���ʒu�̔���
	if (m_texPos.y > 1.0f)
	{
		// 1.0f�𒴂����ꍇ0.0f�ɂ���
		m_texPos.y = 0.0f;
	}
	else if (m_texPos.y < 0.0f)
	{
		// 0.0f����������ꍇ1.0f�ɂ���
		m_texPos.y = 1.0f;
	}
}

