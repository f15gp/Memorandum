/**
 * Javaの勉強 2日目(jar、複数のMain)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test2;

import test2.sample_jar.Sample;

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
        // jarの説明
        // 一応 jarではmainメソッドを含めてjar単独で実行させる方法もある。
        // が、99%(言い過ぎ？) jarを使う場合も作成する場合のどちらも、いわゆるライブラリとしての
        // 使い方となると思うので、そちらの方法のみを説明する。
        // ※ 多分大昔？のJavaアプレットとかが全盛期だったころなら、jar単独実行とかもあったんだろうけど、
        //    さすがに今はライブラリとしての利用ばっかりやろ。

        var sample = new Sample();
        /*
         * sample_jarフォルダにあるSamle.javaをjarファイル化して、
         * App.javaをコンパイル・実行する場合の手順を下に書く。
         * と言っても最小限の形だけとなっているので複雑な構成にする場合は慣れるまで試行錯誤が必要でしょう。
         * ・・・この辺もEclipseとかだと上手いこと隠蔽してくれるのかな？
         * 筆者はエディタとコマンドプロンプトで実装してるので、その辺はわからない。
         * 
         * 1. 始まりはtest1&2の親フォルダ
         * 
         * $ tree
         * .
         * ├── test1
         * │   ├── App.java
         * │   └── packA
         * │       └── SampleA.java
         * └── test2
         *     ├── App.java
         *     └── sample_jar
         *         └── Sample.java
         * 
         * 2. Sample.javaのみclassファイルを作成
         * 
         * $ javac test2/sample_jar/Sample.java
         * 
         * $ tree
         * .
         * ├── test1
         * │   ├── App.java
         * │   └── packA
         * │       └── SampleA.java
         * └── test2
         *     ├── App.java
         *     └── sample_jar
         *         ├── Sample.class
         *         └── Sample.java
         * 
         * 3. jarファイルの作成
         * 
         * $ jar cvf ./test2/Sample.jar test2/sample_jar/Sample.class
         * 
         * $ tree
         * .
         * ├── test1
         * │   ├── App.java
         * │   └── packA
         * │       └── SampleA.java
         * └── test2
         *     ├── App.java
         *     ├── Sample.jar
         *     └── sample_jar
         *         ├── Sample.class
         *         └── Sample.java
         * 
         * 4. App.javaのコンパイル
         * 
         * $ javac -cp ./test2/Sample.jar ./test2/App.java
         * 
         * $ tree
         * .
         * ├── test1
         * │   ├── App.java
         * │   └── packA
         * │       └── SampleA.java
         * └── test2
         *     ├── App.class
         *     ├── App.java
         *     ├── Sample.jar
         *     └── sample_jar
         *         ├── Sample.class
         *         └── Sample.java
         * 
         * 5. 実行
         * 
         * $ java -cp . test2.App
         */
    }

    /**
     * 2つ目のメソッド(説明用)
     * 
     */
    static void second() {
        // first()が長いので2つに分けたくて作成

        // すごくどうでもいいことですが、、Javaは各クラスにMainを用意できます。
        // 試しにtest1&2の親フォルダで
        // $ java test2.sample_jar.Sample
        // を実行してみてください。
        // Sample.javaのmainの処理が出力されるはずです。
        //
        // しかしfirstでApp.javaを動かしたときはApp.javaのmainが動きましたよね？
        // 不思議じゃないでしょうか？
        // そこでmainに付随するpublicとかの説明は置いておいて、なぜmainがあるのかを説明しましょう。
        // 答え: JVMがclassファイルをロードするときに最初に探して処理を開始するメソッドがmain
        //
        // ただ、それだけのことです。
        // なのでSample.javaにもApp.javaのどちらにもmainがあっても問題にならないのです。
        // でも、それって何が利点なの？と思うでしょうが、まぁテストに使えるわけです。
        //
        // 今はUnitテストとかが流行りらしいので、複数のMainなんて使うかわかりませんが、
        // 新しいクラスやメソッドを作成した時にファイル単体で実行させてテストという用途で使えます。
        // まともな開発なら余程小規模でないかぎりは複数ファイルで構成するでしょうが、
        // その際他のソースを待っていたら開発が進まないので単独でテストする時に使えると思いますよー多分。

        // パッケージでもう一つ小話
        // 大切なことで2度書きます。パッケージ"名"は階層構造を取りますが、パッケージは階層構造にはならず、
        // パッケージ自体には階層構造はありません。
        //
        // つまり、
        // $ tree
        // .
        // ├── package
        //     ├── SubA
        //     └── SubB
        //
        // こんなフォルダ構成でパッケージを作成した場合、
        // パッケージ名は、package、package.SubA、package.SubBになるわけです。
        // なので、名前に関しては階層構造になってます。
        // ですが、package、package.SubA、package.SubBのパッケージはお互いに親子関係がありません。
        // これは3日目に書くクラスの説明のところで大きく関係してきます。

    }
}
