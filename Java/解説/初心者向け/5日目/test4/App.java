/**
 * Javaの勉強 5日目(record、シールクラス)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test4;

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
    	var p1 = new Point(3, 5);
    	System.out.println(p1.x());
    	System.out.println(p1.y());

    	var p2 = new Point(3, 5);
    	System.out.println(p1 == p2);
    	System.out.println(p1.equals(p2));

    	//var p3 = new Point2(-1, 4);
    	var p3 = new Point2(8, 9);
    	System.out.println(p3.x());
    	System.out.println(p3.y());
    }

    /**
     * 2つ目のメソッド(説明用)
     * 
     */
    static void second() {
    	var a = new A();
    	var b = new B();
    	a.print();
    	b.print();
    }

}
