//=========================================================
//
// �u���b�N���� [block.h]
// Author = �����đ�Y
//
//=========================================================
#ifndef _BLOCK_H_     // ���̃}�N����`������ĂȂ�������
#define _BLOCK_H_     // 2�d�C���N���[�h�h�~�̃}�N����`����

#include "main.h"
#include "object2D.h"

//===============================================
// �}�N����`
//===============================================
#define BLOCK_SIZEX		(40)					// ���i�����j
#define BLOCK_SIZEY		(40)					// �����i�����j
#define MOVE_GRAVITY	(0.75f)					// �d��
#define MOVE_LIFTING	(-20.85f)				// ���t�e�B���O���̈ړ���
#define LIFTING_POWER	(0.2f)					// �R�鋭��
#define MAX_POWER		(-29.0f)				// �ő僊�t�e�B���O��

//===============================================
// �u���b�N�N���X
//===============================================
class CBlock : public CObject2D
{
public:		//�N�ł��A�N�Z�X�\[�A�N�Z�X�w��q]
	CBlock();						// �f�t�H���g�R���X�g���N�^
	CBlock(int nPriority = 5);		// �I�[�o�[���[�h���ꂽ�R���X�g���N�^
	~CBlock();						// �f�X�g���N�^

	static CBlock *Create(int nPriority = 5);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:	//�����̂݃A�N�Z�X�\[�A�N�Z�X�w��q]
	static int m_nIdxTexture;		// �g�p����e�N�X�`���̔ԍ�
	float m_fPower;					// �R�鋭��
	bool m_bLifting;				// ���t�e�B���O���ł��邩
};

#endif