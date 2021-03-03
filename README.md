# curve-fitter

curve-fitter is a small c-program that can fit datapoints in a two-column .csv file.
It can fit linear, exponential, logarithmic and polynomial curves and returns the root-mean-squared-error, R2, sum-of-squared-estimate-of-errors (SSE) and mean-squared-error (MSE) for each fit.
The result can be exported to a .txt or .csv file.

## Version 1.0.0
## Installation

To compile the program, use 

```bash
make
```
## Usage

The input-files can be stored in the "data" folder, but can also be read from anywhere.

```bash
./fit <filepath> <opt: write/silent> <commands> # fits the data that <filepath> leads to
./fit --help    # lists all commands that can be used to fit the data
./fit --info    # explains the nomenclature of the fitting coefficients
```

If console-logging should be disabled or the results exported to file, instructions must be given after the filepath.

```bash
--write         # will write/export the results to a .txt file in the "results" folder
--write=csv     # will write/export the results to a .csv file
 -s             # disables console logging
```

Fitting commands can be chained, e.g.

```bash
--lin --log --pol 2 --pol 4:6 # will fit linear, logarithmic and polynomial curves of degree 2 and degrees 4 to 6
```

## Limits and Outlook

* This program utilizes the Linear Least-Squares-Methods with Gauss-Jordan Elimination for polynomial fits.
* The exponential fit method does not support negative values (version: 1.0.0)
* The delimiters in the .csv files in both input and output are/have to be ";"

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Contact
If you have questions or find errors in the code, please contact yiguang.tt.wang@gmail.com