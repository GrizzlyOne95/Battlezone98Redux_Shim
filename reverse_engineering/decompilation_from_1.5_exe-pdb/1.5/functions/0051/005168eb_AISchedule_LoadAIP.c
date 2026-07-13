/*
 * Entry: 005168eb
 * Name: AISchedule_LoadAIP
 * Namespace: Global
 * Signature: void * AISchedule_LoadAIP(int param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl AISchedule_LoadAIP(int param_1,char *param_2)

{
  FindSendPoints *this;
  AiMission *pAVar1;
  tagAIP_struct *ptVar2;
  
  if (!loadedAIP) {
    loadedAIP = true;
    this = operator_new(0x20);
    if (this != (FindSendPoints *)0x0) {
      pAVar1 = AiMission::GetCurrent();
      FindSendPoints::FindSendPoints(this,pAVar1);
    }
  }
  ptVar2 = AI_AIPLoad(param_1,param_2);
  return ptVar2;
}
