
# cFlask - HTTP C-based flask server

cFlask is a mini flask, purely written in c, implementing handling logic of various types of GET requests like simple get request, get request with query parameters etc.
## Features

- Uses Civetweb library to create web server.
- Handles different types of GET request, with parameter and without parameters.
- loadgen.sh script to test how much load our server can handle.
## Tech Stack

**C**: The core language used to create the project.

**Civetweb**: Library used to implement web server.


## Dependencies

To run locally following dependencies must be installed and configured.

- **Civetweb** - Install set it up globally to use -lcivetweb
- **gcc**
- **Apache Benchmark** - For load testing. (optional)
- **Web Browser / Postman** - To check routes
- **Matplotlib** - For visualizing plots. (optional)
- **Python** (optional)
## Run Locally

Clone the project

```bash
git clone https://github.com/menishantsharma/cFlask
```

Go to the project directory

```bash
cd cFlask
```

Compiler server

```bash
gcc flask.c functions.c -o flask -lcivetweb
```

Run server

```bash
./flask <PORT> <THREAD_POOL_SIZE>
```

Change permissions of loadgen script (optional)
```bash
chmod +x loadgen.sh
```

Run loadgen script (optional)
```bash
./loadgen.sh
```

Open your favorite web browser or postman to test individual routes.

```bash
127.0.0.1/square?num=3
```
## API Reference

#### Returns 'hello world' message to user

```http
/
```

#### Returns the square of a number

```http
/square?num=3
```

#### Returns the cube of a number

```http
/cube?num=3
```

#### Returns the same string prefixed by hello back to the user

```http
/helloworld?str=Ashwin
```

#### Returns the same string back to the user

```http
/helloworld?str=Ashwin
```

#### Returns the same string back to the user

```http
/pingpong?str=hello
```

#### Returns 'True' to the user if the number is a prime and 'False' if the number is not prime.

```http
/arithmetic/prime?num=5
```

#### Returns the kth fibonacci number to the user

```http
/arithmetic/fibonacci?num=4
```

## Authors

- **Nishant Sharma** - MTech CSE Student at IIT Bombay
- **Github** - [@Nishant Sharma](https://github.com/menishantsharma)


## License

[MIT](https://choosealicense.com/licenses/mit/)

