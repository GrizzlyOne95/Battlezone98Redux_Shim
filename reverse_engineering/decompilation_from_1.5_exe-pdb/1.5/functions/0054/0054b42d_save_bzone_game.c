/*
 * Entry: 0054b42d
 * Name: save_bzone_game
 * Namespace: Global
 * Signature: int save_bzone_game(int param_1, int param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl save_bzone_game(int param_1,int param_2,char *param_3)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char local_108 [4];
  undefined4 uStack_104;
  char acStack_100 [4];
  undefined4 uStack_fc;
  undefined1 local_88 [128];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_88;
  builtin_strncpy(local_108,"NULL",4);
  uStack_104 = uStack_104 & 0xffffff00;
  memset((int)&uStack_104 + 1,0,0xfb);
  iVar2 = (int)saveGameDesc - (int)param_3;
  do {
    cVar1 = *param_3;
    param_3[iVar2] = cVar1;
    param_3 = param_3 + 1;
  } while (cVar1 != '\0');
  switch(param_2) {
  case 1:
    pcVar3 = "save\\game1.sav";
    break;
  case 2:
    pcVar3 = "save\\game2.sav";
    break;
  case 3:
    pcVar3 = "save\\game3.sav";
    break;
  case 4:
    pcVar3 = "save\\game4.sav";
    break;
  case 5:
    pcVar3 = "save\\game5.sav";
    break;
  case 6:
    pcVar3 = "save\\game6.sav";
    break;
  case 7:
    pcVar3 = "save\\game7.sav";
    break;
  case 8:
    pcVar3 = "save\\game8.sav";
    break;
  case 9:
    pcVar3 = "save\\game9.sav";
    break;
  case 10:
    builtin_strncpy(local_108,"save",4);
    uStack_104._0_1_ = '\\';
    uStack_104._1_1_ = 'g';
    uStack_104._2_1_ = 'a';
    uStack_104._3_1_ = 'm';
    builtin_strncpy(acStack_100,"e10.",4);
    uStack_fc._0_1_ = 's';
    uStack_fc._1_1_ = 'a';
    uStack_fc._2_1_ = 'v';
    uStack_fc._3_1_ = '\0';
    goto LAB_0054b4e9;
  default:
    return 0;
  }
  local_108 = *(char (*) [4])pcVar3;
  uStack_104 = *(uint *)(pcVar3 + 4);
  acStack_100 = *(char (*) [4])(pcVar3 + 8);
  uStack_fc._0_3_ = *(undefined3 *)(pcVar3 + 0xc);
LAB_0054b4e9:
  binarySave = BinarySave != 0;
  missionSave = false;
  iVar2 = SaveGame(local_108,param_1);
  binarySave = false;
  return iVar2;
}
