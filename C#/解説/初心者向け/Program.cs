// C# 4日で業務コード触れます(Lv5想定)のMain
// はじめに：主にC#6.0位までの主要？文法をつまみ上げて紹介。
//         もっと詳しく分かりやすいサイトもあると思いますが、まぁオイラの独断と偏見で解説を書いてみたよと。
//         多分ここに書いていること全部できれば最低限の文法は扱えると思う、多分、きっと
// 命名規則：インターフェース は 'I' + パスカル記法 (IListなど)
//         ローカル変数は キャメル記法 (hogeHogeなど)
//         それ以外は パスカル記法
// 注意: C#7.0の技法も混じる可能性があるので、一応わかる技法はいつから使えるようになるかバージョンを併記する予定。
//      また、説明なのでコード分析での指摘やクイック操作を完全には除去してません。
//      .Net Core 3.1のプロジェクト設定を使っているので、Net Frameworkとは差異があるかも。
// その他：
//   文法よりライブラリの使い方、設計の方法(デザインパターンのような)を身につける方が重要だと思いますが、
//   とりあえず文法中心に書いてます。
using System;
using System.Collections.Generic;
using CSharpSample2_1;

namespace 初心者向け
{
    class Program
    {
        /// <summary>
        /// いわゆるスタートルーチンです。
        /// </summary>
        /// <param name="args">プログラム起動時の引数</param>
        static void Main(string[] args)
        {
            #region 1日目

#if true // 全部出すとコンソール出力が長いので見たいところだけ #if trueにして

            // 1日目はSample1_1.cs側でやってることが大半
            // だからMain側ではあんまコメント書かない
            var sample1 = new CSharpSample1_1.Sample1_1();

            sample1.Output();
            System.Console.WriteLine(sample1.Name);
            sample1.Name = "Main";
            System.Console.WriteLine(sample1.Name);
            sample1.Func1();
            sample1.Func15();
            sample1.Func2();
            sample1.Func3();
            sample1.Func4();

            CSharpSample1_1.StaticLib.Func5();
            string str1 = "";
            sample1.Func6(ref str1);
            string str2;
            sample1.Func7(out str2);
            System.Console.WriteLine(sample1.Func8(5));
            // C# 4.0から可能。 これは名前付き引数の例。オプション引数ではないxを個別に指定している
            // でも、やったらめったに使うものじゃないし、色々あるので過去の資産に使うのは注意が必要
            System.Console.WriteLine(sample1.Func8(x:10));
#endif
            #endregion

            #region 2日目

#if true
            // 継承クラス
            var h2 = new Hoge2();

            // overrideとnewの違い
            var lh = new List<CSharpSample2_1.Hoge3>
            {
                new CSharpSample2_1.Hoge3(){},
                new CSharpSample2_1.Hoge4(){},
            };
            foreach(var h in lh)
            {
                h.Func1();
            }

            // 抽象クラス
            var dac = new DerivedAbsClass();
            dac.Print();
            dac.Print2();

            // インターフェース
            // var inter = new ISample(); インターフェースだからこれ無理
            var mc = new MulCalc();
            mc.Calc(3, 5);
            Console.WriteLine("計算結果 : {0}", mc.result);

            // インターフェースと抽象クラスの使い分け
            // 1. インターフェースは多重継承できる。でも抽象クラスと違ってメソッド実装ができない
            // 2. 使う側からみた振る舞い(メソッド)の共通化が行いたいだけならインターフェース。
            //    共通化したい対象がインスタンスなら抽象クラス。(抽象化でも良いけど多分共通化の方が分かりやすい)
            //
            //    インスタンスというかクラスはフィールドを持つ関係で状態が内包されていると考え、
            //    その状態含めて振る舞いを共通化したい場合と考えりゃいんじゃねぇかなと

            // 例外
            var es = new ExceptSample();
            try
            {
                es.Func1();
            }
            catch(CSharpSample2_1.WrapNotFoundException ex)
            {
                Console.WriteLine(ex.StackTrace);
            }
            catch(Exception ex)
            {
                // 何でも例外受け取っちゃうので多分他の人に怒られるｗ
                Console.WriteLine(ex.Message);
                Console.WriteLine(ex.StackTrace);
            }
#endif
            #endregion

            #region 3日目

#if true
            // クラスメソッドのデリゲート
            // C# 2.0以前は
            // CSharpSample3_1.DelegateSample.IntReturn Funct1 = new CSharpSample3_1.DelegateSample.IntReturn(CSharpSample3_1.DelegateSample.MulInt);
            // と書きました。が、今は作成済みのインスタンスのメソッドを指定する時とか以外は↓の方が簡単なので、↓使えばよし
            CSharpSample3_1.DelegateSample.IntReturn Funct1 = CSharpSample3_1.DelegateSample.MulInt;
            Console.WriteLine(Funct1(5));
            // -=や+=を使えば自由にデリゲートを追加したり外したりできる。ただし、気を付けるのは
            // 宣言しただけの状態ではデリゲートはnullになっているということ。
            // 実際に使う際は nullチェックをするか何もしない匿名メソッドなどを用意してnull例外が発生しないようにしないといけない
            Funct1 -= CSharpSample3_1.DelegateSample.MulInt;
            Funct1 += CSharpSample3_1.DelegateSample.MulInt;

            var delegetorInst = new CSharpSample3_1.DelegateSample();
            delegetorInst.Func1();

            // イベント
            var button = new CSharpSample3_1.Button();
            var receiver = new CSharpSample3_1.Receiver();
            button.DoEvent += receiver.ReceivedEvent;

            //button.DoEvent -= receiver.ReceivedEvent; null条件演算子がどう働くのかはコメントを付けたり外したりで調べてみ
            // イベント発生！
            button.Clicked("Main-イベント発生サンプル ");

            // 匿名メソッド
            var anonymous = new CSharpSample3_1.AnonymousClass();
            anonymous.Func1();

            // ラムダ
            var lambda = new CSharpSample3_1.LambdaClass();
            lambda.Func1();
#endif

            #endregion

            #region 4日目

#if true
            // LINQだよーん
            var linq1 = new CSharpSample4_1.LINQSsmple();
            linq1.Selector();
            linq1.Wherer();
            linq1.Sorter();
            linq1.Aggreater();

            // ↓実在のディレクトリを指定してね。ただ、ヒットするファイルが多すぎるとウザいで
            var files = linq1.SearchFiles(@"E:\壁紙\バイク", ".jpg");
            foreach (var file in files)
            {
                System.Console.WriteLine(file);
            }

            var eliminateStrings = new List<string> { "str", "test", null, ",", "get" };
            var filtered = linq1.EliminateCommaNull(eliminateStrings);
            foreach (var elem in filtered)
            {
                Console.WriteLine(elem);
            }

            // スレッド
            var threadSample = new CSharpSample4_1.ThreadSample();
            threadSample.StartThread();
            System.Threading.Thread.Sleep(100); // ちょっとSleepでも入れないとスレッドが動く間もなく終わるので・・・

            // タスク(古い書式)
            var taskSample = new CSharpSample4_1.TaskSample();
            taskSample.StartTask();
            System.Threading.Thread.Sleep(100); // ちょっとSleepでも入れないとスレッドが動く間もなく終わるので・・・

            // タスク(新しい？書式)
            taskSample.StartTask2();
            System.Threading.Thread.Sleep(100); // ちょっとSleepでも入れないとスレッドが動く間もなく終わるので・・・

            // タスク async & await版
            // ただこのasync&awaitには悪い所がありまして・・・
            taskSample.StartTask3();
            System.Threading.Thread.Sleep(5000); // awaitするのは呼び出し先のメソッド内なので

            // ↑に書いてる悪い所を知りたい人は次をどうぞ(その内知る必要がどうせあるが)
            taskSample.StartTask4();
#endif

            #endregion

            // お疲れ。これで完了です。
            // 後は実践ですな。。。と言いたいところですが
            // 実践をしながら、以下のページとかを眺めてLevel 10以上を目指してちょうだいな

            // C# 7.0対応 ポケットリファレンスみたいな
            // www.buildinsider.net/language/quickref/csharp/01

            // C# コーディング規則 (C# 本家本元のMicrosoftが書いてるんだからある程度は普及してるんでしょ)
            // https://docs.microsoft.com/ja-jp/dotnet/csharp/programming-guide/inside-a-program/coding-conventions

            // MSによるC#解説 (はっきり言って、下手なサイトを探す位ならMSのページを見た方が確実)
            // まぁ、↓だと静的クラス＆メソッドを開いているので一番トップから見ればいんじゃないかと
            // https://docs.microsoft.com/ja-jp/dotnet/csharp/programming-guide/classes-and-structs/static-classes-and-static-class-members

            Console.WriteLine("end");
        }
    }
}
