#ifndef COMPSEARCH_H
#define COMPSEARCH_H

#include <stdio.h>


#include <iostream>
#include <rtm/CorbaNaming.h>
#include <rtm/RTObject.h>
#include <rtm/CorbaConsumer.h>
#include <assert.h>
#include <string>
#include <vector>

/*
*バイナリファイルに文字保存する関数
*/
void WriteString(std::string a, std::ofstream &ofs);
/*
*バイナリファイルより文字読み込みする関数
*/
std::string ReadString(std::ifstream &ifs);

/*
*
*/
std::string GetExtension(std::string &path);
/*
*パスよりファイル名を除く関数
*/
std::string ExtractPathWithoutExt(std::string &fn);
/*
*パスよりファイル名取得する関数
*/
std::string ExtractFileName(std::string &path);

#endif