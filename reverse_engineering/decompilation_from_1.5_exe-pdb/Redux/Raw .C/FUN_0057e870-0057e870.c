
undefined4 *
FUN_0057e870(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined1 *puVar2;
  undefined4 uVar3;
  undefined4 extraout_var;
  
  cVar1 = FID_conflict_operator__(&param_3);
  if (cVar1 != '\0') {
    uVar3 = extraout_var;
    cVar1 = FID_conflict_operator__(&param_4);
    if (cVar1 != '\0') {
      puVar2 = (undefined1 *)_Iter_cat<>(&stack0xfffffffb,&param_2,uVar3);
      uVar3 = FUN_0042eee0(param_4,*puVar2);
      uVar3 = FUN_0042eee0(param_3,uVar3);
      uVar3 = FUN_0042eee0(param_2,uVar3);
      _Rotate<>(uVar3);
    }
  }
  uVar3 = distance<>(param_3,param_4);
  advance<>(&param_2,uVar3);
  *param_1 = param_2;
  return param_1;
}

