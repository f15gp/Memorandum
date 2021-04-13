/**
**********************************************************************
* @file		Sample1-1.h
* @brief	浅くC言語 を学ぶためのサンプル1-1
* @date		2021/04/13
* @par		Copyright
  (c) 2019-2021 Bunya
**********************************************************************
*	@par	History
*			- 2019-07-03 Bunya
*				-# 新規作成
*			- 2021-04-13 Bunya
*				-# ミスや誤解を招く内容を訂正。
*
**********************************************************************
*/
// 大枠：関数(プロトタイプ宣言)、暗黙の型変換、キャスト、static、配列

#pragma once

/************************** 関数プロトタイプ宣言 ***************************/
// 関数プロトタイプ宣言と言って、関数の戻り値や引数が定義と異なっているか？をコンパイラがチェックするもの。
// ちなみにC言語はクラスなんてないので関数単体で存在することができます。
// 必ず関数を"使用する前"に宣言されるようにしてください。
// じゃないと、コンパイラはxxxって関数があるけど、俺このxxxの戻り値も引数も分からねぇよとお怒りになります。

// 宣言と定義
// [変数]
// int x; //<-宣言
// int x = 0; //<-宣言と定義
// [関数]
// int func(void); //<-宣言
// int func(void) //<-定義(プロトタイプ宣言がない場合は宣言も兼ねる)
// {
//     return 1;
// }

void Sample11Func1();	// 戻り値はない。引数は"何でもよい"(チェックしない)
int Sample11Func2(void);// 戻り値はint型。引数はない
int Sample11Func3(int);	// 戻り値はint型。引数はint型の変数一つ
//Sample11Func4(void);	// これダメ。C90はintの戻り値があるとみなすが、C99はエラー
// お気づきでしょうが、複数の戻り値を返すことはC言語ではできません。でも引数は複数渡せます

// [仮引数と実引数]
// 仮引数は関数定義の引数のこと。実引数は関数呼び出し時の引数のこと。
// 実引数は変数でなく直値でも良い。

// この関数プロトタイプ宣言でvoid hoge(int data);と仮引数名を書くスタイルがあります。
// ま、仕事でスタイルが強制されるなら従うしかないですがぁ、個人的には仮引数名書きません。
// 理由1:関数プロトタイプ宣言の仮引数名と関数定義の仮引数名が異なってもエラーにならないから
// 理由2:使い方が知りたいだけなので、引数名なぞどうでも良い。ヘッダに書かなくてもいいでしょ？
// 理由3:defineによって置き換えられ、コンパイルエラーを食らうことがあるから

/************************** static ***************************/
void Sample11Func4(void);
void Sample11Func5(void);

/************************** const ***************************/
void Sample11Func6(void);

/************************** 配列 ***************************/
void Sample11Func7(void);
// ちょっと2次元配列のサイズをとりたいので禁断のマクロ関数を
#define countof2(Array) (sizeof(Array[0]) / sizeof(Array[0][0]))
// ちなみにC11ではマクロ関数の代わりとなるinline関数(C++だと随分前からですが)が追加されました。
// Lv5だと上手く使えない(使わない？)でしょうから、キーワードだけ出して検索できるようにしておきます。
