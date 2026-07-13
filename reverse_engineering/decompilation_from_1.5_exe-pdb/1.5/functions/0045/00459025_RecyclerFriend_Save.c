/*
 * Entry: 00459025
 * Name: RecyclerFriend::Save
 * Namespace: RecyclerFriend
 * Signature: bool Save(RecyclerFriend * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall RecyclerFriend::Save(RecyclerFriend *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = out_ptr(param_1,&this->fCraft,4,"undefptr");
  if ((((bVar1) && (bVar1 = ::out(param_1,&this->fWhat,4,"fWhat"), bVar1)) &&
      (bVar1 = ::out(param_1,&this->lastHit,4,"lastHit"), bVar1)) &&
     ((bVar1 = ::out(param_1,&this->attacked,4,"attacked"), bVar1 &&
      (bVar1 = ::out(param_1,&this->waitToSetup,4,"waitToSetup"), bVar1)))) {
    bVar1 = RecyclerProcess::Save((RecyclerProcess *)this,param_1);
    return bVar1;
  }
  return false;
}
