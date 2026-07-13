/*
 * Entry: 00495745
 * Name: GameObject::SetCommand
 * Namespace: GameObject
 * Signature: void SetCommand(GameObject * this, AiCommand param_1, GameObject * param_2, VECTOR_3D * param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
GameObject::SetCommand
          (GameObject *this,AiCommand param_1,GameObject *param_2,VECTOR_3D *param_3,float param_4)

{
  bool bVar1;
  int iVar2;
  AiPath *pAVar3;
  VECTOR_3D *pVVar4;
  VECTOR_3D *pVVar5;
  
  pAVar3 = (this->nextCmd).where;
  if (pAVar3 != (AiPath *)0x0) {
    AiPath::Release(pAVar3);
  }
  (this->nextCmd).priority = 0;
  (this->nextCmd).what = param_1;
  if (param_2 == (GameObject *)0x0) {
    iVar2 = 0;
  }
  else {
    iVar2 = GetHandle(param_2);
  }
  (this->nextCmd).who = iVar2;
  pAVar3 = ::operator_new(0x1c);
  if (pAVar3 == (AiPath *)0x0) {
    pAVar3 = (AiPath *)0x0;
  }
  else {
    pVVar5 = param_3;
    pVVar4 = (VECTOR_3D *)(**(code **)(this->_padding_ + 0xc))();
    pAVar3 = AiPath::AiPath(pAVar3,pVVar4,pVVar5);
  }
  (this->nextCmd).param = 0;
  (this->nextCmd).when = param_4;
  (this->nextCmd).where = pAVar3;
  bVar1 = DistributedObject::IsRemote((DistributedObject *)&this->_padding_);
  if (bVar1) {
    DistributedObject::SendCommand((DistributedObject *)&this->_padding_,param_1,param_3);
  }
  return;
}
