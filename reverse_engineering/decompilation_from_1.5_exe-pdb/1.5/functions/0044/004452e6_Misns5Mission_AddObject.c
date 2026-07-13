/*
 * Entry: 004452e6
 * Name: Misns5Mission::AddObject
 * Namespace: Misns5Mission
 * Signature: void AddObject(Misns5Mission * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns5Mission::AddObject(Misns5Mission *this,GameObject *param_1)

{
  int iVar1;
  
  iVar1 = GameObject::GetHandle(param_1);
  AddObject(this,iVar1);
  AiMission::AddObject((AiMission *)this,param_1);
  return;
}
