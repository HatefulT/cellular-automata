# Cellular automata experiments
This is a bunch of programs witch can create bmp picture of cellular automata evolution.

## Compilation and running
```
git clone https://github.com/HatefulT/cellular-automata.git
cd cellular-automata
cd discrete-N2-1d # for example
make
```

## discrete-N2-1d
An one dimensional (1d) cellular automata with 2 cell states (black and white) (N2)

### discrete-N2-1d/test
This folder contains `script.sh` which can generate all discrete-N2-1d possibilities.
To run:
```
cd discrete-N2-1d
make build/main.out
cd test
mkdir outputs
./script.sh
```

## continious-1d
An one dimensional (1d) cellular automata, cell states can be represented as numbers from [0, 1] (continious)
