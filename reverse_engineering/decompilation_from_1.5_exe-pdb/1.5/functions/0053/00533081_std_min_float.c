/*
 * Entry: 00533081
 * Name: std::min<float>
 * Namespace: std
 * Signature: float * min<float>(float * param_1, float * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float * __cdecl std::min<float>(float *param_1,float *param_2)

{
  if (*param_1 <= *param_2) {
    param_2 = param_1;
  }
  return param_2;
}
