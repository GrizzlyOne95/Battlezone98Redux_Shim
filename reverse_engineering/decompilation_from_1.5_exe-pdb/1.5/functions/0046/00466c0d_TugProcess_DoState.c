/*
 * Entry: 00466c0d
 * Name: TugProcess::DoState
 * Namespace: TugProcess
 * Signature: void DoState(TugProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TugProcess::DoState(TugProcess *this)

{
  Craft *this_00;
  char cVar1;
  VECTOR_3D *pVVar2;
  GameObject *this_01;
  SPHERE *pSVar3;
  float *pfVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  VECTOR_3D local_34;
  VECTOR_3D local_28;
  float local_1c;
  float fStack_18;
  float local_14;
  undefined4 local_10;
  float local_c;
  float local_8;
  
  switch(this->curState) {
  case WAIT:
    (**(code **)(this->craft->_padding_ + 0x84))(0);
    iVar5 = this->craft->_padding_;
    local_1c = *(float *)(iVar5 + 0x38);
    fStack_18 = *(float *)(iVar5 + 0x3c);
    local_14 = *(float *)(iVar5 + 0x40);
    local_10 = local_1c;
    local_c = local_14;
    (**(code **)(this->craft->_padding_ + 0x88))(local_1c,local_14);
    return;
  case GOTO:
  case FOLLOW:
  case PICKUP:
  case RESCUE:
    cVar1 = (**(code **)(this->task->_padding_ + 0x18))();
    if (cVar1 != '\0') {
LAB_00466e70:
      this->nextState = WAIT;
      return;
    }
    break;
  case PARK:
    cVar1 = (**(code **)(this->task->_padding_ + 0x18))();
    if (cVar1 != '\0') {
      (**(code **)(this->craft->_padding_ + 0x60))();
      this->hitchCargo = (_OBJ76 *)0x0;
      pVVar2 = (VECTOR_3D *)(**(code **)(this->craft->_padding_ + 0xc))();
      pVVar2 = AddMultVectors(&local_34,*pVVar2,-15.0,*(VECTOR_3D *)(this->craft->_padding_ + 0x38))
      ;
      fVar6 = pVVar2->y;
      fVar7 = pVVar2->z;
      (this->where).x = pVVar2->x;
      (this->where).y = fVar6;
      (this->where).z = fVar7;
      this->nextState = GOTO;
      return;
    }
    break;
  case DROPOFF:
    cVar1 = (**(code **)(this->task->_padding_ + 0x18))();
    if (cVar1 != '\0') {
      pVVar2 = (VECTOR_3D *)(**(code **)(this->craft->_padding_ + 0xc))();
      pVVar2 = AddMultVectors(&local_28,*pVVar2,this->dropoffPoint,
                              *(VECTOR_3D *)(this->craft->_padding_ + 0x38));
      local_1c = pVVar2->x;
      fStack_18 = pVVar2->y;
      local_14 = pVVar2->z;
      (this->where).x = local_1c;
      (this->where).y = fStack_18;
      (this->where).z = local_14;
      Say(this->craft,SELECT_DROPOFF_MSG,0);
      this->nextState = PARK;
      return;
    }
    break;
  case REPAIR:
    DoRepair(this);
    return;
  case RECYCLE:
    if ((this->task == (AiTask *)0x0) ||
       (cVar1 = (**(code **)(this->task->_padding_ + 0x18))(), cVar1 != '\0')) {
      this_01 = GameObjectHandle::GetObj(this->task[2]._padding_);
      if (this_01 != (GameObject *)0x0) {
        this_00 = this->craft;
        fVar7 = 40.0;
        pSVar3 = GameObject::GetSphere((GameObject *)this_00);
        local_8 = Max((float)this_00->_padding_,pSVar3->radius);
        pSVar3 = GameObject::GetSphere(this_01);
        fVar6 = Max(this_01->collisionRadius,pSVar3->radius);
        local_8 = Max(fVar6 + local_8 + 20.0,fVar7);
        pfVar4 = (float *)(**(code **)(this_01->_padding_ + 0xc))();
        local_c = *pfVar4;
        pfVar4 = (float *)(**(code **)(this->craft->_padding_ + 0xc))();
        if (ABS(local_c - *pfVar4) < local_8) {
          iVar5 = (**(code **)(this_01->_padding_ + 0xc))();
          local_c = *(float *)(iVar5 + 8);
          iVar5 = (**(code **)(this->craft->_padding_ + 0xc))();
          if (ABS(local_c - *(float *)(iVar5 + 8)) < local_8) {
            (**(code **)(this->craft->_padding_ + 0x24))();
          }
        }
      }
      if (this->craft->_padding_ == CMD_RECYCLE) {
        GameObject::ClearCommand((GameObject *)this->craft);
      }
      goto LAB_00466e70;
    }
    break;
  default:
    goto switchD_00466c25_default;
  }
  (**(code **)(this->task->_padding_ + 0x1c))();
switchD_00466c25_default:
  return;
}
