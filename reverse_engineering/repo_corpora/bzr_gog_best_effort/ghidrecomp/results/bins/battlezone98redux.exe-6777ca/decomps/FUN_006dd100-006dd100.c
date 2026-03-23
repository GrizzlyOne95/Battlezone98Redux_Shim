
undefined4 *
FUN_006dd100(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  puVar1 = (undefined4 *)FUN_0042ef30(local_8,param_4);
  uVar2 = FUN_00417780(param_3,*puVar1);
  uVar2 = FUN_00417780(param_2,uVar2);
  puVar1 = (undefined4 *)FUN_006ef3a0(local_c,uVar2);
  puVar1 = (undefined4 *)FUN_0042ef30(&param_4,*puVar1);
  *param_1 = *puVar1;
  return param_1;
}

