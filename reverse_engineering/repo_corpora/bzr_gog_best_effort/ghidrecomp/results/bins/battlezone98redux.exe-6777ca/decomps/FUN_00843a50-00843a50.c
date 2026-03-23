
undefined4 * FUN_00843a50(undefined4 *param_1,LPCWSTR param_2,undefined4 *param_3)

{
  char cVar1;
  LPCWSTR lpFileName;
  DWORD DVar2;
  undefined4 uVar3;
  undefined4 local_8;
  
  lpFileName = param_2;
  if (7 < *(uint *)(param_2 + 10)) {
    lpFileName = *(LPCWSTR *)param_2;
  }
  DVar2 = GetFileAttributesW(lpFileName);
  if (DVar2 != 0xffffffff) {
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = 0;
      uVar3 = FUN_0083e820();
      param_3[1] = uVar3;
    }
    if ((DVar2 & 0x400) == 0) {
      local_8 = 3;
      if ((DVar2 & 0x10) == 0) {
        local_8 = 2;
      }
    }
    else {
      cVar1 = FUN_00842ef0(param_2);
      local_8 = 4;
      if (cVar1 == '\0') {
        local_8 = 9;
      }
    }
    uVar3 = FUN_008430e0(param_2,DVar2);
    *param_1 = local_8;
    param_1[1] = uVar3;
    return param_1;
  }
  FUN_00843490(param_1,param_2,param_3);
  return param_1;
}

