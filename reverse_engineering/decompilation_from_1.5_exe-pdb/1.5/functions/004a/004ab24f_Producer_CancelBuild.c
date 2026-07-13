/*
 * Entry: 004ab24f
 * Name: Producer::CancelBuild
 * Namespace: Producer
 * Signature: bool CancelBuild(Producer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Producer::CancelBuild(Producer *this)

{
  long lVar1;
  long lVar2;
  
  if (this->buildClass == (GameObjectClass *)0x0) {
    return false;
  }
  this->_padding_ = -1;
  lVar1 = AdjustedScrapCost(this->_padding_,this->buildClass);
  lVar2 = AdjustedPilotCost(this->_padding_,this->buildClass);
  Team::AddScrap((Team *)this->_padding_,lVar1);
  Team::AddPilot((Team *)this->_padding_,lVar2);
  this->buildClass = (GameObjectClass *)0x0;
  return true;
}
