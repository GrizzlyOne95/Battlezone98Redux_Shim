/*
 * Entry: 00530f47
 * Name: LauncherClass::LauncherClass
 * Namespace: LauncherClass
 * Signature: LauncherClass * LauncherClass(LauncherClass * this, LauncherClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

LauncherClass * __thiscall
LauncherClass::LauncherClass(LauncherClass *this,LauncherClass *param_1,long64 param_2)

{
  float *pfVar1;
  int iVar2;
  float fVar3;
  longlong lVar4;
  int iVar5;
  int *piVar6;
  uint uVar7;
  int iVar8;
  undefined4 unaff_EDI;
  char local_20 [4];
  ParameterDB local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  WeaponClass::WeaponClass
            ((WeaponClass *)this,(WeaponClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB(&local_1c,(char *)&this->_padding_);
  iVar5 = this->_padding_;
  if (iVar5 == 0) {
    this->ammoCost = param_1->ammoCost;
    fVar3 = param_1->lockRange;
  }
  else {
    this->ammoCost = *(long *)(iVar5 + 0x48);
    fVar3 = *(float *)(iVar5 + 0x50) * *(float *)(iVar5 + 0x4c);
  }
  pfVar1 = &this->lockRange;
  *pfVar1 = fVar3;
  ParameterDB::Get(&local_1c,0xfa72719b,0x742c80cf,pfVar1,*pfVar1);
  ParameterDB::Get(&local_1c,0xfa72719b,0xd9356908,&this->shotDelay,param_1->shotDelay);
  ParameterDB::Get(&local_1c,0xfa72719b,0xf7e186b5,&this->lockDelay,param_1->lockDelay);
  ParameterDB::Get(&local_1c,0xfa72719b,0xa3f03b49,&this->coneAngle,param_1->coneAngle);
  ParameterDB::Get(&local_1c,0xfa72719b,0x3ab425d,this->lockingSound,0x10,param_1->lockingSound);
  ParameterDB::Get(&local_1c,0xfa72719b,0x4e2778a,local_18,0x10,(char *)0x0);
  if (local_18[0] == '\0') {
    iVar5 = this->_padding_;
  }
  else {
    iVar5 = GetSpriteIndex(local_18);
  }
  this->lockingReticle = iVar5;
  ParameterDB::Get(&local_1c,0xfa72719b,0x27b5cb2,this->lockedSound,0x10,param_1->lockedSound);
  ParameterDB::Get(&local_1c,0xfa72719b,0x748a8151,local_18,0x10,(char *)0x0);
  if (local_18[0] == '\0') {
    this->lockingReticle = this->_padding_;
  }
  else {
    iVar5 = GetSpriteIndex(local_18);
    this->lockedReticle = iVar5;
  }
  ParameterDB::Get(&local_1c,0xfa72719b,0xc188a147,&this->targetCount,0);
  lVar4 = (ulonglong)(uint)this->targetCount * 4;
  piVar6 = operator_new__(-(uint)((int)((ulonglong)lVar4 >> 0x20) != 0) | (uint)lVar4);
  this->targetReticle = piVar6;
  iVar5 = 0;
  if (0 < this->targetCount) {
    do {
      iVar2 = iVar5 + 1;
      sprintf(local_20,"%02d",iVar2);
      uVar7 = Hash(local_20,0xa3a90a78);
      ParameterDB::Get(&local_1c,0xfa72719b,uVar7,local_18,0x10,(char *)0x0);
      iVar8 = GetSpriteIndex(local_18);
      this->targetReticle[iVar5] = iVar8;
      iVar5 = iVar2;
    } while (iVar2 < this->targetCount);
  }
  ParameterDB::~ParameterDB(&local_1c);
  return this;
}
