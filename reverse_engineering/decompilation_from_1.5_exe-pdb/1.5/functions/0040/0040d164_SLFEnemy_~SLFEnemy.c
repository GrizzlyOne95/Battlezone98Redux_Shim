/*
 * Entry: 0040d164
 * Name: SLFEnemy::~SLFEnemy
 * Namespace: SLFEnemy
 * Signature: void ~SLFEnemy(SLFEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SLFEnemy::~SLFEnemy(SLFEnemy *this)

{
  *(undefined ***)this = &ArmoryProcess::_vftable_;
  ArmoryProcess::CleanState((ArmoryProcess *)this);
  AiProcess::~AiProcess((AiProcess *)this);
  return;
}
