Install from source:
- protobuf : https://github.com/protocolbuffers/protobuf/blob/master/src/README.md
- protobuf-c : https://github.com/protobuf-c/protobuf-c (PATCH: https://github.com/protobuf-c/protobuf-c/pull/342/files)

For some reason we need to have the python2 langid installed:
`pip2 install langid`

Finally we should be able to build:

`cd langid.c`

`make all`

`sudo python3 setup.py install`


Then, this can be used in python in the following way:
```python
from _langid import identify
lang = identify("Toto va à la plage.")
```
