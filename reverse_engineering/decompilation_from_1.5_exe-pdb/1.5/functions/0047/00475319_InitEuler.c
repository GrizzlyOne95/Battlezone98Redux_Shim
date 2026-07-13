/*
 * Entry: 00475319
 * Name: InitEuler
 * Namespace: Global
 * Signature: void InitEuler(EULER * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InitEuler(EULER *param_1)

{
  param_1->mass = 0.0;
  param_1->mass_inv = 1e+30;
  param_1->v_mag_inv = 1e+30;
  param_1->v_mag = 0.0;
  param_1->I = 1.0;
  param_1->k_i = 0.0;
  (param_1->Alpha).x = 0.0;
  (param_1->Alpha).y = 0.0;
  (param_1->Alpha).z = 0.0;
  (param_1->Accel).x = 0.0;
  (param_1->Accel).y = 0.0;
  (param_1->Accel).z = 0.0;
  (param_1->omega).x = 0.0;
  (param_1->omega).y = 0.0;
  (param_1->omega).z = 0.0;
  (param_1->v).x = 0.0;
  (param_1->v).y = 0.0;
  (param_1->v).z = 0.0;
  return;
}
