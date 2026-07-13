/*
 * Entry: 0043d548
 * Name: Misn17Mission::AddObject
 * Namespace: Misn17Mission
 * Signature: void AddObject(Misn17Mission * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn17Mission::AddObject(Misn17Mission *this,GameObject *param_1)

{
  int iVar1;
  
  iVar1 = GameObject::GetHandle(param_1);
  AddObject(this,iVar1);
  AiMission::AddObject((AiMission *)this,param_1);
  return;
}
