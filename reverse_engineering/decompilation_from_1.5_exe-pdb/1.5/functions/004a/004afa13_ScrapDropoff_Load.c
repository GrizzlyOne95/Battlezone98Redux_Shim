/*
 * Entry: 004afa13
 * Name: ScrapDropoff::Load
 * Namespace: ScrapDropoff
 * Signature: bool Load(ScrapDropoff * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ScrapDropoff::Load(ScrapDropoff *this,_iobuf *param_1)

{
  bool bVar1;
  ScrapDropoff *local_8;
  
  local_8 = this;
  if (version < 0x3fa) {
    bVar1 = in_ptr(param_1,&local_8,4,"ScrapDropoff: recycler",this);
    if (!bVar1) goto LAB_004afa4b;
  }
  bVar1 = PowerUp::Load((PowerUp *)this,param_1);
LAB_004afa4b:
  *(undefined4 *)&this->field_0xf0 = 0;
  return bVar1;
}
