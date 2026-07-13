/*
 * Entry: 00543b3c
 * Name: releaseTexture
 * Namespace: Global
 * Signature: void releaseTexture(D3DCACHEENTRY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl releaseTexture(D3DCACHEENTRY *param_1)

{
  int *piVar1;
  undefined4 *unaff_ESI;
  
  if (unaff_ESI[3] != 0) {
    D3DTextMem = D3DTextMem - ((uint)unaff_ESI[1] >> 0xc & 0xfff) * (unaff_ESI[1] & 0xfff);
    piVar1 = (int *)unaff_ESI[3];
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 8))(piVar1);
    }
    unaff_ESI[3] = 0;
    *unaff_ESI = 0x7fffffff;
  }
  return;
}
