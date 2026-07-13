/*
 * Entry: 00495641
 * Name: GameObject::SetCommand
 * Namespace: GameObject
 * Signature: void SetCommand(GameObject * this, AiCommand param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::SetCommand(GameObject *this,AiCommand param_1,GameObject *param_2)

{
  int iVar1;
  AiPath *pAVar2;
  VECTOR_3D *pVVar3;
  VECTOR_3D *pVVar4;
  
  pAVar2 = (this->nextCmd).where;
  if (pAVar2 != (AiPath *)0x0) {
    AiPath::Release(pAVar2);
  }
  (this->nextCmd).priority = 0;
  (this->nextCmd).what = param_1;
  if (param_2 == (GameObject *)0x0) {
    iVar1 = 0;
  }
  else {
    iVar1 = GetHandle(param_2);
  }
  (this->nextCmd).who = iVar1;
  pAVar2 = ::operator_new(0x1c);
  if (pAVar2 == (AiPath *)0x0) {
    pAVar2 = (AiPath *)0x0;
  }
  else {
    pVVar3 = (VECTOR_3D *)(**(code **)(param_2->_padding_ + 0xc))();
    pVVar4 = (VECTOR_3D *)(**(code **)(this->_padding_ + 0xc))();
    pAVar2 = AiPath::AiPath(pAVar2,pVVar4,pVVar3);
  }
  (this->nextCmd).param = 0;
  (this->nextCmd).where = pAVar2;
  return;
}
