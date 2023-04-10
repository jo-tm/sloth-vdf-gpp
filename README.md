# sloth-vdf-gpp
C++ implementation of Sloth

## Building

Run `make` in the terminal to compile the project.

Please note that you need to have GMP installed on your system to successfully compile this code. You can install GMP on Ubuntu/Debian systems by running:

```bash
sudo apt-get install libgmp-dev
```

For macOS users with Homebrew, you can install GMP by running:

```bash
brew install gmp
```

## Performance

Approx 400 steps per second on a Macbook Pro Intel.

```bash
$ time ./main
Generated proof: 59683856271171280934534051625134865929370914914652611635686341364939823784420013881287764346818033233200073540988372810898246604046344269099365124584192690757276581875436220947196639751663329550157211075570846342085921842865790127665184482697549172567321579004912434646488410886043153894564655315489817408450
Verification result: true

real	0m24.404s
user	0m24.218s
sys	0m0.010s
$ python
>>> 10000. / 24.4
409.8360655737705
```
