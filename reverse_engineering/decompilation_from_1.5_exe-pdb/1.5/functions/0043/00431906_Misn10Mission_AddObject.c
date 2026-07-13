/*
 * Entry: 00431906
 * Name: Misn10Mission::AddObject
 * Namespace: Misn10Mission
 * Signature: void AddObject(Misn10Mission * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn10Mission::AddObject(Misn10Mission *this,GameObject *param_1)

{
  int iVar1;
  
  iVar1 = GameObject::GetHandle(param_1);
  AddObject(this,iVar1);
  AiMission::AddObject((AiMission *)this,param_1);
  return;
}
