/*
 * Entry: 0052f7a6
 * Name: FlamePuffClass::FlamePuffClass
 * Namespace: FlamePuffClass
 * Signature: FlamePuffClass * FlamePuffClass(FlamePuffClass * this, FlamePuffClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

FlamePuffClass * __thiscall
FlamePuffClass::FlamePuffClass(FlamePuffClass *this,FlamePuffClass *param_1,long64 param_2)

{
  int iVar1;
  undefined4 unaff_EDI;
  int local_20;
  ParameterDB local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  BulletClass::BulletClass
            ((BulletClass *)this,(BulletClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB(&local_1c,(char *)&this->_padding_);
  ParameterDB::Get(&local_1c,0x8e290509,0x278d7166,&this->flameRadius,param_1->flameRadius);
  ParameterDB::Get(&local_1c,0x8e290509,0xc7dc5ce9,&this->frameDelay,param_1->frameDelay);
  ParameterDB::Get(&local_1c,0x8e290509,0xb051e2db,local_18,0x10,(char *)0x0);
  if (local_18[0] == '\0') {
    iVar1 = param_1->flameFirst;
  }
  else {
    iVar1 = GetSpriteIndex(local_18);
  }
  this->flameFirst = iVar1;
  ParameterDB::Get(&local_1c,0x8e290509,0x5d27caba,&local_20,0);
  this->flameLast = this->flameFirst + -1 + local_20;
  ParameterDB::~ParameterDB(&local_1c);
  return this;
}
