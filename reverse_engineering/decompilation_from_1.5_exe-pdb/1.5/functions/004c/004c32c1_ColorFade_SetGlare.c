/*
 * Entry: 004c32c1
 * Name: ColorFade::SetGlare
 * Namespace: ColorFade
 * Signature: void SetGlare(ColorFade * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ColorFade::SetGlare(ColorFade *this,float param_1)

{
  this->glare = param_1 + this->glare;
  return;
}
