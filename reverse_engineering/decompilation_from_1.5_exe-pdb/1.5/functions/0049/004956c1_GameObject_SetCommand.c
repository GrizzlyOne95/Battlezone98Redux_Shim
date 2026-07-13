/*
 * Entry: 004956c1
 * Name: GameObject::SetCommand
 * Namespace: GameObject
 * Signature: void SetCommand(GameObject * this, AiCommand param_1, VECTOR_3D * param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
GameObject::SetCommand(GameObject *this,AiCommand param_1,VECTOR_3D *param_2,long param_3)

{
  bool bVar1;
  AiPath *pAVar2;
  VECTOR_3D *pVVar3;
  VECTOR_3D *pVVar4;
  
  pAVar2 = (this->nextCmd).where;
  if (pAVar2 != (AiPath *)0x0) {
    AiPath::Release(pAVar2);
  }
  (this->nextCmd).priority = 0;
  (this->nextCmd).who = 0;
  (this->nextCmd).what = param_1;
  pAVar2 = ::operator_new(0x1c);
  if (pAVar2 == (AiPath *)0x0) {
    pAVar2 = (AiPath *)0x0;
  }
  else {
    pVVar4 = param_2;
    pVVar3 = (VECTOR_3D *)(**(code **)(this->_padding_ + 0xc))();
    pAVar2 = AiPath::AiPath(pAVar2,pVVar3,pVVar4);
  }
  (this->nextCmd).where = pAVar2;
  (this->nextCmd).param = param_3;
  bVar1 = DistributedObject::IsRemote((DistributedObject *)&this->_padding_);
  if (bVar1) {
    DistributedObject::SendCommand((DistributedObject *)&this->_padding_,param_1,param_2);
  }
  return;
}
