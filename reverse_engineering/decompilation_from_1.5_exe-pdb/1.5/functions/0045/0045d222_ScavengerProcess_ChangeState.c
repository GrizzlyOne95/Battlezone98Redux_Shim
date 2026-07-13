/*
 * Entry: 0045d222
 * Name: ScavengerProcess::ChangeState
 * Namespace: ScavengerProcess
 * Signature: void ChangeState(ScavengerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScavengerProcess::ChangeState(ScavengerProcess *this)

{
  VECTOR_2D *pVVar1;
  State SVar2;
  Scavenger *this_00;
  AiPath *pAVar3;
  bool bVar4;
  GameObject *pGVar5;
  int iVar6;
  
  SVar2 = this->nextState;
  if (SVar2 == GOTO) {
    this_00 = this->craft;
    pAVar3 = (AiPath *)this_00->_padding_;
    pVVar1 = pAVar3->points + pAVar3->pointCount + -1;
    (this->where).x = pVVar1->x;
    (this->where).y = -1.0;
    (this->where).z = pVVar1->z;
    pGVar5 = GameObject::GetWho((GameObject *)this_00);
    iVar6 = 0;
    if (pGVar5 != (GameObject *)0x0) {
      iVar6 = GameObject::GetHandle(pGVar5);
    }
    this->whoHandle = iVar6;
    if ((pGVar5 == (GameObject *)0x0) ||
       (iVar6 = (**(code **)pGVar5->_padding_)(), *(int *)(iVar6 + 0x28) != 7)) {
      bVar4 = false;
    }
    else {
      bVar4 = true;
    }
    this->recycle = bVar4;
    return;
  }
  if ((SVar2 != FOLLOW) && (SVar2 != RESCUE)) {
    return;
  }
  pGVar5 = GameObject::GetWho((GameObject *)this->craft);
  iVar6 = 0;
  if (pGVar5 != (GameObject *)0x0) {
    iVar6 = GameObject::GetHandle(pGVar5);
  }
  this->whoHandle = iVar6;
  return;
}
