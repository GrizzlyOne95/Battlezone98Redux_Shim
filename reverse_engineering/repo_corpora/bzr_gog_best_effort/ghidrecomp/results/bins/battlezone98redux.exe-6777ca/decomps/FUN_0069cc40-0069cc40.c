
void FUN_0069cc40(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  int *piVar1;
  char local_108 [256];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  piVar1 = (int *)FUN_006998c0(param_1,param_2);
  if (piVar1 == (int *)0x0) {
    *param_3 = 0xffffffff;
    sprintf(local_108,"Config or AIP float parameter \'%s\' not found.",param_2);
    FUN_00699180(local_108,1);
  }
  else if ((*piVar1 == 3) || (*piVar1 == 2)) {
    *param_3 = 0;
  }
  else {
    *param_3 = 0xffffffff;
    sprintf(local_108,"Config or AIP float parameter \'%s\' found but wrong type.",param_2);
    FUN_00699180(local_108,0);
  }
  FUN_0083e885();
  return;
}

