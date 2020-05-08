'''
一週間でPython3プログラムいじれるぜ！講座？ 3日目
関数周りの落ち葉拾い、リストとか再び
'''

import functools    # デコレーター, 高階関数で使う

def sample3_base():
    """講座3日目で使う関数を呼び出す母体

    引数:
    なし
    """
    around_function()
    list_etc()
    

def around_function():
    """関数周りについての残り物

    引数:
    なし
    """

    # ラムダ(lambda)
    # Pythonのコーディング規約 PEP8では変数にラムダ入れるなとあるそうな。
    # で、関数内関数が出来るからsorted()のkeyとかラムダ使って簡潔になるとき
    # 以外は使うなという感じに見える。要はPythonはC#と違ってラムダが嫌いみたい
    #
    # 書式は lambda 引数: 処理内容(returnはダメ。でも処理した結果はreturnされる)
    #
    # ラムダが主に使われるのはこの後述べる関数の引数に関数を渡す時と思っとけばOK
    sample = lambda str: str + " lambda"
    print(sample("Hello,"))

    # イテレータ
    # あんま関数周りじゃないけど、ジェネレータとかの説明にいるかなぁと
    # イテレータオブジェクトは、__iter__()で__next__()メソッドを持つオブジェクトを返却。
    # __next__()メソッドは次の要素を返却し、最後に達するとStopIteration例外を出すようにする。
    #
    # ちなみにpython 2系では__next__()はnext()だったそうで、今でもネットのサンプルにいっぱいある。
    # でも、Python3じゃnext()じゃ動かなくて怒られますんで
    class MyIterator(object):
        def __init__(self, *numbers):
            self._numbers = numbers
            self._index = 0

        def __iter__(self):
            return self

        def __next__(self):
            if self._index == len(self._numbers):
                raise StopIteration

            value = self._numbers[self._index]
            self._index += 1
            return value

    iterator = MyIterator(10, 20, 30)
    for n in iterator:
        print(n)

    # ジェネレータ(yield)
    # C# の奴と同じかなぁ。yieldは、イテレータオブジェクトを返すジェネレータを定義する時に使います。
    # いわゆる遅延評価って奴です。
    # 参照されるたびに計算を行うのでメモリや処理効率が改善されるみたい
    def func(list):
        """yieldにより呼び出されるたびに2倍した値を返す

        引数:
        list -- 計算対象のリスト
        """
        for n in list:
            yield n * 2

    for n in func([1, 2, 3, 4, 5]):
        print(n)

    # デコレーター(関数を修飾するんだと)
    # 色々な書き方があるらしいが、要は既存関数に機能を簡単に追加させるためのものでしょうかね。
    # 時間を測るデコレーターを一つ用意して、色々な関数の処理時間を計れるようにするみたいな。
    # それとも名前の通り、元々はDecoratorパターンのために入れたのだろうか？
    def decolater(func):                # デコレーター関数。funcはデコレートされる関数
        @functools.wraps(func)          # お約束
        def wrapper(*args, **kwargs):   # 実際の中身を書く関数
            print("--start--")
            func(*args, **kwargs)       # デコレートした関数はここで実行。つまり前後にprintを加えるデコレーション
            print("--end--")

        return wrapper                  # お約束

    @decolater  # decolater()って関数で次の関数をデコレートするよって意味
    def test():
        print("Hello")

    test()

def list_etc():
    """リストとか再び

    引数:
    なし
    """

    # ラムダも説明したし、リストの操作関数(高階関数。LINQに近いなぁ)でも

    # map(各要素に対して処理を行うもの)を。mapはPython2まではリストを返してたようですが、Python3ではイテレータを返すので
    # ネットのサンプルそのままでは狙った通り動かない場合(Python2を前提にしてるものもたくさんあるから)がある。
    # イテレータというよりyield使ってると思うんだけど。
    # ラムダは関数でもOKだから複雑な処理を行うなら関数渡せばいいと思う。
    # 良く内部処理は分からんが関数の場合、yieldじゃなくてreturnで良いみたい。というかreturnじゃないと怒られる
    original = [1, 2, 3, 4, 5]
    print(list(map(lambda x: x * 2, original))) # listが直接欲しい時はlist()で変換

    map1 = map(lambda x: x * 3, original)
    for n in map1:
        print(n)

    # 関数版も作っとこうか。
    # elseは重要よ。もし、なかったらNoneが入っちゃう
    def hoge(number):
        if number < 3:
            return number * 2
        elif number >= 3 and number < 5:
            return number * 3
        else:
            return number

    print(list(map(hoge, range(10))))

    # で、filterなわけですよ。
    # 多分 C# の SelectがmapでWhereがfilterなはずですが
    # こんなの
    print(list(filter(lambda x: x % 3 == 1, range(1, 10)))) # 1-10の中で3で割った余りが1と等しい数を返す

    # mapとfilterの合わせ技
    # ま、そりゃ誰だってわかると思うけど
    print(list(map(lambda x: x * 2, filter(lambda x: x % 3 == 1, range(1, 10)))))

    # で、基礎編最後のreduce.
    # C#のAggregateだろうな。Python3からはreduce()というbuilt-in関数でなくfunctoolsモジュールになったので注意。
    # 2変数を取って、その計算式を与えた演算結果を作る。こいつはイテレータじゃなく、演算結果を返す
    print(functools.reduce(lambda x, y: x + y, range(1, 11)))

    # 内包記法ってのがある。
    # 個人的にはぐちゃぐちゃ書くので嫌い(速度もmapとかfilterと比べて絶対早いってわけでもないし)、
    # ドローン同好会じゃ恐らく使わないので、業務で使う必要がある人は自分で調べてｗ

    # 後、Setという重複のないリストとかもあるけど、その辺は実践で使う際に調べるだろうから、
    # 各自調べて。そんなのが必要になる場面じゃないと、真面目に調べないだろうし


if __name__ == "__main__":
    sample3_base()
