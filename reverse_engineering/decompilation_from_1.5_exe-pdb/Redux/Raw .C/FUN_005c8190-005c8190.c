
bool FUN_005c8190(float *param_1,int param_2)

{
  int iVar1;
  float local_c;
  float *local_8;
  
  if (param_2 != 0) {
    iVar1 = FUN_00453d10();
    local_8 = (float *)(*(int *)(param_2 + 8) + iVar1 * 8);
    FUN_00785730((double)*local_8,(double)local_8[1],&local_c,0);
    *param_1 = *local_8;
    param_1[1] = local_c;
    param_1[2] = local_8[1];
  }
  return param_2 != 0;
}

