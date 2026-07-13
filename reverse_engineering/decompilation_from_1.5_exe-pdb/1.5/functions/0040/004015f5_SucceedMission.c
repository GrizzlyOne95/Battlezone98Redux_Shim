/*
 * Entry: 004015f5
 * Name: SucceedMission
 * Namespace: Global
 * Signature: void SucceedMission(float param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SucceedMission(float param_1,char *param_2)

{
  AiMission::End(mission,param_1,param_2,false);
  return;
}
