//========================================
// 
// �����L���O
// 
//========================================
// *** ranking.h ***
//========================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "../main.h"
#include "../manager.h"

//****************************************
// �O���錾
//****************************************
class CText;

//****************************************
// �N���X
//****************************************
class CRanking : public CScene
{
	static const char* FILE_PATH;			// �ǂݍ��ރt�@�C���p�X
	static const char* TEXT_FILE_PATH;		// �ǂݍ��ރt�@�C���p�X
	static const int RANK_NUM = 8;			// ���ʐ�
	static const int NAME_NUM = 5;			// �����L���O�̂̕�����
	static const int EXPLAIN_MAX = 6;		// ��������̃e�L�X�g��
	static const int TEXT_MAX = 9;			// �����\���̃e�L�X�g��
	static const int NAME_START_DEX = 5;	// ���O�̊J�n�ʒu
	static const int BLINK_TIME = 4;		// �_�Ŏ���


// �����L���O���̕�������
// �����L���O���̕������
// �����L���O���̊J�n����
#define NAME_MIN_CHAR	('0')
#define NAME_MAX_CHAR	('Z' + 1)
#define NAME_START_CHAR	('A')

#define BLINK_COLOR		D3DXCOLOR{1.0f,1.0f,1.0f,1.0f}	// �����L���O�t���[���̓_�ŐF
#define RANKING_COLOR	D3DXCOLOR{0.824f,0.824f,0.0f,1.0f}	// �����L���O�t���[���̍X�V�F

public:

	// ***** �֐� *****
	CRanking();
	~CRanking();

	// -- ���C�� ------------------------------------------
	/* ������		*/HRESULT Init(void);
	/* �I��			*/void Uninit(void);
	/* �X�V			*/void Update(void);
	/* �`��			*/void Draw(void);
	/* �ǂݍ���		*/void Load(void);
	/* �����ǂݍ���	*/void WordsLoad(void);
	/* �����o��		*/void Save(void);
	/* ����			*/static CRanking *Create(void);

	// -- �ݒ� ------------------------------------------
	/* �X�R�A	*/int SetScore(int nScore);
	/* ���O����	*/void SetNameEntry(int nUpdateRank);
	/* �X�R�A	*/static void SetScore11(int nScore);

	// -- �擾 ------------------------------------------
	/* ���ʂ̕\���`���̎擾	*/char *GetRankText(int nRank) { return m_aRank[nRank].aRankText; }


	// ***** �ϐ� *****
	static int m_nGameScore;
	static bool m_bSetScore;

private:

	// ***** �\���� *****
	
	// ����
	struct Letter
	{
		char aConv[4];		// ����
	};

	// �ϊ���
	struct Conv
	{
		Letter *pLetter;
	};

	// ������
	struct String
	{
		Conv	*pConv;		// ����
		int		nLettreMax;	// �����̍ő吔
		int		nConvMax;	// �ϊ������̍ő吔
	};

	// ���ʏ��
	struct Info
	{
		int		nCounterState;	// ��ԃJ�E���^�[
		bool	bNameEntry;		// ���O����
		int		nCntName;		// ���O�J�E���g
		int		nCntChar;		// �����J�E���g
		int		nUpdateRank;	// �X�V����
		int		nCntBlink;		// �_�ŃJ�E���^�[
		bool	bNameInput;		// ���̓t���O

		int		nCntString;		// ������J�E���g
		int		nCntLetter;		// �����J�E���g
		int		nCntConv;		// �ϊ������J�E���g

		int		nCounterBlink;	// �_�ŃJ�E���^�[
	};

	// �e���ʂ̃e�L�X�g
	struct Rank
	{
		char aRankText[TXT_MAX];	// �e�L�X�g
	};

	// �����L���O���
	struct Ranking
	{
		int nScore;				// �X�R�A
		char aName[TXT_MAX];	// ���O 
	};

	// ***** �֐� *****
	/* ��ԏ���			*/void State(void);
	/* ���O����			*/void NameEntry(void);
	/* ���O����			*/void NameInput(void);
	/* �\�[�g�~��		*/void SortDesc(int *nUpdateRank);
	/* �󔒖���			*/void strinit(char *pData, int nNum);
	/* �����\��(�ݒ�)	*/void SetWords(void);
	/* �����\��(�X�V)	*/void UpdateWords(void);

	// ***** �ϐ� *****
	Info m_Info;					// ���ʏ��
	Ranking m_Ranking[RANK_NUM];	// ���ʏ��
	CText *m_Text[RANK_NUM];		// ���ʃe�L�X�g
	char m_aNameData[TXT_MAX];		// �\���e�L�X�g

	CText *m_Explain[EXPLAIN_MAX];	// ��������e�L�X�g
	CText *m_Words[TEXT_MAX];		// �e�L�X�g�\��

	String	*m_pString;		// ������
	int		nStringMax;		// ������̍ő吔

	// ���ʂ̕\���`��
	Rank m_aRank[RANK_NUM] =
	{
		"1ST",
		"2ND",
		"3RD",
		"4TH",
		"5TH",
		"6TH",
		"7TH",
		"8TH",
	};
};

#endif