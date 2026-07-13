/*
 * Entry: 004b4c1f
 * Name: TurretTank::PackTempState
 * Namespace: TurretTank
 * Signature: void PackTempState(TurretTank * this, void * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTank::PackTempState(TurretTank *this,void *param_1,uint *param_2)

{
  int iVar1;
  undefined1 extraout_AL;
  undefined1 extraout_AL_00;
  
  *param_2 = *param_2 + 3;
  iVar1 = this->_padding_;
  if (iVar1 == 0) {
    *(undefined1 *)((int)param_1 + 2) = 3;
  }
  else if (iVar1 == 1) {
    *(undefined1 *)((int)param_1 + 2) = 1;
  }
  else if (iVar1 == 2) {
    *(undefined1 *)((int)param_1 + 2) = 2;
  }
  else if (iVar1 == 3) {
    *(undefined1 *)((int)param_1 + 2) = 0;
  }
  if (((*(byte *)(this->_padding_ + 0x14) & 0x10) != 0) &&
     ((UserProfilePtr->playOption & 0x10) != 0)) {
    *(byte *)((int)param_1 + 2) = *(byte *)((int)param_1 + 2) | 0x40;
  }
  if ((this->_padding_ != 0) || (this->_padding_ != 0)) {
    *(byte *)((int)param_1 + 2) = *(byte *)((int)param_1 + 2) | 0x80;
  }
  if (0.0 < (float)this->_padding_) {
    ceil((double)((float)this->_padding_ * 255.0));
    _ftol2();
    *(undefined1 *)param_1 = extraout_AL;
  }
  else {
    *(undefined1 *)param_1 = 0;
  }
  if (0.0 < (float)this->_padding_) {
    ceil((double)((float)this->_padding_ * 255.0));
    _ftol2();
    *(undefined1 *)((int)param_1 + 1) = extraout_AL_00;
  }
  else {
    *(undefined1 *)((int)param_1 + 1) = 0;
  }
  if (this->_padding_ == 0) {
    HoverCraft::PackTempState((HoverCraft *)this,(void *)((int)param_1 + 3),param_2);
  }
  return;
}
