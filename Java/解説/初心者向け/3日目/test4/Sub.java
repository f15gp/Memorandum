/**
 * Javaの勉強 3日目(クラス残り物)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test4;

import java.util.Collections;
import java.util.List;

// イミュータブルクラス(Immutable class)
// record使えるならそっち使う方がいいけど、バージョンの縛りなどがあるだろうから紹介しておく。
// 意味としては、一度インスタンスが生成されるとその状態が変更されないクラスのことです。
// Java標準では、Stringとかラッパークラス(Integerとか)ですね。
// Entityクラスなんかもこれであることを強く望みます。というかデータを保持するような目的のクラスは全部これでしょ。
//
// 基本的な作成ルール？
// 1. クラスはfinal
// 2. フィールドはprivateかつfinal
// 3. コンストラクタで全フィールドを初期化
// 4. セッターは禁止
// 5. 可変オブジェクトの参照を外にさらさない。
// サンプルを書いてみます。

/**
 * @イミュータブルクラス
 * 
 */
final class Person {
	/** 名前 */
	private final String name;
	/** 年齢 */
	private final int age;
	/** 子供たち(ただの説明用) Listも後で説明 */
	private final List<String> children;

    /**
     * コンストラクタ
     * 
     * @param name 名前
     * @param age 年齢
     * @param children 子供
     */
	Person(String name, int age, List<String> children) {
		// 例外は後に説明するのでフーンと
		// フィールドの不変条件を満たせれるか確認するのは大事
		if (name.isEmpty() || name.equals("")) {
			throw new IllegalArgumentException("nameがNULLか空です。");
		}
		if (age < 0) {
			throw new IllegalArgumentException("ageがマイナスです。");
		}
		// 子供が誰しもいるわけではないので、nullしか見ないのは意図的
		// nullを見るのはunmodifiableListで例外を出させないため
		if (children == null) {
			throw new IllegalArgumentException("childrenがNULLか空です。");
		}
		// ちなみにネットを見れば、Listの確認はapacheのライブラリを使って調べる方法が良く出てくると思う。
		// が、それを使えるかどうかはプロジェクト次第。というより、本来ライセンスが絡んでくるので、
		// 日本のプロジェクト(大きめなやつ)だと外部ライブラリを使えないこともよくある。
		// なんかそういった事情を知らずに、使わない奴はダメ的な書き方してる記事もあるので、
		// そんなのを鵜呑みにされるとたまったものじゃない。
		// どことは言わないが、筆者が今所属してる会社とかは、ライセンス・保守期間なんて無視してる気がしてならない。
		// それは法律的にかなりアウト寄りのグレーだ。

		this.name = name;
		this.age = age;
		// 可能なら、基本不変オブジェクトを使用する。あれ？これバージョンいつから使えるんだっけかな。。。
		// 今なら使えるのは間違いないから、まぁいいかぁ。
		this.children = Collections.unmodifiableList(children);
		// もし、不変オブジェクトを使えないバージョンなら、
		// このようにコピーを格納する。
		//this.children = new ArrayList<>(children);

		// privateのメソッドを使うバージョン
		//this.children = getUnmodifiedList(children);
	}

    /**
     * 変更不可リストを取得する
     * 
     * @param list 文字列のリスト
     *
     * @return 空のリストまたは変更不可に変更したリスト
     */
	private List<String> getUnmodifiedList(List<String> list) {
		// コンストラクタのchildrenに代入するところは、このようなメソッドを用意してしまうのも手。
		// このメソッドの場合だとnullで空文字列を作成するので、nullが許容されると仕様が変わってる点に注意。
		if (list == null) {
			return Collections.emptyList();
		} else {
			// Java8まではunmodifiableList(始まりのバージョンは知らん。わからん)
			// Java9ではList.ofが使えるようになり
			// Java10からはList.copyOfが使える
			return List.copyOf(list);
		}
	}

    // ゲッターは用意してOK.
    // これらのサンプルは同じパッケージ内で動くように実装しているため、
    // アクセス修飾子がなくても動きます。
    // そのため、publicとかは書いてないケースが良くあります。
    // 今回も気付いたけど、面倒で書いてないときが多々あります。
    // 実際の開発では、そこのコーディング規約に従って下さい。

    /**
     * 名前を取得する
     * 
     * @return 名前
     */
	String getName() {
		return name;
	}

    /**
     * 年齢を取得する
     * 
     * @return 年齢
     */
	int getAge() {
		return age;
	}

    /**
     * 子供を取得する
     * 
     * @return 子供
     */
    List<String> getChildren() {
    	return children;
    	// コンストラクタ同様に、不変オブジェクトを使えないバージョンなら、
		// このようにコピーを返す。
		// コピーを返さない場合、このインスタンスの外でいくらでも変更出来るし、
		// 参照が続く限りはこのインスタンスが滅びた後もGCは回収しない。
		//return new ArrayList<>(children);
    }

    /**
     * 比較する
     * 
     * @return 比較結果
     */
    @Override
    public boolean equals(Object obj) {
    	// イミュータブルクラスの場合 比較出来た方が便利なことが普通でしょうから、併せて用意します。
    	// 絶対必要ってわけじゃないですが

    	if (this == obj) {
    		return true;
    	}
    	if (obj == null) {
    		return false;
    	}
    	if (getClass() != obj.getClass()) {
    		return false;
    	}

    	var other = (Person)obj;

    	if (name == null) {
    		if (other.name != null) {
    			return false;
    		}
    	} else {
    	    if (!name.equals(other.name)) {
    		    return false;
    		}
    	}
    	if (age != other.age) {
    		return false;
    	}
    	if (children == null) {
    		if (other.children != null) {
    			return false;
    		}
    		return true;
    	}
    	return children.equals(other.children);
    }

    /**
     * ハッシュを得る
     * 
     * @return ハッシュコード
     */
    @Override
    public int hashCode() {
    	// Hashmapとかを使わないと必要ないのでは？と思うが、
    	// まぁequalsを用意したらhashCodeも用意しなければいけないというので・・・
    	// これは説明のため独自で書いてますが、多分JetBrainsやEclispeではクラスから
    	// 自動生成してくれる機能があると思うので、そっちを使うこと。
    	// でも、このイミュータブルクラスはrecordに置き換えてくれとは思うが。
    	// ※良く知らないが、もしかしたらequalsも自動で用意してくれるのかな？
    	//   確かVisual StudioのC#は用意されてた気がするが。
    	final int prime = 31;
    	int result = 1;
    	result = prime * result + ((name == null) ? 0 : name.hashCode());
    	result = prime * result + age;
    	result = prime * result + ((children == null) ? 0 : children.hashCode());

    	return result;
    }

}

// クローンについて
// 正直いうとrecord使ってくれなのですが、
// recordが使えないバージョンが普通でしょうから一応書いておきます。
// ていうか、やっぱりKotlinと違ってrecordが長いことなかったのがJavaの欠陥の一つだよぉ。
// ※ といっても、record使って=でコピーとかそういう意味ではない。
//    recordをnewするときにデータを全部渡しちゃえばよくないですか？という意味。
//
// クローンがなぜ必要か？
// それは参照を保持せずデータだけがほしい場合があるからです。
// そのような時にクローンが必要になります。
// それに関連し、参照値だけをコピーすることをシャローコピーといい、値そのものをコピーすることをディープコピーと言います。
// まぁマルチスレッドを扱わない限り、そう滅多に必要とは思えないが。
// てか下手するとイミュータブルクラスをちゃんと用意するなら不要な可能性も・・・

/**
 * @クローンサンプルクラス
 * 
 */
final class Point2D implements Cloneable {
	// このクラスも正直Immutable classだが、面倒なので、ここではCloneの説明だけに絞る。
	// ちなみになぜクローンが必要かというと標準のクローンとか代入は全部シャローコピーという
	// 参照値のコピーが行われているため。
	// 参照をもたず実際の内容のコピー(ディープコピー)として取得したい場合はCloneを実装する必要がある。
	// クローンを実装するにはCloneableのマーカーインターフェースを実装する。

	/** x座標 */
	double x;
	/** y座標 */
	double y;
	/** 参照型のコピーの説明用 */
	String s;

    /**
     * クローン
     * 
     * @return コピーしたインスタンス
     */
    @Override
    public Point2D clone() {
    	// 元々JDK 1.4まではオーバライドした際の戻り値の型が同じでなければいけなかった(元々の戻り値はObject)。
    	// JDK 1.5からは共変戻り値型(戻り値の型をサブクラスにする)が許されたので、
    	// 呼び出し側が適切な型にキャストする必要がなくなった。
    	// Javaは、ジェネリクス(あとで ry))や共変戻り値型がなかった1.4までは、色々なところでキャストが必要な言語でした。
    	//
    	// また、例外の所で書くかと思いますが、オーバーライドした場合、throwsを書かないことにより例外を減らすことが出来ます。
    	// protected Object clone() throws CloneNotSupportedException {
    	// Objectのcloneの定義は確か↑の感じ。

    	Point2D obj = null;

    	try {
    		// プリミティブとかだけならsuper.cloneだけでOK
    		obj = (Point2D)super.clone();
    		// 適切なクラスを用意するのが面倒だったので、文字列を新規作成してコピーすることでお茶を濁す
    		obj.s = new String(s);
    	} catch (CloneNotSupportedException ex) {
    		System.out.println("例外発生!");
    		ex.printStackTrace();
    		System.exit(1);
    	}

    	return obj;
    }
    // JDK 1.4までかつインスタンス変数に参照型がなかったら下のような書きかた。
	//public Object clone() {
	//	Object obj = null;
    //
	//	try {
	//		obj = super.clone();
	//	} catch (CloneNotSupportedException ex) {
	//		System.out.println("例外発生!");
	//		ex.printStackTrace();
	//		System.exit(1);
	//	}
	//
	//	return obj;
	//}

}

// 局所クラス(またはローカルクラス)
// ただ、大事なこと。
// この局所クラスを知らない人もいるだろうし、書くのが好みじゃない人もいるでしょう。
// 個人で開発する時は止めませんが、複数人(ましてや大規模開発だと絶対)の場合は必ずコーディング規約に従って下さい。
// まじで、政治的な争いや揉め事に発展します。
// てか、1ファイル1クラスだとそもそも許されない・・・のか？

/**
 * @局所クラス サンプルクラス
 * 
 */
final class Sample1 {
	/** Sample1のフィールド1 */
	private int field1 = 1;
	/** Sample1のフィールド2 */
	private int field2 = 2;
	/** Sample1のフィールド3 */
	private static int field3 = 3;

    /**
     * フィールド2の値を取得
     * 
     * @return フィールド2の値
     */
	private int getField2() {
		return field2;
	}

    /**
     * 局所クラスの説明用
     * 
     */
	public void doLocalClass1() {
		int localInt = 11;
		final int localInt2 = 22;

		// このようにメソッドの中にクラスを定義するのが局所クラス。
		// 他のメソッドから使用することは出来ない。
		// 局所クラスは内部クラスの一種で、外側のクラス(ここではSample1)のフィールドやメソッドにアクセスできる。
		// 局所クラスを含んでいるメソッドのローカル変数はfinal付きならアクセス可能。
		// ところでこの場合、Javadoc書くのが一般的なんかい？
		class LocalClass {
			public void method() {
				System.out.println(field1);
				System.out.println(getField2());
				//System.out.println(localInt1);
				System.out.println(localInt2);
			}
		}

		var local = new LocalClass();
		local.method();
	}

    /**
     * 局所クラスの説明用
     * 
     */
	public static void doLocalClass2() {
		// staticメソッドの局所クラスは、
		// 外側クラスのstaticでないものにアクセスできない。
		class LocalClass {
			public void method() {
				// System.out.println(field2);
				System.out.println(field3);
			}
		}

		var local = new LocalClass();
		local.method();
	}
}

// 内部クラス(メンバークラス・入れ子クラス)
// これは局所クラスと違い、メソッドの中でなくクラスの中にクラスを定義する。
// ※ C++だとこれは出来るけど局所クラスは出来ない。
// てか、1ファイル1クラスだとそもそも許されない・・・のか？
// なんでJava 1.0からある文法(つまり誕生した当時からそれの使い道があったはずのもの)を無視するルールが横行するのかねぇ。
// gotoと同じで一つでも例外を設けると、勝手に実装する奴がでて収拾がつかないとかいう理由か？
// ※ これ冗談でなく、昔gotoがダメな理由を聞いた時、"効果的な使い方があるのは分かってるけど、"とかの後に出てきた言葉。
//    または、goto使ってるだけで使い方に関係なく、"使っちゃダメじゃん。技術力が低いね"と脳死で答えてくるパターンもあったが。
//    まぁそれだけレビューも杜撰だし、エンジニア一人の力量とかが無視されてましたね。だから、技術が漏れたり衰退したんでしょうが。
//    ちなみにアセンブラとか組み込みだとgoto使わないと逆に蹴り上げますよ。
//    だって、アセンブラってjmp命令しかないし、組み込みでgotoせずに例外で・・・ってそもそも例外サポートしてないのが普通だし。

/**
 * @内部クラス サンプルクラス<br>
 * ちなみにこのネストしてない一番外側のクラスはトップレベルクラス(top level class)と言います。
 * 
 */
final class Root1 {
 
    // このネストした内側のクラスを入れ子クラス(nested class)と呼びます。
    // クラスの直下(フィールドやメソッドと同じ位置)に定義したネストクラスをメンバークラスと言い、
    // ネストしたクラスのうち、staticでないものを内部クラス(inner class)と呼びます。外側のクラスはアウタークラス(outer class)ですね。
    // staticな場合などはちょっとややこしい部分がある。
    // もし、内部クラスのアクセスがpublicならRoot1の外からInnerを生成できる。
    // その場合は、new Root1().new Inner()とかとして生成する。
 	private class Inner {
 		int field1;
 		void method() {
 			field1 = 2;
 			System.out.println("Inner");
 		}
 	}
 
 	public void method() {
 		var i = new Inner();
 		i.method();
 	}
}
 
// ちょっと内部クラスを実用的？に使おうと思うと定数のクラスが思いついたので書いてみる。
// 内部クラスを使う利点は関連する定数に階層構造を与えて分類できること。かなぁ？
// それ以外だと許されるか分からんけど、あるクラスの中だけで使用する機能を内部クラスにして整理するとかかな。
/**
 * @定数クラス(食べ物)
 * 
 */
final class Food {
	 /**
      * コンストラクタ(生成を禁止する)
      * 
      */
 	 private Food() {}

 	 /**
 	  * @定数クラス(肉)
 	  * 
 	  */
 	 public static class Meat {
 	 	 /** 定数 牛肉 */
 	 	 public static final int BEEF = 3;
 	 	 /** 定数 豚肉 */
 	 	 public static final int PORK = 5;
 	 	 /** 定数 鶏肉 */
 	 	 public static final int CHICKEN = 7;
 	 }
 	 /**
 	  * @定数クラス(果物)
 	  * 
 	  */
 	 public static class FRUIT {
 	 	 /** 定数 リンゴ */
  	 	 public static final int APPLE = 5;
  	 	 /** 定数 オレンジ */
  	 	 public static final int ORRANGE = 8;
 	 }
}
