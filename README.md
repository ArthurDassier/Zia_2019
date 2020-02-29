# Zia_2019

> **C++**

---

Zia project is an HTTP server.
This server is able to serve typical HTTP documents and page requests, as well as CGI execution and more.


```
git submodule update --init --recursive
```

# Compile Zia
```
mkdir build && cd build && cmake .. -G "Unix Makefiles" && cmake --build . && - 
```
# Compile Zia Unit Tests
```
mkdir build && cd build && cmake ../.. -DZIA_TESTS=TRUE -DZIA_COVERAGE=TRUE && cmake --build . 
```