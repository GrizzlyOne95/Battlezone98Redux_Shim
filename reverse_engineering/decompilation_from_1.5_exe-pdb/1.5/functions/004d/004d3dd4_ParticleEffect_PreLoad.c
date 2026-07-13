/*
 * Entry: 004d3dd4
 * Name: ParticleEffect::PreLoad
 * Namespace: ParticleEffect
 * Signature: void PreLoad(ParticleEffect * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall ParticleEffect::PreLoad(ParticleEffect *this)

{
  int iVar1;
  ParameterDB local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  ParameterDB::ParameterDB(&local_1c,"particle.odf");
  ParameterDB::Get(&local_1c,0x92033d5a,0xf50ddfe,local_18,0x10,"particle.0");
  iVar1 = GetSpriteIndex(local_18);
  this->particleTexture = iVar1;
  ParameterDB::Get(&local_1c,0x92033d5a,0x9ce7acd5,&this->particleFrames,0x10);
  ParameterDB::Get(&local_1c,0x92033d5a,0x531e553d,&this->particleRadius,0.5);
  ParameterDB::Get(&local_1c,0x92033d5a,0xf7e89ce2,&this->initDelay,0.5);
  ParameterDB::Get(&local_1c,0x92033d5a,0xc7dc5ce9,&this->frameDelay,0.1);
  this->indexFirst = 0;
  this->indexLast = 0;
  ParameterDB::~ParameterDB(&local_1c);
  return;
}
