/*
 * Entry: 004ebc72
 * Name: DeleteNotepad
 * Namespace: Global
 * Signature: void DeleteNotepad(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DeleteNotepad(void)

{
  HGDIOBJ pvVar1;
  
  Graphic_Buffer_Close(&np.TextGB);
  Graphic_Buffer_Close(&np.TextureGB);
  if (np.DC != (HDC__ *)0x0) {
    pvVar1 = GetStockObject(0xd);
    SelectObject((HDC)np.DC,pvVar1);
    pvVar1 = GetStockObject(5);
    SelectObject((HDC)np.DC,pvVar1);
    DeleteDC((HDC)np.DC);
  }
  if (np.Texture != (TEXTURE *)0x0) {
    UnlockRDItem(np.TextureName,0,4);
  }
  if (np.TextBitmap != (HBITMAP__ *)0x0) {
    DeleteObject(np.TextBitmap);
  }
  if (np.Font != (HFONT__ *)0x0) {
    DeleteObject(np.Font);
  }
  memset(&np,0,0xa4);
  return;
}
