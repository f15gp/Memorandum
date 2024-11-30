/**
 * Javaの勉強 3日目(クラス)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test1;

/**
 * @Deprecatedの説明用
 * 
 */
@Deprecated
class SubA {

    /**
     * 引数で与えられた数を2倍にして返すメソッド
     * 
     * @param x 計算に使用する値
     */ 
    public int Double(int x) {
        return (x * 2);
    }
}

/**
 * フィールドとかの説明用
 * 
 */
class SubB {
    /*
    * フィールド変数
    * クラスに固有の情報を扱う変数になります。
    *
    * [書式]
    * アクセス修飾 static フィールド修飾子 型 フィールド名;
    *
    * (アクセス修飾)
    * 未指定: このクラス内と同じパッケージ内のクラスから使用出来る。
    * private: このクラス内でのみ使用出来る。
    * protected: このクラス内とサブクラス、そして同じパッケージ内のクラスから使用出来る。
    * public: どのクラスからも使用出来る。
    * まぁメソッドと同じですね。private以外はパッケージが関係してくることに注意。
    *
    * (static) ※クラス同様、フィールド修飾子の一部だけどstatic finalって順番で書かれることも多いし説明のしやすさで別項目にした。
    * つければクラスフィールド(またはstaticフィールド)、つけなければインスタンスフィールドとなる。
    * クラスフィールドの場合、このクラスの全てのインスタンス(=newで作成した)で共有されるデータ。
    * インスタンスフィールドは、インスタンスごとに別のデータになります。
    * まぁ滅多なことでクラスフィールドを用意する必要はないはず。
    *
    * (フィールド修飾子)
    * final: 
    * 
    * 一度初期化したら変更不能なデータになります。
    * まぁ使う用途としては定数とかじゃないですかね。
    *
    * フィールドは何もしなくても型ごとに決まっているデフォルト値で初期化されます。
    * そのため、Javaではデフォルト値で初期化するのは多分大抵の静的解析ツールで怒られます。
    * 
    * transient: このフィールドはシリアライズ対象外となる。
    * volatile: フィールドは常にメモリから読まれ(=キャッシュしない)、スレッド間での同期が保証される。マルチスレッドで重要。
    */
    // 変数名の後に=でその値で初期化されます。ただ、これ1.0から可能だったのか、後のバージョンで出来るようになったのか
    // 不明です。
    private int x = 1;
    private static int y = 2;
    private int z = initMethod();

    /**
     * コンストラクタ
     * コンストラクタを定義しない場合は自動的にこの引数のないコンストラクタが用意されます。
     * それをデフォルトコンストラクタとか呼んでます。
     * コンストラクタが呼ばれるのはnewした時です。
     * 
     */ 
    SubB() {
        x = 3;
        System.out.println("SubB コンストラクタ");
    }
    /**
     * 引数付きコンストラクタ
     * 
     * @param a フィールドxを初期化する値
     */ 
    SubB(int a) {
        x = a;
    }

    /**
     * フィールドzの初期化に使用するメソッド
     * 
     * 戻り値をフィールドに代入してるメソッドはコンストラクタより先に呼び出されます。
     * というより、フィールドの初期化式がコンストラクタより優先されて呼び出されてるだけじゃないかと。
     * 
     * @return 4
     */ 
    int initMethod() {
        System.out.println("SubB initMethod");
        return 4;
    }

    private String s;
    // {}が初期化ブロックです。
    // 
    {
        s = "はじめまして";
        System.out.println(s);
    }

    // メソッド引数のfinalについて説明を加える
}

public record Sub(String name, int age){
}

/*
interface InterfaceSubA {
    int Double(int x);
}

class SubC implements InterfaceSubA {

    //@Override
    public int Double(int x) {
        return (x * 2);
    }
}

class SubA2 extends SubA {
    @Override
    public long Double(long x) {
        return (x * 3);
    }
}
*/

