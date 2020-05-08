/**
**********************************************************************
* @file		Sample3-1.c
* @brief	浅くC言語 を学ぶためのサンプル3-1(実装)
* @date		2019/06/25
* @par		Copyright
  (c) 2019-2019 Bunya
**********************************************************************
*	@par	History
*			- 2019-06-25 Bunya
*				-# 新規作成
*
**********************************************************************
*/
// 大枠：要素指示子付きの初期化、複合リテラル、可変長構造体、文字列リテラル、可変長マクロ、VLA

#include <stdio.h>
#include <stdlib.h>
#include "Sample3-1.h"

/************************** 要素指示子付きの初期化 ***************************/
/**
* @brief		要素指示子付きの初期化(C99より)の説明用
* @param[in]	なし
* @param[out]	なし
* @return		なし
* @detail       briefに全部書いてる。
*/
void Sample31Func1(void)
{
	// C99から搭載された要素指示子付きの初期化です。論より証拠で、まず見て
	typedef struct {
		int a;
		int b;
		int c;
		int array[10];
	} Hoge;

	Hoge hoge = { .b = 3,.c = 5, {[3] = 10, 11,[6] = 12} };	// ここね
	printf("hoge.b=%d, hoge.c=%d\n", hoge.b, hoge.c);
	printf("hoge.array[] %d %d %d %d %d\n",
		hoge.array[2], hoge.array[3], hoge.array[4], hoge.array[5], hoge.array[6]);

	// 構造体、共用体、配列の要素を個別に指定して初期化が出来ます。残りの要素は全て0です。
	// (0と言ってもポインタならヌルポインタで小数なら0.0に初期化しますけど)
	// これだけでも大変便利ですが、次に述べる複合リテラルが組み合わさると激しくC90とは変化します
}

/************************** 複合リテラル ***************************/
typedef struct {
	double x;
	double y;
} Point;

/**
* @brief		posのメンバを2倍にします
* @param[in]	pos    Point型の引数
* @param[out]	なし
* @return		なし
* @detail       引数のメンバを2倍にします。意味はありません。
*               また、ポインタを説明したら変わるかもしれませんが、この位のサイズの構造体なら別に値渡しで十分です。
*/
static Point DoublePoint(Point pos)
{
	const double raise = 2.0;

	// ポインタで返すのはやめとけ。
	// 後で述べる生存期間の問題から不定値になる。
	// 大きな構造体の中身を変更する場合は後で述べるポインタ渡しを使うことを推奨。
	// ま、多分C++同様最適化で大した問題にならない気はするけど
	return (Point) { (pos.x * raise), (pos.y * raise) };
}
/**
* @brief		複合リテラル(C99より)の説明用
* @param[in]	なし
* @param[out]	なし
* @return		なし
* @detail       briefに全部書いてる。
*/
void Sample31Func2(void)
{
	Point result = DoublePoint((Point) {.x = 10.0, .y = 2.0});
	printf("double! x=%f, y=%f\n", result.x, result.y);

	// 複合リテラルは (型名) {.メンバ名=初期値, ...}という形で構造体や配列についてリテラル(定数みたいなもの)を
	// その場で作成するものです。
	// C90では、構造体引数に渡す場合、元々用意されている変数か関数を呼ぶためだけの一時変数を作る必要があり、結果的に
	// double hoge1, double hoge2ってな感じの引数にすることがままあったと思います。
	// ただ、関数の引数を構造体にするのはメンテナンス面でとても利点があります。
	// C99からは大変楽になるので、バンバン使うべきです。あと初期化も楽勝だしね
	result = (Point) {0};	// 0初期化はこれでOKです。C++での一時オブジェクトによる初期化に近いノリ

	// 配列の場合の複合リテラルは少し複雑(ポインタを用いる必要あり)なのでまずは構造体で使うのをマスター推奨。
	// ちなみに生存期間はそれが宣言されたスコープ内です。

	// 詳しくは知らないのですが、この機能はgcc拡張によりかなり以前からLinuxカーネルで多用されていたそうです。
	// なので便利だから規格に取り込まれたんじゃないかなと思います。
}

/************************** 可変長構造体 ***************************/
/**
* @brief		可変長構造体(C99より)の説明用
* @param[in]	なし
* @param[out]	なし
* @return		なし
* @detail       briefに全部書いてる。
*/
void Sample31Func3(void)
{
	// ま、これの正式名称をなんていうか私知りませんけども、
	// 構造体を使って可変データを扱うお約束構文がありました。
	typedef struct {
		int x;
		int y;
		char data[1];
	} VAR1;
	// この構造体と後で述べる動的確保ってなもんで伸縮自在のデータを表現するってものです。
	VAR1 *bmp1 = malloc(sizeof(VAR1) + sizeof(char) * (10 - 1));
	if (bmp1 == NULL)
		return;

	bmp1->x = 10;
	bmp1->y = 1;
	bmp1->data[2] = 1;
	// C90では実際の所、配列の宣言に[0]が出来なかったので、1つだけ用意して
	// サイズ計算では-1してるというやつですね。
	free(bmp1);

	// それで、これはgccだと独自拡張で[0]が使えていて、Linuxカーネルとかでも見ることが出来るんですが、
	// C99で構造体の最後のメンバに限って[]というのが認められました。こうです
	typedef struct {
		int x;
		int y;
		char data[];
	} VAR2;
	VAR1 *bmp2 = malloc(sizeof(VAR1) + sizeof(char) * 10);
	if (bmp2 == NULL)
		return;

	bmp2->x = 10;
	bmp2->y = 1;
	bmp2->data[2] = 1;
	free(bmp2);
	// 無駄な計算がなくなってスッキリしました。

	// ま、それは分かったけど、こんなの使わないよね？って人もいると思います。
	// けど、結構身近で使われてます。組み込みだとRTOSのタスク間通信で使うメッセージはまずこの形なわけですが、
	// それ以前にビットマップはまさにこれです。
	// ビットマップはこの形＋構造体をバイナリでそのまま保存っていう荒業もやってますけどね。
	// ビットマップの構造を知ってる人ならご存じでしょうが、ビットマップはヘッダとデータ部に分かれます。
	// んで、ヘッダ部はサイズなどのさまざまな情報が格納されてデータの先頭にくるのですが、データ部は可変なので
	// この方式でもって画像データが最後にくっついています。

	// 余談
	// 本当はどちらにせよ、このやり方って規格的にアウトっちゃアウトなんですが、まぁ無視でいいでしょう。
	// 広く使われてますし。
	// ただ、構造体をバイナリ形式でファイルに保存/読み込みっていまだに組み込みでは使われてます。
	// 保存/読み込みが楽(読み込みは構造体のサイズ分読み出すだけ)だからなんだと思いますが、
	// 構造体の形を変える、アライメントの指定をミスる、OSやコンパイルを変えるなんてことをすると正しく保存/読み込みが
	// 出来なくなって、データの互換性がなくなるというとっても痛いデメリットが存在します。

	// 以前とあることで"こんなやり方規格的には保証されてませんけどね"なんてうっかり口にしてしまい、えらく吊るされた
	// ことがあります。曰く、"様々なソースで使っているのに、それが本当なら大問題ですよ"みたいなノリで。
	// が、残念なことにC言語の規格(私が知らないだけかもしれませんが)において構造体のデータをバイナリでファイルに出力し、そのデータを再度同じ構造体
	// に読み込んだら、同じデータが手に入るなんてことは欠片も記述されてないし、保証もされません。
	// ていうか別のOSとかにもっていって同じように動くデータ形式になるわけがないｗ
	// まぁもし"同じ"(バージョンその他を含め)コンパイラとOSで動かすなら、わざわざそんな手のこんだことをするとは思えませんけど。
	// 私としては規格で保証されない(私の知る限り)し、データの柔軟性(アライメントの影響とか削除/追加に弱い)がないこともあってかなり嫌いです。
	// 書き込み読み込み用のヘルパー関数を用意するだけのことなんですけどねぇ。iniファイル使うことも多いですし。
	// iniファイルも結構お約束みたいなのが多いので、CSV、XMLやJSONみたいな拡張しやすいファイルで保存して
	// おけば後が楽なのにと何度も思ったことがあります。
	// 最悪テキストで書いても手間じゃないだろうなんて。データの機密性が必要なら独自暗号化でもすればいいだけでしょうし。

	// ぶっちゃけ、組み込みではデータの後方互換性を客から強く求められることが多いです。
	// なので、構造体をバイナリで出力してる場合、仕様拡張に備えてdummyというメンバで結構なサイズをがめておき、
	// メンバを追加するたびそのdummyを減らして対処なんて汚いことやります。さらにメモリアライメントをそろえるため4byteと思われる型で調節するみたいな。
	// そういう小細工を行った結果、全体のサイズが同じなら一応そのまま読み込めるので。
	// しかし、それなら最初からテキスト形式とかで対処する方が楽なのでは？と思うんですけどねぇ。
	// dummy領域減らすの忘れてデータ破壊起きてるのをテストでスルーしたのみたことあるしなぁ・・・

	// 以前からあるソースの修正ならまだ分かるけど、新しい機種でなんでこんな旧世代のやり方してるのか悲しくなります。
	// 普通の組み方の方が楽だと思うんだけどなぁ(勉強しないから習ったことしかできない人に考慮なんてのはあると思うが)
	// さらに余談ですが、個人的にプログラマの力量を見るには文字列、ファイルの扱いをさせてみればいんじゃないかなと思います。
	// 気のせいか、この2つの扱いがめちゃ下手な人が多いです。sprintf使えない人一回みたことありますし
}

/************************** 文字列リテラル ***************************/
/**
* @brief		文字列リテラルの説明用
* @param[in]	なし
* @param[out]	なし
* @return		なし
* @detail       briefに全部書いてる。
*/
void Sample31Func4(void)
{
	// 大した話じゃないですが、文字列リテラルって並べて書くと連結されるの知ってます？
	// なにかというとこういうことです。
	char *table[] = {
		"おはよう"
		"こんにちは\n",
	};
#define GOODBYE "さようなら"
#define SEAYOU "じゃぁね\n"

	char str1[] = GOODBYE SEAYOU;
	printf(str1);
	printf(table[0]);
	// ↑2つのprintfで文字列の結合をみることが出来ます。
	// defineの方は意図的に使うことがあるでしょうが、tableの方は,をつけ忘れたことによるバグでしょ。
	// 十中八九ね。なのでdefineの場合とかは便利に使えますがtableの方みたいに,を付け忘れたらバグの元になる
	// ので気を付けて下さいね

	// 一応これの絡みで普通のcharとwchar_tのリテラルを結合する場合、
	// 結果はwchar_tのリテラルになるってのもC99で明文化されたわけです。が、そもそもwchar_t自体を使うことが少ない。。。
	// ていうかLv5でwchar_t使うとしたらそりゃ悪夢だ
}

/************************** 可変個数引数マクロ ***************************/
/**
* @brief		可変長構造体(C99より)の説明用
* @param[in]	なし
* @param[out]	なし
* @return		なし
* @detail       briefに全部書いてる。
*/
void Sample31Func5(void)
{
	// あんま紹介しなくても良かったのですが、
	// 可変長引数って機能がC言語にはあります。
	// はっきり言って用途はログとかデバッグ出力です。通常は
	// が、お作法があるので、もちょっと気楽に使えない？と思ったかどうかは知りませんが、
	// 可変引数を取るマクロがC99で追加されました。でも、多分用途は同じだろうねぇ
#define dbg(fmt, ...) \
	printf("debug:" fmt, __VA_ARGS__)
#define adbg(...) \
	printf("debug:" __VA_ARGS__)

	// __VA_ARGS__が可変引数の証ですね。マクロは一行で書かないといけないのですが、
	// マクロ関数(でも、基本的に使うな)では複数行に渡ることが多いです。
	// 改行する場合は、\で次の行に記述が続いていることにしないといけません。

	// 使い方
	int a = 2;
	int b = 3;
	dbg("value1=%d value2=%d\n", a, b);
	adbg("value1=%d value2=%d\n", a, b);
	adbg();	// 省略もOK
}

/************************** VLA ***************************/
/**
* @brief		VLA(C99より)の説明用
* @param[in]	なし
* @param[out]	なし
* @return		なし
* @detail       briefに全部書いてる。でもコメントだけで中身はない
*/
void Sample31Func6(int n)
{
	// 可変長配列。C99では必須でメジャーなコンパイラはサポート(VSは除く)したのに、
	// なぜかC11ではオプション扱いとなった可哀そうな子です。
	// そして、配列をスタックに取る実装がなされていることがほとんど(規格上の定義は知らん)なので、
	// スタックオーバーフローに対処できないとして使うんじゃない扱いにもされてる、更に可哀そうな子です。

	// 私的には、自動変数(staticでないローカル関数ないで宣言された変数)にしか適用できないという制限から
	// サイズチェックをするか必ず小さな値しか来ないことが分かっているものには使っていいと思います。

	// ちょっとした可変サイズの配列を確保したいことってたまにあると思うのですが
}

