import re

HaveIndex = 1 # snippetに目次がある場合１

s = ''
path = './storage/test.json'

if HaveIndex:
    with open(path) as f:
        s = f.read()

s = re.sub('/\*[\s\S]*?\*/', '', s)

with open(path, mode='w') as f:
    f.write(s)

print('スニペットの加工が完了しました')