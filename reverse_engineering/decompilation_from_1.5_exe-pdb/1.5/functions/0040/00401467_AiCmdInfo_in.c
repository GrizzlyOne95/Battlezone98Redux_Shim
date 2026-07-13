/*
 * Entry: 00401467
 * Name: AiCmdInfo::in
 * Namespace: AiCmdInfo
 * Signature: bool in(AiCmdInfo * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall AiCmdInfo::in(AiCmdInfo *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::in(param_1,&this->priority,4);
  if ((((bVar1) && (bVar1 = ::in(param_1,&this->what,4), bVar1)) &&
      (bVar1 = ::in(param_1,&this->who,4), bVar1)) &&
     ((bVar1 = in_ptr(param_1,&this->where,4,"AiCmdInfo:where",this), bVar1 &&
      (bVar1 = ::in(param_1,&this->param,4), bVar1)))) {
    return true;
  }
  return false;
}
