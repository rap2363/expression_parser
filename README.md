# Expression Parser

Takes an input file with the following format:
```sh
x = 3
y = x + z
z = 1
```
Evaluates and solves for all variables:

```sh
x = 3
y = 4
z = 1
```

Currently only supports addition and no operator precedence.