'''
一週間でPython3プログラムいじれるぜ！講座？ 4日目
クラス
'''

def sample4_base():
    """講座4日目で使う関数を呼び出す母体

    引数:
    なし
    """
    class_sample1()
    class_sample2()
    class_sample3()
    class_sample4()
    class_sample5()
    class_sample6()


def class_sample1():
    """クラスの説明用 その1

    引数:
    なし
    """

    # とりあえずクラスを定義
    # Python2まではobjectを継承するかどうかにより、出来ることが違っていたようです。
    # Python3はどんな書き方をしても、Python2でobjectを継承したのと同じになります。
    class Person:
        """シンプル？なクラス"""

        def __init__(self, name, age):      # コンストラクタ
            self.name, self.age = name, age

    # でインスタンスを作成と
    bun = Person("Bunya", 38)
    print(bun.name)

    # クラス変数とインスタンス変数
    # インスタンス変数はインスタンス.変数名でアクセスするやつでインスタンスごとに独立した変数。
    # コンストラクタで初期化しとくといい
    #
    # クラス変数はクラス名.変数名でアクセスする奴で全インスタンス共通の変数。
    class Sample1:
        """クラス変数とインスタンス変数について"""

        class_var = 2               # クラス変数

        def __init__(self):
            self.name = "Sample"    # インスタンス変数(コンストラクタで書くのが一般的らしい)

    print(Sample1.class_var)
    sam1 = Sample1()
    print(sam1.name)

    # ただし、クラス、インスタンスの両変数はいくらでも動的に追加できちゃうことに注意。
    # 良い点もあるが悪い点(保守性悪い)もある
    sam1.age = 11
    Sample1.class_num = 1
    print(sam1.age)
    print(Sample1.class_num)

    # もし、インスタンス変数(なんか属性だ、アトリビュートだと色々言い方があるようだが)を
    # 追加するのを制限したいならスロットってのを使う
    class Sample2():
        """スロットサンプル"""

        __slots__ = ["color", "value"]  # ここに書いたの以外追加できない
        def __init__(self):
            self.color = "green"
            self.value = 10

    sam2 = Sample2()
    print(sam2.color)
    # sam2.blue = "blue" 怒られる
    Sample2.colors = "red"  # でも、クラス変数の追加は制限できない。。。

    # もしクラスにインスタンス変数が1つもないのに、インスタンス名.変数名とすると
    # クラス変数を参照に行くことに注意。

    # 属性確認はdir()でOK
    print(dir(sam2))


def class_sample2():
    """クラスの説明用 その2

    引数:
    なし
    """

    # クラス内の関数はメソッドと言います
    # で、メソッドの第1引数を必ずselfにします。selfはインスタンス自身のこと
    # C++の呼び出しを明示化してるもんですね
    class Sample3():
        """メソッド"""
        def __init__(self, x):
            self.__x = x
        def f(self):
            print(self.__x)

    a = Sample3(10)
    a.f()           # この2つは等価
    Sample3.f(a)    #
    # どうも変数名はselfじゃなくてもいいらしい。が、多分そんなことしたら総スカン食らうので、
    # 大人しくselfにしましょう。

    # pythonのクラスでは、privateだprotectedだというスコープを制御するものはありません。全部publicです。
    # また、メソッドといいますが、これもpublicです。
    #
    # なので_一つを先頭に置いた変数、関数は外から参照しないっていう慣習があり、また、_二つを先頭に置いた場合は
    # 直接参照できなくなります。
    class Sample4():
        """アクセス制御例"""

        def __init__(self):
            self.name = "1"
            self._name = "2"
            self.__name = "3"

        def hello(self):
            print("hello")
        def _hello(self):
            print("_hello")
        def __hello(self):
            print("__hello")

    sam4 = Sample4()
    print(sam4.name)    # 参照できる
    print(sam4._name)   # 参照するなっていうルールなだけで怒られない
    #print(sam4.__name) # 参照できない

    # 上と同じ
    sam4.hello()
    sam4._hello()
    #sam4.__hello()

    # でも実は_クラス名__変数名またはメソッド名とすると参照出来てしまいます
    # なので、過信しないように(でも、変な書き方するから普通は気づきそうだけど)
    print(sam4._Sample4__name)
    sam4._Sample4__hello()


def class_sample3():
    """クラスの説明用 その3

    引数:
    なし
    """

    # C#のプロパティみたいなのもある。
    # スタイルが2流派あるみたいだ。ちょっとLL系言語に慣れてない人でも読みやすい方
    # を紹介しておこう(古い方法らしいけど)。でも多数は、デコレーターを使う方で書かれている
    class Sample5:
        """プロパティ説明用。プロパティ関数を使います"""

        def __init__(self):
            # 内部で使うのはプロパティ名nameとは違う名前にしないとループする
            self.__name = ""

        def get_name(self):         # ゲッター
            return self.__name

        def set_name(self, name):   # セッター
            self.__name = name

        def del_name(self):         # デリーター
            del self.__name

        name = property(get_name, set_name, del_name, "プロパティの説明用")

    sam5 = Sample5()
    sam5.name = "sam5"
    print(sam5.name)
    del sam5.name   # 変数をdelしたときに呼ばれるのばデリーター

    # デコレーターの方も書いてみるか。
    # @の後がゲッターで書いた変数名？っていうのが落とし穴かも
    # 古い書き方の方が分かりやすいと思うのは気のせいだろうか。。。。
    class Sample6:
        """プロパティ説明用2。デコレーターを使います"""

        def __init__(self):
            self.__name = ""

        @property
        def name(self):         # ゲッター
            return self.__name

        @name.setter
        def name(self, name):   # セッター
            self.__name = name

        @name.deleter
        def name(self):         # デリーター
            del self.__name

    sam6 = Sample6()
    sam6.name = "sam6"
    print(sam6.name)
    del sam6.name


def class_sample4():
    """クラスの説明用 その4

    引数:
    なし
    """

    # デストラクタと文字列化を書いておく
    class Sample7:
        """デストラクタと文字列化"""

        def __init__(self):
            pass

        def __del__(self):  # デストラクタ。あんま使うことないかなぁ
            print("del")

        def __str__(self):  # 文字列化。直接print()で呼ばれた時にWho are you?に答える
            return "I'm Sample"

        # __enter__(),__exit__()はwith使うので用意
        def __enter__(self):
            """with()に入った時呼ばれる
            """
            print("入った")
            return self
        def __exit__(self, exc_type, exc_value, traceback):
            """
            with()から抜けるとき呼ばれる。

            with内で例外が発生した時は、exc_type, exc_value, tracebackに値が入る。
            例外がなかったら全部の変数はNoneに設定される。

            このメソッドがTrueを返すと例外を握りつぶし、Falseを返すと例外を伝搬する。
            """
            print(exc_type)
            print(exc_value)
            print(traceback)
            return False

    sam7 = Sample7()    # コンストラクタが呼ばれる
    print(sam7)         # __str__()が呼ばれる
    del sam7            # 正式には分からんが、delした瞬間にデストラクタは呼ばれない
    with Sample7() as sam77:
        print(sam77)    
    # withのスコープが終了した瞬間にデストラクタは呼ばれない。(ステップ実行を見る限り)
    # でもwithの終わりに__exit__()は呼ばれる。
    # デストラクタは下手をするとプログラム終了を基準にしてる感じがあるので、
    # すぐ解放する必要があるのは__exit__()に書いて、デストラクタは無視するで良いのでは？
    # すぐ解放する必要があるのにwith使わない人はほっておいてだな・・・、
    # C++のRAIIみたいに確実にデストラクタ呼び出した方が分かりやすいのにねぇ。。。
    # なんで後継言語はことごとくC++の悪いところじゃなくて良い所は引き継がないのかと。。。
    # GCでもメモリ不足でcrashなんて普通に出来るのにねぇ・・・


def class_sample5():
    """クラスの説明用 その5

    引数:
    なし
    """

    # ほいじゃ、まぁ継承にでも入ります。簡単ですけど
    # あ、Pythonのclassは全部objectクラスから派生してます＆Jave人間に嫌われる？
    # (デフォルト実装はいったんだから、んなこたぁねぇだろ)
    # 多重継承ありまっせ。
    # 逆にあれがありませんけどねぇ。
    # 面倒なのでコメント省き気味で行きます。

    class Sample8:
        def __init__(self):
            pass

        def print_8(self):
            print("Sample8")

    class Sample9(Sample8):     # はい、継承
        def __init__(self):
            pass

        def print_9(self):
            super(Sample9, self).print_8()  # ほい、親クラスを呼び出すと
            print("Sample9")

        def print_8(self):
            print("オーバーライドしたったぜ")   # Sample8のprint_8()を上書き

    sam8 = Sample8()
    sam8.print_8()

    sam9 = Sample9()
    sam9.print_9()
    sam9.print_8()  # 上書きした方を呼び出すと

    # ちなみに言っときますが、virtualとかabstructないので全部オーバーライドしかありません。
    # コンテナには好き勝手に色々な型が突っ込めるので、必要なかったのかもしれません。
    # なので、多分C#, C++, Javaに凝り固まった人は面食らうと思います。
    # とりあえずオーバーライドするのがPythonにおけるポリモーフィズムだと思っとけば良いです。
    # ま、この辺は言語の文化だからね

    # あ、あと多重継承できるんですが
    #class Sample10(Sample8, Sample9):  # こんな感じで並べるだけ
    #   pass

    # 継承したメソッドを呼び出す順番は左から右です。
    # だから、同じメソッドがあった場合、左側が優先して呼び出されます(Javaのデフォルト実装と同じかな)

    # 組み込み型を継承することも出来ます
    class StrDict(dict):    # 辞書クラスを継承
        # 書き換えるのだけオーバーライドするわ
        def __setitem__(self, key, value):
            if not isinstance(key, str):
                raise ValueError("keyは文字列じゃないといけません")
            super().__setitem__(key, value)

    dict1 = StrDict()
    dict1["red"] = "0xFF0000"
    print(dict1["red"])

    # 左側のインスタンスが右側のクラスか派生クラスかを調べる時は、isinstance()
    print(isinstance(sam9, Sample8))    # True
    print(isinstance(sam9, int))        # False
    # 左側のクラスが右側のクラスのサブクラスかを調べる時は、issubclass
    print(issubclass(Sample9, Sample8)) # True


def class_sample6():
    """クラスの説明用 その6

    引数:
    なし
    """

    # 残り物です。オーバーライドするための特殊メソッドをつらつらと。
    # 組み込みクラスを継承した時に使うもんです。
    # 必要な時にでもみれば？以下のようにいっぱいあるのですが、必要になったら調べてね
    #__add__(self, obj)         # +  (self + obj)
    #__iadd__(self, obj)        # *= (self + obj)
    #__sub__(self, obj)         # -  (self + obj)
    #__mul__(self, obj)         # *  (self + obj)
    #__truediv__(self, obj)     # /  (self + obj)
    #__floordiv__(self, obj)    # // (self + obj)


if __name__ == "__main__":
    sample4_base()
