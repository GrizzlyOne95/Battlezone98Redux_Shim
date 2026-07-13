/*
 * Entry: 0054df41
 * Name: ExitMainMenu
 * Namespace: Global
 * Signature: void ExitMainMenu(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ExitMainMenu(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  i76_total *piVar4;
  i76_total *piVar5;
  bool bVar6;
  
  get_user_entity();
  ClearMenu();
  iVar3 = 0x1d;
  bVar6 = true;
  piVar4 = UserProfilePtr;
  piVar5 = &UserProfileSave;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    iVar2._0_2_ = (piVar5->player).dpid;
    iVar2._2_1_ = (piVar5->player).playerName[0];
    iVar2._3_1_ = (piVar5->player).playerName[1];
    iVar1._0_2_ = (piVar4->player).dpid;
    iVar1._2_1_ = (piVar4->player).playerName[0];
    iVar1._3_1_ = (piVar4->player).playerName[1];
    bVar6 = iVar1 == iVar2;
    piVar4 = (i76_total *)((piVar4->player).playerName + 2);
    piVar5 = (i76_total *)((piVar5->player).playerName + 2);
  } while (bVar6);
  if ((!bVar6) || ((UserProfilePtr->graphicDetail).resolution != ResSave)) {
    if ((UserProfilePtr->graphicDetail).resolution != ResSave) {
      iVar3 = (*Device.VideoMode.ChangeMode)(&Device,(uint)ResSave);
      if (iVar3 == 0) {
        DEBUG_systemError("BattleZone Init_Graphic_System");
      }
      InformMouseOfVideoModeChange();
      Init_View_Record(0);
    }
    (UserProfilePtr->graphicDetail).resolution = ResSave;
    SaveUserProfile();
  }
  SetGASMasterVolumes(-1,-1,-1);
  iVar3 = GetRunning();
  if (iVar3 == 5) {
    UnPauseGAS();
  }
  SetScreenMode(SCREENMODE_SIM);
  return;
}
