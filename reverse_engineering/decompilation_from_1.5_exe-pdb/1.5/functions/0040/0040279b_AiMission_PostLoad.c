/*
 * Entry: 0040279b
 * Name: AiMission::PostLoad
 * Namespace: AiMission
 * Signature: bool PostLoad(AiMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall AiMission::PostLoad(AiMission *this)

{
  char cVar1;
  bool bVar2;
  AiProcess **ppAVar3;
  char *pcVar4;
  int iVar5;
  _Const_iterator<1> local_18;
  _Const_iterator<1> local_10;
  char local_5;
  
  local_5 = '\x01';
  if (!missionSave) {
    std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_10,((this->processes)._Myhead)->_Next,&this->processes);
    do {
      std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::_Const_iterator<1>
                (&local_18,(this->processes)._Myhead,&this->processes);
      bVar2 = std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::operator==
                        (&local_10,&local_18);
      if (bVar2) break;
      ppAVar3 = std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::operator*
                          (&local_10);
      local_5 = (**(code **)((*ppAVar3)->_padding_ + 8))();
      std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::operator++(&local_10)
      ;
    } while (local_5 != '\0');
    if (this->done != false) {
      SetRunning((uint)(this->failed == false));
      pcVar4 = this->resultName;
      if (*pcVar4 == '\0') {
        builtin_strncpy(cMissionResult,"nofile",7);
      }
      else {
        iVar5 = (int)cMissionResult - (int)pcVar4;
        do {
          cVar1 = *pcVar4;
          pcVar4[iVar5] = cVar1;
          pcVar4 = pcVar4 + 1;
        } while (cVar1 != '\0');
      }
    }
  }
  return (bool)local_5;
}
