
//-===============================================
//-
//-	���Ԃ̏����̃w�b�_�[[timer.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _TIMER_H_		// ���̃}�N������`����Ȃ�������
#define _TIMER_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

//-======================================
//-	�}�N����`
//-======================================

#define SECOND_DIGITS	(3)		// �b�̌���
#define COMMA_DIGITS	(2)		// �R���}�b�̌���

//===============================================
// �O���錾
//===============================================

class CNumber;

//-======================================
//-	�N���X��`
//-======================================

class CTimer
{
public:

	CTimer();
	~CTimer();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTimer *Create(void);

	void SetData(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 intervalValue, D3DXVECTOR3 intervalDigits);

private:

	void Add(void);
	void NumberTex(void);

	void SetNumber(void);

	D3DXVECTOR3 m_pos;				// �ʒu
	D3DXVECTOR3 m_size;				// �傫��
	D3DXVECTOR3 m_intervalValue;	// �l�̊Ԋu
	D3DXVECTOR3 m_intervalDigits;	// ���̊Ԋu

	int m_nSecond;			// �b��
	int m_nCommaSecond;		// �R���}�b

	int m_nCntTime;			// ���Ԃ̃J�E���g
	
	CNumber *m_apSecondNumber[SECOND_DIGITS];	// �b�̐����̃|�C���^
	CNumber *m_apCommaNumber[COMMA_DIGITS];		// �R���}�b�̐����̃|�C���^

};

#endif	// ��d�C���N���[�h�h�~�̏I��
