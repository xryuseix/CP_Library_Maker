import re
import os
f = open('./input.txt', 'r')
line = f.readline()

code = []
formated_code = []

while line:
    code.append(line)
    line = f.readline()
f.close()

    
for i in range(len(code)):
    match_obj = re.search(r'[^ ]', code[i])
    if i != len(code)-1:
        formated_code.append('"' + "\\t"*(int)(match_obj.start()/4) + code[i][match_obj.start():-1].replace('"', '\\"') + '",')
    else:
        formated_code.append('"' + "\\t"*(int)(match_obj.start()/4) + code[i][match_obj.start():].replace('"', '\\"') + '"')


path = './output.txt'
os.remove(path)
with open(path, mode='a') as f:
    f.write('\t"": {\n\t\t"prefix": "",\n\t\t"body": [\n')

for i in formated_code:
    with open(path, mode='a') as f:
        f.write('\t\t\t' + i + '\n')

with open(path, mode='a') as f:
    f.write('\t\t],\n\t\t"description": ""\n\t}')
		