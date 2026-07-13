/*
 * Entry: 004652b2
 * Name: Tran04Mission::AddObject
 * Namespace: Tran04Mission
 * Signature: void AddObject(Tran04Mission * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tran04Mission::AddObject(Tran04Mission *this,GameObject *param_1)

{
  int iVar1;
  
  iVar1 = GameObject::GetHandle(param_1);
  AddObject(this,iVar1);
  AiMission::AddObject((AiMission *)this,param_1);
  return;
}
