
undefined4 *
FUN_00756c40(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = FID_conflict_operator__(&param_3);
  if (cVar1 == '\0') {
    *param_1 = param_4;
  }
  else {
    uVar2 = FUN_0042eee0(param_3,param_4,param_5);
    uVar2 = FUN_0042eee0(param_2,uVar2);
    FUN_00757140(param_1,uVar2);
  }
  return param_1;
}

