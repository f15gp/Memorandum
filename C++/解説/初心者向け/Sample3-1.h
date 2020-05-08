// サンプル 3-1
// 大枠：STL、ラムダ、テンプレートとか
// 命名規則：原則スネーク記法

#pragma once

namespace sample3_1 {

#pragma region 関数プロトタイプ

#pragma region array_vector_list
	void func1();
#pragma endregion array_vector_list

#pragma region string_regex
	void func2();
#pragma endregion string_regex

#pragma region map_unordered_map
	void func3();
#pragma endregion map_unordered_map

#pragma region unique_ptr
	void func4(int);
#pragma endregion unique_ptr

#pragma region function
	void func5();
#pragma endregion function

#pragma region thread_async
	void func6();
#pragma endregion thread_async

#pragma region アルゴリズム
	void func7();
#pragma endregion アルゴリズム

#pragma region テンプレート
	/// <summary>
	/// まぁなくてもいいかなぁと思ったんだけど、テンプレートの超さわりだけを
	/// 最強？の黒魔法ｗ
	/// </summary>
	template <typename T>
	auto func8(T x, T y)
	{
		return x * y;
	}
#pragma endregion テンプレート

#pragma endregion 関数プロトタイプ

}