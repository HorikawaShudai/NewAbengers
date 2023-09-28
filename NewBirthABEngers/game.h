//=========================================================
//
// �Q�[����ʏ��� [game.h]
// Author = �����đ�Y
//
//=========================================================
#ifndef _GAME_H_     // ���̃}�N����`������ĂȂ�������
#define _GAME_H_     // 2�d�C���N���[�h�h�~�̃}�N����`����

#include "manager.h"

//===============================================
// �}�N����`
//===============================================
#define TIME_STATEREADY		(120)	// �ҋ@��Ԃ։�ʂ��؂�ւ��܂ł̗]�C

//===============================================
// �O���錾
//===============================================
class CObjectX;
class CObject3D;
class CPause;

//===============================================
// �Q�[����ʃN���X
//===============================================
class CGame : public CScene
{
public:		// �N�ł��A�N�Z�X�\ [�A�N�Z�X�w��q]
	CGame();						// �f�t�H���g�R���X�g���N�^
	~CGame();						// �f�X�g���N�^

	// �Q�[���̏��
	enum STATE
	{
		STATE_NONE = 0,	// �������Ă��Ȃ����
		STATE_READY,	// �J�n�ҋ@���
		STATE_NORMAL,	// �ʏ���
		STATE_END,		// �I�����
		STAET_MAX
	};

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObject3D *GetObject3D() { return m_pObject3D; }
	static CPause *GetPause() { return m_pPause; }

	static void SetEnablePause(const bool bPause);
	static bool GetPauseState(void) { return m_bPause; }
	static bool GetStateReady(void) { return m_bStateReady; }

	STATE GetState(void) { return m_state; }

private:	// �����̂݃A�N�Z�X�\ [�A�N�Z�X�w��q]
	static CObject3D *m_pObject3D;					// �I�u�W�F�N�g3D�N���X�̃|�C���^
	static CPause *m_pPause;						// �|�[�Y�N���X�̃|�C���^

	static bool m_bStateReady;		// GAMSESTATE_READY���ǂ���
	static bool m_bPause;			// ���݂̃|�[�Y�̏��
	STATE m_state;					// �Q�[���̏��
	int m_nCounterState;			// ��ԊǗ��J�E���^�[
};

#endif