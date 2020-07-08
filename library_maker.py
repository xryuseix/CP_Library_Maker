import os
import datetime

# Python コマンド
os.system('python remove_index.py')
os.system('cd json_to_header; python json_to_header.py')
os.system('cd json_splitter/; python ./json_splitter.py')
os.system('cd snippet_to_tex/; g++ snippet_to_latex.cpp; ./a.out')

# git コマンド
# 現在時刻を取得
dt_now = datetime.datetime.now()

print('Input commit_message -> ', end='')
commit_message = list(input())

os.system('git add --all')
if commit_message:
    os.system('git commit -m "' + ''.join(commit_message) + '"')
else:
    os.system('git commit -m "update at ' + str(dt_now) + '"')
os.system('git push origin master')