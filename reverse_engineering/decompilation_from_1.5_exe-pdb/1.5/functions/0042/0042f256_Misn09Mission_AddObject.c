/*
 * Entry: 0042f256
 * Name: Misn09Mission::AddObject
 * Namespace: Misn09Mission
 * Signature: void AddObject(Misn09Mission * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn09Mission::AddObject(Misn09Mission *this,GameObject *param_1)

{
  int iVar1;
  
  iVar1 = GameObject::GetHandle(param_1);
  AddObject(this,iVar1);
  AiMission::AddObject((AiMission *)this,param_1);
  return;
}
