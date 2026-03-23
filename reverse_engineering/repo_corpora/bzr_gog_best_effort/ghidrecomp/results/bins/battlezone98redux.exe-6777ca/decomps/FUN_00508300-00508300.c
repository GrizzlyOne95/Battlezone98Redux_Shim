
void FUN_00508300(undefined4 param_1)

{
  float *pfVar1;
  char local_88 [128];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  pfVar1 = (float *)FUN_004ff7c0(param_1,1);
  sprintf(local_88,"{x=%f, y=%f, z=%f}",(double)*pfVar1,(double)pfVar1[1],(double)pfVar1[2]);
  FUN_0082cd77(param_1,local_88);
  FUN_0083e885();
  return;
}

