/*
 * Entry: 0040c668
 * Name: ArmoryProcess::Init
 * Namespace: ArmoryProcess
 * Signature: void Init(ArmoryProcess * this, AiMission * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ArmoryProcess::Init(ArmoryProcess *this,AiMission *param_1,GameObject *param_2)

{
  AiProcess::Init((AiProcess *)this,param_1,param_2);
  this->craft = (Armory *)param_2;
  this->curState = START;
  this->nextState = WAIT;
  this->task = (AiTask *)0x0;
  this->where = (AiPath *)0x0;
  this->release = false;
  this->whoHandle = 0;
  this->classtobuild = (GameObjectClass *)0x0;
  this->target = (GameObject *)0x0;
  return;
}
