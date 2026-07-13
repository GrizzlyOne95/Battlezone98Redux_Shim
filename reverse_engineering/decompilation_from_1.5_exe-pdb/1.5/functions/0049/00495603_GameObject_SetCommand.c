/*
 * Entry: 00495603
 * Name: GameObject::SetCommand
 * Namespace: GameObject
 * Signature: void SetCommand(GameObject * this, AiCommand param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::SetCommand(GameObject *this,AiCommand param_1)

{
  AiPath *pAVar1;
  
  pAVar1 = (this->nextCmd).where;
  if (pAVar1 != (AiPath *)0x0) {
    AiPath::Release(pAVar1);
  }
  (this->nextCmd).priority = 0;
  (this->nextCmd).who = 0;
  (this->nextCmd).where = (AiPath *)0x0;
  (this->nextCmd).param = 0;
  (this->nextCmd).what = param_1;
  return;
}
