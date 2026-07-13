/*
 * Entry: 0053f3a0
 * Name: WeaponClass::WeaponClass
 * Namespace: WeaponClass
 * Signature: WeaponClass * WeaponClass(WeaponClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass * __thiscall WeaponClass::WeaponClass(WeaponClass *this)

{
  vector<WeaponClass_*,std::allocator<WeaponClass_*>_> *this_00;
  int iVar1;
  char *pcVar2;
  WeaponClass **ppWVar3;
  WeaponClass *local_8;
  
  ppWVar3 = &local_8;
  this->_padding_ = (int)&_vftable_;
  local_8 = this;
  this_00 = GetProtoList();
  std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::push_back(this_00,ppWVar3);
  this->proto = this;
  this->sig = 0x5745504e;
  this->label = "weapon";
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
  this->ordnanceClass = (OrdnanceClass *)0x0;
  this->wpnNameIndex = 0;
  pcVar2 = this->wpnName;
  for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
    pcVar2[0] = '\0';
    pcVar2[1] = '\0';
    pcVar2[2] = '\0';
    pcVar2[3] = '\0';
    pcVar2 = pcVar2 + 4;
  }
  this->fireSound[0] = '\0';
  this->wpnReticle = 0;
  this->wpnLadder = 0;
  return this;
}
