/*
 * Entry: 004232dd
 * Name: Misn04Mission::AddObject
 * Namespace: Misn04Mission
 * Signature: void AddObject(Misn04Mission * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn04Mission::AddObject(Misn04Mission *this,GameObject *param_1)

{
  int iVar1;
  
  iVar1 = GameObject::GetHandle(param_1);
  AddObject(this,iVar1);
  AiMission::AddObject((AiMission *)this,param_1);
  return;
}
