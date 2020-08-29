'''
一週間でPython3プログラムいじれるぜ！講座？ 5日目
標準ライブラリをいくつか
'''

def sample5_base():
    """講座5日目で使う関数を呼び出す母体。

    引数:
    なし
    """

    # ぶっちゃけ、長々と書きましたがPythonとかの場合、色々書くよりまずは
    # 標準ライブラリと拡張ライブラリををいかに使いこなすかの方が重要だと思います。
    # だからこそ、世界中で使われるわけで。。。
    # なんせ、Python初心者がまとめたものですしねｗ
    # ま、莫大にあるので少しだけ紹介。なのでえらく短い。

    # 日時扱おうか。
    # 良いかどうかは別にしてここから内部importを使いまくりです。
    # (何をimportすれば使えるかを書きたいだけ。近くにある方がわかりやすいっしょ？)
    import datetime

    print(datetime.date.today())    # 今日
    print(datetime.datetime.now())  # 現在の日時

    d = datetime.date(2018, 5, 2)
    print(d.year)
    print(d.month)
    print(d.day)
    print(d.weekday())
    print(d.strftime("%Y/%m/%d %H:%M:%S"))

    # 正規表現
    import re

    print(re.findall(r"[abcedf]", "abcxfy"))    # 重複してない文字列を返す。
    print(re.split(r",", "ab,cd,fg"))           # 指定した文字で分割した文字列を返す。
    print(re.sub(r"a", "b", "abced"))           # 一致する文字を入れ替える。

    for match in re.finditer(r"[a-z]+", "I'm bunya."):
        print(match.group(0), end = " ")

    # 数学系モジュール
    import math

    print(math.pi)
    print(math.sqrt(2))
    print(math.sin(60))
    print(math.cos(60))
    print(math.tan(60))

    # 乱数
    import random

    random.seed(datetime.datetime.now())
    x = random.random()         # 0 <= n <= 1の乱数を返すらしい。
    y = random.randint(1, 10)   # この指定だと 1-10の乱数を返す。
    print(x, y)

    # 非同期
    # 場合によってはスレッドではハマるのでプロセスを検討した方が良いらしい。
    # でも、昔(Python2系)のことなのかも。
    import time
    import concurrent.futures

    # じゃ、スレッドプールで。
    def func1():
        i = 0
        while i < 10:
            print("func1")
            i += 1
            time.sleep(1)

    def func2():
        i = 0
        while i < 10:
            print("func2")
            i += 1
            time.sleep(1)

    # ThreadPoolExecutorをProcessPoolExecutorに変えるとプロセスプールに。
    # そうするとGlobal Interpreter Lock(GIL)の制約をうけなくなって、マルチコアで動かせるようになるそうです。
    # が！別の制約が出てくるので、そこはお忘れなく。
    executor = concurrent.futures.ThreadPoolExecutor(max_workers=2)
    executor.submit(func1)
    executor.submit(func2)

    # C#その他と同じでasync的なのがありますな。
    # ファイルとか通信とかのIOを意図してるんだろうけど。サンプルだけ書きますわ。
    # C# のasync/await, C++のasyncが分かってるならすっとくるとおもうけど、
    # ま違いはあるんだけどねぇ。
    import asyncio

    @asyncio.coroutine
    def func3():
        i = 0
        while i < 10:
            print("func3")
            i += 1
            yield from asyncio.sleep(1)

    @asyncio.coroutine
    def func4():
        i = 0
        while i < 10:
            print("func4")
            i += 1
            yield from asyncio.sleep(1)

    loop = asyncio.get_event_loop()
    tasks = asyncio.wait([func3(), func4()])
    loop.run_until_complete(tasks)


if __name__ == "__main__":
    sample5_base()
