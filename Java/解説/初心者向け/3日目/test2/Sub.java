/**
 * Javaの勉強 3日目(クラス続き)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test2;

/**
 * @引数にクラスを使う場合とfinalの関係について1
 * 
 */
class ClassArgs {
	/** フィールドA */
	private int fieldA;
	/** フィールドB */
	public int fieldB;

    /**
     * コンストラクタ
     * 
     * @param a fieldAの初期値
     * @param b fieldBの初期値
     */ 
	ClassArgs(int a, int b) {
		// インスタンスフィールドへのアクセスにthisを使うかはコーディング規約に従って下さい。
		// さらっとGoogle Java Style Guide調べたら、記載なかったので今書くのが主流なのか分からない。
		// なので、とりあえずthis使わずに書いていきます。
		// ※ 昔は Sunのコーディング規約が標準だったと思うが、今はOracleだし勢いあるのはどれなんでしょう？
		fieldA = a;
		fieldB = b;
	}

    /**
     * fieldAを設定
     * 
     * @param x 新しい値
     */ 
    public void setFieldA(int x) {
    	fieldA = x;
    }

    /**
     * インスタンスフィールドを表示
     * 
     */ 
    public void print() {
    	System.out.printf("fieldA(%d) fieldB(%d)。%n", fieldA, fieldB);
    }
}

/**
 * @引数にクラスを使う場合とfinalの関係について2
 * 
 */
class ClassArgsAndFinal {

    /**
     * ClassArgsを引数に渡した場合の動き1
     * 
     * @param x ClassArgsのインスタンス
     */ 
    public void setArg(ClassArgs x) {
    	x = new ClassArgs(8, 7);
    	x.print();
    	// クラスは前に説明した通り参照型です。
    	// さすがに配列と違って上記のようにnewして代入したら、呼び出し元のインスタンスが書き変わるだと洒落にならないので、
    	// それは起きないようになっています。
    	//
    	// 参照値が引数に設定されているだけなので、このメソッド内でnewしたインスタンスを代入し、
    	// 使ってみても呼び出し元のインスタンスには影響を与えません。良かった良かった・・・は嘘で。
    }

    /**
     * ClassArgsを引数に渡した場合の動き2
     * 
     * @param x ClassArgsのインスタンス
     */ 
    public void setArg2(ClassArgs x) {
    	x.setFieldA(10);
    	x.fieldB = 21;
    	x.print();
    	// このようにpublicで定義されたメソッドからフィールドを操作している場合とpublicなインスタンスフィールドを
    	// 介したアクセスでは、呼び出し元のインスタンスに影響を与えます。
    	// なので、それらが用意されているクラスでは、場合によってですが、メソッド呼び出し前後で内容が変わってるかもしれません。
    }

    /**
     * ClassArgsを引数に渡した場合の動き3
     * 
     * @param x ClassArgsのインスタンス
     */ 
    public void setArg3(final ClassArgs x) {
    	// 引数にfinal付けたら変更できないよ。とか聞いたことあるかもしれません。
    	// でも、好意的に解釈してもそれは嘘です。少なくとも初心者は絶対に騙されたと思うはずです。
    	// x = new ClassArgs(8, 7);
    	// ↑このように引数にインスタンスを代入するなど、引数を変更するようなことをするとコンパイルエラーになります。

    	x.setFieldA(29);
    	x.fieldB = 33;
    	x.print();
    	// 実はfinalをつけていても、setArg2()で行ったパターンの場合は、呼び出し元のインスタンスに影響を与えます。
    	// なぜなら、finalが書き換え不可にしているのは参照先の値であり、参照先を使った操作ではないからです。
    	// C#の場合もこれと同様です。でも、C++のconstを使った場合は上記操作ができなくなります。
    	// C++のconstは解析が複雑になるのにメリットがないってことでJavaでは捨てられた文法だったはずです。
    	// ※ const自体は将来必要になるかもしれないと予約語にはなってるのですがね。結局捨てられました。
    	//
    	// なので、筆者としてはC++のconst同様のものじゃない限り必要ないと思っている(newしても呼び出し元に影響ないし)んですが、
    	// Javaの皆さんはどんな場面で使うんでしょうね？

    	// ちなみに、なんでこんな動きしてるんだろ？と言うと、言葉を変えてみたりなんたりしてますが、
    	// C言語とかいうので聞いたことがあるかもしれない"ポインタ"というものしかJavaにないからです(一応、機能限定化されてます)。
    	// ※ 一応Javaでは参照というのですが、初期の頃のJavaのFAQにも"Javaにポインタがないってのは、とんでもない出鱈目だ。"的な回答があったりします。
    	// この参照型の引数の動きなんて、経験者には"あぁ、ポインタだよ"って説明した方がしっくり来る可能性があるくらいです。
    	// すっげ、どうでもいいのですがC言語的に言ったら final ClassArgsはconst *ClassArgsだし、
    	// publicのsetterとかも封印するならconst * const ClassArgsだなぁと。
    }
}

/**
 * @privateについて勘違いしてるかもしれないことの説明
 * 
 */
class ClassPrivate {
	/** フィールドA */
	private int fieldA;

    /**
     * コンストラクタ
     * 
     * @param a fieldAの初期値
     */ 
	ClassPrivate(int a) {
		fieldA = a;
	}

    /**
     * インスタンスフィールドを表示
     * 
     * @param p 表示するインスタンス
     */
    public void print(ClassPrivate p) {
    	System.out.printf("fieldA(%d)。%n", p.fieldA);

    	// 勘違いしてるかもっていうのはこういう動きのことです。
    	// このメソッドは引数にセットされるインスタンスのprivateなインスタンスフィールドを表示させてます。
    	// privateとかのアクセス制御は"インスタンス"単位で行われると勘違いされてる方がいます。
    	// 覚えておいてほしいですが、アクセス制御は"クラス"単位で行われます。
    	// よって本メソッドのように同一クラスであれば、インスタンスが違ってもprivateなインスタンスフィールドに
    	// アクセスすることが可能です。
    	// これはC++だろうがC#だろうが同じです。
    }
}


/**
 * @いわゆるゲッター、セッターについて一言。
 * 
 */
class Person {
	/** 名前 */
	private String name;
	/** 年齢 */
	private int age;

	// ここではネットのサンプルにあったthisちりばめまくりのテンションで書いてます。

    /**
     * 名前を設定
     * 
     * @param nama 名前
     */ 
    public void setName(String name) {
    //public void setName(String nama) {
        this.name = name;
        // おっとそういえばの話ですが、↑のコメントで殺してる奴のように例え引数名をミスタイプしても、
        // コンパイラはエラーとしません。
        // その場合はthis.name = nameで自分自身を代入ってことになるだけです。
        // this が微妙なのは、このようにthisをつけてもつけなくてもエラーにならない(=強制されない)のと、
        // 引数が異なっていた場合など気付きようがないからです。
        // ましてや、Java誕生当時のC++のコーディング規約に存在したインスタンス変数(フィールドつけるの長いので省略)には、
        // 変数名の先頭にm_をつけるとかは"ダサい"という理由で付けないことになったわけですし。
        // キャメル記法onlyにするより何らかのプレフィックスを付与したか、いっそthisを強制した方が良かったのではと思うんですが、
        // "ダサい"って粋がるなんてアホなことを・・・(今更変えるのも手遅れですし)
    }
    /**
     * 年齢を設定
     * 
     * @param age 年齢
     */ 
    public void setAge(int age) {
        this.age = age;
    }

    /**
     * 名前を取得
     * 
     * @return 名前
     */ 
    public String getName() {
        return this.name;
    }
    /**
     * 年齢を取得
     * 
     * @return 年齢
     */ 
    public int getAge() {
        return this.age;
    }

    /**
     * 新しいインスタンスを取得
     * 
     * @return 新しいインスタンス
     */
    public static Person getNewPerson() {
    	return new Person();
    }
}
