
# 🍿 CycloneKRD
Dumping Kernel Routines Address' From User Mode, Effective Tooling That Can Be Used To Hook the **SSDT**.



## 🌟 Usage & Output
```
$ UMKmrD.exe [REQ] <OUTPUT_FILE> [OPT] <SPECIFIC_ROUTINE>
```
If No **Specific Routine** Was Specified, CycloneKRD (UMKmrD) Will Proceed To Dump All Routines.

```
$ UMKmrD.exe dump.txt
Dumped 3070 Kernel Routines.
```

```
$ UMKmrD.exe dump.txt ZwQueryVirtualMemory
ZwQueryVirtualMemory ~> 0xFFFFF807397FA1A0
```

## 🌟 Usage & Output
```
$ UMKmrD.exe [REQ] <OUTPUT_FILE> [OPT] <SPECIFIC_ROUTINE>
```
If No **Specific Routine** Was Specified, CycloneKRD (UMKmrD) Will Proceed To Dump All Routines.

```
$ UMKmrD.exe dump.txt
Dumped 3070 Kernel Routines.
```

```
$ UMKmrD.exe dump.txt ZwQueryVirtualMemory
ZwQueryVirtualMemory ~> 0xFFFFF807397FA1A0
```

## 🍥 Inspection In WinDbg

To Make Sure This Works, I inspected the Dumped Routine Address Of **ZwQueryVirtualMemory**.


```
$ UMKmrD.exe dump.txt ZwQueryVirtualMemory
ZwQueryVirtualMemory ~> 0xFFFFF807397FA1A0
```

```
lkd> u 0xFFFFF807397FA1A0
nt!ZwQueryVirtualMemory:
fffff807`397fa1a0 488bc4          mov     rax,rsp
fffff807`397fa1a3 fa              cli
fffff807`397fa1a4 4883ec10        sub     rsp,10h
fffff807`397fa1a8 50              push    rax
fffff807`397fa1a9 9c              pushfq
fffff807`397fa1aa 6a10            push    10h
fffff807`397fa1ac 488d058d840000  lea     rax,[nt!KiServiceLinkage (fffff807`39802640)]
fffff807`397fa1b3 50              push    rax
```
