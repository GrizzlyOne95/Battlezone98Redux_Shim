/*
 * Entry: 0049559d
 * Name: GameObject::ClearCommand
 * Namespace: GameObject
 * Signature: void ClearCommand(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::ClearCommand(GameObject *this)

{
  AiPath *pAVar1;
  
  pAVar1 = (this->curCmd).where;
  if (pAVar1 != (AiPath *)0x0) {
    AiPath::Release(pAVar1);
  }
  (this->curCmd).priority = 0;
  (this->curCmd).what = CMD_NONE;
  (this->curCmd).who = 0;
  (this->curCmd).where = (AiPath *)0x0;
  (this->curCmd).param = 0;
  return;
}
