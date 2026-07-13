/*
 * Entry: 004209d9
 * Name: Misn03Mission::AddObject
 * Namespace: Misn03Mission
 * Signature: void AddObject(Misn03Mission * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn03Mission::AddObject(Misn03Mission *this,GameObject *param_1)

{
  int iVar1;
  
  iVar1 = GameObject::GetHandle(param_1);
  AddObject(this,iVar1);
  AiMission::AddObject((AiMission *)this,param_1);
  return;
}
