/*
 * Entry: 0040142c
 * Name: AI_Cleanup
 * Namespace: Global
 * Signature: void AI_Cleanup(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Cleanup(void)

{
  AiMission *pAVar1;
  
  if (mission == (AiMission *)0x0) {
    pAVar1 = AiMission::GetCurrent();
    if (pAVar1 != (AiMission *)0x0) {
      (**(code **)pAVar1->_padding_)(1);
    }
  }
  else {
    (**(code **)mission->_padding_)(1);
    mission = (AiMission *)0x0;
  }
  AiPath::Cleanup();
  return;
}
