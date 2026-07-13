/*
 * Entry: 0051666a
 * Name: FindSendPoints::FindSendPoints
 * Namespace: FindSendPoints
 * Signature: FindSendPoints * FindSendPoints(FindSendPoints * this, AiMission * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

FindSendPoints * __thiscall FindSendPoints::FindSendPoints(FindSendPoints *this,AiMission *param_1)

{
  long *plVar1;
  uint uVar2;
  
  AiProcess::AiProcess((AiProcess *)this,param_1,(GameObject *)0x0);
  uVar2 = grid_columns * grid_rows;
  this->_padding_ = (int)&_vftable_;
  plVar1 = operator_new__(-(uint)((int)((ulonglong)uVar2 * 4 >> 0x20) != 0) |
                          (uint)((ulonglong)uVar2 * 4));
  this->i = 0;
  sendPoints = plVar1;
  if (0 < (int)uVar2) {
    do {
      plVar1[this->i] = -1;
      this->i = this->i + 1;
    } while (this->i < (int)uVar2);
  }
  this->row = -1;
  this->col = -1;
  this->i = -1;
  return this;
}
