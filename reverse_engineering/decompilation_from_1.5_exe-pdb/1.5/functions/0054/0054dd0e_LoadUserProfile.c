/*
 * Entry: 0054dd0e
 * Name: LoadUserProfile
 * Namespace: Global
 * Signature: void LoadUserProfile(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl LoadUserProfile(void)

{
  undefined4 *puVar1;
  char cVar2;
  char cVar3;
  uchar uVar4;
  uchar uVar5;
  uchar uVar6;
  int iVar7;
  void *pvVar8;
  i76_graphicDetail *piVar9;
  FILE *_File;
  int iVar10;
  i76player *piVar11;
  i76_total *piVar12;
  __time64_t _Var13;
  undefined4 auStack_148 [10];
  i76_graphicDetail local_120;
  int local_110;
  char local_10c;
  undefined1 local_10b [67];
  undefined1 local_c8 [192];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_c8;
  local_10c = '\0';
  memset(local_10b,0,0x103);
  if (UserProfilePtr == (i76_total *)0x0) {
    _Var13 = _time64((__time64_t *)0x0);
    srand((uint)_Var13);
    iVar7 = rand();
    iVar7 = iVar7 % 10;
    if (iVar7 < 3) {
      iVar7 = 3;
    }
    local_110 = 0;
    if (0 < iVar7) {
      do {
        pvVar8 = malloc(0x40);
        iVar10 = local_110 + 1;
        puVar1 = auStack_148 + local_110;
        local_110 = iVar10;
        *puVar1 = pvVar8;
      } while (iVar10 < iVar7);
    }
    UserProfilePtr = malloc(0x74);
    iVar10 = 0;
    if (0 < iVar7) {
      do {
        free((void *)auStack_148[iVar10]);
        iVar10 = iVar10 + 1;
      } while (iVar10 < iVar7);
    }
  }
  memset(UserProfilePtr,0,0x74);
  piVar11 = &i76Player;
  piVar12 = UserProfilePtr;
  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
    cVar2 = piVar11->playerName[0];
    cVar3 = piVar11->playerName[1];
    (piVar12->player).dpid = piVar11->dpid;
    (piVar12->player).playerName[0] = cVar2;
    (piVar12->player).playerName[1] = cVar3;
    piVar11 = (i76player *)(piVar11->playerName + 2);
    piVar12 = (i76_total *)((piVar12->player).playerName + 2);
  }
  piVar9 = GetMachineDefaults(&local_120);
  uVar4 = piVar9->clouds;
  uVar5 = piVar9->lineskip;
  uVar6 = piVar9->cockpit;
  piVar12 = UserProfilePtr;
  (piVar12->graphicDetail).resolution = piVar9->resolution;
  (piVar12->graphicDetail).clouds = uVar4;
  (piVar12->graphicDetail).lineskip = uVar5;
  (piVar12->graphicDetail).cockpit = uVar6;
  uVar4 = piVar9->objTex;
  uVar5 = piVar9->shadow;
  uVar6 = piVar9->terrain;
  (piVar12->graphicDetail).hardware = piVar9->hardware;
  (piVar12->graphicDetail).objTex = uVar4;
  (piVar12->graphicDetail).shadow = uVar5;
  (piVar12->graphicDetail).terrain = uVar6;
  uVar4 = piVar9->objDetail;
  uVar5 = piVar9->visibility;
  uVar6 = piVar9->terTex;
  (piVar12->graphicDetail).pit3D = piVar9->pit3D;
  (piVar12->graphicDetail).objDetail = uVar4;
  (piVar12->graphicDetail).visibility = uVar5;
  (piVar12->graphicDetail).terTex = uVar6;
  uVar4 = piVar9->scrounge;
  uVar5 = piVar9->road;
  uVar6 = piVar9->vehTex;
  (piVar12->graphicDetail).brightness = piVar9->brightness;
  (piVar12->graphicDetail).scrounge = uVar4;
  (piVar12->graphicDetail).road = uVar5;
  (piVar12->graphicDetail).vehTex = uVar6;
  (UserProfilePtr->audioControl).music = '\x02';
  (UserProfilePtr->audioControl).sfx = '\b';
  (UserProfilePtr->audioControl).voice = '\n';
  (UserProfilePtr->audioControl).channels = '@';
  (UserProfilePtr->audioControl).stereo = '\x01';
  (UserProfilePtr->audioControl).revChannels = '\0';
  UserProfilePtr->playOption = 0x30;
  (UserProfilePtr->config).jIndex = 0;
  (UserProfilePtr->config).mIndex = 3;
  (UserProfilePtr->config).jSensitivity = 5;
  (UserProfilePtr->config).difficulty = 2;
  (UserProfilePtr->config).option = 0;
  (UserProfilePtr->config).option2 = 0;
  strcat_s(&local_10c,0x104,"BZPLYR.DEF");
  _File = fopen(&local_10c,"rb");
  if (_File != (FILE *)0x0) {
    fread(UserProfilePtr,1,0x74,_File);
    fclose(_File);
  }
  if ((((UserProfilePtr->graphicDetail).resolution < 5) && (UseDDraw == 0)) &&
     ((UserProfilePtr->graphicDetail).resolution = '\x05', firstTime != 0)) {
    SaveUserProfile();
  }
  Cheater = (int)((UserProfilePtr->playOption & 0x30fU) != 0);
  UserProfilePtr->playOption = UserProfilePtr->playOption & 0xfffffcf0;
  firstTime = 0;
  return;
}
