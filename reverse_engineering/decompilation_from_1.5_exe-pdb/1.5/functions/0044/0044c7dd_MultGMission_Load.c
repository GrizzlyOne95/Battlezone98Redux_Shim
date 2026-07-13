/*
 * Entry: 0044c7dd
 * Name: MultGMission::Load
 * Namespace: MultGMission
 * Signature: bool Load(MultGMission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall MultGMission::Load(MultGMission *this,_iobuf *param_1)

{
  _iobuf *p_Var1;
  bool bVar2;
  AiProcess *pAVar3;
  MultGMission *pMStack_c;
  MultGMission *pMStack_8;
  
  p_Var1 = param_1;
  pMStack_c = this;
  pMStack_8 = this;
  bVar2 = ::in(param_1,"[AiMission]");
  if (missionSave == false) {
    bVar2 = ::in(param_1,(int *)&pMStack_c,4);
    param_1 = (_iobuf *)0x0;
    if (bVar2) {
      pMStack_8 = (MultGMission *)0x0;
      bVar2 = true;
      do {
        if ((int)pMStack_c <= (int)param_1) break;
        do_load_bar(shell_hwnd,(int)pMStack_8 / (int)pMStack_c + 0x55);
        pAVar3 = (AiProcess *)RtimeClass::Load(p_Var1);
        if (pAVar3 == (AiProcess *)0x0) {
          bVar2 = false;
        }
        else {
          AiMission::AddProcess((AiMission *)this,pAVar3);
        }
        param_1 = (_iobuf *)((int)&param_1->_ptr + 1);
        pMStack_8 = (MultGMission *)((int)pMStack_8 + 5);
      } while (bVar2);
      if ((((bVar2) && (bVar2 = ::in(p_Var1,(bool *)&this->field_0x24,1), bVar2)) &&
          (bVar2 = ::in(p_Var1,(float *)&this->field_0x28,4), bVar2)) &&
         ((bVar2 = ::in(p_Var1,(bool *)&this->field_0x2c,1), bVar2 &&
          (bVar2 = ::in(p_Var1,&this->field_0x2d,0xe), bVar2)))) {
        return true;
      }
    }
    bVar2 = false;
  }
  return bVar2;
}
