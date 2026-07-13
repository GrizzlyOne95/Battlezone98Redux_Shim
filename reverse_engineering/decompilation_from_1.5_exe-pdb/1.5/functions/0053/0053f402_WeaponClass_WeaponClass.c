/*
 * Entry: 0053f402
 * Name: WeaponClass::WeaponClass
 * Namespace: WeaponClass
 * Signature: WeaponClass * WeaponClass(WeaponClass * this, WeaponClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

WeaponClass * __thiscall
WeaponClass::WeaponClass(WeaponClass *this,WeaponClass *param_1,long64 param_2)

{
  char *pcVar1;
  undefined4 *puVar2;
  OrdnanceClass *pOVar3;
  int iVar4;
  uint unaff_EDI;
  undefined4 *puVar5;
  uint in_stack_00000008;
  WeaponClass *local_44;
  int local_40;
  int local_3c;
  WeaponClass *local_38;
  ParameterDB local_34;
  char local_30 [32];
  char local_10 [8];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_38 = param_1;
  this->_padding_ = (int)&_vftable_;
  this->proto = param_1;
  local_44 = this;
  std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::push_back(&classList,&local_44);
  this->sig = param_1->sig;
  this->label = param_1->label;
  *(uint *)&this->cfg = in_stack_00000008 & 0x7f7f7f7f;
  *(uint *)((int)&this->cfg + 4) = (uint)param_2 & 0x7f7f7f7f;
  strncpy(this->odf,(char *)&this->cfg,8);
  this->odf[8] = '\0';
  puVar2 = (undefined4 *)((int)&this->cfg + 7);
  do {
    puVar5 = puVar2;
    puVar2 = (undefined4 *)((int)puVar5 + 1);
  } while (*(char *)((int)puVar5 + 1) != '\0');
  *(undefined4 *)((int)puVar5 + 1) = 0x66646f2e;
  *(undefined1 *)((int)puVar5 + 5) = 0;
  ParameterDB::ParameterDB(&local_34,this->odf);
  ParameterDB::Get(&local_34,0xacda90ab,0x10e6fd23,(long64 *)&local_40,(ulonglong)unaff_EDI << 0x20)
  ;
  if (local_40 == 0 && local_3c == 0) {
    this->ordnanceClass = (OrdnanceClass *)0x0;
  }
  else {
    pOVar3 = OrdnanceClass::Find(CONCAT44(local_3c,local_40));
    this->ordnanceClass = pOVar3;
  }
  ParameterDB::Get(&local_34,0xacda90ab,0xcfde2fc0,this->fireSound,0x10,local_38->fireSound);
  pcVar1 = this->wpnName;
  ParameterDB::Get(&local_34,0xacda90ab,0xf429d8cf,pcVar1,0x20,local_38->wpnName);
  if (*pcVar1 == '\0') {
    this->wpnNameIndex = 0;
  }
  else {
    iVar4 = GetSpriteIndex(pcVar1);
    this->wpnNameIndex = iVar4;
  }
  ParameterDB::Get(&local_34,0xacda90ab,0x1a05f72c,local_30,0x20,(char *)0x0);
  if (local_30[0] == '\0') {
    this->wpnReticle = 0;
  }
  else {
    iVar4 = GetSpriteIndex(local_30);
    this->wpnReticle = iVar4;
  }
  ParameterDB::Get(&local_34,0xacda90ab,0x48dae6d8,local_30,0x20,(char *)0x0);
  if (local_30[0] == '\0') {
    this->wpnLadder = 0;
  }
  else {
    iVar4 = GetSpriteIndex(local_30);
    this->wpnLadder = iVar4;
  }
  ParameterDB::Get(&local_34,0xacda90ab,0xd84e3a3c,&this->wpnPriority,0);
  ParameterDB::Get(&local_34,0xacda90ab,0xf21ccf2c,local_10,8,(char *)0x0);
  iVar4 = _strnicmp(local_10,"CANN",4);
  if (iVar4 == 0) {
    this->wpnCategory = CLASS_ID_CANNON_HARDPOINT;
  }
  else {
    iVar4 = _strnicmp(local_10,"ROCK",4);
    if (iVar4 == 0) {
      this->wpnCategory = CLASS_ID_ROCKET_HARDPOINT;
    }
    else {
      iVar4 = _strnicmp(local_10,"MORT",4);
      if (iVar4 == 0) {
        this->wpnCategory = CLASS_ID_MORTAR_HARDPOINT;
      }
      else {
        iVar4 = _strnicmp(local_10,"SPEC",4);
        this->wpnCategory = (-(uint)(iVar4 != 0) & 0xfffffffc) + CLASS_ID_SPECIAL_HARDPOINT;
      }
    }
  }
  ParameterDB::~ParameterDB(&local_34);
  return this;
}
