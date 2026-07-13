/*
 * Entry: 0040e8c3
 * Name: AttackGroup::Join
 * Namespace: AttackGroup
 * Signature: void Join(AttackGroup * this, GameObject * param_1, UnitTask * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AttackGroup::Join(AttackGroup *this,GameObject *param_1,UnitTask *param_2)

{
  float fVar1;
  GameObject *pGVar2;
  float *pfVar3;
  float10 fVar4;
  float local_14;
  AttackerInfo local_10;
  AttackGroup *local_8;
  
  local_10.attackTask = param_2;
  local_10.attacker = param_1;
  local_8 = this;
  std::list<AttackerInfo,std::allocator<AttackerInfo>_>::push_back(&this->attackers,&local_10);
  if ((this->attackers)._Mysize == 1) {
    pGVar2 = GameObjectHandle::GetObj(this->target);
    if ((param_1 == (GameObject *)0x0) || (pGVar2 == (GameObject *)0x0)) {
      local_14 = 0.0;
      local_10.attackTask = (UnitTask *)0x3f800000;
      local_8 = this;
    }
    else {
      pfVar3 = (float *)(**(code **)(pGVar2->_padding_ + 0xc))();
      local_14 = *pfVar3;
      fVar1 = pfVar3[2];
      pfVar3 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
      local_14 = *pfVar3 - local_14;
      local_10.attackTask = (UnitTask *)(pfVar3[2] - fVar1);
    }
    fVar4 = (float10)fpatan((float10)local_14,(float10)(float)local_10.attackTask);
    local_8->zeroHeading = (float)fVar4;
  }
  return;
}
