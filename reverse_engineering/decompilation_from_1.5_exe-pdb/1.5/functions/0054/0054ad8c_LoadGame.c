/*
 * Entry: 0054ad8c
 * Name: LoadGame
 * Namespace: Global
 * Signature: int LoadGame(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl LoadGame(char *param_1)

{
  char cVar1;
  bool bVar2;
  char *pcVar3;
  int iVar4;
  _iobuf *p_Var5;
  char *pcVar6;
  FILE *_File;
  int *piVar7;
  undefined1 *puVar8;
  long lVar9;
  code *pcVar10;
  int local_18;
  int local_14;
  float local_10;
  uint local_c;
  char local_5;
  
  pcVar10 = strrchr_exref;
  if (param_1 == (char *)0x0) {
    return 0;
  }
  DistributedObject::dwLocalIDCounter = 1;
  pcVar3 = strrchr(param_1,0x5c);
  do_load_bar(shell_hwnd,1);
  if (pcVar3 == (char *)0x0) {
    pcVar3 = param_1;
    do {
      cVar1 = *pcVar3;
      pcVar3[(int)TerrainName - (int)param_1] = cVar1;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    pcVar3 = param_1;
    do {
      cVar1 = *pcVar3;
      pcVar3[(int)&msn_filename - (int)param_1] = cVar1;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    pcVar3 = strrchr(TerrainName,0x2e);
    if (pcVar3 != (char *)0x0) {
      *pcVar3 = '\0';
    }
    if ((NobodyHome != 0) ||
       ((pcVar3 = strrchr(param_1,0x2e), pcVar3 != (char *)0x0 &&
        (iVar4 = _stricmp(pcVar3,".TRN"), iVar4 == 0)))) {
LAB_0054aecf:
      iVar4 = LoadDefaultGame(&msn_filename);
      return iVar4;
    }
    local_5 = '\x01';
    p_Var5 = zixReadFile(param_1,(int *)&local_c);
    if (p_Var5 == (_iobuf *)0x0) {
      DEBUG_systemWarning("Could not load \"%s\"");
      iVar4 = LoadDefaultGame(&msn_filename);
      return iVar4;
    }
  }
  else {
    pcVar3 = pcVar3 + 1;
    pcVar6 = pcVar3;
    do {
      cVar1 = *pcVar6;
      pcVar6[(int)TerrainName - (int)pcVar3] = cVar1;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    pcVar6 = pcVar3;
    do {
      cVar1 = *pcVar6;
      pcVar6[(int)&msn_filename - (int)pcVar3] = cVar1;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    pcVar6 = strrchr(TerrainName,0x2e);
    if (pcVar6 != (char *)0x0) {
      *pcVar6 = '\0';
    }
    if ((NobodyHome != 0) ||
       ((pcVar3 = strrchr(pcVar3,0x2e), pcVar3 != (char *)0x0 &&
        (iVar4 = _stricmp(pcVar3,".TRN"), iVar4 == 0)))) goto LAB_0054aecf;
    local_5 = '\0';
    _File = fopen(param_1,"rb");
    if (_File == (FILE *)0x0) {
      piVar7 = _errno();
      strerror(*piVar7);
      DEBUG_systemWarning("Could not load \"%s\": %s");
      iVar4 = LoadDefaultGame(&msn_filename);
      return iVar4;
    }
    fseek(_File,0,2);
    local_c = ftell(_File);
    fseek(_File,0,0);
    p_Var5 = operator_new__(local_c);
    fread(p_Var5,1,local_c,_File);
    fclose(_File);
    pcVar10 = strrchr_exref;
  }
  p_Var5 = in_open(p_Var5,local_c);
  do_load_bar(shell_hwnd,5);
  local_10 = 0.0;
  binarySave = false;
  in(p_Var5,&version,4);
  if ((0x3fe < version) && (in(p_Var5,&binarySave,1), 0x3ff < version)) {
    in(p_Var5,&msn_filename,0x10);
  }
  param_1._3_1_ = in(p_Var5,&local_18,4);
  if (version < 0x3f8) {
    missionSave = false;
  }
  else {
    param_1._3_1_ = in(p_Var5,&missionSave,1);
  }
  if (version < 0x407) {
LAB_0054b069:
    if ((missionSave != false) || (0x40b < version)) goto LAB_0054b0a7;
    DEBUG_systemWarning("Old Saved Games are not backwards compatible");
  }
  else {
    if (missionSave == false) {
      param_1._3_1_ = in(p_Var5,&local_14,4);
      if (0x409 < version) {
        in(p_Var5,saveGameDesc,0x100);
      }
      LoadShellGame(p_Var5,local_14);
      goto LAB_0054b069;
    }
LAB_0054b0a7:
    if (0x3ee < version) {
      param_1._3_1_ = in(p_Var5,TerrainName,100);
      puVar8 = (undefined1 *)(*pcVar10)(TerrainName,0x2e);
      if (puVar8 != (undefined1 *)0x0) {
        *puVar8 = 0;
      }
    }
    Close_Terrain_Texture_Info();
    TerrainSaveName(TerrainName);
    CreateTerrainTextureNames((char *)0x0);
    lVar9 = Init_Zone_Manager(TerrainName);
    if ((lVar9 != 0) && (iVar4 = Terrain_Create(0,0,0.0), iVar4 != 0)) {
      Set_Terrain_Texture_Info();
      DisplayInterface_LoadColors();
      do_load_bar(shell_hwnd,0xe);
      if ((0x3ea < version) && (missionSave == false)) {
        param_1._3_1_ = in(p_Var5,&local_10,4);
      }
      InitPathing();
      if ((((param_1._3_1_ != false) && (bVar2 = GameObject::LoadAll(p_Var5), bVar2)) &&
          (bVar2 = Team::LoadAll(p_Var5), bVar2)) &&
         (((bVar2 = AiMission::LoadMission(p_Var5), bVar2 && (bVar2 = AOI::LoadAll(p_Var5), bVar2))
          && (bVar2 = AiPath::LoadAll(p_Var5), bVar2)))) {
        Addr::PartialCleanup();
        if (missionSave == false) {
          AiTask::LoadAll(p_Var5);
        }
        LoadScriptUtils(p_Var5);
        Addr::Cleanup();
        GameObject::SetSeqCount(local_18);
        bVar2 = Net::IsNetGame();
        if (!bVar2) {
          Set_Game_Start_Time(local_10);
          Pause();
        }
        AiMission::PostLoadMission();
        GameObject::PostLoadAll();
        Team::PostLoadAll();
        if (missionSave == false) {
          AiTask::PostLoadAll();
        }
        PostLoadScriptUtils();
        iVar4 = 1;
        goto LAB_0054b08b;
      }
    }
  }
  iVar4 = 0;
LAB_0054b08b:
  p_Var5 = in_close(p_Var5);
  if (local_5 == '\0') {
    operator_delete__(p_Var5);
  }
  else {
    zixFree(p_Var5);
  }
  return iVar4;
}
