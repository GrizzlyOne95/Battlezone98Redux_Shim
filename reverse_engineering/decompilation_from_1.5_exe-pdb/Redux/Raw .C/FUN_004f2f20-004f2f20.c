
void FUN_004f2f20(undefined4 param_1,int *param_2,int *param_3,int *param_4,undefined4 param_5)

{
  float fVar1;
  float fVar2;
  undefined8 uVar3;
  
  uVar3 = FUN_00689eb0();
  fVar2 = (float)((ulonglong)uVar3 >> 0x20);
  fVar1 = (float)uVar3;
  FUN_0068afb0(param_1,(int)((float)*param_3 - fVar1 * 2.0),(int)((float)param_3[1] - fVar2 * 2.0),
               (int)((float)*param_3 + fVar1 * 2.0),(int)((float)param_3[1] + fVar2 * 2.0),param_5,0
              );
  if (param_4[1] != -1) {
    FUN_0068af40(param_1,*param_3,param_3[1],(int)((float)*param_2 - fVar1 * 50.0),param_3[1],
                 param_5,0);
    FUN_0068af40(param_1,(int)((float)*param_2 - fVar1 * 50.0),param_3[1],*param_4,param_4[1],
                 param_5,0);
    FUN_0068afb0(param_1,(int)((float)*param_4 - fVar1 * 2.0),(int)((float)param_4[1] - fVar1 * 2.0)
                 ,(int)((float)*param_4 + fVar1 * 2.0),(int)((float)param_4[1] + fVar1 * 2.0),
                 param_5,0);
  }
  return;
}

