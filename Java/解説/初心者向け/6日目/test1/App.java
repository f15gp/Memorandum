/**
 * Javaの勉強 6日目(リスナーとスレッド)
 * 
 * @version 1.0.0
 * @author Bunya
 */

package test1;

import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import java.util.*;

// リスナーとスレッドを同時に説明してみようかと思います。
// リスナーは古いものなので、もう見ることないのかも？
// で、両方を一度にとなるとGUIアプリがいいかなとか思って、
// Swingで簡単なのを書いてみたいと思います。

/**
 * アプリ クラス
 * 
 */
public final class App {

    /**
     * Mainメソッド
     * 
     * @param args 起動時に与えられたコマンドの配列
     */
    public static void main(String[] args) {
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                var frame = new ButtonFrame();
                frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                frame.setVisible(true);
            }
        });
    }

}

/**
 * フレーム(ウィンドウ)の設定を行う
 * 
 */
class ButtonFrame extends JFrame {
	/** ボタンなどを貼り付けるパネル */
	private JPanel buttonPanel;
	/** synchronizedで使う */
	private Object lock = new Object();

    /**
     * コンストラクタ
     *
     */
    public ButtonFrame() {
    	// フレームのタイトルとサイズを設定
        setTitle("Swing フレーム");
        setSize(400, 300);

        // 貼り付けるボタンを作成
        // ※ 波括弧で囲っているのは、全てボタン作成の処理であるが、
        //    コメントの説明があるため一連のまとまりとして見やすいかな？と思ってやっているだけです。
        //    別にかならず{}で囲む必要があるわけではないです。
        JButton button1;
        {
        	button1 = new JButton("押してね");
        	// Swingは、委譲イベントモデル(event delegation model)というイベント処理機構を採用していて、
            // イベントを発生させるオブジェクト(イベントソース）に対して、イベントリスナーオブジェクト(event listener)を指定します。
            // イベントリスナーオブジェクトは、リスナーインターフェイス(listener interface)を実装したオブジェクトです。
            // 具体的にリスナーインターフェイスはActionListenerというインターフェイスです。
            //
            // そして、↓がリスナー。button1が押されたときの動作を登録する。
            // ラムダ式の引数はvarでいいのだけど、ここの型知らない人ばっかりだろうから明示する。
            //button1.addActionListener((ActionEvent e) -> JOptionPane.showMessageDialog(null, "こんにちは"));
            // ↑これだとウィンドウにボタンが張り付いていて、押したら"こんにちは"を表示する。
            //
            // ↓対した意味もなくスレッドを作成してdoThread()を動かす。
            //   スレッドは、GUIだと割と頻繁に出てきて、あることをやっている間に他の処理を実行するためのものです。
            //   例えばデータの取得に時間がかかるデータを取得して表示する場合だと、
            //   スレッドを使わないとデータ取得中はウィンドウがフリーズしたような挙動になります(データ取得が終わるまで)。
            //   それだと、色々まずいのでそんな時はスレッドにデータを取得させ、全部取得できたら表示するなんてことを行います。
            button1.addActionListener((ActionEvent e) -> { new Thread(() -> doThread()).start(); });
        }

        // パネルを作成してボタンを貼り付け、それをフレームに追加
        buttonPanel = new JPanel();
        buttonPanel.add(button1);
        add(buttonPanel);
    }

    /**
     * スレッドでの動作を実装
     *
     */
	private void doThread() {
	    // ↓このsynchronizedというのは、{}で囲った区間の処理が同時に実行されないというものです。
	    //   書き方は、synchronized(ロックオブジェクト){}で、同じロックオブジェクトを利用しているsynchronizedの区間が
	    //   同時に動作しません。
	    //   スレッドは別々に動作するので、データを奪い合ったりすることがあります。
	    //   この奪い合いを防ぐために用いるものです。
		synchronized(lock) {
			// ただ、これはサンプルなので特に処理はありません。
		}
		JOptionPane.showMessageDialog(null, "こんにちは");
	}
}
