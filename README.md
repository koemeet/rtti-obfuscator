# C++ RTTI Obfuscator
Obfuscates all RTTI (Run-time type information) inside a binary so AC's can't catch you on it.

### Usage
You can simply drop any binary into it and it outputs the obfuscated binary in `<relative-dir>/<filename>.tan.<extension>`.

It can also be used on the command line by simply providing the path to the input binary as its first argument:
```
$ rtti-obfuscator <path-to-binary>
```
