/**
 * Javaの勉強 5日目(パターンマッチング)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test5;

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

        // 画面に表示する
        System.out.println("正常終了");
    }

    /**
     * 最初のメソッド(説明用)
     * 
     */
    static void first() {
    	var ss = new SwitchStatement();
    	ss.method1();

    	var se = new SwitchExpression();
    	se.method1();
    	se.method2();
    	se.method3();
    	se.method4();
    }

}
