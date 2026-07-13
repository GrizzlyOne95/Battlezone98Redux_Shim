/*
 * Entry: 00401ac9
 * Name: AiMission::PostLoadMission
 * Namespace: AiMission
 * Signature: bool PostLoadMission(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl AiMission::PostLoadMission(void)

{
  bool bVar1;
  char cVar2;
  bool bVar3;
  
  bVar3 = true;
  AISchedule_PostLoad();
  bVar1 = Net::IsNetGame();
  if (!bVar1) {
    cVar2 = (**(code **)(current->_padding_ + 8))();
    bVar3 = cVar2 != '\0';
  }
  return bVar3;
}
