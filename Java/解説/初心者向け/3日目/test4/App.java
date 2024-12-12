/**
 * Javaの勉強 3日目(クラス残り物)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test4;

import java.util.Arrays;

// staticインポート
// static変数やstaticメソッドをクラス名を指定せずに使用出来るようにする。
//
// 構文的にはこんな感じ
// import static パッケージ名.クラス名.static変数名;
// import static パッケージ名.クラス名.staticメソッド名;
// import static パッケージ名.クラス名.*;
import static test4.Food.*;

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
    	// コメントアウトした行を有効化すると実行時例外
    	//var p1 = new Person("", -1, "");
    	//var p1 = new Person("bu", -1, "");
    	//var p1 = new Person("bu", 1, null);
    	var p1 = new Person("bun", 32, Arrays.asList("child1", "child2", "child3"));

        System.out.println(p1.getName());
        System.out.println(p1.getAge());
        var children = p1.getChildren();
        // children.add("追加");
        var p2 = new Person("bun", 32, Arrays.asList("child1", "child2", "child4"));
        System.out.println(p1.equals(p2));
    }

    /**
     * 2つ目のメソッド(説明用)
     * 
     */
    static void second() {
    	var p1 = new Point2D();
    	p1.x = 11.0;
    	p1.y = 20.0;
    	p1.s = "おはようございます";
    	var p2 = p1.clone();
    	System.out.println(p1);
    	System.out.println(p2);
    	System.out.println(String.format("%f %f %s", p2.x, p2.y, p2.s));
    }

    /**
     * 3つ目のメソッド(説明用)
     * 
     */
    static void third() {
    	var s1 = new Sample1();
    	s1.doLocalClass1();
    	s1.doLocalClass2();

    	var r1 = new Root1();
    	r1.method();

    	System.out.println(Food.Meat.BEEF);
    	System.out.println(FRUIT.ORRANGE);
    }

}
