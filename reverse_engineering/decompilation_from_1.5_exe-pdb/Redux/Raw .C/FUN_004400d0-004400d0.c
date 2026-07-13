
undefined4 *
FUN_004400d0(undefined4 *param_1,float param_2,float param_3,float param_4,float param_5)

{
  undefined4 *puVar1;
  undefined1 local_10 [12];
  
  puVar1 = (undefined4 *)
           FUN_00440000(local_10,param_3 * param_2,param_4 * param_2,param_5 * param_2);
  *param_1 = *puVar1;
  param_1[1] = puVar1[1];
  param_1[2] = puVar1[2];
  return param_1;
}

