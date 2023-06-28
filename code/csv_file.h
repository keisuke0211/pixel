//========================================
// 
// csvファイル処理
// 
//========================================
// *** csv_file.h ***
//========================================
#ifndef _CSV_FILE_H_	// このマクロ定義がされていなかった時
#define _CSV_FILE_H_	// 二重インクルード防止のマクロを定義する

#pragma once
#include <iostream>	// 外部の装置と入出力
#include <fstream>	// ファイル の入出力
#include <vector>
#include <string>
#include <sstream>	// カンマで区切るために必要

using namespace std;

//****************************************
// クラス
//****************************************
template <typename T>
class CSVFILE
{
public:
	string filepath;	// ファイルパス
	bool bHeader;		// ヘッダーの有無
	bool bIndex;		// インデックスの有無
	char delim;			// 区切り文字

	/* 保管 */
	vector<string> header;	// ヘッダー名
	vector<string> index;	// インデックス名
	vector<vector<T>> cell;	// 要素

	// コンストラクタ
	CSVFILE()
	{
		bHeader = false;	// ヘッダー
		bIndex = false;		// インデックス
		delim = ',';		// 区切り文字
	}

	// デストラクタ
	~CSVFILE()
	{

	}

	// *** テンプレート関数 ***
	T cast_cell(string);						// 型に応じたキャスト処理
	void csv_read(string, bool, bool, char);	// 読み込み
	void csv_write(string, char);				// 書き出し
	void csv_show(void);						// コンソール出力
};

//****************************************
// キャスト処理
//****************************************

// int型
int CSVFILE<int>::cast_cell(string str)
{
	return stoi(str);  
}

// double型
double CSVFILE<double>::cast_cell(string str)
{
	return stod(str);
}

// string型
string CSVFILE<string>::cast_cell(string str)
{
	return str;
}

//================================================================================
// 読み込み処理
// ファイルパス / ヘッダー有無 / インデックス有無 / 区切り文字
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

	// ファイルを開く (ifstreamのコンストラクタで開く)
	ifstream ifs_csv_file(filepath);

	// １行ずつ読み込む (読み込んだ内容を str_buf に格納)
	for (int nLine = 0; getline(ifs_csv_file, str_buf); nLine++)
	{
		cell.push_back(vector<T>());

		// delim 区切りごとにデータを読み込むために istringstream にする
		istringstream i_stream(str_buf);

		for (int nRow = 0; getline(i_stream, str_comma_buf, delim); nRow++)
		{
			// -- 読み込み------------------------
			if (bHeader && bIndex)
			{// ヘッダーとインデックスがある時

				/* 折り返す		*/if (nRow == 0 && nLine == 0) continue;
				/* ヘッダー		*/if (nRow == 0 && nLine != 0) header.push_back(str_comma_buf);
				/* インデックス */if (nRow != 0 && nLine == 0) index.push_back(str_comma_buf);
				/* 要素			*/if (nRow != 0 && nLine != 0) cell.at(nRow - 1).push_back(cast_cell(str_comma_buf));
			}
			else if (bHeader)
			{// ヘッダーがある時
				/* ヘッダー		*/if (nRow == 0)				header.push_back(str_comma_buf);
				/* インデックス */if (nRow != 0 && nLine == 0)	index.push_back(string());
				/* 要素			*/if (nRow != 0)				cell.at(nRow - 1).push_back(cast_cell(str_comma_buf));
			}
			else if (bIndex)
			{// インデックスがある時
				/* ヘッダー		*/if (nRow == 0 && nLine != 0)	header.push_back(str_comma_buf);
				/* インデックス */if (nLine == 0)				index.push_back(str_comma_buf);
				/* 要素			*/if (nLine != 0)				cell.at(nRow).push_back(cast_cell(str_comma_buf));
			}
			else
			{// 要素のみ
				/* ヘッダー		*/if (nRow == 0)	header.push_back(str_comma_buf);
				/* インデックス */if (nLine == 0)	index.push_back(str_comma_buf);
				/* 要素			*/					cell.at(nRow).push_back(cast_cell(str_comma_buf));
			}
		}
	}
}

//================================================================================
// 書き出し処理
// ファイルパス / 区切り文字
//================================================================================

template <typename T>
void CSVFILE<T>::csv_write(string filepath, char delim)
{
	// 書き込むファイルを開く (ofstreamのコンストラクタで開く)
	ofstream ofs_csv_file(filepath);

	if (bHeader)
	{
		for (int nRow = 0; nRow < header.size(); nRow++)
		{
			/* 空白		*/if (bIndex && nRow == 0)ofs_csv_file << delim;
			/* ヘッダー */ofs_csv_file << header.at(nRow) << delim;
		}
		ofs_csv_file << endl;
	}

	for (int nLine = 0; nLine < index.size(); nLine++)
	{
		if (bIndex)
		{
			/* インデックス */ofs_csv_file << index.at(nLine) << delim;
		}
		for (int nRow = 0; nRow < header.size(); nRow++)
		{
			/* 要素 */ofs_csv_file << cell.at(nLine).at(nRow) << delim;
		}
		ofs_csv_file << endl;
	}
	ofs_csv_file << endl;
}

//================================================================================
// コンソール出力理
//================================================================================

template <typename T>
void CSVFILE<T>::csv_show(void)
{
	/* ファイルパス			*/cout << "filepath = " << filepath << ", ";
	/* ヘッダー				*/cout << "bHeader = " << int(bHeader) << ", ";
	/* インデックス			*/cout << "bIndex = " << int(bIndex) << ", ";
	/* 要素					*/cout << "delim = " << delim << endl;
	/* ヘッダー サイズ		*/cout << "header size = " << header.size() << ", ";
	/* インデックス サイズ	*/cout << "index size = " << index.size() << endl;

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