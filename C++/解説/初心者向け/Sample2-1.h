/**
**********************************************************************
* @file		Sample2-1.h
* @brief	浅くC++言語 を学ぶためのサンプル2-1
* @date		2020/08/17
* @par		Copyright
  (c) 2019-2020 Bunya
**********************************************************************
*	@par	History
*			- 2020-08-17 Bunya
*				-# 新規作成
*
**********************************************************************
*/

// サンプル 2-1
// 大枠：列挙型、構造体、制御(if, 繰り返し)、typedef、using、namespace再び、例外、(嫌だけど)動的確保
// 命名規則：原則スネーク記法

#pragma once

namespace sample2_1 {

#pragma region 関数プロトタイプ

#pragma region 列挙型
	void func1();
#pragma endregion 列挙型

#pragma region 構造体
	void func2();
#pragma endregion 構造体

#pragma region 制御_if_繰り返し
	void func3();
#pragma endregion 制御_if_繰り返し

#pragma region typedef
	void func4();
#pragma endregion typedef

#pragma region using
	void func5();
#pragma endregion using

#pragma region namespace再び
	void func6();
#pragma endregion namespace再び

#pragma region 例外
	void func7();
#pragma endregion 例外

#pragma region (嫌だけど)動的確保
	void func8();
#pragma endregion (嫌だけど)動的確保

#pragma endregion 関数プロトタイプ
}
