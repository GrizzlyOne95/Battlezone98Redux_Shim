/*
 * Entry: 004f89ee
 * Name: Pow
 * Namespace: Global
 * Signature: float Pow(double param_1, double param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Pow(double param_1,double param_2)

{
  float10 fVar1;
  float10 fVar2;
  
  if (param_1 <= 0.001) {
    return 0.0;
  }
  fVar1 = (float10)param_1;
  param_1._0_4_ = SUB84((double)((float10)param_2 * fVar1 + (float10)Float2Int),0);
  fVar2 = (float10)fscale((float10)1,(float10)param_1._0_4_);
  fVar1 = (float10)f2xm1((float10)param_2 * fVar1 - (float10)param_1._0_4_);
  return (float)(fVar2 * (fVar1 + (float10)1));
}
