/*
 * Entry: 00411889
 * Name: MUFEnemy::MUFEnemy
 * Namespace: MUFEnemy
 * Signature: MUFEnemy * MUFEnemy(MUFEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MUFEnemy * __thiscall MUFEnemy::MUFEnemy(MUFEnemy *this)

{
  RecyclerProcess::RecyclerProcess((RecyclerProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
