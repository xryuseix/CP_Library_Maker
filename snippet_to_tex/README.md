snippet_latex_converter
====

moved to https://github.com/xryuseix/Competitive_Programming_Library_Maker

## Overview

This program is convert from C++ user snippet to latex document.

## Usage

1. Paste your snippet on "snippet.json".

2. Change your name line 28 in "init.txt".

3. Run C++ code. (This command is example of run command.)

```zsh
g++ -std=c++1z snippet_to_latex.cpp
./a.out (or ./a.exe)
```

## Importantant Point

* Please rearrange snippet order to this order.

    1. prefix
    2. body
    3. descryption

* If you use tab in body of snippet to use "\t", not to use "space".

## Example of Snippet

```json
"lcm": {
	"prefix": "lcm",
    "body": [
        "ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a;}",
        "ll lcm(ll a, ll b) { return a / gcd(a,   b) * b;}"
    ],
    "description": "least common multiple"
},
```

## Author

[xryuseix](https://github.com/xryuseix)

