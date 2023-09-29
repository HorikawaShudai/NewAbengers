
//=========================================================
//
// �w�i���� [ground.h]
// Author = ����쏟
//
//=========================================================
#ifndef _GROUND_H_     // ���̃}�N����`������ĂȂ�������
#define _GROUND_H_     // 2�d�C���N���[�h�h�~�̃}�N����`����

#include "object2D.h"

//===============================================
// �}�N����`
//===============================================

//===============================================
// �w�i�N���X
//===============================================
class CGround : public CObject2D
{
public:		// �N�ł��A�N�Z�X�\ [�A�N�Z�X�w��q]
	CGround();					// �f�t�H���g�R���X�g���N�^
	CGround(int nPriority = 5);	// �I�[�o�[���[�h���ꂽ�R���X�g���N�^
	~CGround();					// �f�X�g���N�^

	// �w�i�̃e�N�X�`��
	enum TEX
	{
		TEX_GROUND_000 = 0,	// �n��000
		TEX_MAX
	};

	static CGround *Create(int nTex, int nPriority = 3);

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