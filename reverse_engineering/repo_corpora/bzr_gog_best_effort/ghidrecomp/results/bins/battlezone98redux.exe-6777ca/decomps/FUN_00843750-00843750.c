
undefined4 FUN_00843750(undefined4 param_1,int param_2,undefined4 *param_3)

{
  char cVar1;
  undefined4 uVar2;
  DWORD DVar3;
  
  if (param_2 == 1) {
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = 0;
      uVar2 = FUN_0083e820();
      param_3[1] = uVar2;
    }
    return 0;
  }
  if ((param_2 == 3) || (param_2 == 0xb)) {
    cVar1 = FUN_008436b0(param_1);
    if (cVar1 == '\0') {
      DVar3 = GetLastError();
    }
    else {
      DVar3 = 0;
    }
    cVar1 = FUN_00842d80(DVar3,param_1,param_3,"boost::filesystem::remove");
    if (cVar1 != '\0') {
      return 0;
    }
  }
  else {
    cVar1 = FUN_00843700(param_1);
    if (cVar1 == '\0') {
      DVar3 = GetLastError();
    }
    else {
      DVar3 = 0;
    }
    cVar1 = FUN_00842d80(DVar3,param_1,param_3,"boost::filesystem::remove");
    if (cVar1 != '\0') {
      return 0;
    }
  }
  return 1;
}

