/*
 * Entry: 004b0849
 * Name: ScrapSilo::Save
 * Namespace: ScrapSilo
 * Signature: bool Save(ScrapSilo * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ScrapSilo::Save(ScrapSilo *this,_iobuf *param_1)

{
  bool bVar1;
  bool bVar2;
  GameObject *pGVar3;
  
  pGVar3 = ScrapDropoff_GetObj(this->dropoff);
  this->dropObj = pGVar3;
  bVar1 = out_ptr(param_1,&this->dropObj,4,"undefptr");
  bVar2 = false;
  if (bVar1) {
    bVar2 = Building::Save((Building *)this,param_1);
  }
  return bVar2;
}
