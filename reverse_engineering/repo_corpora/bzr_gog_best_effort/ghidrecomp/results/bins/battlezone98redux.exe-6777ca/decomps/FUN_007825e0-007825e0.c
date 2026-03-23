
void FUN_007825e0(int param_1,int param_2)

{
  float *pfVar1;
  ushort *puVar2;
  
  pfVar1 = (float *)(DAT_02cc50f0 * 0xc + DAT_02cecf70);
  DAT_02cc50f0 = DAT_02cc50f0 + 1;
  *pfVar1 = (float)param_1;
  puVar2 = (ushort *)FUN_00492d60(param_1,param_2);
  pfVar1[1] = (float)(*puVar2 & 0xfff);
  pfVar1[2] = (float)param_2;
  return;
}

