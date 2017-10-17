# C++ RTTI Obfuscator
Obfuscates all RTTI (Run-time type information) inside a binary so AC's can't catch you on it.

### Usage
You can simply drop any binary into it and it outputs the obfuscated binary in `<relative-dir>/<filename>.tan.<extension>`.

It can also be used on the command line by simply providing the path to the input binary as its first argument:
```
$ rtti-obfuscator <path-to-binary>
```

### Preview

This is how a binary would look without any RTTI obfuscation:
![](https://i.gyazo.com/5621b2402351cf9c47e1fd406b09d199.png)

Now when ran through the obfuscator, it will turn into this:
![](https://i.gyazo.com/44724ac7089db578abfd242ab7a474ec.png)

### Download
Get the latest binary from https://github.com/koemeet/rtti-obfuscator/releases.
