/*
 * Entry: 0040b075
 * Name: AOI::Save
 * Namespace: AOI
 * Signature: bool Save(AOI * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall AOI::Save(AOI *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::out(param_1,"[AOI]");
  if ((((bVar1) && (bVar1 = out_ptr(param_1,this,4,"undefptr"), bVar1)) &&
      (bVar1 = ::out(param_1,&this->team,4,"team"), bVar1)) &&
     (((bVar1 = ::out(param_1,&this->interesting,1,"interesting"), bVar1 &&
       (bVar1 = ::out(param_1,&this->inside,1,"inside"), bVar1)) &&
      ((bVar1 = ::out(param_1,&this->value,4,"value"), bVar1 &&
       (bVar1 = ::out(param_1,&this->force,4,"force"), bVar1)))))) {
    return true;
  }
  return false;
}
