/*
 * Entry: 00464bab
 * Name: Tran04Mission::Load
 * Namespace: Tran04Mission
 * Signature: bool Load(Tran04Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Tran04Mission::Load(Tran04Mission *this,_iobuf *param_1)

{
  _iobuf *p_Var1;
  bool bVar2;
  int iVar3;
  AiMission *this_00;
  Tran04Mission_u_100 *pTVar4;
  Tran04Mission_u_136 *pTVar5;
  
  p_Var1 = param_1;
  if (missionSave) {
    pTVar4 = &this->field18_0x64;
    for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
      (pTVar4->_s_0).player = 0;
      pTVar4 = (Tran04Mission_u_100 *)((int)pTVar4 + 4);
    }
    Setup(this);
    bVar2 = AiMission::Load(this_00,param_1);
  }
  else {
    bVar2 = ::in(param_1,(this->field16_0x40).b_array,0x16);
    if (((bVar2) && (bVar2 = ::in(param_1,(this->field17_0x58).f_array,8), bVar2)) &&
       (bVar2 = ::in(param_1,(this->field18_0x64).h_array,0x20), bVar2)) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    pTVar5 = &this->field19_0x88;
    param_1 = (_iobuf *)0x8;
    do {
      if ((bVar2) && (bVar2 = in_ptr(p_Var1,pTVar5->p_array,4,"p_array",this), bVar2)) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      pTVar5 = (Tran04Mission_u_136 *)((int)pTVar5 + 4);
      param_1 = (_iobuf *)((int)&param_1[-1]._tmpfname + 3);
    } while (param_1 != (_iobuf *)0x0);
    if (((bVar2) && (bVar2 = ::in(p_Var1,(this->field20_0xac).i_array,8), bVar2)) &&
       (bVar2 = AiMission::Load((AiMission *)this,p_Var1), bVar2)) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
  }
  return bVar2;
}
