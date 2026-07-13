/*
 * Entry: 00572ade
 * Name: read_video_mode
 * Namespace: Global
 * Signature: int read_video_mode(OptionBox * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl read_video_mode(OptionBox *param_1,int param_2)

{
  int *piVar1;
  i76_total *piVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  int local_2c;
  char local_28 [32];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  puVar5 = &DAT_0062da90;
  iVar4 = 0;
  piVar1 = &DAT_0062da90;
  do {
    if ((piVar1[-2] != 0) && (*piVar1 == 0)) {
      iVar4 = iVar4 + 1;
    }
    piVar1 = piVar1 + 8;
  } while ((int)piVar1 < 0x62e270);
  iVar3 = 0;
  piVar1 = &DAT_0062da90;
  do {
    if ((piVar1[-2] != 0) && (*piVar1 == 1)) {
      iVar3 = iVar3 + 1;
    }
    piVar1 = piVar1 + 8;
  } while ((int)piVar1 < 0x62e270);
  if ((UserProfilePtr->graphicDetail).hardware == '\0') {
    if (iVar4 == 0) {
      if (iVar3 == 0) {
LAB_00572b46:
        DEBUG_systemError("BattleZone (read_video_mode) no res modes found!");
        return 0;
      }
      (UserProfilePtr->graphicDetail).hardware = '\x01';
LAB_00572b5a:
      param_1->nItemCount = iVar3;
      goto LAB_00572b5d;
    }
  }
  else {
    if (iVar3 != 0) goto LAB_00572b5a;
    if (iVar4 == 0) goto LAB_00572b46;
    (UserProfilePtr->graphicDetail).hardware = '\0';
  }
  param_1->nItemCount = iVar4;
LAB_00572b5d:
  iVar4 = 1;
  local_2c = 0;
  piVar2 = UserProfilePtr;
  do {
    if ((puVar5[-2] != 0) && (*puVar5 == (uint)(piVar2->graphicDetail).hardware)) {
      sprintf(local_28,"%dx%d",puVar5[2],puVar5[3]);
      OptionBox::LoadItemList(param_1,local_2c,local_28,iVar4);
      local_2c = local_2c + 1;
      piVar2 = UserProfilePtr;
    }
    puVar5 = puVar5 + 8;
    iVar4 = iVar4 + 1;
  } while ((int)puVar5 < 0x62e270);
  iVar4 = 0;
  if (param_2 == 0) {
    if (0 < param_1->nItemCount) {
      piVar1 = &param_1->itemList[0].nReturnNum;
      do {
        if (*piVar1 == (uint)(piVar2->graphicDetail).resolution) goto LAB_00572bc2;
        iVar4 = iVar4 + 1;
        piVar1 = piVar1 + 0x41;
      } while (iVar4 < param_1->nItemCount);
    }
    OptionBox::SetOptionBox(param_1,0);
    (UserProfilePtr->graphicDetail).resolution = (uchar)param_1->itemList[0].nReturnNum;
    return 0;
  }
  (piVar2->graphicDetail).resolution = (uchar)param_1->itemList[0].nReturnNum;
LAB_00572bc2:
  OptionBox::SetOptionBox(param_1,iVar4);
  return 1;
}
