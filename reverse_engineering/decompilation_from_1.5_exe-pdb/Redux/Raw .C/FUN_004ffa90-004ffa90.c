
undefined4 FUN_004ffa90(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_c;
  
  uVar1 = FUN_0082ba59(param_1,1,0);
  local_c = 0;
  iVar2 = FUN_0082d490(param_1,2,uVar1);
  if (0 < iVar2) {
    uVar3 = FUN_004ff750(param_1,2);
    iVar2 = FUN_00462630(uVar3);
    if (iVar2 != 0) {
      local_c = (**(code **)(*(int *)(iVar2 + 0x18) + 0x30))();
    }
  }
  iVar2 = FUN_0043ac70(uVar1,local_c);
  if (iVar2 != 0) {
    FUN_0043aaa0(iVar2);
  }
  return 0;
}

