/*
 * Entry: 00468e3f
 * Name: UnitProcess::DoState
 * Namespace: UnitProcess
 * Signature: void DoState(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::DoState(UnitProcess *this)

{
  char cVar1;
  bool bVar2;
  UnitMsg UVar3;
  
  cVar1 = (**(code **)(this->me->_padding_ + 100))();
  if ((cVar1 == '\0') && (cVar1 = (**(code **)(this->me->_padding_ + 0x68))(), cVar1 == '\0')) {
    bVar2 = true;
  }
  else {
    bVar2 = false;
  }
  this->isInTransition = bVar2;
  if ((this->wasInTransition != false) && (bVar2 == false)) {
    cVar1 = (**(code **)(this->me->_padding_ + 100))();
    if (cVar1 == '\0') {
      UVar3 = PACKED_MSG;
    }
    else {
      UVar3 = DEPLOYED_MSG;
    }
    Say(this->me,UVar3,0);
  }
  switch(this->curState) {
  case WAIT:
    (**(code **)(this->_padding_ + 0x38))();
    break;
  case GOTO:
    (**(code **)(this->_padding_ + 0x44))();
    break;
  case PATROL:
    (**(code **)(this->_padding_ + 0x50))();
    break;
  case STAGE:
    (**(code **)(this->_padding_ + 0x5c))();
    break;
  case ATTACK:
    (**(code **)(this->_padding_ + 0x68))();
    break;
  case FOLLOW:
    (**(code **)(this->_padding_ + 0x74))();
    break;
  case DEFEND:
    (**(code **)(this->_padding_ + 0x80))();
    break;
  case REPAIR:
    (**(code **)(this->_padding_ + 0x8c))();
    break;
  case RELOAD:
    (**(code **)(this->_padding_ + 0x98))();
    break;
  case RESCUE:
    (**(code **)(this->_padding_ + 0xa4))();
    break;
  case RECYCLE:
    (**(code **)(this->_padding_ + 0xb0))();
    break;
  case PACKUP:
    (**(code **)(this->_padding_ + 0xbc))();
    break;
  case SUBATTACK:
    (**(code **)(this->_padding_ + 200))();
    break;
  case USTATE1:
    (**(code **)(this->_padding_ + 0xd4))();
    break;
  case USTATE2:
    (**(code **)(this->_padding_ + 0xe0))();
  }
  this->wasInTransition = this->isInTransition;
  return;
}
