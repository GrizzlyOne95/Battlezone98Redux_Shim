
void __thiscall FUN_005c8a50(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00462630(param_2,param_1);
  if (iVar1 != 0) {
    uVar2 = FUN_004ff060(param_3);
    *(undefined4 *)(iVar1 + 0xec) = uVar2;
  }
  return;
}

