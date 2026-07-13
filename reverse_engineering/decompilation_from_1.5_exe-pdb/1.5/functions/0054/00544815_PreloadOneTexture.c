/*
 * Entry: 00544815
 * Name: PreloadOneTexture
 * Namespace: Global
 * Signature: void PreloadOneTexture(TEXTURE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PreloadOneTexture(TEXTURE *param_1)

{
  TEXTURE *in_EAX;
  long lVar1;
  TEXTURE **unaff_EBX;
  TEXTURE *unaff_ESI;
  
  if (in_EAX != (TEXTURE *)0x0) {
    lVar1 = FindTextureIndex(unaff_ESI);
    if (cache[lVar1].texture != in_EAX) {
      Make_Texture_Handle(lVar1,(TEXTURE *)0x0,0,unaff_EBX);
    }
  }
  return;
}
