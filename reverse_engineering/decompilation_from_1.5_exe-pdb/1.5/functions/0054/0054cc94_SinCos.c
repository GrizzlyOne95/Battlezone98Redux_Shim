/*
 * Entry: 0054cc94
 * Name: SinCos
 * Namespace: Global
 * Signature: SINCOS SinCos(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SINCOS __cdecl SinCos(float param_1)

{
  float10 fVar1;
  SINCOS SVar2;
  float10 fVar3;
  
  fVar1 = (float10)fcos((float10)param_1);
  fVar3 = (float10)fsin((float10)param_1);
  SVar2.Cos = (float)fVar1;
  SVar2.Sin = (float)fVar3;
  return SVar2;
}
