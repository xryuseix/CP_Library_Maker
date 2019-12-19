#!/bin/sh

#ここはスニペットがあるパスに変更
#デフォルトはこれ
cp ~/Library/Application\ Support/Code/User/snippets/cpp.json ./storage
cd storage
rm snippet.json
mv cpp.json snippet.json