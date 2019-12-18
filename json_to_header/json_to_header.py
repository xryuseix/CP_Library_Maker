import json
import os
# jsonを辞書に変更
file = open('./../storage/snippet.json', 'r')
json_dict = json.load(file)
file_pass = './../storage/Header/xryuseix.h'

keys = json_dict.keys()

os.system('rm ./../storage/Header/xryuseix.h')
os.system('touch ./../storage/Header/xryuseix.h')


for k in keys:
    if k == 'template' or k == 'icpctemplate':
        continue
    with open(file_pass, mode='a') as f:
        for st in json_dict[k]['body']:
            f.write(st + '\n')
