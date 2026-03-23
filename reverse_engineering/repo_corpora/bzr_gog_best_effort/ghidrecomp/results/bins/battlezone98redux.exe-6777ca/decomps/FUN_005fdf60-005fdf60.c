
void FUN_005fdf60(undefined4 param_1,float param_2,float *param_3)

{
  int iVar1;
  float10 fVar2;
  float10 fVar3;
  
  fVar2 = (float10)FUN_00822da0();
  iVar1 = FUN_004b75c0();
  fVar3 = (float10)FUN_00822970((float)iVar1 + (float)fVar2 * 0.5);
  *param_3 = (float)fVar3 * param_2 + *param_3;
  iVar1 = FUN_004b75c0();
  fVar2 = (float10)FUN_00822970((float)iVar1 + (float)fVar2 * 0.5 + 17.59);
  param_3[2] = (float)fVar2 * param_2 + param_3[2];
  return;
}

