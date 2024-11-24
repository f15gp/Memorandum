/**
 * Javaの勉強 2日目(jarの説明のためだけと複数のMain)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test2.sample_jar;

/**
 * Sample クラス
 * 
 */
public class Sample {

    /**
     * コンストラクタ
     * 細かいことは後のクラスで説明するので今は無視で
     * 
     */
    public Sample() {
        System.out.println("Hello, Sample!");
    }

    /**
     * Mainメソッド
     * 
     * @param args 起動時に与えられたコマンドの配列
     */ 
    public static void main(String[] args) {
        System.out.println("SampleのMain");

        // 画面に表示する
        System.out.println("正常終了");
    }
}
