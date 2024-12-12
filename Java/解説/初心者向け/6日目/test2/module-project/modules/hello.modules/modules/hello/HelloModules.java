/**
 * Javaの勉強 6日目(モジュール)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package modules.hello;

// 凄く後回しになりましたが、Java9で入ったモジュールについて説明。
// 身も蓋もないことを言えば、モジュールは複数のパッケージをまとめたものです。
// ちなみに今回このファイルにはモジュールの作成手順しか書いていきません。

// でも、これによって以下のパッケージ問題が解決されます。
// 1. モジュール定義ファイル(module-info.java)に従って、パッケージ単位で公開範囲を定義可能になる。
// 2. 正しいライブラリ(JARファイル)が"モジュールパス"と呼ばれるパス上に配置されていることが保証される。

// ただ、筆者は初心者なので、
// 本当に基本的な部分しか紹介できませんので悪しからず。

// まず、module-info.javaを用意します。
// 中に書く構文としては、
// module モジュール名 {
//     exports パッケージ名;
//     requires モジュール名;
// }
// exportsにモジュールの外に公開するパッケージを書き、requiresには依存しているモジュール名を書きます。
// ただし、標準APIを含むパッケージ(java.lang等)には依存していても、
// これら標準APIは"java.base"モジュールにまとめられていて、このモジュールは暗黙的にrequiresされているので、
// requiresに書く必要はありません。

// 今回はモジュールのテストとして↓のようなフォルダを作成してます。
// それはこのページ(https://www.baeldung.com/java-modularity)を参考にしてアレンジを加えたものだからです。
// 感謝、感謝です。
//└─test2
//    └─module-project <- ここでコンパイルとか実行を行う。
//        └─modules
//            ├─hello.modules
//            │  └─modules
//            │      └─hello
//            └─main.app
//                └─modules
//                    └─main

// まずコンパイルするにはmodule-projectに移動する。
// あ、筆者WindowsでPowerShell使ってるので、と前置き。
// これでコンパイルします。
// Get-ChildItem -Recurse -Filter "*.java" | foreach { javac -d outDir --module-source-path .\modules\ $_.FullName }
// 意味) (module-projectにいるので)modules以下の*.javaのファイルを探して、javacにフルパスでファイル名を渡してコンパイルし、
//       結果をoutDirに出力する。です。
// で、実行するには、↓です。
// java --module-path outDir -m main.app/modules.main.MainApp

// これで、main.cppに対してhello.modulesを公開するというサンプルになります。
// これがモジュールの基本となります。

/**
 * モジュール説明のための クラス
 * 
 */
public class HelloModules {

    /**
     * 説明のための文字列を出力します。
     * 
     */
    public static void doSomething() {
        System.out.println("Hello, Modules!");
    }

}
