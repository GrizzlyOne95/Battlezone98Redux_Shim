/*
 * Entry: 004aa84f
 * Name: Producer::StartBuild
 * Namespace: Producer
 * Signature: bool StartBuild(Producer * this, GameObjectClass * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Producer::StartBuild(Producer *this,GameObjectClass *param_1)

{
  bool bVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  if (this->buildClass == (GameObjectClass *)0x0) {
    lVar2 = AdjustedScrapCost(this->_padding_,param_1);
    lVar3 = AdjustedPilotCost(this->_padding_,param_1);
    lVar4 = Team::GetScrap((Team *)this->_padding_);
    if ((lVar4 < lVar2) || (lVar4 = Team::GetPilot((Team *)this->_padding_), lVar4 < lVar3)) {
      bVar1 = false;
    }
    else {
      Team::AddScrap((Team *)this->_padding_,-lVar2);
      Team::AddPilot((Team *)this->_padding_,-lVar3);
      this->buildClass = param_1;
      this->buildDoneTime = param_1->buildTime;
      bVar1 = true;
    }
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}
