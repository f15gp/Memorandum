﻿// サンプル 1-1
// 大枠：変数、コレクション、制御(if, 繰り返し)、クラス
// 命名規則：インターフェース は 'I' + パスカル記法 (IListなど)
//         ローカル変数は キャメル記法 (hogeHogeなど)
//         それ以外は パスカル記法
// 注意: C#7.0の技法も混じる可能性があるので、一応わかる技法はいつから使えるようになるかバージョンを併記する予定

// ↓はVS2017で最初から追加されるusingディレクティブ
// using ディレクティブは、完全修飾子で指定しなくても別の名前空間を使えるようにするもの
// ※ C++/CLIとかから考えると多分参照するDLL(.Net用語ではアセンブリ)の指定でもあろう
// 例えばWriteLineを使って文字列表示したいときSystem.Console.WriteLineとしなくても
// using System.Console;としておけばWriteLineだけで使用できるようになる
using System;
using System.Collections.Generic;

using System.Collections;

// 名前空間はC++と同じクラスの分類・階層に使用する
// 下のSample1_1のメソッドでは、完全修飾子がCSharpSample.Sample1_1.メソッド()となる
namespace CSharpSample1_1
{
    // これはusing aliasディレクティブ。C++みたいに別名を付ける。
    // でも、そんなに使うことはないので忘れ去ってもかまわない
    // Printfは偉大な先輩のC言語をリスペクトしてｗ
    using Printf = System.Console;

    /// <summary>
    /// クラス。クラスは名前空間に直に定義される場合public, private, internalのアクセシビリティをもつ。
    /// 何も付けなかったらinternal。internalとpublicの違いは他のアセンブリから参照できる/できないだけ
    /// 最初から他のアセンブリから見えないようにする場合を除いて、publicで定義してよいのでは？
    /// </summary>
    public partial class Sample1_1
    {
        /// <summary>
        /// このクラスの場合、名前空間に直に書いていないのでpublic, internal, privateが指定できる
        /// でもまぁ、この場合 privateになることが多いんじゃないだろうか(構造体なら話は別だが)
        /// </summary>
        private class Example
        {
        }

        #region フィールド
        // クラスに用意する定数とか、C++でいうメンバ変数(というかプロパティ以外のメンバ変数)をフィールドと呼んでいるようだ。
        // readonlyは代入不可の変数で宣言以外にコンストラクタでも初期化可能。switch文やデフォルト引数には使用不可
        // constはswitch文やデフォルト引数に使えるが、コンパイルでのみ更新されるため問題あり
        // 基本はstatic readonlyを使っとけばいい
        static readonly double PI = System.Math.PI; // ここはPiよりPIの方がなじみがありそうなのでパスカル記法じゃない
        const int Week = 7;
        #endregion

        #region プロパティ
        // いわゆるセッター/ゲッターのこと

        // 最初からあった手動のプロパティ
        // 特殊な場合(複雑な処理をした値を返すなど)を除いて、自動プロパティを使わない理由がないので忘れてもかまわない
        private string name;    // これはフィールドで変数の本体
        public string Name      // これがクラス外からアクセスするプロパティ
        {
            get { return name;  }
            set { name = value; }   // valueは暗黙のパラメータで代入の右辺の値が割り当てられる
        }

        // C# 3.0から使える自動実装プロパティ。名前が違うだけで手動実装と同じ内容がコンパイラによって展開される
        public string Name2 { get; set; }

        // 外部から参照だけできるようにするなら、set側をprivate定義
        public string Name3 { get; private set; }

        // C# 6.0 getのみが許された。でも、readonly扱いなのをお忘れなく
        // readonlyとして暗黙的に扱われるのでコンストラクタでも初期化できる
        public string Name4 { get; } = "I am class";    // C#6.0以降初期化子が許されたのでこれで初期化OK
        #endregion

        #region コンストラクタ
        /// <summary>
        /// コンストラクタ。インスタンス作成時に呼び出される
        /// publicをつけ忘れるとインスタンス化できないとコンパイラに怒られる
        /// C++出身者は最初各メソッドにアクセシビリティを付け忘れるので要注意！(オイラだけ？)
        /// </summary>
        public Sample1_1()
        {
            name = "Sample1_1"; // Nameプロパティの初期化
        }
        #endregion

        #region デストラクタ？
        /// <summary>
        /// デストラクタと呼ばれることもあるけど実際はファイナライザ
        /// 修飾子を付けないしパラメータもない
        /// メモリが回収されるときに呼ばれるものなので、使うことはそんなに多くない。
        /// どうしてもすぐ回収する必要があるならIDisposableを継承して、Disposeを実装するべき
        /// </summary>
        ~Sample1_1()
        {
        }
        #endregion

        #region メソッド
        /// <summary>
        /// C#では関数のことをメソッドという
        /// ()の中がない場合はC++と同じで引数なし。C言語のように型チェックをしないではない
        /// メソッドは、public or private or protected or internal or protected internalのアクセシビリティをもつ。
        /// 何も付けなかったらprivate。
        /// Level5ならpublic(誰からも呼べる), private(自分だけ呼べる), protected(自分と継承先から呼べる)を使い分ければいんちゃう？
        /// Level5でアセンブリを気にすると思えないし・・・
        /// </summary>
        public void Output()
        {
            Printf.WriteLine("hello");  // C#は文字列がすべてUNICODE(UTF-16)で扱われる
                                        // が、サロゲートペアの関係で正確な文字列を求める場合,
                                        // .Length()では求まらないので注意(これ、MFCのCStringでLength使って文字数を出す場合と同じ)
                                        // UTF-16で扱う理由はWindowsがUTF-16であるためと思われる
        }
        #endregion

        #region 変数型
        /// <summary>
        /// 型の説明
        /// </summary>
        public void Func1()
        {
            // これは値型
            byte b = 1;         // 1byte( 8bit整数 符号あり)
            sbyte sb = 1;       // 1byte( 8bit整数 符号なし)
            short s = 1;        // 2byte(16bit整数 符号あり)
            ushort uh = 1;      // 2byte(16bit整数 符号なし)
            int i = 1;          // 4byte(32bit整数 符号あり)
            uint ui = 1U;       // 4byte(32bit整数 符号なし)
            long l = 1L;        // 8byte(64bit整数 符号あり)
            ulong ul = 1UL;     // 8byte(64bit整数 符号なし)
            char c = 'a';       // UNICODE(UTF-16)の文字型

            float f = 0.1f;     // 単精度浮動小数点
            double d = PI;      // 倍精度浮動小数点
            decimal de = 1.1m;  // 10進小数(正確に小数を保持できる。ただし、floatやdoubleより表現できる範囲は狭く、16byte必要)
            bool bo = false;    // 論理値

            // これは参照型
            string str = "ss";  // 文字列 ちなみに@"C:\Hoge"とかけばエスケープシーケンス扱いはなくなる。@付けなかったら"C:\\Hoge"としないといけない
            object o = "abc";   // 全ての参照型のルートクラス (void*みたいなもの) WriteLineで出力するのでしょうがなく文字列を入れた

            // WriteLineの{}は引数の順番。表示したい引数の並んでる順番を指定してる
            // WriteLineでこんな意味のない変数を出すのはC#の場合使ってない変数あるよと丁寧に教えてくれるため
            Console.WriteLine("{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}, {13}, {14}"
                , b, sb, s, uh, i, ui, l, ul, c, f, d, de, bo, str, o);
        }
        #endregion

        #region 列挙
        /// <summary>
        /// 列挙型。C++11と同じでスコープを持つし、型も指定できる(指定できる型は決まってるけど)
        /// </summary>
        public enum Range : int { Ten = 10, Two = 2 };

        /// <summary>
        /// こっちはFlagsAttribute宣言した列挙
        /// ビットフィールドで扱う
        /// </summary>
        [Flags]
        public enum Star
        {
            Sun = 0x01,     // Flagsにより0001
            Moon = 0x02,    // Flagsにより0010
            Earth = 0x04,   // Flagsにより0100
        }
        public void Func15()
        {
            int ten = (int)Range.Ten;   // これキャストが必要
            Console.WriteLine("Ten = {0}", ten);

            Star name = Star.Moon | Star.Earth;
            Console.WriteLine(name);
            Console.WriteLine((int)name);
        }
        #endregion

        #region 配列とList、そしてキャストも
        /// <summary>
        /// 配列とListコレクション
        /// </summary>
        public void Func2()
        {
            // var はC#3.0から 型推論できる場合に型を勝手に勘案してくれる
            // ただ、基本型にも使うと面倒なことになったりもするので、右辺に明確に型が示される場合だけ使えばいんじゃないかと

            // これは配列
            var strArray = new string[] { "ab", "cd", "efg", "hi"};
            // これはArrayList 格納できるのはObject つまりなんでもあり
            var oldList = new ArrayList();
            oldList.Add(1);
            oldList.Add("One");
            // これはList C# 2.0から
            var newList = new List<string>();
            // newList.Add(1); NG!string型のListだから整数は格納できない
            newList.Add("One");

            // 配列を一つづつ出力
            for (int i = 0; i < strArray.Length; i++)
            {
                Console.WriteLine("{0}", strArray[i]);
            }

            // foreachでくるくる回す
            // newListの先頭から一要素ごとに取り出してlistへ格納してループする感じ
            foreach (var list in newList)
            {
                Console.WriteLine("{0}", list);
            }

            // コピーについて
            var from = new int[] { 1, 2, 3 };
            var to = new int[5];
            int[] to2;

            // これで配列のコピー(これだとディープコピー)
            from.CopyTo(to, 0);
            // ↓も配列をコピーしてるように見えるけど、実際はシャローコピー
            // (参照先が共有されているのでfromとto2のお互いへの変更は相互に影響する)
            to2 = from;
            from[0] = 3;
            // シャローで問題ないこともあるが、ディープじゃないと問題になることがあるので注意
            // というよりクラスの配列とか書き換える気ないのに誰かが書き換えた時、シャローだと多分悲惨なことに

            // Listのコピー(当然ディープ、シャローはある) どっちがそうかはデバッガでみてみな
            var list1 = new List<int>() { 3, 2, 1 };
            var list2 = list1;
            var list3 = new List<int>(list1);
            list1[0] = 5;

            // 配列<->List
            var stringArray = new string[] { "str1", "str2" };
            var stringList = new List<string>();
            stringList.AddRange(stringArray);   // これディープコピー
            stringArray[0] = "test";
            var stringArray2 = stringList.ToArray();

            // ()キャストはキャストできない時例外を出す
            // as はキャストできない時nullを返す
            // is はキャストできるかどうかをboolで返す
            // なので型が自明か例外がほしいときはキャスト、例外は嫌ならas
            // isは・・・無視でも良いと思うが
            int temp = (int)oldList[0];
            string temp2 = oldList[1] as string;
            bool temp3 = oldList[1] is int;

            // 結論：Listとforeachだけ覚えればOK。配列やArrayListは忘れ去ってよし
        }
        #endregion

        #region Dictionary
        /// <summary>
        /// もう一つのコレクション　Dictionaryことmap
        /// </summary>
        public void Func3()
        {
            // 一つ目がkey, 2つ目が値
            // Listも同じような形で初期化できるので後から追加するのでなければこの形推奨
            // ただし、基本型だけね。参照型(strignのぞく)だと少しやり方が違う。それは、また、後程
            var mapTable = new Dictionary<string, int>() {
                {"sample1", 123},
                {"sample2", 456},
            };

            // くるくる回してifにhitするのを出力
            // キーのみ受けたりvalueのみ受ける方法もあるけど、まぁそんなに多く使わないだろうからムシムシ
            foreach (var map in mapTable)
            {
                if (map.Key == "sample2")
                {
                    Console.WriteLine("{0}", map.Value);
                }
            }

            // 繰り返しは他にwhileやdo-whileもあるけど、とりあえず忘れ去っていんじゃない？
        }
        #endregion
    }

    #region パーシャル
    /// <summary>
    /// partialを書けば、別ファイルでも指定クラスのメソッドとかを実装できるよ
    /// まぁ、Windows Formの実装を書いたりするのに便利だし、最初はそれが目的だったような気もするけど
    /// 面倒なのはpartialになるクラスに全部partialって書く必要があることだけど
    /// </summary>
    public partial class Sample1_1
    {
        public void Func4()
        {
            Console.WriteLine("Func4");
        }

        #region 引数のref
        /// <summary>
        /// refというのがC#にある。値型(基本型と構造体)でなく参照型(クラス、文字列とか おおむねnewする系統)
        /// は全部C++で言うところの参照渡しになるのだが(つまりC++ならconst &付き、Cならconst * constでの引数)
        /// 実際は値渡しということで呼ばれているようだが、参照型は常にポインタ渡しになってる。(じゃなきゃ、超パフォーマンスに問題あり)
        /// もし、その引数を書き換えたかったらrefを付ければいい。呼び出し元もref付けなきゃいけないけど
        /// いくつかのサイトで参照型をref(or 後に出てくるout)付けなくても書き換えれるとかあるがそれは嘘だ
        /// その手のサイトは非常に多いので鵜呑みにしてはいけない。
        /// もし、refもoutもなくて引数で渡した引数が勝手に書き換え可能ならC#は現代の言語として終わっているｗ
        /// それだと、C89前のC言語かよ！と聞きたくなるわ
        /// 恐らく書いた奴らは検証することもなく他のLL言語がそうだからと書いている気がする
        /// だから、簡単にネットを信じてはいけない
        /// </summary>
        /// <param name="str"></param>
        public void Func6(ref string str)
        {
            str = "abc";
        }
        #endregion

        #region 引数のout
        /// <summary>
        /// outとrefの違いは、簡単に言うとoutの場合、メソッド側に初期化などの代入がないとコンパイルエラーになるということ
        /// なのでoutの場合、初期化してない引数を渡すことが主になる
        /// 使い分けとしては、refの場合書き換える"こと"もある。outの場合"必ず書き換える"基準にするといい
        /// outは具体的にfactoryパターンを使う場合とかになるんじゃないだろうか
        /// でも、まぁ、この辺が必要になることそんなにあるんでしょうか？という感覚
        /// 存外、C#の業務レベルではそんなに書き換え可能かどうかとか、参照型がなんて意識していないような気もする
        /// </summary>
        /// <param name="str"></param>
        public void Func7(out string str)
        {
            str = "abc";
        }
        #endregion

        #region オプション引数
        /// <summary>
        /// これはオプション引数。yを諸略してFunc8(10)と呼び出しても10+5として15が戻る
        ///  C# 4.0から可能。 
        ///  C++だとデフォルト引数(でも、C++だと引数の最後尾に限定してとなるがC#はそうじゃない)と思いなよ
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <returns></returns>
        public long Func8(int x, int y = 5)
        {
            return (x + y);
        }
        #endregion
    }
    #endregion


    #region 静的クラス
    /// <summary>
    /// staticを付けると静的クラスになる。
    /// staticだとnewしなくても存在することになるので、実際のレガシィスタイルなプログラムだと
    /// ライブラリの関数とかに使われてたりする。newしなくても呼び出せるからｗ
    /// </summary>
    public static class StaticLib
    {
        // まぁstaticメソッドだから必然的にpublicになるよね
        // publicじゃなかったら存在意義を小一時間問い詰め・・・れたらいいね(　´_ゝ｀)ﾌｰﾝ
        public static void Func5()
        {
            Console.WriteLine("静的メソッド");
        }
    }
    #endregion

    // あ、あと拡張メソッドなんてのもあるのですが、あんま覚えなくても実務じゃ使わないよ
    // ・・・あ、そういえばDVDドライブのリジェクト処理を実装するために一度使って、それをコピーして使わせてほしい
    // なんて言われた気もするけど、そんなに使う機会はない。
    // 必要になったら眺める位で丁度良いんじゃないかと
}

// これで1日目終了 Level2くらいかなぁ
