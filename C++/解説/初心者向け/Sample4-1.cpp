/**
**********************************************************************
* @file		Sample4-1.cpp
* @brief	浅くC++言語 を学ぶためのサンプル4-1(実装)
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

// サンプル 4-1
// 大枠：クラス
// 命名規則：原則スネーク記法

#include <iostream>
#include <string>

#include "Sample4-1.h"

namespace sample4_1 {

#pragma region 4_1_1
	/// <summary>
	/// private指定の関数ね
	/// </summary>
	/// <returns>private変数bを3倍する</returns>
	int class_0::func2()
	{
		return b * 3;
	}
#pragma endregion 4_1_1

#pragma region hoge_4_1_7
	int hoge_4_1_7_1::func1(int x)
	{
		return x * 3;
	}
	int hoge_4_1_7_1::func2()
	{
		return 15;
	}

	int hoge_4_1_7_2::func1(int x)
	{
		return x * 5;
	}
	int hoge_4_1_7_2::func2()
	{
		return 25;
	}
#pragma endregion hoge_4_1_7

#pragma region 実際の使い方
	int hoge_4_1_6::b = 11;	// 4-1-6に出てくるstaticメンバ変数の初期化です。うざいよね、これ

	void func1()
	{
		class_0 a;			// class_0のインスタンスを用意しました
		a.a = 2;			// public変数なら直接代入したりできる
		a.func1(4);			// public関数はインスタンス経由で呼び出せる
		//a.b = 4;			// private変数は触れません
		//a.func2();		// private関数は呼び出せません

		hoge_4_1_2 b;
		b.a();				// 継承の説明だけ

		hoge_4_1_5 c(5);
		hoge_4_1_5 d = std::move(c);	// ちゃんとこれでムーブされる。
										// でも、ムーブされるからcの方を以後触っちゃだめ(再代入はいいけど)

		// ほれ。インスタンスを経由しなくても呼べる
		std::cout << hoge_4_1_6::calculate_value(11) << std::endl;

		{
			// だってポリモーフィズムするには、C++だとポインタにしないといけないから。
			// でも、ポインタの配列で管理するの面倒なんでunique_ptrですよ。
			std::vector<std::unique_ptr<Base4_1_7>> polymorphism;
			polymorphism.emplace_back(std::make_unique<hoge_4_1_7_1>());
			polymorphism.emplace_back(std::make_unique<hoge_4_1_7_2>());
			// ↓でポリモーフィズムしてるのがわかるじゃろ？
			for (const auto& v : polymorphism) {
				std::cout << v->func1(11) << std::endl;
				std::cout << v->func2()   << std::endl;
			}
		}
		// スコープ抜けたのでここで↑のunique_ptrは自動解放されてる

		// ほい。統一初期化とrange-based-forへ対応した独自クラスの出来上がりと
		// サラリとテンプレート使ってるが気にすんなｗ
		hoge_4_1_8<double> vvv{ 1.0, 3.5, 4.4 };
		for (const auto& vv : vvv) {
			std::cout << vv << std::endl;
		}
	}
#pragma endregion 実際の使い方
}

// ま、実際にはオブジェクトの定義ってなんか指針がほしいですよね？
// なんで少し自分ならこうするってのを書いときましょう。(ただの一例ですぜ、自分ですら諸事情で従わないことは多々あるわけで)

// C++はC#やJavaと違うので共通データ型的なものを構造体で宣言することが結構あります。
// なので共通データ型としての構造体は↓に述べる制約とは無関係です。
// むしろ共通データ型なので引数とかにそのまんまで適用するべきです。よって、以下はオブジェクトとして扱う場合の話なのでお間違えの無いよう

// また、面倒なのでほとんどprivateの関数を書いてませんが、publicな関数から外部へ実際の処理を隠蔽するために
// 良くprivate関数使います。私は
// Pimplとか使うこともあるかもしれんけど、あれはあれで面倒なことあるので、仕事だと大人しくprivateに。
// 企業同士でヘッダとDLLしか提供しないならpimpl使うかもしれんけど、それ以外だとねぇ

// データ型(ただデータを保持してるだけ)
// ぶっちゃけグローバル変数とか
struct hoge_data_only
{
	// 変数は原則初期化構文で。コンポジットする事情があるなら、コンポジット側でも原則初期化させる
	int x = 11;
	int y = 21;

	// ゲッター、セッターは用意しない(データの入出力で加工を行わないため)
	// ま、あってもいいけど
	// そもそもゲッターとかセッターとかって、GUI部品を用意するとか、
	// C++みたいにstructやクラス外の変数、関数を用意できないって事情から始まったんじゃない？って気がする。
	// 用意するならそうだな、排他が必要なデータを管理するなら用意するかなぁ。

	// コンストラクタ、デストラクタをわざわざ用意するのはムーブを禁止にするから
	// で、現場で組む人間全員がきちんと規則分かってる奴らonlyならそんなこと考慮しなくていいが、まぁそんなことないので
	hoge_data_only() = default;		// コンストラクタは用意しても基本何もしない。だからdefault
	~hoge_data_only() = default;	// デストラクタも同じく基本何もしないよ。だからdefault

	// move系は削除。だって、色々な箇所でコピーしたりすることが予想されるのに、元データなくすとかなんの冗談？って思う
	hoge_data_only(hoge_data_only&& rhs) = delete;
	hoge_data_only& operator=(hoge_data_only&& rhs) = delete;

	// コピー系は原則default。もしなんか処理が必要ならコンポジットも含めて全部きちんと書くこと
	hoge_data_only(const hoge_data_only& rhs) = default;
	hoge_data_only& operator=(const hoge_data_only& rhs) = default;
};

// データ型(ただし、外部と内部でデータの保持形式が違う)
// 外部から文字列で入出力するのに内部データはXMLみたいなやつ
struct hoge_data_xml
{
	// ゲッター、セッターは用意する
	void set_value(const std::string& str)
	{
		// ここでなんかの加工をして保存
		_xml_data = str;
	}
	std::string get_value() const
	{
		// ここでメンバ変数から取り出して、returnする形への変換を行う
		std::string rvalue = _xml_data;
		return rvalue;
	}

	// コンストラクタ、デストラクタはとりあえず
	hoge_data_xml() = default;
	~hoge_data_xml() = default;

	// move系は削除
	hoge_data_xml(hoge_data_xml&& rhs) = delete;
	hoge_data_xml& operator=(hoge_data_xml&& rhs) = delete;

	// コピー系は原則default
	hoge_data_xml(const hoge_data_xml& rhs) = default;
	hoge_data_xml& operator=(const hoge_data_xml& rhs) = default;

private:
	std::string _xml_data = "";
};

// 例えば、ファイルを扱うとか単独のインスタンスとして扱うもの
// インスタンス一つ一つが個々のオブジェクトに写像するようなもの
class hoge_monolithic final
{
public:
	// 継承は使わない。コンポジットだけ。で、基本はポリモーフィズム的にふるまう必要性がないので、
	// 継承もさせない(ファイルごとにポリモーフィズムするとか、そうないと思う)

	// move、コピー系は削除。個々のオブジェクトに意味があるのに、それらの操作が出来るって、変でしょ？
	// もし用意するなら配列的に多数のオブジェクトを扱う場合ですが、そんなに多いケースではないと思う
	hoge_monolithic(hoge_monolithic&& rhs) = delete;
	hoge_monolithic& operator=(hoge_monolithic&& rhs) = delete;
	hoge_monolithic(const hoge_monolithic& rhs) = delete;
	hoge_monolithic& operator=(const hoge_monolithic& rhs) = delete;

	// デストラクタは自動生成されるだろうが、コンストラクタは無理だかんなぁ
	// ま、どっちもdefaultでいいけど
	hoge_monolithic() = default;
	~hoge_monolithic() = default;

private:
	// 当たり前だけど、メンバ変数はprivate
	// 全部。一つの例外もなく
	int x = 1;
};

// ポリモーフィズムするのを前提とするが、外からみた振る舞いが重要なオブジェクト
// あるコマンドに対して反応するオブジェクト群とかかしら。こいつらは外側からみえる振る舞いが同じだが、
// リアクションは個々のオブジェクトで違うからねぇ
class hoge_interface
{
	// 振る舞いをポリモーフィズムさせるから、publicな操作関数だけ用意する。
	// そんで原則は全て純粋仮想関数。
public:
	virtual void notify(int command, int arg) = 0;

	// ほとんどの派生先で同じ振る舞いをさせたい(あるオブジェクトだけ違うとかはオーバーライド)関数は仮想関数
	// そんで、基本の振る舞いを実装しておく(ただ、これをやろうとすると、protectedのメンバ変数が必要になることが多いだろうけど。
	// さすがにそれのために変わった継承を使うのも、業務じゃリスクがありすぎて。。。)
	virtual void async_notify(int command, int arg)
	{
		_command = command;
		_arg = arg;
	}

	// 書くのたるいからあれだが、ポリモーフィズムさせる以上virtual デストラクタが必須なので、
	// コピー、ムーブ系をdefaultで全て定義な。コンストラクタもよろすく。
	// unique_ptrで突っ込むならmoveは継承元にも必要なことが分かれば、まぁ言いたいこと分かるっしょ。

	virtual ~hoge_interface() {}	// 絶対用意してください。
									// 全員がその意味が分かって、不要であることも設計できてるなら話は別だが

protected:
	int _command = 0;
	int _arg = 0;
};
class hoge_behavior : public hoge_interface
{
public:
	// 振る舞いが重要な場合、あんんまセッター、ゲッターは必要ないと思う。
	// 環境とかの関係で一つのオブジェクトが設定値によって振る舞いを変える必要があるなら、セッターを継承元に用意するのもありだしょうが。
	// ただ、ゲッターはまずいらんのちゃいます？
	// もし、両方どうしても必要というなら、それはGUI部品とかじゃないかな。あれは振る舞い一緒だけど、コピーとかプロパティが特に重要なものだし。
	// ただ、GUI部品系だとどうしてもdynamic_castとかstatic_castでもって、ダウンキャストすることが必要になると思うよ。
	// ボタンとラジオボタンは全然別物に見えるけど、振る舞いや使うデータは似通ってるので、同じ親から継承されることって多いだろう。でも、決定的に違うIF持つから、
	// 継承元に関数用意するより、ダウンキャストして個々のクラス特化の振る舞いを持たせるのが普通な気がする。
	// いや、C++だから多重継承したって、いいのよｗ

	void notify(int command, int arg) override
	{
		// なんか処理して
	}

	// コピー、ムーブ、コンストラクタ、デストラクタよろすく

private:
	// 必要なデータを
};

// ポリモーフィズムするのを前提とするが、状態が重要なオブジェクト(場合によっては継承しないこともある)。
// 基本的な状態遷移を受け持つオブジェクトがあるけど、実際の状態遷移、外部へのアクセスなどは個々のインスタンスで少しずつ違うという場合に。
// こいつらはよっぽどのことがない限り、コンテナに格納するんじゃない？だって一つ、二つしかないなら、
// わざわざポリモーフィズムさせる意味ないし。
class hoge_base
{
public:
	// 外部からの要求的な
	enum class request : int
	{
		init = 0,
		start,
	};

	// なんかの依頼を外部から受けるみたいな
	bool command(request req)
	{
		// 派生先のオブジェクトに判定させる
		if (!check_request(req)) {
			return false;
		}

		// で、なんか状態を変えると。まぁそりゃcheckとmoveを同時にやっても構いませんが
		move_next_state(req);
	}

	// セッター、ゲッターは原則ないよ。
	// そんなのがあると状態保持や変更に外部からのアクセスが介在することになるんで、カプセル化とオブジェクト指向の原則を破ることになる

protected:
	// こいつらは派生先のオブジェクトが独自に実装することになる。
	// ま、派生元のデフォルト実装をほとんどのオブジェクトで実装するなら純粋仮想関数じゃなくて仮想関数でもいいけど
	virtual bool check_request(request) = 0;
	virtual bool move_next_state(request) = 0;

private:
	// あんまここに定義するものがあると思わないけど
};
// 派生クラスでもってprotectedなのを書きかえちゃいな
// privateはそのオブジェクト独自のものだし
// publicの奴はあくまで派生元が受け取って、同じ手続きで処理するけど、その詳細が派生元にあるって形になるだしょうから

