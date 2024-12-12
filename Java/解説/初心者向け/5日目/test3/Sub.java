/**
 * Javaの勉強 5日目(Optional、Stream)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test3;

import java.util.Arrays;
import java.util.Comparator;
import java.util.function.*;
import java.util.List;
import java.util.Optional;
import java.util.stream.Stream;
import java.util.stream.Collectors;

// Optionalは、値を1つラップするクラスです。JDK1.8(Java8)で追加されました。
// Optionalはただ単に値を保持しているだけですが、Optionalの各メソッドは、
// 保持している値がnullか否かによって挙動が変わる特徴があります(基本的に、null以外のときだけ処理を行う)。
//
// Optionalのインスタンスは、値がnullだとemptyというものになり、値が有る時は普通に値を保持するインスタンスになります。
// Optionalを受け取った側は、そのOptionalがemptyかどうかを判定して処理を行う。
//
// emptyかどうかの判定を自分でしないといけないなら、null判定を行うのと大差ないですが、
// Optionalには判定を自動的に行ってくれるメソッドが存在しています。

// "ある値を返すが、特定の場合だけ値を返せない"というメソッドは、良く転がってます。
// 例えば、StringのindexOf()は、指定した文字列が見つけれたら見つけた位置を返しますが、見つからなかった場合は-1を返します。
// こうしたメソッドの戻り値を表現するのがOptinalの役割です。
// ちなみにOptional自体は参照型を対象としますが、OptionalIntなどプリミティブ型を扱うクラスも用意されています。

// では、サクっと例を
// ※ 注意) Java8～Java11に至るまで少しずつメソッドが追加されてますので、お使いのバージョンでそのメソッドが使用可能か？ご注意下さい。

/**
 * @Optionalの説明用1
 * 
 */
final class IntegerList {
	/** nullを含むリスト */
	private final List<Integer> LIST = Arrays.asList(new Integer[]{10, null, 12});

	/**
     * 指定された位置の値を返す
     * 
     * @param index 取得位置(0オリジン)
     *
     * @return 値
     */
    public Optional<Integer> get(int index) {
    	return Optional.ofNullable(LIST.get(index));
	}

}

// 実はもうちょっと手の込んだ使い方をしようとするとStreamは避けて通れないので、
// 一旦Streamに行きますね。

// Streamは、同じくJDK1.8(Java8)から導入されました。
// ※ ところで、JDKx.xって言い方とJavaxって言い方ってどこら辺から変わるのか良くわかりません。
//    また、本の帯とかはJDKじゃなくJavaxの方ばかり使ってる気がします。
//    なので以降はJavaxだけ書きますね。
// 
// 複数の値に対して何かの処理(変換や集計)を行うのを簡潔に記述できる方法です。
// C#知ってる方ならLINQです。
// 一応書いとくと、C#のLINQは2007年搭載で、Java8は2014年リリースなので、大分C#の方が先輩？です。
//
// Streamの利点の一つに、操作対象群を変更しないで結果を取り出せることがあります。
// つまりStreamの操作は非破壊の振る舞いをするわけです。
//
// Streamの対象は、コレクションや配列であり、
// それらを用いた操作については原則Streamを使うのが現代Javaです。多分。
// forなんて使ってはいけません。
//
// 操作(メソッド)はとてもたくさんあるので、基本的な使い方のみ記載します。
// 操作には、ラムダ式やメソッド参照を使って処理を渡します。
//
// ちなみにStreamはOptionalと同じで参照型を対象としますが、IntStreamなどプリミティブ型を扱うものが用意されています。
//
// また、Streamにはシーケンシャルなものとパラレルのものがあり、パラレルのものはマルチスレッドで並列に処理されます。
//
// さて、例に・・・と行きたいところですが、もうちょっとだけ説明。
// Streamのメソッドは大きく分けて、中間処理(Streamを返すメソッド)と末端処理(中間処理以外)に分かれます。
// filter()やmap()等の(関数を渡して)処理を記述するメソッドは中間処理で、"渡された関数を保持した新しいStream"を返します。
// Stream内に保持している処理は、中間処理では行いません。
// forEach()やcollect()などは終端処理で、こいつを呼ぶと実際に処理を行います。
// そして、Streamはインターフェースなので、newで作成は出来ません。専用のメソッドを使います。
// では、例へ
final class StreamSample {

	// 一つ一つの例を切り分けやすいので、各メソッドに分割してますが、別にこのような作り方が良いという意味ではない。

	/**
     * Listの中から文字列長以上のStringを取り出し、そのListを返す。
     * 
     * @param population 操作元List
     * @param length 文字列長
     *
     * @return 操作済みList
     */
    public List<String> filterListByStringLength(List<String> population, int length) {
    	// filterは条件に合致するものを取り出す。Java11以降となるが条件に一致しないものを取り出すときは、Predicate.notを併用する。
    	return population.stream()
    		.filter(s -> s.length() > length)
    		.collect(Collectors.toList());
	}

	/**
     * Listの文字列を全て大文字に変換し、格納したListを返す。
     * 
     * @param population 操作元List
     *
     * @return 操作済みList
     */
    public List<String> convertAllUpperCase(List<String> population) {
    	// mapはStreamの各要素に対して、操作を適用します。
    	return population.stream()
    		.map(String::toUpperCase)
    		.collect(Collectors.toList());
    }

	/**
     * 数値のListをソートする。ソート方法は呼び出し元が指定する。
     * 
     * @param population 操作元List
     * @param comp ソート方法
     *
     * @return 操作済みList
     */
    public <T extends Number> List<T> sortIntList(List<T> population, Comparator<T> comp) {
    	return population.stream()
    		.sorted(comp)
    		.collect(Collectors.toList());
    	// このサンプルを書く際にJava初心者の筆者は困った。
    	// OracleのページがC++、C#と比べて非常に分かりにくく、Comparatorとsortedの型定義が分からず暫く検索の海に溺れた。
    	// ・・・ドキュメントになるのはいいけど、まさかJavadocのページをそのまま載せてるだけとは。見づらいなぁ。
    	// これってメソッドを探す以外の用途だと凄く使いにくいなと思ったが、慣れなんだろうかなぁ。
    	//
    	// また、ラムダやStreamのWeb記事では、こんな感じで使いますってだけで、このサンプルのように
    	// 自分で作成するメソッドの引数や戻り値にして使用するといった記事が全然見つからないのに閉口する。
    	// 実用的な開発でメソッドやクラスにラムダ式や関数型インターフェースを渡したり保持させたりをしないわけがないのに。
    	// 実のところ、最初sortedは2変数を受けて1値を返すBiFunctionと誤解したが、蓋を開けたらComparatorだけで良かったのです。
    	// コンパイルエラーを見て、ComparatorがComparator<? super T>で定義されてることも分かったが、簡単に分かるようにしてほしいわ。
    	//
    	// ・・・これはかなり前からの話ですが、
    	// Qiitaとかが普及？したためなのか初心者が使い方をまとめてみました(凄い低レベルで、実際の開発で使えないけど)。
    	// 的なのが凄い多くて、ちょっと詳しい記事が極端に少ないことになってると思います。
    	// ※ 少ないだけなら良いのですが、間違いが多いのが困ります。まぁ誰もお金もらってるわけじゃないですし、
    	//    正しいこと書かなくても問題ないですしね。
    	//    誰とは言いませんが、説明してもネットの記事ばかり信用して(初心者が間違いを見分けれるわけがないのに)、筆者の説明を無視してたら、
    	//    そりゃ伸びませんわ。
    	// これは書籍でも一緒で、初心者向けのものしかない状態になってきてるんですよね。
    	// 困ったものです。
    	// ※ ところが、英語版となると結構詳しく解説したのとかが出版されてます。日本語化されてないのも多々あるし、
    	//    日本語化されてもかなり遅れます。
    	//    こんなだから、Javaのフレームワークにしたって日本発で広く使われているのがないとかになるんでしょう。
    	//    まぁ凄いの作っても日本語での説明しかなかったら、世界の人使ってくれないですしね。
    }

    // とりあえずこのくらいにしておきます。
}

// 帰ってきて、OptionalとStreamの融合を

/**
 * @OptionalとStreamの融合
 * 
 */
final class OptionalNextSample {

	/**
     * 文字列をトリムし、空でなければ大文字に変換し、接頭語を追加する
     * 
     * @param input 操作元の文字列
     *
     * @return 操作した文字列
     */
    public Optional<String> processString(String input) {
    	return Optional.ofNullable(input)
    		.map(String::trim)
    		.filter(s -> !s.isEmpty())
    		.map(String::toUpperCase)
    		.flatMap(this::addPrefix);
    }

	/**
     * 文字列に接頭語を追加する
     * 
     * @param input 操作元の文字列
     *
     * @return 操作した文字列
     */
    private Optional<String> addPrefix(String input) {
    	return Optional.of("Hello, " + input);
    }
}
