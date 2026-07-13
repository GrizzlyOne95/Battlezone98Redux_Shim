/*
 * Entry: 004111e3
 * Name: DemoMission::Load
 * Namespace: DemoMission
 * Signature: bool Load(DemoMission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall DemoMission::Load(DemoMission *this,_iobuf *param_1)

{
  _iobuf *p_Var1;
  bool bVar2;
  AiMission *this_00;
  DemoMission_u_184 *pDVar3;
  
  p_Var1 = param_1;
  if (missionSave) {
    Setup(this);
    bVar2 = AiMission::Load(this_00,param_1);
  }
  else {
    bVar2 = ::in(param_1,(this->field16_0x40).b_array,0x13);
    if (((bVar2) && (bVar2 = ::in(param_1,(this->field17_0x54).f_array,0x14), bVar2)) &&
       (bVar2 = ::in(param_1,(this->field18_0x70).h_array,0x30), bVar2)) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    pDVar3 = &this->field19_0xb8;
    param_1 = (_iobuf *)0x4;
    do {
      if ((bVar2) && (bVar2 = in_ptr(p_Var1,pDVar3->p_array,4,"p_array",this), bVar2)) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      pDVar3 = (DemoMission_u_184 *)((int)pDVar3 + 4);
      param_1 = (_iobuf *)((int)&param_1[-1]._tmpfname + 3);
    } while (param_1 != (_iobuf *)0x0);
    if (((bVar2) && (bVar2 = ::in(p_Var1,(this->field20_0xcc).i_array,0x14), bVar2)) &&
       (bVar2 = AiMission::Load((AiMission *)this,p_Var1), bVar2)) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
  }
  return bVar2;
}
