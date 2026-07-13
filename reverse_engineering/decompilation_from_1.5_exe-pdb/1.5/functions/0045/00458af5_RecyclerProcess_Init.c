/*
 * Entry: 00458af5
 * Name: RecyclerProcess::Init
 * Namespace: RecyclerProcess
 * Signature: void Init(RecyclerProcess * this, AiMission * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecyclerProcess::Init(RecyclerProcess *this,AiMission *param_1,GameObject *param_2)

{
  AiProcess::Init((AiProcess *)this,param_1,param_2);
  this->lastHit = 0.0;
  this->curState = START;
  this->task = (AiTask *)0x0;
  this->where = (AiPath *)0x0;
  this->release = false;
  this->whoHandle = 0;
  this->classtobuild = (GameObjectClass *)0x0;
  this->target = (GameObject *)0x0;
  this->nextState = WAIT;
  this->craft = (Recycler *)param_2;
  (**(code **)(this->_padding_ + 0x20))();
  return;
}
