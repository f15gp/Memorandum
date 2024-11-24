/**
 * Javaの勉強 2日目(インポート、パッケージ)
 * 
 * @version 1.0.0
 * @author Bunya
 */

// パッケージを書いてない場合デフォルトパッケージになります。
// とりあえずtest1とかいうふざけたパッケージ名にしておきます。
// 使える英字記号は_だけとのこと。
package test1;

// import用(書式はimport パッケージ名.クラス名)
import java.time.LocalDate; // 1つ目
import java.util.*; // 2つ目

//import packA.SampleA;
import test1.packA.SampleA;

// static importは多分書かないかなぁ ★★★

/**
 * アプリ クラス
 * 
 */
public class App {

    /**
     * Mainメソッド
     * 
     * @param args 起動時に与えられたコマンドの配列
     */ 
    public static void main(String[] args) {
        // メソッドの呼び出し
        first();
        second();

        // 画面に表示する
        System.out.println("正常終了");
    }

    /**
     * 最初のメソッド(説明用)
     * 
     */
    static void first() {
        // import
        // パッケージとも関わってくるimportを説明。

        // Javaではクラスを利用する場合、自分で作成したかどうかに関わらず完全修飾名で利用することになります。
        // 完全修飾名というのは、以下のようにパッケージ名を含めたクラス名を全て記述するものです。
        var day = java.time.LocalDate.now();
        System.out.println(day);

        // 1つ目のimportによりLocalDateクラスが宣言されたので、クラス名だけで使用できるようになる。
        // このクラス名だけのものを単純名といいます。
        day = LocalDate.now();
        System.out.println(day);

        // 2つ目のimportによりjava.utilパッケージに含まれる全てのクラスをimport宣言したのと同じになります。
        // その結果 例えばDateクラスを単純名で使用できます。
        var date = new Date();
        System.out.println("現在の日時 : " + date);
        // ただし、*を使用したimport宣言では、それより下層のパッケージの中のクラスを単純名で使用できません。

        // なお、java.langパッケージは暗黙にimport宣言したと扱われるので、
        // java.lang.Stringやjava.lang.Systemなどは単純名で何もしなくても使用できます。

        // importがやっているのはその名前と違い？、パッケージ名の省略です。
        // それ以外の機能は一切ありません(C言語やってた方は#includeとは全くの別物なので誤解のないよう)。
    }

    /**
     * 2つ目のメソッド(説明用)
     * 
     */
    static void second() {
        // パッケージを説明していくメソッド
        //
        // このパッケージは筆者がJavaを激しく嫌う理由の筆頭。
        // 個人的にではあるが、わかりにくい上に実用性が低いと思う。
        // 実際の開発で、パッケージを作成しないわけがないので、どうにかしてほしい。
        // 逆にeclipseあたりでjarを使うだけなら、あまり難しく考えなくても動くと思うので、
        // 使用することと開発することの難易度が違いすぎるのが問題だと思う。
        // =>つまり初心者が実用的な開発で悩むんじゃないかなと。
        // それとも、eclipseやらはその辺を勝手に行って、面倒なことを隠蔽してくれるのだろうか？
        // でも、それはそれで少し手の込んだことをしようとすると、ハマって涙目になりそうな気も。
        //
        // 結局jarも様々な問題が出たからモジュールが入ってきたわけで、
        // このパッケージって正直Javaの欠点だと思うんですがねぇ。。。
        var A = new SampleA();
        //var A = new packA.SampleA();
        System.out.println(A);

        /* パッケージとコマンドの関係
        先に断っておきますが、最終的なソースコードの配置は6.のものとなっているため、
        1.からはtreeコマンドで表示されるようなファイル・フォルダ配置で進んでるんだと思ってください。
        ※ 1つ1つフォルダを用意していけばわかりやすいが大変なのでご勘弁を

        1. packageを指定していない場合
        つまり App.javaのimport packA.SampleA;がなく、
        SampleA.javaにpackage packA;がなく、
        second()でvar A = new SampleA();としているとき。

        $ tree(treeというコマンドを実行)
        .
        ├── App.java
        └── packA
            └── SampleA.java

        $ javac -cp .:./packA App.java ・・・コンパイル

        $ tree
        .
        ├── App.class
        ├── App.java
        └── packA
            ├── SampleA.class
            └── SampleA.java

        $ java -cp .:./packA App ・・・実行

        この場合、SampleAとAppクラスがどこにあるかを知らせなければいけないので、-cpで
        カレントディレクトリとpackAフォルダを指定することでSampleAがどこにあるかjavacと
        javaが認識できるようになる。

        2. second()のnew SampleA()をnew packA.SampleA()とする場合
        このときSampleA.javaにpackage packA;を追加する必要がある。

        $ javac App.java
        $ java App

        SampleAが完全修飾名で使われたことでjavacとjavaはpackAにSampleAを探しにいく。
        そこでSampleA.javaにpackageがあることでjavacとjavaはSampleAのクラスが
        どこにあるか分かるようになるので-cpで場所を知らせる必要がなくなる。

        3. App.javaにimport packA.SampleA;を追加して、
           var A = new SampleA();に変更

        $ javac App.java
        $ java App
        SampleAを単純名に変えただけなので2.同様 -cpは必要ない。

        4. packBフォルダを作成し、3.のApp.classをpackBにコピー

        $ tree
        .
        ├── App.class
        ├── App.java
        ├── packA
        │   ├── SampleA.class
        │   └── SampleA.java
        └── packB
            └── App.class

        $ java -cp ./packB App

        途中まで実行されるが、new SampleA()でSampleAクラスが見つけれず、java.lang.NoClassDefFoundErrorが発生。
        クラスを見つけれないのは、package宣言の階層構造と.classファイルの配置が正しくなっていないため。
        
        5. 4.からpackBの下にpackAフォルダを作成しApp.classをコピー

        $ tree
        .
        ├── App.class
        ├── App.java
        ├── packA
        │   ├── SampleA.class
        │   └── SampleA.java
        └── packB
            ├── App.class
            └── packA
                └── SampleA.class

        $ java -cp ./packB App
        最後まで実行される。
        SampleA.classをpackage通りの階層に配置したことで、JVMが正しくクラスをロードできるようになったため。
        階層構造を作るのは、あくまでパッケージ"名"だけで、パッケージに階層が出来るわけではない。
        にも関わらず、classファイルはJVMのロードの都合によりパッケージ名の階層と対になる配置を要求してくる。
        JVMを手抜きで作ったからだろう(半分嘘。Javaは.classの遅延ロードを許しているので、
        必要になった段階で指定された完全修飾名やimportを元に.classを探すので仕方がない面がある)。
        ・・・やっぱり嫌いだ。C#は名前空間とDLLを採用したので、こんなことで悩まなくていい(これもちょっとだけ嘘ｗ)

        6. 3.の状態でApp.javaにpackage test1;を追加し、import test1.packA.SampleA;に変更。
        また、SampleA.javaのpackageもpackage test1.packA;に変更。
        その上でtest1フォルダなどを作成し.javaファイルをコピーして実験。

        なぜそんなことが必要かというと、App.javaにtest1パッケージを追加したため、
        App.javaをtest1フォルダの下に配置しないといけないため。

        $ tree
        .
        └── test1
            ├── App.java
            └── packA
                └── SampleA.java

        $ javac ./test1/App.java

        $ tree
        .
        └── test1
            ├── App.class
            ├── App.java
            └── packA
                ├── SampleA.class
                └── SampleA.java

        $ java -cp . test1.App

        */
    }

}
