# Yet another text editor Yate

### Installation

- Download this repository
- Unpack it
- Change into its directory
- Open a terminal (For <b>linux</b> users):<br>
  ```
  mkdir build && cd build
  cmake ..
  make
  ```

(Windows was not tested so far)

### Run it
```./yate``` (or ```.\yate``` under Windows if build succeed)<br>
With a webbrowser visit ```localhost:8082``` or ```localhost:8083```. (The user interface is started two times in the example implementation)

### Run unittests
#### Linux
  ```
  cd build
  cmake -DYATE_PROJECT_BUILD_TESTING=true ..
  make
  make test
  ```

### Dependencies
#### Internal
Small asynchronous http server created for this project:<br>
https://github.com/brickeddroid/small_httpserver
#### External
Json library: https://github.com/nlohmann/json
