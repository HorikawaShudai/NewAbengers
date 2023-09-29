
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
// �����N���X
//===============================================
class CNumber : public CObject2D
{
public:		// �N�ł��A�N�Z�X�\ [�A�N�Z�X�w��q]
	CNumber();					// �f�t�H���g�R���X�g���N�^
	CNumber(int nPriority = 5);	// �I�[�o�[���[�h���ꂽ�R���X�g���N�^
	~CNumber();					// �f�X�g���N�^

	// �����̃e�N�X�`��
	enum TEX
	{
		TEX_GOLD_000 = 0,	// ������000
		TEX_MAX
	};

	static CNumber *Create(int nTex, int nPriority = 3);

	HRESULT Init(D3DXVECTOR3 pos, int nTex, int nPriority);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(const int nType);

	void SetData(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);

	void SetValue(int nValue);

private:	// �����̂݃A�N�Z�X�\ [�A�N�Z�X�w��q]

	void SetVtx(void);

	static const char *m_apTextureData[TEX_MAX];	// �e�N�X�`���t�@�C����
	static int m_aIdxTexture[TEX_MAX];				// �g�p����e�N�X�`���̔ԍ�

	int m_nTypeTex;									// �e�N�X�`���̎��

	D3DXVECTOR3 m_size;								// �T�C�Y
	D3DXCOLOR m_color;								// �F
	int m_nValue;									// ���l
};

#endif
