/*
 * Entry: 004a6a3f
 * Name: Person::DamageAlloc
 * Namespace: Person
 * Signature: bool DamageAlloc(Person * this, DAMAGE * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Person::DamageAlloc(Person *this,DAMAGE *param_1,VECTOR_3D *param_2)

{
  uint *puVar1;
  bool bVar2;
  Explosion *pEVar3;
  char *pcVar4;
  uint uVar5;
  int iVar6;
  int extraout_EAX;
  int iVar7;
  uint uVar8;
  float *pfVar9;
  MAT_3D *pMVar10;
  float fVar11;
  char cVar12;
  _OBJ76 *p_Var13;
  GAS_CTRL *pGVar14;
  MAT_3D local_4c;
  int local_c;
  float local_8;
  
  if (((*(uint *)(this->_padding_ + 0x14) & 0x1000200) != 0) ||
     ((UserProfilePtr->playOption & 1) != 0)) {
    return false;
  }
  GameObject::SetDamageFlags((GameObject *)&this[-1]._padding_,param_1);
  local_8 = param_1->dmg_value;
  if ((param_1->field_0x8 & 0xf) == 8) {
    local_8 = local_8 * 10.0;
  }
  if ((GameObject *)&this[-1]._padding_ == GameObject::userObject) {
    ColorFade::SetFade(&colorFade,local_8 * 0.03,5.0,0xff,0,0);
  }
  iVar7 = this->_padding_;
  local_c = iVar7;
  bVar2 = DistributedObject::IsRemote((DistributedObject *)this);
  if ((!bVar2) && (GameObject::AddHealth((GameObject *)this,-local_8), (float)this->_padding_ < 0.0)
     ) {
    puVar1 = (uint *)(this->_padding_ + 0x14);
    *puVar1 = *puVar1 | 0x1000000;
    fVar11 = (float)this->_padding_;
    pfVar9 = (float *)(this->_padding_ + 0x20);
    pMVar10 = &local_4c;
    for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
      pMVar10->right_x = *pfVar9;
      pfVar9 = pfVar9 + 1;
      pMVar10 = (MAT_3D *)&pMVar10->right_y;
    }
    local_4c.posit_x = (double)fVar11;
    local_4c.posit_y = (double)(float)this->_padding_;
    local_4c.posit_z = (double)(float)this->_padding_;
    pEVar3 = ExplosionClass::Build(xplSecondary,&local_4c,(_OBJ76 *)0x0);
    if ((param_1->field_0x8 & 8) == 0) {
      if (this->_padding_ == 0) goto LAB_004a6b94;
      pGVar14 = (GAS_CTRL *)0x0;
      p_Var13 = pEVar3->obj;
      uVar5 = rand();
      pcVar4 = (char *)((uVar5 % 5) * 0x10 + 0x41c + local_c);
    }
    else {
      pGVar14 = (GAS_CTRL *)0x0;
      p_Var13 = pEVar3->obj;
      pcVar4 = (char *)(local_c + 0x46c);
    }
    DoAudioFixedLoc(pcVar4,p_Var13,pGVar14);
LAB_004a6b94:
    iVar7 = Net_IsNetGame();
    if ((((iVar7 != 0) && (iVar7 = (**(code **)(this->_padding_ + 4))(), iVar7 != 0)) &&
        (0 < *(int *)(local_c + 0x58))) && ((*(byte *)(this->_padding_ + 0x14) & 4) == 0)) {
      puVar1 = (uint *)(this->_padding_ + 0x14);
      *puVar1 = *puVar1 | 4;
      DistributedObject::RecordDeath
                ((DistributedObject *)this,*(ushort *)&param_1->field_0x8 >> 6 & 0xf);
      uVar8 = (uint)((GameObject *)&this[-1]._padding_ == GameObject::userObject);
      uVar5 = *(ushort *)&param_1->field_0x8 >> 6 & 0xf;
      cVar12 = 'P';
      iVar7 = (**(code **)(this->_padding_ + 4))();
      KillMessage(iVar7,uVar5,cVar12,uVar8);
    }
    return true;
  }
  if ((float)this->_padding_ <= 0.0) {
    return false;
  }
  if (this->_padding_ == 0) {
    return false;
  }
  fVar11 = Get_TimeLocal();
  if (fVar11 <= (float)this->_padding_) {
    return false;
  }
  if ((param_1->field_0x8 & 4) == 0) {
    if (local_8 <= 0.0) {
      pGVar14 = (GAS_CTRL *)0x0;
      p_Var13 = (_OBJ76 *)this->_padding_;
      pcVar4 = (char *)(iVar7 + 0x48c);
      goto LAB_004a6ccd;
    }
    _ftol2_sse();
    iVar6 = rand();
    uVar5 = iVar6 >> 8 & 3;
    if (uVar5 == 1) {
      iVar6 = extraout_EAX + 1;
    }
    else {
      iVar6 = extraout_EAX;
      if (uVar5 == 2) {
        iVar6 = extraout_EAX + -1;
      }
    }
    if (iVar6 < 0) {
      iVar6 = 0;
    }
    else if (5 < iVar6) {
      iVar6 = 5;
    }
    pGVar14 = (GAS_CTRL *)0x0;
    p_Var13 = (_OBJ76 *)this->_padding_;
    iVar6 = iVar6 * 0x10 + 0x39c;
  }
  else {
    pGVar14 = (GAS_CTRL *)0x0;
    p_Var13 = (_OBJ76 *)this->_padding_;
    iVar6 = rand();
    iVar6 = (iVar6 >> 8 & 1U) * 0x10 + 0x3fc;
  }
  pcVar4 = (char *)(iVar6 + iVar7);
LAB_004a6ccd:
  DoAudioNew(pcVar4,p_Var13,pGVar14);
  fVar11 = Get_TimeLocal();
  this->_padding_ = (int)(fVar11 + 0.5);
  return false;
}
