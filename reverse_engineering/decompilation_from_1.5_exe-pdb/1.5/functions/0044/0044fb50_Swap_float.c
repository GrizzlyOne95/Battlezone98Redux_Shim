/*
 * Entry: 0044fb50
 * Name: Swap<float>
 * Namespace: Global
 * Signature: void Swap<float>(float * param_1, float * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Swap<float>(float *param_1,float *param_2)

{
  float fVar1;
  
  fVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = fVar1;
  return;
}
