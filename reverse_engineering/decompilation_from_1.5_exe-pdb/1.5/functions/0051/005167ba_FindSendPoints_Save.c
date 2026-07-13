/*
 * Entry: 005167ba
 * Name: FindSendPoints::Save
 * Namespace: FindSendPoints
 * Signature: bool Save(FindSendPoints * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall FindSendPoints::Save(FindSendPoints *this,_iobuf *param_1)

{
  _iobuf *p_Var1;
  bool bVar2;
  
  p_Var1 = param_1;
  bVar2 = ::out(param_1,&this->row,4,"row");
  if (((bVar2) && (bVar2 = ::out(p_Var1,&this->col,4,"col"), bVar2)) &&
     (bVar2 = ::out(p_Var1,&this->i,4,"i"), bVar2)) {
    bVar2 = true;
  }
  else {
    bVar2 = false;
  }
  param_1 = (_iobuf *)(grid_columns * grid_rows);
  if (((bVar2) && (bVar2 = ::out(p_Var1,(int *)&param_1,4,"n"), bVar2)) &&
     ((bVar2 = ::out(p_Var1,sendPoints,(int)param_1 << 2,"sendPoints"), bVar2 &&
      (bVar2 = AiProcess::Save((AiProcess *)this,p_Var1), bVar2)))) {
    return true;
  }
  return false;
}
