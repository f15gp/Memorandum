/**
 * Javaの勉強 4日目(総称型(ジェネリクス)とコレクション)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test4;

import java.util.ArrayList;
import java.util.List;

// 総称型(ジェネリクス)は、C++のテンプレートみたいな感じの文法としてJDK 1.5から導入された。
// ※ でも、実際のところC++のテンプレートとは主旨が違うけど
// これが導入されるまでのJavaはVector(多分存在すら忘れられてるだろう)とかのようになんでもかんでもObjectで格納できるため、
// プログラマーが注意してキャストして使用するという今とはかなり趣の違う世界が広がってました。
//
// 使うことの利点は、
// 1. 目的の型へのキャストが不要。
// 2. 間違った型を扱うとコンパイルエラーにしてくれる。
// 3. コレクションを返すメソッドは、何の型を扱っているか明白になる。
//    ※ 例えばJDK 1.4まではpublic List method()などになっているのでJavadocに書いてもらうか、ソースを追っかけないと型が分からなかった。
//       コレクションといえば、誕生のころ(JDK 1.0)はVector/Hashtablenなどの実装クラスのみで、List/ArrayListなどが入ってくるのはJDK 1.2からとなる。
//       JDK 1.2は1998年のことだが、その年にC++の最初の規格が成立しているわけで、その時にC++はSTLによる型安全のコレクションを持っていた。
//       といったことを考えると、いうほどJava誕生当時の仕様は優れていなかったと思う。JDK 1.5がリリースされたのは2004年のことだから。
//       すごくどうでも良いことだが、筆者が初めてJavaを触ったのは、このJDK 1.2＆Swingだった。

// ではとりあえずクラスの総称型をサンプルとして
/**
 * ジェネリクス サンプル クラス
 * 
 */
final class GenericSample<T> {
	// クラス名の後の<>の中は仮型引数と言います。複数書くこともできます(書く場合は,で区切る)。
	// 普通は大文字1文字のTとかEとかを使う(文法的に1文字でなくても良いが慣例。C++の真似したのか？)。

	/** 値 */
	private T value;

    /**
     * 値を設定する
     * 
     * @param name 値
     */
	public void setValue(T val) {
		value = val;
	}

    /**
     * 値を取得する
     * 
     * @return 値
     */
	public T getValue() {
		return value;
	}

}

// Throwableの派生クラスは総称型に出来ない。
// 配列は作れない。宣言は出来るけど、生成する式が書けない。

// 次はメソッドの総称型について

/**
 * ジェネリクス メソッド サンプル クラス
 * 
 */
final class GenericMethodSample1 {

	/**
     * 配列を表示する
     * 
     * @param input 表示する配列
     */
	public static <T> void printArray(T[] input) {
		// 戻り値の型の直前に仮型引数を書くだけ。後はクラスと同じ

		for (T element : input) {
			System.out.println(element);
		}
	}

	// 型パラメータに制約を設けることができ、これを"型制約"と呼びます。
	// 例えば、Numberとそのサブクラスのみを受け入れる場合だと↓のような感じ
	/**
     * 渡された数値を加工して表示する
     * 
     * @param value 加工前の数値
     */
	public static <T extends Number> void processNumber(T value) {
		System.out.println("Number: " + value);
	}

	// 複数の型制約を課す場合、& とComparableを実装し、かつSerializableである型に制約を課せます。
	/**
     * 渡された2つ数値の内大きい数値を取得する
     * 
     * @param lha 値1
     * @param rha 値2
     *
     * @return 大きい数値
     */
	public static <T extends Number & Comparable<T>> T getMax(T lha, T rha) {
		if (lha.compareTo(rha) > 0) {
			return lha;
		} else {
			return rha;
		}
	}

	// 一応コンストラクタの総称型も可能です。
}

// とまぁ、まだ詳しくジェネリクスを説明してもいいのだが、
// 先にListとかのコレクションを説明しないといい加減辛いので、先にそちらに脱線する。

// コレクション
// ひと昔前だとアルゴリズムとデータ構造と説明しちゃえばすんだものですが、
// 色々な格納方法で多数の値を保持しておくものです。
// 広義の意味では配列もそうだと思います。
// で、コレクションはジェネリクスによって成立するように変わったので、
// 色々な型をコレクションに格納できます。
// その中で全部説明してるとキリがないので、よく使われるリストのみに絞ります。

/**
 * コレクション サンプル クラス
 * 
 */
final class CollectionSample1 {

	/**
     * コレクションを説明する
     * 
     */
	public static void Method() {
		// リストにはListとArrayListの2種が良く知られていると思います。
		// それぞれjava.util.Listとjava.util.ArrayListになります。
		// この2つの違いってなんだ？というと、ListがインターフェースでArrayListはListを実装したクラスという違いがあります。
		// 大きな違いはListはnewで生成できないことです。
		// でも、↓は可能です。
		List<Integer> list1 = new ArrayList<Integer>();
		list1.add(1);
		// ArrayListの場合は、左辺もそれに出来ますけどね。
		ArrayList<Integer> list2 = new ArrayList<Integer>();
		list2.add(3);

		// Listに格納した場合とArrayListに格納した場合とで何が違うのか？というと、Listの場合はListインターフェースに
		// 用意された操作しか出来ないことです。
		// ArrayList型にすれば、ArrayList独自の操作が使用できます。
		// ちなみに、ここでポリモーフィズムがぁとか難しいこと言わなくても、Listにはポリモーフィズムが使われています。
		// だってArrayListはListを実装してるんですもの。これをポリモーフィズムといわずしてなんというのやら。
		// 基本的にListに格納しておいて、必要に応じてArrayListとかに変換するってので良いと思います。
		// ※ C#だとコレクションの種類が多様なので、もっと細かい使い分けになりますが、Javaならこんなものでしょう。
		//
		// むしろ今は、変更不可のコレクションになるべく変更して保持するってことを意識した方がいいのかな。
	}

}

/**
 * ジェネリクス メソッド サンプル2 クラス
 * 
 */
final class GenericMethodSample2 {

	// コレクション説明したので、リスト専用のジェネリクス メソッドでも
	/**
     * 最大値を取得する
     * 
     * @param list 最大値を探すリスト
     */
	public static <T extends Comparable<T>> T findMax(List<T> list) {
		T max = list.get(0);
		for (T element : list) {
			if (element.compareTo(max) > 0) {
				max = element;
			}
		}
		return max;
	}

	// ワイルドカードってのもあります。
	// ワイルドカードは、実行してみるまで型が限定されない場合に使用します。
	// こいつは通常extendsやsuperと組み合わせて使用します。
	//
	// まずは上限境界ワイルドカードを。
	// リスト内の要素がTまたはそのサブクラスなら適用できます。
	/**
     * Numberのリストを表示する
     * 
     * @param list 表示するリスト
     */
	public static void processList(List<? extends Number> list) {
		for (var num : list) {
			System.out.println(num);
		}
	}

	// つづいて下限境界ワイルドカード
	// superはTまたはそのスーパークラスを表します。
	/**
     * リストに値を追加する
     * 
     * @param list 値を追加するリスト
     */
	public static void addNumbers(List<? super Integer> list, int value) {
		list.add(value);
	}

}
