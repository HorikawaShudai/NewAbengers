//=========================================================
//
// �{�[������ [ball.h]
// Author = �����đ�Y
//
//=========================================================
#ifndef _BALL_H_     // ���̃}�N����`������ĂȂ�������
#define _BALL_H_     // 2�d�C���N���[�h�h�~�̃}�N����`����

#include "main.h"
#include "object2D.h"

//===============================================
// �}�N����`
//===============================================
#define BALL_SIZEX		(40)		// ���i�����j
#define BALL_SIZEY		(40)		// �����i�����j
#define MOVE_GRAVITY	(0.75f)		// �d��
#define MOVE_LIFTING	(-16.85f)	// ���t�e�B���O���̈ړ���		

//===============================================
// �{�[���N���X
//===============================================
class CBall : public CObject2D
{
public:		//�N�ł��A�N�Z�X�\[�A�N�Z�X�w��q]
	CBall();						// �f�t�H���g�R���X�g���N�^
	CBall(int nPriority = 5);		// �I�[�o�[���[�h���ꂽ�R���X�g���N�^
	~CBall();						// �f�X�g���N�^

	static CBall *Create(int nPriority = 5);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:	//�����̂݃A�N�Z�X�\[�A�N�Z�X�w��q]
	static int m_nIdxTexture;		// �g�p����e�N�X�`���̔ԍ�
};

#endif