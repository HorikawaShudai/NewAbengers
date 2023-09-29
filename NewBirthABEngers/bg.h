
//=========================================================
//
// �w�i���� [bg.h]
// Author = ����쏟
//
//=========================================================
#ifndef _BG_H_     // ���̃}�N����`������ĂȂ�������
#define _BG_H_     // 2�d�C���N���[�h�h�~�̃}�N����`����

#include "object2D.h"

//===============================================
// �}�N����`
//===============================================

//===============================================
// �w�i�N���X
//===============================================
class CBg : public CObject2D
{
public:		// �N�ł��A�N�Z�X�\ [�A�N�Z�X�w��q]
	CBg();					// �f�t�H���g�R���X�g���N�^
	CBg(int nPriority = 5);	// �I�[�o�[���[�h���ꂽ�R���X�g���N�^
	~CBg();					// �f�X�g���N�^

	// �w�i�̃e�N�X�`��
	enum TEX
	{
		TEX_GAME = 0,	// �Q�[��
		TEX_TITLE,		// �^�C�g��
		TEX_RESULT,		// ���U���g
		TEX_TUTORIAL,	// �`���[�g���A��
		TEX_MAX
	};

	static CBg *Create(int nTex, int nPriority = 3);

	HRESULT Init(D3DXVECTOR3 pos, int nTex, int nPriority);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(const int nType);

	void SetData(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color, D3DXVECTOR2 texMove);

	void SetVtx(void);

	void DestTexPos(void);

private:	// �����̂݃A�N�Z�X�\ [�A�N�Z�X�w��q]
	static const char *m_apTextureData[TEX_MAX];	// �e�N�X�`���t�@�C����
	static int m_aIdxTexture[TEX_MAX];				// �g�p����e�N�X�`���̔ԍ�

	int m_nTypeTex;									// �e�N�X�`���̎��

	D3DXVECTOR3 m_size;								// �T�C�Y
	D3DXCOLOR m_color;								// �F

	D3DXVECTOR2 m_texPos;							// �e�N�X�`���̈ʒu
	D3DXVECTOR2 m_texMove;							// �e�N�X�`���̈ړ���
};

#endif