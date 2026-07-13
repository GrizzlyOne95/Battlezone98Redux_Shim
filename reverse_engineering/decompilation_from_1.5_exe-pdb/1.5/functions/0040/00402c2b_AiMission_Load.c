/*
 * Entry: 00402c2b
 * Name: AiMission::Load
 * Namespace: AiMission
 * Signature: bool Load(AiMission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall AiMission::Load(AiMission *this,_iobuf *param_1)

{
  _iobuf *p_Var1;
  bool bVar2;
  AiProcess *pAVar3;
  AiMission *local_c;
  AiMission *local_8;
  
  p_Var1 = param_1;
  local_c = this;
  local_8 = this;
  bVar2 = ::in(param_1,"[AiMission]");
  if (missionSave == false) {
    bVar2 = ::in(param_1,(int *)&local_c,4);
    param_1 = (_iobuf *)0x0;
    if (bVar2) {
      local_8 = (AiMission *)0x0;
      bVar2 = true;
      do {
        if ((int)local_c <= (int)param_1) break;
        do_load_bar(shell_hwnd,(int)local_8 / (int)local_c + 0x55);
        pAVar3 = (AiProcess *)RtimeClass::Load(p_Var1);
        if (pAVar3 == (AiProcess *)0x0) {
          bVar2 = false;
        }
        else {
          AddProcess(this,pAVar3);
        }
        param_1 = (_iobuf *)((int)&param_1->_ptr + 1);
        local_8 = (AiMission *)((int)local_8 + 5);
      } while (bVar2);
      if ((((bVar2) && (bVar2 = ::in(p_Var1,&this->done,1), bVar2)) &&
          (bVar2 = ::in(p_Var1,&this->shutdownTime,4), bVar2)) &&
         ((bVar2 = ::in(p_Var1,&this->failed,1), bVar2 &&
          (bVar2 = ::in(p_Var1,this->resultName,0xe), bVar2)))) {
        return true;
      }
    }
    bVar2 = false;
  }
  return bVar2;
}
