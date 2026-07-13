/*
 * Entry: 0041d85f
 * Name: Misn01Mission::Load
 * Namespace: Misn01Mission
 * Signature: bool Load(Misn01Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn01Mission::Load(Misn01Mission *this,_iobuf *param_1)

{
  _iobuf *p_Var1;
  bool bVar2;
  AiMission *this_00;
  Misn01Mission_u_116 *pMVar3;
  
  p_Var1 = param_1;
  if (missionSave) {
    Setup(this);
    bVar2 = AiMission::Load(this_00,param_1);
  }
  else {
    bVar2 = ::in(param_1,(this->field16_0x40).b_array,0x10);
    if (((bVar2) && (bVar2 = ::in(param_1,(this->field17_0x54).f_array,0xc), bVar2)) &&
       (bVar2 = ::in(param_1,(this->field18_0x64).h_array,0xc), bVar2)) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    pMVar3 = &this->field19_0x74;
    param_1 = (_iobuf *)0x4;
    do {
      if ((bVar2) && (bVar2 = in_ptr(p_Var1,pMVar3->p_array,4,"p_array",this), bVar2)) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      pMVar3 = (Misn01Mission_u_116 *)((int)pMVar3 + 4);
      param_1 = (_iobuf *)((int)&param_1[-1]._tmpfname + 3);
    } while (param_1 != (_iobuf *)0x0);
    if (((bVar2) && (bVar2 = ::in(p_Var1,(this->field20_0x88).i_array,0xc), bVar2)) &&
       (bVar2 = AiMission::Load((AiMission *)this,p_Var1), bVar2)) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
  }
  return bVar2;
}
