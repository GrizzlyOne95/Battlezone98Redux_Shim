/*
 * Entry: 00468cb5
 * Name: UnitProcess::Init
 * Namespace: UnitProcess
 * Signature: void Init(UnitProcess * this, AiMission * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::Init(UnitProcess *this,AiMission *param_1,GameObject *param_2)

{
  AiProcess::Init((AiProcess *)this,param_1,param_2);
  this->me = (Craft *)param_2;
  (**(code **)(this->_padding_ + 0x20))();
  return;
}
