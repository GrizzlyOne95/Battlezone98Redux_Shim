/*
 * Entry: 0045ce65
 * Name: ScavengerProcess::Init
 * Namespace: ScavengerProcess
 * Signature: void Init(ScavengerProcess * this, AiMission * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
ScavengerProcess::Init(ScavengerProcess *this,AiMission *param_1,GameObject *param_2)

{
  int iVar1;
  
  AiProcess::Init((AiProcess *)this,param_1,param_2);
  this->curState = START;
  (this->lastScrap).y = -1.0;
  this->nextState = START;
  this->craft = (Scavenger *)param_2;
  this->recycle = true;
  iVar1 = (**(code **)(param_2->_padding_ + 4))();
  this->team = iVar1;
  Init_Escorts(this);
  return;
}
