/*
 * Entry: 004da61c
 * Name: SmokeEffect::PreLoad
 * Namespace: SmokeEffect
 * Signature: void PreLoad(SmokeEffect * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall SmokeEffect::PreLoad(SmokeEffect *this)

{
  int extraout_EAX;
  int iVar1;
  SmokeEmitter *pSVar2;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  int extraout_EAX_03;
  int extraout_EAX_04;
  int iVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  ParameterDB local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  this->emitterLast = this->emitterFirst;
  this->puffLast = this->puffFirst;
  ParameterDB::ParameterDB(&local_1c,"smoke.odf");
  ParameterDB::Get(&local_1c,0x23e9d0db,0xdd33060c,&local_20,16.0);
  ParameterDB::Get(&local_1c,0x23e9d0db,0xbcc03185,&local_28,1.6);
  ParameterDB::Get(&local_1c,0x23e9d0db,0x8566cba4,&local_2c,1.5);
  ParameterDB::Get(&local_1c,0x23e9d0db,0x2a532704,&local_24,1.0);
  ParameterDB::Get(&local_1c,0x23e9d0db,0xe4e87623,local_18,0x10,"lsmoke.0");
  fVar4 = local_20 / local_28;
  fVar5 = local_2c;
  fVar6 = local_24;
  _ftol2_sse();
  iVar3 = extraout_EAX;
  iVar1 = GetSpriteIndex(local_18);
  pSVar2 = AddEmitter(this,iVar1,iVar3,fVar4,fVar5,fVar6);
  this->smokeWhite = pSVar2;
  ParameterDB::Get(&local_1c,0x23e9d0db,0x89e40141,local_18,0x10,"msmoke.0");
  fVar4 = local_20 / local_28;
  fVar5 = local_2c;
  fVar6 = local_24;
  _ftol2_sse();
  iVar3 = extraout_EAX_00;
  iVar1 = GetSpriteIndex(local_18);
  pSVar2 = AddEmitter(this,iVar1,iVar3,fVar4,fVar5,fVar6);
  this->smokeTan = pSVar2;
  ParameterDB::Get(&local_1c,0x23e9d0db,0x55473cb2,local_18,0x10,"dsmoke.0");
  fVar4 = local_20 / local_28;
  fVar5 = local_2c;
  fVar6 = local_24;
  _ftol2_sse();
  iVar3 = extraout_EAX_01;
  iVar1 = GetSpriteIndex(local_18);
  pSVar2 = AddEmitter(this,iVar1,iVar3,fVar4,fVar5,fVar6);
  this->smokeBrown = pSVar2;
  ParameterDB::Get(&local_1c,0x23e9d0db,0x68ad0781,local_18,0x10,"bsmoke.0");
  fVar4 = local_20 / local_28;
  fVar5 = local_2c;
  fVar6 = local_24;
  _ftol2_sse();
  iVar3 = extraout_EAX_02;
  iVar1 = GetSpriteIndex(local_18);
  pSVar2 = AddEmitter(this,iVar1,iVar3,fVar4,fVar5,fVar6);
  this->smokeBlack = pSVar2;
  ParameterDB::Get(&local_1c,0x23e9d0db,0x170efc31,&local_20,16.0);
  ParameterDB::Get(&local_1c,0x23e9d0db,0x4225e338,&local_28,1.6);
  ParameterDB::Get(&local_1c,0x23e9d0db,0x4583bc21,&local_2c,2.0);
  ParameterDB::Get(&local_1c,0x23e9d0db,0xc2c0fe4b,&local_24,1.0);
  ParameterDB::Get(&local_1c,0x23e9d0db,0x325cf422,local_18,0x10,"lsmoke.0");
  fVar4 = local_20 / local_28;
  fVar5 = local_2c;
  fVar6 = local_24;
  _ftol2_sse();
  iVar3 = extraout_EAX_03;
  iVar1 = GetSpriteIndex(local_18);
  pSVar2 = AddEmitter(this,iVar1,iVar3,fVar4,fVar5,fVar6);
  this->steamEmitter = pSVar2;
  ParameterDB::Get(&local_1c,0x23e9d0db,0xc86d87f8,&local_20,16.0);
  ParameterDB::Get(&local_1c,0x23e9d0db,0xb6fc11f9,&local_28,1.6);
  ParameterDB::Get(&local_1c,0x23e9d0db,0x899409c8,&local_2c,2.0);
  ParameterDB::Get(&local_1c,0x23e9d0db,0x978015a0,&local_24,1.0);
  ParameterDB::Get(&local_1c,0x23e9d0db,0xb0ca99d,local_18,0x10,"lsmoke.0");
  fVar4 = local_20 / local_28;
  _ftol2_sse();
  iVar3 = extraout_EAX_04;
  iVar1 = GetSpriteIndex(local_18);
  pSVar2 = AddEmitter(this,iVar1,iVar3,fVar4,local_2c,local_24);
  this->sprayEmitter = pSVar2;
  ParameterDB::~ParameterDB(&local_1c);
  return;
}
