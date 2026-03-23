
void __thiscall
FUN_005946f0(int *param_1,float param_2,float param_3,float param_4,undefined4 param_5,
            undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  if (param_4 * (float)param_1[0x10] < 1.5) {
    param_4 = 1.5 / (float)param_1[0x10];
  }
  (**(code **)(*param_1 + 0x24))(param_2 - param_4,param_3 + param_4,param_5,param_6);
  (**(code **)(*param_1 + 0x24))(param_2 + param_4,param_3 - param_4,param_7,param_8);
  return;
}

