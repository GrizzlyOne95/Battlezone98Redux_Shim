
undefined4 FUN_00811230(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  char local_5;
  
  cVar1 = FID_conflict_operator__(param_2);
  if (cVar1 == '\0') {
    uVar2 = *param_1;
    cVar1 = FUN_0080f9e0(param_1,param_2);
    if (cVar1 == '\0') {
      local_5 = FUN_008124b0(param_1,param_2,param_3);
    }
    else {
      local_5 = FUN_00812490(param_1,param_2,param_3);
    }
    if (local_5 == '\0') {
      *param_1 = uVar2;
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

