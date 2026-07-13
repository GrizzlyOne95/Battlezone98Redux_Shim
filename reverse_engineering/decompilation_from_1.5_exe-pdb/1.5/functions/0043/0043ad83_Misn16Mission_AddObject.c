/*
 * Entry: 0043ad83
 * Name: Misn16Mission::AddObject
 * Namespace: Misn16Mission
 * Signature: void AddObject(Misn16Mission * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn16Mission::AddObject(Misn16Mission *this,GameObject *param_1)

{
  int iVar1;
  
  iVar1 = GameObject::GetHandle(param_1);
  AddObject(this,iVar1);
  AiMission::AddObject((AiMission *)this,param_1);
  return;
}
