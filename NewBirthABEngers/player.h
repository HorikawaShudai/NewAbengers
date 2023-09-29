//=========================================================
//
// �v���C���[���� [player.h]
// Author = �����đ�Y
//
//=========================================================
#ifndef _PLAYER_H_     // ���̃}�N����`������ĂȂ�������
#define _PLAYER_H_     // 2�d�C���N���[�h�h�~�̃}�N����`����

#include "main.h"
#include "object2D.h"

//===============================================
// �}�N����`
//===============================================
#define PLAYER_SIZEX		(60)		// ���i�����j
#define PLAYER_SIZEY		(90)		// �����i�����j

//===============================================
// �v���C���[�N���X
//===============================================
class CPlayer : public CObject2D
{
public:		//�N�ł��A�N�Z�X�\[�A�N�Z�X�w��q]

	// ���
	enum STATE
	{
		STATE_NONE = 0,		//�v���C���[�������
		STATE_KICK,			//�v���C���[�L�b�N���
		STATE_MAX
	};

	CPlayer();						// �f�t�H���g�R���X�g���N�^
	CPlayer(int nPriority = 5);		// �I�[�o�[���[�h���ꂽ�R���X�g���N�^
	~CPlayer();						// �f�X�g���N�^

	static CPlayer *Create(int nPriority = 5);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:	//�����̂݃A�N�Z�X�\[�A�N�Z�X�w��q]
	static int m_nIdxTexture;		// �g�p����e�N�X�`���̔ԍ�

	STATE m_state;		// ���
	int m_nCounterAnim;			// �A�j���[�V�����J�E���^�[
	int m_nPatternAnim;			// �A�j���[�V�����p�^�[��No.
};

#endif