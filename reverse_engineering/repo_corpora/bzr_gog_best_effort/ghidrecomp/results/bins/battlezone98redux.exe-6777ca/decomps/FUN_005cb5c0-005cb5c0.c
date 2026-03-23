
undefined4 __thiscall FUN_005cb5c0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00462630(param_2,param_1);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = *(undefined4 *)(iVar1 + 0xac);
  }
  return uVar2;
}

