// サンプル 2-1
// 大枠：クラスの継承と例外
// 命名規則：インターフェース は 'I' + パスカル記法 (IListなど)
//         ローカル変数は キャメル記法 (hogeHogeなど)
//         それ以外は パスカル記法
// 注意: C#7.0の技法も混じる可能性があるので、一応わかる技法はいつから使えるようになるかバージョンを併記する予定。

using System;
using System.IO;                        // これファイル検索で使う
using System.Runtime.CompilerServices;  // これ例外の行番号で使う

namespace CSharpSample2_1
{
    #region 継承をする
    /// <summary>
    /// Hoge2の親クラス
    /// </summary>
    public class Hoge1
    {
        public Hoge1()
        {
            Console.WriteLine("Hoge1 生まれる");
        }
        public void Print()
        {
            Console.WriteLine("Hoge1");
        }
    }

    /// <summary>
    /// Hoge1を継承したクラス。
    /// 継承するには : 親クラスを指定すればok。
    /// ただし、アクセシビリティが異なるクラス同士だと怒られるので注意。
    /// </summary>
    public class Hoge2 : Hoge1
    {
        /// <summary>
        /// コンストラクタ。
        /// 親のコンストラクタを呼んで親のメソッドを呼び出している。
        /// </summary>
        public Hoge2() : base()
        {
            base.Print();
        }
    }
    #endregion

    #region overrideとnew
    /// <summary>
    /// overrideとnewがどう違うのかだけのために用意したクラス。
    /// vitualは派生クラスで書き換え可能かを示す。
    /// ただし、virtual付いたからって必ず書き換えないといけないわけじゃない
    /// </summary>
    public class Hoge3
    {
        public virtual void Func1()
        {
            Console.WriteLine("Hoge3-Func1");
            Func2();
        }

        public virtual void Func2()
        {
            Console.WriteLine("Hoge3-Func2");
        }
    }

    /// <summary>
    /// new と overrideがどう違うのかだけ示す役割のクラス。
    /// </summary>
    public class Hoge4 : Hoge3
    {
#if true // #if falseにするとこっち側が無効になる。

        /// <summary>
        /// 派生クラスが親クラスのメソッドを書き換えちゃうよ。
        /// overrideじゃなくてnewなら型に応じて呼び出されるメソッドが異なるよ。
        /// newが出てきたらたいていの場合、間違いだと思う。
        /// </summary>
        public override void Func1()
        {
            Console.WriteLine("Hoge3 virtual method");
        }

#else

        /// <summary>
        /// newを付けるとメソッドが隠蔽される。
        /// 隠蔽じゃわかりにくいだろうが、違いが出るのはポリモーフィズムするとき。
        /// overrideならインスタンスに応じて該当するメソッドを呼び出すが、newだと作成したインスタンスに応じて呼ばれるメソッドが決定する。
        /// 親クラスのインスタンスなら親クラスだし、派生クラスのインスタンスなら派生クラスのメソッド。
        /// 親クラスのメソッドにいれて～というポリモーフィズム目的なことをすると、派生クラスのメソッドは呼ばれない。
        /// その部分に対して、newが出ると多分何か間違えている
        /// </summary>
        public new void Func1()
        {
            Console.WriteLine("Hoge3 new method");
        }

#endif
    }
    #endregion

    #region 抽象クラス、メソッドとは

    /// <summary>
    /// abstractつけたら抽象クラス。このクラス単体でのインスタンス化は出来ない。
    /// アクセシビリティはpublicかprotected。
    /// </summary>
    public abstract class AbsClass
    {
        /// <summary>
        /// こちらは関数実体を実装しないとコンパイルエラーになる。
        /// </summary>
        public void Print()
        {
            Console.WriteLine("AbsClass-Print");
        }

        /// <summary>
        /// これが抽象メソッド。実装はしちゃいけない。
        /// 派生クラス側で必ずoverrideしないといけない。
        /// </summary>
        public abstract void Print2();
    }

    /// <summary>
    /// 抽象クラスを具現化するクラス。
    /// </summary>
    public class DerivedAbsClass : AbsClass
    {
        /// <summary>
        /// もし、これが
        /// public void Print2() or public new void Print2()
        /// だと書き換えてないのでコンパイラに怒られる。
        /// </summary>
        public override void Print2()
        {
            Console.WriteLine("DerivedAbsClass-Print2");
        }
    }
    #endregion

    #region インターフェース

    /// <summary>
    /// これがインターフェース。メソッドにはvirtualついてないけど、暗黙に添付される。
    /// インターフェースなんだから当たり前だけど。
    /// メソッド宣言は出来るが実装は出来ない。プロパティを宣言できる(そうすると派生先が同じプロパティを用意しないとダメ)
    /// でもなぁ、インターフェースだとprivate setとかに出来ない(privateで怒られる)から、使い道は・・・。
    /// 全メソッド、プロパティのアクセシビリティはすべてpublic強制。
    /// 
    /// でも出来るから書いてるだけで、インターフェースにプロパティ用意はやめた方がいいと思う。
    /// それをやってしまうと、メソッド(振る舞い)の共通化に対して、データ入出力も暗に規定してしまうので。
    /// </summary>
    interface ISample
    {
        /// <summary> 計算結果を入れるところ </summary>
        double Result { get; set; }

        /// <summary>
        /// なんか計算してね
        /// </summary>
        /// <param name="x">計算値1</param>
        /// <param name="y">計算値2</param>
        void Calc(int x, int y);
    }

    /// <summary>
    /// とりあえず掛け算してみる
    /// </summary>
    public class MulCalc : ISample
    {
        /// <summary>
        /// これ計算結果いれるところ
        /// </summary>
        public double Result { get; set; }

        /// <summary>
        /// インターフェースの場合、overrideって付けれない。
        /// でも実装が見つからないとちゃんと怒られるから、実装漏れかどうかはすぐわかる。
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        public void Calc(int x, int y)
        {
            Result = x * y;
        }
    }

    #endregion

    #region 例外

    /// <summary>
    /// FileNotFoundExceptionをラップする独自例外クラス
    /// </summary>
    public class WrapNotFoundException : Exception
    {
        public WrapNotFoundException() { }
        public WrapNotFoundException(string message) : base(message) { }
        public WrapNotFoundException(string message, Exception inner) : base(message, inner) { }
    }
    /// <summary>
    /// 意図的に起こす例外
    /// </summary>
    public class ExceptSample
    {
        /// <summary>
        /// 一つだけ注意。例外はオブジェクト指向におけるgotoともいわれる。
        /// また、何を呼び出し元にスローして、何をスローしないのかもきちんと決めておかないと痛い目をみる。
        /// ※ていうか本当にまともなプロジェクトなら決まってる。決まってない時点で、それはまともじゃない。
        /// 
        /// スローしない場合、戻り値あるいはタプルで何が起きたか教えてやるべき。
        /// タプルの一つ目が結果で残りが結果値とかに決め打ちしたってよさげ。
        /// </summary>
        public void Func1()
        {
            try
            {
                // ファイルの属性を取得(こんなファイル or フォルダはないという想定)
                File.GetAttributes(@"D:\WORK");
            }
            catch (FileNotFoundException ex)    // ちなみに何も使う予定がないならexって書かなくてよい。逆に書くと"使われてないよ"と丁寧に教えてくれるｗ
            {
                Console.WriteLine("例外キャッチ");
                throw new WrapNotFoundException("再スローします" + GetLineNumber(), ex);
                // throw ex; ←これをやるとスタックトレースがつぶれるので嫌がられるはず。1階層なら違いなくても多階層あるとね・・。
                // throw; ex使う予定ないし、再スローするだけなら左で。これだとスタックトレースつぶさない。
            }
            finally
            {
                Console.WriteLine("必ず実行される");
            }
        }

        /// <summary>
        /// デバッグ用 行番号を返す。ただし、このCallerなんちゃらはC# 5.0(visual studio 2012)あたりから
        /// 入った機能くさい。
        /// </summary>
        /// <param name="line"></param>
        /// <returns>行番号</returns>
        int GetLineNumber([CallerLineNumber] int line = 0)
        {
            return line;
        }
    }

    #endregion
}
