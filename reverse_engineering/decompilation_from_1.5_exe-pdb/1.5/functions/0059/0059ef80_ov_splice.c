/*
 * Entry: 0059ef80
 * Name: _ov_splice
 * Namespace: Global
 * Signature: void _ov_splice(float * * param_1, float * * param_2, int param_3, int param_4, int param_5, int param_6, float * param_7, float * param_8)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
_ov_splice(float **param_1,float **param_2,int param_3,int param_4,int param_5,int param_6,
          float *param_7,float *param_8)

{
  float *pfVar1;
  float *pfVar2;
  int local_14;
  int local_10;
  int local_c;
  float *local_8;
  
  local_8 = param_7;
  local_c = param_3;
  if (param_4 < param_3) {
    local_c = param_4;
    local_8 = param_8;
  }
  for (local_14 = 0; (local_14 < param_5 && (local_14 < param_6)); local_14 = local_14 + 1) {
    pfVar1 = param_2[local_14];
    pfVar2 = param_1[local_14];
    for (local_10 = 0; local_10 < local_c; local_10 = local_10 + 1) {
      pfVar2[local_10] =
           pfVar1[local_10] * (1.0 - local_8[local_10] * local_8[local_10]) +
           pfVar2[local_10] * local_8[local_10] * local_8[local_10];
    }
  }
  for (; local_14 < param_6; local_14 = local_14 + 1) {
    pfVar1 = param_1[local_14];
    for (local_10 = 0; local_10 < local_c; local_10 = local_10 + 1) {
      pfVar1[local_10] = pfVar1[local_10] * local_8[local_10] * local_8[local_10];
    }
  }
  return;
}
