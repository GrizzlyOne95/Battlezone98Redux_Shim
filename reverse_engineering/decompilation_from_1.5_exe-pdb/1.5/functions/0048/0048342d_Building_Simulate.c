/*
 * Entry: 0048342d
 * Name: Building::Simulate
 * Namespace: Building
 * Signature: void Simulate(Building * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall Building::Simulate(Building *this,float param_1)

{
  int *this_00;
  char *pcVar1;
  uint uVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  bool bVar6;
  _gas_object *p_Var7;
  GAS_PREP_INFO local_50;
  GAS_CTRL local_34;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  this_00 = &this->_padding_;
  bVar6 = DistributedObject::IsRemote((DistributedObject *)this_00);
  if (!bVar6) {
    uVar2 = *(uint *)(this->_padding_ + 0x14);
    if ((uVar2 & 0x1000000) != 0) {
      (**(code **)(*this_00 + 0x14))();
      return;
    }
    if ((uVar2 & 0x200) != 0) {
      (**(code **)(*this_00 + 0x10))();
      return;
    }
  }
  if (((*(uint *)(this->_padding_ + 0x14) & 0x200) == 0) &&
     (pcVar1 = (char *)(this->_padding_ + 0x150), *pcVar1 != '\0')) {
    fVar3 = (float)this->_padding_ - (float)View_Record.MainCam.View_Pyramid[0].x;
    fVar4 = (float)this->_padding_ - (float)View_Record.MainCam.View_Pyramid[0].y;
    fVar5 = (float)this->_padding_ - (float)View_Record.MainCam.View_Pyramid[0].z;
    if (2500.0 <= fVar5 * fVar5 + fVar4 * fVar4 + fVar3 * fVar3) {
      p_Var7 = this->soundAmbient;
      if (p_Var7 != (_gas_object *)0x0) {
        StopGASEvent(p_Var7);
        this->soundAmbient = (_gas_object *)0x0;
      }
    }
    else if (this->soundAmbient == (_gas_object *)0x0) {
      InitGASCtrl(&local_34);
      local_34.flags = 1;
      InitGASPrep(&local_50);
      local_50.loopMode = 1;
      local_50.pri = 10;
      p_Var7 = StartGASEvent(pcVar1,(_OBJ76 *)this->_padding_,&local_34,&local_50);
      this->soundAmbient = p_Var7;
    }
  }
  return;
}
