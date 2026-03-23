
undefined4 * FUN_00440060(undefined4 *param_1,uint param_2,uint param_3,uint param_4)

{
  undefined4 *puVar1;
  undefined1 local_10 [12];
  
  puVar1 = (undefined4 *)
           FUN_00440000(local_10,param_2 ^ 0x80000000,param_3 ^ 0x80000000,param_4 ^ 0x80000000);
  *param_1 = *puVar1;
  param_1[1] = puVar1[1];
  param_1[2] = puVar1[2];
  return param_1;
}

