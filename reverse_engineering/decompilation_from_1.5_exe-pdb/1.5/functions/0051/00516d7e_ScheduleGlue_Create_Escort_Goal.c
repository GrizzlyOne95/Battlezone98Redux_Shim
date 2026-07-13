/*
 * Entry: 00516d7e
 * Name: ScheduleGlue_Create_Escort_Goal
 * Namespace: Global
 * Signature: Escort_Goal * ScheduleGlue_Create_Escort_Goal(ScavengerProcess * param_1, int param_2, Craft * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Escort_Goal * __cdecl
ScheduleGlue_Create_Escort_Goal(ScavengerProcess *param_1,int param_2,Craft *param_3)

{
  tag_team *ptVar1;
  Escort_Goal *pEVar2;
  
  ptVar1 = AI_map->team[param_2];
  if (ptVar1 != (tag_team *)0x0) {
    pEVar2 = operator_new(0x58);
    if (pEVar2 != (Escort_Goal *)0x0) {
      pEVar2 = Escort_Goal::Escort_Goal
                         (pEVar2,param_1,(GameObject *)param_3,1,1,15000.0,AI_map,ptVar1);
      return pEVar2;
    }
  }
  return (Escort_Goal *)0x0;
}
