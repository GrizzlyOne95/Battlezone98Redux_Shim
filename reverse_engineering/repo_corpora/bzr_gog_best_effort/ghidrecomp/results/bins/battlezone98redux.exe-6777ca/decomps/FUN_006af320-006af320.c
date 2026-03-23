
int FUN_006af320(int param_1,byte param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
                undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  char cVar1;
  int iVar2;
  undefined1 local_18 [8];
  undefined1 local_10 [8];
  int local_8;
  
  if (param_1 == -1) {
    FUN_006d8cf0(0x2719);
  }
  else {
    do {
      local_8 = FUN_006af270(param_1,param_3,param_4,param_5,param_6,param_7,param_8);
      if (-1 < local_8) {
        return local_8;
      }
      if ((param_2 & 1) != 0) {
        return 0;
      }
      FUN_006d8cc0(0x2733,0);
      cVar1 = operator!=<>(param_8,local_10);
      if (cVar1 != '\0') {
        FUN_006d8cc0(0x4d5,0);
        cVar1 = operator!=<>(param_8,local_18);
        if (cVar1 != '\0') {
          return 0;
        }
      }
      iVar2 = FUN_006af9e0(param_1,0,param_8);
    } while (-1 < iVar2);
  }
  return 0;
}

