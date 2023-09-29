//=========================================================
//
// �n�ʏ��� [ground.cpp]
// Author = ����쏟
//
//=========================================================

#include "ground.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//===============================================
// �}�N����`
//===============================================

//===============================================
// �ÓI�����o�ϐ�
//===============================================

int CGround::m_aIdxTexture[TEX_MAX] = {};				// �g�p����e�N�X�`���̔ԍ�

//===============================================
// �e�N�X�`���t�@�C����
//===============================================
const char *CGround::m_apTextureData[TEX_MAX] =
{
	{ "data\\TEXTURE\\Ground000.png" },		// �n��000
};

//===============================================
// �R���X�g���N�^
//===============================================
CGround::CGround() : CObject2D(5)
{
	// �l�̃N���A
	m_nTypeTex = 0;

	m_texPos = D3DXVECTOR2(0.0f, 0.0f);
	m_texMove = D3DXVECTOR2(0.0f, 0.0f);
}

//===============================================
// �R���X�g���N�^�i�I�[�o�[���[�h�j
//===============================================
CGround::CGround(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
	m_nTypeTex = 0;

	m_texPos = D3DXVECTOR2(0.0f, 0.0f);
	m_texMove = D3DXVECTOR2(0.0f, 0.0f);
}

//===============================================
// �f�X�g���N�^
//===============================================
CGround::~CGround()
{

}

//===============================================
// ��������
//===============================================
CGround *CGround::Create(int nTex, int nPriority)
{
	CGround *pGround;

	// �n�ʂ̐���
	pGround = new CGround(nPriority);

	// ��ނ̐ݒ�
	pGround->SetType(TYPE_BULLET);

	// �T�C�Y�̐ݒ�
	pGround->SetSize(0.0f, 0.0f);

	// ����������
	pGround->Init(D3DXVECTOR3(650.0f, 600.0f, 0.0f), nTex, nPriority);

	// �ݒ菈��
	pGround->Set(nTex);

	return pGround;
}

//===============================================
// ����������
//===============================================
HRESULT CGround::Init(D3DXVECTOR3 pos, int nTex, int nPriority)
{
	// �I�u�W�F�N�g2D�̏���������
	CObject2D::Init(pos);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CGround::Uninit(void)
{
	// �I�u�W�F�N�g2D�̏I������
	CObject2D::Uninit();
}

//===============================================
// �X�V����
//===============================================
void CGround::Update(void)
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
void CGround::Draw(void)
{
	// �I�u�W�F�N�g2D�̕`�揈��
	CObject2D::Draw();
}

//===============================================
// �ݒ菈��
//===============================================
void CGround::Set(const int nType)
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
void CGround::SetData(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color, D3DXVECTOR2 texMove)
{
	m_pos = pos;
	m_size = size;
	m_color = color;

	m_texMove = texMove;

	// ���_���̐ݒ�
	SetVtx();
}

//-------------------------------------
//- �n�ʂ̒��_���ݒ�
//-------------------------------------
void CGround::SetVtx(void)
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
//- �n�ʂ̃e�N�X�`�����W�̕␳
//-------------------------------------
void CGround::DestTexPos(void)
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
