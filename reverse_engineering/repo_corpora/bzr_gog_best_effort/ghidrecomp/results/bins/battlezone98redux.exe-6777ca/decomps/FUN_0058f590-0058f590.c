
float10 FUN_0058f590(float *param_1)

{
  float10 fVar1;
  float10 fVar2;
  undefined8 uVar3;
  
  fVar1 = (float10)FUN_0058bec0(param_1[4]);
  if ((float)fVar1 == 99999.0) {
    fVar1 = (float10)3.4028235e+38;
  }
  else {
    fVar1 = (float10)FUN_00447ed0(DAT_02a13c7c,*param_1 * DAT_02cc50e0 + 1.0,
                                  param_1[2] * DAT_02cc50e0 - 1.0);
    fVar2 = (float10)FUN_00447ed0(DAT_02a13c80,param_1[1] * DAT_02cc50e0 + 1.0,
                                  param_1[3] * DAT_02cc50e0 - 1.0);
    uVar3 = FUN_00444e40((float)fVar1,(float)fVar2,DAT_02a13c7c,DAT_02a13c80);
    fVar1 = (float10)FUN_00444e70(uVar3,uVar3);
  }
  return fVar1;
}

