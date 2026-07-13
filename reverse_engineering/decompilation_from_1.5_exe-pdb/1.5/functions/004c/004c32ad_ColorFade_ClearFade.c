/*
 * Entry: 004c32ad
 * Name: ColorFade::ClearFade
 * Namespace: ColorFade
 * Signature: void ClearFade(ColorFade * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ColorFade::ClearFade(ColorFade *this)

{
  this->ratio = 0.0;
  (this->fade).r = '\0';
  this->rate = 0.0;
  (this->fade).g = '\0';
  (this->fade).b = '\0';
  return;
}
