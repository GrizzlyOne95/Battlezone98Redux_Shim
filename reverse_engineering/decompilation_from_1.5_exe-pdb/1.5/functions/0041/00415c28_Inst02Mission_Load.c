/*
 * Entry: 00415c28
 * Name: Inst02Mission::Load
 * Namespace: Inst02Mission
 * Signature: bool Load(Inst02Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Inst02Mission::Load(Inst02Mission *this,_iobuf *param_1)

{
  _iobuf *p_Var1;
  bool bVar2;
  AiProcess *pAVar3;
  Inst02Mission *pIStack_c;
  Inst02Mission *pIStack_8;
  
  p_Var1 = param_1;
  pIStack_c = this;
  pIStack_8 = this;
  bVar2 = ::in(param_1,"[AiMission]");
  if (missionSave == false) {
    bVar2 = ::in(param_1,(int *)&pIStack_c,4);
    param_1 = (_iobuf *)0x0;
    if (bVar2) {
      pIStack_8 = (Inst02Mission *)0x0;
      bVar2 = true;
      do {
        if ((int)pIStack_c <= (int)param_1) break;
        do_load_bar(shell_hwnd,(int)pIStack_8 / (int)pIStack_c + 0x55);
        pAVar3 = (AiProcess *)RtimeClass::Load(p_Var1);
        if (pAVar3 == (AiProcess *)0x0) {
          bVar2 = false;
        }
        else {
          AiMission::AddProcess((AiMission *)this,pAVar3);
        }
        param_1 = (_iobuf *)((int)&param_1->_ptr + 1);
        pIStack_8 = (Inst02Mission *)((int)pIStack_8 + 5);
      } while (bVar2);
      if ((((bVar2) && (bVar2 = ::in(p_Var1,(bool *)&this->_padding_,1), bVar2)) &&
          (bVar2 = ::in(p_Var1,(float *)&this->_padding_,4), bVar2)) &&
         ((bVar2 = ::in(p_Var1,(bool *)&this->_padding_,1), bVar2 &&
          (bVar2 = ::in(p_Var1,(char *)((int)&this->_padding_ + 1),0xe), bVar2)))) {
        return true;
      }
    }
    bVar2 = false;
  }
  return bVar2;
}
