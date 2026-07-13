/*
 * Entry: 00475160
 * Name: Euler_SetMass
 * Namespace: Global
 * Signature: void Euler_SetMass(EULER * param_1, float param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Euler_SetMass(EULER *param_1,float param_2,float param_3)

{
  float fVar1;
  
  param_1->mass = param_2;
  if (0.0001 < param_2) {
    param_1->mass_inv = 1.0 / param_2;
  }
  param_1->I = param_3;
  if (param_3 <= 0.0001) {
    fVar1 = 1e+10;
  }
  else {
    fVar1 = param_2 / param_3;
  }
  param_1->k_i = fVar1;
  return;
}
