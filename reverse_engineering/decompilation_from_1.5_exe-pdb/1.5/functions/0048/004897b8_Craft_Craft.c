/*
 * Entry: 004897b8
 * Name: Craft::Craft
 * Namespace: Craft
 * Signature: Craft * Craft(Craft * this, _OBJ76 * param_1, CraftClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Craft * __thiscall Craft::Craft(Craft *this,_OBJ76 *param_1,CraftClass *param_2)

{
  int iVar1;
  _OBJ76 *p_Var2;
  SmokeEmitter *pSVar3;
  CraftClass *pCVar4;
  VEHICLE *pVVar5;
  Scanner *pSVar6;
  float *pfVar7;
  int iVar8;
  int *piVar9;
  float10 extraout_ST0;
  
  pCVar4 = param_2;
  GameObject::GameObject((GameObject *)this,param_1,(GameObjectClass *)param_2);
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  init_vehicle((_OBJ76 *)this->_padding_);
  this->state = UNDEPLOYED;
  this->abandoned = 0;
  pVVar5 = get_obj_vhcl(param_1);
  this->vhcl = pVVar5;
  pVVar5->entity = (tagENTITY *)this->_padding_;
  this->pathingType = 0;
  GameObject::SetCommand((GameObject *)this,CMD_NONE);
  if (0.0 < pCVar4->rangeScan) {
    pSVar6 = operator_new(0x14);
    if (pSVar6 == (Scanner *)0x0) {
      pSVar6 = (Scanner *)0x0;
    }
    else {
      pSVar6 = Scanner::Scanner(pSVar6,(GameObject *)this);
    }
    this->_padding_ = (int)pSVar6;
    pSVar6->range = pCVar4->rangeScan;
    *(float *)(this->_padding_ + 4) = pCVar4->periodScan;
  }
  this->fPersonEjectRatio = pCVar4->fPersonEjectRatio;
  if (0.0 < pCVar4->velocJam) {
    pfVar7 = operator_new(8);
    if (pfVar7 == (float *)0x0) {
      pfVar7 = (float *)0x0;
    }
    else {
      pfVar7[1] = (float)this;
      *pfVar7 = 0.0;
    }
    this->_padding_ = (int)pfVar7;
    *pfVar7 = pCVar4->velocJam;
  }
  pVVar5 = this->vhcl;
  iVar1 = this->_padding_;
  piVar9 = &this->_padding_;
  for (iVar8 = 0x12; pVVar5 = (VEHICLE *)&pVVar5->euler, iVar8 != 0; iVar8 = iVar8 + -1) {
    *piVar9 = (int)((EULER *)pVVar5)->mass;
    piVar9 = piVar9 + 1;
  }
  if (((iVar1 == 0) || (*(int *)(iVar1 + 0x24) != 1)) ||
     (piVar9 = *(int **)(iVar1 + 0x28), piVar9 == (int *)0x0)) {
    p_Var2 = (_OBJ76 *)this->_padding_;
    get_obj_bounding_box(p_Var2,&(p_Var2->bBox).min,&(p_Var2->bBox).max);
  }
  else {
    *(int *)(this->_padding_ + 0xd8) = piVar9[3];
    *(int *)(this->_padding_ + 0xdc) = piVar9[7];
    *(int *)(this->_padding_ + 0xe0) = piVar9[0xb];
    *(int *)(this->_padding_ + 0xe4) = piVar9[*piVar9 + 2];
    *(int *)(this->_padding_ + 0xe8) = piVar9[piVar9[1] + 6];
    *(int *)(this->_padding_ + 0xec) = piVar9[piVar9[2] + 10];
  }
  this->vhcl->timer = -1e+30;
  p_Var2 = (_OBJ76 *)this->_padding_;
  *(undefined1 *)((int)&this->_padding_ + 1) = 0;
  pSVar3 = smokeEffect.smokeWhite;
  this->smokeTimer = 0.0;
  this->smokeCount = 0;
  this->smokeEmitter = pSVar3;
  FindSmokeSource(this,p_Var2);
  this->pitchAng = (float)extraout_ST0;
  this->lastCollideTime = 0;
  param_1 = (_OBJ76 *)this;
  std::vector<Craft_*,std::allocator<Craft_*>_>::push_back(&craftList,(Craft **)&param_1);
  return this;
}
