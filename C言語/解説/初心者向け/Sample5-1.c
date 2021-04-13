/**
**********************************************************************
* @file		Sample5-1.c
* @brief	浅くC言語 を学ぶためのサンプル5-1(実装)
* @date		2021/04/13
* @par		Copyright
  (c) 2019-2021 Bunya
**********************************************************************
*	@par	History
*			- 2019-07-08 Bunya
*				-# 新規作成
*			- 2021-04-13 Bunya
*				-# ミスや誤解を招く内容を訂正。
*
**********************************************************************
*/
// 大枠：標準ライブラリの使い方(でも、他に多数あるので使うとき調べてみて)

#include "Sample5-1.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <math.h>

// qsortの説明用
int comp(const int *, const int *);
typedef struct {
	double x;
	double y;
	char name[20];
} Point;
int compPoint(const Point *, const Point *);
int compPointReverse(const Point *, const Point *);

void Sample51Func1(void)
{
	// セキュアなのを使えとVSがうるさいので_s付きの奴は、_sを取っ払うと標準形式です。
	// が、_sがない方は引数が違うんだよなぁ。。。

	// printf
	// さんざん出てきたprintfですが、出力する関数です。
	// printf(fmt, 変数...)なんですが、fmt(書式)の所は ""で区切られた中に記入します。
	// も、本当にたくさんの書式があるのですが良く使う所を↓に
	// あぁ、そうそう忘れてましたけど、文字列って"abcd"だと4文字に見えますけど、5文字になります。
	// C言語の文字列は必ず最後が\0で終わることになっているからです。もし\0で終わらない文字列を扱う場合、
	// 分かってないと簡単にプログラムを強制終了させれます。
	struct PRINT {
		char str[16];
		short s;
		int i;
		long l;
		double d;
	};
	struct PRINT print = { .str = "print",.s = 16,.i = 24,.l = 32,.d = 3.534 };
	printf("each value str:%s, short:%hd int:%d long:%ld double:%05.2f\n",
		print.str, print.s, print.i, print.l, print.d);
	// 文字列は%s, short %hd, int %d long %ld, double %fで\n=改行。
	// でも、%05.2fってなんでしょうか？これは全体が5文字で小数点以下2桁(3桁目を四捨五入)で整数型の数字が余ったら
	// 0を左に補うって話です。もっと詳しくは使う時にどうぞ

	// ファイル関係
	FILE *fp;
	errno_t err = fopen_s(&fp, "main.c", "r");	// ファイルを開く
	if (err != 0 && fp != NULL ) {
		char line[512];
		fgets(line, _countof(line), fp);	// 1行読み込む
		printf(line);
	}
	if (fp != NULL) {
		fclose(fp);	// ファイルを閉じる
	}

	// 乱数
	srand((unsigned int)time(0));	// 乱数を初期化
	printf("random %d\n", rand());	// 乱数を生成

	// 文字判定. is～使う場合、念のためunsigned charにキャストして使うと良いよ。なんせ、引数int型ですから
	printf("'a' is %s\n", isalpha((unsigned char)'a') ? "TRUE" : "FALSE");	// アルファベットか判定。説明してない文法がｗ
	printf("'5' is %s\n", isdigit((unsigned char)'5') ? "TRUE" : "FALSE");	// 数字か判定

	// 数値
	printf("abs %d\n", abs(-11));	// 絶対値を求める
	printf("number %d\n", atoi("125"));	// 文字列を数値に

	// 文字列操作
	char temp[32];
	char src[] = "abcd";
	strcpy_s(temp, _countof(temp), src);	// 文字列コピー。絶対に\0終端した文字列を渡すこと。メモリを盛大に破壊するで
	printf("%s\n", temp);
	sprintf_s(temp, _countof(temp), "%s+%d\n", src, 123);	// printfさながらにfmtで文字列に変換する便利な奴
	printf(temp);
	strcpy_s(temp, _countof(temp), src);
	if (strcmp(src, temp) == 0) {	// 文字列同士の比較
		printf("左右は同じ\n");
	}

	// 数学系
	printf("2の平方根 %f\n", sqrt(2.0));	// 平方根
	printf("2の3乗 %f\n", pow(2.0, 3.0));	// 累乗

	// 時間
	time_t now;
	struct tm local;
	errno_t error;
	char buf[64];
	time(&now);	// 現在時刻を取得
	error = localtime_s(&local, &now);	// 国内時刻に変換
	error = asctime_s(buf, _countof(buf), &local);	// 時刻を文字列変換
	printf("時刻: %s", buf);

	// ソート
	// 数値でやっているがcompの中身を変えれば文字列だって、構造体だって並び変えれる。
	// 要はcompは関数ポインタなので自分でソートの方法を自由に定義できる。
	// qsortは条件によっては最速でもなんでもないが、標準ライブラリに用意されているものなので
	// これを上手く使いこなしてください。なんか無駄に一生懸命自作のソート関数作る人みたことありますけど、
	// qsortがvoid*なのでこれ使えよなぞと。アルゴリズムに詳しい人がやらない限り標準関数より早くなることなんざないっての。
	// というかvoid*で受けるのは何でも入れれることによる弊害があるということをおっしゃる人がいます(間違ってはない)が、
	// 基本的なライブラリをvoid*で作って一枚wrapperとして皮をかぶせたライブラリを用意しといた方が生産性がぐっと上がるので、
	// そう毛嫌いしなくてもいいのではと思う。だって、批判する以前にその基本ライブラリとやらを各社用意してませんので。。。
	int array[] = { 3,7,5,9,1,6,4,8,2 };
	for (int i = 0; i < _countof(array); i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
	qsort(array, _countof(array), sizeof(array[0]), comp);
	for (int i = 0; i < _countof(array); i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
	// 構造体＋文字列ならばこんな感じ
	Point array2[] = {
		{ .x = 5.0, .y = 7.0, .name = "bbb" },
		{ .x = 2.0, .y = 3.5, .name = "ccc" },
		{ .x = 3.0, .y = 4.0, .name = "aaa" },
	};
	for (int i = 0; i < _countof(array2); i++) {
		printf("%s ", array2[i].name);
	}
	printf("\n");
	qsort(array2, _countof(array2), sizeof(array2[0]), compPoint);
	for (int i = 0; i < _countof(array2); i++) {
		printf("%s ", array2[i].name);
	}
	printf("\n");
	qsort(array2, _countof(array2), sizeof(array2[0]), compPointReverse);
	for (int i = 0; i < _countof(array2); i++) {
		printf("%s ", array2[i].name);
	}
	printf("\n");
}

// qsort用 糞マジメに書く
// あ、そうそうqsortで渡す関数の引数はvoid*なのだけど、
// void*引数の関数を作って、関数内部で引数使う時にキャストして使う書き方をする人がいます。
// でも、普通に型に合ったのを定義してやれば↓のように不要なキャストなしで使えますぜ
// ※ void*だと必ずキャストが必要になる
static int comp(const int *lhs, const int *rhs)
{
	if (*lhs < *rhs) {
		return -1;
	} else if (*lhs == *rhs) {
		return 0;
	}

	return 1;
}
// 構造体の中の文字列を辞書式順に並び替え
static int compPoint(const Point *lhs, const Point *rhs)
{
	return strcmp(lhs->name, rhs->name);
}
// もし、降順にしたかったらこれでいんでね？
// ま、データの持ちようによっては先に判断条件が必要でしょうけどね
int compPointReverse(const Point *lhs, const Point *rhs)
{
	return -1 * compPoint(lhs, rhs);
}
