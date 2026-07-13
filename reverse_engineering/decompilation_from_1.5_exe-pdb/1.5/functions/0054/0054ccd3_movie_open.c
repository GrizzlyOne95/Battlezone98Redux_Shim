/*
 * Entry: 0054ccd3
 * Name: movie_open
 * Namespace: Global
 * Signature: int movie_open(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl movie_open(char *param_1)

{
  char cVar1;
  MCIERROR MVar2;
  char *pcVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  undefined1 local_658 [4];
  uint local_654;
  char *local_650;
  char *local_64c;
  char *local_648;
  char *local_644;
  char local_640 [104];
  undefined1 local_5d8 [152];
  char local_540 [256];
  char local_440 [256];
  char local_340 [256];
  char local_240 [256];
  CHAR local_140 [55];
  char cStack_109;
  char local_108;
  undefined3 local_107;
  undefined4 uStack_104;
  undefined4 uStack_100;
  char acStack_fc [244];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_5d8;
  local_644 = param_1;
  mci_movie.aliasName = "movie";
  CDLetter = CDDriveLetter();
  _local_108 = 0x69766f6d;
  uStack_104 = CONCAT13(uStack_104._3_1_,0x5c65);
  pcVar3 = param_1;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  pcVar7 = &cStack_109;
  do {
    pcVar6 = pcVar7 + 1;
    pcVar7 = pcVar7 + 1;
  } while (*pcVar6 != '\0');
  pcVar6 = param_1;
  for (uVar4 = (uint)((int)pcVar3 - (int)param_1) >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar4 = (int)pcVar3 - (int)param_1 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar7 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  }
  iVar5 = 0;
  do {
    pcVar3 = &local_108 + iVar5;
    local_540[iVar5] = *pcVar3;
    iVar5 = iVar5 + 1;
  } while (*pcVar3 != '\0');
  uStack_104 = 0x6569766f;
  uStack_100 = CONCAT22(uStack_100._2_2_,0x5c);
  _local_108 = CONCAT31(0x6d5c3a,CDLetter);
  pcVar3 = param_1;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  pcVar7 = &cStack_109;
  do {
    pcVar6 = pcVar7 + 1;
    pcVar7 = pcVar7 + 1;
  } while (*pcVar6 != '\0');
  pcVar6 = param_1;
  for (uVar4 = (uint)((int)pcVar3 - (int)param_1) >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar4 = (int)pcVar3 - (int)param_1 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar7 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  }
  iVar5 = 0;
  do {
    pcVar3 = &local_108 + iVar5;
    local_440[iVar5] = *pcVar3;
    iVar5 = iVar5 + 1;
  } while (*pcVar3 != '\0');
  uStack_104._0_1_ = 'z';
  uStack_104._1_1_ = 'o';
  uStack_104._2_1_ = 'n';
  uStack_104._3_1_ = 'e';
  uStack_100._0_1_ = '\\';
  uStack_100._1_1_ = 'm';
  uStack_100._2_1_ = 'o';
  uStack_100._3_1_ = 'v';
  builtin_strncpy(acStack_fc,"ie\\",4);
  _local_108 = CONCAT31(0x625c3a,CDLetter);
  pcVar3 = param_1;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  pcVar7 = &cStack_109;
  do {
    pcVar6 = pcVar7 + 1;
    pcVar7 = pcVar7 + 1;
  } while (*pcVar6 != '\0');
  pcVar6 = param_1;
  for (uVar4 = (uint)((int)pcVar3 - (int)param_1) >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar4 = (int)pcVar3 - (int)param_1 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar7 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  }
  iVar5 = 0;
  do {
    pcVar3 = &local_108 + iVar5;
    local_340[iVar5] = *pcVar3;
    iVar5 = iVar5 + 1;
  } while (*pcVar3 != '\0');
  local_64c = local_340;
  local_648 = mci_movie.aliasName;
  local_650 = "AVIVideo";
  MVar2 = mciSendCommandA(0,0x803,0x2600,(DWORD_PTR)local_658);
  if (MVar2 != 0) {
    local_64c = local_440;
    MVar2 = mciSendCommandA(0,0x803,0x2600,(DWORD_PTR)local_658);
    if (MVar2 != 0) {
      local_64c = local_540;
      MVar2 = mciSendCommandA(0,0x803,0x2600,(DWORD_PTR)local_658);
      if (MVar2 != 0) {
        sprintf(local_640,"movie_open ( %s ) Error!",local_644);
        return 0;
      }
    }
  }
  mci_movie.movieID = local_654;
  sprintf(local_240,"seek %s to end",mci_movie.aliasName);
  MVar2 = mciSendStringA(local_240,local_140,0x37,(HWND)0x0);
  if (MVar2 != 0) {
    DEBUG_systemError("BattleZone (mcimovie) movie_seek error!");
  }
  sprintf(local_240,"seek %s to start",mci_movie.aliasName);
  MVar2 = mciSendStringA(local_240,local_140,0x37,(HWND)0x0);
  if (MVar2 != 0) {
    DEBUG_systemError("BattleZone (mcimovie) movie_seek error!");
  }
  return 1;
}
