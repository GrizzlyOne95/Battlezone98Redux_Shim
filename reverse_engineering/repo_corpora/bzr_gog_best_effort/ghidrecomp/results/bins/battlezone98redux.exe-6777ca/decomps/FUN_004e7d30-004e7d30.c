
void __thiscall FUN_004e7d30(int param_1,float param_2)

{
  float10 fVar1;
  undefined4 local_c;
  
  *(float *)(param_1 + 0x34) = *(float *)(param_1 + 0x34) - param_2 * 4.9;
  FUN_005bd060(param_2);
  *(float *)(param_1 + 0x34) = *(float *)(param_1 + 0x34) - param_2 * 4.9;
  fVar1 = (float10)FUN_0045c420(*(undefined4 *)(param_1 + 0x30),*(undefined4 *)(param_1 + 0x34),
                                *(undefined4 *)(param_1 + 0x38));
  *(float *)(param_1 + 0x20) = (float)fVar1;
  if (*(float *)(param_1 + 0x20) <= 0.0) {
    local_c = 1e+30;
  }
  else {
    local_c = 1.0 / *(float *)(param_1 + 0x20);
  }
  *(float *)(param_1 + 0x24) = local_c;
  FUN_005856a0();
  return;
}

