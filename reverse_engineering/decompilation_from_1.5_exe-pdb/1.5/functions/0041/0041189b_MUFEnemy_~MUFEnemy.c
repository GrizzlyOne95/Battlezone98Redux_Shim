/*
 * Entry: 0041189b
 * Name: MUFEnemy::~MUFEnemy
 * Namespace: MUFEnemy
 * Signature: void ~MUFEnemy(MUFEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MUFEnemy::~MUFEnemy(MUFEnemy *this)

{
  *(undefined ***)this = &RecyclerProcess::_vftable_;
  RecyclerProcess::CleanState((RecyclerProcess *)this);
  AiProcess::~AiProcess((AiProcess *)this);
  return;
}
