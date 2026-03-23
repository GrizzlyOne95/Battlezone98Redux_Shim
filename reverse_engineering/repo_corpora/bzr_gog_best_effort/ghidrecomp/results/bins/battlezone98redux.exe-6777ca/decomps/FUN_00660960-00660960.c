
void __thiscall FUN_00660960(int param_1,undefined4 *param_2,undefined4 param_3,char param_4)

{
  undefined4 *puVar1;
  float10 fVar2;
  int local_c;
  
  fVar2 = (float10)FUN_00456080(0x3f800000,param_3);
  fVar2 = (float10)FUN_0044fb20(0,(float)fVar2);
  if (param_4 == '\0') {
    local_c = *(int *)(param_1 + 0x1b0);
  }
  else {
    local_c = *(int *)(param_1 + 0x1ac);
  }
  if ((((0 < local_c) && (DAT_008eaad8 != 9)) && (DAT_008eaad8 != 10)) &&
     ((DAT_008fe240 == 1 && (*(uint *)(param_1 + 0x1a8) < param_1 + 0x1a8U)))) {
    puVar1 = *(undefined4 **)(param_1 + 0x1a8);
    *puVar1 = *param_2;
    puVar1[1] = param_2[1];
    puVar1[2] = param_2[2];
    puVar1[3] = param_2[3];
    *(float *)(*(int *)(param_1 + 0x1a8) + 0x10) = (float)fVar2;
    *(char *)(*(int *)(param_1 + 0x1a8) + 0x14) = param_4;
    *(int *)(param_1 + 0x1a8) = *(int *)(param_1 + 0x1a8) + 0x18;
  }
  return;
}

