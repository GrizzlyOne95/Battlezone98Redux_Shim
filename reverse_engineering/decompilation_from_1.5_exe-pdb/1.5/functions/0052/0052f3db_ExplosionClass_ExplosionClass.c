/*
 * Entry: 0052f3db
 * Name: ExplosionClass::ExplosionClass
 * Namespace: ExplosionClass
 * Signature: ExplosionClass * ExplosionClass(ExplosionClass * this, ExplosionClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ExplosionClass * __thiscall
ExplosionClass::ExplosionClass(ExplosionClass *this,ExplosionClass *param_1,long64 param_2)

{
  ExplosionClass *pEVar1;
  undefined4 *puVar2;
  bool bVar3;
  ushort uVar4;
  _OBJ76 *p_Var5;
  int iVar6;
  ushort uVar7;
  undefined4 *puVar8;
  uint in_stack_00000008;
  ExplosionClass *local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  ExplosionClass *local_34;
  ParameterDB local_30;
  byte local_29;
  char local_28 [32];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_34 = param_1;
  this->_padding_ = (int)&_vftable_;
  this->proto = param_1;
  local_48 = this;
  std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::push_back(&classList,&local_48);
  this->sig = param_1->sig;
  *(uint *)&this->cfg = in_stack_00000008 & 0x7f7f7f7f;
  *(uint *)((int)&this->cfg + 4) = (uint)param_2 & 0x7f7f7f7f;
  strncpy(this->odf,(char *)&this->cfg,8);
  this->odf[8] = '\0';
  puVar2 = (undefined4 *)((int)&this->cfg + 7);
  do {
    puVar8 = puVar2;
    puVar2 = (undefined4 *)((int)puVar8 + 1);
  } while (*(char *)((int)puVar8 + 1) != '\0');
  *(undefined4 *)((int)puVar8 + 1) = 0x66646f2e;
  *(undefined1 *)((int)puVar8 + 5) = 0;
  p_Var5 = create_obj((_OBJ76 *)0x0,".\\fun3d\\ExplosionClass.cpp");
  this->freeObj = p_Var5;
  ParameterDB::ParameterDB(&local_30,this->odf);
  ParameterDB::Get(&local_30,0xca0c1378,0x9c646a05,local_28,0x20,(char *)0x0);
  if (local_28[0] == '\0') {
    iVar6 = local_34->frameIndex;
  }
  else {
    iVar6 = GetSpriteIndex(local_28);
  }
  pEVar1 = local_34;
  this->frameIndex = iVar6;
  ParameterDB::Get(&local_30,0xca0c1378,0xe67274d5,&this->frameCount,local_34->frameCount);
  if (this->frameCount < 1) {
    this->frameCount = 1;
  }
  ParameterDB::Get(&local_30,0xca0c1378,0xc7dc5ce9,&this->frameRate,1.0 / pEVar1->frameRate);
  if (0.0 < this->frameRate) {
    this->frameRate = 1.0 / this->frameRate;
  }
  ParameterDB::Get(&local_30,0xca0c1378,0x18c612d2,&this->explRadius,pEVar1->explRadius);
  ParameterDB::Get(&local_30,0xca0c1378,0xa38eb173,this->explSound,0x10,pEVar1->explSound);
  ParameterDB::Get(&local_30,0xca0c1378,0xb68798a6,&this->damageRadius,pEVar1->damageRadius);
  this->damageValue = pEVar1->damageValue;
  this->damageTypes = pEVar1->damageTypes;
  local_29 = ParameterDB::Get(&local_30,0xca0c1378,0x7c8a1300,&local_38,0.0);
  bVar3 = ParameterDB::Get(&local_30,0xca0c1378,0x5be2a777,&local_40,0.0);
  local_29 = local_29 | bVar3;
  bVar3 = ParameterDB::Get(&local_30,0xca0c1378,0x52fd4a53,&local_44,0.0);
  local_29 = bVar3 | local_29;
  bVar3 = ParameterDB::Get(&local_30,0xca0c1378,0x38720d72,&local_3c,0.0);
  if (bVar3 || local_29 != 0) {
    this->damageValue = local_3c + local_44 + local_38 + local_40;
    if (local_38 == 0.0) {
      uVar7 = 0;
    }
    else {
      uVar7 = 2;
    }
    if (local_44 == 0.0) {
      local_34 = (ExplosionClass *)0x0;
    }
    else {
      local_34 = (ExplosionClass *)0x4;
    }
    if (local_3c == 0.0) {
      uVar4 = 0;
    }
    else {
      uVar4 = 8;
    }
    this->damageTypes = local_40 != 0.0 | uVar7 | (ushort)local_34 | uVar4;
  }
  ParameterDB::Get(&local_30,0xca0c1378,0x63c6a1be,&this->omegaShake,pEVar1->omegaShake);
  ParameterDB::~ParameterDB(&local_30);
  return this;
}
