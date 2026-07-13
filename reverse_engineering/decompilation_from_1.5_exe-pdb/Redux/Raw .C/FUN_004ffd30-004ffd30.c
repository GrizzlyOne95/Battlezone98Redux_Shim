
undefined4 FUN_004ffd30(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_c;
  
  uVar1 = FUN_0082ba1c(param_1,1);
  iVar2 = FUN_0082c9c5(param_1,2);
  if (iVar2 == 0) {
    local_c = FUN_005c8030(uVar1);
  }
  else {
    uVar3 = FUN_0082d338(param_1,2);
    local_c = FUN_005c8050(uVar1,uVar3);
  }
  FUN_004ff770(param_1,local_c);
  return 1;
}

