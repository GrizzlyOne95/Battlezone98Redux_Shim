
void FUN_0044b940(double *param_1,double *param_2,double *param_3,float param_4)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  
  dVar1 = param_3[1];
  dVar2 = param_2[1];
  dVar3 = param_2[1];
  dVar4 = param_3[2];
  dVar5 = param_2[2];
  dVar6 = param_2[2];
  *param_1 = (double)param_4 * (*param_3 - *param_2) + *param_2;
  param_1[1] = (double)param_4 * (dVar1 - dVar2) + dVar3;
  param_1[2] = (double)param_4 * (dVar4 - dVar5) + dVar6;
  FUN_0083e885();
  return;
}

