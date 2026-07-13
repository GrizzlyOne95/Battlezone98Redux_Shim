/*
 * Entry: 00445d79
 * Name: Misns6Mission::AddObject
 * Namespace: Misns6Mission
 * Signature: void AddObject(Misns6Mission * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns6Mission::AddObject(Misns6Mission *this,GameObject *param_1)

{
  int iVar1;
  
  iVar1 = GameObject::GetHandle(param_1);
  AddObject(this,iVar1);
  AiMission::AddObject((AiMission *)this,param_1);
  return;
}
