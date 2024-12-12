/**
 * Javaの勉強 4日目(例外)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test1;

// Javaには例外を投げることと例外を捕捉する仕組みが備わってます。
// 例外ってなんすか？というと、まぁ本来起こりえないことが起きた状況って感じですな。
//
// 厳密にいうとJavaで投げることが出来るのはThrowableとそれを継承したオブジェクトです。
// ThrowableにはException(例外)とError(エラー)があります。
// エラーの方はJVMが発生させるものなので普通のプログラマは存在だけ知っとけばOK。
// ちなみに階層としては、
// Throwableを頂点として子にExceptionとErrorがある。そして、Exceptionの子の一部にRuntimeExceptionがある。
// このうちErrorとRuntimeExceptionはthrows(メソッドが投げる例外の種類を記述)に書かなくてもよい。

/**
 * @例外の説明用1
 * 
 */
final class exceptionExperiment1 {

    /**
     * 例外を発生させる
     * 
     */
	public void occurException() {
		// throwによって例外を投げます。
		throw new UnsupportedOperationException("サポートしてません");
	}
}

/**
 * @例外の説明用
 * 
 */
final class exceptionExperiment2 {

    /**
     * 例外を発生させる
     * 
     */
	public void occurException() throws Exception {
		// throwsでこのメソッドはExceptionを投げることを宣言します。
		// 継承の所で述べたようにオーバーライドの際は、スーパークラスのメソッドと同じthrowsしか書けません。
		// ただ、throwsの種類を(記載しないことで)減らすことは出来ます。
		throw new Exception("Exceptionです");
	}

    /**
     * ところでリソース付きtry文というのがあるので
     * 
     */
	public void readFile() {
		// JDK1.7からリソース付きtry文(tyr-with-resources)というのが追加された。
		// それは↓のようなものである。
		try (var is = new java.io.FileInputStream("");
		     var os = new java.io.FileOutputStream("")) {
			// varを使えるのはJava10から
			// 実行順としては tryブロック->close->catch->finallyの順
			// これ一体何をしているのか？というとCloseableを実装したクラスの場合、自動的にclose()を呼び出すということです。
			//
			// ん？それ何の意味があるの？と思う方がいるかもしれません。
			// ですが、JavaのGCが回収してくれるのはメモリ上に存在するインスタンスだけです。
			// ファイルであったりDBといったものを閉じたりというのは一切関与しません。
			// この機構が入るまでは、finallyにて必ずファイルを閉じるなどをやってました。
			// ですが、今はそんなことしないのでfinallyの必要性はかなり薄れていると思います。
			//
			// ちなみにC++にfinallyがないことは問題だとかほざく方がいますが、
			// C++は文法でインスタンスの寿命etcが明確に決まっているので、
			// RAII(簡単に言うとコンストラクタでリソースを確保し、デストラクタでリソースを解放する)という形にして、
			// 勝手にクラスが自分の持っているリソースを解放するのでfinallyなくても問題は起きません。
			// 言語が違うんだから解決方法が違うのは当たり前だと思うんだけどなぁ・・・
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			System.out.println("finally");
		}
	}

}
