/*
 * Entry: 00571119
 * Name: localize_mission_names
 * Namespace: Global
 * Signature: int localize_mission_names(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl localize_mission_names(void)

{
  _USAMission *p_Var1;
  _USSRMission *p_Var2;
  _TrainingMission *p_Var3;
  
  p_Var1 = USAMissionList;
  do {
    read_text_label("mission_title",p_Var1->cMissionName,p_Var1->cMissionTitle);
    p_Var1 = p_Var1 + 1;
  } while ((int)p_Var1 < 0x6383cc);
  p_Var2 = USSRMissionList;
  do {
    read_text_label("mission_title",p_Var2->cMissionName,p_Var2->cMissionTitle);
    p_Var2 = p_Var2 + 1;
  } while ((int)p_Var2 < 0x63a3f0);
  p_Var3 = TrnMissionList;
  do {
    read_text_label("mission_title",p_Var3->cMissionName,p_Var3->cMissionTitle);
    p_Var3 = p_Var3 + 1;
  } while ((int)p_Var3 < 0x63b7f0);
  return 1;
}
