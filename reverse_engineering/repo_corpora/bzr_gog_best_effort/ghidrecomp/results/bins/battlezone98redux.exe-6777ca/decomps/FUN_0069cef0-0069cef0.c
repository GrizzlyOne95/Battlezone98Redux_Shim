
void FUN_0069cef0(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  char local_108 [256];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_0069c4d0(param_1,param_2);
  if (iVar1 == 0) {
    *param_3 = 0xffffffff;
    sprintf(local_108,"Config or AIP float parameter \'%s\' not found.",param_2);
    FUN_00699180(local_108,1);
  }
  else {
    *param_3 = 0;
  }
  FUN_0083e885();
  return;
}

