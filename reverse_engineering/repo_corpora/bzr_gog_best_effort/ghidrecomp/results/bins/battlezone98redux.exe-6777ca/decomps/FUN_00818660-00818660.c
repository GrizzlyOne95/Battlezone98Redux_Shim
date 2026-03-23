
undefined4 __thiscall FUN_00818660(undefined4 param_1,uint *param_2,undefined1 param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*param_2 < 0x10000000) {
    *param_2 = *param_2 << 4;
    iVar2 = FUN_008186c0(param_3,param_1);
    if (-iVar2 - 1U < *param_2) {
      uVar1 = 0;
    }
    else {
      *param_2 = *param_2 + iVar2;
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

