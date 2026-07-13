/*
 * Entry: 0052a096
 * Name: BeamClass::BeamClass
 * Namespace: BeamClass
 * Signature: BeamClass * BeamClass(BeamClass * this, BeamClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

BeamClass * __thiscall BeamClass::BeamClass(BeamClass *this,BeamClass *param_1,long64 param_2)

{
  int iVar1;
  undefined4 unaff_EDI;
  ParameterDB local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  BulletClass::BulletClass
            ((BulletClass *)this,(BulletClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB(&local_1c,(char *)&this->_padding_);
  ParameterDB::Get(&local_1c,0xf18c83ca,0x74a4cc84,&this->segmentRadius,param_1->segmentRadius);
  ParameterDB::Get(&local_1c,0xf18c83ca,0x97bf6bf2,&this->segmentLength,param_1->segmentLength);
  ParameterDB::Get(&local_1c,0xf18c83ca,0xc01fedb1,&this->segmentVariance,param_1->segmentVariance);
  ParameterDB::Get(&local_1c,0xf18c83ca,0xe30fe0e9,local_18,0x10,(char *)0x0);
  if (local_18[0] == '\0') {
    this->spriteIndex = 0;
  }
  else {
    iVar1 = GetSpriteIndex(local_18);
    this->spriteIndex = iVar1;
  }
  ParameterDB::~ParameterDB(&local_1c);
  return this;
}
