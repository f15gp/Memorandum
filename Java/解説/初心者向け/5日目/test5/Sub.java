/**
 * Javaの勉強 5日目(パターンマッチング)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test5;

import java.time.DayOfWeek;

// まずはswitch式。Java14から使えます(プレビュー機能としてはJava12から)。
// switch"文"は値を返すことが出来ませんが、
// switch"式"は、各caseから値を返し、switchの結果としての値を返すことが出来ます。
// ※ 文の方が今までなじみのあるswitch
//
// switch文とswitch式の判別は、switchから値を受け取るようになっていたらswitch式、
// そうでなければswitch文と扱う模様です。

/**
 * switch文説明 クラス
 * 
 */
final class SwitchStatement {
	
	/**
	 * 説明用1
	 *
	 */
	void method1() {
		// switch文のおさらい
		// 使用できるのはプリミティブ、列挙、文字列、record＆seald(Java21から)。
		// caseには定数を指定する。Java21からはcase null;も可能。
		// Java14からは、カンマで並べて複数のcaseをまとめれる。
		int n = 3;
		switch (n) {
		case 1, 2:
			break;
		case 3:
			System.out.println(n);
			break;
		default:
			break;
		}
	}
}

/**
 * switch式説明 クラス
 * 
 */
final class SwitchExpression {

	/**
	 * 説明用1
	 *
	 */
	void method1() {
		// switch式
		// yieldの後に値または式を書く。
		var day = DayOfWeek.WEDNESDAY;
		var value = switch (day) {
			case SUNDAY: yield 4;
			default:     yield 10 + day.ordinal();
		};
		System.out.println(value);
		
		// yieldを使わずアロー構文(->)を使うことも出来ます。
		// ↑のを置き換えると↓に、
		day = DayOfWeek.SUNDAY;
		value = switch (day) {
			case SUNDAY -> 4;
			default     -> 10 + day.ordinal();
		};
		System.out.println(value);

		// yieldを使う場合、case 値: yield 式;となるが、
		// アロー構文では、case 値 -> 式;になります。
		// また、アロー構文では式の所にブロックまたは例外を書くことも出来ます。
		// ただし、ブロックを書く場合は、値を返すのは(アロー構文でも)yieldを使うことになります。
		// 一応アロー構文ではフォールスルーが発生しません。
		day = DayOfWeek.MONDAY;
		value = switch (day) {
			case MONDAY -> { System.out.println(day); yield 8; }
			default     -> throw new IllegalStateException(day.toString());
		};
		
		// switch式では網羅性がチェックされ、満たしていないとコンパイルエラーになります。
		// つまり、default含め、全ての列挙子が書かれていないとダメってことですね。
		// ↓は全て網羅していないので、コンパイルエラーです。
		//value = switch (day) {
		//	case SUNDAY -> 4;
		//	case MONDAY -> 8;
		//};

		// switch式ではbreak、continue、returnは使えません。
		value = switch (day) {
			case SUNDAY  -> 4;
			case MONDAY  -> 8;
	        //case TUESDAY -> { break; }
	        //case TUESDAY -> { continue; }
	        //case TUESDAY -> { return; }
			default      -> 12;
		};

		// switch文と同じようにcaseを,で区切って複数並べることが可能です。
		value = switch (day) {
			case SUNDAY, TUESDAY -> 4;
			default              -> 12;
		};
	}

	/**
	 * 説明用2
	 *
	 */
	void method2() {
		// Java21から(プレビュー機能としてはJava17から)は、caseにデータ型を指定することが出来ます。
		// switch文、式両方ですが、ここでは式を
		double d = 1.;
		System.out.println(formatterSwitchMatting(d));
	}

	/**
	 * データ型に応じた文字列を返す
	 *
	 * @param o 認識用のデータ
	 *
	 * @return データ型に応じた文字列
	 */
	private static String formatterSwitchMatting(Object o) {
		return switch (o) {
			// case 型 変数となります。
			// 変数にはoが型変換されて格納される感じですかね。
			// 変数名は同じswitch内で重複しても問題ないですが、この形ではパターンを受ける変数がないのは
			// コンパイルエラーです。
			case null      -> "null";
			case Integer i -> String.format("int %d", i);
			case Long l    -> String.format("long %d", l);
			//case Long i    -> String.format("long %d", i);
			//case Long      -> String.format("long");
			case Double d  -> String.format("double %f", d);
			case String s  -> String.format("String %s", s);
			default        -> o.toString();
		};
	}

	/**
	 * 説明用3
	 *
	 */
	void method3() {
		var s1 = new Sample1(7, 11);
		var s2 = new Sample2(99, 22);
		recordSwitchMatting(s1);
		recordSwitchMatting(s2);
	}

	/**
	 * recordからデータを取り出して表示する
	 *
	 * @param data データを取り出すrecord
	 *
	 */
	private static void recordSwitchMatting(recordRoot data) {
		// Java21から(プレビュー機能としてはJava19から)は、instanceofやswitch文/式でレコードの分解が出来ます。
		switch (data) {
		case Sample1(var x, var y):
			System.out.printf("Sample1=%d, %d %n", x, y);
		    break;
		case Sample2(var x, var y):
			System.out.printf("Sample2=%d, %d %n", x, y);
		    break;
		default:
		    break;
		}
		
		// もう一つメソッド作るのが面倒だったので、
		// 無理やりObject型に代入してinstanceofで分類
		Object o = data;
		if (o instanceof Sample2(var x, var y)) {
			System.out.printf("%d %d %n", x, y);
		}
	}

	/**
	 * 説明用4
	 *
	 */
	void method4() {
		// Java21から(プレビュー機能としてはJava17から)は、パターンマッチングした変数を使って条件を書くことが出来ます。
		// guarded patternっていうのかな？
		guardSwitch("abc");
		guardSwitch("te");
		guardSwitch("address");
		guardSwitch(5);
	}

	/**
	 * データに条件を付けてマッチングし、表示する
	 *
	 * @param data マッチングするデータ
	 *
	 */
	private static void guardSwitch(Object data) {
		// 今回も手抜きで引数にはObjectを使う。
		// 条件を書くところは()で囲むこともできます。
		// case String sがwhenのcaseより前にあるとコンパイルエラーが起きます。
		switch (data) {
		case String s when s.length() == 2:
		    System.out.println("1 string " + s);
		    break;
		case String s when (s.length() == 7):
		    System.out.println("7 string " + s);
		    break;
		case String s:
		    System.out.println("n string " + s);
		    break;
		default:
		    System.out.println(data.toString());
		    break;
		}
	}

}

/**
 * recordのパターンマッチング説明で使う用のinterface
 *
 */
sealed interface recordRoot permits Sample1, Sample2 {}
/**
 * recordのパターンマッチング説明で使う用1
 *
 * @param x 特に意味はない
 * @param y 特に意味はない
 */
record Sample1(int x, int y) implements recordRoot {}
/**
 * recordのパターンマッチング説明で使う用2
 *
 * @param y 特に意味はない
 * @param z 特に意味はない
 */
record Sample2(int y, int z) implements recordRoot {}

// これでパターンマッチングはおしまい。
// ちょっと5日目が長いのでここできります。
// 相変わらず日付ごとの関連性がないなぁｗ
