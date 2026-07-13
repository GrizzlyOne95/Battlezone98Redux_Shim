/*
 * Entry: 00543b74
 * Name: D3D_Flush_Texture_Cache
 * Namespace: Global
 * Signature: void D3D_Flush_Texture_Cache(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl D3D_Flush_Texture_Cache(void)

{
  IDirect3DTexture9 *pIVar1;
  IDirect3DTexture9 **ppIVar2;
  int local_8;
  
  if (textureCount != 0) {
    local_8 = 0;
    if (0 < textureCount) {
      ppIVar2 = &cache[0].lpD3DTex;
      do {
        pIVar1 = *ppIVar2;
        if (pIVar1 != (IDirect3DTexture9 *)0x0) {
          D3DTextMem = D3DTextMem -
                       (((D3D_CACHE_KEY *)(ppIVar2 + -2))->Key >> 0xc & 0xfff) *
                       (((D3D_CACHE_KEY *)(ppIVar2 + -2))->Key & 0xfff);
          (*pIVar1->lpVtbl->Release)(pIVar1);
          *ppIVar2 = (IDirect3DTexture9 *)0x0;
          ((D3DCACHEENTRY *)(ppIVar2 + -3))->texture = (TEXTURE *)0x7fffffff;
        }
        local_8 = local_8 + 1;
        ppIVar2 = ppIVar2 + 6;
      } while (local_8 < textureCount);
    }
    TexCache_CleanupD3DVideoFlag();
  }
  lastTextPtr = (TEXTURE *)0x0;
  lastTextHandle = (IDirect3DTexture9 *)0x0;
  textureCount = 0;
  cache[0].texture = (TEXTURE *)0x7fffffff;
  if (D3DTextLoads != 0) {
    D3DTextFlushes = D3DTextFlushes + 1;
  }
  D3DTextMem = 0;
  D3DTextMisses = 0;
  D3DTextHits = 0;
  D3DTextLoads = 0;
  return;
}
