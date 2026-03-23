
double * __thiscall
FUN_005b2740(double *param_1,double param_2,double param_3,double param_4,double param_5,
            double param_6,double param_7,undefined4 param_8)

{
  int iVar1;
  undefined4 uVar2;
  double dVar3;
  
  *param_1 = 1.0 / param_2;
  param_1[1] = 1.0 / param_3;
  param_1[3] = param_6;
  param_1[2] = param_4;
  dVar3 = floor((param_7 - param_6) * *param_1);
  iVar1 = FUN_0046eaf0(dVar3);
  *(int *)((int)param_1 + 0x24) = iVar1 + 1;
  dVar3 = floor((param_5 - param_4) * param_1[1]);
  iVar1 = FUN_0046eaf0(dVar3);
  *(int *)(param_1 + 5) = iVar1 + 1;
  *(undefined4 *)(param_1 + 4) = param_8;
  uVar2 = FUN_0083d92c();
  *(undefined4 *)(param_1 + 6) = uVar2;
  uVar2 = FUN_0083d92c();
  *(undefined4 *)((int)param_1 + 0x34) = uVar2;
  FUN_005b2bd0();
  return param_1;
}

