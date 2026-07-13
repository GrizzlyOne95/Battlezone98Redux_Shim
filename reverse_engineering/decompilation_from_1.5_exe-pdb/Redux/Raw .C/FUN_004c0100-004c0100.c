
void __thiscall
FUN_004c0100(undefined4 param_1,undefined4 param_2,int param_3,int param_4,float *param_5,
            float *param_6,undefined4 param_7,ulong *param_8,ulong param_9,int param_10,
            undefined4 param_11,int param_12,int param_13)

{
  float fVar1;
  int iVar2;
  int iVar3;
  
  FUN_00689ab0(param_8,param_7,param_5,param_6,param_1);
  iVar3 = (int)((float)param_3 - ((float)param_12 * *param_5) / 2.0);
  iVar2 = (int)((float)param_4 - ((float)param_13 * *param_6) / 2.0);
  *param_5 = (float)iVar3 + *param_5;
  *param_6 = (float)iVar2 + *param_6;
  if (-1 < param_10) {
    fVar1 = DAT_00920ef4;
    DAT_00920ef4 = DAT_00920ef4 + 0.01;
    FUN_0068afb0(param_2,iVar3,iVar2,(int)*param_5,(int)*param_6,param_10,param_11);
    DAT_00920ef4 = fVar1;
  }
  std::_Init_atomic_counter(param_8,param_9);
  FUN_00689d10(param_8,param_2,iVar3,iVar2,param_7);
  return;
}

