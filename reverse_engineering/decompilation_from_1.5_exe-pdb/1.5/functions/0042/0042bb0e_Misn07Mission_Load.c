/*
 * Entry: 0042bb0e
 * Name: Misn07Mission::Load
 * Namespace: Misn07Mission
 * Signature: bool Load(Misn07Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn07Mission::Load(Misn07Mission *this,_iobuf *param_1)

{
  _iobuf *p_Var1;
  bool bVar2;
  int iVar3;
  Misn07Mission_u_364 *pMVar4;
  Misn07Mission_u_484 *pMVar5;
  Misn07Mission_u_1288 *pMVar6;
  
  p_Var1 = param_1;
  if (missionSave) {
    memset(&this->field16_0x40,0,0x12a);
    pMVar4 = &this->field17_0x16c;
    for (iVar3 = 0x1d; iVar3 != 0; iVar3 = iVar3 + -1) {
      (pMVar4->_s_0).unit_spawn_time = 99999.0;
      pMVar4 = (Misn07Mission_u_364 *)((int)pMVar4 + 4);
    }
    pMVar5 = &this->field18_0x1e4;
    for (iVar3 = 200; iVar3 != 0; iVar3 = iVar3 + -1) {
      (pMVar5->_s_0).user = 0;
      pMVar5 = (Misn07Mission_u_484 *)((int)pMVar5 + 4);
    }
    pMVar6 = &this->field19_0x508;
    for (iVar3 = 0x70; iVar3 != 0; iVar3 = iVar3 + -1) {
      (pMVar6->_s_0).turret1_spot = (AiPath *)0x0;
      pMVar6 = (Misn07Mission_u_1288 *)((int)pMVar6 + 4);
    }
    (this->field20_0x6cc)._s_0.count = 0;
    (this->field20_0x6cc)._s_0.mine_check = 0;
    (this->field20_0x6cc)._s_0.x = 0;
    (this->field20_0x6cc)._s_0.units = 0;
    (this->field20_0x6cc)._s_0.audmsg = 0;
    Setup(this);
    bVar2 = AiMission::Load((AiMission *)this,param_1);
  }
  else {
    bVar2 = ::in(param_1,(this->field16_0x40).b_array,0x12a);
    if (((bVar2) && (bVar2 = ::in(param_1,(this->field17_0x16c).f_array,0x74), bVar2)) &&
       (bVar2 = ::in(param_1,(this->field18_0x1e4).h_array,800), bVar2)) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    pMVar6 = &this->field19_0x508;
    param_1 = (_iobuf *)0x70;
    do {
      if ((bVar2) && (bVar2 = in_ptr(p_Var1,pMVar6->p_array,4,"p_array",this), bVar2)) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      pMVar6 = (Misn07Mission_u_1288 *)((int)pMVar6 + 4);
      param_1 = (_iobuf *)((int)&param_1[-1]._tmpfname + 3);
    } while (param_1 != (_iobuf *)0x0);
    if (((bVar2) && (bVar2 = ::in(p_Var1,(this->field20_0x6cc).i_array,0x14), bVar2)) &&
       (bVar2 = AiMission::Load((AiMission *)this,p_Var1), bVar2)) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
  }
  return bVar2;
}
