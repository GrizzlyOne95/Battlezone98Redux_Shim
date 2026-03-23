
undefined4 FUN_004ffb70(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 local_10;
  
  uVar1 = FUN_0082ba59(param_1,1,0);
  uVar2 = FUN_0082ba1c(param_1,2);
  iVar3 = FUN_004ff820(param_1,3);
  if (iVar3 == 0) {
    iVar3 = FUN_004ff7a0(param_1,3);
    if (iVar3 == 0) {
      iVar3 = FUN_0082c9f5(param_1,3);
      if (iVar3 == 0) {
        uVar4 = FUN_004ff750(param_1,3);
        local_10 = FUN_005c8080(uVar1,uVar2,uVar4,0);
      }
      else {
        uVar4 = FUN_0082d377(param_1,3,0);
        uVar5 = FUN_0082c1fd(param_1,4,0);
        local_10 = FUN_005c8250(uVar1,uVar2,uVar4,uVar5,0);
      }
    }
    else {
      local_10 = FUN_005c8380(uVar1,uVar2,iVar3,0);
    }
  }
  else {
    local_10 = FUN_005c82b0(uVar1,uVar2,iVar3,0);
  }
  FUN_004ff770(param_1,local_10);
  return 1;
}

