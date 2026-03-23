
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_0068a0c0(float param_1)

{
  float10 fVar1;
  float fVar2;
  
  fVar2 = DAT_02ceb81c * param_1 + _DAT_02ceb820;
  if (0.0 <= fVar2) {
    if (fVar2 <= 1.0) {
      fVar1 = (float10)fVar2;
    }
    else {
      fVar1 = (float10)1;
    }
  }
  else {
    fVar1 = (float10)0;
  }
  return fVar1;
}

