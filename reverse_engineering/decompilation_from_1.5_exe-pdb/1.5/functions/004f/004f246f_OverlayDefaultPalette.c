/*
 * Entry: 004f246f
 * Name: OverlayDefaultPalette
 * Namespace: Global
 * Signature: void OverlayDefaultPalette(long param_1, long param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl OverlayDefaultPalette(long param_1,long param_2,long param_3)

{
  int iVar1;
  undefined4 *puVar2;
  RGB *pRVar3;
  RGB local_304 [256];
  
  puVar2 = (undefined4 *)&Default_Palette;
  pRVar3 = local_304;
  for (iVar1 = 0xc0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *(undefined4 *)pRVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    pRVar3 = (RGB *)&pRVar3[1].g;
  }
  ApplyGammaToPalette(local_304,param_1,param_2,0);
  (*Device.VideoMode.OverlayPalette)(&Device,local_304);
  return;
}
