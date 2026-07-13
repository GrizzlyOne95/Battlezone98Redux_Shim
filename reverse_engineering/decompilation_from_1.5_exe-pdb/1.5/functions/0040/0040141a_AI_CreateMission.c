/*
 * Entry: 0040141a
 * Name: AI_CreateMission
 * Namespace: Global
 * Signature: void AI_CreateMission(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_CreateMission(void)

{
  mission = AiMission::Create(missionID);
  return;
}
