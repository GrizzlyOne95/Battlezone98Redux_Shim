
void __thiscall FUN_006885c0(undefined4 param_1,int param_2,float param_3)

{
  int iVar1;
  
  if (param_3 < 0.5) {
    param_3 = 0.5;
  }
  if (100.0 < param_3) {
    param_3 = 100.0;
  }
  *(float *)(param_2 + 0x30) = param_3;
  iVar1 = FUN_00688330(*(undefined4 *)(param_2 + 0x38),param_1);
  param_3 = (float)iVar1 * 0.5 * param_3;
  *(float *)(param_2 + 8) = param_3 / (*(float *)(param_2 + 0x2c) * *(float *)(param_2 + 0x28));
  *(float *)(param_2 + 0xc) = -param_3 / *(float *)(param_2 + 0x28);
  FUN_00688760(param_2,(int)*(float *)(param_2 + 0x14),(int)*(float *)(param_2 + 0x18),
               (int)*(float *)(param_2 + 0x1c),(int)*(float *)(param_2 + 0x20));
  return;
}

