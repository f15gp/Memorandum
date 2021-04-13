/**
**********************************************************************
* @file		Sample4-1.h
* @brief	浅くC++言語 を学ぶためのサンプル4-1
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

#pragma once

#include <vector>	// vector使うんで
#include <memory>	// unique_ptr使うんで
#include <utility>	// make_unique使うんで

namespace sample4_1 {
	// クラスを利用したりするサンプルを書くための関数が↓
	void func1();

#pragma region 4_1_1
	// お待ちかね。
	// 皆多分大好きクラスだよ。
	// シンプルなクラスから行くね。
	/// <summary>
	/// シンプルクラス。難しいことは省いて、必要なことだけ書く。
	/// publicとかそういうのを付けなかったら、デフォルトはすべてprivate指定なんだけど、ま、気長に付き合ってちょ。
	/// </summary>
	class class_0
	{
		// C++はアセンブリとかそういう概念がないので、classにprivateとかは付けません。

		// "class クラス名"のクラス名で定義する変数をインスタンスとか実体と呼びます。

		// 最初にはまりやすいので、JavaやC#のクラスとの違いを述べる。
		// 1 各変数、関数にいちいちprivate, public, protectedとか不要
		// 2 インスタンスのコピーはディープーコピーが基本(でもメンバ変数のポインタはシャローコピー)
		//   なので、クラスのメンバ変数にポインタを保持してしまうと、くわすく知ってないと直ぐorz状態に陥る。
		//   が、ポインタをクラス内部に持たないなら、大した話じゃない。
		// 3 メンバ関数は非virtualがデフォルト。
		//
		// 1については↓で示す
		// 2 はC言語から発展したことが関係するがC++のクラス、構造体の扱いを複雑にしてる理由(他言語と比べてね。でも、これはこれでいんじゃない？)。
		//	 ただ、JavaやC#みたいなインスタンスコピー＝シャローコピー(=ポインタのコピー)も場合によっては問題がある。
		//   スレッド間データのやり取りとかではシャローコピーだとハマることがあると思われる。
		// 3 はC#と同じというかC#がC++に倣ったというか、まぁJavaと違ってvirtual付けないとポリモーフィズムしねぇぞっと

		// C++では、クラスの中に宣言または定義する変数をメンバ変数。関数はメンバ関数と呼びます。

		// public: って書いたら以下全部公開要素ね。
		// 公開要素だからpublicの変数、関数は他からアクセスが可能です。
		// C#とかJavaと違って、いちいち変数や関数にpublicって書く必要ないから。
		// てか、これだけはC#とかJavaに引き継いで欲しかった。だって面倒じゃん、全部の変数、関数にいちいち書くの
	public:
		int a = 1;
		int func1(int a)
		{
			// これインラインでメンバ関数内容を書くやつね。
			// こうやって、class宣言の中でもメソッドを書くことができる。

			func2();	// private関数でも自分自身では呼べるよ。private関数は、主に外部に対して詳細な実装を隠すのに使う

			return a * 3;
		}

		// protectedっていう自分自身と継承先のクラスから参照できるって指定があるけど、それは後でね

		// privateを書いたのでここからはpublicじゃなくてprivate属性
		// privateはこのクラスだけで見れるっていうやつね。
		//
		// で、勘違いをたくさんみたので書いておきます。
		// このpublic, privateなどの概念はインスタンスではなくクラスに帰属します。
		// よってclass_0のpublic関数にvoid ModifyClass(class_0& instance)のようなメンバ関数を用意したとすると、
		// メンバ関数と引数は同じクラスであるため、引数のprivate変数を書き換えることができます。
		// これはアクセス制限が"クラス"を基準とするためですが、インスタンスを基準に考えている方が多いので念のため書いておきます。
	private:
		int b = 3;
		int func2();
	};
#pragma endregion 4_1_1

#pragma region 4_1_2
	// ほいじゃ、まぁ継承とprotectedでも
	// ただ、継承を何に使うかはここでは記載してません。・・・書くと長いので。
	class Base4_1_2
	{
	protected:
		int hoge2 = 2;
	};

	// ↓こうやって: public クラス名とすると継承できます。
	// ちなみにC++の場合、継承にはvirtual, public, private, protected継承があります。
	// が、理解しない限りpublic継承だけ使用してください。ちなみに、もしpublicとか何も書かなかったら、
	// classではprivate継承、structならpublic継承になります。
	class hoge_4_1_2 : public Base4_1_2
	{
	public:
		void a()
		{
			// protected属性なので、継承先クラスからは触れる。
			// private属性なら触れないし、public属性なら継承先クラスじゃなくても触れる。
			Base4_1_2::hoge2 = 12;
		}
	};
#pragma endregion 4_1_2

#pragma region 4_1_3
	// じゃ、まぁC++のclassの深淵に少しずつ行きましょうかね
	class hoge_4_1_3
	{
	public:
		// これ、デフォルトコンストラクタと言います。自分で実装しないと勝手にコンパイラが作成します。
		// 一時オブジェクトとか()初期化の時呼び出されます。
		hoge_4_1_3() : a(3), b(5) {}
		// ちなみに: a()なんて書いているのはメンバイニシャライザと言います。
		// メンバイニシャライザで書いた初期化は、コンストラクタの処理が始まる前に実行されます。
		// C++03だとメンバのconst変数(=変数は不変の値を持つ)を初期化する場合、これしかやりようがありませんでした。
		// なんでかというとオブジェクトが構築されたあとに動く(少し語弊あり)コンストラクタでconst変数が値を持つには、コンストラクタの前に値が与えられている必要があったからです。
		//
		// 今はprivate:の所で書いているように変数に初期値を与えれるのでそんなに必要ありません。
		// ちなみに変数に初期値を与えるのとメンバイニシャライザを両方書くと、メンバイニシャライザの値(またはコンストラクタの中での代入処理)で初期化されます。
		// 2回初期化されるのでなく、メンバイニシャライザ(またはコンストラクタの中での代入処理)のみ実行されます
		// そんで、くそVSは2005から配列の初期化もメンバイニシャライザで出来るようになっている(VC6ってのではできなかった)のですが、
		// くそ邪魔なことに警告(なんで警告使うよ(ノД`)・゜・。)で"配列もイニシャライザで初期化できるようになったよ♪"なんてのを出します。
		// うざいので↓の構文使うか、許されるならpragma or プロジェクト設定で警告を消しちゃいましょう。
		//
		// 大事なので2度言います(どっかで1度目言ったかしら？)。理解するまで全てのメンバ変数は必ず初期化するように！

		// ↓は引数付きコンストラクタです。オブジェクト宣言の際にhoge_4_1_3 a(4);とか書くとデフォルトコンストラクタの代わりにこっちが呼び出されます。
		// explicitって何？ってのはまぁそのなんだ、細かいことは無視して引数一つのコンストラクタに付けとけばいいよ。うん。
		explicit hoge_4_1_3(int x) : a(x) {}

		// ちなみにC++にはデフォルト引数(C#の・・・名前忘れたｗ)ってのがあります。
		// C++の場合は最後の引数に限ってそれを使用できます。別にクラスのメンバ関数じゃなくて、普通の関数にも使えるけどね。
		// 用途はhoge4_1_3(3L)なんてしたらboolの変数bはfalseとして関数に渡されるってものですね。
		// ただ、このデフォルト引数があって(3L)みたいに引数一つだと、↓はlong xだけになっちゃいます。
		// なので、まぁ詳しく理解するまで最終的に引数が一つになるコンストラクタにはexplicitを付けなさいってね
		explicit hoge_4_1_3(long x, bool b = false) : a(static_cast<int>(x)) {}

		// あ、そうそう。引数付きコンストラクタを定義するとデフォルトコンストラクタは自動的に作られなくなります。使いたかったら、自分で追加してね

		// んで、これはデストラクタですね。C#とかJavaだとファイナライザに該当すんだっけかなぁ
		// このクラスで明示的に解放が必要なリソースはないので何も処理を書きません。あるのならこの中に書いてちょ
		~hoge_4_1_3() {}

	private:
		int a = 1;			// これ、今まで書かなかったけどC++11以降で許された構文です。
							// 非静的変数をコンストラクタとかメンバイニシャライザじゃなくても初期化できる方法です。
		const int b = 3;	// こんな感じでC++11以降ならメンバイニシャライザ使わくてもconst変数に初期値を与えれます。
		//static int c;		// staticをメンバ変数に使うとこのクラス全体で唯一の変数となります。いくらインスタンスが存在しても一つだけ存在する変数になります。
							// 初期化は諸事情で変わった書き方になるので、コメントアウトします。そんなに利用する機会は多くないですがC++で簡易シングルトンパターンを作るのに使ったりします。
							// しかし、まぁそんなに使うことはないので、必要になったら初期化の仕方とか調べて(はーと)
							// ただ、それゆえ、
							// オブジェクトを生成せずに使用することができて、オブジェクトを複数生成したとしたら、静的メンバ変数はそれぞれで共有されます。 
							// ハマることあるので使う場面を限定してね

		// [超大事なことを]
		// 全く理解してない人がいるのですが、C++においてクラス変数の初期化＆解放順は厳格に規定されてます。
		// 同じクラスの中では変数宣言を書いた順番です。メンバイニシャライザやコンストラクタで書いた順番ではありません。
		// なので、gccとか使った場合、変数宣言順とメンバイニシャライザの順番が異なったりすると、わざわざ警告が出たりします。
		// そんで、クラスのコンストラクタが呼ばれる順番は基底クラスのコンストラクタ->派生クラスのコンストラクタです。
		// で、解放する順番は、変数だとコンストラクタが呼ばれる順番の逆順。デストラクタは、コンストラクタの逆の派生クラス->基底クラスです。
		// 規格でそう決まってるので知らないとかもぐりかよ扱いで問題ないでしょう(仕事では知らないもぐりが多いので、言葉を選ぶか沈黙するかの2つを選びましょう)
		// んで、基底クラスのコンストラクタは普通にやるとデフォルトコンストラクタですが、引数付きのを呼ぶやり方もあります。
		// 必要だったら勉強してね。
		// ま、結局継承間でのコンストラクタ、デストラクタの順番依存や変数の相互依存をしてなけりゃ関係ない話ですけどね
	};
#pragma endregion 4_1_3

#pragma region 4_1_4
	// 頭が痛くなるC++の最深淵付近でも
	class hoge_4_1_4
	{
	public:
		// コンストラクタ
		hoge_4_1_4() {}

		// 以下↓2つはコピーコンストラクタとコピー代入演算子というものです。
		// なにそれ？と思うだろうが、こういうとき呼ばれます
		// hoge_3_1_4 a;
		// hoge_3_1_4 b = a; <- ここでbに対してコピーコンストラクタが呼び出されます。一時オブジェクトというもんを呼ぶ時にも使われたり
		// hoge_3_1_4 c;
		// c = a; <- ここでcに対してコピー代入演算子が呼び出されます。operator=ってのは演算子オーバーロードの一種で=の演算に対してのオーバーロードを提供します
		hoge_4_1_4(const hoge_4_1_4& rhs) {}
		hoge_4_1_4& operator=(const hoge_4_1_4& rhs) {}
		// さて何が頭痛いかというと、ポインタのメンバ変数とかがあると、それに対して適切なコピー処理を書いてあげないといけない(ポインタはシャローコピー。でも普通データもコピーされることを期待するでしょ？)ことです。
		// 新たにポインタに領域を用意してやってデータをコピーするような処理が必要です。
		// ※中身のコピーなんていらないよって方は別にいいですけど(いいのか？)

		// 以下↓2つはムーブコンストラクタとムーブ代入演算子というものです。
		// なにそれ？と思うだろうが、こういうとき呼ばれます
		// hoge_3_1_4 a;
		// hoge_3_1_4 b = std::move(a); <- ここでbに対してムーブコンストラクタが呼び出されます。
		// hoge_3_1_4 c;
		// c = std::move(b); <- ここでcに対してムーブ代入演算子が呼び出されます。
		hoge_4_1_4(hoge_4_1_4&& rhs) noexcept {}
		hoge_4_1_4& operator=(hoge_4_1_4&& rhs) noexcept {}
		// やっぱり頭痛いことにポインタがあるとね・・・
		// で、このムーブってコピー処理だと時間かかるやん！ポインタの差し替えですむオブジェクトならそうしちゃえよ！
		// ってので生まれました。なのでムーブって処理をした後に元のオブジェクトを触っては原則ダメです。
		// だって、ポインタとか付け替えちゃったので有効な値になってないんですよ、普通。

		// が、こういうやつらは実はポインタ使ってなかったら話は楽です。それを次に述べます。
		// また、～コンストラクタ、デストラクタ、代入演算子などはpublicに定義されないと使えません。
	};
#pragma endregion 4_1_4

#pragma region 4_1_5
	class hoge_4_1_5
	{
		// 4_1_4で述べた話ですが、簡単です。
		// ポインタを使わなければいんです。
		// STLのコンテナとスマートポインタはコピー＆ムーブ両対応です(スマートポインタはムーブonlyもあるけど)
	private:
		std::vector<int> v;			// コンテナは初期化されるよ。emptyだけどね
		std::unique_ptr<int[]> u;	// こっちは無効ポインタで初期化されるはず。
									// あ、unique_ptrってのはコピーを許さないので必ずムーブしてね

	public:
		hoge_4_1_5(int n)
		{
			unsigned int t = (n <= 0) ? 1 : n;
			v.push_back(t);
			u = std::make_unique<int[]>(t);
			u[t - 1] = 10;	// 確保した領域は0オリジンですから、-1しないとね
		}
		// Sample4-1.cppの方動かしてみればわかるけど、ちゃんとこれで問題がないクラスになります。
		// スマートポインタに対してなんかしてみたいにょとか思わなければこれだけで良いです。
		// コンストラクタが不要なら削除できる位です。
		//
		// ちなみにこれでsample4_1::func1()が終わる時に呼び出されるデストラクタでvectorもunique_ptrの領域とも正しく解放されます。
		// 下手に生ポインタを使うと構築、コピー、ムーブ、解放を全部プログラマが責任を持たないといけません。

		// ちなみにコンストラクタとデストラクタは自分で定義しない限り、勝手にコンパイラが作成します。
		// で、コピーとかムーブにも自動生成規則があるのですけど、確実なのはデストラクタを定義してしまったら、自動生成されないってこと。
		// なので、デストラクタがどうしても必要(ファイルを保持してるので解放したいですぅとか)で定義したいなら良い方法があります。
		~hoge_4_1_5() {/* 何かの処理 */}
		// ↑みたいなのを書いたら次の方法を使います。
		hoge_4_1_5(const hoge_4_1_5& rhs) = default;
		hoge_4_1_5& operator=(const hoge_4_1_5& rhs) = default;
		hoge_4_1_5(hoge_4_1_5&& rhs) = default;
		hoge_4_1_5& operator=(hoge_4_1_5&& rhs) = default;
		// = defaultは自動生成されるのと同じ処理で良いよって記述です。こうすると中身をわざわざ書く必要がありません。
		// ちなみにムーブ禁止、コピー禁止、デフォルトコンストラクタでのオブジェクト生成禁止とかしたかったら、
		// 昔はprivateにそれらメソッドを宣言してましたが、今は = defaultの代わりに=delete;と書けば未定義というかその実装は削除されます。
	};

	// ところで、もし仮にdefaultにしたくないってんなら、多分たいていこれでOKです。
	// "コピーしてmove"。ん？と思うでしょうが、こういうこっちゃです
	//
	// コピーコンストラクタ、ムーブコンストラクタ、ムーブ代入演算子をまずdefaultにします。
	// でコピー代入演算子を↓のようにします。あ、noexceptってのは、このメンバ変数からは例外を投げないって宣言します。
	// 強い例外安全のためにありまして、ムーブコンストラクタとかにはついておく必要がありますし、また例外を投げないように作成する
	// 必要があります。なぜ必要かと言うと、インスタンスのコピーを行う位で例外を投げられると、コンパイラは困るからです。
	// なので、ムーブと指定してもnoexceptがついてないと、より安全なコピーを使うコードを作成したりします。
	// クラス名& operator=(const クラス名& rhs) noexcept
	// {
	//    return *this = クラス名(rhs);
	// }
	// は？って思うかもしれませんが、クラス名(rhs)ってのは一時オブジェクトって呼ばれる物を作ります。
	// 一時オブジェクトはまぁ名前のないオブジェクトを作るんです。その場で。生存期間は少し複雑なので無視しますが、
	// ま、この場合return 抜けたら一時オブジェクトは削除されます。
	// クラス名(rhs)でrhsを元にしてコピーコンストラクタが発動します。
	// そいで、一時オブジェクトはC++11用語で言うと右辺値です。で、右辺値を代入しようとするのでムーブ代入演算子が呼ばれます。
	// よって、結果的にコピーしてムーブしてるんです。
	// ま、正直、かなり深い話だしdefaultでほとんど済むのだから、単純にそうしたら？(他にコピーしてswapってのもありますが、一長一短)
	// こんなのを使うのはLv5じゃねぇってｗ
	//
	// まじ、コンストラクタと他の公開メンバ関数以外書かなくて良くなるしね。
	// ね？生ポインタ使わなかったら、C#やJavaなみに簡易なクラスに近づくでしょ？
	// 変な拘りもってポインタ使いやがったうえに知識が不確かだと、そいつがどんな奴だろうと蹴飛ばしてやりたくなる。
	// バグをわざわざ入れるんじゃねぇ、ク○ry)ｗ
#pragma endregion 4_1_5

#pragma region 4_1_6
	/// <summary>
	/// constとstaticメンバ関数についてだけ。大事なので
	/// </summary>
	class hoge_4_1_6
	{
	public:
		/// <summary>
		/// はい。私大嫌い、皆大好きのゲッターです
		/// </summary>
		int get_value() const
		{
			// constと後ろについてるのはconstメンバ関数の宣言です。
			// なんのためにあるかというと、この関数内でメンバ変数に変更を加えないと宣言するためです。
			// なのでメンバ変数に代入なんぞするとコンパイルエラーが発生します。
			return a;
		}

		/// <summary>
		/// 静的メンバ関数。
		/// この関数は静的なメンバ変数しかアクセスできない。で、"静的"に存在するのでインスタンスがなくても呼び出すことが可能。
		/// C++で一番使うのはコールバック関数を受けることだと思う、個人的には
		/// </summary>
		/// <param name="x">引数1</param>
		/// <returns>引数1とstaticメンバ変数の足し算</returns>
		static int calculate_value(int x)
		{
			return (b + x);
			//return a;
		}

	private:
		int a = 10;
		static int b;
	};
#pragma endregion 4_1_6

#pragma region 4_1_7
	// ほいじゃ、ポリモーフィズムってのをやりましょうか
	class Base4_1_7
	{
	public:
		// ↓純粋仮想関数といいます。これがあると、そのクラスは実体化できません。
		// なにに使うってそりゃインターフェースのためですよ
		// そんで、継承先は必ずこいつを実装しないとコンパイルエラーになります
		virtual int func1(int x) = 0;

		virtual int func2() { return 31; }	// virtual が付いてるメンバ関数は、派生先クラスで書き換え可能です。

		// ポリモーフィズムさせるクラスなら諸事情でvirtualデストラクタを用意してください。
		// ただ、デストラクタを用意しちゃうってことは、、、ちゃんとわかってやってね
		virtual ~Base4_1_7() {}
	};

	// finalはhoge_4_1_7_1は継承不可能と指定するもの。メンバ関数単位でも指定できます
	class hoge_4_1_7_1 final : public Base4_1_7
	{
	public:
		// overrideはvirtual関数のオーバーライドを行う宣言。
		// もし継承元がvirtual宣言してないとコンパイルエラーになります。
		int func1(int x) override;
		int func2() override;

		// virtual 付けてませんが、継承元についているので暗黙的に付加されます。明示的に書くのもOK
		~hoge_4_1_7_1() { std::cout << "hoge_4_1_7_1 destructor" << std::endl; }
	};

	class hoge_4_1_7_2 final : public Base4_1_7
	{
	public:
		int func1(int x) override;
		int func2() override;

		~hoge_4_1_7_2() { std::cout << "hoge_4_1_7_2 destructor" << std::endl; }
	};
#pragma endregion 4_1_7

#pragma region 4_1_8
	/// <summary>
	/// 統一初期化構文とrange-based-forに対応させる
	/// </summary>
	template <class T>
	class hoge_4_1_8 {
	public:
		// 統一初期化用のコンストラクタ
		hoge_4_1_8(std::initializer_list<T> init)	: _data(init.begin(), init.end()) {}

		// range-based-for用
		auto begin() { return _data.begin(); }
		auto cbegin() const { return _data.cbegin(); }
		auto end() { return _data.end(); }
		auto cend() const { return _data.cend(); }

	private:
		std::vector<T> _data;
	};
#pragma endregion 4_1_8
}
