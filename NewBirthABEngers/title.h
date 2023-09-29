//=========================================================
//
// �^�C�g����ʏ��� [title.h]
// Author = �����đ�Y
//
//=========================================================
#ifndef _TITLE_H_     // ���̃}�N����`������ĂȂ�������
#define _TITLE_H_     // 2�d�C���N���[�h�h�~�̃}�N����`����

#include "manager.h"

//===============================================
// �O���錾
//===============================================
class CFade;

class CBg;

//===============================================
// �^�C�g����ʃN���X
//===============================================
class CTitle : public CScene
{
public:		// �N�ł��A�N�Z�X�\ [�A�N�Z�X�w��q]
	CTitle();						// �f�t�H���g�R���X�g���N�^
	~CTitle();						// �f�X�g���N�^

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool GetFade(void) { return m_bFade; }

private:	// �����̂݃A�N�Z�X�\ [�A�N�Z�X�w��q]

	int m_nTimeFade;	// �����t�F�[�h����
	bool m_bFade;		// �t�F�[�h�ɓ�������

	static CBg *m_pBg;	// �w�i�̃|�C���^
};

#endif