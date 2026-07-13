
void FUN_0062d150(undefined4 *param_1,uint param_2,short param_3,undefined4 param_4,
                 undefined4 param_5)

{
  if (param_1[0x20] != 0) {
    FUN_0062d150(param_1[0x20],param_2 + 1,param_3,param_4,param_5);
  }
  if ((param_1[0x1f] != 0) && (1 < param_2)) {
    FUN_0062d150(param_1[0x1f],param_2 + 1,param_3,param_4,param_5);
  }
  *(undefined2 *)(param_1 + 4) = 1;
  *param_1 = 0;
  *(short *)((int)param_1 + 0x12) = *(short *)((int)param_1 + 0x12) - param_3;
  if (*(short *)((int)param_1 + 0x12) == 0) {
    FUN_0062cfe0(param_1);
  }
  return;
}

