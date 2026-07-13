/*
 * Entry: 00465d09
 * Name: Tran05Mission::AddObject
 * Namespace: Tran05Mission
 * Signature: void AddObject(Tran05Mission * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tran05Mission::AddObject(Tran05Mission *this,GameObject *param_1)

{
  int iVar1;
  
  iVar1 = GameObject::GetHandle(param_1);
  AddObject(this,iVar1);
  AiMission::AddObject((AiMission *)this,param_1);
  return;
}
