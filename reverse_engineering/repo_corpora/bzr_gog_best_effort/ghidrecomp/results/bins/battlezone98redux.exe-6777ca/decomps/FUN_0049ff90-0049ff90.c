
void __thiscall FUN_0049ff90(undefined4 param_1,undefined4 param_2,int *param_3,undefined4 param_4)

{
  float fVar1;
  
  fVar1 = DAT_00920ef4;
  DAT_00920ef4 = DAT_00920ef4 + 0.04;
  FUN_0068ca30(DAT_00917580,param_4,DAT_0260d734,*param_3,param_3[1],(param_3[2] - *param_3) + 1,
               (param_3[3] - param_3[1]) + 1,1,0,param_1);
  DAT_00920ef4 = fVar1;
  return;
}

