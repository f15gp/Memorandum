/**
 * Javaの勉強 4日目(シリアライズとデシリアライズ)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test3;

import java.io.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

// シリアライズ(直列化)はJDK1.1で入った機能です。
// やることって何かというと、インスタンスをそのままファイルに書き込むことです。
// で、ファイルからインスタンスに戻すのをデシリアライズって言います。

// 最初にやることはシリアライズ可能なクラスを作ることです。
// そのためにはjava.io.Serializableを実装する必要があります。
/**
 * パーソン クラス
 * 
 */
final class Person implements Serializable {
	/** 名前 */
	private String name;
	/** 生年月日(yyyy/mm/dd形式) */
	private Date birthDay;
	/** 年齢(シリアライズ対象外) */
	private transient int age;

    /**
     * コンストラクタ
     * 
     * @param name 名前
     * @param birth 生年月日
     */
	public Person(String name, String birth) throws ParseException {
		if (name.isEmpty() || name.equals("")) {
			throw new IllegalArgumentException("nameがNULLか空です。");
		}
		if (birth.isEmpty() || birth.equals("")) {
			throw new IllegalArgumentException("birthがNULLか空です。");
		}

		this.name = name;
		var format = new SimpleDateFormat("yyyy/MM/dd");
		this.birthDay = format.parse(birth);
		this.age = getAge(this.birthDay);
	}

    /**
     * 名前を取得
     * 
     * @return 名前
     */
	public String getName() {
		return name;
	}
    /**
     * 生年月日を取得
     * 
     * @return 生年月日
     */
	public String getBirthDay() {
		return new SimpleDateFormat("yyyy-MM-dd").format(birthDay);
	}
    /**
     * 年齢を取得
     * 
     * @return 年齢
     */
	public int getAge() {
		return age;
	}

    /**
     * 年齢を取得する
     * 
     * @param birth 生年月日
     *
     * @retuan 年齢
     */
	private static int getAge(Date birth) {
		var calendar = Calendar.getInstance();
		calendar.setTime(birth);
		return (Calendar.getInstance().get(Calendar.YEAR) - calendar.get(Calendar.YEAR));
	}

    /**
     * readObject()から呼ばれるメソッド
     * 
     * @param in 入力ストリーム
     *
     */
	private void readObject(ObjectInputStream in) throws IOException, ClassNotFoundException {
		// デフォルトのシリアライズ
		in.defaultReadObject();

		// transientのフィールドを復元
		age = getAge(birthDay);

		// なお、privateなど含めてメソッドの形式は正確にこの形で実装すること。じゃないと呼び出してくれません。
		// それはオーバーライドでなく、リフレクションを用いて強制的に呼び出すことをしてるからです。
		//
		// また、trasientの領域がない。復元する必要がない場合は、readObjectは書かなくて問題ありません。
		// それとwriteObjectの方も書き換えることが出来るよ。
	}
}
