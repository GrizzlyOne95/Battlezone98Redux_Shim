/*
 * Entry: 00444a01
 * Name: Misns4Mission::AddObject
 * Namespace: Misns4Mission
 * Signature: void AddObject(Misns4Mission * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns4Mission::AddObject(Misns4Mission *this,GameObject *param_1)

{
  int iVar1;
  
  iVar1 = GameObject::GetHandle(param_1);
  AddObject(this,iVar1);
  AiMission::AddObject((AiMission *)this,param_1);
  return;
}
