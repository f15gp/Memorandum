/**
**********************************************************************
* @file		Sample0-Global.cpp
* @brief	浅くC++言語 を学ぶためのSample0(実装)
* @date		2019/06/23
* @par		Copyright
  (c) 2019-2019 Bunya
**********************************************************************
*	@par	History
*			- 2019-06-23 Bunya
*				-# 新規作成
*
**********************************************************************
*/

// 大枠：グローバル、変数、定数、名前空間

#include "Sample0-Global.h"

const int loop_max = 100;
const char c_loop_max = 100;
const wchar_t wc_loop_max = L'w';	// wchar_tはワイド文字列を表すのでLが先頭につく
const short s_loop_max = 100;
const int i_loop_max = 100;
const long l_loop_max = 100;
const long long ll_loop_max = 100;
const float f_loop_max = 100.0;
const double d_loop_max = 100.0;
const long double ld_loop_max = 100.0;
const bool b_loop_max = true;

// 文字列定数(std::stringの方が良いと思うけどね)
const char* str_loop_max = "C++";

// リテラル(プレフィックス、サフィックスは。。。自分で調べて)
// C++には数値、文字リテラルとして次のものがあります
int a = 0;			// 10進数リテラル
int b = 0x0;		// 16進数リテラル(0xから始まる数値)
int c = 072;		// 8進数リテラル。左は10進で58.0から始まって残りがすべて0-7の並びが続く数値
int d = 0b11;		// 2進数リテラル。0bから始まって、0-1の並びが続く数値
int e = 1'000'000;	// 数値リテラルの区切り。整数と小数で任意に区切れる

char f[] = R"(sample\ttt)";	// 生文字列リテラル。R"()"の()の中ではエスケープシーケンスを無視する。パスや正規表現で使用

/************************** 補足 ***************************/
// 一つ補足
// constのないglobal変数(ソース側で定義する前提)は、果たしてC++でどういう扱いでしょう？
// ↓を見てちょ。この中の内、他のファイルから参照できるのはさてどれでしょう？
#if 0
extern int x = 10;
int y = 20;
static int z = 30;
#endif
// 正解は、
// そのままだと、どれも参照できません。
// 参照したいファイル側で↓のようにしないといけません。
#if 0
extern int x;
extern int y;
extern int z;
#endif
// だけど、zだけは参照できません。
// それはstaticが付いているからです。staticが付いているためファイル内だけのグローバル変数扱いになっています。
// ま、そんなにglobal変数使うことないと思うので、必要な時に見直せばいんじゃないかなぁ。使わないからすぐ忘れるし
