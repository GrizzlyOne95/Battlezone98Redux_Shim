/*
 * Entry: 0052ccfa
 * Name: ChargeGunClass::ChargeGunClass
 * Namespace: ChargeGunClass
 * Signature: ChargeGunClass * ChargeGunClass(ChargeGunClass * this, ChargeGunClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ChargeGunClass * __thiscall
ChargeGunClass::ChargeGunClass(ChargeGunClass *this,ChargeGunClass *param_1,long64 param_2)

{
  longlong lVar1;
  OrdnanceData *pOVar2;
  uint uVar3;
  OrdnanceClass *pOVar4;
  int iVar5;
  int iVar6;
  char *unaff_ESI;
  undefined4 unaff_EDI;
  long64 *plVar7;
  char *pcVar8;
  long lVar9;
  float fVar10;
  undefined4 uVar11;
  int local_2c;
  int local_28;
  int local_24;
  char local_20 [4];
  ParameterDB local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  CannonClass::CannonClass
            ((CannonClass *)this,(CannonClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB(&local_1c,(char *)&this->_padding_);
  ParameterDB::Get(&local_1c,0x700e4deb,0x2e2012e5,&this->startRate,param_1->startRate);
  ParameterDB::Get(&local_1c,0x700e4deb,0xb9782373,&this->deltaRate,param_1->deltaRate);
  ParameterDB::Get(&local_1c,0x700e4deb,0xbc8f5a39,&this->startVolume,param_1->startVolume);
  ParameterDB::Get(&local_1c,0x700e4deb,0xedfcc3cb,&this->deltaVolume,param_1->deltaVolume);
  ParameterDB::Get(&local_1c,0x700e4deb,0x7e82425c,&this->ordnanceCount,param_1->ordnanceCount);
  iVar6 = 0x24;
  lVar1 = (ulonglong)(this->ordnanceCount + 1) * 0x24;
  pOVar2 = operator_new__(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1);
  this->ordnanceData = pOVar2;
  pOVar2->shotDelay = 0.0;
  this->ordnanceData->salvoCount = 0;
  this->ordnanceData->salvoDelay = 0.0;
  this->ordnanceData->fireSound[0] = '\0';
  this->ordnanceData->ordnanceClass = (OrdnanceClass *)0x0;
  this->ordnanceData->wpnReticle = this->_padding_;
  local_24 = 1;
  if (0 < this->ordnanceCount) {
    do {
      sprintf(local_20,"%d",local_24);
      fVar10 = (float)local_24 * 0.2;
      pcVar8 = this->ordnanceData->fireSound + iVar6 + -0xc;
      uVar3 = Hash(local_20,0xd9356908);
      ParameterDB::Get(&local_1c,0x700e4deb,uVar3,(float *)pcVar8,fVar10);
      lVar9 = 1;
      pcVar8 = this->ordnanceData->fireSound + iVar6 + -8;
      uVar3 = Hash(local_20,0x9260ea63);
      ParameterDB::Get(&local_1c,0x700e4deb,uVar3,(long *)pcVar8,lVar9);
      pcVar8 = this->ordnanceData->fireSound + iVar6 + -4;
      fVar10 = 0.1;
      uVar3 = Hash(local_20,0xd76f37db);
      ParameterDB::Get(&local_1c,0x700e4deb,uVar3,(float *)pcVar8,fVar10);
      pOVar2 = this->ordnanceData;
      uVar3 = Hash(local_20,0xcfde2fc0);
      ParameterDB::Get(&local_1c,0x700e4deb,uVar3,pOVar2->fireSound + iVar6,0x10,(char *)0x0);
      uVar11 = 0;
      plVar7 = (long64 *)&local_2c;
      uVar3 = Hash(local_20,0x10e6fd23);
      ParameterDB::Get(&local_1c,0x700e4deb,uVar3,plVar7,CONCAT44(unaff_ESI,uVar11));
      if (local_2c == 0 && local_28 == 0) {
        pcVar8 = this->ordnanceData->fireSound + iVar6 + 0x10;
        pcVar8[0] = '\0';
        pcVar8[1] = '\0';
        pcVar8[2] = '\0';
        pcVar8[3] = '\0';
      }
      else {
        pOVar4 = OrdnanceClass::Find(CONCAT44(local_28,local_2c));
        *(OrdnanceClass **)(this->ordnanceData->fireSound + iVar6 + 0x10) = pOVar4;
      }
      uVar3 = Hash(local_20,0x1a05f72c);
      unaff_ESI = (char *)0x0;
      ParameterDB::Get(&local_1c,0x700e4deb,uVar3,local_18,0x10,(char *)0x0);
      if (local_18[0] == '\0') {
        *(undefined4 *)(this->ordnanceData->fireSound + iVar6 + 0x14) =
             *(undefined4 *)(this->ordnanceData->fireSound + iVar6 + -0x10);
      }
      else {
        unaff_ESI = local_18;
        iVar5 = GetSpriteIndex(unaff_ESI);
        *(int *)(this->ordnanceData->fireSound + iVar6 + 0x14) = iVar5;
      }
      local_24 = local_24 + 1;
      iVar6 = iVar6 + 0x24;
    } while (local_24 <= this->ordnanceCount);
  }
  this->_padding_ = (int)this->ordnanceData->ordnanceClass;
  ParameterDB::~ParameterDB(&local_1c);
  return this;
}
