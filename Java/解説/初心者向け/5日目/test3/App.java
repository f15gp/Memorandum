/**
 * Javaの勉強 5日目(Optional、Stream)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test3;

import java.util.Arrays;
import java.util.Comparator;

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
        fourth();

        // 画面に表示する
        System.out.println("正常終了");
    }

    /**
     * 最初のメソッド(説明用)
     * 
     */
    static void first() {
    	// 値を取得(取得値がnullの場合は-1にする)を表示する
    	var integerList = new IntegerList();
    	System.out.println("値:" + integerList.get(1).orElse(-1));
    }

    /**
     * 2つ目のメソッド(説明用)
     * 
     */
    static void second() {
    	var sample = new StreamSample();
    	sample.filterListByStringLength(Arrays.asList("a", "bc", "efg", "hijk", "lmnop"), 2)
    		.forEach(System.out::println);
    	// ここでのforEachはStreamのじゃなくListのメソッドですね

    	// ↓の部分を実行するとわかりますが、filterListByStringLengthでのStream操作はlistの中身に変更を加えていません。
    	//var list = Arrays.asList(new String[]{"a", "bc", "efg", "hijk", "lmnop"});
    	//list.forEach(System.out::println);
    	//sample.filterListByStringLength(list, 2).forEach(System.out::println);
    	//list.forEach(System.out::println);
    }

    /**
     * 3つ目のメソッド(説明用)
     * 
     */
    static void third() {
    	var sample = new StreamSample();
    	sample.convertAllUpperCase(Arrays.asList("Apple", "orange", "cheRRY"))
    		.forEach(System.out::println);

    	// ラムダ式をソートの方法として変数に保持し、sortIntListに渡す変数を変えることで
    	// ソート方法を入れ替えるサンプル
    	var intList = Arrays.asList(24, 7, 10, 54, 33);
    	Comparator<Integer> ascendingCompare = (a, b) -> a - b;
    	Comparator<Integer> descendingCompare = (a, b) -> b - a;
    	// 昇順にソート
	    sample.sortIntList(intList, ascendingCompare)
    		.forEach(System.out::println);
    	// 降順にソート
	    sample.sortIntList(intList, descendingCompare)
    		.forEach(System.out::println);
    }

    /**
     * 4つ目のメソッド(説明用)
     * 
     */
    static void fourth() {
    	var sample = new OptionalNextSample();
    	//sample.processString("") <- "Empty String"を表示
    	//sample.processString(null) <- "Empty String"を表示
    	sample.processString("   BUN  ") // <- "Hello, BUN"を表示
    		.ifPresentOrElse(
    		input -> System.out.println(input), // <- 値が存在する場合に実行
    		() -> System.out.println("Empty String")); // <- 値が存在しない場合に実行
    }

}
