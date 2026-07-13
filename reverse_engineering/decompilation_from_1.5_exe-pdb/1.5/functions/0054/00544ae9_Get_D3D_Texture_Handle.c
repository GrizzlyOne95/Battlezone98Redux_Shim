/*
 * Entry: 00544ae9
 * Name: Get_D3D_Texture_Handle
 * Namespace: Global
 * Signature: IDirect3DTexture9 * Get_D3D_Texture_Handle(TEXTURE * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

IDirect3DTexture9 * __cdecl Get_D3D_Texture_Handle(TEXTURE *param_1,int param_2)

{
  ulong uVar1;
  long lVar2;
  IDirect3DTexture9 *pIVar3;
  TEXTURE *unaff_EDI;
  
  uVar1 = Get_Frame_Count();
  if ((textureCount == 0) && ((D3IniFlags & 0xc000U) != 0)) {
    PreloadTextures();
  }
  lVar2 = FindTextureIndex(unaff_EDI);
  if (cache[lVar2].texture == param_1) {
    D3DTextHits = D3DTextHits + 1;
    cache[lVar2].timeStamp = uVar1;
    pIVar3 = cache[lVar2].lpD3DTex;
  }
  else {
    if ((D3IniFlags & 0x8000U) != 0) {
      cacheName(param_1);
      Trace("Texture not preloaded: %s %dx%d\n");
    }
    pIVar3 = Make_Texture_Handle(lVar2,(TEXTURE *)param_2,0,(TEXTURE **)unaff_EDI);
  }
  return pIVar3;
}
