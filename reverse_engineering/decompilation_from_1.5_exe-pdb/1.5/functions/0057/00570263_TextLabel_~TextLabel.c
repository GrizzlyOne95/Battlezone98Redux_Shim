/*
 * Entry: 00570263
 * Name: TextLabel::~TextLabel
 * Namespace: TextLabel
 * Signature: void ~TextLabel(TextLabel * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TextLabel::~TextLabel(TextLabel *this)

{
  DeleteObject(this->hTextFont);
  DeleteObject(this->hTextBack);
  this->hTextBack = (HBITMAP__ *)0x0;
  return;
}
