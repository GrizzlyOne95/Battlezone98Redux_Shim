/*
 * Entry: 004160f7
 * Name: Inst4XMission::Load
 * Namespace: Inst4XMission
 * Signature: bool Load(Inst4XMission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Inst4XMission::Load(Inst4XMission *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (missionSave) {
    *(undefined2 *)&this->field19_0x4c = 0;
    (this->field19_0x4c)._s_0.timerRunning = false;
    (this->field20_0x50)._s_0.float_1 = 99999.0;
    (this->field20_0x50)._s_0.timeLeft = 99999.0;
    (this->field21_0x5c)._s_0.handle_1 = 0;
    (this->field22_0x64)._s_0.int_1 = 0;
    Setup(this);
    bVar1 = LuaMission::Load((LuaMission *)this,param_1);
  }
  else {
    bVar1 = ::in(param_1,(this->field19_0x4c).b_array,3);
    if ((((bVar1) && (bVar1 = ::in(param_1,(this->field20_0x50).f_array,8), bVar1)) &&
        (bVar1 = ::in(param_1,(this->field21_0x5c).h_array,4), bVar1)) &&
       ((bVar1 = ::in(param_1,(this->field22_0x64).i_array,4), bVar1 &&
        (bVar1 = LuaMission::Load((LuaMission *)this,param_1), bVar1)))) {
      return true;
    }
    bVar1 = false;
  }
  return bVar1;
}
