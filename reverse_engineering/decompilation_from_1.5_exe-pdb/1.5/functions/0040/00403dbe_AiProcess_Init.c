/*
 * Entry: 00403dbe
 * Name: AiProcess::Init
 * Namespace: AiProcess
 * Signature: void Init(AiProcess * this, AiMission * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AiProcess::Init(AiProcess *this,AiMission *param_1,GameObject *param_2)

{
  this->fMission = param_1;
  AiMission::AddProcess(param_1,this);
  this->exited = 0;
  this->fOwner = param_2;
  if (param_2 != (GameObject *)0x0) {
    GameObject::SetAIProcess(param_2,this);
  }
  return;
}
