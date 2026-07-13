/*
 * Entry: 0044eb50
 * Name: Intersects
 * Namespace: Global
 * Signature: bool Intersects(float param_1, float param_2, float param_3, float param_4, float param_5, float param_6, float param_7, float param_8, float * param_9, float * param_10)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl
Intersects(float param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
          float param_7,float param_8,float *param_9,float *param_10)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar2 = param_3 - param_1;
  if (fVar2 == 0.0) {
    fVar2 = 1e-05;
  }
  fVar2 = (param_4 - param_2) / fVar2;
  fVar1 = param_7 - param_5;
  if (fVar1 == 0.0) {
    fVar1 = 1e-05;
  }
  fVar1 = (param_8 - param_6) / fVar1;
  fVar5 = param_2 - fVar2 * param_1;
  fVar3 = param_6 - fVar1 * param_5;
  fVar4 = fVar2 - fVar1;
  if (fVar4 == 0.0) {
    fVar4 = 1e-05;
  }
  *param_9 = (fVar3 - fVar5) * (1.0 / fVar4);
  fVar2 = (fVar3 * fVar2 - fVar1 * fVar5) * (1.0 / fVar4);
  *param_10 = fVar2;
  if (param_7 != param_5) {
    if (*param_9 < param_5) {
      return false;
    }
    fVar1 = *param_9;
    if ((!NAN(param_7) && !NAN(fVar1)) && param_7 < fVar1 != (param_7 == fVar1)) {
      return false;
    }
  }
  if (param_8 != param_6) {
    if (fVar2 < param_6) {
      return false;
    }
    if (param_8 <= fVar2) {
      return false;
    }
  }
  return true;
}
