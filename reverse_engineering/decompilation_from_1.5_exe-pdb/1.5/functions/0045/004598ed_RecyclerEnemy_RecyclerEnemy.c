/*
 * Entry: 004598ed
 * Name: RecyclerEnemy::RecyclerEnemy
 * Namespace: RecyclerEnemy
 * Signature: RecyclerEnemy * RecyclerEnemy(RecyclerEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RecyclerEnemy * __thiscall RecyclerEnemy::RecyclerEnemy(RecyclerEnemy *this)

{
  RecyclerProcess::RecyclerProcess((RecyclerProcess *)this);
  this->attacked = 0.0;
  this->fCraft = (Recycler *)0x0;
  this->waitToSetup = 0.0;
  this->fWhat = CMD_NONE;
  this->lastHit = 0;
  this->fFollow = (_OBJ76 *)0x0;
  this->_padding_ = (int)&_vftable_;
  return this;
}
