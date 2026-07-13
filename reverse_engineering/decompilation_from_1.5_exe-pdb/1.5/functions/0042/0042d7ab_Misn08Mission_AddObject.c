/*
 * Entry: 0042d7ab
 * Name: Misn08Mission::AddObject
 * Namespace: Misn08Mission
 * Signature: void AddObject(Misn08Mission * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn08Mission::AddObject(Misn08Mission *this,GameObject *param_1)

{
  int iVar1;
  
  iVar1 = GameObject::GetHandle(param_1);
  AddObject(this,iVar1);
  AiMission::AddObject((AiMission *)this,param_1);
  return;
}
