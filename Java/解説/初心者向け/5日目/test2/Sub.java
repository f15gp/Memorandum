/**
 * Javaの勉強 5日目(ラムダ式、メソッド参照)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test2;

import java.util.Arrays;
import java.util.Collections;
import java.util.function.*;
import java.util.ArrayList;
import java.util.List;

import java.io.Serializable;

import java.util.function.Consumer;

// ラムダ式にしろメソッド参照にしろ、まず関数型インターフェースを説明しないと話にならないので、先にそれを書きます。
// 関数型インターフェースは、ラムダ式やメソッド参照の代入先になれるインターフェースのことです。
// 関数型インターフェースの条件は、大雑把に言って、定義されている抽象メソッドが1つだけあるインターフェースになります。
// staticメソッドやデフォルトメソッドは含まれていても問題ないです(関数型インターフェースの条件としては、無視される)。
// また、Objectクラスにあるpublicメソッドがインターフェース内に抽象メソッドとして定義されている場合、そのメソッドも無視されます。
// (この条件を満たすインターフェースを、JDK1.8(Java8)で"関数型インターフェース"と呼ぶようになりました)
// これで一旦説明をやめて、ラムダ式に行きます。
/**
 * @ラムダ式の説明
 * 
 */
final class FuncInterface {

	/**
     * 説明用メソッド1
     * 
     */
	void explanationFunc1() {
		// ラムダ式はJDK1.8(Java8)で導入されました。
		// 関数型インターフェースの変数に代入する箇所ではラムダ式を渡すことが出来ます。
		//
		// ラムダ式は、関数型インターフェースのメソッドをオーバーライドする形になります。
		// しかし、関数型インターフェースには抽象メソッドが1つしかないため、どのメソッドか指定しなくても決定できます。
		//
		// ラムダ式は、引数部->処理本体という形式になります。
		// メソッド名と戻り値の宣言が無いメソッド定義みたいな形ですね。
		// 詳しく書く前に、下にlistをソートするラムダ式書いときますね。
		List<Integer> list = Arrays.asList(5, 7, 6, 4);
		Collections.sort(list, (arg1, arg2) -> Integer.compare(arg1, arg2));
		for (var l : list) {
			System.out.println(l);
		}

		// 引数部詳細(引数部の例なので処理本体は全て{}と書いてます)
		// 1. (型1 引数名1, 型2 引数名2, ・・・)
		//    普通のメソッド定義の引数部分と同じように書く。型の前にアノテーションを付けることもできる。
		// 1. の例)
		//    () -> {}, (String s) -> {}, (int n1, int n2) -> {}, (@NotNull String s) -> {}
		//
		// 2. (引数名1, 引数名2, ・・・)
		//    ラムダ式がオーバーライドするメソッドは、代入先の関数型インターフェースから分かるため、引数の型を省略できる。
		//    ただし、複数の引数がある場合、全ての引数の型を省略する必要がある。
		// 2. の例)
		//    () -> {}, (s) -> {}, (n1, n2) -> {}
		//
		// 3. 引数名
		//    引数が1つのみの場合、引数を囲む丸括弧を省略できます。
		//    この場合は、型も省略する必要がある。
		// 3. の例)
		//    s -> {}
		// 4. (var 引数名1, var 引数名2, ・・・)
		//    Java11から、引数にvarが付けれるようになった。
		//    この場合、全ての引数にvarを付ける必要がある。
		//    が、これは本来いらない(varはJava10から入った型推論だが、ラムダが入ったJDK1.8(Java8)からラムダは型推論していたため)のだが、
		//    どうやらローカル変数の構文と一致させるために導入したんだそうな。・・・はぁ。
		// 4. の例)
		//    (var s) -> {}, (@アノテーション var s) -> {}

		// 処理本体詳細(引数部は全て(int n)と書いてます)
		// 1. {
		//      文1;
		//      文2;
		//      ・・・
		//      return 戻り値;
		//    }
		//    普通のメソッド定義の本体と同じように書く。
		//    ラムダ式がオーバーライドするメソッドは、代入先の関数型インターフェースから分かるため、戻り値の型に応じた値をreturn文で返すようにする。
		// 1. の例)
		//    (int n) -> {
		//       System.out.println(n);
		//       return n + 1;
		//    }
		//
		// 2. {
		//      文1;
		//      文2;
		//      ・・・
		//    }
		//    関数型インターフェースのメソッドの戻り型がvoidの場合は、return文は省略可能。
		// 2. の例)
		//    (int n) -> {
		//       System.out.println(n);
		//    }
		//
		// 3. 波括弧の省略
		//    処理本体に文が1つしか無い場合、波括弧を省略出来る。
		//    この場合は、returnと末尾のセミコロンも記述しない。
		// 3. の例)
		//    戻り値がvoidの場合:     (int n) -> System.out.println(n)
		//    戻り値がvoid以外の場合: (int n) -> n + 1      <- 捕捉するとこれはreturn n + 1;のみという意味。

		// 関数が長くなったので分けます。
	}

	/**
     * 説明用メソッド2
     * 
     */
	void explanationFunc2() {
		// ラムダ式で使う変数のスコープ

		// ラムダ式の外側で定義されている変数を内部から参照出来ます。
		// 匿名クラスでも同じ。
		int n = 12;
		Runnable runner1 = () -> {
			System.out.println(n);
		};
		runner1.run();

		// 匿名クラスで説明したようにfinalになるので、
		// 変更は出来ない。
		//Runnable runner2 = () -> {
		//	n++;
		//};
		//runner2.run();

		// runner1で参照している以上、ラムダ式の外でも変更は出来ない。
		//n++;

		// ラムダ式の外で既に定義されている変数名はコンパイルエラーになる。
		// これはfor文のスコープと同じ。
		// ただし、匿名クラスでは別スコープになるので問題ない。
		// なお、ラムダ式の引数に使った変数名を、ラムダ式より後で使うのは問題ないです。
		//Consumer<String> consumer = (n) -> System.out.println(n);
		//consumer.accept("abc");
		Consumer<String> consumer = (str) -> System.out.println(str);
		consumer.accept("abc");

		String str;// これはOK。

		// thisは、"ラムダ式を定義したメソッド"が属しているクラスのインスタンスを指す。
		// 匿名クラスだと、thisは、匿名クラスのインスタンスを指します。
		Runnable runner2 = () -> System.out.println(this);
		runner2.run();

		// ただ、このメソッドがstaticだと、当然ながらthisをラムダ式内部で使えない。

		// 関数が長くなったので分けます。
	}

	/**
     * 説明用関数3
     * 
     */
	void explanationFunc3() {
		// 関数型インターフェースのメソッドの引数の型とラムダ式の引数の型は、プリミティブ型とラッパークラスを区別します。
		// オートボクシングのような事は行いません。
		// なお、戻り値の型に関してはオートボクシングされます。

		// ラムダ式は関数型インターフェースの変数に代入する形で使うので、代入先がObjectクラスだったりするとコンパイルエラーになります。
		// 関数型インターフェースにキャストする形をとれば、Objectクラスの変数にも代入できます。出来ますが、やる利点ある？
		Runnable obj1 = () -> System.out.println("ttt");
		//Object obj2 = () -> System.out.println("ttt");
		Object obj3 = (Runnable)() -> System.out.println("ttt");

		// JDK1.8(Java8)から交差型キャストという仕様が導入されました。
		// "インターフェース名1 & インターフェース名2 & …"という形で、キャストするときに「&」でインターフェース名を繋いでいくものです。
		//
		// ラムダ式の場合、この交差型キャストを使うと、マーカーインターフェースと合成できます。
		Runnable obj4 = (Runnable & Serializable & Cloneable) () -> System.out.println("RNC");
		System.out.println(obj4 instanceof Runnable);
		System.out.println(obj4 instanceof Serializable);
		System.out.println(obj4 instanceof Cloneable);
		obj4.run();
		// あ、知ってると思いますが、instanceofはインスタンスの型を調べるものです。
		// Objectからのキャストが頻発した頃ならまだしも、今はそうそう使うことがなくなったものだと思います。
	}
}

// そんでメソッド参照
/**
 * @メソッド参照の説明
 * 
 */
final class MethodReference {

	/**
     * 説明用メソッド1
     * 
     */
	void explanationMethod1() {
		// メソッド参照は、JDK1.8(Java8)で導入された構文です。
		// 関数型インターフェースの変数にメソッドそのものを代入することが出来、これをメソッド参照と言います。
		// ↓こんな感じで指定します。
		// staticメソッドの場合（場合によってはインスタンスメソッドも）
		//    クラス名::メソッド名
		// インスタンスメソッドの場合
		//    インスタンス変数名::メソッド名
		// 例を書いていきます。

		// 例1)
		// IntSupplierは、引数なしで戻り型がintのメソッド(getAsInt)を持ちます。
		var s = "abc";
		IntSupplier supplier1 = s::length;
		//IntSupplier supplier1 = "abc"::length; <- この書き方も出来ます。
		System.out.println(supplier1.getAsInt());
		// これがラムダなら↓になります。
		// IntSupplier supplier1 = () -> s.length();

		// 例2)
		// Consumerは、引数が1個で戻り型がvoidのメソッド(accept)を持ちます。
		Consumer<String> con = System.out::println;
		con.accept("def");
		// これがラムダなら↓になります。
		// Consumer<String> con = str -> System.out.println(str);

		// 例3)
		// IntBinaryOperatorは、引数が2個でintを返すメソッド(applyAsInt)を持ちます。
		IntBinaryOperator op = Integer::sum;
		System.out.println(op.applyAsInt(3, 5));
		// これがラムダなら↓になります。
		// IntBinaryOperator op = (n1, n2) -> Integer.sum(n1, n2);

		// 例4)
		// 自分のメソッドを渡す。
		IntSupplier supplier2 = this::method1;
		System.out.println(supplier2.getAsInt());
		// 渡すメソッドがstaticなら自クラス名::になる。
		supplier2 = MethodReference::method2;
		System.out.println(supplier2.getAsInt());

		// インスタンスメソッドを使ってる例1)
		ToIntFunction<String> f = String::length;
		//ToIntFunction<String> f = s2 -> s2.length(); <- ラムダならこう
		System.out.println(f.applyAsInt("abc"));

		// インスタンスメソッドを使ってる例2)
		BiFunction<List<String>, String, Boolean> f2 = List<String>::add;
		//BiFunction<List<String>, String, Boolean> f2 = (list, s3) -> list.add(s3); <- ラムダならこう
		List<String> list = new ArrayList<>();
		f2.apply(list, "abc");
		System.out.println(list);
	}

	/**
     * 例4で渡すメソッド
     * 
     * return 整数値
     */
	int method1() {
		return 111;
	}

	/**
     * 例4で渡すメソッド2個目
     * 
     * return 整数値
     */
	static int method2() {
		return 123;
	}

	/**
     * 説明用メソッド2
     * 
     */
	void explanationMethod2() {
		// コンストラクタ参照
		// なんてことはありません、コンストラクタを変数に代入したものをそう呼びます。
		// クラス名::new <- こんな感じで指定します。
		// コンストラクタが複数あると、代入先の関数型インターフェースの引数の型が一致するものが選ばれます。

		// 例1)
		Supplier<List<String>> supplier1 = ArrayList::new;
		List<String> list = supplier1.get();
		// これがラムダなら↓になります。
		// Supplier<List<String>> supplier1 = () -> new ArrayList<>();

		// 例2)
		IntFunction<List<String>> factory1 = ArrayList::new;
		List<String> array = factory1.apply(10);
		// これがラムダなら↓になります。
		// IntFunction<List<String>> factory1 = (n) -> new ArrayList<>();
	}

}

// 改めて戻ってきて、関数型インターフェースの説明と思ったのですが、途中で断りなくポンポン使っちゃいましたね。失礼しました。
// まぁ、必要なら自分で関数型インターフェースを作ればいいのですが、
// 標準として用意してくれているのがたくさんあるので、まずはそれ使ったらいかがですか？って話ですね。
// 本当にたくさんあるので。
// ※ 筆者はC++でSTL使って散々やってたので、この辺のことは全く違和感がありません。
//    てか誤解してる人いるんですが、C++では1.0版(1998年。JDK1.2発表の年)から、STLとコンテナ(Javaのコレクションみたいなの)、テンプレート(ジェネリクスの強化版)が
//    ありました。
//    Javaより1.0版が出来たのが遅いのもあまり知られてませんし、クラスとかポインタってのでグリグリやるんだろうみたいに思われてます。
//    むしろ、クラスよりSTLとコンテナを上手く使って作る方が中心で、クラス使わずにメソッドだけで組んでもいいのですがねぇ・・・。
//    クラスなしで大きなプログラムが組めるのか？って思う方いるかもしれませんが、
//    LinuxのカーネルだってクラスがないC言語だけで構成されてた時代が長かったですよ(その当時ですら200万行とかあったのでは？)
//    まぁ、データと処理を一体化してインスタンスを分離できるクラスは強力なので、そりゃ使えるなら使った方がいいですがね。
//
// で、例では変数使ってやってばかりですが、当然実践的なものはフィールドへの適用、
// メソッドの引数、戻り値にも適用していくことになります。
// それはこの後に書く、OptioalやStreamで使っていくことになりますのでスキップ。
