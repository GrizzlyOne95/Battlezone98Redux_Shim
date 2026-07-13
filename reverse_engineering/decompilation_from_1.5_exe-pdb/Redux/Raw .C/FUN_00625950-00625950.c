
void FUN_00625950(float *param_1,undefined4 param_2,undefined2 param_3)

{
  float10 fVar1;
  float10 fVar2;
  float10 fVar3;
  
  fVar1 = (float10)FUN_00625810((undefined2)param_2);
  fVar2 = (float10)FUN_00625810(param_2._2_2_);
  fVar3 = (float10)FUN_00625810(param_3);
  *param_1 = (float)fVar1;
  param_1[1] = (float)fVar2;
  param_1[2] = (float)fVar3;
  FUN_0083e885();
  return;
}

