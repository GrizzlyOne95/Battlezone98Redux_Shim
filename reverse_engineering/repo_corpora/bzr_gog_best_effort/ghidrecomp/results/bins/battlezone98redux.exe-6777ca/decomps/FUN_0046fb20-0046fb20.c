
void __thiscall FUN_0046fb20(int param_1,undefined4 *param_2)

{
  float10 fVar1;
  float local_c;
  
  *(undefined4 *)(param_1 + 300) = *param_2;
  *(undefined4 *)(param_1 + 0x130) = param_2[1];
  *(undefined4 *)(param_1 + 0x134) = param_2[2];
  fVar1 = (float10)FUN_0045c420(*(undefined4 *)(param_1 + 300),*(undefined4 *)(param_1 + 0x130),
                                *(undefined4 *)(param_1 + 0x134));
  *(float *)(param_1 + 0x11c) = (float)fVar1;
  if (*(float *)(param_1 + 0x11c) <= 0.0) {
    local_c = 1e+30;
  }
  else {
    local_c = 1.0 / *(float *)(param_1 + 0x11c);
  }
  *(float *)(param_1 + 0x120) = local_c;
  return;
}

