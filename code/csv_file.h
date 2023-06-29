//========================================
// 
// csv�t�@�C������
// 
//========================================
// *** csv_file.h ***
//========================================
#ifndef _CSV_FILE_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _CSV_FILE_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

#pragma once
#include <iostream>	// �O���̑��u�Ɠ��o��
#include <fstream>	// �t�@�C�� �̓��o��
#include <vector>
#include <string>
#include <sstream>	// �J���}�ŋ�؂邽�߂ɕK�v

using namespace std;

//****************************************
// �N���X
//****************************************
template <typename T>
class CSVFILE
{
public:
	string filepath;	// �t�@�C���p�X
	bool bHeader;		// �w�b�_�[�̗L��
	bool bIndex;		// �C���f�b�N�X�̗L��
	char delim;			// ��؂蕶��

	/* �ۊ� */
	vector<string> header;	// �w�b�_�[��
	vector<string> index;	// �C���f�b�N�X��
	vector<vector<T>> cell;	// �v�f

	// �R���X�g���N�^
	CSVFILE()
	{
		bHeader = false;	// �w�b�_�[
		bIndex = false;		// �C���f�b�N�X
		delim = ',';		// ��؂蕶��
	}

	// �f�X�g���N�^
	~CSVFILE()
	{

	}

	// *** �e���v���[�g�֐� ***
	T cast_cell(string);						// �^�ɉ������L���X�g����
	void csv_read(string, bool, bool, char);	// �ǂݍ���
	void csv_write(string, char);				// �����o��
	void csv_show(void);						// �R���\�[���o��
};

//****************************************
// �L���X�g����
//****************************************

// int�^
int CSVFILE<int>::cast_cell(string str)
{
	return stoi(str);  
}

// double�^
double CSVFILE<double>::cast_cell(string str)
{
	return stod(str);
}

// string�^
string CSVFILE<string>::cast_cell(string str)
{
	return str;
}

//================================================================================
// �ǂݍ��ݏ���
// �t�@�C���p�X / �w�b�_�[�L�� / �C���f�b�N�X�L�� / ��؂蕶��
//================================================================================
template <typename T>
void CSVFILE<T>::csv_read(string filepath, bool bHeader, bool bIndex, char delim)
{
	this->filepath = filepath;
	this->bHeader = bHeader;
	this->bIndex = bIndex;
	this->delim = delim;

	string str_buf;
	string str_comma_buf;

	// �t�@�C�����J�� (ifstream�̃R���X�g���N�^�ŊJ��)
	ifstream ifs_csv_file(filepath);

	// �P�s���ǂݍ��� (�ǂݍ��񂾓��e�� str_buf �Ɋi�[)
	for (int nLine = 0; getline(ifs_csv_file, str_buf); nLine++)
	{
		cell.push_back(vector<T>());

		// delim ��؂育�ƂɃf�[�^��ǂݍ��ނ��߂� istringstream �ɂ���
		istringstream i_stream(str_buf);

		for (int nRow = 0; getline(i_stream, str_comma_buf, delim); nRow++)
		{
			// -- �ǂݍ���------------------------
			if (bHeader && bIndex)
			{// �w�b�_�[�ƃC���f�b�N�X�����鎞

				/* �܂�Ԃ�		*/if (nRow == 0 && nLine == 0) continue;
				/* �w�b�_�[		*/if (nRow == 0 && nLine != 0) header.push_back(str_comma_buf);
				/* �C���f�b�N�X */if (nRow != 0 && nLine == 0) index.push_back(str_comma_buf);
				/* �v�f			*/if (nRow != 0 && nLine != 0) cell.at(nRow - 1).push_back(cast_cell(str_comma_buf));
			}
			else if (bHeader)
			{// �w�b�_�[�����鎞
				/* �w�b�_�[		*/if (nRow == 0)				header.push_back(str_comma_buf);
				/* �C���f�b�N�X */if (nRow != 0 && nLine == 0)	index.push_back(string());
				/* �v�f			*/if (nRow != 0)				cell.at(nRow - 1).push_back(cast_cell(str_comma_buf));
			}
			else if (bIndex)
			{// �C���f�b�N�X�����鎞
				/* �w�b�_�[		*/if (nRow == 0 && nLine != 0)	header.push_back(str_comma_buf);
				/* �C���f�b�N�X */if (nLine == 0)				index.push_back(str_comma_buf);
				/* �v�f			*/if (nLine != 0)				cell.at(nRow).push_back(cast_cell(str_comma_buf));
			}
			else
			{// �v�f�̂�
				/* �w�b�_�[		*/if (nRow == 0)	header.push_back(str_comma_buf);
				/* �C���f�b�N�X */if (nLine == 0)	index.push_back(str_comma_buf);
				/* �v�f			*/					cell.at(nRow).push_back(cast_cell(str_comma_buf));
			}
		}
	}
}

//================================================================================
// �����o������
// �t�@�C���p�X / ��؂蕶��
//================================================================================

template <typename T>
void CSVFILE<T>::csv_write(string filepath, char delim)
{
	// �������ރt�@�C�����J�� (ofstream�̃R���X�g���N�^�ŊJ��)
	ofstream ofs_csv_file(filepath);

	if (bHeader)
	{
		for (int nRow = 0; nRow < header.size(); nRow++)
		{
			/* ��		*/if (bIndex && nRow == 0)ofs_csv_file << delim;
			/* �w�b�_�[ */ofs_csv_file << header.at(nRow) << delim;
		}
		ofs_csv_file << endl;
	}

	for (int nLine = 0; nLine < index.size(); nLine++)
	{
		if (bIndex)
		{
			/* �C���f�b�N�X */ofs_csv_file << index.at(nLine) << delim;
		}
		for (int nRow = 0; nRow < header.size(); nRow++)
		{
			/* �v�f */ofs_csv_file << cell.at(nLine).at(nRow) << delim;
		}
		ofs_csv_file << endl;
	}
	ofs_csv_file << endl;
}

//================================================================================
// �R���\�[���o�͗�
//================================================================================

template <typename T>
void CSVFILE<T>::csv_show(void)
{
	/* �t�@�C���p�X			*/cout << "filepath = " << filepath << ", ";
	/* �w�b�_�[				*/cout << "bHeader = " << int(bHeader) << ", ";
	/* �C���f�b�N�X			*/cout << "bIndex = " << int(bIndex) << ", ";
	/* �v�f					*/cout << "delim = " << delim << endl;
	/* �w�b�_�[ �T�C�Y		*/cout << "header size = " << header.size() << ", ";
	/* �C���f�b�N�X �T�C�Y	*/cout << "index size = " << index.size() << endl;

	if (bHeader)
	{
		for (int nRow = 0; nRow < header.size(); nRow++)
		{
			if (bIndex && nRow == 0) cout << "\t";
			cout << header.at(nRow) << "(h)" << "\t";
		}
		cout << endl;
	}
	for (int nLine = 0; nLine < index.size(); nLine++)
	{
		if (bIndex)
		{
			cout << index.at(nLine) << "(i)" << "\t";
		}
		for (int j = 0; j < header.size(); j++)
		{
			cout << cell.at(nLine).at(j) << "\t";
		}
		cout << endl;
	}
	cout << endl;
}
#endif