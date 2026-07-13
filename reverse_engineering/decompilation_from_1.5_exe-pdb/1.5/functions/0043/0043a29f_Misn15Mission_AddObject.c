/*
 * Entry: 0043a29f
 * Name: Misn15Mission::AddObject
 * Namespace: Misn15Mission
 * Signature: void AddObject(Misn15Mission * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn15Mission::AddObject(Misn15Mission *this,GameObject *param_1)

{
  int iVar1;
  
  iVar1 = GameObject::GetHandle(param_1);
  AddObject(this,iVar1);
  AiMission::AddObject((AiMission *)this,param_1);
  return;
}
