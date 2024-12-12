/**
 * Javaの勉強 5日目(record、シールクラス)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test4;

// レコードです。
// Java16から正式(プレビューとしてはJava14から入っていた)に定義できるようになりました。
// レコードは、値を保持するだけの不変クラス。
// まぁ要はgetter/setterの塊を凄く簡単に定義できるようになった不変クラス。
//
// 定義方法
// (public) record レコード名(型 変数名, ・・・) (implements インターフェース名) {
//     (コンストラクタ、メソッド定義)
// }

// レコードのJavadocは↓を参照しました。
// https://github.com/openjdk/valhalla/blob/lworld/test/langtools/jdk/javadoc/doclet/testRecordTypes/examples/Point.java
/**
 * 直交座標系の座標
 *
 * @param x x座標
 * @param y y座標
 */
record Point(int x, int y) {}
// ↑これで
// ↓これとほぼ同じような定義になる。はず
//public final class Point extends java.lang.Record {
//	private final int x;
//	private final int y;
//
//	public Point(int x, int y) {
//		this.x = x;
//		this.y = y;
//	}
//	public int x() {
//		return this.x;
//	}
//
//	public int y() {
//		return this.y;
//	}
//
//	@Override
//	public int hashCode() {
//		～
//	} 
//	@Override
//	public boolean equals(Object other) {
//		～
//	} 
//	@Override
//	public String toString() {
//		～
//	} 
//}
//
// コンストラクタは、自動で用意される。特別な処理をしない限り定義する必要はない。
// メソッドは自由に追加できますが、static以外のフィールドを追加することは出来ません。
// 不変クラスなので、フィールドに値を設定するメソッドはありません。
//
// 値を取得するメソッドの名前はフィールド名と全く同じで、getとかは付きません。
// これはアクセサーメソッドとかって名前らしいです
//
// hashCode、equals、toStringメソッドは、自動で生成されます。

/**
 * 直交座標系の座標
 *
 * @param x x座標
 * @param y y座標
 */
record Point2(int x, int y) {

	/**
     * 標準コンストラクタ
     * 
     * チェック用の処理を入れるのに使う。(引数)は書かない。<br>
     * Javadocは普通のメソッドと同じで良いかは不明。
     *
     */
	public Point2 {
		if ((x < 0) || (y < 0)) {
			throw new IllegalArgumentException();
		}
		// ↑これでチェックが出来ます。x, yへの代入はありませんが、自動的に代入してくれます。
		// ただ、自分でどうしても値を設定したい場合はthisを付けずに行ってください。
		// this使うとコンパイルエラーになります。
		//this.x = 100;
		x = 100; // 自分で入れたら、xだけ<- の値になります。
	}
}

// シールクラスです。
// Java17(プレビュー機能としてはJava15から)から使えます。
// シールはsealedで表し、クラスを継承できるクラスを限定します。
// 使い方はclassの前にsealedを入れ、permitsの後に継承できるクラスを定義する。
// ちなみにpermitsで並べたクラスが全てスーパークラスを継承していない場合は、コンパイルエラーになります。
/**
 * シールクラスの説明
 *
 */
abstract sealed class Root permits A, B {

	/**
     * 抽象メソッド(オーバライド用)
     *
     */
	abstract void print();
}

/**
 * 許可クラス1
 *
 * sealedクラスを継承するクラスは、final, sealed, non-sealedを付けなければいけない
 *
 */
final class A extends Root {

	/**
     * 自分を表示
     *
     */
	@Override
	void print() {
		System.out.println(toString());
	}
}

/**
 * 許可クラス2
 *
 */
final class B extends Root {

	/**
     * 自分を表示
     *
     */
	@Override
	void print() {
		System.out.println(toString());
	}
}

// sealedがあるのにprmitsがない場合は、そのクラスがあるソースファイル内で
// そのクラスを継承するクラスは自動でpermitsに追加しているものとして扱われます。
//
// permitsにより許可されるサブクラスはsealed宣言されたスーパークラスの"近く"になければいけません。
// "近く"ってのは、↓です。
//  ・同じモジュール内(スーパークラスが名前付きモジュール内にある場合)
//  ・同じモジュール内 パッケージ(スーパークラスが名前のないモジュールにある場合)
// モジュール説明してないので申し訳ないが、多分後で説明するかなと思います。
// 今の段階だと同じパッケージの中でしかダメと思ってれば概ね間違ってません。

// で、シールクラスの目的なのですが、
// JEP 409(https://openjdk.org/jeps/409)を読むと↓のようになってます。
// 1. クラスまたはインターフェイスの作成者が、担当するコードを責任ある実装のため制御できるようにする
// 2. スーパークラスの使い方を制限するため、アクセス修飾子よりも宣言的な方法を提供する
// 3. パターンの徹底的な分析の基盤を提供し、パターンマッチングにおける将来の方向性をサポート。
// 3.のパターンマッチ(後で説明)はJava21で実現されます。でも、普通の開発者は主に1.が目的になるでしょうね。
// 特にJavaのprotectedはパッケージ全体に及ぶので、それを制御出来るのは意義あるのではないでしょうか。
