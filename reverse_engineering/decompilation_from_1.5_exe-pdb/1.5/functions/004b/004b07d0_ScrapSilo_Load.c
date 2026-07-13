/*
 * Entry: 004b07d0
 * Name: ScrapSilo::Load
 * Namespace: ScrapSilo
 * Signature: bool Load(ScrapSilo * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ScrapSilo::Load(ScrapSilo *this,_iobuf *param_1)

{
  int iVar1;
  bool bVar2;
  GameObject *pGVar3;
  
  bVar2 = true;
  if (version < 0x3fd) {
    if (-1 < this->dropoff) {
      pGVar3 = ScrapDropoff_GetObj(this->dropoff);
      this->dropObj = pGVar3;
      goto LAB_004b083a;
    }
    this->dropObj = (GameObject *)0x0;
  }
  else {
    iVar1 = this->dropoff;
    if (-1 < iVar1) {
      ScrapDropoff_Get(iVar1);
      this->dropoff = -1;
    }
    bVar2 = in_ptr(param_1,&this->dropObj,4,"ScrapSilo",this);
  }
  if (bVar2 == false) {
    return false;
  }
LAB_004b083a:
  bVar2 = Building::Load((Building *)this,param_1);
  return bVar2;
}
