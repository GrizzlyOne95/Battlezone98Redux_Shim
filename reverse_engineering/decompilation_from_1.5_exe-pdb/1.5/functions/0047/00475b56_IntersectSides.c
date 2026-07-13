/*
 * Entry: 00475b56
 * Name: IntersectSides
 * Namespace: Global
 * Signature: int IntersectSides(float param_1, float param_2, float param_3, float param_4, float * param_5, float * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
IntersectSides(float param_1,float param_2,float param_3,float param_4,float *param_5,float *param_6
              )

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  if ((param_2 <= -0.0001) || (0.0001 <= param_2)) {
    fVar1 = (param_3 - param_1) * (1.0 / param_2);
    fVar2 = (param_4 - param_1) * (1.0 / param_2);
    fVar3 = fVar2;
    if (fVar2 < fVar1) goto LAB_00475bc7;
  }
  else {
    if (param_1 < param_3) {
      return 0;
    }
    if (param_4 < param_1) {
      return 0;
    }
    fVar1 = -1e+30;
    fVar3 = 1e+30;
  }
  fVar2 = fVar1;
  fVar1 = fVar3;
LAB_00475bc7:
  *param_5 = fVar2;
  *param_6 = fVar1;
  if (*param_6 < 0.0) {
    return 0;
  }
  return 1;
}
