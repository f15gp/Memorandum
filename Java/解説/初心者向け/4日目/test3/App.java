/**
 * Javaの勉強 4日目(シリアライズとデシリアライズ)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test3;

import java.text.ParseException;
import java.io.*;

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
    	try {
    		var p = new Person("bun", "2002/12/01");

    		// ここからシリアライズを書く
    		try (var out = new ObjectOutputStream(new FileOutputStream("object.txt"))) {
    			out.writeObject(p);
    		} catch (IOException ex) {
    			ex.printStackTrace();
    		}
    	} catch (ParseException ex) {
    		ex.printStackTrace();
    	}
    }

    /**
     * 2つ目のメソッド(説明用)
     * 
     */
    static void second() {
    	// こっちでデシリアライズによってファイルからインスタンスを復元
   		try (var in = new ObjectInputStream(new FileInputStream("object.txt"))) {
   			var p = (Person)in.readObject();
   			System.out.println(String.format("名前:%s 誕生日:%s 年齢:%d", p.getName(), p.getBirthDay(), p.getAge()));
   		} catch (IOException ex) {
   			ex.printStackTrace();
   		} catch (ClassNotFoundException ex) {
   			ex.printStackTrace();
   		}
    }
}
