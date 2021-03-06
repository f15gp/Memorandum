/**
**********************************************************************
* @file		Sample1-1.h
* @brief	浅くC++言語 を学ぶためのサンプル1-1
* @date		2020/08/12
* @par		Copyright
  (c) 2019-2020 Bunya
**********************************************************************
*	@par	History
*			- 2020-08-12 Bunya
*				-# 新規作成
*
**********************************************************************
*/

// サンプル 1-1
// 大枠：関数(参照、ポインタ、値渡し)、暗黙の型変換、キャスト、型推論、static
// 命名規則：原則スネーク記法

#pragma once

namespace sample1_1 {

#pragma region 関数プロトタイプ
	// 関数プロトタイプと言って、関数の戻り値や引数が実装と異なっているか？をコンパイラがチェックするもの。
	// ちなみにjavaやC#と違ってC, C++は関数単体で存在することができます。
	// 必ず関数を使用するより前に関数プロトタイプがあるようにしてください。じゃないと、コンパイラはxxxって関数があるけど、俺このxxxの
	// 戻り値も引数も分からねぇよとお怒りになります。
	// ※ 本当は関数の実装が宣言(プロトタイプ)を兼ねるので、使うより前方に存在してれば必ずしも関数プロトタイプは必要ないのですが、
	//    まぁ慣れるまでは必ず書くようにした方がよいでしょう。

	void func1();	// C++では仮引数が()はvoid扱い。
					// ただし、C言語だと引数は何でも良いになって型チェックが行われないので注意。

	void func2();

	int func3(int);	// プロジェクトによっては引数のintに仮引数名を付けることがある。が、そういう縛りがない限り、変数名は書くな。
					// なぜなら、プロトタイプ宣言での引数名と実装の引数名が異なってもコンパイラは警告やエラーにしない。
					// 引数名を付ける人たちは"ヘッダを見るだけで何となく使い方が分かるだろ？"なんてことを言ったりするが、
					// 本当の実装と異なってたら混乱の元になるだけだ。
					// ※ 第一使い方はインターフェース仕様書に書かれているべきで分かりやすい変数名書いたから、だからなんだっての
					//
					// それと、プロトタイプ宣言と関数実装での引数名は、defineにより書き換えられるので不思議なエラーになったりする。
					// それを防ぐためにもdefineはすべて大文字の慣習になったんだと思うが、変数名の命名規則によってはねぇ・・・

	//func3(int); <-これアウト。C89, C95だと暗黙的にintを返すと仮定されてOKなのだけど、C99以降のC言語とC++はエラー

#pragma region 参照_ポインタ_値渡し
	void func4(int&);
	void func5(const int&);
	void func6(int*);
	void func7(int);
#pragma endregion 参照_ポインタ_値渡し

#pragma region 型推論
	void func8();
#pragma endregion 型推論

#pragma region static
	void func9();
#pragma endregion static

#pragma endregion 関数プロトタイプ

}
