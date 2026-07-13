/*
 * Entry: 00459915
 * Name: RecyclerEnemy::~RecyclerEnemy
 * Namespace: RecyclerEnemy
 * Signature: void ~RecyclerEnemy(RecyclerEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecyclerEnemy::~RecyclerEnemy(RecyclerEnemy *this)

{
  this->_padding_ = (int)&RecyclerProcess::_vftable_;
  RecyclerProcess::CleanState((RecyclerProcess *)this);
  AiProcess::~AiProcess((AiProcess *)this);
  return;
}
