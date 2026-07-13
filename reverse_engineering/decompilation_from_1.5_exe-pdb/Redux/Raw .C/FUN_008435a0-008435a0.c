
uint FUN_008435a0(LPCWSTR param_1,undefined4 *param_2)

{
  char cVar1;
  LPCWSTR lpFileName;
  DWORD DVar2;
  uint *puVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined1 local_8 [8];
  
  lpFileName = param_1;
  if (7 < *(uint *)(param_1 + 10)) {
    lpFileName = *(LPCWSTR *)param_1;
  }
  DVar2 = GetFileAttributesW(lpFileName);
  if (DVar2 == 0xffffffff) {
    puVar3 = (uint *)FUN_00843490(local_8,param_1,param_2);
    return *puVar3;
  }
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = 0;
    uVar4 = FUN_0083e820();
    param_2[1] = uVar4;
  }
  if ((DVar2 & 0x400) == 0) {
    return (DVar2 & 0x10 | 0x20) >> 4;
  }
  cVar1 = FUN_00842ef0(param_1);
  if (cVar1 == '\0') {
    return 9;
  }
  uVar5 = 4;
  if ((DVar2 & 0x10) != 0) {
    uVar5 = 0xb;
  }
  return uVar5;
}

