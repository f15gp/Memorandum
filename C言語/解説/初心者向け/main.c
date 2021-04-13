/**
**********************************************************************
* @file		main.c
* @brief	浅くC言語 を学ぶためのmain
* @date		2021/04/13
* @par		Copyright
  (c) 2019-2021 Bunya
**********************************************************************
*	@par	History
*			- 2019-06-23 Bunya
*				-# 新規作成
*			- 2020-09-03 Bunya
*				-# ポインタ渡しについて内容を追加。
*			- 2021-04-13 Bunya
*				-# ミスや誤解を招く内容を訂正。
*
**********************************************************************
*/

// C言語 5日で業務コード触れます(Lv5想定)のmain
// はじめに：今時C言語使わないといけないってのは大変です。
//         しかし、まぁどうしても指定言語がC言語ってことがあるでしょう、たまには。
//         なので、そんな時に落胆しないよう最低限使えるようになることを目指してみました。
// 原則：処理はmain.c以外の.cファイル、.hファイルに記述。
//      したがって、このmain.cでは大した内容を書かない予定
// 命名規則：原則関数はパスカル記法、変数はキャメル記法。
//         C言語ならスネーク記法の方が"自分の"好みだが、仕事でスネークを見たことがないので。
// 注意: C99(1999年に策定)を前提に記載予定。C11(2011年に策定)も入れるかも？
//      ただ、未だにC90で作成されたorそれ以前の内容で作られたソースが多数を占めます。
//      なので、C90でも書くべきと思う内容は記載する予定。

// 断り：本プログラムはVisual Studio(以後VSと記載)にべったり依存します。このソースはVS2019でビルドされています。
//      よってC99を全くサポートしていないVS2012以前は対象外になります。
//      ちなみにVS2017(2019は良く分かりません)でもC99は完全サポートでなく、C11の内容は少しだけサポートしている感じです。
//      ただ、C言語ではXMLドキュメントのありがたみがないのでdoxygenスタイルで書いてます。
// 環境: GitHubにUploadするため、UTF-8(BOMなし)で書いてます(GitHubにShift-JISのソースコードをUploadすると文字化けしちゃうから)。
//      しかし、VSで新規作成した場合はShift-JISで作成されるので文字コードを後から変更しています。
//      更にUTF-8ではビルドエラーになるので、プロパティ -> C/C++ -> コマンドライン "追加のオプション(D)"
//      に/source-charset:utf-8 を指定。ついでに関係ないけど、全般の文字セットも"Unicode 文字セットを使用する"に変更します。
//
//      あと、知らない人がいるので書きますが、VSの場合プロパティを変更しない限り、.cppファイルはC++、.cファイルはC言語としてビルドされます。
//      なぜわざわざ書くかというと以前これを勘違いしてC++の規格をC言語と勘違いしてそうな例をネットで見かけたからです。

// 注意：正直、Lv5じゃねぇだろ的な話も扱うかもしれない。しかし大目に見てくれ。
//      そして初学者のために、あえて不正確なことを書く(だってマジメに説明するには沢山かかないといけないし)場合がある。
//      が、多分そんなに外れたことは書いてないと思う。ただし、自分が不正確に覚えてる項目はすまんこって

/************************** コメント ***************************/
// 既に多数行書いていますが、//で行末までコメントです。
// また /* ～ */で複数行コメントとなります。
// 注意としてはC99までコメントは/* */のみ許されるのですが、ほとんどのコンパイラは//が使えます。
// ですので、C90縛りでない限り// を書いても多分問題にならないと思います。

/************************** インクルード ***************************/
// ↓は#includeを用いてヘッダファイルを取り込んでいます
//
// まず、なぜJavaやC#と違ってヘッダファイルというのがあるかというと様々ですが、一つには後で説明する定数とか関数プロトタイプ宣言を取り込むためです。
// C言語は文字の入出力などの基本的な機能も標準ライブラリに丸投げし、言語機能としては持っていません。
// 何か機能を使いたいと思ったらヘッダファイルをincludeしないとコンパイラがエラーを出してきます。
// なぜなら、xxxという機能を使いたいとするとコンパイラはこのxxxがどういった引数とかを持っているか知らないと
// どうにもできないから、このxxxとはなんじゃい？とエラーになるわけです。
// それを防ぐためにxxxが宣言されているヘッダファイルをincludeしたりするわけです。
//
// だったら、ソースファイルを取り込めば？と思うでしょうが、これはC言語的に無理です。
// #includeは正式にはプリプロセッサというものの一部でコンパイルが始まる前に動きます。
// その動作は対象ヘッダファイルを丸ごとcppファイルに"文字列"として挿入することです。
//
// 2つ以上の異なるソースファイルから別のソースファイルをincludeすると、
// 文字列で挿入しているので関数の実体が複数あることになってコンパイルエラーが多発します。
// よって、関数に関してはプロトタイプ宣言(後で説明)だけが書かれているヘッダファイルをincludeします。
// ま、定数とかグローバル変数とかもヘッダファイルにあるけんど。
//
// 他にも理由はあるので、C言語での業務では十分お気を付けを
//
// ちなみに、まず見かけませんが、本来ヘッダファイルは対象の.cファイルが読み込むだけのプライベートなヘッダと
// 外部に公開するパブリックなヘッダが分離されるべきです。カプセル化にもなるし、ビルド時間の短縮が出来ることもある。
// ま、ちょっとこのサンプルだと分離しませんがね。面倒な(ry
//
// C言語で定められている機能や定数が宣言されたりしているのは標準ライブラリと呼んだりします。
// で、その機能とincludeするヘッダはおいおい登場していきます。

#include <stdio.h>	// このmain.cでは使用しないがサンプルなので

#include "Sample1-1.h"
#include "Sample2-1.h"
#include "Sample3-1.h"
#include "Sample4-1.h"
#include "Sample5-1.h"

// ちなみに#includeには#include <>と#include ""の書き方があります。
// これはどこを基準にしてヘッダファイルを探すかの違いだけなので、
// 標準ライブラリのヘッダファイルとかは<>で、自分たちで作ったヘッダファイルは""にしとけば問題ないんじゃないかと

// この後#if と #endifを多用するので軽く説明。
// #if 0～#endifはその区間は無効、#if 1～#endifはその区間が有効ということ。
// #if, #elif, #else, #endifを駆使して色々やることがマレにある。
// これらも全てプリプロセッサなのでコンパイル前に文字列置き換えを色々やります。

// あぁ、そうそうC言語では各ヘッダ、ソースファイルの最後が改行で終わらないといけません。
// じゃないと未定義動作です。まぁ、たいてい問題になることはないのですが、規格的にはそうです。
// 典型的な間違いは、↓な感じ
// int main(int argc, char *argv[])
// {
//     return 0;
// }EOF
//
// 正式にはこんな感じ(規格上はもうちょっと長い文章)で書かれています。
// "空で無いソースファイルは改行文字で終了しなければならない。さらに、この改行文字の直前に(接合を行う前の時点で)斜線があってはならない。"

/**
* @brief		いわゆるスタートルーチン(プログラムを起動した時、最初に呼び出される場所)です。
* @param[in]	argc    プログラム起動時の引数個数
* @param[in]	argv    プログラム起動時の引数値が入ったポインタの配列
* @param[out]	なし
* @return		プログラムの終了状態
*				- 0    正常終了
*				- 0以外 異常終了
* @detail       泣く子も黙る？main関数。ちなみに、VSはint main()で作成します。
*               C言語の規格書に書かれているから無難な宣言は
*               int main(int argc, char** argv), int main(int argc, char* argv[])のいづれか。
*               引数と戻り値については誤解が多いので関数の時改めて記載しますが今はこのくらいを理解すればOK
*/
int main(int argc, char *argv[])
{
#if 1
	/************************** Sample1-1 ***************************/
	{
		Sample11Func1(1);	// ほら、引数を渡せる
		int a = Sample11Func2();
		int b = Sample11Func3(3);
		Sample11Func4();
		Sample11Func4();
		//Sample11Func5(); エラーになるのでコメントアウト
		Sample11Func6();
		Sample11Func7();
	}
#endif

#if 1
	/************************** Sample2-1 ***************************/
	{
		Sample21Func1();
		Sample21Func2();
		Sample21Func3();
		Sample21Func4();
		Sample21Func5();
	}
#endif

#if 1
	/************************** Sample3-1 ***************************/
	{
		Sample31Func1();
		Sample31Func2();
		Sample31Func3();
		Sample31Func4();
		Sample31Func5();
		Sample31Func6(128);
	}
#endif

#if 1
	/************************** Sample4-1 ***************************/
	{
		Sample41Func1();
		Sample41Func2();
		Sample41Func3();
		Sample41Func4();
		Sample41Func5();
		Sample41Func6();
		Sample41Func7();
	}
#endif

#if 1
	/************************** Sample5-1 ***************************/
	{
		Sample51Func1();
	}
#endif

	return 0;
}
