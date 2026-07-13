/*
 * Entry: 00464ab3
 * Name: Tran03Mission::AddObject
 * Namespace: Tran03Mission
 * Signature: void AddObject(Tran03Mission * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tran03Mission::AddObject(Tran03Mission *this,GameObject *param_1)

{
  int iVar1;
  
  iVar1 = GameObject::GetHandle(param_1);
  AddObject(this,iVar1);
  AiMission::AddObject((AiMission *)this,param_1);
  return;
}
