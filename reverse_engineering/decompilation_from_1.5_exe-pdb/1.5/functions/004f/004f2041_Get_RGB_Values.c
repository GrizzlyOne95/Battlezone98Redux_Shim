/*
 * Entry: 004f2041
 * Name: Get_RGB_Values
 * Namespace: Global
 * Signature: void Get_RGB_Values(long param_1, float * param_2, float * param_3, float * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Get_RGB_Values(long param_1,float *param_2,float *param_3,float *param_4)

{
  *param_2 = Float_Pal[param_1][0];
  *param_3 = Float_Pal[param_1][1];
  *param_4 = Float_Pal[param_1][2];
  return;
}
