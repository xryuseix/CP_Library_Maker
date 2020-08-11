[![xryuseix](https://img.shields.io/endpoint?url=https%3A%2F%2Fatcoder-badges.now.sh%2Fapi%2Fatcoder%2Fjson%2Fxryuseix)](https://atcoder.jp/users/xryuseix) [![xryuseix](https://img.shields.io/endpoint?url=https%3A%2F%2Fatcoder-badges.now.sh%2Fapi%2Fcodeforces%2Fjson%2Fxryuseix)](https://codeforces.com/profile/xryuseix)

# Competitive_Programming_Library_Maker

競技プログラミングで使用するライブラリの編集ツール群です．

## Usage

### My Library

`./storage` に入っています．

### Converter(from json_snippet)

macのVS Code標準の`~/Library/Application\ Support/Code/User/snippets/cpp.json`にご自身のスニペットを入れてください．以下のコマンドを実行すると，jsonスニペットをLaTeX(.tex),分割されたC++ファイル(.cpp),ヘッダファイル(.h)を作成することができます．

```sh
$ python library_maker.py
```

### Converter(from cpp)

cppで作ったコードをsnippetにそのまま貼れる形式のjsonに変換できます．`./cpp_to_json/input.txt` にcppコードを貼り付け，以下のコマンドを実行すると ./cpp_to_json/output.txt にjson形式のデータが書かれます．

```sh
$ cd cpp_to_json
$ python cpp_to_json.py
```

## Environment

Python 3.6.0  
Apple clang version 11.0.0 (clang-1100.0.33.12)
