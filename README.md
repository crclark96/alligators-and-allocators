# Alligators and Allicators

## Purpose

This repo is a demonstration of a binary hooking technique used to override dynamic libraries
in order to affect program behavior in a way that the author did not intend. It includes two 
dynamic libraries: one that overrides allocator functions (malloc and free) and one that
overrides `__cxa_finalize`.

## Running

There are two demonstrations which both use `LD_PRELOAD` to map in the corresponding
dynamic symbols. Each can be run my first compiling all of the required binary files,
then executing them as follows:

```
$ LD_PRELOAD=./allocator.so ./demo
...
$ ./patcher.py demo    # the second example requires patching the source binary first
$ LD_PRELOAD=./statichooks.so ./demo
```

## Troubleshooting

There are two hardcoded addresses in both the `patcher.py` and `statichooks.c` files.
Verify that the addresses are correct with the following commands:

```
$ objdump -dj .text demo | grep call
    10bf:	ff 15 13 2f 00 00    	call   *0x2f13(%rip)        # 3fd8 <__libc_start_main@GLIBC_2.34>
    1162:	e8 f9 fe ff ff       	call   1060 <__cxa_finalize@plt>
    1167:	e8 64 ff ff ff       	call   10d0 <deregister_tm_clones>
    11b5:	e8 c6 fe ff ff       	call   1080 <write@plt>
    11e1:	e8 a3 ff ff ff       	call   1189 <hello>                              <-- patch_offset
    11eb:	e8 a0 fe ff ff       	call   1090 <malloc@plt>
    11fb:	e8 70 fe ff ff       	call   1070 <free@plt>
$ readelf -h demo
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              DYN (Position-Independent Executable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x10a0                                       <-- entry_offset
  Start of program headers:          64 (bytes into file)
  Start of section headers:          16624 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         13
  Size of section headers:           64 (bytes)
  Number of section headers:         37
  Section header string table index: 36
```

## Additional Reading

* [How To Write Shared Libraries](https://www.akkadia.org/drepper/dsohowto.pdf)
* [Using GDB with LD_PRELOAD](https://www.baeldung.com/linux/gdb-with-ld_preload)
