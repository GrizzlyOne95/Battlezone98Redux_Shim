
undefined4
FUN_00692150(undefined4 *param_1,undefined4 param_2,int param_3,undefined4 param_4,
            undefined4 param_5)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00690950(*param_1,param_4,param_5,*(uint *)(param_3 + 0x24) >> 0x12 & 0xf,
                       *(uint *)(param_3 + 0x24) >> 0x16 & 0xf);
  if (iVar1 == 0) {
    iVar1 = FUN_00691cd0(0,param_4,param_5);
    if (iVar1 == 0) {
      iVar1 = FUN_00691cd0(1,param_4,param_5);
      if (iVar1 == 0) {
        iVar1 = FUN_00691c50(param_2,param_3,param_4,param_5);
        if (iVar1 == 0) {
          uVar2 = 0;
        }
        else {
          uVar2 = FUN_00434910(param_3,param_4,param_5);
        }
      }
      else {
        uVar2 = 0;
      }
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

