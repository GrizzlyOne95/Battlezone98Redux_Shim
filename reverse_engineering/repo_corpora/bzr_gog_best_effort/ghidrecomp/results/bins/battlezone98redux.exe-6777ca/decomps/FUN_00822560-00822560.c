
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00822560(int param_1,int *param_2,int *param_3)

{
  int iVar1;
  float10 fVar2;
  float fVar3;
  double dVar4;
  double local_34;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ((DAT_00946740 != 7) || (DAT_0094673c != param_1)) {
    FUN_00821af0();
    DAT_00946758 = DAT_00946768;
    DAT_00946760 = DAT_00946770;
  }
  local_34 = 0.0;
  if (param_3 != (int *)0x0) {
    local_34 = (double)((float)*param_3 * 0.01);
  }
  fVar3 = (float)*param_2 * 0.01;
  if (fVar3 < 1.0) {
    fVar3 = 1.0;
  }
  fVar2 = (float10)FUN_00822d60();
  dVar4 = (double)fVar2 * local_34 * _DAT_00946750;
  if (1.0 < DAT_00946748) {
    if (*(int *)(param_1 + 4) <= DAT_00946744 + 2) {
      DAT_0094673c = 0;
      DAT_00946740 = 0;
      DAT_00946738 = 1;
      goto LAB_00822820;
    }
    FUN_0062e800((float)DAT_00946748,0x3f800000,DAT_00946744 + 1,param_1);
    FUN_00821af0();
  }
  iVar1 = DAT_00946744 + 1;
  DAT_00946740 = 7;
  DAT_0094673c = param_1;
  DAT_00946738 = 0;
  local_14 = (float)DAT_00946758;
  local_c = (float)DAT_00946760;
  fVar2 = (float10)FUN_007855e0(DAT_00946758,DAT_00946760);
  local_10 = (float)fVar2 + fVar3;
  FUN_00821d00(param_1,iVar1,param_2,&local_14);
  fVar2 = (float10)FUN_004c1050();
  DAT_00946758 = (double)fVar2;
  fVar2 = (float10)FUN_004c1050();
  DAT_00946760 = (double)fVar2;
  DAT_00946748 = DAT_00946748 + dVar4;
  DAT_00946768 = DAT_00946778 * dVar4 + DAT_00946768;
  DAT_00946770 = DAT_00946780 * dVar4 + DAT_00946770;
LAB_00822820:
  FUN_0083e885();
  return;
}

