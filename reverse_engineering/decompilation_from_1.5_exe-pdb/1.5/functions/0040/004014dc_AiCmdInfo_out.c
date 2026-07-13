/*
 * Entry: 004014dc
 * Name: AiCmdInfo::out
 * Namespace: AiCmdInfo
 * Signature: bool out(AiCmdInfo * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall AiCmdInfo::out(AiCmdInfo *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::out(param_1,&this->priority,4,"priority");
  if ((((bVar1) && (bVar1 = ::out(param_1,&this->what,4,"what"), bVar1)) &&
      (bVar1 = ::out(param_1,&this->who,4,"who"), bVar1)) &&
     ((bVar1 = out_ptr(param_1,&this->where,4,"where"), bVar1 &&
      (bVar1 = ::out(param_1,&this->param,4,"param"), bVar1)))) {
    return true;
  }
  return false;
}
