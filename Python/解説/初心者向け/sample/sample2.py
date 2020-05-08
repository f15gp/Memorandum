'''
一週間でPython3プログラムいじれるぜ！講座？ 2日目
制御、例外処理、withとかその辺、関数、グローバル変数
'''

# 例外で使用するので以下をインポート
import traceback
import sys
import inspect
import os

def sample2_base():
    """講座2日目で使う関数を呼び出す母体

    引数:
    なし
    """
    control_method()
    exception_sample()
    with_etc()
    func_()
    global_var()


def control_method():
    """ifとかforとかそういうの

    引数:
    なし
    """

    # if(前に説明したから複数条件を)
    MAX_VALUE = 10
    MIN_VALUE = 3
    if MIN_VALUE <= 5 <= MAX_VALUE:
        print("複数条件は並べて書く")

    # 条件演算は直感的じゃないね
    z = 10 if "a" in "abc" else 15  # 条件成立なのでz=10
    z = 10 if "x" in "abc" else 15  # 条件不成立なのでz=15

    # whileとelse
    # 条件が成立してる間はループする。elseがあったらループ後に実行される
    # do-whileはない
    n = 0
    while n < 10:
        print(n)
        n += 1
    else:
        print("終了")

    # forとelse
    # elseはwhileと同じ。forはイテレータ的かつ全部舐めていく用途じゃないかなぁ
    for n in (1, 2, 3, "abc"):  # for 取り出した値を格納する変数 in コンテナ:
        print(n)
    else:
        print("終了")
    # 決まった回数だけ回したい時はrange使えばいい
    LOOP = 12
    for n in range(LOOP):
        print(n)

    # breakとcontinueは他の言語と同じ。
    # 最も内側のループから抜ける、先頭に戻る

    # あ、そうそうswitch-caseもない


def exception_sample():
    """例外

    引数:
    なし
    """ 
    str = "ABC"
    try:
        c = str[5]  # ない場所にアクセスしてIndexError例外を発生させる
    except IndexError:
        print("例外キャッチ")
    else:
        print("例外が発生しなかったらここにくる")
    finally:
        print("常に最後に実行される")

    try:
        try:
            raise Exception("エラー")   # raiseで例外を発生させる
        except Exception as e:
            print("type:{0}".format(type(e)))
            print("args:{0}".format(e.args))
            print("{0}".format(e))
            raise   # 再度例外を発生。直近に発生した例外を再度発生。例外がなかったらTypeError例外になる
        except (KeyError, FileNotFoundError) as e:
            print("ここはこないけど、こうやって複数の例外を指定することもできる")
    except: # 全て捕捉できる。あまり使うならしい
        # as eの付け方が分からないので他の方法を使う
        traceback.print_exc()   # スタック情報を表示
        print(sys.exc_info())   # 処理中の例外を表示

    # 後で説明するクラスを使って独自例外を作ることも可能
    # 内部関数(複数戻り値)、内部クラスとか勝手に使ってますけど、後で書きます。今は無視で
    class MyExceptionError(Exception):
        def __init__(self, file, func, lineno):
            self.file = file
            self.func = func
            self.lineno = lineno

    def location():
        frame = inspect.currentframe().f_back
        return os.path.basename(frame.f_code.co_filename), frame.f_code.co_name, frame.f_lineno

    try:
        file, func, line = location()
        raise MyExceptionError(file, func, line)
    except MyExceptionError as e:
        print(e.file)
        print(e.func)
        print(e.lineno)


def with_etc():
    """withとかそういうの

    引数:
    なし
    """

    # withブロックが終了したらオブジェクトの終了処理が呼ばれる
    # C#のusingなんとかと同じ
    try:
        with open("test.txt") as file:
            print(file.read())
    except FileNotFoundError as e:
        print(e.args)
    except UnicodeDecodeError as e:
        print(e.args)
    finally:
        print("読み込み完了")

    # assertは省略

    # passは関数やクラスの中身がないと指定します。ユニットテストとかで使う以外は
    # ダックタイピングで使うんだろうねぇ
    def my_func():
        pass

    my_func()

    # delとするとオブジェクトが削除されます
    x = 5
    del x

    # execってのがあるらしい
    # 引数の文字列をPythonのスクリプトとして実行するらしいが
    # 最小行のコードを競う大会とかでしか使うことない気がするのでパス


def func_():
    """
    やっと関数の説明。あ、今まで説明してなかったけど、
    関数の先頭に書いてるこれはdocstringっていうものらしい。関数コメントみたいなもんかな
    これを書いておくと呼び出し側の関数にマウスかざしたり、インテリセンスが動いた時に見えるよ.
    色々試したら複数行書いた場合、このインデントの方がインテリセンスは見やすい。
    なんかこのdocstringは標準の書き方がないっぽいので、以後複数行はインテリセンスで見やすいこの形にします

    引数:
    なし
    """

    # 基本的なことは最初に書いたし、バンバン使ってるので今更感が強いのだが。。。

    # あ、Pythonは関数内部に関数かけまっせ。内部に書くと外部からは参照できません
    def internal_func():
        pass
    internal_func() # 内部同士なら普通に見れる

    # キーワード付き引数とデフォルト値
    def repeat_word(msg="Bunya", repeat=3):
        """キーワード付き引数とデフォルト値の説明用

        引数:
        msg -- 表示させる文字列(default "Bunya")
        repeat -- 繰り返し表示させる回数(default 3)
        """
        for i in range(repeat):
            print(msg)

    # このように引数名を指定するので順番が違っていても良い。今回の関数はどちらも
    # デフォルト値を与えているので不要なら与えなくて良い
    repeat_word(repeat=4,msg="hello")

    # 複数の戻り値があるならreturnで,区切りで書いちゃいな。
    # return (a, b) or return a, b でOK
    def multiple_return():
        """複数戻り値の例

        引数:
        なし
        """
        return 1, 2, "str"

    # 標準だとタプルで返してくるが()を[]に変えてリストにすることもできる。
    # 数が増えるとNamed tupleとかを使うことを検討した方がいい
    result = multiple_return()
    print(result[2])
    multi1, multi2, multi3 = multiple_return()  # アンパックして別々の変数に入れるのも可能
    print(multi3)

    # 可変引数？
    def variable_args(a1, *args, **params):
        """可変引数？の例

        引数:
        a1 -- ただ何かを渡す
        args -- a1以降の引数(タプルで受け取る)
        params -- キーワード付き引数を辞書で受け取る
        """

        print(a1)
        print(type(args))
        print(args)
        print(type(params))
        print(params)

    variable_args("a", 123, 4, b1="b1", b2="b2")
    # 変数使って渡すならこう
    args = (14, 32)
    params = {"c1":"c1", "c2":"c2"}
    variable_args("b", *args, **params) # この場合渡す側でも*や**が必要

    # 引数の値渡し、参照渡しについて
    # 全部参照渡し。だけど変更可能(mutable)な型のみ書き換え可能。
    # 変更不可(immutable)な型： int, float, str, タプル, bytes, frozensetなど
    # 変更可能(mutable)な型： リスト, 辞書, set, bytearrayなど
    #
    # 変更可能な型で別のオブジェクト用意して利用したいなぁって場合はimport copy + copy.deepcopy()を使えばいいみたい
    #
    # ちなみにデフォルト引数は、関数やクラスが作成された時に一度だけ作成されるもののようなので
    # immutableな型を指定するのを推奨だそうです


# グローバル変数の説明用に
global_count1 = 11
global_count2 = 15

def global_var():
    """グローバル変数とやらを

    引数:
    なし
    """

    # 関数の外で宣言された変数はグローバル変数として扱われます
    print(global_count1)    # こんな感じで参照できる
    # ただし、もしこのグローバル変数に値を入れたくなったら！
    # globalと宣言する必要があります
    #global_count1 = 12 # ここで怒られます。なんせグローバル変数に代入してますから
    #print(global_count1)

    # それでglobalですが、一つ注意が。
    # 参照とかしてるのが先にあるとローカル変数として扱われるので、
    # global宣言できません。使うなら関数の先頭に置いた方が無難だろう
    global global_count2
    global_count2 = 12
    print(global_count2)


if __name__ == "__main__":
    sample2_base()
