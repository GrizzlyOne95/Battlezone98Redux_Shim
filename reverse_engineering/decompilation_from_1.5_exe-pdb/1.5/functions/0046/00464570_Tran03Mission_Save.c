/*
 * Entry: 00464570
 * Name: Tran03Mission::Save
 * Namespace: Tran03Mission
 * Signature: bool Save(Tran03Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Tran03Mission::Save(Tran03Mission *this,_iobuf *param_1)

{
  bool bVar1;
  Tran03Mission_u_120 *pTVar2;
  int local_8;
  
  if (missionSave) {
    bVar1 = AiMission::Save((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::out(param_1,(this->field16_0x40).b_array,0x18,"b_array");
    if (((bVar1) && (bVar1 = ::out(param_1,(this->field17_0x5c).f_array,4,"f_array"), bVar1)) &&
       (bVar1 = ::out(param_1,(this->field18_0x64).h_array,0x10,"h_array"), bVar1)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    pTVar2 = &this->field19_0x78;
    local_8 = 4;
    do {
      if ((bVar1) && (bVar1 = out_ptr(param_1,pTVar2,4,"p_array"), bVar1)) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
      pTVar2 = (Tran03Mission_u_120 *)((int)pTVar2 + 4);
      local_8 = local_8 + -1;
    } while (local_8 != 0);
    if (((bVar1) && (bVar1 = ::out(param_1,(this->field20_0x8c).i_array,4,"i_array"), bVar1)) &&
       (bVar1 = AiMission::Save((AiMission *)this,param_1), bVar1)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  return bVar1;
}
