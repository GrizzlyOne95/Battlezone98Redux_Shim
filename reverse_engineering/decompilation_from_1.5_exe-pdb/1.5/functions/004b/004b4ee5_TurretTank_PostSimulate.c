/*
 * Entry: 004b4ee5
 * Name: TurretTank::PostSimulate
 * Namespace: TurretTank
 * Signature: void PostSimulate(TurretTank * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTank::PostSimulate(TurretTank *this,float param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  if (this->_padding_ == 0) {
    HoverCraft::PostSimulate((HoverCraft *)this,param_1);
  }
  else {
    if ((*(uint *)(this->_padding_ + 0x14) & 0x200) == 0) {
      fVar1 = (float)this->_padding_ - (float)View_Record.MainCam.View_Pyramid[0].x;
      fVar2 = (float)this->_padding_ - (float)View_Record.MainCam.View_Pyramid[0].y;
      fVar3 = (float)this->_padding_ - (float)View_Record.MainCam.View_Pyramid[0].z;
      if (22500.0 <= fVar3 * fVar3 + fVar2 * fVar2 + fVar1 * fVar1) {
        HoverCraft::CleanupSound((HoverCraft *)this);
      }
      else {
        HoverCraft::UpdateSound((HoverCraft *)this,param_1);
      }
    }
    Craft::PostSimulate((Craft *)this,param_1);
  }
  return;
}
