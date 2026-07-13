/*
 * Entry: 00495538
 * Name: GameObject::GetWhat
 * Namespace: GameObject
 * Signature: AiCommand GetWhat(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiCommand __thiscall GameObject::GetWhat(GameObject *this)

{
  AiPath *pAVar1;
  AiCommand AVar2;
  int iVar3;
  AiCmdInfo *pAVar4;
  AiCmdInfo *pAVar5;
  
  if ((this->nextCmd).what == CMD_SELECT) {
    (this->nextCmd).what = CMD_NONE;
    return CMD_SELECT;
  }
  pAVar1 = (this->curCmd).where;
  if (pAVar1 != (AiPath *)0x0) {
    AiPath::Release(pAVar1);
  }
  pAVar4 = &this->nextCmd;
  pAVar5 = &this->curCmd;
  for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
    pAVar5->priority = pAVar4->priority;
    pAVar4 = (AiCmdInfo *)&pAVar4->what;
    pAVar5 = (AiCmdInfo *)&pAVar5->what;
  }
  (this->nextCmd).priority = 0;
  AVar2 = (this->curCmd).what;
  (this->nextCmd).what = CMD_NONE;
  (this->nextCmd).who = 0;
  (this->nextCmd).where = (AiPath *)0x0;
  (this->nextCmd).param = 0;
  return AVar2;
}
