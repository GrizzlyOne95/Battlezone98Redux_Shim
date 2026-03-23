
undefined8 FUN_00418610(int *param_1,float param_2,float param_3,float param_4)

{
  int iVar1;
  float10 fVar2;
  float fVar3;
  int local_20;
  
  fVar3 = param_2 - (float)param_1[1];
  if ((float)*param_1 <= 1024.0) {
    iVar1 = *param_1;
    fVar2 = (float10)FUN_00417970(param_3 * param_3 - fVar3 * fVar3);
    fVar3 = (float)iVar1 + (float)fVar2 * param_4;
  }
  else {
    iVar1 = *param_1;
    fVar2 = (float10)FUN_00417970(param_3 * param_3 - fVar3 * fVar3);
    fVar3 = (float)iVar1 - (float)fVar2 * param_4;
  }
  local_20 = (int)fVar3;
  return CONCAT44((int)param_2,local_20);
}

