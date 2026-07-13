/*
 * Entry: 0057190a
 * Name: AnimButton::~AnimButton
 * Namespace: AnimButton
 * Signature: void ~AnimButton(AnimButton * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AnimButton::~AnimButton(AnimButton *this)

{
  movie_close(this);
  this->hParentHwnd = (HWND__ *)0x0;
  return;
}
