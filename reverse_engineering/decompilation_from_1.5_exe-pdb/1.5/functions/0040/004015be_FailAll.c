/*
 * Entry: 004015be
 * Name: FailAll
 * Namespace: Global
 * Signature: void FailAll(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FailAll(int param_1)

{
  float fVar1;
  
  fVar1 = Get_Time();
  AiMission::End(mission,fVar1 + (float)param_1,(char *)0x0,true);
  return;
}
