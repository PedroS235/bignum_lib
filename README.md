# Bignum Library
- Authors:
    - **Pedro Soares**
    - **Issam Jomaa**


## Dependencies
This library depends on the cunit in case tests are desired to be run.
If on a debian based OS, you can use:
```sh
sudo apt-get install libcunit1 libcunit1-doc libcunit1-dev
```

If on a macOS, one can install usign Homebrew with:
```sh
brew install cunit
```

## Usage
A Makefile is available which will make the process of running the tests and example faster. 

If you just want to see the example available at `./src/main.c`, simply type `make run`. This should compile and run the executable.

In case you want to run all the tests available at `./test`, simply type `make test`. **This requires Cunit** to be installed. This might take some time depending on you machine, especially on the `rsa\_large` test.

