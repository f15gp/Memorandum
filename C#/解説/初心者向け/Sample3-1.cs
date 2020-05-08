﻿// サンプル 3-1
// 大枠：delegate, event, ラムダにつながる道
// 命名規則：インターフェース は 'I' + パスカル記法 (IListなど)
//         ローカル変数は キャメル記法 (hogeHogeなど)
//         それ以外は パスカル記法
// 注意: C#7.0の技法も混じる可能性があるので、一応わかる技法はいつから使えるようになるかバージョンを併記する予定

using System;

namespace CSharpSample3_1
{
    #region デリゲート

    // デリゲートはメソッド参照(関数ポインタみたいなもん)する"型"。
    // 自分で定義できる。
    // Func, Action, Predicate他 最初から用意されているものもある。
    // すべてのデリゲートはDelegate型からの派生型となるが普通は専用キーワードを使う

    class DelegateSample
    {
        // 引数にintをとってintを返すメソッドを参照するデリゲート型
        public delegate int IntReturn(int value);

        /// <summary>
        /// ↑のデリゲート型に対応するクラスメソッド。
        /// Mainから呼ぶのでstaticを付与
        /// </summary>
        /// <param name="value">計算に使用する値</param>
        /// <returns>計算結果</returns>
        public static int MulInt(int value)
        {
            return value * 5;
        }

        /// <summary>
        /// ジェネリックを使う
        /// とりあえず Func<T, TResult>を使う。戻り値いらないならAction使いなさい
        /// </summary>
        public void Func1()
        {
            // str1の長さを表示するだけ。サンプルだからこうやってるのであって、
            // 当たり前だが文字列の長さが知りたければ.Lengthを使えばいい
            string str1 = "Hello, world!";
            Func<string, int> GetStringLength = GetLength;
            Console.WriteLine(GetStringLength(str1));
        }
        /// <summary>
        /// Func1から呼び出され文字列の長さを返す
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
    /// イベントの説明のため、ボタンじゃないけどボタン的なクラスというものを作ってみる
    /// </summary>
    public class Button
    {
        // これがevent宣言
        // 戻り値がない想定なのでActionを使う
        public event Action<string> DoEvent;

        /// <summary>
        /// イベント発生用関数。呼ばれたら、DoEventに登録されているメソッドを呼び出す
        /// </summary>
        /// <param name="eventName"></param>
        public void Clicked(string eventName)
        {
            Console.WriteLine("クリック イベント発生");

            // C# 6.0から null条件演算子と呼ばれる
            // 対象がnullかどうかで振る舞いが変わる
            // Invokeが何かは自分で調べろ
            DoEvent?.Invoke(eventName);
        }
    }

    /// <summary>
    /// イベントを受けるために用意するクラス
    /// </summary>
    public class Receiver
    {
        /// <summary>
        /// イベントによって呼び出される
        /// </summary>
        /// <param name="eventName">イベント名</param>
        public void ReceivedEvent(string eventName)
        {
            Console.WriteLine("{0}イベント発生を検知", eventName);
        }
    }

    #endregion

    #region 匿名メソッド

    // 匿名メソッドはラムダの旧世代版
    // はっきり言ってラムダ使いなさいなのだが、
    // 慣れてない方とかはこれ使う方が読みやすいかもしれないこともあるだろう。
    // そして、時代と共に変わったんだよを示すためにあえてサンプルとして
    // 一応 C# 2.0(visual studio 2005)から使えるよ。10年以上たってるから知らないとかねぇだろ

    public class AnonymousClass
    {
        public void Func1()
        {
            // 意味なく↓で匿名メソッド使うからね
            // delegateってのが付いてるのが特徴なんですけどねぇ
            // 文字列の長さ好きだな、オイラ
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

    // ラムダは、"デリゲート 型または 式ツリー 型を作成するために使用できる 匿名関数"(MSDNにそう書いてある)
    // が、もともとは関数型言語で無名関数と呼ばれ、関数または式が第一級オブジェクトとして扱われる関数型言語では当たり前のように使われる機能
    // C++erであっても関数ファンクタ使いまくってると欲しくなる機能(だからC++11で標準化された)
    // C# 3.0(visual studio 2008)から使えるよ。10年近くたってるから知らないとかねぇだろ
    // あと最近のC#というか.Netの機能では当たり前のようにラムダが出てくるので、必修の機能
    // ま、ロングスカートをマイクロスカートにすると、"1行で関数定義＆実装が出来ちゃう機能。
    // でもって型を作り出すからdelegateとかで持ち運び可能だよ"な機能かなぁ

    // そういえば昔Sさんにラムダの何が良いんですか？って聞かれたなぁ
    // あの当時Sさんは関数ファンクタ扱ってなかったけど。
    // なぜかといえば、C++ で for_each回すたんびにPredicator(比較関数ファンクタ)を書くためだけに、
    // 新しい名前付けに苦しむクラス作成しなくちゃいけないってのが無くなることだよ。あと、関数持ち運べるしね
    // なんて、今なら言ってもいいのかしらねぇ
    // 特にC++03だと関数ポインタをpredicatorに指定できなかったからねぇ(C++11だとstd::functionの関係で出来るんだけどさ)

    public class LambdaClass
    {
        public void Func1()
        {
            // 意味なく↓でラムダ使うからね
            // 分かりやすくするため匿名メソッドと同じ処理にする
            string str = "TEST";
            Func<string, int> lambdaFunc = (string value) =>
            {
                return value.Length;
            };
            Console.WriteLine(lambdaFunc(str));
            // ただ、実際には型推論とかあるので↑の場合、多分MSDNとかWeb上では
            // このように書かれるはず(複数の引数とかあれば別なんだけどね。一言。書式に慣れてねハートw)
            // Func<string, int> lambdaFunc = value => value.Length
            //                                引数      戻り値. returnがなければ型推論
        }
    }

    #endregion
}
