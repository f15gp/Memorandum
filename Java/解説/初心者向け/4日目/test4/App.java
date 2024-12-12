/**
 * Javaの勉強 4日目(総称型(ジェネリクス)とコレクション)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test4;

import java.util.ArrayList;
import java.util.List;

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
    	var gs = new GenericSample<String>();
    	gs.setValue("char");
    	System.out.println(gs.getValue());
    	// ちなみにJDK1.7ではダイアモンド演算子というのが追加されました。
    	// GenericSample<String> gs = new GenericSample<>();
    	// こんな感じで右辺の<>の中の型を省略できるものでした。
    	// でも、varの方が短いからそっち使えばいいかな。
    	// ちなみに、このダイアモンド演算子、記憶が間違いでなければ確かJDK 1.7の目玉機能でした。

    	// プリミティブ型は指定できないので、ラッパークラスを使うことになる。
    	// が、オートボクシングが働いてるのでソース上はintのように扱える。
    	var gi = new GenericSample<Integer>();
    	gi.setValue(123);
    	System.out.println(gi.getValue().toString());
    }

    /**
     * 2つ目のメソッド(説明用)
     * 
     */
    static void second() {
    	Integer[] intArray = {1, 2, 3, 4, 5};
    	Character[] charArray = {'H', 'E', 'L', 'L', 'O'};
    	GenericMethodSample1.printArray(intArray);
    	GenericMethodSample1.printArray(charArray);

    	GenericMethodSample1.processNumber(5);

    	System.out.println(GenericMethodSample1.getMax(7, -1));
    }

    /**
     * 3つ目のメソッド(説明用)
     * 
     */
    static void third() {
    	CollectionSample1.Method();
    }

    /**
     * 3つ目のメソッド(説明用)
     * 
     */
    static void fourth() {
    	System.out.println(GenericMethodSample2.findMax(List.of(1, 9, 7)));

    	GenericMethodSample2.processList(List.of(2.3, 7.32, 3.48));
    	// addNumbers()が可変のListを要求するのでインスタンスイニシャライザを使って生成
    	var l = new ArrayList<Integer>() {
    		{
    			add(11);
    			add(2);
    			add(5);
    		}
    	};
    	GenericMethodSample2.addNumbers(l, 8);
    	GenericMethodSample2.processList(l);
    }

}
