/*
 * Entry: 0051089d
 * Name: Geom_OrientationScale
 * Namespace: Global
 * Signature: int Geom_OrientationScale(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Geom_OrientationScale(int param_1,int param_2)

{
  int iVar1;
  
  if (param_2 < 1) {
    return 0;
  }
  iVar1 = (param_1 >> 0x10 & 0xffU) * param_2 + 0x80;
  iVar1 = (int)(iVar1 + (iVar1 >> 0x1f & 0xffU)) >> 8;
  if (param_2 <= iVar1) {
    iVar1 = iVar1 - param_2;
  }
  return iVar1;
}
