
undefined4 *
FUN_004b7380(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  undefined1 local_10 [4];
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  puVar1 = (undefined4 *)FUN_004b73e0(local_8,param_3,param_4);
  puVar1 = (undefined4 *)FUN_004b73e0(local_c,param_2,*puVar1);
  puVar1 = (undefined4 *)FUN_004b7490(local_10,*puVar1);
  puVar1 = (undefined4 *)FUN_0046ea70(&param_2,*puVar1);
  *param_1 = *puVar1;
  return param_1;
}

