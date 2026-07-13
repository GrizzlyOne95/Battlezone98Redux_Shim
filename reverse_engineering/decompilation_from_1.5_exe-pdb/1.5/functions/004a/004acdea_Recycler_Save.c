/*
 * Entry: 004acdea
 * Name: Recycler::Save
 * Namespace: Recycler
 * Signature: bool Save(Recycler * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Recycler::Save(Recycler *this,_iobuf *param_1)

{
  bool bVar1;
  bool bVar2;
  GameObject *pGVar3;
  
  pGVar3 = ScrapDropoff_GetObj(this->scrapDropoff);
  this->dropObj = pGVar3;
  bVar1 = out_ptr(param_1,&this->dropObj,4,"undefptr");
  bVar2 = false;
  if (bVar1) {
    bVar2 = Producer::Save((Producer *)this,param_1);
  }
  return bVar2;
}
