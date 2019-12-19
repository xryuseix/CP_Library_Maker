import os
os.system('python remove_index.py')
os.system('cd json_to_header; python json_to_header.py')
os.system('cd json_splitter/; python ./json_splitter.py')
os.system('cd snippet_to_tex/; g++ snippet_to_latex.cpp; ./a.out')