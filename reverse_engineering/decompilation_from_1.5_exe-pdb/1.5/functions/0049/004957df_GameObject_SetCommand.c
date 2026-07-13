/*
 * Entry: 004957df
 * Name: GameObject::SetCommand
 * Namespace: GameObject
 * Signature: void SetCommand(GameObject * this, AiCommand param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::SetCommand(GameObject *this,AiCommand param_1,long param_2)

{
  AiPath *pAVar1;
  
  pAVar1 = (this->nextCmd).where;
  if (pAVar1 != (AiPath *)0x0) {
    AiPath::Release(pAVar1);
  }
  (this->nextCmd).priority = 0;
  (this->nextCmd).who = 0;
  (this->nextCmd).where = (AiPath *)0x0;
  (this->nextCmd).what = param_1;
  (this->nextCmd).param = param_2;
  return;
}
