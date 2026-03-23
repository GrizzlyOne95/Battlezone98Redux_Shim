
void FUN_0083c185(int *param_1,int *param_2,int param_3)

{
  uint *puVar1;
  undefined4 uVar2;
  uint uVar3;
  
  FUN_0083c667(param_1,param_2);
  if (*param_2 == 1) {
    FUN_0083c9f3(param_1,param_3,1);
    goto LAB_0083c260;
  }
  if (*param_2 < 2) {
    return;
  }
  if (*param_2 < 4) {
    uVar3 = (uint)(*param_2 == 2);
    uVar2 = 2;
  }
  else {
    if (*param_2 == 4) {
      FUN_0083c5ff(param_1,1,param_3,param_2[2]);
      goto LAB_0083c260;
    }
    if (*param_2 == 5) {
      uVar2 = FUN_0083ca81(param_1,*(undefined8 *)(param_2 + 2));
      FUN_0083c5ff(param_1,1,param_3,uVar2);
      goto LAB_0083c260;
    }
    if (*param_2 == 0xb) {
      puVar1 = (uint *)(*(int *)(*param_1 + 0xc) + param_2[2] * 4);
      *puVar1 = *puVar1 ^ (param_3 << 6 ^ *(uint *)(*(int *)(*param_1 + 0xc) + param_2[2] * 4)) &
                          0x3fc0;
      goto LAB_0083c260;
    }
    if (*param_2 != 0xc) {
      return;
    }
    if (param_3 == param_2[2]) goto LAB_0083c260;
    uVar3 = param_2[2];
    uVar2 = 0;
  }
  FUN_0083c5d2(param_1,uVar2,param_3,uVar3);
LAB_0083c260:
  param_2[2] = param_3;
  *param_2 = 0xc;
  return;
}

