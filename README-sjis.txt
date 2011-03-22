usggmpost.wsf

GIGERMAP用 USB-GEIGER 測定値送信ソフトウェア

[ビルド手順]

1. bcc32 をセットアップする
	参考) http://apis.jpn.ph/fswiki/wiki.cgi?page=Win32%2FCompiler%2FBcc32
	DL  ) http://update.codegear.com/forms/jp_cpp_download_reg
	インストールしたBinフォルダにパスを通す
	Binフォルダに bcc32.cfg, ilink32.cfg を設置する
2. ライブラリの準備
	Strawberry Linux のサイト
	http://strawberry-linux.com/catalog/items?code=53001
	からライブラリをダウンロードして、
	gmlib.dll を bin\usbgmpost の中に設置する
3. make でコンパイル

[設定手順]
binフォルダの中の usbgmpost.wsf をエディタで開き

id : "..."
key : "........"

を編集する

[テスト実行手順]
テストで1回だけ実行するには、USB-GEIGERを接続して usbgmpost.wsf を実行する。
コマンドラインから cscript で実行してもいい

[継続的に実行させる]
タスク で usbgmpost.wsf を1分おきに実行する用に設定する
"開始"(実行時のカレントディレクトリ) を usbgmpost.wsf があるディレクトリに設定すること

※タスク実行時に黒いウインドウが一瞬表示されるのを防ぐには
タスク実行専用アカウントを作成して、そのアカウントで実行する
binフォルダの中身をそのアカウントがアクセスできる場所に移動するのを忘れずに

