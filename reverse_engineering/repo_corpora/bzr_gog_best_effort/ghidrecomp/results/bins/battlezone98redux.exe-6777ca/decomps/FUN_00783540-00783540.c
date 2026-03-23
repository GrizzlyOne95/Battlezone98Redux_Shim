
void FUN_00783540(uint *param_1,float *param_2)

{
  float fVar1;
  
  fVar1 = param_2[2] * DAT_02cc50e4;
  *param_1 = (int)(*param_2 * DAT_02cc50e4) & 0xfffffffc;
  param_1[1] = (int)fVar1 & 0xfffffffc;
  return;
}

