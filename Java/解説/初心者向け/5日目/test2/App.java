/**
 * Javaの勉強 5日目(ラムダ式、メソッド参照)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test2;

/**
 * アプリ クラス
 * 
 */
public final class App {

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
    	var fi = new FuncInterface();
    	fi.explanationFunc1();
    	fi.explanationFunc2();
    	fi.explanationFunc3();
    }

    static void second() {
    	var mr = new MethodReference();
    	mr.explanationMethod1();
    	mr.explanationMethod2();
    }

}
