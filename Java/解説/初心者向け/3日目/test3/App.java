/**
 * Javaの勉強 3日目(interface、ついでに継承＆実装)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test3;

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
        third();

        // 画面に表示する
        System.out.println("正常終了");
    }

    /**
     * 最初のメソッド(説明用)
     * 
     */
    static void first() {
    	System.out.println(Sample.SubString);
    }

    /**
     * 2つ目のメソッド(説明用)
     * 
     */
    static void second() {
    	var c1 = new Sample1Child();
    	System.out.println(c1.toString());

    	// ↓抽象クラスの親は生成できない
    	// var p1 = new Sample2Parent();
    	var c2 = new Sample2Child();
    	System.out.println(c2.speech());
    }

    /**
     * 3つ目のメソッド(説明用)
     * 
     */
    static void third() {
    	// ↓interfaceは生成できない
    	//var i = new MathMethod();
    	var i1 = new Sample1Implement();
    	System.out.println(i1.add(1, 2));

    	var i2 = new Sample2Implement();
    	System.out.println(i2.motion2nd(2, 2));
    }

}
