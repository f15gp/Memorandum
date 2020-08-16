/**
**********************************************************************
* @file		Sample1-1.cpp
* @brief	浅くC++言語 を学ぶためのサンプル1-1(実装)
* @date		2020/08/16
* @par		Copyright
  (c) 2019-2020 Bunya
**********************************************************************
*	@par	History
*			- 2020-08-16 Bunya
*				-# 新規作成
*
**********************************************************************
*/
// サンプル 1-1
// 大枠：関数(参照、ポインタ、値渡し)、暗黙の型変換、キャスト、型推論、static
// 命名規則：原則スネーク記法

#include <cstdint>		// uint64_tを使うので
#include <iostream>		// ちょっと表示したいので

#include "Sample1-1.h"

#pragma region 暗黙の型変換
/// <summary>
/// 暗黙の型変換というものを紹介する。(それ以外の方が長いような・・・？)
/// 概念はC#とかもあるのでそんなに細かく書くこともないのだけど
/// func1はsample1_1の名前空間に属しているので、関数実装はsample1_1::func1となる.
/// または、つぎのようにしても良い(好みかなぁ)。でもたくさんあるとイチイチ関数につけるの面倒なんだよねぇ
/// namespace sample1_1
/// {
///     void func1()
///     {
/// </summary>
void sample1_1::func1()
{
	// 最初に大事なことを述べておく。変数にはスコープというものがある。
	// C++はスコープを抜けると、その変数は破棄される。また、スコープが異なる変数は同名でも別の変数として扱われる
	// 基本的にスコープの代表は{}、次が同じ関数内、で名前空間となる。
	{
		int x = 1;
		std::cout << x << std::endl;	// <- ここでxを表示
		{
			int x = 3;	// このxは↑のxとは別の変数。もし、↑の変数使いたいなら名前空間を・・・あ、名前空間ないから絶対無理ｗ
			std::cout << x << std::endl;	// <- ここでxを表示
			int y = x;
			std::cout << x << ' ' << y << std::endl;	// <- ここでx, yを表示
		}
		int y = x;	// {内の変数は}の時点で破棄されるので、x = 1がyに入る
		std::cout << x << ' ' << y << std::endl;	// <- ここでx, yを表示
	}

	// ここからが暗黙の型変換

	// 本来long型の定数は10にサフィックスであるLを付けるので10Lとなる。
	// しかし、ここでは10としておりint型として扱われる。ところが、代入先がlong型のため実際にはlong型に
	// 暗黙の型変換が行われて格納される。代入もそうだが、+=などでも代入先の型に変換してから格納される。
	// でも、代入だけで発生するわけでなく、計算時に型が異なってたらいつでも発動します。
	long a = 10;

	// 式の片方が型変換規則の優先度高の場合、自動的に型変換されてから計算される。
	// これを知らない人はキャストでもって無理やり型変換するが、不要なキャストは邪魔なだけだ。
	// キャストで型変換を明示的に示すという書き方もあるらしいけど、キャストによりミスが消される可能性が高いため、やめた方がよいと思う。
	// ※ 静的解析ツールや最近のVSなら警告を出してくるかもしれないが、キャストにより警告がつぶされる可能性がある
	double b = a * 10.0;

	// というか整数拡張ってのもあって、単項の+とかが行われただけで型の昇格が起こることがある。
	// 便利な場合もあるが問題が出ることもある。
	// 便利例) ostringstreamでcharを扱う場合、そのままだとASCII文字と扱うので+することでint化し、値として扱う
	// 問題例) if (-1 < 1U)が必ず偽になる。 -1はint, 1Uはunsigned intのため-1をunsigned intに昇格すると、とても巨大な値になるから

	// これはダメなパターン。割り算の分母分子が両方ともlongの為、まずlongで計算する。
	// ま、切り捨てonlyならダメなパターンでもないが、切り捨てない方が普通でしょ？
	// で、代入する際、暗黙の型変換でdoubleに変換されるが 10 / 100の小数点以下が切り捨て済みなので
	// cには0.0しか入らない。
	double c = a / 100L;

	// これダメパターン2。どうせVSなら警告食らうけどね。ULはunsigned longのサフィックス。
	// なぜダメかというと、1がintの関係でULとの優先順位からunsinged longで計算される。
	// しかーし、64bit Windowsではlongが4byteで扱われるので、+1した時点でオーバーフローする。
	// その後、uint64_tに変換しても時すでに遅しなのである。
	//uint64_t d = 0xFFFFFFFFUL + 1;

	// だから↓にしてね。非推奨のC言語キャストしてみました。
	uint64_t e = (uint64_t)0xFFFFFFFF + 1;

	// 余談：
	// 突っ込んだ話をすると実数型での計算は、丸め誤差とか情報落ちを考慮する必要がある。
	// floatとdoubleはIEEE754の32bitと64bitで大概実装されてるから。この辺はJava、C#でも同じ。
	// 表現できる範囲は広い感じがするけど実数型の有効桁は少ないよ(floatで7桁、doubleで15桁位)。
	// マイナスが絡む場合はもう一つ落とし穴があるけどね。
	// ちなみに、IEEE754には128bitも規定されている。現在これは4倍精度と呼ばれソフトウェアで実装される。
	//
	// それともう一つ。MMX以前では小数の計算にはx87命令を使います。これは80bitとなってます。
	// しかし、MMX, SSE, AVXは32bitと64bitでもって計算します。
	// なので、実はオーバーフローとかアンダーフローを考慮して一度変数に代入とかすると、とあるパターンでハマります。
	// 小数の計算にx87使ってないならハマらないのだけど、使っていたもしくは使うように設定がなされていたとして、
	// 計算の時はx87(=80bit)で計算するのですが、変数とかに代入するときdouble(=64bit)に丸めるため誤差が出るんでやんの。
	// まぁ丸めないようにするアセンブラが使われていればいんだけど、そうじゃない時にハマるっていうレアパターンなんだけどね。
	//
	// 余談ついでに、C言語やC++で数値を文字列に変換するとき、よくsprintfって関数を使います。
	// これ%5.2fとかやると99.21とかって感じの文字列にしてくれるんですが、この指定の場合は小数第三位を四捨五入します。
	// で、四捨五入されたくない場合に涙ぐましい努力で回避しようとするのですけど、単純に%7.4fとかやって小数第四位まで取得して、
	// 下2桁の文字を捨てればOKです。
	// もひとつ余談を言えば、sprintfはprintf系の書式指定に属すのですが、小数の取り込みは%fです。
	// scanf系の書式指定と混同して%lfと書く人が後を絶ちません。あまりにも多いので、C言語の規格C99ではOKにされたのですが、
	// それ以前のC言語の規格(C89とかC95)とC++では未定義動作です。突然そこでプログラムが終了するようなコードをコンパイラが
	// 出力しても規格準拠なので文句言えません(未定義動作=何が起きても文句をいうな)。
}
#pragma endregion 暗黙の型変換

#pragma region キャスト
/// <summary>
/// キャストの説明用。あんま説明なしに気軽にポインタが登場するｗ
/// そして、不要なキャストはやめてね。見づらくなるし、警告してくれるところを抑制するから
/// </summary>
void sample1_1::func2()
{
	// 意味ないキャストだけど、これはC言語からあるキャストでなんでもキャストできちゃう。
	int a = (int)100;

	// C++は、C言語のじゃなくて↓のキャスト使って。ダメな変換はコンパイルエラーになるから

	// static_castは、 const や volatile を外すようなキャスト、
	// 異なるポインタ型同士のキャスト（void*型からの変換は可能）を除いたものをキャストする。
	// 継承関係にあるクラスでダウンキャストする場合でも使える。
	long long b = static_cast<long>(120) + 11;
	double* c = static_cast<double*>(nullptr);	// nullptr(本当の型はstd::nullptr)は何も指し示していない
												// ポインタを示す。前はNULLとか0使ってた。

	// reinterpret_castは、異なるポインタ型同士をキャストする。
	// 正直いって古いAPIの利用など以外で多用するのはダメなキャスト
	int d;
	long* e = reinterpret_cast<long*>(&d);

	// ついでに説明しておくとvoid*から任意のポインタ型への変換はstatic_castでOK。
	// で、任意のポインタ型からvoid*へはキャスト無しで暗黙的に代入可能。
	// んで、
	// double* f = static_cast<double*>(&d); <- これダメ。出来ない
	double* f = static_cast<double*>(static_cast<void*>(&d));	// これだとOK

	// でもそれならreinterpret_castで良いじゃんと思うじゃないですか？
	// んでもC++11の前の規格であるC++03ではstatic_castのダブルとreinterpret_castが同じことになるのは保証されてません。
	// C++11からは保証されるので現代ではreinterpret_cast一択でOKです。
	double* ff = reinterpret_cast<double*>(&d);	// つまりこれでOK。(でも多用は禁物)
	// 
	// 後、継承関係にあるクラスを指すポインタでダウンキャスト(※1)を行うにはreinterpret_cast NGです。
	// static_cast か dynamic_cast を使ってください。
	// 理由はダウンキャストするときメモリアドレスに手を加える必要があるんだけど、reinterpret_castはそれをしないから。
	// ※1 : 継承元にキャストするのをアップキャスト、継承先にキャストするのがダウンキャスト

	// const_castは、const や volatile を外すようなキャストをする。
	// 普通は、"使うなバカ野郎"です。
	// 存在理由は、
	// 1. constやvolatileに対応してない古い関数に渡すため
	// 2. あるんだけどとてもLv5で使うような代物じゃないのであえて書かない
	int g = 100;
	const int* h = &g;
	int* i = const_cast<int*>(h);	// ここでconstが外れた普通のgへのポインタがiに入る
	*i = 200; // g, hが200になる

	// は！constとvolatileの説明を書いてなかった。よし、書こうｗ

	// ↓jの書き換えを禁じます。constってのは原則書き換え不能の意味。
	// クラスではちょっと異なるけど、ま、多分その時かく
	const int j = 100;
	//j = 1;	// 書き換え不能なためコメントを外すとビルドエラー

	// ↓多分このvolatileが分かりにくい(さらに分かりにくいmutableってのがあるが、このプログラムでは扱わない)と思う。
	// volatileはコンパイラに最適化するなを命令します。具体的にはIOアクセスなんかで確実に読み書きしたい場合に使用します。
	// 後、VSの場合2005辺りからvolatileの変数に関しては排他制御を行ったかのようにメモリバリアを行うアセンブリを出力するようです。
	// 今でいうとatomic命令を使うのに等しい。が、多分そんなこと他人に説明するのが面倒だろうから排他制御した方が、
	// レビューとかいうので辛い想いしなくていんじゃないかなぁ
	volatile int k = 100;
	int l = k;

	// dynamic_castはクラスのポインタもしくは参照に対してダウンキャストする場合に使うキャスト。
	// 動的に行うんだが本当にそのクラスがダウンキャストできるか不安な場合だけに使用する。
	// ダウンキャストできる確信があるならstatic_castでOK.
	// ま、とりあえず後で出てくるかもね(今はとりあえずいらないや)
}
#pragma endregion キャスト

/// <summary>
/// 引数の値を2倍にして返す
/// </summary>
/// <param name="a">元の値</param>
/// <returns>元の値aを2倍した値</returns>
int sample1_1::func3(int a)
{
	return a * 2;
}

#pragma region 参照_ポインタ_値渡し
// ま、値渡しと参照渡し(const版含む)を覚えればOK
// ポインタ渡しなんて忘れればいい

/// <summary>
/// 参照渡しの例。C#だとrefとかoutに近い概念かなぁ
/// </summary>
/// <param name="a">参照渡しされる変数</param>
void sample1_1::func4(int& a)
{
	// あ・・・大変遅くなりました。
	// 変数なのですがローカル変数(関数の中とかに定義される変数)は値を与えない場合、不定値となります。
	// で、グローバル変数ですが、値を与えないと整数だと0、実数型だと0.0、オブジェクトはデフォルトに初期化されます。
	// オブジェクトはまた後程

	// 参照は元々↓のようなもんです
	// ある変数の別名を付けるという感じ。なので別名を付ける元がないと宣言できません
	// この場合、bとcは同じ扱いになるのでbを変更してもcを変更しても値が変わります
	int b = 100;
	int& c = b;

	// 本題。
	// 参照渡ししたaはこの関数内で変更できます。呼び出し元の変数の内容も変更されます。
	// なので戻り値以外で値を格納したい場合に使います。
	// それ以外にも構造体やクラスのサイズが大きい場合にコピーコストがかかるので使用します。

	a = 19;
	// 構造体とかの場合は
	// a.xxx = 19;というように.演算子を用いてアクセスします
}

/// <summary>
/// const参照渡しの例。C#には類似の概念はない。というか入れてほしい
/// => C# 8.0の読み取り専用メンバーによって構造体(クラスは現状？)に関しては同じことが可能
/// </summary>
/// <param name="a">const参照渡しされる変数</param>
void sample1_1::func5(const int& a)
{
	// const 参照渡しの場合、キャストで説明したようにconstが付いているので変更できません。
	// は？何に使うの？と言われると文字列、構造体、クラスを引数に入れたいが、変更されたくない時に使います。
	// ちなみに参照渡しなのでコピーコストはかかりません

	//a = 19; <- これエラーになります。致命的にどうにもならない場合以外にconst_castでもってconstを外すなんて血迷ったことしちゃだめよ
	int b = a;	// bにaの値を入れる。これはOK
}

/// <summary>
/// なんていうか、いわゆるポインタ渡しという奴です
/// </summary>
/// <param name="a">ポインタ渡しされる変数</param>
void sample1_1::func6(int* a)
{
	// 悪名高きポインタで引数を渡す方法です。
	// 動作としては参照渡しと同じですが、参照渡しと違って構造体とかは.でなく->でもってアクセスします。

	// 重要なポイント：
	//    古いコードのメンテや頭固い人(何故ポインタを使わない！とか言う人)が存在する時以外、使うな。
	//    現C++ではそこまで意味がない。最適化を阻害する"こともある"(コンパイラによる)
	//    簡単なサンプルを組むとわかるが、参照渡しとポインタ渡しはほぼ同等かむしろ参照渡しの方が早いこともある。
	//    また、ポインタ渡しの場合はnullptrを引数に設定出来るので、引数チェックが往々にして必要。
	//    参照の場合、nullptrに相当する概念がないのでそのチェックが不要というのも理由。
	//    ※このnullptr検査により、多少早くても(単純なループ処理だとそりゃすごい差になることあるけど)、バグの可能性が低くなる。
	//      なによりnullptr検査まで入れて考えると実用的な実装でそこまで差が付くのか不明

#pragma region 簡単なポインタ説明
	// ポインタについて簡単に述べておく。
	// C言語の規格から引用するね。
	// "ポインタ型は、被参照型(関数型、オブジェクト型または不完全型)の実体を参照するための値を持つオブジェクト"
	// ただし、ポインタ型というものは単独では存在しなくて、必ず何かの型から派生します。

	int b = 1;		// これはbという変数の宣言よね。ここではintを入れる実体の確保が行われ、その場所に1が入ります
	int* c;			// これはcというポインタ型を宣言してます。この場合、intへのポインタを宣言したわけです。間違っちゃいけませんが、ちゃんとポインタ型の領域は用意されます
	c = &b;			// cが参照する先としてbを割り当てます。割り当てないでアクセスするとメモリ保護違反を食らいます
					// &を付けると派生元の実体の参照先が取得できます。

	*c = 2;			// *を付けると参照先の実体を手繰り寄せます。これによりbの値そのものをさすことになるので、
					// bと*cが共に1から2へと変わります。

	// ざっくり言うとポインタってのはこういうものです。それ以上でもそれ以外でもないです。
	// ポインタがややこしくなるのはポインタ演算という必要性が極小のものと配列との妙な関係のせいです。
	// ただ、業務ソースだとポインタ大好きな方が居たりするので、ある程度知っておく必要があるでしょうけどね。。。
	// ま、それは各自お勉強頂くとして。。。

	// もっと詳しく説明してもいいけど、C++だとポインタを原則使うな派なので、興味があったら自分でしらべんしゃい。
	// でも、C言語にしろC++にしろ、ポインタがとっちらかるのは配列との妙な互換性にあるので、そこだけ気を付けたらいい。
	// どれだけアホォーな互換性かだけ軽く書いておく(理解できなくても支障は全くない)
	//
	// int array[] = { 10, 20, 30 }; // こうやって書くと要素が3つあるから、要素3の配列とコンパイラが自動計算する
	// // 関数プロトタイプがvoid func(int*)だと思いねぇ
	// func(array); <- ん？なんで&付けずに配列をintのポインタ型に渡してるの？
	// 
	// void func(int* c)
	// {
	//     c[0] = 11;  // は？なんでintのポインタ型なのに[]で配列のごとくアクセスしてるの？
	// }
	//
	// 簡略化して書くが、
	// func(array);は実はfunc(&array[0])と同等。配列をポインタに渡す場合に限って変数だけ書くと、&変数[0]として
	// 配列要素の先頭へのポインタ変数として扱われる(というより配列が即座にポインタに変換された結果、先頭の要素が渡されるのが正解だが)
	// また、c[0]でアクセスしてる点だが、これはC言語だといくつかの例外を除いて配列は全てポインタに置き換えられてしまうから。
	// c[0]は *(c + 0)の糖衣構文なので、0[c]でもコンパイルは通る(通るが絶対0[c]なんて書き方をするんじゃない)。
	// この辺が変な互換性なんだよねぇ。(まぁこれでも最初期のC言語よりいくぶん人にやさしくなってるのではあるのだけど)
	//
	// どの位、はぁー？って言うと、最初期のC言語ではポインタは左辺の型はなんでもよく 0177->xxx なんてので構造体のメンバにアクセス
	// できたりする。この辺Lions本を読むなり、2238 Clubでネット検索したらわかるかも。
	// とにかく、最初期のPDP-11(最大メモリ 265kbyte)に使われたSystem V version 6とかのソースなんて見たら吐き気がするよｗ

#pragma endregion 簡単なポインタ説明

	*a = 19;

	// 余談
	// [ポインタの必要性]
	// C++で、どうしてもポインタが必要な場面
	// 1. ポリモーフィズム
	// 2. スタックオーバーフローが発生するほどの巨大なオブジェクトをローカル変数で扱う
	// 3. vectorなどにオブジェクトを格納する
	// 4. 可変長配列、リスト、木構造みたいなものを扱う
	// 5. 文字フォーマットの変換、画像加工などバイナリデータをぐりぐりと
	//
	// ↑であげたような場面がありますが、原則生ポインタで扱う必要はないです。
	// 1. はスマートポインタ(まぁstd::unique_ptrとか)とvector
	// 2. はスマートポインタ(まぁstd::unique_ptrとか)
	// と1., 2.は生ポインタ不要。
	//
	// 3. はC++03とかならまぁ意味があったかもしれませんが、今は意味ないことが多いです。
	// ポインタでオブジェクトを格納すると確かにコピー処理(後で述べる)は走りませんが、
	// チマチマとメモリを確保するペナルティの方が大きいです。現在のCPUはキャッシュとかも大容量なので
	// 実体を入れてもさほど問題になりません(家のPCでは確実にそうだった)
	// スライシングの話とかもあると思いますが、そもそもポインタをバリバリ使うスタイル自体が既に時代遅れだと思うので、
	// 細かいことは試してません。それにスパコンか、マイコンか？とか動かす環境にもかなり依存すると思うので、PCでならそう気にすることもないかと
	// ※ これはMFC全盛のころならC++でDBに接続とかは普通だったと思いますが、今やC++でDBに接続って少ないと同じようにコンピュータ資源も大幅に変わってしまってるので一概に言えません
	//
	// 4.は、STLで置換しちゃいます
	// 5.は、うーん、これはしょうがないです。でも、そこら辺をガリガリ書かないといけないのはレアケースじゃないかと
	// というかLv5でこの辺触るならそりゃ悪夢です。
	//
	// C言語ならしょうがないけど、C++で生ポインタがバシバシ出るとしたら。。。勉強不足かコピペ坊やかC言語からの拘りか。。。
	// C++でほとんどポインタが不要になったのはSTLと参照のお陰です。C言語のようにデータ構造を自分で組まないといけないってのがまぁありませんので
	// 
	// [ポインタはほとんど使うものじゃない]
	// 原則C++で生ポインタを使用しないでください。その方がバグが減ります(多少高速に動作する可能性がないとは言えませんがね。多少ですし)。
	// 第一ポインタでは誰かがどこかで書き換えるとか複数の引数に渡されたポインタが必ず別変数であるとかがコンパイラは分からないので、
	// 最大限に最適化できないことが多いのです。
	// また、初期の頃のJavaやらC#(C#はまだましか)が猛烈に遅かったのは、一つにあのnew ばかり出るのが理由です。
	// JavaやらC#は原則オブジェクトをヒープに置きます。C++でもmallocやらnewをするとヒープに置きます。
	// で、普通のローカル変数はスタックに割り当ててレジスタを使おうとコンパイラは頑張ります。
	// レジスタを使うと高速です。
	// また、ヒープを取得する処理自体に結構なコストが必要で、チマチマ取得するとかなり危険です。
	//
	// 確証はないですが、多分VMは最初にある程度のヒープ領域を確保して、newされたら実体を確保じゃなくて、既に確保済みの領域のポインタを
	// 割り当てるようにしているんじゃないかと思われます(これは昔からC言語でお馴染みの技法)。じゃないと、あれだけnewしてるのに早いわけがない。。
	//
	// 高速化ついでに言うとグローバル変数も安易に使うと高速化されません。
	// いったんローカル変数にコピーしたりした方が高速化が確実に適用されます。だって、グローバル変数もどこかで誰かが変更したり
	// するかもしれないので、コンパイラさんは頑張れないのです

	// もし、ポインタに興味が出て、きちんと理解したいと思うなら、
	// "新・標準プログラマーズライブラリ C言語 ポインタ完全制覇 前橋 和弥" 2,678円とか買って読んでください。
	// 現存する本できちんとまとまってるのはこれ位じゃないんちゃいます？2678円なんて勉強のためなら屁みたいなもんでしょ？
}

/// <summary>
/// 値渡しってやつです
/// </summary>
/// <param name="a">値渡しされる変数</param>
void sample1_1::func7(int a)
{
	// 値渡しの場合、呼び出し元の変数の値がコピーされて渡ってきます。
	// だから呼び出し元の変数になんら影響を与えません
	// ただの整数、小数を渡す場合は値渡しの方が最適化される確率が高いので
	// 整数、小数では原則値渡しにして下さい。
	// 十分小さな構造体だったり、少量の文字列しか格納されていない確信がある変数なら
	// 値渡しで十分だし早いのですが、考えるのが面倒の一言でそれらは全部参照渡しにしてもOK

	// 実を言うとC++11以降ではムーブて概念があるので、条件がそろった場合値渡しの方が効率良いのですが、
	// 多分、その条件を全部理解できてる人はそもそもLv5じゃないので、ちょっとこのクラスはサイズでかいな
	// と思ったら素直に参照渡しにしておけば、問題になることはないだろうと思います
	int b = a;
}
#pragma endregion 参照_ポインタ_値渡し

#pragma region 型推論
/// <summary>
/// 型推論を説明する。ただそれだけ
/// </summary>
void sample1_1::func8()
{
	// C++で出来る型推論は次の2つ.autoとdecltype
	// でも、多分基本型は型を明示した方がいんじゃないかなぁ。
	// ちなみに引数(それはラムダで活躍)や関数の戻り値にも使える。
	// が、なんつうか
	auto a = 10;					// aはint型になる。
	auto b = func3(3);				// bはsample1_1::func3()の戻り値からint型になる

	// decltypeはちょっと面白くて、与えられた式から型を得ます
	// ただ、decltypeはテンプレートを使ったり、後置型の関数宣言を使う場合に大活躍ですから、
	// まぁLv5だとautoだけでいいと思う
	double c = 10.0;
	decltype(c) d = 20.0;	// cがdoubleなのでdはdoubleになる。関数とかを与えて戻り値の型を得ることもできる
}
#pragma endregion 型推論

#pragma region static
// staticについてのべておこうか。正直現場であまり使われないけども
// それにstaticの変数はまだしも関数なんて、そら使われてませんよ。えぇ。悲しい話ですが
void local_func1();

/// <summary>
/// staticの説明のためだけ。意味のある処理は全くない
/// </summary>
void sample1_1::func9()
{
	local_func1();
}

// 関数の先頭にstaticを付けると内部結合関数になります。
// 簡単に言うと、Sample1-1.cppの中ではどの関数からも呼び出しができるけど、他のファイルからは呼び出せない。
// いわばそのファイル限定のグローバル関数とでも呼ぶべきもの
static void local_func1()
{
	static int a = 10;	// 静的ローカル変数って言うのだっけかな。
						// ローカル変数は関数から抜けると削除されますが、この変数は関数を抜けても、ローカル変数と違って値が保持されます。
						// まれに使いますがマルチスレッドで使うと死ねます。
}

static int b = 10;	// ソースプログラム側で関数内以外の場所で宣言されたstatic変数はそのファイル内でのみ
					// グローバルにアクセスできる変数になります。ヘッダ側に書くのとはちょっと意味合いが変わります。
					// クラスを使用する場合、そう必要になることはありませんけど、ライブラリなんかだとまれに使います

#pragma endregion static
