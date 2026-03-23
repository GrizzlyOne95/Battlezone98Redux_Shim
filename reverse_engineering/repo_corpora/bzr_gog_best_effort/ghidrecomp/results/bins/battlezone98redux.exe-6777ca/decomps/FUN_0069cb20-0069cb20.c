
void FUN_0069cb20(undefined4 param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  int *piVar2;
  char local_108 [256];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = *param_3;
  piVar2 = (int *)FUN_006998c0(param_1,param_2);
  if (piVar2 == (int *)0x0) {
    *param_3 = -1;
    sprintf(local_108,"Config or AIP int parameter \'%s\' not found.",param_2);
    if (iVar1 != -0x11) {
      FUN_00699180(local_108,1);
    }
  }
  else if ((*piVar2 == 1) || (*piVar2 == 3)) {
    *param_3 = 0;
  }
  else {
    *param_3 = -1;
    sprintf(local_108,"Config or AIP int parameter \'%s\' found but wrong type.",param_2);
    if (iVar1 != -0x11) {
      FUN_00699180(local_108,0);
    }
  }
  FUN_0083e885();
  return;
}

