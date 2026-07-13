/*
 * Entry: 004c3285
 * Name: ColorFade::SetFade
 * Namespace: ColorFade
 * Signature: void SetFade(ColorFade * this, float param_1, float param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
ColorFade::SetFade(ColorFade *this,float param_1,float param_2,int param_3,int param_4,int param_5)

{
  float fVar1;
  
  fVar1 = this->ratio;
  (this->fade).r = (uchar)param_3;
  (this->fade).g = (uchar)param_4;
  this->ratio = param_1 + fVar1;
  (this->fade).b = (uchar)param_5;
  this->rate = param_2;
  return;
}
