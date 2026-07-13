/*
 * Entry: 004590bc
 * Name: RecyclerEnemy::Load
 * Namespace: RecyclerEnemy
 * Signature: bool Load(RecyclerEnemy * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall RecyclerEnemy::Load(RecyclerEnemy *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = in_ptr(param_1,&this->fCraft,4,"RecyclerEnemy",this);
  if ((((bVar1) && (bVar1 = ::in(param_1,&this->fWhat,4), bVar1)) &&
      (bVar1 = ::in(param_1,&this->lastHit,4), bVar1)) &&
     ((bVar1 = ::in(param_1,&this->attacked,4), bVar1 &&
      (bVar1 = ::in(param_1,&this->waitToSetup,4), bVar1)))) {
    bVar1 = RecyclerProcess::Load((RecyclerProcess *)this,param_1);
    return bVar1;
  }
  return false;
}
