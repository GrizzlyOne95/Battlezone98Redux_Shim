
void FUN_00684650(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined1 local_10 [4];
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  puVar1 = (undefined4 *)FUN_00684860(local_8,param_3);
  puVar1 = (undefined4 *)FUN_00684860(local_c,param_2,*puVar1);
  puVar1 = (undefined4 *)FUN_00684860(local_10,param_1,*puVar1);
  FUN_00684880(*puVar1);
  return;
}

