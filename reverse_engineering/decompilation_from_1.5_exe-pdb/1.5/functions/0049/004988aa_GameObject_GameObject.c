/*
 * Entry: 004988aa
 * Name: GameObject::GameObject
 * Namespace: GameObject
 * Signature: GameObject * GameObject(GameObject * this, _OBJ76 * param_1, GameObjectClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall
GameObject::GameObject(GameObject *this,_OBJ76 *param_1,GameObjectClass *param_2)

{
  float fVar1;
  _OBJ76 *p_Var2;
  GameObjectClass *pGVar3;
  vector<GameObject_*,std::allocator<GameObject_*>_> *this_00;
  tagENTITY *ptVar4;
  MAT_3D *pMVar5;
  SPHERE *pSVar6;
  ulong uVar7;
  Carrier *pCVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  AiCmdInfo *pAVar12;
  char (*pacVar13) [4];
  MAT_3D *pMVar14;
  AiCmdInfo *pAVar15;
  MAT_3D local_8c;
  MAT_3D local_4c;
  WeaponClass *local_c;
  _OBJ76 *local_8;
  
  Attachable::Attachable((Attachable *)this);
  DistributedObject::DistributedObject((DistributedObject *)&this->_padding_);
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  this->obj = param_1;
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->objClass = param_2;
  ModeList::RemoveAllModes(&this->modeList);
  (this->modeList).activeSlot = -1;
  this->obj->gameObj = this;
  if (objectList == (vector<GameObject_*,std::allocator<GameObject_*>_> *)0x0) {
    this_00 = ::operator_new(0x18);
    if (this_00 == (vector<GameObject_*,std::allocator<GameObject_*>_> *)0x0) {
      objectList = (vector<GameObject_*,std::allocator<GameObject_*>_> *)0x0;
    }
    else {
      objectList = std::vector<GameObject_*,std::allocator<GameObject_*>_>::
                   vector<GameObject_*,std::allocator<GameObject_*>_>(this_00);
    }
    std::vector<GameObject_*,std::allocator<GameObject_*>_>::reserve(objectList,0x300);
  }
  if ((this->obj->flags & 0x10) != 0) {
    userTeamNumber = *(ushort *)((int)&this->obj->flags + 2) & 0xf;
    userObject = this;
    userTeamList = Team::GetTeam(userTeamNumber);
  }
  iVar9 = nextSeqNo;
  this->teamNumber = -1;
  this->teamSlot = -1;
  nextSeqNo = nextSeqNo + 1;
  this->seqNo = iVar9;
  p_Var2 = this->obj;
  this->seen = 0;
  this->locked = 0;
  this->teamList = (Team *)0x0;
  this->perceivedTeam = *(ushort *)((int)&p_Var2->flags + 2) & 0xf;
  if (p_Var2->parent == (_OBJ76 *)0x0) {
    ptVar4 = FindObjectEntity(param_1);
    this->ent = ptVar4;
    param_1 = (_OBJ76 *)this;
    std::vector<GameObject_*,std::allocator<GameObject_*>_>::push_back
              (objectList,(GameObject **)&param_1);
    ptVar4 = this->ent;
    if (ptVar4 != (tagENTITY *)0x0) {
      Vector_Transform(&this->pos,&(ptVar4->bSphere).origin,1,&this->obj->transform);
    }
  }
  else {
    this->ent = (tagENTITY *)0x0;
    pMVar5 = obj_rel_parent_matrix(&local_8c,p_Var2,(_OBJ76 *)0x0);
    p_Var2 = this->obj;
    pMVar14 = &local_4c;
    for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
      pMVar14->right_x = pMVar5->right_x;
      pMVar5 = (MAT_3D *)&pMVar5->right_y;
      pMVar14 = (MAT_3D *)&pMVar14->right_y;
    }
    Vector_Transform(&this->pos,&(p_Var2->bSphere).origin,1,&local_4c);
  }
  pGVar3 = param_2;
  this->tug = (GameObject *)0x0;
  this->isCargo = false;
  pAVar12 = &this->nextCmd;
  for (iVar9 = 6; iVar9 != 0; iVar9 = iVar9 + -1) {
    pAVar12->priority = 0;
    pAVar12 = (AiCmdInfo *)&pAVar12->what;
  }
  (this->nextCmd).what = CMD_NONE;
  pAVar12 = &this->nextCmd;
  pAVar15 = &this->curCmd;
  for (iVar9 = 6; iVar9 != 0; iVar9 = iVar9 + -1) {
    pAVar15->priority = pAVar12->priority;
    pAVar12 = (AiCmdInfo *)&pAVar12->what;
    pAVar15 = (AiCmdInfo *)&pAVar15->what;
  }
  this->aiProcess = (AiProcess *)0x0;
  this->label = (char *)0x0;
  this->independence = 1;
  this->curPilot = (GameObjectClass *)0x0;
  SetName(this,param_2->unitName);
  this->who_shot_JR = 0;
  this->playerCollide = -1e+30;
  this->hitOrdClass = (OrdnanceClass *)0x0;
  this->playerShot = -1e+30;
  this->who_i_shot = 0;
  this->friendCollide = -1e+30;
  this->friendShot = -1e+30;
  this->enemyCollide = -1e+30;
  this->enemyShot = -1e+30;
  this->when_i_shot = -1e+30;
  param_1 = (_OBJ76 *)AdjustedMaxHealth(*(ushort *)((int)&this->obj->flags + 2) & 0xf,pGVar3);
  this->maxHealth = (float)(int)param_1;
  SetCurHealth(this,(float)(int)param_1);
  this->healthRatio = 1.0;
  SetMaxAmmo(this,pGVar3->maxAmmo);
  SetCurAmmo(this,this->maxAmmo ^ 0x33333333);
  if ((int)(this->maxAmmo ^ 0x33333333U) < 1) {
    fVar1 = 0.0;
  }
  else {
    fVar1 = 1.0;
  }
  this->ammoRatio = fVar1;
  iVar9 = pGVar3->weaponMask;
  uVar10 = 0;
  this->weaponMask = 0;
  param_1 = (_OBJ76 *)0x5;
  do {
    if (iVar9 % 10 < 1) {
      uVar11 = 0;
    }
    else {
      uVar11 = 0x10;
    }
    uVar10 = (int)uVar10 >> 1 | uVar11;
    param_1 = (_OBJ76 *)((int)&param_1[-1].bBox.max.z + 3);
    iVar9 = iVar9 / 10;
  } while (param_1 != (_OBJ76 *)0x0);
  this->weaponMask = uVar10;
  if (pGVar3->collisionRadius <= 0.0) {
    pSVar6 = GetSphere(this);
    fVar1 = pSVar6->radius;
  }
  else {
    fVar1 = pGVar3->collisionRadius;
  }
  this->collisionRadius = fVar1;
  uVar7 = Get_Time_Long();
  this->scanner = (Scanner *)0x0;
  this->jammer = (Jammer *)0x0;
  this->carrier = (Carrier *)0x0;
  param_1 = (_OBJ76 *)0x0;
  this->createTime = uVar7;
  pacVar13 = pGVar3->weaponHard;
  do {
    local_c = *(WeaponClass **)(pacVar13 + 5);
    param_2 = (GameObjectClass *)0x0;
    if ((*pacVar13)[0] != '\0') {
      if (this->carrier == (Carrier *)0x0) {
        pCVar8 = ::operator_new(0x40);
        if (pCVar8 == (Carrier *)0x0) {
          pCVar8 = (Carrier *)0x0;
        }
        else {
          pCVar8 = Carrier::Carrier(pCVar8,this);
        }
        this->carrier = pCVar8;
      }
      local_8 = FindHardpoint(this->obj,*pacVar13);
      if (local_c != (WeaponClass *)0x0) {
        if (local_8 == (_OBJ76 *)0x0) {
          DEBUG_systemWarning("Object \'%.8s\' slot #%d: no hardpoint named \'%s\'");
        }
        else {
          param_2 = (GameObjectClass *)WeaponClass::Build(local_c,this->obj,local_8);
          if (param_2 == (GameObjectClass *)0x0) {
            DEBUG_systemWarning(
                               "Object \'%.8s\' slot #%d: couldn\'t add weapon \'%.8s\' to hardpoint \'%s\'"
                               );
          }
        }
      }
      Carrier::SetHardpoint(this->carrier,(int)param_1,local_8);
      Carrier::SetWeapon(this->carrier,(int)param_1,(Weapon *)param_2);
    }
    param_1 = (_OBJ76 *)&(param_1->objHandle)._s_0.field_0x1;
    pacVar13 = pacVar13 + 1;
  } while ((int)param_1 < 5);
  pCVar8 = this->carrier;
  if (pCVar8 != (Carrier *)0x0) {
    pCVar8->enabled = pCVar8->existant;
    Carrier::SetSelected(this->carrier,0xffffffff);
  }
  this->illumination = 0.0;
  this->targetHandle = 0;
  this->ownerHandle = 0;
  this->hitch = (_OBJ76 *)0x0;
  Attachable::InitAttachments((Attachable *)this,gameObjectClass.attachCount);
  this->isVisible = 0;
  this->isObjective = false;
  this->isSelected = false;
  InitEuler(&this->euler);
  UpdatePosition(this);
  GameFeature::AddObjectEvent(this);
  this->_padding_ = 0;
  this->_padding_ = -0x40100000;
  return this;
}
