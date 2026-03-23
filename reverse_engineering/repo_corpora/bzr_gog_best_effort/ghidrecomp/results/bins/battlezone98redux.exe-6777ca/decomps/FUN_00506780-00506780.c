
undefined4 FUN_00506780(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int local_10;
  
  iVar1 = FUN_005062f0(param_1,1);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0082c225(param_1,2,0,0);
    uVar3 = FUN_0082ba59(param_1,3,0);
    local_10 = FUN_0082c225(param_1,4,0,0);
    uVar3 = FUN_00446460(uVar3,0x811c9dc5,local_10);
    uVar2 = FUN_00446460(uVar2,0x811c9dc5,uVar3);
    iVar1 = FUN_00589620(uVar2,uVar3);
    if (iVar1 != 0) {
      local_10 = iVar1;
    }
    FUN_0082cd77(param_1,local_10);
    FUN_0082cbf5(param_1,iVar1 != 0);
    uVar2 = 2;
  }
  return uVar2;
}

