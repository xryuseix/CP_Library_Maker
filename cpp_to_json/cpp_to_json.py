import re
import os

root = __file__[:-15]
f = open(f"{root}/input.txt", "r")
line = f.readline()

codes = []
formated_codes = []

while line:
    codes.append(line)
    line = f.readline()
f.close()


for i, code in enumerate(codes):
    match_obj = re.search(r"[^ ]", code)
    if i != len(codes) - 1:
        formated_codes.append(
            '"'
            + "\\t" * (int)(match_obj.start() / 4)
            + code[match_obj.start() : -1].replace('"', '\\"')
            + '",'
        )
    else:
        formated_codes.append(
            '"'
            + "\\t" * (int)(match_obj.start() / 4)
            + code[match_obj.start() :].replace('"', '\\"')
            + '"'
        )


path = f"{root}/output.txt"
os.remove(path)
with open(path, mode="a") as f:
    f.write('\t"": {\n\t\t"prefix": "",\n\t\t"body": [\n')

for i in formated_codes:
    with open(path, mode="a") as f:
        f.write("\t\t\t" + i + "\n")

with open(path, mode="a") as f:
    f.write('\t\t],\n\t\t"description": ""\n\t}')
