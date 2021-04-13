/**
**********************************************************************
* @file		Sample3-1.cpp
* @brief	浅くC++言語 を学ぶためのサンプル3-1(実装)
* @date		2021/04/13
* @par		Copyright
  (c) 2019-2021 Bunya
**********************************************************************
*	@par	History
*			- 2020-08-19 Bunya
*				-# 新規作成
*			- 2021-04-13 Bunya
*				-# ミスや誤解を招く内容を訂正。
*
**********************************************************************
*/

// サンプル 3-1
// 大枠：STL、ラムダ、テンプレートとか
// 命名規則：原則スネーク記法

#include "Sample3-1.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <array>
#include <vector>
#include <list>
#include <string>
#include <regex>
#include <map>
#include <unordered_map>
#include <memory>
#include <utility>
#include <thread>
#include <future>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>

namespace sample3_1 {

	// STLはStandard Template Libraryの略
	// C++の黒魔法？たるtemplateを使って作られた汎用ライブラリ。使えないと、C++er Level 0すら超えられない(ま、現場で知らない人が3割はいる気がするが)
	// それに知っててもvectorだけだったりね。。。
	// よーし、とりあえずコンテナってのに行っちゃうぞ
#pragma region array_vector_list
	/// <summary>
	/// array, vector, listサンプル。以上
	/// </summary>
	void func1()
	{
		std::array<int, 10> ar{};	// int型の配列 10個
		std::vector<int> vec;		// int型の可変長配列。C#のListと同じ
		std::list<int> list;		// int型の双方向連結リスト。vectorに対して途中の削除、追加が多い場合に使う。
									// 片方向連結リストもあるんだが、必要ならそっちつかいなぁ

		ar.at(0) = 10;				// ar[0]に10を入れるのと同義
		vec.push_back(11);			// vecに1要素追加。追加した要素の値は11。emplace_backってのもあるんだが、使いこなすのはねぇ
		list.push_back(12);			// listに1要素追加。追加した要素の値は12

		// vectorは領域が足りなくなると倍々ゲームに近いノリで動的確保を行います。
		// んで、現在vectorの領域は連続してることを保証しなければならないので、
		// 領域再確保の時はメモリの再配置、データのコピーなんかが必要になってきます。
		// なので、最初からこの程度は追加を行うってのが分かっているならreserveとかコンストラクタで指示してください。
		//
		// あ、余談ですが、小さなデータをチマチマ確保するのってC++はC#やJavaに劣っているので、ご注意を。
		// 逆に大きなデータになるとC++の方がガッツリ早くなりますけど。

		// 生データがほしい(arrayとvector限定。listはリスト構造なんで連続した領域を持たない)
		// あえてポインタをｗ (なんで、生データかというと、この2つはoldスタイルの関数に渡したりするときにポインタが必要
		// なことが往々にしてあるから)
		int* p = ar.data();
		for (std::size_t i = 0; i < ar.size(); i++) {
			std::cout << p[i] << std::endl;
		}
		p = vec.data();
		for (std::size_t i = 0; i < vec.size(); i++) {
			std::cout << p[i] << std::endl;
		}
		// listをくるくるループしたいならイテレータでよろしく

		// 他にもメソッドいっぱいだから自分で調べて

		// 当然これら(array, vector, list)はスコープを外れる時に内部で確保した領域は自動的に解放される
	}
#pragma endregion array_vector_list

#pragma region string_regex
	/// <summary>
	/// string, regexのサン ry)
	/// </summary>
	void func2()
	{
		// C++で文字列と言ったらstd::stringだしょ位に文字列で使う。使うの前提みたいな
		std::string str = "I seemd like Mr.bunya is always tired.";
		std::cout << str << std::endl;

		// 連結とか
		std::string str2 = str + " but he is funny unless his face.";
		std::cout << str2 << std::endl;

		std::string str3 = std::to_string(12);	// 数値を文字列へ
		char str4[128] = { '\0' };
		sprintf_s(str4, "%s %s", str3.c_str(), str2.c_str() );
		// c_str()はC言語形式の文字列への変換。
		// sprintf_sはVS2005から追加(セキュリティのために)されたものでバッファのサイズを付与するもの。元はsprintf
		std::cout << str4 << std::endl;
		
		// ま、検索とかそういうのもstringに使えるのですけども、いっぱいあるから各自見てみてと

		// んじゃ、C++11で入った正規表現と
		// C++は以前文字列の扱いがへぼすぎると酷評されてましたが正規表現が入ったので大分マシになったかと
		std::cout << std::regex_search(str2, std::regex("bunya")) << std::endl;	// regex_searchは部分一致。"bunya"の代わりに正規表現を持ってくる場合、R文字列を指定したらいんじゃない？
		std::cout << std::regex_search(str3, std::regex(R"(\d)")) << std::endl;	// こんな感じで。エスケープシーケンス無視できるし
	}
#pragma endregion string_regex

#pragma region map_unordered_map
	/// <summary>
	/// std::mapに独自オブジェクトを入れるならソートするために比較演算子が必要になる。
	/// そしたらそこにjave野郎共に大不評の演算子オーバーロードが必要になるって話ですよ。
	/// 演算子オーバーロードが出来たのは、こうやって独自定義オブジェクトを標準提供のものと同じように
	/// ふるまえるようにできないか？というのが、そもそもの発端なわけです。
	/// ・・・でもさ、<とか+とか-とかっていうのをオーバーロードしてないだけでさ、Javaだって
	///      Equals()、GetHashなんちゃら、CompareToってのをオーバーロードするよね？同じじゃね？
	///      グローバル変数、gotoなんかと同じで実質的にやることが同じでも、名称が違うだけで別物だって叫ぶ考え方が多すぎる気がするねぇ
	/// </summary>
	struct map_sample {
		int x = 10;
		int y = 11;

#if 1
		// #ifが0で↓の関数が死んじゃうとstd::mapへのinsertでエラーが起きます。
		// なぜかというとmapのinsertを行う際に、<で比較する処理を見つけれなくなるからです。
		// std::mapに自作インスタンスを突っ込みたかったら、operatorとかの知識が必須です。
		// だけど、secondたる値の方に入れるなら特に知らなくてもOK。なぜならstd::mapはキーを比較基準にするんで
		bool operator<(const map_sample& rhs) const	// ここのconstはクラス編でちゃんと説明する予定だぞ(ハート)
		{
			// あ、thisってのは自分自身を指すポインタね。
			// 別にメンバ関数だからメンバ変数に対して明示する必要もないけど、とりあえず使ってみた
			return this->x < rhs.x;
		}
#endif
	};

	/// <summary>
	/// std::map, std::unordered_mapのサン ry)
	/// </summary>
	void func3()
	{
		std::map<int, std::string> mapper{		// キーをint型、値をstd::stringとした木構造。std::mapはC#のDictionaryと同じ
			{3, "hoge"},
			{4, "hogehoge"},
			{6, "hopper"},
		};
		// えーと、std::mapは大抵std::pairと一緒に用いられます。
		// かつキーをstd::stringにして、valueを関数ポインタ(or std::function)にすると面白いことが出来る。
		// とりあえずここではそんなこと無視してデータをinsertする
		mapper.insert(std::make_pair<int, std::string>(1, "mapper"));

		// 一つ注意
		// std::mapは必ずデータ挿入のたびにソートするので、ソートが必要なかったらstd::unordered_mapを使うこと。
		// あと、もし存在しないデータに対して[]演算子でアクセスした場合は自動的にその要素を追加するんで、注意ね。

		// キー4で検索かけてみて、あれば表示しますわ。
		// んでキーはfirst, 値はsecondってことに決まってる。find()はそのまんまで値を検索キーにして探索を行う
		auto it = mapper.find(4);
		if (it != std::end(mapper)) {
			std::cout << it->second << std::endl;
		} else {
			std::cout << "not exists" << std::endl;
		}

		// ↓を動かすとソートされてるのもわかるだろ。これは独自オブジェクトのソートを行うサンプルね
		std::map<map_sample, int> mapper2;
		mapper2.insert(std::make_pair<map_sample, int>({ 5, 11 }, 109));
		mapper2.insert(std::make_pair<map_sample, int>({ 3, 12 }, 111));

		// データ挿入時のソートがないから追加、削除が早いよってだけだが、一応ね
		std::unordered_map<std::string, int> unordered{ { "1st", 1 },{ "2nd", 2 },{ "3rd", 3 }, };
		std::cout << "3rd:" << unordered.at("3rd") << std::endl;	// まぁfindを使わなくてもキーを指定したらvalueが取れるんだけどねｗ
	}
#pragma endregion map_unordered_map

#pragma region unique_ptr
	/// <summary>
	/// スタックあふれちゃうよー。てな時に使うスマートポインタなやつ。unique_ptrだ。
	/// いや、本当は他にもポリモーフィズムとかにも使ったりするのですが、Lv5ならまずはスタックオーバーフロー防止の
	/// ポインタ代わりとしてねとね
	/// </summary>
	void func4(int placed_size)
	{
		auto protected_overflow = std::make_unique<int[]>(placed_size);
		// 100個(呼び出し元が100を指定してるので)のint型配列を確保する。でも、これ位のサイズなら普通の配列でOK...
		// このunique_ptrはコピーができず、moveしか許されてない。排他的アクセスも考慮されないのでお気を付けを。
		// ただ、一時的にオブジェクトを動的に確保するのには使えるので、まぁいんじゃない？
		// でも、こいつサイズを教えてくれないから自分で覚えておくしかないけどさ。。。
		// 昔のC言語と違って動的確保サイズを外部から与える引数で指定できちゃうのが良いところではあるけんど

		protected_overflow[3] = 15;
		auto p = protected_overflow.get();		// get()するとポインタが取得できるんで。forを使う理由？だって、unique_ptrの配列はrange-based-forできないんだもん。
		for (int i = 0; i < placed_size; i++) {
			if (p[i] != 0) {
				std::cout << "hit! n = " << (i + 1) << std::endl;
			}
		}

		// どうしても配列風なのをrange-based-forしたいんじゃーな向きでは以下のようにvector+unique_ptrのコンビネーションアーツを
		std::vector<std::unique_ptr<int>> vectors_overflow;
		for (int i = 0; i < placed_size; i++) {
			vectors_overflow.emplace_back(std::make_unique<int>(i+1));
		}
		for (const auto& elem : vectors_overflow) {
			if ((*elem % 10) == 0) {
				std::cout << "10刻み？ n = " << *elem << std::endl;
			}
		}

		// 関数を抜ける時に自動的に領域は解放される。
		// が、逆に自動解放全般に言えるが、例えばforの中の処理で毎回宣言するように書いちゃいけません。
		// さすがにそれだとforの1回のループが終わる度に解放、で次のループで確保が繰り返されるのでシャレになりませーん。

		// でも、スタックオーバーフロー防止のポインタ代わりなら配列じゃなくて変数だから上の説明とは・・・
		// 。。。まぁ使う機会あるんだし、いいか
	}
#pragma endregion unique_ptr

#pragma region function

	/// <summary>
	/// 関数ファンクタの説明用
	/// </summary>
	struct functor
	{
		// ↓が関数ファンクタ。各クラス、構造体の()呼び出しで呼び出される関数をそう呼ぶ
		void operator()(int x)
		{
			std::cout << (x * 10) << std::endl;
		}
	};

	/// <summary>
	/// 関数オブジェクトの説明用
	/// </summary>
	/// <param name="x">引数1</param>
	void func_pointer(int x)
	{
		std::cout << (x * 10) << std::endl;
	}

	/// <summary>
	/// コンテナじゃない気がする(でも、持ち運べるしぃ)けど、重要なのでアルゴリズムより先にfunctionについて
	/// ついでに関連する関数ファンクタやラムダ式もね。for_eachもからめちゃおっかな
	/// </summary>
	void func5()
	{
		// ま、まずはラムダについて述べてみようか。
		auto func_lamda = [](auto x){ return x + 2; };	// これは最小のラムダ式じゃありません。
		// 戻り値は引数の+2ってなラムダですわ。詳しく知りたければ、各自調べん ry)
		// ・・・ごほん。これだけだとちょっと酷いので書式だけ書いておこう。
		// [キャプチャー句](パラメータリスト) mutable throw() -> 戻り値 {本体}
		// キャプチャー句: = 外部の変数をコピーしてアクセス & 外部の変数を参照でアクセス。省略可能(=外部の変数に触らない)
		// パラメータリスト: 引数。省略可能
		// mutable: キャプチャした変数のconstを外すので、変数を変更できるようにする。でもオリジナルは変更できない。省略可能
		// throw(): ラムダが例外を投げないと宣言。投げたら警告。省略可能
		// ->: 戻り値を推論させる場合、戻り値ともども省略する。逆に戻り値を書く時は省略不可
		// 戻り値: 戻り値。型を明示しなくてautoと書けばOK
		// 本体: ラムダの処理

		// さぁ、まずは使ってみるか。ほれ、普通に関数呼び出し的に使えてるじゃろ？
		auto x = func_lamda(10);
		std::cout << x << std::endl;

		// あ、そうそう。↓の{}ってのは統一初期化っていうもので、指定値で初期化したvector(下だとサイズ 5つ)を作成します。
		// 配列とかlistとかでも使える。独自クラスも(実装すれば)使える。一応実装したものはクラスの所で説明予定
		// ちなみに引数や戻り値にもこの統一初期化は使える。。。
		std::vector<int> vec{ 1, 2, 3, 4, 5 };

		// ほいじゃ、まぁ関数ファンクタを使おうかね
		// アルゴリズムのfor_eachを使う。for_eachは指定された位置(先頭ではない)から終了までを指定された処理で繰り返す。
		// ここではfunctorの関数ファンクタを割り当てているのでvecの中身が10倍されたものを表示する。
		std::for_each(std::begin(vec), std::end(vec), functor());

		// 当然 for_eachの処理にはラムダが使える(関数ファンクタとあえて同じ処理にしてみた)
		std::for_each(std::begin(vec), std::end(vec), [](int x) {
			std::cout << (x * 10) << std::endl;
		});

		// 関数ファンクタの存在理由は、それが一番最適化がかかったからです(それだけじゃないけど無視)。
		// でも、関数ファンクタの問題は、1クラスに一つしか定義できないこと。だから、関数ファンクタの為だけに、適当なクラス名を考えるのが大変だし、プロジェクト規則
		// に触れる場合だってあるだろう。そんなわけでラムダを使うのを推奨するのだが、、、プロジェクト規則や何度も使う処理ならきちんと関数を用意して、
		// それを関数オブジェクト(ラムダとかもここに属してるのですけぇーど)に取り込むのが一番いい。関数オブジェクトはstd::functionを使う。

		auto func_obj = func_pointer;	// 型推論しない場合はこうかく。std::function<void(int)> func_obj;
										// <戻り値(引数)>ってなもんだ
		func_obj(3);
		// func_objの引数はfor_eachによって与えられる。なれないとちょっと分かりにくいかもねぇ
		std::for_each(std::begin(vec), std::end(vec), func_obj);

		// こんなわけで関数オブジェクトたるfunc_objには void xxx(int)の型を持つ関数とかラムダ式とかをいくらでも代入可能です、変数なので。
		// ただ、まぁその場限りで使うなら、ラムダでいいし、ちょっとだけラムダと比べて余分な処理をする関係上、速度が多少遅い。
		// ま、そんなこたぁ気にするほどじゃないと思うけど。
		// クラスのメンバ関数についても可能。それは元々std::mem_fnというものだったし、引数を束縛するstd::bindってのもあるが、
		// どちらもstd::functionで済ますことも出来ちゃう(場合によっては、複合技になることがあるけど)

		// ま、これ位が基本かな
	}
#pragma endregion function

#pragma region thread_async

	/// <summary>
	/// thread用に実装。単に0-99までの乱数を1000000回発生させてみるだけの処理
	/// </summary>
	void thread_func()
	{
		std::random_device rd_seed;			// ハードウェア状態で決める乱数
		std::mt19937 rander(rd_seed());		// メルセンヌツイスター法(MT法) 32bit長符号なし整数型の乱数
		std::uniform_int_distribution<> range_rander(0, 99);	// 0から99までを等確率で返してくる
		int a;
		int b = 0;	// bは最適化防止のため。本当に頭が良いコンパイラならループをなかったことにするはず。
					// なぜなら、aの値はループを抜けると全く使われないので、このループは不要と判断する可能性が高いから

		auto start = std::chrono::system_clock::now();
		for (int32_t i = 0; i < 1000000; i++) {
			a = range_rander(rander);
			if (b < a) {
				b = a;
			}
		}
		auto end = std::chrono::system_clock::now();

		// 多分早いPCなら1秒もかかるはずはない(最適化がかかるRelease版だと間違いなく)のだが、とりあえず秒単位に換算
		std::cout << "maximum numeric is " << b << std::endl;
		std::cout << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()	<< "sec" << std::endl;
	}

	/// <summary>
	/// async用に実装。ファイルを読み込む
	/// </summary>
	/// <param name="file">ファイルパス</param>
	/// <returns>ファイルデータ</returns>
	/// <exception cref="runtime_error">ファイル例外</exception>
	auto async_func(std::string file)
	{
		std::ifstream ifs(file, (std::ifstream::ate|std::ifstream::binary));

		// ファイルが開けたかどうか確認
		if (!ifs) {
			// でも呼び出し元は例外とるの面倒なのでとってないというｗ
			throw std::runtime_error("file open failed.");
		}

		// ファイルサイズ取る
		auto file_size = ifs.tellg();
		ifs.seekg(0, std::ifstream::beg);

		// 読む。ただのサンプルだから手抜きですけど、扱えるファイルのサイズを無言で規定してる処理であることに注意
		std::vector<char> buf(static_cast<const unsigned int>(file_size));
		ifs.read(buf.data(), file_size);

		// あ、これでRVOとかNRVOが発動するの確実なのでstd::vectorをそのままreturnすりゃいいよ
		return buf;
	}

	/// <summary>
	/// C#やjavaの人からけちょんけちょん？にされる
	/// スレッドやら非同期専用のasyncが追加された。
	/// ま、C++で書くような分野なら非同期当たり前でしょうが、一応標準ライブラリで扱えるようになったぞっと
	/// </summary>
	void func6()
	{
		// ほいじゃ、メジャーなスレッドの方から
		// 時間かかる乱数でも発生させてみる
		auto th1 = std::thread(thread_func);
		std::cout << "スレッド スタート" << std::endl;
		th1.join();	// 直ぐ待ち合わせしてるので非同期でもなんでもねぇけどｗ
		// ラムダを入れれて、std::vector<std::thread>のようにコンテナにもぶちこめるっす。おす

		// んじゃ、非同期処理専用のasyncね
		auto fread = std::async(std::launch::async | std::launch::deferred, async_func, "Sample2-1.cpp");
		// ここで何かを処理したとして(deferred(遅延評価)指定のせいでまだ処理は始まってない)
		auto result = fread.get();	// ここで実際の処理と待ち合わせが発動。もし例外を取るなら、ここで取る。だってdererredですから
		// せっかくなのでファイルの中身を表示してみるか
		// でもみたいときだけにしてね(じゃないとコマンドプロンプトがファイルの中身で埋め尽くさ ry))
#if 0
		for (const auto& data : result) {
			std::cout << data;
		}
		std::cout << std::endl;
#endif
	}
#pragma endregion thread_async

#pragma region アルゴリズム
	// STLのコンテナと双璧をなすアルゴリズムを。だけんど、昔に基礎が作られたので結構イテレータの知識が前提みたいな。
	// ここで紹介する奴以外の方が多いので、各自調べてみたら。むしろ、ほんの触りしか書いてないともいう。
	// ちなみにbegin、end、sortとかは各コンテナにメンバ関数として用意されてる場合がある。
	// ちょぅとだけそっちの方が早かったりするけど、ま、どのコンテナにもアルゴリズムは適用できるので、
	// アルゴリズムの側を使うんだってスタンスでとりあえず下は記載してる
	// ※ begin,endに対してconstの扱いとなるcbegin, cendもあるよー

	void func7()
	{
		// 固定のサイズなのでarrayでいんだけど、削除のアルゴリズムとかも扱うので便宜的にvectorで
		std::vector<int> vec1{ 1, 2, 3, 7, 8, 1, 10, 15, 17, 1 };

		// count 読んで字のごとし。指定値と同じのをコンテナから探して数える
		std::cout << std::count(std::begin(vec1), std::end(vec1), 1) << std::endl;

		// アルゴリズムのxx_ifは、イテレータを返します。

		// remove_if(指定した値だけを削除するremoveもある)
		// remove_ifは指定した値の要素を削除(ちょっと語弊があるけど)する。でもサイズは変わらない。本当に消すならeraseを使う
		auto vec2 = vec1;
		auto result1 = std::remove_if(std::begin(vec2), std::end(vec2), [](auto x) { return x % 2; });
		std::for_each(std::begin(vec2), result1, [](auto x) { std::cout << x << ","; });
		std::cout << std::endl;
		// eraseで本当に消える
		std::cout << "before size: " << vec2.size() << std::endl;
		vec2.erase(result1, std::end(vec2));
		std::cout << "after size: " << vec2.size() << std::endl;

		// find_if(条件に合致する最初の要素を探す)
		auto result2 = std::find_if(std::begin(vec1), std::end(vec1), [](auto x) { return x > 10; });
		if (result2 != std::end(vec1)) {
			std::cout << *result2 << std::endl;
		}

		// minmax_element 読んで字の ry)
		auto result3 = std::minmax_element(std::begin(vec1), std::end(vec1));
		std::cout << "min: " << *result3.first << " max: " << *result3.second << std::endl;

		// fill 指定した値で全要素を埋める
		auto vec3 = vec1;
		std::fill(std::begin(vec3), std::end(vec3), 5);

		// accumulate 総和を求める
		int sum = std::accumulate(std::begin(vec1), std::end(vec1), 0);

		// sort デフォは昇順とな
		std::sort(std::begin(vec1), std::end(vec1));
		for (const auto& prt : vec1) {
			std::cout << prt << ", ";
		}
		std::cout << std::endl;
		// 当然降順にしたいとかあるデータをキーにしたソートをしたいとかなら比較関数をラムダとかでどうぞ
		// 安定したソートが必要ならstable_sortを使ってちょ
	}
#pragma endregion アルゴリズム
}
