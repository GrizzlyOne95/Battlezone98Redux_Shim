/*
 * Entry: 004015a1
 * Name: SuccessAll
 * Namespace: Global
 * Signature: void SuccessAll(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SuccessAll(int param_1)

{
  float fVar1;
  
  fVar1 = Get_Time();
  AiMission::End(mission,fVar1 + (float)param_1,(char *)0x0,false);
  return;
}
