/*
 * Entry: 004b9443
 * Name: WeaponPowerupClass::WeaponPowerupClass
 * Namespace: WeaponPowerupClass
 * Signature: WeaponPowerupClass * WeaponPowerupClass(WeaponPowerupClass * this, WeaponPowerupClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponPowerupClass * __thiscall
WeaponPowerupClass::WeaponPowerupClass
          (WeaponPowerupClass *this,WeaponPowerupClass *param_1,long64 param_2)

{
  WeaponPowerupClass *pWVar1;
  WeaponClass *pWVar2;
  uint unaff_ESI;
  undefined4 unaff_EDI;
  int in_stack_00000008;
  
  pWVar1 = param_1;
  PowerUpClass::PowerUpClass
            ((PowerUpClass *)this,(PowerUpClass *)param_1,CONCAT44(unaff_EDI,(int)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x397a9ac1,0xfbf47dba,(long64 *)&stack0x00000008,
                   (ulonglong)unaff_ESI << 0x20);
  if (in_stack_00000008 == 0 && (int)param_2 == 0) {
    this->weaponClass = pWVar1->weaponClass;
  }
  else {
    pWVar2 = WeaponClass::Find(CONCAT44((int)param_2,in_stack_00000008));
    this->weaponClass = pWVar2;
    if (pWVar2->wpnName[0] != '\0') {
      this->_padding_ = pWVar2->wpnNameIndex;
      strncpy((char *)&this->_padding_,pWVar2->wpnName,0x20);
    }
  }
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
