
undefined4 __thiscall
FUN_0043b520(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  FUN_0043b110(param_4,param_3 + 0x30,param_1);
  iVar1 = FUN_0043b380(param_3);
  if (iVar1 == 0) {
    iVar1 = FUN_0043b210(param_3);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else if (((*(uint *)(param_3 + 0x14) & 0x20) == 0) &&
            (iVar1 = FUN_0043b4a0(param_3), iVar1 != 0)) {
      uVar2 = 0;
    }
    else {
      FUN_0043bc60(param_3);
      FUN_0043bdc0(param_3);
      if (*(int *)(param_3 + 100) == -1) {
        uVar2 = 0;
      }
      else {
        iVar1 = FUN_0043b4f0(param_3);
        if (iVar1 == 0) {
          if ((*(uint *)(param_3 + 0x70) & 0x200) == 0) {
            iVar1 = FUN_00481af0(param_3 + 4);
            if (iVar1 == 0) {
              return 0;
            }
            FUN_00481990(param_3 + 4);
            if (DAT_0260c217 != '\0') {
              *(uint *)(param_3 + 0x70) = *(uint *)(param_3 + 0x70) | 8;
            }
          }
          else {
            iVar1 = FUN_0043b360(param_3);
            if (iVar1 == 0) {
              return 0;
            }
          }
          uVar2 = 1;
        }
        else {
          uVar2 = 0;
        }
      }
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

