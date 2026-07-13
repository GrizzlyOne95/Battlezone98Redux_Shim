/*
 * Entry: 0046445e
 * Name: Tran03Mission::Load
 * Namespace: Tran03Mission
 * Signature: bool Load(Tran03Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Tran03Mission::Load(Tran03Mission *this,_iobuf *param_1)

{
  bool bVar1;
  AiMission *this_00;
  Tran03Mission_u_120 *pTVar2;
  int local_8;
  
  if (missionSave) {
    (this->field18_0x64)._s_0.scav = 0;
    (this->field18_0x64)._s_0.attacker = 0;
    (this->field18_0x64)._s_0.geyser = 0;
    (this->field18_0x64)._s_0.recycler = 0;
    Setup(this);
    bVar1 = AiMission::Load(this_00,param_1);
  }
  else {
    bVar1 = ::in(param_1,(this->field16_0x40).b_array,0x18);
    if (((bVar1) && (bVar1 = ::in(param_1,(this->field17_0x5c).f_array,4), bVar1)) &&
       (bVar1 = ::in(param_1,(this->field18_0x64).h_array,0x10), bVar1)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    pTVar2 = &this->field19_0x78;
    local_8 = 4;
    do {
      if ((bVar1) && (bVar1 = in_ptr(param_1,pTVar2->p_array,4,"p_array",this), bVar1)) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
      pTVar2 = (Tran03Mission_u_120 *)((int)pTVar2 + 4);
      local_8 = local_8 + -1;
    } while (local_8 != 0);
    if (((bVar1) && (bVar1 = ::in(param_1,(this->field20_0x8c).i_array,4), bVar1)) &&
       (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  return bVar1;
}
