T319059 谷本樹希
タイトル　８パズル

説明
８パズルを遊べる。数字タイルをスライドさせて数字を順に並び替えるパズル。大きさを変えると難易度が上がる。ターン数で人と競う。

操作方法
はじめにパズルの大きさを指定する。これは後述するセーブデータをロードする場合でもこの作業は必要になる。
w a s d がそれぞれ↑ ← ↓ →に対応している。@を選んだ方向に動かすことが出来る。進行方向にあった数字タイルと@の空白タイルを交換する。
rでセーブ、lでロード、qで終了を行うことができる。セーブしたデータはバイナリーファイルとして実行した場所にsave_dataとして保存される。

注意事項
・パズルの動作確認は、n = ３、４、５で行った。それ以外の大きさでは、表示などが崩れる可能性がある。
・ロード時はsave_dataがプログラムを実行した場所にある状態でロードを行う必要がある。

データ構造
pazzle_8のデータ構造について説明する。
pazzle_8のメンバ変数は、int型のn、turn、blankと一次元のint型ベクトルのpazzle、map<char,bool>型のMovableから成る。
パズルの配置は、turnとMovable以外の変換により決まる。nはそのパズルの大きさ、blankはパズルの空きマスとして表示する数字を表していてn*nのことである。pazzleは数字の位置を保持していて、０番目からn*n番目までをパズルの左上から右下にかけて正方形に表示することでパズルになる。

プログラム
プログラムの大まかな説明をする。
pazzle_8というクラスを実装して、本プログラムを作成した。pazzle_8は、パズルの生成、操作、終了判定、表示といったパズルを遊ぶ上で必要なメソッドを備えている。そのため、メイン関数にインスタンス化すれば他のクラスを必要とせずにパズルを遊ぶことができる。pazzle_8はインスタンス化の際に、揃ったパズルを疑似乱数を使って並び替えることでパズルの生成を行っている。しかし、８パズルでは数学的に解くことの出来ないパズルがあることが知られている。数学的に解くことができる８パズルの問題では、パズルの並べ替えの置換のパリティと空きマスの正解位置への最短距離の偶奇が等しいという条件が成り立つことが知られている。isSolvable関数でこの条件を満たしているかを確認している。解くことが出来ないとわかった場合には、refinePazzle関数で解ける問題に変換している。refinePazzle関数では、空き以外のマスを２つ選びそれを交換することで解ける問題に変えている。パズルは数字が１から順にn*nまで並んでいれば解けたことになるので、順番に並んでいるかを確認する作業をisFinish関数で行っている。
パズルの操作は、空きマスとその上下左右を入れ替えることで行う。その操作はmove関数が担っている。move関数で空きマスはblankとして定義されているのでblankのイテレータをfind関数をつかって探して対象のマスと交換している。move関数の前にはその操作が現状のパズルに許された操作であるかをMovableにより確認する必要がある。またMovableは各ターンごとに確実にrenewMovableList関数を使って更新する必要がある。

参考文献
高校数学の美しい物語 8パズル，15パズルの不可能な配置と判定法 https://manabitimes.jp/math/979 アクセス日2020/08/02
	・isSolvable関数とrefinePazzle関数の設計時に参考にした。

感想
はじめは８パズルを実装した上で、木探索などの探索を行って回答も表示することができるプログラムを目指していた。講義内ので学習したalgorithmやvectorなどのSTLを使って実装すれば、容易に実装できると考えたからである。しかし、８パズルに数学的に解くことの出来ない配置が存在することを知らなかったため、isSolvable関数とrefinePazzle関数の実装に手間取った。そのため木探索まで実装することが叶わなかった。今後は下調べを入念に行い、プログラムを実装する際の工数なども考えて作業を行いたい。
