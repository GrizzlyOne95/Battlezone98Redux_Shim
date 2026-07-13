/*
 * Entry: 00544562
 * Name: Replace_Entry
 * Namespace: Global
 * Signature: D3DCACHEENTRY * Replace_Entry(long param_1, D3DCACHEENTRY * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

D3DCACHEENTRY * __cdecl Replace_Entry(long param_1,D3DCACHEENTRY *param_2)

{
  undefined4 *in_EAX;
  int iVar1;
  long lVar2;
  D3DCACHEENTRY *pDVar3;
  int in_ECX;
  TEXTURE *unaff_ESI;
  D3DCACHEENTRY *unaff_EDI;
  D3DCACHEENTRY *pDVar4;
  
  if (in_ECX + 1 < textureCount) {
    memmove(cache + in_ECX,cache + in_ECX + 1,(textureCount - in_ECX) * 0x18 - 0x18);
  }
  textureCount = textureCount + -1;
  iVar1 = D3D_Load_Texture_To_Entry(unaff_EDI);
  pDVar3 = (D3DCACHEENTRY *)0x0;
  if (iVar1 != 0) {
    lVar2 = FindTextureIndex(unaff_ESI);
    if (lVar2 < textureCount) {
      memmove(cache + lVar2 + 1,cache + lVar2,(textureCount - lVar2) * 0x18);
    }
    textureCount = textureCount + 1;
    pDVar3 = cache + lVar2;
    pDVar4 = pDVar3;
    for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
      pDVar4->texture = (TEXTURE *)*in_EAX;
      in_EAX = in_EAX + 1;
      pDVar4 = (D3DCACHEENTRY *)&pDVar4->TransWidthHeight;
    }
  }
  return pDVar3;
}
