/**
 * Javaの勉強 4日目(enumとか)
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
    	var s = test2.Sex.男;
    	System.out.println(s);

    	// switchにも使える。
    	// この場合、caseには列挙子のみを書く。
    	// ただ、nullをswitchに渡すとNullPointerExceptionが発生してしまうよ。
    	switch (s) {
    	case 男:
	    	System.out.println(1);
    		break;
    	case 女:
    		System.out.println(2);
    		break;
    	default:
    		System.out.println(3);
    		break;
    	}

    	// valuesで全列挙子を取得し、表示する
    	for (var a : s.values()) {
    		System.out.println(a);
    	}
    }

    /**
     * 2つ目のメソッド(説明用)
     * 
     */
    static void second() {
    	var s = test2.Status.STATUS1;
    	System.out.println(s.toString());

    	for (var a : s.values()) {
    		System.out.println(a.getValue());
    	}
    }

}
