/**
**********************************************************************
* @file		Sample0-Global.h
* @brief	浅くC++言語 を学ぶためのSample0
* @date		2021/04/13
* @par		Copyright
  (c) 2019-2021 Bunya
**********************************************************************
*	@par	History
*			- 2019-10-23 Bunya
*				-# 新規作成
*			- 2020-08-11 Bunya
*				-# 内容を修正。
*			- 2021-04-13 Bunya
*				-# ミスや誤解を招く内容を訂正。
*
**********************************************************************
*/

// 大枠：グローバル、変数、定数、名前空間

// pragma onceはインクルードガードといって多重にincludeされるのを防ぐためのおまじないです。
// 現在、ほとんどのメジャーなコンパイラ(というか使えないのは大昔のものだけ)で使用できます。
// ただ、知らない人もいて場合によっては伝統的な#ifndef, #define, #endifを用いることもあります。
// が、そうじゃないならpragma once使えばいい。
// ※ 逆に何らかの方法をとらないとすぐにビルドエラーを食らうと思う。ある有名なコーディング規約で
//    多重にインクルードするなというのがあるが簡単に起きちゃうから現実的じゃないと思う
#pragma once

/************************** 定数 ***************************/
// C言語から続く伝統の定数宣言。本当は非推奨ですが、現場で良く使われるので。。。
// #defineもプリプロセッサです。役割はプログラム中に出てくる直後の単語(この場合、LOOP_MAX)を、
// その後の文字列に置き換えること。つまり、LOOP_MAXは全部コンパイル前に121に置き換わるってこと。
// ちなみに非推奨の理由
// 1. 後で出てくる関数プロトタイプと関数実装で変数を宣言した場合に問題が出ることがある(=ビルドエラーの元)
// 2. 同じdefine定義は後から読み込まれる値が優先され、警告すら出ないこともある(=バグの元)
// 3. グローバルな空間を持ちnamespaceやenumを侵食するので、同じ名前が使えない(=既に定義済みになる)
// なお、defineはC言語からの名残ですべて大文字＋アンダースコアで記述するのが一般的だと思います。
#define LOOP_MAX 121

// また、このdefineを使ってマクロ関数なるものを作ることができますが、一部を除いて
// 使わない方がいいです。自分で使うのもなるべく避けて下さい。なので書きません。
// ※ C++ならinline関数を使うかtemplateにしてしまうのが常套手段。マクロ関数はまず不要です。
// 使うとしたらVSの_countofかoffSetof(Lv5では確実に使わない)とかですかねぇ・・・

/************************** 名前空間 ************************/
// これは名前空間。C#なんかにあるものと基本は同じ変数、定数、関数、クラスなど様々ものを分類・階層化するのに使用する。
// アクセスする場合はsample0_global::変数名となります。(書かないけどネストも出来るよー)
// C#と同じで、別名前空間からは、あることをしない(C#のusing構文みたいなもの)と省略して記述することはできません。
// ただし、同じ名前空間内にある関数などからアクセスする場合は省略することが可能(でも、付けると意味が明確なのでそれでもいいけど)
// ちなみにいわゆるグローバルというのはC++では名前空間に囲まれていないもののことで、グローバル名前空間と呼ぶ。
//
// 余談だがC#が.でつなげていくのに対してC++は::なのでたまに忘れていてはまる。とくにDLLやEXE呼び出しの時はまる。
// std::みたいに::をたくさん付けるのが気持ち悪いという意見を聞いたことあるが、C#でもusingしてないと.ばっかり出るのでそれは気持ち悪くないのか？
// と不思議に思ったことがある。
namespace sample0_global {
}

/************************** グローバル定数 *******************/
// C++でグローバル定数として使う場合はこんな風にヘッダにextern const 型 変数名で宣言して、
// どこか一か所でconst int 変数名 = 定数値と定義を書くのを推奨。
// これだと定数値を変えてもその一か所だけのビルドで済むし。
// constは変更されない値ということでC++からは配列のサイズ宣言にも使用できる。
// ヘッダに書く場合、const int loop_max;とすることは出来ない(書き換え不能なのに値が与えられないので、値を初期化できないから)。
// そのためヘッダはexternを付けて、どこかに実体定義している奴が居るよでやり過ごす。
// クラス内で使用する場合は少し癖があるので多分後で記載する。
//
// ちなみに変数に対するexternですが、
// "Ｃ言語の場合、グローバル変数はstatic修飾子を付ければ内部結合になるが、付けなければ外部結合。
//  でもC++ の場合は、extern修飾子を付ければ外部結合で、付けなければ内部結合。"
// とC言語とC++で扱いが違います。
extern const int loop_max;

/************************** グローバル変数 昔話(無視してよし) ****************/
/*
// ちなみに、C言語では↓の方法を用いるのがお約束。
// ヘッダ側
#ifdef GLOBAL_DEFINE
#define GLOBAL
#define GLOBAL_VALUE(v) = (v)
#else
#define GLOBAL extern
#define GLOBAL_VALUE(v)
#endif

GLOBAL int g_value;   // この場合は0で初期化。値なしのグローバル変数は0初期化されることが決まっているため
GLOBAL int g_value GLOBAL_VALUE(1);	// こっちだと1で初期化される

// そして、これを宣言したヘッダファイルをglobal.hなんかにしてる場合、
// どっか一か所の.cppファイル(仮にglobal.cppとする)で
#define GLOBAL_DEFINE
#include "global.h"
// とすることで、global.cppだけでexternなしの実体確保が行われ、他のファイルではexternした変数(というか定義しただけの変数)扱いとなる。
//
// ※externを入れる理由はC89で追加された変数の仮定義が大きく関わってくる。
//   でもなぁ、C言語の場合externありなしがまったく外部結合有無(=externなしでも変数は外部結合)に関係しませんからなぁ。
//   ま、皆参照してるか書き換えているはずだよって目印替わりになる位でしょうかね。
//   ちなみに、これもあんま知られてない。だからって、これで揚げ足を取るのは、紳士淑女の嗜みじゃないな
//
//   Cの聖典？(いわゆるK&R)から引用しておく。
//   "初期値式をもたず、またextern指示子を含まない外部的なオブジェクト宣言は、仮の定義と呼ばれる。
//    オブジェクトの定義が翻訳単位に現れると、仮の定義は単に冗長な定義として扱われる。
//    そのオブジェクトに対する定義が翻訳単位に現れないときには、仮の定義はすべて、初期値0をもつ単一の定義になる。"
// 分かりやすく？書くと、
// "(コンパイルまたはリンクされる一連のソースファイル)内に書かれたグローバル扱いの複数のint 変数1は、
// 初期値を代入する式がなければ暗黙ですべてがint 変数=0にまとめられる。
// もし、初期値を代入している式が一つでもあればそれを唯一の定義とみなす。(複数定義があったら当然エラー)"
// で、externは仮定義扱いで全部無視される(つまり、GLOBAL_DEFINEが#defineされてないソースすべてで無視)。
// でも実体確保しないと0扱いなのでglobal.cで#defineいれて実体確保。という話
//
// これがお約束の理由はこうやってグローバル変数を1ファイルにまとめないと、ある規模を超えると収拾不能になるから。
// だけど、不幸にもこうしているのを見たことがあまりない。。。
//
// グローバル変数なんて不要！という話もあるが、
// 例えばログを実施するインスタンスってグローバル変数の方が楽ですよね？(どこで使うかわからないから)
// ちなみにシングルトンとかも大抵グローバル変数の代わりになってるのに、あれはデザインパターンでグローバル変数じゃない！
// という素晴らしいご意見を伺ったことがある・・・いや、グローバル変数じゃろｗ
*/

/************************** 変数型 **************************/
// というわけでグローバル変数(定数?)として変数型の説明をば
// あ、名前は滅茶苦茶です。とてもよくありません。
// せめて名前空間に入れるか、globalなんていうプレフィックスをつけておくべきです。
extern const char c_loop_max;		// char型。C言語から伝統的に文字列を格納してきましたが、
									// c++での文字列は後に出るstd::stringとかを素直に使ってください
extern const wchar_t wc_loop_max;	// wchar型。ワイド文字列と呼ばれる奴でまぁWindowsならUTF-16みたいなもんかなぁ。
extern const short s_loop_max;		// short型。でもそんなに現代で使う必要があるのだろうか？メモリを激ケチりたいとか？
extern const int i_loop_max;		// int型。CPUが最も扱いやすいサイズになる(規格上これだけ以上は表現できないといけないことになっているけど)
									// 16bit, 32bit, 64bit CPUでサイズが変わってしまうことに注意。
extern const long l_loop_max;		// long型。intより大きな数字を扱えれることになっているが、Windowsではintと違いがないはず
extern const long long ll_loop_max;	// long long型。大体8バイト扱い。64bit CPUではネイティブに扱えるが32bit OSとかだと、64bitで扱うために
									// ソフトで色々やってるよぉ。
// これに+/-を考慮しないunsigned 型がそれぞれあり

extern const float f_loop_max;		// 単精度浮動小数。現在はゲーム(16ARGB)とかGPGPU。ディープラーニングにしか必要ない。
									// あ、でも今ディープラーニングは8bit型使うのが増えてるんだっけかなぁ。
extern const double d_loop_max;		// 倍精度浮動小数。小数使うなら素直にこれで。ただ、誤差は出るからお気をつけを
									// ちなみに大抵のCPUではdoubleがネイティブなのでfloat使うとそのための変換とかが必要なので、遅いよ。
									// 本当にfloatはメモリをケチる必然性がある時以外使うんじゃない。
									// とはいうものの、CPUによってはfloat専用に定義される型があったりして、実はそっちの方が早い場合もあるので
									// 簡単に言い切れないのだけど。。。
extern const long double ld_loop_max;	// doubleと同じ場合もある。滅多に使われない。
										// ただし、暗黙の型変換というものが発生する場合、必ず以下の優先順位になるので注意
										// char < short < int < long < float < double < long double
// 実数型にunsigned型はない

extern const bool b_loop_max;		// ブール型。trueとfalseをとる。

extern const char* str_loop_max;	// 文字列定数(今ならstd::stringの配列とかでもよいけど)

// 型について追記
// char型はかなり厄介です。charと書いた場合、符号付きか符号なしかは実装依存です。
// VSだとcharは符号付きだったと思います。
// で、このchar型ってビット演算とかで多用されるんですが符号なし型に入れるかキャストってのをしないと
// 符号付きのため期待した結果にならないことがあります。
// ※本当はC++なら文字列はstd::string、unsigned charをバイナリのバイトデータとして扱って、
//   charを文字に使うとかバイトデータとして扱うのはやめていただきたいのであるが。。。
//
// それと同じでchar 1byte, short 2byte, int 4byteって考えてる人がいますが、
// 実際の規格ではここからここまで表現できなければいけないと書いてるだけです。
// んでもまぁ、Windowsでしか触らないだろうから、
// char 1byte, short 2byte, int 4byteでいんじゃないかなぁと。
// longは勘違いするかもしれませんが4byteです。Windowsでは64bitであろうとそうなんです。(Linux と Macだと話違うで。最近のARMもそうかもね)
// 8byte使う時はlong long一択です。
// あと、実数はlong doubleは忘れ去るとして、floatも意味あって使える人はこんな話を読んでないので、
// doubleだけ覚えとけばOK。
// 蛇足) 多分現場ではサイズに合わせて型を宣言するように言われるでしょうから、本当に蛇足なんですけど、
//      現代なら余程のことがない限り整数にはint or unsigned intだけ使うのが幸せになると思います。
//      型変換(整数拡張含む)とかx86の制限とかメモリたくさんetcを考えると。
//      むしろ数バイト ケチりたいためにshortとかにしたら、x86の制限で遅くなる可能性大なのだが。。。
