// サンプル 3-1
// 大枠：delegate, event, ラムダにつながる道
// 命名規則：インターフェース は 'I' + パスカル記法 (IListなど)
//         ローカル変数は キャメル記法 (hogeHogeなど)
//         それ以外は パスカル記法
// 注意: C#7.0の技法も混じる可能性があるので、一応わかる技法はいつから使えるようになるかバージョンを併記する予定。

using System;

namespace CSharpSample3_1
{
    #region デリゲート

    // デリゲートはメソッド参照(関数ポインタみたいなもん)する"型"。
    // 自分で定義できる。
    // Func, Action, Predicate他 最初から用意されているものもある。
    // すべてのデリゲートはDelegate型からの派生型となるが普通は専用キーワードを使う。

    class DelegateSample
    {
        // 引数にintをとってintを返すメソッドを参照するデリゲート型
        public delegate int IntReturn(int value);

        /// <summary>
        /// ↑のデリゲート型に対応するクラスメソッド。
        /// Mainからインスタンスを経由せずに使用するのでstaticを付与しておく。
        /// </summary>
        /// <param name="value">計算に使用する値</param>
        /// <returns>計算結果</returns>
        public static int MulInt(int value)
        {
            return value * 5;
        }

        /// <summary>
        /// ジェネリックを使う。
        /// とりあえず Func<T, TResult>を使う。戻り値いらないならActionを使いなさい。
        /// </summary>
        public void Func1()
        {
            // str1の長さを表示するだけ。サンプルだからこうやってるのであって、
            // 当たり前だが文字列の長さが知りたければ.Lengthを使えばいい。
            // ※ サロゲートペアの関係上、厳格な文字数が欲しかったらLengthはダメよ。
            string str1 = "Hello, world!";
            Func<string, int> GetStringLength = GetLength;
            Console.WriteLine(GetStringLength(str1));
        }
        /// <summary>
        /// Func1から呼び出され文字列の長さを返す。
        /// </summary>
        /// <param name="value">長さを調べる文字列</param>
        /// <returns>渡された文字列の長さ</returns>
        public int GetLength(string value)
        {
            return value.Length;
        }
    }

    #endregion

    #region イベント

    /// <summary>
    /// イベントの説明のため、ボタンじゃないけどボタン的なクラスというものを作ってみる。
    /// </summary>
    public class Button
    {
        // これがevent宣言。
        // 戻り値がない想定なのでActionを使う。
        public event Action<string> DoEvent;

        /// <summary>
        /// イベント発生用関数。呼ばれたら、DoEventに登録されているメソッドを呼び出す。
        /// </summary>
        /// <param name="eventName"></param>
        public void Clicked(string eventName)
        {
            Console.WriteLine("クリック イベント発生");

            // C# 6.0から null条件演算子と呼ばれる。
            // 対象がnullかどうかで振る舞いが変わる。
            // Invokeが何かは自分で調べろ。
            DoEvent?.Invoke(eventName);
        }
    }

    /// <summary>
    /// イベントを受けるために用意するクラス。
    /// </summary>
    public class Receiver
    {
        /// <summary>
        /// イベントによって呼び出される。
        /// </summary>
        /// <param name="eventName">イベント名</param>
        public void ReceivedEvent(string eventName)
        {
            // C#6.0から 文字列補完式で表示してみよう。
            // ""の前に$付けて{}の中に数字じゃなくて変数とかを直入れ。
            //Console.WriteLine("{0}イベント発生を検知", eventName);
            Console.WriteLine($"{eventName}イベント発生を検知");
        }
    }

    #endregion

    #region 匿名メソッド

    // 匿名メソッドはラムダの旧世代版。
    // はっきり言ってラムダ使いなさいなのだが、
    // 慣れてない方とかはこれ使う方が読みやすいかもしれないこともあるだろう。
    // ※慣れより省略が少ないだけでは？
    // そして、時代と共に変わったんだよを示すためにあえてサンプルとして。
    // 一応 C# 2.0(visual studio 2005)から使えるよ。10年以上たってるから知らないとかねぇだろ。

    public class AnonymousClass
    {
        public void Func1()
        {
            // 意味なく↓で匿名メソッド使うからね。
            // delegateってのが付いてるのが特徴なんですけどねぇ。
            // 文字列の長さ好きだな、オイラ♪
            string str = "TEST";
            Func<string, int> anonymousFunc = delegate (string value)
            {
                return value.Length;
            };
            Console.WriteLine(anonymousFunc(str));
        }
    }

    #endregion

    #region ラムダ

    // ラムダは、"デリゲート 型または 式ツリー 型を作成するために使用できる 匿名関数"(MSDNにそう書いてある)。
    // が、もともとは関数型言語で無名関数と呼ばれ、関数または式が第一級オブジェクトとして扱われる関数型言語では当たり前のように使われる機能。
    // C++erであっても関数ファンクタ使いまくってると欲しくなる機能(だからC++11で標準化された)。
    // C# 3.0(visual studio 2008)から使えるよ。10年以上たってるから知らないとかねぇだろ。
    // 最近のC#というか.NETの機能サンプルでは当前のように説明なしに使われるので、必修の機能。
    // ま、"名前なしに関数を定義し、型を作り出すからdelegateなどで持ち運び可能だよ"な機能かなぁ？

    public class LambdaClass
    {
        public void Func1()
        {
            // 意味なく↓でラムダ使うからね。
            // 分かりやすくするため匿名メソッドと同じ処理にする。
            string str = "TEST";
            Func<string, int> lambdaFunc = (string value) =>
            {
                return value.Length;
            };
            Console.WriteLine(lambdaFunc(str));
            // ただ、実際には型推論とかあるので↑の場合、多分MSDNとかWeb上では、
            // ↓のように書かれるはず(複数の引数とかあれば別なんだけどね。書式に慣れてねハートw)
            // Func<string, int> lambdaFunc = value => value.Length
            //                                引数      戻り値. returnがなければ型推論
        }

        // そういえばラムダは何が良いんですか？って聞かれることがある。
        // 言語によって違うので一括りには言えない。
        // 例えばC++ならアルゴリズムに渡す関数ファンクタとして良く使うし、関数ポインタの代わりとしてやコールバックに使う。
        // C#でも同じくコールバック、関数ポインタ的なことに使うし、パターンハッチングなんかもその発展形だろうな。
        // よって利点は各自でどんどん探してみてくれ(というか、C#でLINQやTask使うとラムダは嫌でも頻出するだろうけど)。
        // そもそも慣れないと、どんなに良い書き方も面倒/分かりにくい だけ、という印象を持たれることが多い気がする。
        //
        // ラムダは'式'であることが最大の特徴なので例えば以下のような使い方も出来る。
        // 意味のある処理じゃないけど。
        // ※旧形式に頭が凝り固まってる人は慣れが必要かな？
        public delegate bool IsShowable();
        public class Menu
        {
            public readonly string Name;
            public readonly Action<string> Action;
            public readonly IsShowable IsShow;

            public Menu(string name, Action<string> action, IsShowable isShow)
            {
                Name = name;
                Action = action;
                IsShow = isShow;
            }
        }
        private static void Print(string value)
        {
            Console.WriteLine($"{value}");
        }
        private static Menu[] menu = {
            // いつでも表示可能
            new Menu("ハム", Print, ()=>true),
            // 19時以降表示可能
            new Menu("お酒", Print, ()=>DateTime.Now.Hour >= 19),
        };
        // ↑みたいに初期化と同時に判定式を埋め込んだりね。使い方は色々よ。
    }

    #endregion
}
