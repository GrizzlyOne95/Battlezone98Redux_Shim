/*
 * Entry: 004c9552
 * Name: DustEffect::PreLoad
 * Namespace: DustEffect
 * Signature: void PreLoad(DustEffect * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall DustEffect::PreLoad(DustEffect *this)

{
  long *plVar1;
  float *pfVar2;
  int iVar3;
  float *pfVar4;
  ParameterDB local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  this->puffLast = this->puffFirst;
  ParameterDB::ParameterDB(&local_1c,"dust.odf");
  ParameterDB::Get(&local_1c,0xc8e4c134,0xc1fe0e54,local_18,0x10,"dust.0");
  iVar3 = GetSpriteIndex(local_18);
  this->dustTexture = iVar3;
  plVar1 = &this->dustFrames;
  ParameterDB::Get(&local_1c,0xc8e4c134,0x2e9fa32f,plVar1,0x20);
  pfVar2 = &this->dustRate;
  ParameterDB::Get(&local_1c,0xc8e4c134,0xfeb0cc2b,pfVar2,1.2);
  *pfVar2 = (float)*plVar1 / *pfVar2;
  ParameterDB::Get(&local_1c,0xc8e4c134,0x922db093,&this->dustRadius,1.5);
  pfVar4 = &this->dustScale;
  ParameterDB::Get(&local_1c,0xc8e4c134,0x7bb4f7d1,pfVar4,1.0);
  *pfVar4 = ((*pfVar4 - 1.0) * this->dustRadius * *pfVar2) / (float)*plVar1;
  ParameterDB::~ParameterDB(&local_1c);
  return;
}
