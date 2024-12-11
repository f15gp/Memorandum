/**
 * Javaの勉強 5日目(匿名クラス)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test1;

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
    	var n = new nonNameInner();
    	n.doNonNameInner1();
    	n.doNonNameInner2();
    	n.doNonNameInner3();
    }

}
