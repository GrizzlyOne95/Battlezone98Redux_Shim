/*
 * Entry: 004015db
 * Name: FailMission
 * Namespace: Global
 * Signature: void FailMission(float param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FailMission(float param_1,char *param_2)

{
  AiMission::End(mission,param_1,param_2,true);
  return;
}
