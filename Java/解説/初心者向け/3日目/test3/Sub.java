/**
 * Javaの勉強 3日目(interface、ついでに継承＆実装)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test3;

/**
 * サンプル インターフェース(interface説明用)
 * 
 */
interface Sample {
    // とりあえず継承とか実装を説明するにしてもinterfaceを避けて通れないので、
    // 先にinterface書いちゃうぞっと。
    // interfaceは抽象クラスの特殊形態です。
    // publicな抽象メソッドと定数だけが定義できます・・・だった。
    // ※ JDK 1.8(いわゆるJava8)からデフォルトメソッドが定義できるようになったので、多重継承の問題で言われていた一部を取り入れた。
    //    また同じくJava8でstaticメソッドも定義できるようになった。
    //    デフォルトメソッドは確かStreamを取り入れるために既存のライブラリにインパクトを与えないよう導入したような経緯だったと思うが、
    //    それを実現するためにstaticメソッドがあった方が良かったのかな？(あるとしたら、デフォルトメソッドで使うフィールドの初期化だろうけど)
    //    ※※ 多重継承の問題はいくつかあるが、著名なのは重複するメソッド、菱形継承、実装の継承、状態の継承がある。
    //         C++は、これらの問題を全て持っているが、結局使い方の問題だと思う。
    //         interfaceの場合、元々は定数とメソッドだけだったので、重複するメソッドだけが問題で一番厄介かつ問題となる"状態の重複"は発生しない。
    //         だから、安全とかほざいた記事をみた記憶がある。間違いではないが、上記全ての問題を持っているので、"だからC++の多重継承は邪悪で、不要だ。"
    //         などと言われていたのを鑑みると、"いや、必要になって限定的にでもとり入れたJavaの文法は、欠陥だろ？"と思う。
    //         C++だって、とうの昔にinterface的なやり方で継承＆多重継承するのが主流だわ(全てではない。そして多重継承は滅多に使わない)。
    //         ・・・まぁ、interface自体が多重継承を使わないでお茶を濁すために入れたかもしれない気はする。
    //
    // 初期は本当にメソッドの呼び出し方を定義する役割だったのですが、現代では大きく役割が拡大してます。
    // 正直、C++はISOという国際規格で定義される関係上、WG(ワーキンググループ)での議事録やその機能が必要となった背景、代わりに検討された文法etc
    // が全てドキュメントとして残されています。
    // 例えばC++の変数の型推論としてのauto&decltypの議論はhttps://www.open-std.org/jtc1/sc22/wg21/docs/papers/2003/n1478.pdfで公開されてます。
    // ただ、Javaはその経緯とかが残されてない(自分が知らないだけ？)ので、なぜinterfaceにstaticメソッドが必要になったなどは推測でしか分かりません。
    // ※ なんだかんだ言ってC言語とC++はISO規格なので、その辺がしっかりしてるのはJavaに対する優位点かなと思います。
    //    Javaも、OpenJDKが中心となってからは、https://openjdk.org/projects/amber/design-notes/on-ramp みたいにデザインノートが残されてるようですが、
    //    全部じゃないですからねぇ。
    //
	// interfaceの書式はこうです。
	// [public] interface インターフェース名 [extends 親インターフェース名, ・・・]
	// extendsとあるように別のインターフェースを継承することができます。
	// ただ、実際のところinterfaceは元々複数のinterfaceを実装することが出来るので、主にそちらが使われていると思います。
	// だけど、標準ライブラリの一部にも継承した奴があるみたいよ。
	// extendsとか書かなくても、class同様にObjectクラスを継承した扱いになるので、toString()とか呼べちゃいます。
	//
	// ちなみにinterface単体はnewできません、ですが。
	// staticメソッドが許可されたので、mainかけるようになっちゃいましたぁｗ
	// そんなの説明してると長いのでやめときます。。。(なんで、そんな根源が変わるようなこと追加すんのよ)

    // public static finalのフィールドでないといけません、そうじゃないとコンパイルエラーになります。それらを省略した場合は暗黙的にそれらが付いているものとして扱われます。
    /** インターフェースのフィールド */
	String SubString = "Sub interfaceです";

    // public abstractlのメソッドでないといけません、コンパイルエラーになります。それらを省略した場合は暗黙的にそれらが付いているものとして扱われます。
	int Double(int x);

    // フィールドもメソッドもどのように記載するか好みやコーディング規約があると思うので、それに従って下さい。
    // "それにしかできないから省略"と"紛らわしいから全部書け"という大きく2つに分かれそうですが、
    // 個人的な経験から言うと"どのようにしても、かわりゃしない"というのが本音。
    // ほとんどの開発者はそこまで文法を覚えてないし、定義してもしなくても動くので気にしてない。

    // デフォルトメソッド
    // JDK1.8(Java8)から可能。interfaceに処理を記述できるメソッド(=抽象メソッドでない)
    // java.lang.Objectクラスに存在するメソッド(toString, equals, hashCode)は、デフォルトメソッドとして定義できません。
    default String DefaultMethod(int a) {
    	return String.format("%s。%dが渡された", SubString, a);
    }

    // Java9からprivateメソッドも定義できるようになった。どこまでクラス化してんねんｗ
    // staticメソッドとかデフォルトメソッドで使うためだろうが、色々追加するね。

    // interfaceの特殊用途として以下の3つがごぜーます。
    // 1. マーカーインターフェース Serializable, Cloneableとかですね。
    //    1.5でアノテーションが入ったので、お使いの環境で代用アノテーションが用意されてたら、そちらを使って下さい。
    // 2. 定数
    //    staticインポートを使って、クラスに定義するのが良いのかな。
    //    あれ？じゃ、interfaceで定数を定義する役目は終わったのか？(昔は良くやってたイメージ)
    //    ※ なんかinterfaceで定数を宣言するのは色々問題があるので、今はやらない方が良いみたい。
    // 3. 関数型インターフェース
    //    抽象メソッドが1つだけ定義されているインターフェース。これをJDK1.8(Java8)からそう呼ぶようになった。まぁ、ラムダとかのための用語ですね。
}

// それでは、まずクラスの継承を行います。最初は抽象クラスでない普通のクラスさんです。

/**
 * 抽象クラスでない普通のクラスの継承説明用(クラス名を気にしてはいけない)
 * 
 */
class Sample1Parent {
	/** 年齢のつもり */
	protected int age;

    /**
     * 自分が何者か名乗る(通常メソッド)
     * 
     * @return 自分の名前
     */
	public String toString() {
		return "Sample1";
	}

    // 抽象メソッドは書いちゃダメです。書いたらclassを抽象クラスにしないといけないです。

    // あ、そうです。
    // 書き忘れてましたが、メソッド名が同じだけど引数の型が異なるメソッドを複数定義することが出来ます。
    // これをオーバーロードと言います。
    // 使っていいかはコーディング規約次第でしょうね

    /**
     * 演説を行う
     * 
     * @return 演説
     */
	protected String speech() {
		return "";
	}
}

/**
 * 普通のクラスを継承したクラス(クラス名を気にしてはいけない)
 * 
 */
class Sample1Child extends Sample1Parent {
    // class クラス名 extends スーパークラスで継承です。

    /**
     * 自分が何者か名乗る
     * 
     * @return 自己紹介？
     */
    @Override
	public String toString() {
		// JDK1.5より前はアノテーションがないため、メソッド名を間違えると
		// 親クラスのメソッドをオーバーライドするのではなく、このクラスに新メソッドを用意したことになってしまいました。
		// オーバーライドするときは必ず@Overrideつけてくださいね。

        // 意味もなく親のフィールドを使う。というか、とても悪い使い方です。
		age = 1;
		// superを使って親クラスのメソッドを利用します。
		return "私は" + super.toString() + "の子供です。年は" + Integer.toString(age) + "歳です。";
	}

    /**
     * 演説を行う
     * 
     * @return 演説
     */
    @Override
    public String speech() {
    	// これはただのサンプルですが、
    	// 実は継承先のクラスで、メソッドのアクセス指定をスーパークラスより強く(より公開される方向)することは可能です。
    	// 逆のprotected->無指定 or privateと弱く(コンパイルエラーで弱いと出るので弱い、強いで記載)することは出来ません。
    	return "speech!";
    }

}

/**
 * 抽象クラスの継承説明用(クラス名を気にしてはいけない)<br>
 * 抽象メソッドがある場合は必ず抽象クラスにする必要がある。<br>
 * 抽象クラスはnewしてインスタンスを作成することが出来ません。
 * 
 */
abstract class Sample2Parent {

    /**
     * 何か挨拶をする(抽象メソッド)<br>
     * 抽象メソッドなので実装書けません。書いたらコンパイルエラー。
     * 
     * @return 挨拶
     */
    public abstract String speech();
}

/**
 * 抽象クラスを継承したクラス(クラス名を気にしてはいけない)
 * 
 */
class Sample2Child extends Sample2Parent {

    /**
     * 挨拶をする
     * 
     * @return 挨拶
     */
    @Override
	public String speech() {
		// Overrideつけなくても抽象クラスを継承した場合、抽象メソッドを全部オーバーライドしないと
		// インスタンス化できないので、オーバーライドの実装漏れは起きませんが、統一感を出すために@Overrideをつけるべきでしょう。

        return "皆さん、おはようございます。元気ですか？";
	}

}

// とまぁこれがクラスの継承です。
// 1990年代初めまではクラスの継承が良く使われていて、それは主に親の実装を引き継いで差分を実装するというものでした。
// ところが、(差分を実装する)継承は廃れ、デザインパターン(1990年代半ば)などでのポリモーフィズムに見られるだけになりました。
// では差分の実装というのはどこへ行ったのか？というと、それは包含というものに集約されていきます。
// 包含ってなんだ？っていうとクラスのフィールドに別クラスを持つことです。それだけ。
// ※ 良く継承はis-a関係、包含はhas-a関係とか呼ばれます。
// なので、このクラスの(差分を実装する)継承を使う場面はあまりないでしょう。というか、相当の手練れになるまで使わない方がいいでしょう。
//class hoge {
//	// 正直↓のStringがクラスなんだから、この時点で包含になってますけどね。
//	private String str;
//};

// では、クラスの継承はこの程度で次はinterfaceの実装
// ※ interfaceの継承はパス

/**
 * 実装のサンプル インターフェース
 * 
 */
interface MathMethod {

    /**
     * 引数同士を足す
     * 
     * @param x 足される数
     * @param y 足す数
     *
     * @return 加算結果
     */
	int add(int x, int y);

}

/**
 * インターフェースを実装するクラス
 * 
 */
class Sample1Implement implements MathMethod {
    // class クラス名 implements interface名でインターフェースの実装です。

    /**
     * 引数同士を足す
     * 
     * @param x 足される数
     * @param y 足す数
     *
     * @return 加算結果
     */
    @Override
	public int add(int x, int y) {
		// 抽象メソッドなので統一感を出すためにOverride ry)
		// 実際の開発だとどうなんだろ？冗長だから書かないのか？
		// でも、Javaはひたすら長いクラス名やメソッド名が大好きなイメージあるが、果たして
		//
		// interfaceでは暗黙に定義されているが、classでは意味が異なるのでメソッドにアクセス指定をしてやる必要がある。
		return (x + y);
	}

}

/**
 * 多重実装のサンプル インターフェース
 * 
 */
interface ScienceMethod {

    /**
     * 力を求める
     * 
     * @param m 質量
     * @param a 加速度
     *
     * @return 力
     */
	int motion2nd(int m, int a);

}

/**
 * 2つのインターフェースを実装するクラス
 * 
 */
class Sample2Implement implements MathMethod, ScienceMethod {
    // 多重実装するときは、interface名をカンマでつなげて記載する。
    // この場合は並べて記載したインターフェースのメソッドを全て実装しないと
    // インスタンスを作成できない。

    /**
     * 引数同士を足す
     * 
     * @param x 足される数
     * @param y 足す数
     *
     * @return 加算結果
     */
    @Override
	public int add(int x, int y) {
		return (x + y);
	}

    /**
     * 力を求める
     * 
     * @param m 質量
     * @param a 加速度
     *
     * @return 力
     */
    @Override
	public int motion2nd(int m, int a) {
		return (m * a);
	}

}

// interfaceのデフォルト実装が衝突したパターンとかも書いても良いのですが、まぁそんなに遭遇することもないでしょうから、とりあえずパス
