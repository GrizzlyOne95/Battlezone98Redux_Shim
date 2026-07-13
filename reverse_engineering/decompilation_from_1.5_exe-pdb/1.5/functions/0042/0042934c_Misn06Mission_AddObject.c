/*
 * Entry: 0042934c
 * Name: Misn06Mission::AddObject
 * Namespace: Misn06Mission
 * Signature: void AddObject(Misn06Mission * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn06Mission::AddObject(Misn06Mission *this,GameObject *param_1)

{
  int iVar1;
  GameObjectClass *pGVar2;
  
  AiProcess::Attach((AiMission *)this,param_1);
  if (param_1->curPilot == (GameObjectClass *)0x0) {
    iVar1 = (**(code **)param_1->_padding_)();
    if (param_1 == GameObject::userObject) {
      pGVar2 = *(GameObjectClass **)(iVar1 + 0xdc);
    }
    else {
      pGVar2 = *(GameObjectClass **)(iVar1 + 0xd8);
    }
    param_1->curPilot = pGVar2;
  }
  return;
}
