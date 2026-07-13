/*
 * Entry: 0040afdc
 * Name: AOI::Load
 * Namespace: AOI
 * Signature: bool Load(AOI * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall AOI::Load(AOI *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::in(param_1,"[AOI]");
  if ((((bVar1) && (bVar1 = in_ptr(param_1,&this->path,4,"AOI",this), bVar1)) &&
      (bVar1 = ::in(param_1,&this->team,4), bVar1)) &&
     (((bVar1 = ::in(param_1,&this->interesting,1), bVar1 &&
       (bVar1 = ::in(param_1,&this->inside,1), bVar1)) &&
      ((bVar1 = ::in(param_1,&this->value,4), bVar1 && (bVar1 = ::in(param_1,&this->force,4), bVar1)
       ))))) {
    return true;
  }
  return false;
}
