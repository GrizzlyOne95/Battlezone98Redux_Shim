/*
 * Entry: 0044bcbc
 * Name: Misns8Mission::AddObject
 * Namespace: Misns8Mission
 * Signature: void AddObject(Misns8Mission * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns8Mission::AddObject(Misns8Mission *this,GameObject *param_1)

{
  int iVar1;
  
  iVar1 = GameObject::GetHandle(param_1);
  AddObject(this,iVar1);
  AiMission::AddObject((AiMission *)this,param_1);
  return;
}
