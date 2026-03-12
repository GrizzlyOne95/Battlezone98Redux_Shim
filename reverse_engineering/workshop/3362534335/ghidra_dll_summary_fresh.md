# Ghidra DLL Summary

Headless analysis performed with `pyghidra` / `pyghidra_mcp`.

## _bzcp.dll

- Source path: `reverse_engineering\workshop\3362534335\latest\_bzcp.dll`
- Project name: `/_bzcp.dll-65eabf`
- PDB path in debug record: `F:\Battlezone\Janne DLL Shim and Lua\bzpre\Release\_bzcp.pdb`

- Exports:
  - `Ordinal_1` @ `100021d0`
  - `luaopen__bzcp` @ `100021d0`
  - `Ordinal_2` @ `10010280`
  - `patch` @ `10010280`
  - `entry` @ `10020133`
- Imports (first 16):
  - `VERSION.DLL` :: `GetFileVersionInfoA`
  - `VERSION.DLL` :: `VerQueryValueA`
  - `VERSION.DLL` :: `GetFileVersionInfoSizeA`
  - `KERNEL32.DLL` :: `GetModuleHandleW`
  - `KERNEL32.DLL` :: `GetCurrentProcess`
  - `KERNEL32.DLL` :: `WriteProcessMemory`
  - `KERNEL32.DLL` :: `GetModuleFileNameA`
  - `KERNEL32.DLL` :: `GetModuleHandleExW`
  - `KERNEL32.DLL` :: `GetModuleFileNameW`
  - `KERNEL32.DLL` :: `ReadProcessMemory`
  - `KERNEL32.DLL` :: `GetProcAddress`
  - `KERNEL32.DLL` :: `DeleteFileW`
  - `KERNEL32.DLL` :: `GetLastError`
  - `KERNEL32.DLL` :: `MoveFileExW`
  - `KERNEL32.DLL` :: `CopyFileW`
  - `KERNEL32.DLL` :: `Sleep`

### patch export

- Address: `0x10010280`
- Signature: `void __cdecl patch(undefined4 param_1);`
```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl patch(undefined4 param_1)

{
  code *pcVar1;
  undefined4 *_ArgList;
  uintptr_t uVar2;
  int iVar3;
  uint *_ThrdAddr;
  undefined4 uVar4;
  uint local_c [2];
  
                    /* 0x10280  2  patch */
  if (DAT_1002ab10 != '\0') {
    return;
  }
  DAT_1002ab10 = '\x01';
  _ArgList = operator_new(8);
  *_ArgList = param_1;
  _ThrdAddr = local_c;
  _ArgList[1] = FUN_1000eb30;
  uVar2 = _beginthreadex((void *)0x0,0,FUN_10016480,_ArgList,0,_ThrdAddr);
  if (uVar2 != 0) {
    if (DAT_1002aee4 != 0) {
                    /* WARNING: Subroutine does not return */
      terminate();
    }
    _DAT_1002aee0 = CONCAT44(local_c[0],uVar2);
    if ((local_c[0] != 0) && (iVar3 = _Thrd_detach(uVar2,local_c[0],uVar2), iVar3 == 0)) {
      _DAT_1002aee0 = 0;
      return;
    }
    _ThrdAddr = (uint *)0x1;
    std::_Throw_Cpp_error(1);
  }
  uVar4 = 0;
  std::_Throw_Cpp_error(6);
  pcVar1 = (code *)swi(3);
  (*pcVar1)(_ThrdAddr,uVar4);
  return;
}
```

### patch worker

- Address: `0x1000EB30`
- Signature: `void __cdecl FUN_1000eb30(uint param_1);`
```c
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl FUN_1000eb30(uint param_1)

{
  int iVar1;
  errno_t eVar2;
  DWORD DVar3;
  LPCVOID lpData;
  BOOL BVar4;
  HANDLE hProcess;
  int *piVar5;
  int *piVar6;
  uint uVar7;
  int iVar8;
  bool bVar9;
  undefined8 uVar10;
  wchar_t *pwVar11;
  undefined1 local_161;
  int *local_160;
  tm local_15c;
  undefined1 local_138;
  undefined1 local_137;
  undefined1 local_136;
  undefined1 local_135;
  undefined1 local_134;
  undefined4 local_12c;
  CHAR local_128 [264];
  undefined1 local_20;
  undefined1 uStack_1f;
  undefined1 uStack_1e;
  undefined1 uStack_1d;
  undefined1 local_1c;
  uint local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_10021c80;
  local_10 = ExceptionList;
  local_18 = DAT_1002a040 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_20 = (undefined1)param_1;
  uStack_1f = (undefined1)(param_1 >> 8);
  uStack_1e = (undefined1)(param_1 >> 0x10);
  uStack_1d = (undefined1)(param_1 >> 0x18);
  FUN_100186f0(&local_15c.tm_mday,param_1);
  FUN_10018af0(&DAT_1002a264,&local_15c.tm_mday);
  if (0xf < (uint)local_15c.tm_isdst) {
    piVar5 = (int *)local_15c.tm_mday;
    if ((0xfff < local_15c.tm_isdst + 1U) &&
       (piVar5 = *(int **)(local_15c.tm_mday + -4),
       0x1f < (uint)(local_15c.tm_mday + (-4 - (int)piVar5)))) {
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_1001f9a8(piVar5);
  }
  eVar2 = _wfopen_s((FILE **)&DAT_1002af1c,L"bzcp.log",L"w");
  if (eVar2 == 0) {
    if (DAT_1002af1c != 0) {
      FUN_100184c0(DAT_1002af1c,L"=========== START UP ===========\n");
      FUN_100184c0(DAT_1002af1c,L"Community Patch created by Nielk1\n");
      FUN_100189e0(DAT_1002af1c,"Patch Version: %s\n");
      FUN_100184c0(DAT_1002af1c,L"Expected Shim Version: %d\n");
      FUN_100184c0(DAT_1002af1c,L"Shim Version: %d\n");
      fflush((FILE *)DAT_1002af1c);
    }
  }
  else {
    DAT_1002af1c = 0;
  }
  memset(local_128,0,0x104);
  GetModuleFileNameA((HMODULE)0x0,local_128,0x104);
  local_12c = (char *)0x0;
  local_160 = (int *)0x0;
  DVar3 = GetFileVersionInfoSizeA(local_128,(LPDWORD)0x0);
  uVar7 = 0xffffffff;
  if (DVar3 != 0) {
    lpData = (LPCVOID)FUN_1001fd2c(DVar3);
    BVar4 = GetFileVersion
```

### save selection helper

- Address: `0x1000CAF0`
- Signature: `void __fastcall FUN_1000caf0(int param_1);`
```c
void __fastcall FUN_1000caf0(int param_1)

{
  uint *puVar1;
  char *pcVar2;
  
  DAT_1002a1c8 = *(undefined4 *)((*(int **)(param_1 + 0x1c8))[0xb] + 0x150);
  pcVar2 = (char *)(**(int **)(param_1 + 0x1c8) + *(int *)(*(int *)(param_1 + 0x17c) + 0x14c) * 0x18
                   );
  if (pcVar2 != s_Stock_1002a1ec) {
    puVar1 = (uint *)(pcVar2 + 0x10);
    if (0xf < *(uint *)(pcVar2 + 0x14)) {
      pcVar2 = *(char **)pcVar2;
    }
    FUN_10012330(s_Stock_1002a1ec,pcVar2,*puVar1);
  }
  return;
}
```

### restore selection helper

- Address: `0x1000CB40`
- Signature: `void __fastcall FUN_1000cb40(int param_1);`
```c
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __fastcall FUN_1000cb40(int param_1)

{
  int *piVar1;
  byte *pbVar2;
  byte *pbVar3;
  bool bVar4;
  int iVar5;
  byte *pbVar6;
  byte *pbVar7;
  byte *pbVar8;
  int local_2c [2];
  int local_24;
  int local_20;
  int *local_1c;
  int local_18;
  int *local_14;
  code *local_10;
  int local_c;
  uint local_8;
  
  local_8 = DAT_1002a040 ^ (uint)&stack0xfffffffc;
  piVar1 = (int *)*DAT_1002ad78;
  local_14 = piVar1;
  local_c = param_1;
  if ((piVar1 == (int *)0x0) || (iVar5 = (*DAT_1002ad7c)(), local_18 = iVar5, iVar5 == 0)) {
    iVar5 = -1;
  }
  else {
    local_1c = local_2c;
    local_10 = *(code **)(*piVar1 + 0x38);
    (*local_10)(local_1c);
    if (((local_2c[0] == *(int *)(iVar5 + 0x20)) && (local_24 == *(int *)(iVar5 + 0x28))) &&
       (local_20 == *(int *)(iVar5 + 0x2c))) {
      iVar5 = 1;
    }
    else {
      iVar5 = 0;
    }
  }
  if ((iVar5 == 0) || ((iVar5 == -1 && (DAT_1002ab12 == '\0')))) {
    FUN_10012330(s_Stock_1002a1ec,"All Maps",8);
  }
  pbVar3 = (byte *)(*(int **)(param_1 + 0x1c8))[1];
  pbVar2 = (byte *)**(int **)(param_1 + 0x1c8);
  for (pbVar8 = pbVar2; pbVar8 != pbVar3; pbVar8 = pbVar8 + 0x18) {
    pbVar6 = (byte *)s_Stock_1002a1ec;
    if (0xf < DAT_1002a200) {
      pbVar6 = (byte *)s_Stock_1002a1ec._0_4_;
    }
    pbVar7 = pbVar8;
    if (0xf < *(uint *)(pbVar8 + 0x14)) {
      pbVar7 = *(byte **)pbVar8;
    }
    bVar4 = FUN_10014e50(pbVar7,*(uint *)(pbVar8 + 0x10),pbVar6,DAT_1002a1fc);
    if (bVar4) break;
  }
  local_c = *(undefined4 *)(local_c + 0x17c);
  if (pbVar8 != pbVar3) {
    iVar5 = ((int)pbVar8 - (int)pbVar2) / 0x18;
    local_10 = (code *)local_c;
    local_c = iVar5;
    (*DAT_1002ad08)(iVar5);
    return;
  }
  (*DAT_1002ad08)(0);
  return;
}
```

### restore scroll helper

- Address: `0x1000CCA0`
- Signature: `void __fastcall FUN_1000cca0(int param_1);`
```c
void __fastcall FUN_1000cca0(int param_1)

{
  int iVar1;
  
  if ((-1 < DAT_1002a1c8) &&
     (iVar1 = *(int *)(*(int *)(param_1 + 0x1c8) + 0x2c),
     DAT_1002a1c8 < (*(int *)(iVar1 + 0x16c) - *(int *)(iVar1 + 0x168)) / 0x1c)) {
    iVar1 = 0;
    if (0 < DAT_1002a1c8) {
      do {
        (*DAT_1002adb0)();
        iVar1 = iVar1 + 1;
      } while (iVar1 < DAT_1002a1c8);
    }
    DAT_1002a1c8 = 0xffffffff;
    return;
  }
  DAT_1002a1c8 = 0xffffffff;
  return;
}
```

### vehicle list mod fix helper A

- Address: `0x1000D0D0`
- Signature: `void FUN_1000d0d0(byte *param_1);`
```c
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_1000d0d0(byte *param_1)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  bool bVar7;
  byte *pbVar8;
  undefined4 ****ppppuVar9;
  byte *pbVar10;
  uint uVar11;
  code *pcVar12;
  uint uVar13;
  undefined4 *puVar14;
  undefined1 auStack_7c [16];
  undefined4 uStack_6c;
  undefined4 auStack_64 [3];
  undefined4 uStack_58;
  undefined4 *local_30;
  undefined4 ***local_2c [4];
  uint local_1c;
  uint local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_100219fd;
  local_10 = ExceptionList;
  local_14 = DAT_1002a040 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar11 = 0;
  *(undefined4 *)(DAT_1002ac30 + 0x38) = 0xffffffff;
  iVar6 = DAT_1002ac30;
  iVar2 = *(int *)(DAT_1002ac30 + 0x18);
  uVar3 = *(uint *)(iVar2 + 0x10);
  if (uVar3 != 0) {
    iVar4 = *(int *)(iVar2 + 0xc);
    iVar5 = *(int *)(iVar2 + 4);
    iVar2 = *(int *)(iVar2 + 8);
    do {
      pbVar10 = *(byte **)(iVar5 + (iVar4 + uVar11 & iVar2 - 1U) * 4);
      pbVar8 = param_1;
      if (0xf < *(uint *)(param_1 + 0x14)) {
        pbVar8 = *(byte **)param_1;
      }
      puVar1 = (uint *)(pbVar10 + 0x10);
      if (0xf < *(uint *)(pbVar10 + 0x14)) {
        pbVar10 = *(byte **)pbVar10;
      }
      uStack_58 = 0x1000d158;
      bVar7 = FUN_10014e50(pbVar10,*puVar1,pbVar8,*(uint *)(param_1 + 0x10));
      if (bVar7) {
        *(uint *)(iVar6 + 0x38) = uVar11;
        pcVar12 = DAT_1002add8;
        iVar2 = *(int *)(DAT_1002ac30 + 0x18);
        local_30 = *(undefined4 **)
                    (*(int *)(iVar2 + 4) +
                    (*(int *)(iVar2 + 8) - 1U & *(int *)(iVar2 + 0xc) + uVar11) * 4);
        if (local_30 != (undefined4 *)0x0) {
          uStack_6c = 0x1000d217;
          FUN_10018a00(auStack_64,local_30);
          local_8 = 0;
          puVar14 = local_30 + 0xf;
          goto LAB_1000d19a;
        }
        break;
      }
      uVar11 = uVar11 + 1;
    } while (uVar11 < uVar3);
  }
  pcVar12 = DAT_1002add8;
  local_30 = auStack_64;
  uStack_6c = 0x1000d189;
  FUN_10018a00(auStack_64,&DAT_1002a21c);
  local_8 = 1;
  puVar14 = &DAT_1002a204;
LAB_1000d19a:
  FUN_10018a00(auStack_7c,puVar14);
  local_8 = 0xffffffff;
  (*pcVar12)();
  FUN_10018a00(l
```

### vehicle list mod fix 1/4

- Address: `0x1000D460`
- Signature: `void FUN_1000d460(void);`
```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000d460(void)

{
  int unaff_EBP;
  undefined4 unaff_retaddr;
  
  *(undefined4 *)(unaff_EBP + -4) = unaff_retaddr;
  (*DAT_1002adfc)();
  (*DAT_1002ae00)(*(undefined4 *)(unaff_EBP + -4));
                    /* WARNING: Could not recover jumptable at 0x1000d478. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_1002ae08)();
  return;
}
```

### vehicle list mod fix 2/4

- Address: `0x1000D330`
- Signature: `void __thiscall FUN_1000d330(undefined4 param_1,byte *param_2);`
```c
void __thiscall FUN_1000d330(undefined4 param_1,byte *param_2)

{
  DAT_1002ac30 = param_1;
  FUN_1000d0d0(param_2);
  return;
}
```

### vehicle list mod fix helper B

- Address: `0x1000D340`
- Signature: `void FUN_1000d340(void);`
```c
void FUN_1000d340(void)

{
  int iVar1;
  code *pcVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined1 auStack_5c [16];
  undefined4 uStack_4c;
  undefined1 auStack_44 [24];
  uint uStack_2c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  uVar3 = DAT_1002af20;
  pcVar2 = DAT_1002add8;
  local_8 = 0xffffffff;
  puStack_c = &LAB_10021a45;
  local_10 = ExceptionList;
  uStack_2c = DAT_1002a040 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  DAT_1002ac30 = *(int *)(*DAT_1002ad84 + 0x1c8);
  if (-1 < *(int *)(DAT_1002ac30 + 0x38)) {
    iVar1 = *(int *)(DAT_1002ac30 + 0x18);
    puVar4 = *(undefined4 **)
              (*(int *)(iVar1 + 4) +
              (*(int *)(iVar1 + 8) - 1U & *(int *)(iVar1 + 0xc) + *(int *)(DAT_1002ac30 + 0x38)) * 4
              );
    if (puVar4 != (undefined4 *)0x0) {
      uStack_4c = 0x1000d3bd;
      FUN_10018a00(auStack_44,puVar4);
      local_8 = 0;
      puVar4 = puVar4 + 0xf;
      goto LAB_1000d3ff;
    }
  }
  uStack_4c = 0x1000d3ee;
  FUN_10018a00(auStack_44,&DAT_1002a21c);
  local_8 = 1;
  puVar4 = &DAT_1002a204;
LAB_1000d3ff:
  FUN_10018a00(auStack_5c,puVar4);
  local_8 = 0xffffffff;
  (*pcVar2)();
  (*DAT_1002ade4)(uVar3);
  (*DAT_1002addc)();
  ExceptionList = local_10;
  return;
}
```

### vehicle list mod fix 4/4

- Address: `0x1000D440`
- Signature: `void __fastcall FUN_1000d440(undefined4 param_1);`
```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_1000d440(undefined4 param_1)

{
  DAT_1002af20 = param_1;
  FUN_1000d340();
                    /* WARNING: Could not recover jumptable at 0x1000d452. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_1002adf8)();
  return;
}
```

### BZRNET integration host

- Address: `0x1000D7B0`
- Signature: `void FUN_1000d7b0(void);`
```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000d7b0(void)

{
  int unaff_EBP;
  
  *(undefined1 *)(unaff_EBP + -4) = 0xc;
  DAT_1002af2c = *(int **)(unaff_EBP + -0x26c);
  (**(code **)(**(int **)(unaff_EBP + -0x26c) + 0x1c))
            (DAT_1002af2c + 10,unaff_EBP + -0xb8,unaff_EBP + -0x100);
  if (DAT_1002af2c != (int *)0x0) {
    *(undefined4 *)(unaff_EBP + -4) = *(undefined4 *)(*DAT_1002af2c + 0x1c);
    (**(code **)(unaff_EBP + -4))(DAT_1002af2c + 10,&DAT_1002a234,&DAT_1002ae28);
    *(undefined4 *)(unaff_EBP + -8) = *(undefined4 *)(*DAT_1002af2c + 0x1c);
    (**(code **)(unaff_EBP + -8))(DAT_1002af2c + 10,&DAT_1002a24c,&DAT_1002a264);
  }
                    /* WARNING: Could not recover jumptable at 0x1000d843. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_1002ae44)();
  return;
}
```

### BZRNET integration client

- Address: `0x1000D850`
- Signature: `void FUN_1000d850(void);`
```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000d850(void)

{
  int unaff_EBP;
  
  *(undefined1 *)(unaff_EBP + -4) = 7;
  DAT_1002af30 = *(int **)(unaff_EBP + -0xbc);
  (**(code **)(**(int **)(unaff_EBP + -0xbc) + 0x1c))
            (DAT_1002af30 + 10,unaff_EBP + -0xa0,unaff_EBP + -0x40);
  if (DAT_1002af30 != (int *)0x0) {
    *(undefined4 *)(unaff_EBP + -4) = *(undefined4 *)(*DAT_1002af30 + 0x1c);
    (**(code **)(unaff_EBP + -4))(DAT_1002af30 + 10,&DAT_1002a234,&DAT_1002ae28);
    *(undefined4 *)(unaff_EBP + -8) = *(undefined4 *)(*DAT_1002af30 + 0x1c);
    (**(code **)(unaff_EBP + -8))(DAT_1002af30 + 10,&DAT_1002a24c,&DAT_1002a264);
  }
                    /* WARNING: Could not recover jumptable at 0x1000d8df. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_1002ae4c)();
  return;
}
```

### ban button helper A

- Address: `0x1000DF80`
- Signature: `void FUN_1000df80(void);`
```c
void FUN_1000df80(void)

{
  undefined4 uVar1;
  void *pvVar2;
  float in_XMM2_Da;
  float in_XMM3_Da;
  
  uVar1 = DAT_1002af4c;
  pvVar2 = operator_new(0x1ec);
  memset(pvVar2,0,0x1ec);
  DAT_1002af3c = pvVar2;
  DAT_1002af3c = (void *)(*DAT_1002ae60)("Ban User",in_XMM2_Da - 48.0,in_XMM3_Da + 96.0,0x42400000,
                                         0x42400000,0x20,uVar1,0,0);
  (*DAT_1002ae68)("MultiplayerModeButton_off.png");
  (*DAT_1002ae6c)("MultiplayerModeButton_over.png");
  (*DAT_1002ae70)("MultiplayerModeButton_on.png");
  (*DAT_1002ae74)(&DAT_10024c38);
  (*DAT_1002ae80)(FUN_1000ddd0);
  (*DAT_1002ae84)(FUN_1000ddb0);
  (*DAT_1002ae5c)(DAT_1002af3c,0);
  pvVar2 = operator_new(0x930);
  memset(pvVar2,0,0x930);
  DAT_1002af40 = pvVar2;
  DAT_1002af40 = (void *)(*DAT_1002ae64)("Lobby",0x43870000,0x44750000,0x43a90000,0x422c0000,0x8020,
                                         uVar1,0,0);
  (*DAT_1002ae78)("Ban highlighted player");
  (*DAT_1002ae7c)(0);
  (*DAT_1002ae5c)(DAT_1002af40,0);
  return;
}
```

### ban button hook 1/2

- Address: `0x1000E110`
- Signature: `void FUN_1000e110(void);`
```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000e110(void)

{
  int unaff_EBP;
  
  DAT_1002af58 = (uint)*(byte *)(unaff_EBP + 0x20);
  DAT_1002af4c = *(undefined4 *)(unaff_EBP + 8);
  DAT_1002af50 = *(undefined4 *)(unaff_EBP + 0xc);
  DAT_1002af54 = *(undefined4 *)(unaff_EBP + 0x10);
  FUN_1000df80();
                    /* WARNING: Could not recover jumptable at 0x1000e168. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_1002ae94)();
  return;
}
```

### ban button helper B

- Address: `0x1000E1F0`
- Signature: `void FUN_1000e1f0(void);`
```c
void FUN_1000e1f0(void)

{
  undefined4 uVar1;
  void *pvVar2;
  
  uVar1 = DAT_1002af5c;
  pvVar2 = operator_new(0x1ec);
  memset(pvVar2,0,0x1ec);
  DAT_1002af44 = pvVar2;
  DAT_1002af44 = (void *)(*DAT_1002ae60)("Ban User",0xc2040000,0x446b8000,0x42400000,0x42400000,0,
                                         uVar1,0,0);
  (*DAT_1002ae68)("MultiplayerModeButton_off.png");
  (*DAT_1002ae6c)("MultiplayerModeButton_over.png");
  (*DAT_1002ae70)("MultiplayerModeButton_on.png");
  (*DAT_1002ae74)(&DAT_10024c38);
  (*DAT_1002ae80)(&LAB_1000e190);
  (*DAT_1002ae84)(FUN_1000e170);
  (*DAT_1002ae5c)(DAT_1002af44,0);
  pvVar2 = operator_new(0x930);
  memset(pvVar2,0,0x930);
  DAT_1002af48 = pvVar2;
  DAT_1002af48 = (void *)(*DAT_1002ae64)("Lobby",0x43870000,0x447a0000,0x43a90000,0x422c0000,0x20,
                                         uVar1,0,0);
  (*DAT_1002ae78)("Ban highlighted player");
  (*DAT_1002ae7c)(0);
  (*DAT_1002ae5c)(DAT_1002af48,0);
  return;
}
```

### ban button hook 2/2

- Address: `0x1000E360`
- Signature: `void FUN_1000e360(void);`
```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1000e360(void)

{
  int unaff_EBP;
  
  DAT_1002af5c = *(undefined4 *)(unaff_EBP + -0xd8);
  FUN_1000e1f0();
  *(undefined1 *)(unaff_EBP + -4) = 0xff;
                    /* WARNING: Could not recover jumptable at 0x1000e37b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_1002aea8)();
  return;
}
```

## winmm.bin

- Source path: `reverse_engineering\workshop\3362534335\latest\winmm.bin`
- Project name: `/winmm.bin-90da10`
- PDB path in debug record: `F:\Battlezone\Janne DLL Shim and Lua\bzpre\Release\winmm.pdb`

- Exports:
  - `Ordinal_4` @ `10001000`
  - `CloseDriver` @ `10001000`
  - `Ordinal_5` @ `10001010`
  - `DefDriverProc` @ `10001010`
  - `Ordinal_6` @ `10001020`
  - `DriverCallback` @ `10001020`
  - `Ordinal_7` @ `10001030`
  - `DrvGetModuleHandle` @ `10001030`
  - `Ordinal_8` @ `10001040`
  - `GetDriverModuleHandle` @ `10001040`
  - `Ordinal_9` @ `10001050`
  - `NotifyCallbackData` @ `10001050`
  - `Ordinal_10` @ `10001060`
  - `OpenDriver` @ `10001060`
  - `Ordinal_11` @ `10001070`
  - `PlaySound` @ `10001070`
- Imports (first 16):
  - `KERNEL32.DLL` :: `GetFullPathNameW`
  - `KERNEL32.DLL` :: `LoadLibraryW`
  - `KERNEL32.DLL` :: `GetProcAddress`
  - `KERNEL32.DLL` :: `GetSystemDirectoryW`
  - `KERNEL32.DLL` :: `FreeLibrary`
  - `KERNEL32.DLL` :: `IsDebuggerPresent`
  - `KERNEL32.DLL` :: `InitializeSListHead`
  - `KERNEL32.DLL` :: `GetSystemTimeAsFileTime`
  - `KERNEL32.DLL` :: `GetCurrentThreadId`
  - `KERNEL32.DLL` :: `GetCurrentProcessId`
  - `KERNEL32.DLL` :: `QueryPerformanceCounter`
  - `KERNEL32.DLL` :: `IsProcessorFeaturePresent`
  - `KERNEL32.DLL` :: `TerminateProcess`
  - `KERNEL32.DLL` :: `GetCurrentProcess`
  - `KERNEL32.DLL` :: `SetUnhandledExceptionFilter`
  - `KERNEL32.DLL` :: `UnhandledExceptionFilter`

### DllMain entry

- Address: `0x10002E1B`
- Signature: `void entry(HINSTANCE__ *param_1,ulong param_2,void *param_3);`
```c
void entry(HINSTANCE__ *param_1,ulong param_2,void *param_3)

{
  if (param_2 == 1) {
    ___security_init_cookie();
  }
  dllmain_dispatch(param_1,param_2,param_3);
  return;
}
```

### Loader / proxy init

- Address: `0x10001C20`
- Signature: `undefined4 FUN_10001c20(undefined4 param_1,int param_2);`
```c
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_10001c20(undefined4 param_1,int param_2)

{
  DWORD DVar1;
  FARPROC pFVar2;
  WCHAR local_418 [260];
  WCHAR local_210 [260];
  uint local_8;
  
  local_8 = DAT_10007000 ^ (uint)&stack0xfffffffc;
  if (param_2 != 1) {
    if (param_2 != 0) {
      return 1;
    }
    FreeLibrary(DAT_100076d8);
    if (DAT_100073d4 == (HMODULE)0x0) {
      return 1;
    }
    FreeLibrary(DAT_100073d4);
    return 1;
  }
  DVar1 = GetFullPathNameW(L".\\..\\..\\workshop\\content\\301650\\3362534335\\_bzcp.dll",0x104,
                           local_210,(LPWSTR *)0x0);
  if (DVar1 != 0) {
    DAT_100073d4 = LoadLibraryW(local_210);
  }
  if (DAT_100073d4 == (HMODULE)0x0) {
    DVar1 = GetFullPathNameW(L".\\mods\\3362534335\\_bzcp.dll",0x104,local_210,(LPWSTR *)0x0);
    if (DVar1 != 0) {
      DAT_100073d4 = LoadLibraryW(local_210);
    }
    if (DAT_100073d4 == (HMODULE)0x0) goto LAB_10001ccc;
  }
  pFVar2 = GetProcAddress(DAT_100073d4,"patch");
  if (pFVar2 != (FARPROC)0x0) {
    (*pFVar2)(1);
  }
LAB_10001ccc:
  GetSystemDirectoryW(local_418,0x103);
  wcscat_s(local_418,0x104,L"\\WINMM.dll");
  DAT_100076d8 = LoadLibraryW(local_418);
  if (DAT_100076d8 != (HMODULE)0x0) {
    _DAT_100076d4 = GetProcAddress(DAT_100076d8,"CloseDriver");
    _DAT_100076d0 = GetProcAddress(DAT_100076d8,"DefDriverProc");
    _DAT_100076cc = GetProcAddress(DAT_100076d8,"DriverCallback");
    _DAT_100076c8 = GetProcAddress(DAT_100076d8,"DrvGetModuleHandle");
    _DAT_100076c4 = GetProcAddress(DAT_100076d8,"GetDriverModuleHandle");
    _DAT_100076c0 = GetProcAddress(DAT_100076d8,"NotifyCallbackData");
    _DAT_100076bc = GetProcAddress(DAT_100076d8,"OpenDriver");
    _DAT_100076b8 = GetProcAddress(DAT_100076d8,"PlaySound");
    _DAT_100076b4 = GetProcAddress(DAT_100076d8,"PlaySoundA");
    _DAT_100076b0 = GetProcAddress(DAT_100076d8,"PlaySoundW");
    _DAT_100076ac = GetProcAddress(DAT_100076d8,"SendDriverMessage");
    _DAT_100076a8 = GetProcAddress(DAT_100076d8,"WOW32DriverCallback");
    _DAT_100076a4 = GetProcAddress(DAT_100076d8,"WOW32ResolveMultiMediaHandle");
    _DAT_100076a0 = GetProcAddress(DAT_100076d8,"WOWAppExit");
    _DAT_1000769c = GetProcAddress(DAT_100076d8,"aux32Message");
    _DAT_10007
```
