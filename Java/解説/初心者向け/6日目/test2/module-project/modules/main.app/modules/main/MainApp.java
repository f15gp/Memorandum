/**
 * Javaの勉強 6日目(モジュール)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package modules.main;

import modules.hello.HelloModules;

/**
 * アプリ クラス
 * 
 */
public final class MainApp {

    /**
     * mainメソッド
     * 
     * @param args 起動時に与えられたコマンドの配列
     */
    public static void main(String[] args) {
        HelloModules.doSomething();
    }

}

// 後はちょっとしたまともなクラス？とかを作成して終わりにしようと思います。
