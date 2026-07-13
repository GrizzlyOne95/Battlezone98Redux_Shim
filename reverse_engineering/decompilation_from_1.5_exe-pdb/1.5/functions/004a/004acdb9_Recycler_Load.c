/*
 * Entry: 004acdb9
 * Name: Recycler::Load
 * Namespace: Recycler
 * Signature: bool Load(Recycler * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Recycler::Load(Recycler *this,_iobuf *param_1)

{
  bool bVar1;
  bool bVar2;
  
  bVar1 = in_ptr(param_1,&this->dropObj,4,"Recycler",this);
  bVar2 = false;
  if (bVar1) {
    bVar2 = Producer::Load((Producer *)this,param_1);
  }
  return bVar2;
}
