'''
一週間でPython3プログラムいじれるぜ！講座？ 1日目
変数、型、演算、文字列、if、リスト・タプル・辞書(配列的なのがいるかなと)
'''

def sample1_base():
    """講座1日目で使う関数を呼び出す母体。

    引数:
    なし
    """
    variable_type()
    calculate_numeric()
    compare()
    string_etc()
    like_array()
    tupler()
    dicter()


def variable_type():
    """変数の型？を説明する。

    引数:
    なし
    """

    # 先に言っておきますが、Pythonでは変数の型を宣言して使うというものじゃありません。
    # 型自体はありますけどその時変数に入ってるものを指してるだけです。
    # 変数に型が結びついていないので、以下のように1変数に様々な型をいれることができます。
    # ただし、変数名だけで行が終わると値が入ってないのに参照されたと例外が出るので、その点には注意。

    # またPythonの変数は最初の1文字が英字かアンダーバーでなければいけません。
    # それとPythonは定数をサポートしてません(なんで？)。そのため全て大文字＋_の組み合わせを定数として扱うようです。
    # ※別に定数はサポートして良いと個人的には思うのだけど

    num = 1234          # 整数(int。以前はintより大きな整数としてlongがあったようだけど、今はintに統合されたそうだ)
    num = 0b11000100    # 2進数(0bで始まる)
    num = 0o777         # 8進数(0o(数字の0+英小文字のo)で始まる)
    num = 0xffff        # 16進数(0xで始まる)

    num = 1.234         # 小数(float)
    num = 1.2e3         # 指数表記の小数
    num = 1.2E-3        # 同じく指数表記の小数

    num = 3.14j         # 虚数(complex. jかJを末尾に付加)

    num = True          # 論理値(bool. Trueは真)
    num = False         # こっちは偽

    bytes = b'1f002'    # バイト列(bかBを先頭に付加)

    str = "あいうえお"    # 文字列('か"で囲ったもの)
    str = r"aaa\nbbb"   # rかRが先頭に付いたらエスケープシーケンスを無視する


def calculate_numeric():
    """演算と代入

    引数:
    なし
    """
    x = +10 # +は付けなくてもいいけど正の値ってこと
    y = -2  # -付けたら負数
    y = 3

    # 代数演算子(+, -, *, /, %, **, //)
    z = x + y       # 足し算
    z = x - y       # 引き算
    z = x * y       # 掛け算
    z = x / y       # 割り算(ただし、結果は小数(float)となる。Cとかみたいに切り捨て割り算で整数になるのとは違う)
                    # 実はpython2では他の言語と同じで切り捨ての動作だったけど、Python3で変わった。
    z = x % y       # xをyで割った余り
    z = x ** y      # xのy剰
    z = x // y      # 切り捨て割り算(結果は整数。他の言語でいうところの割り算)

    # ビット演算子
    bytes = 0b11110000
    cal = ~bytes        # ビット反転(これ単体では多分使わない。&との組み合わせになる)
                        # Pythonの場合、上位に無限に0が詰まっているとして反転させ負数になるので、単体では多分使わない。
                        # 負数になるだけでなく＋１される。つまり2の補数なので ~n = -(n + 1)となる。
    cal = bytes & 0xC0  # AND演算
    cal = bytes & ~0b01110000
    cal = bytes | 0x0C  # OR演算
    cal = bytes ^ 0x1F  # XOR演算
    cal = bytes << 4    # 左シフト
    cal = bytes >> 4    # 右シフト(論理右シフト。算術は？知らないにょー)

    # 代入演算子(=, +=, -=, *=, /=, %=, **=, //=, &=, |=, ^=, <<=, >>=)
    # ++と--はなし。=は代入だけど今まで何も言わずに使ってるから無視
    x += y          # x = x + yと同じ
    x -= y          # x = x - yと同じ
    x *= y          # x = x * yと同じ
    x /= y          # x = x / yと同じ
    x %= y          # x = x % yと同じ
    x **= y         # x = x ** yと同じ
    x //= y         # x = x // yと同じ
    x = 10          # float(/の所でfloatになってる)とintの&=はサポートされてないので代入)
    x &= y          # x = x & yと同じ
    x |= y          # x = x | yと同じ
    x ^= y          # x = x ^ yと同じ
    x = 10          # ^=で0になっていて面白くないので再代入
    x <<= y         # x = x << yと同じ
    x >>= y         # x = x >> yと同じ


def compare():
    """比較演算

    引数:
    なし
    """
    a = 10
    b = 5
    '''
    比較演算の結果はboolで示される。なので、画面に出力してみた。
    printで画面にだす。後で文字列で遊ぶ時に利用するのでここで紹介
    '''
    print(a == b)       # aがbと等しい
    print(a != b)       # aがbと異なる
    print(a < b)        # aがbよりも小さい
    print(a > b)        # aがbよりも大きい
    print(a <= b)       # aがb以下である
    print(a >= b)       # aがb以上である

    """
    if使いたいのでifを紹介。こんな書式
    if 条件:
        処理(処理は何行あってもいいが必ずインデントすること)
    elif 条件:  #elifはelse ifのこと
        処理
    else:
        処理
    ifは、False、0や0.0、空文字("")、空リスト([])、空タプル(())、空辞書({})などを偽扱い、それ以外を真としているらしい。

    それと他の言語だと3項演算子とか呼ばれるものもある。
    (変数) = (条件がTrueのときの値) if (条件) else (条件がFalseのときの値)
    ってな書式。ま、あんま使わないけど
    """
    if "a" in "abc":    # inは右側に含まれていれば真(文字列の場合。辞書などものによっては少し意味が違う)
        print("in")
    if "d" not in "abc":# not inは右側に含まれてなければ真(文字列の場合。辞書などものによっては少し意味が違う)
        print("not in")
    # ==はオブジェクト同士が等価(同じ値かどうか)であるかを判定する。
    # 対象オブジェクトにより等価の意味が若干違う。
    # == は __eq__の実装により比較され、オーバーロードされていない場合、objectの実装(オブジェクトのIDを比較)に基づく。
    if "abc" == "abc":
        print("文字==比較でOK")
    # 各オブジェクトはid関数で取得できるユニークなIDを持つ。isはそのIDが同一かを判定する。
    if 10 is 10:
        print("isはidが同じってこと")
    if 10 is not 11:
        print("is notはidが違うってこと")
    # None(何もない状態を指すオブジェクト)はisで比較するべし。

    # ブール演算
    print(True and False)
    print(True or False)
    print(not True)


def string_etc():
    """文字列色々

    引数:
    なし
    """
    print("Hello" "world!") # 文字の連結
    print("Hello"+"world!") # こっちでも連結できる
    print("Hello" * 3)      # 文字を繰り返す

    str = "abcdefg"
    # 記載しておいてなんだが下の操作より文字列関数使う方が多いよね
    print(str[1])           # 0オリジンで文字列の[n]番目の文字を取り出す
    #str[1] = "b"           # C系の言語で出来るこの操作はエラー
    print(str[-1])          # -だと後ろからの指定
    print(str[0:3])         # 取り出し開始位置(0オリジン):指定位置-1までの文字を取り出す
    print(str[2:])          # 取り出し開始位置(0オリジン)から最後まで取り出す
    print(str[:4])          # 先頭から指定位置-1までの文字列を取り出す
    print(str[0:5:2])       # 0から5-1までを1つ飛ばしで取り出す

    # 文字列関数。必要に応じて調べるだろうから良く使いそうなのだけ
    print(str.upper())      # 全部大文字。当然lowerもある
    print(str.strip("a"))   # 指定文字を削除。破壊的メソッドじゃないようで、str自体に手を加えない
    print(str.find("c"))    # 指定文字探し。あったら開始位置のindex。なかったら-1

    # 文字列フォーマット指定(3つある)
    print("%s (%d)" % (str, 123))   # C言語のsprintfっぽいの
    print("{0} {1} {0}".format("Bunya", "Hoge"))    # C#の奴っぽいの
    print("{name0} {name1} {name0}".format(name0="Bunya", name1="Hoge"))    # C#の最近っぽいの


def like_array():
    """リストについて

    引数:
    なし
    """

    # リスト。なんでもあり可変長配列かなぁ？
    a = [10, 20, 30]    # [...]がリスト
    colors = [
        "red",
        "green",
        "blue",
    ]
    a = [10, "ABC"]     # 異なる型を1リストに混在も無問題。
    for elem in a:      # 一個ずつ取り出す時はforで。
        print(elem)
    # 文字列で説明した用法で取り出すことも可能。
    a = [11.2, 11.3, "11.4"]
    print(a[1:])

    # リストの結合
    print([1, 2, 3] + [4, 5])
    # リストの長さ。len()を使う
    print(len([1, 2, 3]))

    # リストのリストも作れる
    # 取り出す時は2段階のループ
    a = [[1, 2, 3], ["ABC", "DEF"], [4, "END"]]
    for list in a:
        for elem in list:
            print(elem)

    # リストへの追加とか色々
    array = [1, 4, 3, 2, 8]
    print(max(array))   # 最大
    print(min(array))   # 最小
    array.append(9)     # 追加
    print(array)
    array.sort()        # 並び替え
    print(array)
    array.reverse()     # ひっくり返し
    print(array)
    array.remove(3)     # 削除
    print(array)

    # 番外編。ラムダは後でかきまーす
    a2 = [
        [1, 7, "ABC"],
        [2, 8, "AAA"],
        [3, 9, "BBC"],
    ]
    print(sorted(a2, key=lambda x:x[2]))


def tupler():
    """タプルについて

    引数:
    なし
    """

    # タプルはリストと違って書き換えできません。
    # 固定配列みたいなものです。
    # この後の辞書のキーに利用できるので、そこ以外は全部リストの方が良い気がする。
    a = (10, 20, 30)    # (...)がタプル。要素が1つだけの時はa = (10,)って書く。

    a1 = [10, 20, 30]
    a2 = (10, 20, 30)
    a1[1] = 60
    #a2[1] = 60 書き換えようとするとエラーになる。

    # list()とtuple()で相互に変換可能。
    # ただし、list()＆tuple()は元変数の型は変更せず、新しいオブジェクトを返す(=非破壊メソッド)。
    at1 = tuple(a1)
    print(type(at1))
    al2 = list(a2)
    print(type(al2))    
    # あとはリストと同じ


def dicter():
    """辞書について

    引数:
    なし
    """

    # C#の辞書と同じですわ
    dict1 = {"key1":"岡山", "key2":"倉敷", "key3":"笠岡"}   # {}が辞書。key:valueですたい
    print(dict1["key1"])    # キーを指定すると値が取り出せます
    #del dict1["key3"]      # delで要素を削除できます

    # 辞書の値の取り出し方
    # items(), keys(), values()を使う
    for key, value in dict1.items():
        print(key, value)
    for key in dict1.keys():
        print(key)
    for value in dict1.values():
        print(value)


if __name__ == "__main__":
    sample1_base()
