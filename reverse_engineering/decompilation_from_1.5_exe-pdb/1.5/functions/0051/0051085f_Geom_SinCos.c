/*
 * Entry: 0051085f
 * Name: Geom_SinCos
 * Namespace: Global
 * Signature: void Geom_SinCos(int param_1, float * param_2, float * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Geom_SinCos(int param_1,float *param_2,float *param_3)

{
  uint uVar1;
  
  uVar1 = (int)((param_1 >> 6) + (param_1 >> 0x1f & 0xffU)) >> 8 & 0x3ff;
  *param_3 = costable[uVar1];
  *param_2 = costable[0x100 - uVar1 & 0x3ff];
  return;
}
