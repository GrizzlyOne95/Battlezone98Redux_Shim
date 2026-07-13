/*
 * Entry: 004489ce
 * Name: Misns7Mission::AddObject
 * Namespace: Misns7Mission
 * Signature: void AddObject(Misns7Mission * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns7Mission::AddObject(Misns7Mission *this,GameObject *param_1)

{
  int iVar1;
  
  iVar1 = GameObject::GetHandle(param_1);
  AddObject(this,iVar1);
  AiMission::AddObject((AiMission *)this,param_1);
  return;
}
