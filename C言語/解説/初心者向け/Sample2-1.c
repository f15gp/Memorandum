/**
**********************************************************************
* @file		Sample2-1.c
* @brief	浅くC言語 を学ぶためのサンプル2-1(実装)
* @date		2019/07/08
* @par		Copyright
  (c) 2019-2019 Bunya
**********************************************************************
*	@par	History
*			- 2019-07-08 Bunya
*				-# 新規作成
*
**********************************************************************
*/
// 大枠：制御構造、enum、構造体、共用体、typedef

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sample2-1.h"

/************************** 制御構造 ***************************/
/**
* @brief		制御構造の説明用
* @param[in]	なし
* @param[out]	なし
* @return		なし
* @detail       briefに全部書いてる。
*/
void Sample21Func1(void)
{
	// そろそろ説明がきつくなってきたので、いい加減制御構造を説明

	/* じゃ、ループ3種です */
	// for(初期化; ループ条件(条件成立でループ); 変化式)
	// 初期化とかは不要なら書かなくてもOKです。
	// また、C#を除いて以下の{}を省略した書き方はまずしないと思います。
	for (int i = 0; i < 3; i++)
		printf("i = %d\n", (i+1));

	// C99では↑は↓の内容に暗黙で展開されます。
	// なので目に見えないスコープとかが発生するので、中括弧を素直につければいんじゃないかと
	// 余談ですが、今は多くの職場で{の行下げが多いと思います。
	// が、一部の職場での理由には寂しいものがありますけど
	for (int i = 0; i < 3; i++) {
		printf("i = %d\n", (i + 1));
	}

	// あとループさせるのに2つ構文があります。
	// whileとdo-whileってものです。

	// while使う人は結構いますが、私はまぁ滅多に使いません(お約束の表現とかでは、それに従いますが)
	// 理由として、forとwhileが混在すると何を基準に使い分けるべきか困るってことです。
	// あと、他の言語でもforだけ特別扱いの文法あったりで、for使うの優勢なのかなと。
	// C言語でwhileがforより良く使われたのは、大昔はwhileの方が早かったからです。アセンブラレベルでｗ
	// 使いたい人はネットでもなんでも見て下さい。すぐに見つかります

	// do-whileですが、これは必ず一回は実行されるべきループを実装する場合だけに使います。
	// なので普通は使いません。たくさん出てきたら、アルゴリズム自体疑った方が良いでしょう。
	// ただ、この後書くgotoを使いたくない意味不明な方々(いや、主義主張はあるでしょうが)が生み出したイディオムとしてdo-whileを用いるのがありますね。
	// 確かにgotoが登場しないけど、do-whileっていう滅多に使わない構文でgotoと似たことをするのってどうなんでしょうねぇ。
	// 読み難いし思考が乱されると思うんだけどなぁ。完全にgotoの代わりになるわけじゃないし
	// ま、これも使いたい方が自習で。いや、本当滅多に使わないし(自分が滅多に使わないから、そのたびに忘れて調べるのは内緒だ)

	// if
	// 条件判断です。if の括弧の中が真なら実行されます。真というのはその条件式が成立するってことです。
	// ぶら下がりelseと暗黙のブロック(for同様に)があるので、中括弧使うの推奨
	if (1) {
		printf("真\n");
	}
	// その逆として偽(条件式が成立しない)というのがあります。偽はelseの方が実行されます
	if (0) {
		printf("真\n");
	} else {
		printf("偽\n");
	}
	// ま、C言語は条件をキチンと書いてやってもいんですが、0=偽、0以外=真なのでそれを悪用する人もいます。
	// ちゃんと使う人もたくさんいますけど。あ、!は逆の条件になります
	if (!1) {
		printf("こない\n");	// ここには絶対来ません。メンテ忘れとか悪用でこういうありえないifが生まれることがあります
	}
	// 複数条件を比較するときはelse if使います。
	// &&は左と右が成立すれば真、||は左または右が成立すれば真。
	int x = 10;
	int y = 11;
	if (x == 1)	{
	} else if ((x == 10)&&(y == 11)) {
		printf("ここに来る\n");
	} else if ((x == 10)&&(y == 12)) {
	} else {
	}
	// ちなみに&&とか||は左から順番に調べ、成立しなくなるとそこでチェックが終わります。
	// これを利用したコードもあるので、一応留意ね。

	// 条件に合致するしないで、必ずどちらかの処理を実行しなければいけない場合でelseの書き忘れにご注意

	// break, continue
	// あー、えっと身も蓋もない言い方すると隠れgotoです。Javaの場合、ラベル付き○○っていう言葉でけむに巻いてますが
	// 完全にgotoです。なので滅多やたらに使ってはいけません
	// 使い方はループまたはswitchから抜け出すとか処理をスキップするためです
	for (int i = 0; i < 10; i++) {
		if (i < 5)
			continue;	// 5以下はループの先頭へ。無駄な処理をさせないための枝刈りって手法が主な使い道かなと

		if (i == 8)
			break;		// 8になったらforから抜けます。でもこれは悪い手段です。これなら8回ループするのが自然です

		printf("continu & break i = %d\n", i);
	}
	// 当たり前ですが出力されるのは5,6,7です

	// switch
	// if - else if - elseに似てますが、主に条件式の結果が複数ある場合に使います。
	// 自分の使い分けは同じ条件式の場合はswitch、複数の条件式がある場合はelse ifにしています。
	// 3分岐以上なら確実にswitch使いますな。色々な会社に残る修正コメントを残す時に修正しやすいとか、
	// 1度増えた時は2度以上増えるが経験則なのでifにしてるとつらくなります。
	// ただし、条件式の評価結果は整数のみで文字列が使えないため、その場合はifにせざるを得ません。
	// またジャンプテーブルにする関係でしょうが、同じ値を持つcase式は書けません。
	int a = 10;
	switch (a) {	// ここは変数にしてますが、変数以外に条件式が来ます
	case 0:
		break;
	case 1:	// フォールスルー break;がない場合処理が↓に流れるので意図的にやってることを示すため、私はこんなコメントを入れます
	case 10:
		printf("switch!\n");
		break;
	default: // デフォルトは一番下じゃなくても良いのだけど、基本は一番下
		break;
	}
	// あと評価の仕方なのですが、if文は上から順番に条件式を毎回評価していくのに対し、
	// switchは条件式を一回だけ評価して、あとはジャンプテーブルとかでピョーンとそこの処理まで飛んでいく
	// という違いがあります。
}

/**
* @brief		gotoの説明用
* @param[in]	なし
* @param[out]	なし
* @return		結果
*				- 0    正常
*				- 0以外 異常
* @detail       gotoの説明用として、ちょっと制御構造が長くなったので関数を分けた。
*               そして、ここの説明もひたすら長いｗ
*/
int Sample21Func2(void)
{
	// goto
	// はい、じゃ嫌われて世の中から抹殺されることを余儀なくされているgotoです。
	// でも、私は大好きですｗそして組み込み＋C言語ではgotoを使うシーンはチョクチョクあります。
	// 一応補足ですけど、goto使わなくてもC言語は組めますよ。ただ、最近の言語ではもっと良い方法があったとしても、
	// C言語の文法ではサポートされてないものが多数あります。だから、別にgoto使うのが悪いとは思わないですね。
	// たまに居るのですが、ある言語でのやり方や命名規則を言語が変わっても頑なに変えない人がいます。
	// これって、英語は日本語と違ってあれやこれがおかしい。英語も日本語と同じであるべきだっていうのと変わらない変な考えだと個人的に思うのですがね。
	// あと、Javaをけちょんけちょんにしてる内容を書いてたりしますが、Java自体は悪い言語じゃないですよ。考え方や主義主張が個人的に嫌いですけど。
	// ※ちなみに、Lv5ということを考慮しても私が良いと思っているgotoはリソース解放と多重ループからの脱出位です。
	//   ただ、多重ループからの脱出ってまず使わないし、枝刈りとかしてると普通やらないよねとは思わなくもない

	// ここはとある関数と思いましょう。
	// 詳しくは説明しませんが、ファイルを開いて何かの処理をする関数と思いましょう。
	FILE *fp = NULL;
	errno_t error;
	int ret = -1;

	// 本当はfopenなんですけど、VSがうるさいのでfopen_sを使います
	error = fopen_s(&fp, "main.c", "rb");
	if ((error != 0) || (fp == NULL)) {
		// ここは簡単なんです。だってファイルを開くのに失敗しただけなので、そのまま異常としてreturnすれば良いので
		return ret;
	}

	char buf[1024];	// 賛否両論でしょうが、1024以下に収まる内容なら固定配列で十分です。
	size_t read_size = fread(buf, sizeof(char), _countof(buf), fp);
	if (read_size == 0) {
		// さて、ここが問題です。ここでエラーが起きたらファイルを閉じなくてはいけません。
		// 閉じないと、アプリが落ちるまでそのファイルにはアクセスできなくなります。さぁ、どうします？
		// 私ならこうします。gotoの出番です。gotoは後ろにつづくラベル(慣習的に全て大文字)の場所にジャンプします。
		goto CLEANUP;
	}

	// そりゃ、たった一か所で起きたエラーに対処するなら、ファイル解放してreturnしてもいいです。
	// あるいは、全てのif文エラーでコピペしてファイル解放してもそりゃかまいません。
	// ですが、他にも解放するものがあったら？そのつどコピペで書いたエラー処理に追加します？
	// そんなものgotoで異常処理をまとめればいいじゃないですか。Javaはgotoで有益なリソース確保を出来るようにするため、
	// finallyなんて構文追加したわけですし(正直finallyの出自から考えると当初はそうだったのではないかと考えらえる)
	// さらに"メモリ以外のリソース"を必要なくなったら、すぐに解放するための構文try-with-resourcesを後に追加したわけだし。

	// 正直言うと、"大昔、goto禁止が言われ始めた時代は、for文の中でifの代わりにgotoでループ制御したり、
	// 関数(そのころは関数すらなくサブルーチンとかいうけったいなもの)の中と外をgotoで行き来する"という今では考えられない
	// かもしれない制御が普通でした。
	// でも、C言語ですら標準の文法に従う限り(ちょっと語弊あるかなぁ)、関数内でしかgotoできません。
	// なので、そもそもgotoをなるべく減らそうと言っていた時代とは、前提条件が違いすぎるんです。
	// そりゃ、goto使って関数内をぐるぐる回るようなコード書いたら私も"ゴラァ"ですけど、それはプログラムをきちんと組めない人がやることで、
	// 多分そんな人はgoto使わなくても意味不明なコードを作ると思いますよ。
	// ちにみに、gotoを無理やりifの塊であるとかdo-while-falseイディオムとかいうので表現する例をもっと↓で述べます。

	ret = 0;

CLEANUP:
	// ここで処理が異常でも正常でもファイルが開いていれば解放されるので、解放もれが起きることはありません。
	// 別に説明としてそうしませんでしたが、fopen_sの失敗もgotoしたってかまいません。
	if (fp != NULL) {
		fclose(fp);
	}

	return ret;

	// もしifでにた記述をするなら(長らくしてないので少し自信がない)
	// ↓の感じでどんどんインデントが深くなっていきます。
	// どんどんインデントが深くなるソースに対して、全てのパスをテストする自信あります？
	// というか、そもそも面倒(=テスト漏れやバグ)ですよね？
#if 0
	{
		FILE *fp;
		errno_t error;

		error = fopen_s(&fp, "main.c", "rb");
		if ((error != 0) || (fp == NULL))
		{
			return -1;
		}

		char buf[1024];
		size_t read_size = fread(buf, sizeof(char), _countof(buf), fp);
		if (read_size == 0) {
			if (fp != NULL) {
				fclose(fp);
				return -1;
			}
		}

		if (fp != NULL)	{
			fclose(fp);
			return 0;
		}
	}
#endif

	// そして、gotoを使わないために考えだされたdo-while-falseイディオムです。
	// 個人的には、"きしょ"の一言です。
	// そりゃ、なれればどうということはないですが、そこまで色々駆使して、ほぼgotoと同じことしてでも、
	// "goto"という単語がソースになければOKってなんなの？可読性下がってない？って気がします。
	// あと、このパターンって亜種が多いんですよ。whileやforでやるのを見たことがありますし

	// 認めない人が多いですが、例外処理、finally、条件付きbreak、continue、break・・・
	// こういった文法はただ"goto"と名前がないだけで実質的にgotoです。そりゃ、アセンブラにjmp命令以外ないのですから他の方法に展開しようがありません。
	// というか例外処理は、使い方を誤ると結構大規模開発で問題を引き起こしがちです。組み込みだと敵になったりしますし。
	// ※例外処理は、内部的に動的確保などが必要になるので
	// これはGCでメモリ解放なんて気にしなくていいよってアピールする代わりにusing, try-with-resources, withなどでもって
	// 確実に"メモリ"以外のリソース解放を保証しようという構文を追加したのと同じ位 意味ないなぁと個人的には思います。
	// ※C#は8.0でusing宣言を追加したのでかなりC++のRAIIに近いリソース解放が出来るようになったので、まだマシかな
	// なんで、意味がないと思うかと言うと、GCでメモリ解放を気にしなくて良いはまず嘘だから。
	// ※簡単にメモリを枯渇させたり、解放されないメモリというのを作ることができます。
	// そして、"メモリ"以外を確実に解放するため構文を追加したという点。
	// これじゃ、その構文を教えないと業務でのプログラムじゃ使えないです。
	// ※そんなの知ってるのが当たり前だという意見もあるでしょうし、ごもっともだと思うのですが、
	//   経験上、ほとんどその言語のことを知らない人が作成する例ってちょくちょくあります。
	//   最悪のケースでは規格？上そういう挙動をするのに本人が知らなくて悩んでたり、バグをスルーするなんてことも・・・
	// そりゃ、お勉強やお遊びのプログラムなら目くじらたてませんが、理解せずコピペされているプログラムを良くみるので、
	// 困るなぁですわ。不勉強の人に例外使わせると、スコープでミスるか、全例外を握りつぶしますよ、経験上ね。
#if 0
	do {
		FILE *fp;
		errno_t error;

		error = fopen_s(&fp, "main.c", "rb");
		if ((error != 0) || (fp == NULL))
		{
			ret = -1;
			break;
		}

		char buf[1024];
		size_t read_size = fread(buf, sizeof(char), _countof(buf), fp);
		if (read_size == 0) {
			ret = -1;
			break;
		}
	} while (0);	// 条件式が0なので必ずここで終わる。異常処理は全てbreakにより、ループを抜ける

	if (fp != NULL) {
		fclose(fp);
	}
	ret = 0;
	return ret;
#endif

	// ですが、まぁgoto使用禁止をコーディング規約で謳ったり、
	// 使うと無能扱いするというのが現実でしょう。(その割に"メモリ"以外のリソースを必ず解放してないのは無能とか聞いた
	// ことがないんですけどね。あと、ディープコピーすべきところでシャローコピーにしてたら無能なんてのもないし)
	// だから、声を小さくして、gotoの方が後処理が楽なこと多いよと言っておきますｗ実際スコープの絡みで面倒になることが
	// よくあるし。でも、今時こんなこと言うと、わたしゃ老害にされちゃうんでしょうかね
	// (他にもあるけど、Lv5では省略)
}

/************************** enum ***************************/
// 列挙型といいます。ただ、defineとの絡みがあって使いにくいこともままあります。
// スコープがないのでdefineに上書きされること良くあるんです。
// 特にNG、OK、ERRORなんてのがdefineで定義されてますとね・・えぇ
// 使い方はこうです。
/**
* @brief		enumの説明用
* @param[in]	なし
* @param[out]	なし
* @return		なし
* @detail       briefに全部書いてある
*/
void Sample21Func3(void)
{
	// Mon 0, Tue 1, Wed 2となります。weekはタグ名でこのenumの名前ですな
	enum week {
		Mon,	// Mon = 2とかなら2からスタート、なければ0からスタート
		Tue,
		Wed,
		// 知られてませんが配列では最後の要素にカンマありはC90でもOKです。
		// が、enumの最後カンマが許されるのはC99からです。まぁ独自拡張で大体OKになってるはずですけど
	};

	enum week wk;
	wk = Tue;	// 宣言したメンバを入れれます

	// switchに使えます。というか、多分この使い方が多いはず
	switch (wk) {
	case Tue:
		printf("火曜日\n");
		break;
	}

	// 注意なのはC++とかと違い、enumは整数との相互代入してもコンパイラはエラーにしません。
	// やってるソースを見たことありますが、理解してあえてでない限り、やらない方が無難です。
	// あえての場合でもコメント入れとかないと、勝手に真似するコピペ坊やに悩むかもしれません
}

/************************** 構造体 ***************************/
/**
* @brief		構造体の説明用
* @param[in]	なし
* @param[out]	なし
* @return		なし
* @detail       briefに全部書いてある
*/
void Sample21Func4(void)
{
	// んじゃ、まぁ重要な構造体です。
	// ビットフィールドについては書きません。組み込み以外でほとんど見たことないし

	// 構造体は複数の変数(メンバ)をまとめてデータ構造として表現するものです
	// こんな感じ。↓は宣言のみですが変数を同時に定義することもできます。
	struct Data {
		int a;
		double b;
		char c[16];
	};

	struct Data dataX = { 0 };	// 集成体型なので0初期化できます。でもC++と違って{}のみでの初期化は無理よ

	// 各メンバには↓の感じで
	dataX.a = 10;
	dataX.b = 11.3;
	// ポインタ説明してないしライブラリの説明もしてないので文字列のコピーってこうなんだと思っておいて下さい
	// VSの場合strcpyだと怒るのでしょうがなく_s付きです
	strcpy_s(dataX.c, _countof(dataX.c), "test");
	printf("a=%d b=%lf c=%s", dataX.a, dataX.b, dataX.c);
	// あえて誤解の元に規格が追認する羽目になった小数の出力に%lfを使っています。でも、皆さんは%fで使ってくださいね
	// ちなみにC++とC90では%lfを使うと未定義の動作となります。

	struct Data dataY = { 10, };
	// ifで構造体型変数同士を比較することは出来ません。するならメンバ単位で。
	// あとmemcmpってのでもって構造体の比較をするソースが結構というかかなりあります。
	// でも、メモリのアライメントを1に指定してないと泣きを見るし、1に指定するのは速度とかそんなのであまりうれしくありません。
	// 正直やめてほしい(比較サイズ間違えるとバグの元だし)ですが、現実にあるので仕方がない
	if (dataX.a == dataY.a) {
		printf("同じ\n");
	}
	// コピーは代入で出来ます。memcpyっての使う人がいますけど、完全無視で。多分コンパイルした結果はほぼ同じになると思います。
	// 最適化さえかかるようにしてれば。で、たまにmemcpyのサイズ間違える方いるんです。そうすると即バグになるので、
	// いい加減代入しろよと思ったり。でも、これも現実のソースではね。。。
	dataY = dataX;

	// C11という規格から以下の無名構造体って機能が入りました。まぁ構造体名書かないでいいよってだけですが
	// 多分構造体とか共用体の中でしか使わないと思います。あと、C99はまだしもC11なぞ使えない可能性が高いのでご注意を
	struct Test {
		int a;
		struct {
			int b;
		};
	};
	struct Test c = { 1, 2 };
	printf("a = %d b = %d\n", c.a, c.b);
}

/************************** 共用体 ***************************/
// 説明しません。組み込み以外で使うことはあまりないと思うからです。
// そんなこといったらC言語を組み込み以外で使うことって・・・私はやったことあるので全否定はしません
// まぁ、enumと組み合わせて使うケースもあるのですが・・・
// 役に立つサンプルないと、これの存在意義分かりづらいでしょうね。

/************************** typedef ***************************/
/**
* @brief		typedefの説明用
* @param[in]	なし
* @param[out]	なし
* @return		なし
* @detail       briefに全部書いてある
*/
void Sample21Func5(void)
{
	// typedefは新しい名前付けを行うものです
	// typedef 元々の名前 新しい名前 みたいな感じです。
	typedef unsigned int UINT;
	UINT len = 100;	// UINTをunsigned intの代わりに使える

	// 前に説明したenum, 構造体ですが、実際はtypedefを使って宣言することが99%です。
	// んでもってタグ名というのをぶっ飛ばすことがほとんどです
	typedef struct {
		int a;
		int b;
	} DATA;
	DATA c = { 0 };	// 以前と違ってstructなしで使えます

	typedef enum {
		MON,
		TUE,
		WED,
	} WEEK;
	WEEK wk = MON;	// 同様にenumなしでOK

	// あと関数ポインタってので使いますが後で説明するでしょう
	// ちなみにdefineと違ってtypedefはあくまで別名を付けるだけですからね。お間違いのないよう

	// 昔はtypedefってタイプ量減らすためにあるって感じが強かったですが、今風に言えばstructと付けないことで
	// オブジェクトの型を意識しやすいってノリかもなぁと個人的に感じております。
}
