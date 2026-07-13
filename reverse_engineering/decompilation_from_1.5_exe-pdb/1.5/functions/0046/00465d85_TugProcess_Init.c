/*
 * Entry: 00465d85
 * Name: TugProcess::Init
 * Namespace: TugProcess
 * Signature: void Init(TugProcess * this, AiMission * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TugProcess::Init(TugProcess *this,AiMission *param_1,GameObject *param_2)

{
  AiProcess::Init((AiProcess *)this,param_1,param_2);
  this->curState = START;
  this->dropoffPoint = 5.0;
  this->task = (AiTask *)0x0;
  this->craft = (Craft *)param_2;
  this->nextState = WAIT;
  return;
}
