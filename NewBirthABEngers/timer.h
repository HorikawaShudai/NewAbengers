
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

class CNumberSakai;
class CObject2D;

//-======================================
//-	�N���X��`
//-======================================

class CTimer
{
public:

	// �e�N�X�`���̎��
	enum TEX
	{
		TEX_COMMA = 0,	// �R���}
		TEX_METRE,		// ���[�g��
		TEX_MAX
	};

	CTimer();
	~CTimer();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTimer *Create(void);

	void SetData(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 intervalValue, D3DXVECTOR3 intervalDigits);
	int Get(void);

private:

	void Add(void);
	void NumberTex(void);

	void SetNumber(void);

	static CObject2D *m_apObject2D[TEX_MAX];		// �I�u�W�F�N�g2D�N���X�̃|�C���^
	static int m_aIdxTexture[TEX_MAX];				// �g�p����e�N�X�`���̔ԍ�
	static const char *m_apTextureData[TEX_MAX];	// �e�N�X�`���t�@�C����

	D3DXVECTOR3 m_aPos2d[TEX_MAX];					// �ʒu
	D3DXVECTOR3 m_aSize2d[TEX_MAX];					// �T�C�Y

	D3DXVECTOR3 m_pos;				// �ʒu
	D3DXVECTOR3 m_size;				// �傫��
	D3DXVECTOR3 m_intervalValue;	// �l�̊Ԋu
	D3DXVECTOR3 m_intervalDigits;	// ���̊Ԋu

	int m_nSecond;			// �b��
	int m_nCommaSecond;		// �R���}�b

	int m_nCntTime;			// ���Ԃ̃J�E���g
	
	CNumberSakai *m_apSecondNumber[SECOND_DIGITS];	// �b�̐����̃|�C���^
	CNumberSakai *m_apCommaNumber[COMMA_DIGITS];		// �R���}�b�̐����̃|�C���^

};

#endif	// ��d�C���N���[�h�h�~�̏I��
