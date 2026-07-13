/*
 * Entry: 0044d774
 * Name: NetProcess::Init
 * Namespace: NetProcess
 * Signature: void Init(NetProcess * this, AiMission * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall NetProcess::Init(NetProcess *this,AiMission *param_1,GameObject *param_2)

{
  *(AiMission **)&this->field_0x8 = param_1;
  AiMission::AddProcess(param_1,(AiProcess *)this);
  *(undefined4 *)&this->field_0x10 = 0;
  *(GameObject **)&this->field_0xc = param_2;
  if (param_2 != (GameObject *)0x0) {
    GameObject::SetAIProcess(param_2,(AiProcess *)this);
  }
  return;
}
