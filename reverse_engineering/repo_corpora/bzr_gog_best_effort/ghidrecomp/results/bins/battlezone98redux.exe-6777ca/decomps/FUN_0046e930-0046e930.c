
undefined4 *
FUN_0046e930(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_8 [4];
  
  puVar2 = (undefined4 *)FUN_0046e9c0(local_8,param_2,param_3,param_4);
  param_2 = *puVar2;
  cVar1 = FID_conflict_operator__(&param_3);
  if (cVar1 == '\0') {
    uVar3 = FUN_0042eee0(param_3,param_4);
    uVar3 = FUN_0042eee0(param_2,uVar3);
    uVar3 = FUN_0046ea10(uVar3);
    puVar2 = (undefined4 *)FUN_0046ea70(&param_2,uVar3);
    *param_1 = *puVar2;
  }
  else {
    *param_1 = param_2;
  }
  return param_1;
}

