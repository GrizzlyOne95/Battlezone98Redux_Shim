/*
 * Entry: 00406001
 * Name: std::swap<float>
 * Namespace: std
 * Signature: void swap<float>(float * param_1, float * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::swap<float>(float *param_1,float *param_2)

{
  float fVar1;
  
  if (param_1 != param_2) {
    fVar1 = *param_1;
    *param_1 = *param_2;
    *param_2 = fVar1;
  }
  return;
}
