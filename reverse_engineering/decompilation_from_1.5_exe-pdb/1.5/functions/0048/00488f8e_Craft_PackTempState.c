/*
 * Entry: 00488f8e
 * Name: Craft::PackTempState
 * Namespace: Craft
 * Signature: void PackTempState(Craft * this, void * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Craft::PackTempState(Craft *this,void *param_1,uint *param_2)

{
  undefined1 extraout_AL;
  undefined1 extraout_AL_00;
  float10 fVar1;
  float10 extraout_ST0;
  float10 fVar2;
  float10 extraout_ST1;
  
  fVar2 = (float10)0;
  *param_2 = *param_2 + 3;
  fVar1 = (float10)255.0;
  if (fVar2 < (float10)(float)this->_padding_) {
    _ftol2();
    *(undefined1 *)((int)param_1 + 1) = extraout_AL;
    fVar1 = extraout_ST0;
    fVar2 = extraout_ST1;
  }
  else {
    *(undefined1 *)((int)param_1 + 1) = 0;
  }
  if (fVar2 < (float10)(float)this->_padding_) {
    fVar2 = (float10)(float)this->_padding_;
    if ((float10)1 < fVar2) {
      fVar2 = (float10)1;
    }
    ceil((double)(fVar2 * fVar1));
    _ftol2();
    *(undefined1 *)param_1 = extraout_AL_00;
  }
  else {
    *(undefined1 *)param_1 = 0;
  }
  *(undefined1 *)((int)param_1 + 2) = 0;
  if ((this->_padding_ != 0) || (this->_padding_ != 0)) {
    *(undefined1 *)((int)param_1 + 2) = 0x80;
  }
  if ((*(uint *)(this->_padding_ + 0x14) & 0x400) != 0) {
    *(byte *)((int)param_1 + 2) = *(byte *)((int)param_1 + 2) | 0x40;
  }
  if ((char)this->_padding_ != '\0') {
    *(byte *)((int)param_1 + 2) = *(byte *)((int)param_1 + 2) | 0x20;
  }
  if ((float)this->_padding_ < 0.0) {
    *(byte *)((int)param_1 + 2) = *(byte *)((int)param_1 + 2) | 0x10;
  }
  DistributedObject::PackTempState((DistributedObject *)this,(void *)((int)param_1 + 3),param_2);
  return;
}
