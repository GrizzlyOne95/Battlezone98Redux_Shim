/*
 * Entry: 0049ec69
 * Name: HoverCraft::PostSimulate
 * Namespace: HoverCraft
 * Signature: void PostSimulate(HoverCraft * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall HoverCraft::PostSimulate(HoverCraft *this,float param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar1 = (float)this->_padding_ - (float)View_Record.MainCam.View_Pyramid[0].x;
  fVar2 = (float)this->_padding_ - (float)View_Record.MainCam.View_Pyramid[0].y;
  fVar3 = (float)this->_padding_ - (float)View_Record.MainCam.View_Pyramid[0].z;
  if (22500.0 <= fVar3 * fVar3 + fVar2 * fVar2 + fVar1 * fVar1) {
    CleanupSound(this);
  }
  else {
    UpdateGimbals(this,param_1);
    UpdateSound(this,param_1);
  }
  Craft::PostSimulate((Craft *)this,param_1);
  return;
}
