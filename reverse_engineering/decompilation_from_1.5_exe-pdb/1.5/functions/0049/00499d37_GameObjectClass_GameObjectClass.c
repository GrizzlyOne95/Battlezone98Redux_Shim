/*
 * Entry: 00499d37
 * Name: GameObjectClass::GameObjectClass
 * Namespace: GameObjectClass
 * Signature: GameObjectClass * GameObjectClass(GameObjectClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall GameObjectClass::GameObjectClass(GameObjectClass *this)

{
  vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *this_00;
  int iVar1;
  char *pcVar2;
  BBOX *pBVar3;
  GameObjectClass **ppGVar4;
  GameObjectClass *local_8;
  
  local_8 = this;
  Attachable::Attachable((Attachable *)this);
  ppGVar4 = &local_8;
  this->_padding_ = (int)&_vftable_;
  local_8 = this;
  this_00 = GetProtoList();
  std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::push_back(this_00,ppGVar4);
  this->proto = this;
  this->sig = 0x474f424a;
  this->label = (char *)0x0;
  this->class_id = CLASS_ID_NONE;
  *(undefined4 *)&this->base = 0;
  *(undefined4 *)((int)&this->base + 4) = 0;
  *(undefined4 *)&this->cfg = 0;
  *(undefined4 *)((int)&this->cfg + 4) = 0;
  this->odf[0] = '\0';
  this->odf[1] = '\0';
  this->odf[2] = '\0';
  this->odf[3] = '\0';
  this->odf[4] = '\0';
  this->odf[5] = '\0';
  this->odf[6] = '\0';
  this->odf[7] = '\0';
  this->odf[8] = '\0';
  this->odf[9] = '\0';
  this->odf[10] = '\0';
  this->odf[0xb] = '\0';
  this->odf[0xc] = '\0';
  this->odf[0xd] = '\0';
  this->odf[0xe] = '\0';
  this->odf[0xf] = '\0';
  this->buildTime = 5.0;
  this->scrapCost = 0x7fffffff;
  this->scrapValue = 0;
  this->pilotCost = 0;
  this->maxHealth = 0;
  this->maxAmmo = 0;
  this->unitNameIndex = 0;
  pcVar2 = this->unitName;
  for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
    pcVar2[0] = '\0';
    pcVar2[1] = '\0';
    pcVar2[2] = '\0';
    pcVar2[3] = '\0';
    pcVar2 = pcVar2 + 4;
  }
  pcVar2 = this->aiName;
  for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
    pcVar2[0] = '\0';
    pcVar2[1] = '\0';
    pcVar2[2] = '\0';
    pcVar2[3] = '\0';
    pcVar2 = pcVar2 + 4;
  }
  pcVar2 = this->aiName2;
  for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
    pcVar2[0] = '\0';
    pcVar2[1] = '\0';
    pcVar2[2] = '\0';
    pcVar2[3] = '\0';
    pcVar2 = pcVar2 + 4;
  }
  this->collisionRadius = -1e+30;
  this->imageSignature = 1.0;
  this->radarSignature = 1.0;
  this->heatSignature = 1.0;
  this->nation = '\0';
  this->weaponMask = 0x2b67;
  this->weaponHard[0] = (char  [4])0x0;
  this->weaponHard[1] = (char  [4])0x0;
  this->weaponHard[2] = (char  [4])0x0;
  this->weaponHard[3] = (char  [4])0x0;
  this->weaponHard[4] = (char  [4])0x0;
  this->weaponClass[0] = (WeaponClass *)0x0;
  this->weaponClass[1] = (WeaponClass *)0x0;
  this->weaponClass[2] = (WeaponClass *)0x0;
  this->weaponClass[3] = (WeaponClass *)0x0;
  this->weaponClass[4] = (WeaponClass *)0x0;
  pBVar3 = &this->bBox;
  for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
    (pBVar3->min).x = 0.0;
    pBVar3 = (BBOX *)&(pBVar3->min).y;
  }
  (this->bSphere).origin.x = 0.0;
  (this->bSphere).origin.y = 0.0;
  (this->bSphere).origin.z = 0.0;
  (this->bSphere).radius = 0.0;
  (this->bSphere).radius = -1e+30;
  this->categoryMin = -1;
  this->categoryMax = -1;
  this->infoText = (char *)0x0;
  return this;
}
