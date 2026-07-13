/*
 * Entry: 0041d705
 * Name: Misn01Mission::Save
 * Namespace: Misn01Mission
 * Signature: bool Save(Misn01Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn01Mission::Save(Misn01Mission *this,_iobuf *param_1)

{
  _iobuf *p_Var1;
  bool bVar2;
  Misn01Mission_u_116 *pMVar3;
  
  p_Var1 = param_1;
  if (missionSave) {
    bVar2 = AiMission::Save((AiMission *)this,param_1);
  }
  else {
    bVar2 = ::out(param_1,(this->field16_0x40).b_array,0x10,"b_array");
    if (((bVar2) && (bVar2 = ::out(param_1,(this->field17_0x54).f_array,0xc,"f_array"), bVar2)) &&
       (bVar2 = ::out(param_1,(this->field18_0x64).h_array,0xc,"h_array"), bVar2)) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    pMVar3 = &this->field19_0x74;
    param_1 = (_iobuf *)0x4;
    do {
      if ((bVar2) && (bVar2 = out_ptr(p_Var1,pMVar3,4,"p_array"), bVar2)) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      pMVar3 = (Misn01Mission_u_116 *)((int)pMVar3 + 4);
      param_1 = (_iobuf *)((int)&param_1[-1]._tmpfname + 3);
    } while (param_1 != (_iobuf *)0x0);
    if (((bVar2) && (bVar2 = ::out(p_Var1,(this->field20_0x88).i_array,0xc,"i_array"), bVar2)) &&
       (bVar2 = AiMission::Save((AiMission *)this,p_Var1), bVar2)) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
  }
  return bVar2;
}
