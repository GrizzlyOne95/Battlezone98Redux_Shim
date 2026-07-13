/*
 * Entry: 004a6e06
 * Name: Person::RegCollision
 * Namespace: Person
 * Signature: bool RegCollision(Person * this, _OBJ76 * param_1, CLSN_INFO * param_2, CLSN_INFO * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
Person::RegCollision(Person *this,_OBJ76 *param_1,CLSN_INFO *param_2,CLSN_INFO *param_3)

{
  uint uVar1;
  GameObject *this_00;
  bool bVar2;
  int iVar3;
  AiMission *pAVar4;
  EULER *pEVar5;
  CLSN_INFO *pCVar6;
  int *piVar7;
  float *pfVar8;
  EULER local_b8;
  float local_70 [6];
  float local_58;
  float local_54;
  float local_50;
  VECTOR_3D local_28;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  bVar2 = DistributedObject::IsRemote((DistributedObject *)&this->_padding_);
  if (((bVar2) || (uVar1 = *(uint *)(this->_padding_ + 0x14), (uVar1 & 0x20) != 0)) ||
     ((uVar1 & 0x1000200) != 0)) {
    bVar2 = false;
  }
  else if (this->_padding_ == 0) {
    bVar2 = false;
  }
  else {
    if (param_1->parent != (_OBJ76 *)0x0) {
      param_1 = obj_get_root(param_1);
    }
    iVar3 = IsCraft(param_1);
    if (((iVar3 != 0) && ((param_1->flags & 0x200) == 0)) &&
       (this_00 = param_1->gameObj, this_00->aiProcess == (AiProcess *)0x0)) {
      piVar7 = &this_00->_padding_;
      iVar3 = (**(code **)*piVar7)();
      if (0 < *(int *)(iVar3 + 0x58)) {
        iVar3 = Net_IsNetGame();
        if (iVar3 != 0) {
          GameObject::SetObjective(this_00,false);
          DistributedObject::SetLocal((DistributedObject *)piVar7);
        }
        bVar2 = GameObject::EnemyP((GameObject *)this,this_00);
        if (bVar2) {
          GameObject::ClearCommand(this_00);
          GameObject::SetCommand(this_00,CMD_NONE);
        }
        iVar3 = (**(code **)(*piVar7 + 4))();
        (**(code **)(*piVar7 + 8))(this->_padding_);
        this_00->curPilot = (GameObjectClass *)this->_padding_;
        if (this == (Person *)GameObject::userObject) {
          (**(code **)(this_00->_padding_ + 0xc))();
        }
        else {
          pAVar4 = AiMission::GetCurrent();
          (**(code **)(pAVar4->_padding_ + 0x18))(this_00);
        }
        GameObject::SetPerceivedTeam(this_00,iVar3);
        iVar3 = Net_IsNetGame();
        if (iVar3 != 0) {
          iVar3 = (**(code **)(*piVar7 + 0x30))();
          *(uint *)(iVar3 + 0x14) = *(uint *)(iVar3 + 0x14) & 0xfffffffb;
        }
        if ((undefined4 *)this->_padding_ != (undefined4 *)0x0) {
          (*(code *)**(undefined4 **)this->_padding_)(1);
          this->_padding_ = 0;
        }
        obj_set_flag((_OBJ76 *)this->_padding_,0x201);
        return false;
      }
    }
    pCVar6 = param_2;
    piVar7 = (int *)(this->_padding_ + 0x4c);
    for (iVar3 = 0x1e; iVar3 != 0; iVar3 = iVar3 + -1) {
      *piVar7 = pCVar6->collided;
      pCVar6 = (CLSN_INFO *)&pCVar6->obj;
      piVar7 = piVar7 + 1;
    }
    pEVar5 = ClassGetEuler(&local_b8,param_1);
    pfVar8 = local_70;
    for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar8 = pEVar5->mass;
      pEVar5 = (EULER *)&pEVar5->mass_inv;
      pfVar8 = pfVar8 + 1;
    }
    local_1c = (float)this->_padding_;
    local_18 = (float)this->_padding_;
    local_14 = (float)this->_padding_;
    local_28.x = local_58 - local_1c;
    local_28.y = local_54 - local_18;
    local_28.z = local_50 - local_14;
    if (1.0 < (param_2->normal).x * local_28.x +
              (param_2->normal).y * local_28.y + (param_2->normal).z * local_28.z) {
      local_10 = local_28.x;
      local_c = local_28.y;
      local_8 = local_28.z;
      Damage_Resolve((_OBJ76 *)this->_padding_,param_1,&local_28,&param_2->normal,&param_2->point);
    }
    bVar2 = true;
  }
  return bVar2;
}
