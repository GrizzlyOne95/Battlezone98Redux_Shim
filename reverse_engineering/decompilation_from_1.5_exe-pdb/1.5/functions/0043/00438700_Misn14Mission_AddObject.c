/*
 * Entry: 00438700
 * Name: Misn14Mission::AddObject
 * Namespace: Misn14Mission
 * Signature: void AddObject(Misn14Mission * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn14Mission::AddObject(Misn14Mission *this,GameObject *param_1)

{
  int iVar1;
  
  iVar1 = GameObject::GetHandle(param_1);
  AddObject(this,iVar1);
  AiMission::AddObject((AiMission *)this,param_1);
  return;
}
