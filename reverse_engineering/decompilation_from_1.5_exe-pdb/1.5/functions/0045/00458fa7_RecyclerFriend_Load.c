/*
 * Entry: 00458fa7
 * Name: RecyclerFriend::Load
 * Namespace: RecyclerFriend
 * Signature: bool Load(RecyclerFriend * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall RecyclerFriend::Load(RecyclerFriend *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = in_ptr(param_1,&this->fCraft,4,"RecyclerFriend",this);
  if ((((bVar1) && (bVar1 = ::in(param_1,&this->fWhat,4), bVar1)) &&
      (bVar1 = ::in(param_1,&this->lastHit,4), bVar1)) &&
     ((bVar1 = ::in(param_1,&this->attacked,4), bVar1 &&
      (bVar1 = ::in(param_1,&this->waitToSetup,4), bVar1)))) {
    bVar1 = RecyclerProcess::Load((RecyclerProcess *)this,param_1);
    return bVar1;
  }
  return false;
}
