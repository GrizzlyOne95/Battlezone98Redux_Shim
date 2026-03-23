
void FUN_0069b480(undefined4 param_1,int param_2,int *param_3,undefined4 param_4,undefined4 param_5,
                 undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  undefined4 *local_8;
  
  for (local_8 = *(undefined4 **)(param_2 + 8); local_8 != (undefined4 *)0x0;
      local_8 = (undefined4 *)local_8[3]) {
    FUN_0069b1f0(param_1,*param_3,*local_8,param_4,param_5,param_6,param_7,param_8);
    *param_3 = *param_3 + local_8[2];
  }
  return;
}

