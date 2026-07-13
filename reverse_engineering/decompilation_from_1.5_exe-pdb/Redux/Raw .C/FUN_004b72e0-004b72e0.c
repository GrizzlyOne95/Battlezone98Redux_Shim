
undefined4 *
FUN_004b72e0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 *puVar2;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  puVar2 = (undefined4 *)FUN_004b7380(local_8,param_2,param_3,param_4);
  param_2 = *puVar2;
  cVar1 = FUN_004221b0(&param_3);
  if (cVar1 == '\0') {
    puVar2 = (undefined4 *)FUN_004b73e0(local_c,param_3,param_4);
    puVar2 = (undefined4 *)FUN_004b73e0(local_10,param_2,*puVar2);
    puVar2 = (undefined4 *)FUN_004b7400(local_14,*puVar2);
    puVar2 = (undefined4 *)FUN_0046ea70(&param_2,*puVar2);
    *param_1 = *puVar2;
  }
  else {
    *param_1 = param_2;
  }
  return param_1;
}

