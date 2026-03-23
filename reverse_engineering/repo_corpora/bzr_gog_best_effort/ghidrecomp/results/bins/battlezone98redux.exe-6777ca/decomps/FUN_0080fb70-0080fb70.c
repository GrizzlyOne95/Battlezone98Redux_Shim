
undefined4 FUN_0080fb70(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  cVar1 = FID_conflict_operator__(param_2);
  if (cVar1 == '\0') {
    uVar2 = *param_1;
    uVar3 = FUN_00417780(param_3);
    cVar1 = FUN_00810990(param_1,param_2,uVar3);
    if (cVar1 == '\0') {
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

