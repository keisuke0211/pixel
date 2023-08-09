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
	/* �X�R�A	*/void SetScore(int nScore);

	// -- �擾 ------------------------------------------
	/* ���ʂ̕\���`���̎擾	*/char *GetRankText(int nRank) { return m_aRank[nRank].aRankText; }

private:

	// ***** �\���� *****

	// �����L���O���
	struct Info
	{
		int nScore;		// �X�R�A
	};

	struct Rank
	{
		char aRankText[TXT_MAX];	// �e�L�X�g
	};

	// ***** �֐� *****
	/* �\�[�g�~�� */void SortDesc(void);

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