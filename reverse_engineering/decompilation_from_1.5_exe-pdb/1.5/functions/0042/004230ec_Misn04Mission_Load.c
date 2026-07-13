/*
 * Entry: 004230ec
 * Name: Misn04Mission::Load
 * Namespace: Misn04Mission
 * Signature: bool Load(Misn04Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn04Mission::Load(Misn04Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  Misn04Mission_u_136 *pMVar3;
  Misn04Mission_u_260 *pMVar4;
  
  if (missionSave) {
    memset(&this->field16_0x40,0);
    pMVar3 = &this->field17_0x88;
    for (iVar2 = 0x1e; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar3->_s_0).wave1 = 99999.0;
      pMVar3 = (Misn04Mission_u_136 *)((int)pMVar3 + 4);
    }
    pMVar4 = &this->field18_0x104;
    for (iVar2 = 0x41; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar4->_s_0).svrec = 0;
      pMVar4 = (Misn04Mission_u_260 *)((int)pMVar4 + 4);
    }
    (this->field19_0x20c)._s_0.height = 0;
    (this->field19_0x20c)._s_0.relicstartpos = 0;
    (this->field19_0x20c)._s_0.wavenumber = 0;
    (this->field19_0x20c)._s_0.investigator = 0;
    (this->field19_0x20c)._s_0.warn = 0;
    Setup(this);
    bVar1 = AiMission::Load((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::in(param_1,(this->field16_0x40).b_array,0x44);
    if ((((bVar1) && (bVar1 = ::in(param_1,(this->field17_0x88).f_array,0x78), bVar1)) &&
        (bVar1 = ::in(param_1,(this->field18_0x104).h_array,0x104), bVar1)) &&
       ((bVar1 = ::in(param_1,(this->field19_0x20c).i_array,0x14), bVar1 &&
        (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)))) {
      return true;
    }
    bVar1 = false;
  }
  return bVar1;
}
