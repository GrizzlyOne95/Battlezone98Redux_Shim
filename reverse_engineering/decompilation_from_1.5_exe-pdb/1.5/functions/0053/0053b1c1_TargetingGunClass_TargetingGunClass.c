/*
 * Entry: 0053b1c1
 * Name: TargetingGunClass::TargetingGunClass
 * Namespace: TargetingGunClass
 * Signature: TargetingGunClass * TargetingGunClass(TargetingGunClass * this, TargetingGunClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

TargetingGunClass * __thiscall
TargetingGunClass::TargetingGunClass
          (TargetingGunClass *this,TargetingGunClass *param_1,long64 param_2)

{
  OrdnanceClass *pOVar1;
  int iVar2;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  undefined4 local_24;
  undefined4 local_20;
  ParameterDB local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  WeaponClass::WeaponClass
            ((WeaponClass *)this,(WeaponClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB(&local_1c,(char *)&this->_padding_);
  ParameterDB::Get(&local_1c,0xce3a7e4a,0x760b0e1f,(long64 *)&local_24,
                   CONCAT44(unaff_ESI,(undefined4)param_2));
  pOVar1 = OrdnanceClass::Find(CONCAT44(local_20,local_24));
  this->leaderClass = pOVar1;
  ParameterDB::Get(&local_1c,0xce3a7e4a,0xe4cf54db,this->leaderSound,0x10,param_1->leaderSound);
  ParameterDB::Get(&local_1c,0xce3a7e4a,0xd9356908,&this->shotDelay,param_1->shotDelay);
  ParameterDB::Get(&local_1c,0xce3a7e4a,0x16c2de34,&this->firstDelay,param_1->firstDelay);
  ParameterDB::Get(&local_1c,0xce3a7e4a,0xd76f37db,&this->salvoDelay,param_1->salvoDelay);
  ParameterDB::Get(&local_1c,0xce3a7e4a,0x9260ea63,&this->salvoCount,param_1->salvoCount);
  ParameterDB::Get(&local_1c,0xce3a7e4a,0x4e2778a,local_18,0x10,(char *)0x0);
  if (local_18[0] == '\0') {
    iVar2 = param_1->lockingReticle;
  }
  else {
    iVar2 = GetSpriteIndex(local_18);
  }
  this->lockingReticle = iVar2;
  ParameterDB::Get(&local_1c,0xce3a7e4a,0x748a8151,local_18,0x10,(char *)0x0);
  if (local_18[0] == '\0') {
    iVar2 = param_1->lockedReticle;
  }
  else {
    iVar2 = GetSpriteIndex(local_18);
  }
  this->lockedReticle = iVar2;
  ParameterDB::~ParameterDB(&local_1c);
  return this;
}
