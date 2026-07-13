/*
 * Entry: 0056f7bb
 * Name: ShellBitmap::~ShellBitmap
 * Namespace: ShellBitmap
 * Signature: void ~ShellBitmap(ShellBitmap * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ShellBitmap::~ShellBitmap(ShellBitmap *this)

{
  DeleteObject(this->pBitmapPal);
  this->pBitmapPal = (HPALETTE__ *)0x0;
  if (this->bmBits != (void *)0x0) {
    free(this->bmBits);
  }
  this->bmBits = (void *)0x0;
  if (this->bmInfo != (tagBITMAPINFO *)0x0) {
    free(this->bmInfo);
  }
  this->bmInfo = (tagBITMAPINFO *)0x0;
  return;
}
