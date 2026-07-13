/*
 * Entry: 00539ea7
 * Name: SpecialItem::Simulate
 * Namespace: SpecialItem
 * Signature: void Simulate(SpecialItem * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall SpecialItem::Simulate(SpecialItem *this,float param_1)

{
  int iVar1;
  int iVar2;
  float fVar3;
  char cVar4;
  bool bVar5;
  char *pcVar6;
  _gas_object *p_Var7;
  GAS_PREP_INFO local_58;
  double local_3c;
  GAS_CTRL local_34;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  cVar4 = this->held;
  if ('\0' < cVar4) {
    this->held = cVar4 + -1;
  }
  if (this->triggered == false) {
    this->_padding_ = this->reticleBase;
    this->shotTimer = 0.0;
    this->reticleCount = 0;
    cVar4 = (**(code **)(this->_padding_ + 0x34))();
    if (cVar4 != '\0') {
      if ((this->carrier == (GameObject *)0x0) ||
         (bVar5 = DistributedObject::IsRemote((DistributedObject *)&this->carrier->_padding_),
         !bVar5)) {
        (**(code **)(this->_padding_ + 0x40))();
      }
      pcVar6 = (char *)(this->_padding_ + 0x80);
      if ((*pcVar6 != '\0') &&
         (p_Var7 = FindGASObject(pcVar6,(_OBJ76 *)this->_padding_), p_Var7 != (_gas_object *)0x0)) {
        StopGASEvent(p_Var7);
      }
      if (*(char *)(this->_padding_ + 0x90) != '\0') {
        InitGASCtrl(&local_34);
        local_34.flags = 0x800;
        InitGASPrep(&local_58);
        if ((((_OBJ76 *)this->_padding_)->flags & 0x10) != 0) {
          local_58.pri = 0x41;
        }
        StartGASEvent((char *)(this->_padding_ + 0x90),(_OBJ76 *)this->_padding_,&local_34,&local_58
                     );
      }
    }
  }
  else {
    iVar2 = this->_padding_;
    if (this->reticleCount < *(int *)(iVar2 + 0xa0)) {
      fVar3 = this->shotTimer + param_1;
      this->shotTimer = fVar3;
      if (*(float *)(iVar2 + 0x7c) <= fVar3) {
        iVar1 = this->reticleCount + 1;
        this->reticleCount = iVar1;
        this->_padding_ = this->reticleBase + iVar1;
        this->shotTimer = fVar3 - *(float *)(iVar2 + 0x7c);
        if ((iVar1 == *(int *)(iVar2 + 0xa0)) &&
           (cVar4 = (**(code **)(this->_padding_ + 0x34))(), cVar4 == '\0')) {
          (**(code **)(this->_padding_ + 0x38))();
          if (*(char *)(this->_padding_ + 0x58) != '\0') {
            InitGASCtrl(&local_34);
            local_34.flags = 0x800;
            InitGASPrep(&local_58);
            if ((((_OBJ76 *)this->_padding_)->flags & 0x10) != 0) {
              local_58.pri = 0x41;
            }
            StartGASEvent((char *)(this->_padding_ + 0x58),(_OBJ76 *)this->_padding_,&local_34,
                          &local_58);
          }
          if (*(char *)(this->_padding_ + 0x80) != '\0') {
            InitGASCtrl(&local_34);
            local_34.flags = 0x801;
            InitGASPrep(&local_58);
            local_58.loopMode = 1;
            if ((((_OBJ76 *)this->_padding_)->flags & 0x10) != 0) {
              local_58.pri = 0x41;
            }
            StartGASEvent((char *)(this->_padding_ + 0x80),(_OBJ76 *)this->_padding_,&local_34,
                          &local_58);
          }
        }
      }
    }
    cVar4 = (**(code **)(this->_padding_ + 0x34))();
    if (cVar4 != '\0') {
      fVar3 = (float)*(int *)(this->_padding_ + 0x78) * param_1 + this->fraction;
      local_3c = (double)((float)Float2Int + fVar3);
      this->fraction = fVar3 - (float)local_3c._0_4_;
      (**(code **)(this->carrier->_padding_ + 0x18))(-local_3c._0_4_);
      (**(code **)(this->_padding_ + 0x3c))(param_1);
    }
  }
  return;
}
