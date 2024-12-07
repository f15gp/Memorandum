/**
 * Javaの勉強 3日目(クラス続き)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test2;

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

        // 画面に表示する
        System.out.println("正常終了");
    }

    /**
     * 最初のメソッド(説明用)
     * 
     */ 
    static void first() {
    	var x = new ClassArgs(3, 5);
        var y = new ClassArgsAndFinal();

        x.print();
        y.setArg(x);
        x.print();

        y.setArg2(x);
        x.print();

        y.setArg3(x);
        x.print();
    }

    /**
     * 2つ目のメソッド(説明用)
     * 
     */ 
    static void second() {
        var p1 = new ClassPrivate(3);
        var p2 = new ClassPrivate(21);
        p1.print(p2);
        p2.print(p1);
    }

    /**
     * 3つ目のメソッド(説明用)
     * 
     */ 
    static void third() {
        var person = new Person();

        person.setName("パーソン");
        System.out.println(person.getName());

        // 入門書その他でよくあるカプセル化の方法として出てくるのが
        // getter/setterだと思います。
        // 思いますが、Java以外の言語に金輪際輸出しないで下さい。
        // そして、こんなものまったくカプセル化でなく、むしろ破壊してます。
        //
        // Javaでこれが広く普及してるのは、まずJavaBeanの仕様がそうだからです。
        // でもね、多分今の人、JavaBeanなんて知らないと思うんですよ。
        // だってJavaでGUI扱う用途なんて・・・・
        // そう、このJavaBeanって元々GUIコンポーネントの規格です。
        // ※1 どうもJavaBeanを誤解したり、後々に作られたほにゃららBeanと勘違いして解説してるWeb記事多いけど。
        // ※2 大まかにいって、デフォルトコンストラクタ必要、"プロパティ"設定・取得のためのgetter/setter、シリアライズ可能
        //
        // GUIコンポーネントって、例えば画面のボタンとかあるわけですが、
        // 大きさとか千差万別ですよね？そうすると、ボタンごとに高さと幅を変更するのって自然なことなんです。
        // だから、GUIコンポーネントってプロパティ設定で外観が変わるのって、自然なことです。そう思います。
        // ただ、不幸は、Java開発者？たちが勝手にこんな仕様を一般的なクラスにも適用し始めたことです。
        // 取り換え可能なモジュールとしてやデータクラス以外こんな仕様にするのは悪夢や・・・
        // ※ ↑の※2読めばピーンと来る人いると思いますが、これってC言語の構造体とほとんど同じですよね？
        //    シリアライズ可能は継ぎ足しですが、C言語も構造体のバイナリダンプ＆読み込みでシリアライズしてるとも言えるし。
        //    C言語で構造体扱ったことある人は分かると思いますが、構造体ってデータを媒介する役割以上を求めると難があって、
        //    複雑な処理に向いてないですよね。利点は"モジュール"単位での再利用性が高いこと。
        //    逆に再利用できるようにするために、処理を単純なものに保つ必要がありますけどね。
        //
        // 更に一定期間、JavaのフレームワークがEntityクラスとかに、このsetter/getterを要求したからだと思います。
        // ※ 最近のはなくても良くなってるというネット記事をみた。
        //
        // コーディング規約に定められてるなら、抵抗できるところまで抵抗すること推奨。
        // 少なくとも他の言語では、こんなもの作ってたら仕事なくなるので、そこは切り離しておいた方がいいです。
        //
        // なぜこれがカプセル化じゃないかというと、そもそもインスタンス変数(フィールドつけるの長いので省略)全部にアクセスできるのがまずいです。
        // え？そのためにpublicメソッドからのみアクセスするんでしょ？と思ったそこのあなた！
        //
        // ・・・メソッド使っただけで、インスタンス変数がインスタンスの"外部"から書き換えれる事実は変わらんでしょ？
        // それだと、インスタンスを何も守ってないんですよ。"カプセル"にしてないんです。
        // ※ そもそも狭義のカプセル化って、インスタンスの外からインスタンス変数を変更できないようにすることなんですけどねぇ。。。
        //
        // そして、きちんとクラスを設計した場合、インスタンス変数を直接読みたい、書きたいことなどあまりありません。
        // むしろインスタンスを使う側は、勝手に内部でうまいことやってよ、俺使うだけだからって形になるのが最高のクラスになります。
        //
        // 例として、イメージしやすいようにファイルクラスがあったとして、現実のファイルアクセスには今どこのデータに
        // アクセスしてるとかの情報が当然インスタンス変数に存在してるはずですが、そんなものインスタンスを使う側は意識してないでしょ？
        // せいぜい次のデータを読みだしたいとかで、今どこを読んでるかなんて必要ないはず。
        // また、CSVとかなら、読みだしたデータは生データを渡されるより、フィールドのListなどに加工した方が使い勝手がいいはず。
        // それなのにインスタンス変数を直接returnするようなgetter書かれたら、がっかりするでしょ。
        // おまけにファイルを開いたり、閉じたりってのは結構色々やる必要があるものですが、普通インスタンスを使う側からしたらopen/closeで
        // 終わらせたいでしょう。間違ってもインスタンス変数を取り出しながら開いたり、閉じたりなんてしたくないでしょう。
        //
        // あと、もう一つありまして、給与を計算するデータを保持してるクラスとかを考えてもらうと分かりやすいのですが、
        // 仮にgetterで手に入れた情報を元にクラス外で給与を計算したとするじゃないですか。
        // そうすると、例えば税の制度変更で修正が必要になった時、その計算をした場所全てが影響を受けてしまいます。
        // もし、データを保持するクラスのメソッド内で必要な計算をして結果を手に入れることが出来ていたなら、
        // 変更しないといけないのはそのクラスのメソッドだけになるんですよ。
        // つまり、getterで手に入れた情報を使う箇所が増えるほど保守性が低下してしまうのですよ。
        // カプセル化以前にこれは、オブジェクト指向の原則に反してるんですよねぇー。
        // 厳密に適用すると面倒な場合もありますが、単一責任の原則(Single Responsibility Principle)がそれですね。
        // ただ、この原則はクラスがそもそも非常に単機能な場合にのみ有効かなと筆者は捉えている概念です。
        // 一つの複雑なクラスを細分化されたクラスで構成ってな場合にも使えるのですが、現実の開発では細分化するのに障壁がある場合が多々・・・

        var p = Person.getNewPerson();
        // getNewPerson()はstaticメソッドなのでちょっと話が違うのですが、
        // JavaにGCってのがあってメモリリークとかってのを考慮しなくていいってのを聞いたことがあるかと思います。
        // でもね、例えばgetNewPerson()みたいに戻り値で参照型のインスタンス変数を返すメソッドがあったらどうなると思います？
        // それはですね、全部の参照先がなくならないとGCが発動できないとなります。
        // つまり、インスタンス側はメソッドが終わったりしてとっくに寿命が切れてたとしても、戻り値で受け取った参照が1つでも生存してたら、
        // GCって働かないんです。てか働いたらダメなんです、参照があるのに勝手にそのインスタンスを消滅させるなんて、バグですｗ
        //
        // また、参照型のインスタンス変数を返してしまう場合、その参照型にpublicのsetterがあったりすると、戻り値で受け取った側はそのsetterを使って
        // インスタンスのインスタンス変数を変更できてしまいます。
        // このパターンが存在すると非常に厄介で、それ故に何も考えずにsetter/getterを用意すると、とんでもないことになります。
        // ※ ↑にも書いてますが、特に気を付けるのはsetterを用意することです。setterなんて少ないほどいいです。
        //    多分後で書く話ですが、このようなのをシャローコピーとも言いますが、ディープコピーしてやらないとまずいケースが確実に存在します。
        //    ディープコピーした場合は、データを手に入れた側が好き勝手いじってもよくなります。★★★
        //
        // それでも、"Entityみたいなデータクラスでは全部setter/getterがいるだろう！"という考えもあるかと思いますが、
        // それはもう既に後で説明するrecordに取って代わられ、役目を終えたと思ってます。★★★
        // てか、classがあれば全てOK。C言語の構造体的なものやenumなんて全部いらないって言語仕様になってたのは、時代背景とか学者仕様ｗってことを考えても、
        // Javaの欠陥だと筆者は思ってましたよ。(だから、record入るのが遅すぎたんじゃないの？と思ってたんですが)
        // ※補足すると、C#の1.0もそういう意味では欠陥仕様でしたね。C++に対して意地はって必要なものまで切り落としたんじゃないか？疑惑が個人的にある。
        //   ま、確かにC++自体確かに複雑な所はあるけど、それって無理やりC言語としても使えるって変な制約があったのがかなり大きく影響してるじゃないかなと思ってる。
    }
}
