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
	static const char* FILE_PATH;		// �ǂݍ��ރt�@�C���p�X
	static const int RANK_NUM = 8;		// ���ʐ�
	static const int NAME_NUM = 3;		// �����L���O�̂̕�����

// �����L���O���̕�������
// �����L���O���̕������
// �����L���O���̊J�n����
#define RANKING_NAME_MIN_CHAR	('0')
#define RANKING_NAME_MAX_CHAR	('Z' + 1)
#define RANKING_NAME_START_CHAR	('A')

#define BLINK_TIME	(4)						// �_�Ŏ���
#define BLINK_COLOR	Color{243,189,63,255}	// �����L���O�t���[���̓_�ŐF
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
	/* �����o��		*/void Save(void);
	/* ����			*/static CRanking *Create(void);

	// -- �ݒ� ------------------------------------------
	/* �X�R�A	*/int SetScore(int nScore);

	// -- �擾 ------------------------------------------
	/* ���ʂ̕\���`���̎擾	*/char *GetRankText(int nRank) { return m_aRank[nRank].aRankText; }

private:

	// ***** �\���� *****

	// �����L���O���
	struct Info
	{
		int nScore;				// �X�R�A
		char *aName[TXT_MAX];	// ���O 
	};

	struct Rank
	{
		char aRankText[TXT_MAX];	// �e�L�X�g
	};

	struct Ranking
	{
		int							nCounterState;	// ��ԃJ�E���^�[
		float						fAlpha;			// �S�̂̓����x
		D3DXVECTOR3					pos;			// �ʒu
		bool						bNameEntry;		// ���O����
		int							nCountName;		// ���O�J�E���g
		int							nCountChar;		// �����J�E���g
		int							nUpdateRank;	// �X�V����
		int							nCounterBlink;	// �_�ŃJ�E���^�[
	};

	// ***** �֐� *****
	/* �\�[�g�~�� */void SortDesc(int *nUpdateRank);

	// ***** �ϐ� *****
	Info m_Info[RANK_NUM];		// �����L���O���
	CText *m_Text[RANK_NUM];	// �e�L�X�g

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