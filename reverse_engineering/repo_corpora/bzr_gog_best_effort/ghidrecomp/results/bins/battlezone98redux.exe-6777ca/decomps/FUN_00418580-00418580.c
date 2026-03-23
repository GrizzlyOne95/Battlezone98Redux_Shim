
undefined8 FUN_00418580(int *param_1,undefined4 param_2,float param_3,float param_4)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  float10 fVar4;
  
  iVar1 = *param_1;
  fVar3 = (float10)FUN_00417930(param_2);
  iVar2 = param_1[1];
  fVar4 = (float10)FUN_00417950(param_2);
  return CONCAT44((int)((float)iVar2 + (float)fVar4 * param_3),
                  (int)((float)iVar1 + (float)fVar3 * param_3 * param_4));
}

