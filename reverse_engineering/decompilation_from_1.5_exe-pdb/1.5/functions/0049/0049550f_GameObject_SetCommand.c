/*
 * Entry: 0049550f
 * Name: GameObject::SetCommand
 * Namespace: GameObject
 * Signature: void SetCommand(GameObject * this, AiCmdInfo * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::SetCommand(GameObject *this,AiCmdInfo *param_1)

{
  AiPath *pAVar1;
  int iVar2;
  AiCmdInfo *pAVar3;
  
  pAVar1 = (this->nextCmd).where;
  if (pAVar1 != (AiPath *)0x0) {
    AiPath::Release(pAVar1);
  }
  pAVar3 = &this->nextCmd;
  for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
    pAVar3->priority = param_1->priority;
    param_1 = (AiCmdInfo *)&param_1->what;
    pAVar3 = (AiCmdInfo *)&pAVar3->what;
  }
  return;
}
