
void FUN_00507a40(undefined4 param_1)

{
  undefined4 uVar1;
  char local_2c [36];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar1 = FUN_004ff750(param_1,1);
  sprintf(local_2c,"%0*X",1,uVar1);
  FUN_0082cd77(param_1,local_2c);
  FUN_0083e885();
  return;
}

