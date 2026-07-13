/*
 * Entry: 0054d723
 * Name: CloseMenu
 * Namespace: Global
 * Signature: void CloseMenu(_menu * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CloseMenu(_menu *param_1)

{
  if (mInfo.background != (TEXTURE *)0x0) {
    UnlockRDItem(mInfo.backgroundName,0,0);
    mInfo.background = (TEXTURE *)0x0;
  }
  Graphic_Buffer_Close(&mInfo.bgGB);
  if (mInfo.hBitmap != (HBITMAP__ *)0x0) {
    DeleteObject(mInfo.hBitmap);
    mInfo.hBitmap = (HBITMAP__ *)0x0;
  }
  Graphic_Buffer_Close(&mInfo.textGB);
  return;
}
