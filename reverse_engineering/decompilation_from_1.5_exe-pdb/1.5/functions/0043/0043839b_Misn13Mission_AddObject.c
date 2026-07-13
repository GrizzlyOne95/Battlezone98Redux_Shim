/*
 * Entry: 0043839b
 * Name: Misn13Mission::AddObject
 * Namespace: Misn13Mission
 * Signature: void AddObject(Misn13Mission * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn13Mission::AddObject(Misn13Mission *this,GameObject *param_1)

{
  int iVar1;
  
  iVar1 = GameObject::GetHandle(param_1);
  AddObject(this,iVar1);
  AiMission::AddObject((AiMission *)this,param_1);
  return;
}
