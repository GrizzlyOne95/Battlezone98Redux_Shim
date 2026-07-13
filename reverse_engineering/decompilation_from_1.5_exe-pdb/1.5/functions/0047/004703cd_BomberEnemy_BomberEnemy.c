/*
 * Entry: 004703cd
 * Name: BomberEnemy::BomberEnemy
 * Namespace: BomberEnemy
 * Signature: BomberEnemy * BomberEnemy(BomberEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BomberEnemy * __thiscall BomberEnemy::BomberEnemy(BomberEnemy *this)

{
  WingmanProcess::WingmanProcess((WingmanProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
