// サンプル 4-1
// 大枠：LINQ, 非同期まわり
// 命名規則：インターフェース は 'I' + パスカル記法 (IListなど)
//         ローカル変数は キャメル記法 (hogeHogeなど)
//         それ以外は パスカル記法
// 注意: C#7.0の技法も混じる可能性があるので、一応わかる技法はいつから使えるようになるかバージョンを併記する予定

using System;
using System.IO;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace CSharpSample4_1
{
    #region LINQ

    // ふはは。LINQです。正式名称は忘れた。
    // SQLとの親和を考えて採用された機能らしいが、今やそんなこと関係なしに使われる機能。
    // XMLとも複雑に絡んでるしね。
    // 一応 C#3.0(Visual Studio 2008)から使えるよ。もう10年以上たつから当たり前のように使われるし、
    // 逆に理解できないなら10年前の技術から取り残されている可能性も・・・

    // まぁ、LINQにも色々あるのですが、基本となるselect, where, sort, aggregateを紹介してみますか。

    public class LINQSsmple
    {
        /// <summary>
        /// selectのサンプル。
        /// 射影とも呼ばれるが、ぶっちゃけ各々の値に対して操作を適用する感じかな？
        /// SQL詳しい人ならmapだよ。で終わりなのだが。
        /// </summary>
        public void Selector()
        {
            // こっからは説明済みだからラムダを当たり前のように使うからね。
            var scr1 = new[] { 3, 4, 5, 6 };
            var selected = scr1.Select(elem => elem * 2);
            foreach (var elem in selected)
            {
                Console.WriteLine(elem);
            }
        }

        /// <summary>
        /// where(いわゆるfilter)で条件適合のものを取り出す。
        /// </summary>
        public void Wherer()
        {
            var src2 = new[] { 9, 7, 4, 3 };
            // 5より大きい要素だけを取り出す。
            var where = src2.Where(elem => elem > 5);
            foreach (var elem in where)
            {
                Console.WriteLine(elem);
            }
        }

        /// <summary>
        /// 昇順に並び替える。 OrderByで値を指定して同値ならThenByで順列を付ける。
        /// 降順ならOrderByDescending, ThenByDescendingを使う。
        /// </summary>
        public void Sorter()
        {
            var src3 = new[]
            {
                // あれ？この記法いつのバージョンからオッケーなんだっけなぁ。。。
                new { x = 1, y = 2 },
                new { x = 3, y = 4 },
                new { x = 1, y = 1 },
            };
            var sort = src3.OrderBy(elem => elem.x).ThenBy(elem => elem.y);
            foreach (var elem in sort)
            {
                System.Console.WriteLine("x:{0} y:{1}", elem.x, elem.y);
            }
        }

        /// <summary>
        /// 畳み込み。
        /// 単純に全部足して1要素に畳み込むだけ。
        /// </summary>
        public void Aggreater()
        {
            var src4 = new[] { 3, 2, 9, 6 };
            // ↓ラムダの第1引数がそれまでの計算結果、第2引数が要素。
            var fold = src4.Aggregate((sum, elem) => sum + elem);
            Console.WriteLine(fold);
        }

        // 他にも Count, Take, First, Last, Max, Min, Contains, All, Any, Distinct
        // など色々あるよ。
        // Any や Countとかはwhereとかでも出来るのだけど、Anyとかの引数にラムダ式与える方が意味がはっきりするのでそちら優先。
        // 逆になんでもかんでもwhere使ってるとそれしか知らないんだろうな・・・(　´_ゝ｀)ﾌｰﾝと思っておけばいい。


        // 少しだけLINQを実用的にするパターンを↓に2つほど。

        /// <summary>
        /// dirPath 以下のファイルの中でstrの文字列を含むファイル名のファイル群を返す。
        /// LINQの結果はIEnumerableなのでそれを返すよ。それにIEnumerableならforeachで回せるしね。
        /// </summary>
        /// <param name="dirPath">ディレクトリパス</param>
        /// <param name="str">検索対象のファイル名</param>
        /// <returns></returns>
        public IEnumerable<string> SearchFiles(string dirPath, string str)
        {
            // GetFilesとIndexOfの例外はcatchしていない。

            // 指定フォルダーのファイルをサブフォルダーまで列挙する。
            // GetFilesの例外は無視。
            var di = new System.IO.DirectoryInfo(dirPath);
            IEnumerable<System.IO.FileInfo> fiList = di.GetFiles("*.*", System.IO.SearchOption.AllDirectories);

            // str を含むかでフィルターした後、フルパスに変換。
            return
                fiList
                .Where(fi => { return (0 <= fi.Name.IndexOf(str, StringComparison.CurrentCultureIgnoreCase)); })
                .Select(fi => { return fi.FullName; });
        }

        /// <summary>
        /// 渡された文字列のリストに,もしくはnull(or "")が入っていたら除去した文字列群を返す
        /// </summary>
        /// <param name="elements">除去対象の文字列</param>
        /// <returns>除去し終わった文字列</returns>
        public IEnumerable<string> EliminateCommaNull(List<string> elements)
        {
            return elements.Where(elem =>
            {
                if (string.IsNullOrEmpty(elem))
                {
                    return false;
                }
                else
                {
                    return !elem.Equals(",");
                }
            });
        }
    }

    #endregion

    #region スレッド

    public class ThreadSample
    {
        /// <summary>
        /// スレッドのサンプル
        /// </summary>
        public void StartThread()
        {
            // とりあえずスレッドを作ってみる
            // スレッドのスタートルーチンはラムダで与える
            // でも、今やタスクやら何やらがあるのでスレッド単体は嫌われる
            var t1 = new System.Threading.Thread(() => { Console.WriteLine("hoge"); });
            t1.Start();
        }
    }

    #endregion

    #region タスク

    public class TaskSample
    {
        /// <summary>
        /// タスクのサンプル
        /// スレッドに比べて何がいいかというとスレッドプール(どうせ根幹はWin32のThreadPool API使ってるのだろうけど)
        /// されているので生成、破棄コストが各段に少ないってこと。
        /// ナウい？(最近の)やり方ではないので、awaitやasync使ってません。だから、呼び出し側はsleepしてね
        /// </summary>
        public void StartTask()
        {
            var t = new System.Threading.Tasks.Task(() =>
            {
                try
                {
                    // ↓最後のusingの使用方法。
                    // using() {}の最後にStreamWriterのDisposeメソッドが呼ばれるように自動展開される。
                    // よって、スコープの終わりでStreamWriterは解放される。
                    // ファイルとかは確実にメソッド内で閉じたい場合がほとんどだろうから、その辺にはよく使う。
                    // ファイルを作って書き込んじゃうので安全な場所(=ファイルパス)でやってね！
                    using (var sw = new System.IO.StreamWriter("test.txt"))
                    {
                        try
                        {
                            sw.WriteLine("Hello, C# world!");
                        }
                        catch (Exception e)
                        {
                            // ここは書き込み時のエラーに対処
                            // 例外を握りつぶしなので(ry
                            Console.WriteLine("エラー:{0}", e.Message);
                        }
                    }
                }
                catch (Exception e)
                {
                    // ここはStreamWriterの生成に失敗した場合
                    // 例外を握りつぶしなので(ry
                    Console.WriteLine("エラー:{0}", e.Message);
                }
            });
            t.Start();
        }

        /// <summary>
        /// 現代？版タスク実行。
        /// Task.Runの方が現代だろ？というのは置いておいて。
        /// </summary>
        public void StartTask2()
        {
            Object lockObj = new Object();

            // 全然意味ないけど、むやみにlock(クリティカルセクション)してみる。
            lock (lockObj)
            {
                var t = Task.Factory.StartNew(() =>
                {
                    System.Console.WriteLine("task2");
                });
            }
        }

        /// <summary>
        /// 現代？版タスク await/asyncが使いたかったので。。。
        /// await使ってるのでメソッド定義にasyncが登場。
        /// </summary>
        public async void StartTask3()
        {
            // awaitによってその後のタスク処理の完了を待ち合わせてくれるよ。
            // ただし待ち合わせていても、↓のタスクは非同期で動くので呼び出し元の時間軸とは関係ないよ。
            await Task.Run(() =>
            {
                for (int i = 0; i < 3; i++)
                {
                    System.Console.WriteLine("task3");
                    System.Threading.Thread.Sleep(1000);
                }
            });
        }

        /// <summary>
        /// async & await の悪い所改め
        /// </summary>
        public void StartTask4()
        {
            // 非同期タスク開始
            var reader = new ReadSample();
            var asyncJob = reader.Reader();

            // 非同期タスクの完了待ち
            asyncJob.Wait();

            // 入力待ち
            Console.ReadLine();

            // 悪いのは2点あった。
            // 前のサンプルのように async voidとしてしまうとreader.Readerでタスクが生成されないので、
            // 呼び出し側は待ち合わせが出来ない。これが1つめの良くなかった点。
            // * async voidは多分イベントハンドラ以外で使わないような。。。
            //
            // async関数は、awaitの部分を待って、await処理が終わったらawaitの後から処理がすすむのだが、
            // それはあくまでasync関数の中のお話。呼び出し元はawaitのタイミングで処理が戻ってくる。
            // なにせ、async関数の方は非同期で動いてますんで。
            // よって、GUIと違ってコンソールの場合、mainで盛大にsleep入れるかタスクの完了を待たないと、
            // 処理前にMainが終わってしまうｗ これが2つめの良くなかった点。
            // 前のはsleepを入れてるし、今回のは待ち合わせしてるから悪い点としては変わらないと思うかもしれない。
            // 実際ある意味ではそうなのだが、sleepは処理が終わっても一定時間待つ可能性があるなど待ち合わせとしては不適切。
            // しかし、前回はasync voidなのでsleepで待たざるを得ないのが異なる。
            //
            // でも、コンソールなら待たせてもいいけどGUIの場合、どんどん先に進めさせて処理させないと応答が固まるので、
            // asyncに慣れるまではBackGroundWorkerとかタスクを使った方が混乱しないかも？
        }
    }

    /// <summary>
    /// async/awaitの説明のためのサンプル
    /// </summary>
    class ReadSample
    {
        /// <summary>
        /// ファイルを読み出して画面に表示する人。深い意味はない。
        /// </summary>
        public async Task Reader()
        {
            string fileName = @"G:\test.txt";   // 実在するファイルパス

            try
            {
                // 中身がでかいのを読ませると途中で切れるよ。4096byteまでにしてね。
                // まぁ、全部読みだしてもいんだけどねぇ。
                string text = await FileReaderAsync(fileName);
                Console.WriteLine(text);
            }
            catch (Exception ex)
            {
                // 多分ファイルが存在しないとか位しか出ないだろうけど、ま、全部取ってしまおう。
                Console.WriteLine(ex.Message);
            }
        }

        /// <summary>
        /// 非同期でファイルを読むタスク
        /// </summary>
        /// <param name="path">ファイルパス</param>
        /// <returns>読み取ったテキスト</returns>
        private async Task<string> FileReaderAsync(string path)
        {
            // ファイルを開く
            using (var ReadStream = new FileStream(path,
                FileMode.Open, FileAccess.Read, FileShare.Read,
                bufferSize: 4096, useAsync: true))
            {
                var sb = new StringBuilder();

                var buffer = new byte[4096];
                int numRead;

                // 非同期に読み込む
                Encoding.RegisterProvider(CodePagesEncodingProvider.Instance);  // UWPやNet Coreでshift-jis扱う場合はこいつが必要。
                while ((numRead = await ReadStream.ReadAsync(buffer, 0, buffer.Length)) != 0)
                {
                    string text = System.Text.Encoding.GetEncoding("Shift_JIS").GetString(buffer);
                    sb.Append(text);
                }

                return sb.ToString();
            }
        }
    }
    #endregion
}
