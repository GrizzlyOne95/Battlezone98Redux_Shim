/*
 * Entry: 004aa8d9
 * Name: Producer::Build
 * Namespace: Producer
 * Signature: GameObject * Build(Producer * this, GameObjectClass * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall Producer::Build(Producer *this,GameObjectClass *param_1)

{
  long lVar1;
  long lVar2;
  long lVar3;
  GameObject *pGVar4;
  
  lVar1 = AdjustedScrapCost(this->_padding_,param_1);
  lVar2 = AdjustedPilotCost(this->_padding_,param_1);
  lVar3 = Team::GetScrap((Team *)this->_padding_);
  if ((lVar1 <= lVar3) && (lVar3 = Team::GetPilot((Team *)this->_padding_), lVar2 <= lVar3)) {
    this->buildClass = param_1;
    Team::AddScrap((Team *)this->_padding_,-lVar1);
    Team::AddPilot((Team *)this->_padding_,-lVar2);
    pGVar4 = (GameObject *)(**(code **)(this->_padding_ + 0xa4))();
    return pGVar4;
  }
  return (GameObject *)0x0;
}
