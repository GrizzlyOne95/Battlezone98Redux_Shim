/*
 * Entry: 0053f6a6
 * Name: WeaponMineClass::WeaponMineClass
 * Namespace: WeaponMineClass
 * Signature: WeaponMineClass * WeaponMineClass(WeaponMineClass * this, WeaponMineClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponMineClass * __thiscall
WeaponMineClass::WeaponMineClass(WeaponMineClass *this,WeaponMineClass *param_1,long64 param_2)

{
  WeaponMineClass *pWVar1;
  WeaponClass *pWVar2;
  long lVar3;
  uint unaff_ESI;
  undefined4 unaff_EDI;
  WeaponMineClass *local_c;
  WeaponMineClass *local_8;
  
  pWVar1 = param_1;
  local_c = this;
  local_8 = this;
  MineClass::MineClass((MineClass *)this,(MineClass *)param_1,CONCAT44(unaff_EDI,(int)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x47d843ca,0xe3635ff7,&this->searchRadius,
                   pWVar1->searchRadius);
  ParameterDB::Get((ParameterDB *)&param_1,0x47d843ca,0xcaaa3778,&this->heightScale,
                   pWVar1->heightScale);
  ParameterDB::Get((ParameterDB *)&param_1,0x47d843ca,0xfbf47dba,(long64 *)&local_c,
                   (ulonglong)unaff_ESI << 0x20);
  if (local_c == (WeaponMineClass *)0x0 && local_8 == (WeaponMineClass *)0x0) {
    pWVar2 = pWVar1->weaponClass;
  }
  else {
    pWVar2 = WeaponClass::Find(CONCAT44(local_8,local_c));
  }
  this->weaponClass = pWVar2;
  if (((pWVar2 == (WeaponClass *)0x0) || (pWVar2->sig == 0x44495350)) || (pWVar2->sig == 0x5244524c)
     ) {
    lVar3 = 0;
  }
  else {
    lVar3 = 1;
  }
  ParameterDB::Get((ParameterDB *)&param_1,0x47d843ca,0xb30f7ac,(long *)&param_2,lVar3);
  this->checkSight = (int)param_2 != 0;
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
