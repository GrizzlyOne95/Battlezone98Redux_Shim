/*
 * Entry: 0054b217
 * Name: SaveGame
 * Namespace: Global
 * Signature: int SaveGame(char * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SaveGame(char *param_1,int param_2)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  FILE *_File;
  int local_c;
  undefined4 uStack_8;
  
  local_c = GameObject::GetSeqCount();
  if (param_2 == 0) {
    pcVar2 = strrchr(param_1,0x2e);
    if ((pcVar2 == (char *)0x0) || (iVar3 = _stricmp(pcVar2,".TRN"), iVar3 != 0)) {
      uStack_8 = uStack_8 & 0xffffff;
      if (zoneDataChanged == 0) goto LAB_0054b2c8;
    }
    else {
      uStack_8 = CONCAT13(1,(undefined3)uStack_8);
    }
    pcVar4 = strrchr(param_1,0x5c);
    pcVar2 = param_1;
    if (pcVar4 != (char *)0x0) {
      pcVar2 = pcVar4 + 1;
    }
    pcVar4 = pcVar2;
    do {
      cVar1 = *pcVar4;
      pcVar4[(int)TerrainName - (int)pcVar2] = cVar1;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    if (uStack_8._3_1_ == '\0') {
      iVar3 = (int)&msn_filename - (int)pcVar2;
      do {
        cVar1 = *pcVar2;
        pcVar2[iVar3] = cVar1;
        pcVar2 = pcVar2 + 1;
      } while (cVar1 != '\0');
    }
    pcVar2 = strrchr(TerrainName,0x2e);
    if (pcVar2 != (char *)0x0) {
      *pcVar2 = '\0';
    }
    SaveZoneFiles(param_1);
    if (uStack_8._3_1_ != '\0') {
      return 1;
    }
  }
LAB_0054b2c8:
  _File = fopen(param_1,"wb");
  if (_File != (FILE *)0x0) {
    version = 0x415;
    uStack_8._0_3_ = CONCAT12(binarySave,(undefined2)uStack_8);
    binarySave = false;
    out((_iobuf *)_File,&version,4,"version");
    out((_iobuf *)_File,(bool *)((int)&uStack_8 + 2),1,"binarySave");
    binarySave = (bool)uStack_8._2_1_;
    out((_iobuf *)_File,&msn_filename,0x10,"msn_filename");
    out((_iobuf *)_File,&local_c,4,"seq_count");
    out((_iobuf *)_File,&missionSave,1,"missionSave");
    if (missionSave == false) {
      out((_iobuf *)_File,&param_2,4,"runType");
      out((_iobuf *)_File,saveGameDesc,0x100,"saveGameDesc");
      SaveShellGame((_iobuf *)_File,param_2);
    }
    out((_iobuf *)_File,TerrainName,100,"TerrainName");
    if (missionSave == false) {
      param_2 = (int)Get_Time();
      out((_iobuf *)_File,(float *)&param_2,4,"start_time");
    }
    GameObject::SaveAll((_iobuf *)_File);
    Team::SaveAll((_iobuf *)_File);
    AiMission::SaveMission((_iobuf *)_File);
    AOI::SaveAll((_iobuf *)_File);
    AiPath::SaveAll((_iobuf *)_File);
    if (missionSave == false) {
      AiTask::SaveAll((_iobuf *)_File);
    }
    SaveScriptUtils((_iobuf *)_File);
    fclose(_File);
    return 1;
  }
  DEBUG_systemWarning("Failed to save game\n");
  return 0;
}
