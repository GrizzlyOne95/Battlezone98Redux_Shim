/*
 * Entry: 00518864
 * Name: CloseCommonGameSystems
 * Namespace: Global
 * Signature: void CloseCommonGameSystems(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CloseCommonGameSystems(void)

{
  Build_Close();
  Units_Close();
  AI_SpecialForcesClose();
  AI_AIPClose();
  return;
}
