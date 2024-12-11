/**
 * Javaの勉強 5日目(匿名クラス)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test1;

// 匿名クラス
// 匿名クラスは無名内部クラスとも言って、一か所でしか使用しない場合にクラスをわざわざ作るのが面倒なので、
// 用意された文法。だと思う。最初は。
// だけど、フィールドに格納して使いまわすとかの使い方もあるので、一か所でしか使わないだけではないことにご注意を。
// まぁ、これ多分今はラムダ使うの推奨になってるんじゃないかなと思います。
/**
 * @匿名クラスの説明
 * 
 */
final class nonNameInner {
	/** 匿名クラスの説明用に用意したフィールド */
	private int value;

	/**
     * 匿名クラスの説明 1
     * 
     */
	void doNonNameInner1() {
		// 匿名クラスは、newで作成する際に、クラスを定義するような文を続け、最後に;を書きます。
		// newの後の名前は 親クラスまたはインターフェイス名に限られます。
		new Object() {
			// これJavadoc書くもんなのかな？
			void test() {
				System.out.println(this.getClass());
			}
		}.test();

		// Java10からのvarを使うとローカル変数に匿名クラスを格納して、フィールドやメソッドにアクセスできます。
		var obj = new Object() {
			public final int number = 11;
			void test() {
				System.out.println(this.getClass());
			}
			void print(int value) {
				System.out.println(value);
			}
		};
		obj.test();
		obj.print(obj.number);
	}

	/**
     * 匿名クラスの説明 2
     * 
     */
	void doNonNameInner2() {
		new Object() {
			void test() {
				// 外側のクラス(nonNameInner)のフィールドやアクセスにアクセス出来ます。
				// 外側のクラス名.this.で明示的にアクセスすることも出来ます。
				value = 7;
				System.out.println(value);
				System.out.println(nonNameInner.this.value);
			}
		}.test();
	}

	/**
     * 匿名クラスの説明 3
     * 
     */
	void doNonNameInner3() {
		final int val = 198;
		//int val = 198;
		new Object() {
			void test() {
				// 匿名クラスを定義したメソッドのローカル変数はfinalが付いていたら参照出来ます。
				System.out.println(val);
			}
		}.test();

		// ただ、JDK 1.8(Java8)からなのですが、コメントアウトした宣言のようにfinalがついていなくても、
		// 匿名クラスやラムダ式(これは後で説明)で使用している場合は、暗黙にfinalがついているものとみなすようになっています。
		// これを事実上のfinalとか呼びます。
		// 暗黙にfinalがついているので、↓のように代入してしまうとコンパイルエラーとなるのでご注意を。
		//val = 999;
	}

}
