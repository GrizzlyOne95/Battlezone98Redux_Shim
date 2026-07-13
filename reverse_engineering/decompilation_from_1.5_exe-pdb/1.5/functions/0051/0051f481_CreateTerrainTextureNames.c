/*
 * Entry: 0051f481
 * Name: CreateTerrainTextureNames
 * Namespace: Global
 * Signature: int CreateTerrainTextureNames(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl CreateTerrainTextureNames(char *param_1)

{
  char cVar1;
  int iVar2;
  void *pvVar3;
  RGB *pRVar4;
  undefined4 *puVar5;
  char *local_318;
  RGB *local_314;
  char local_310 [260];
  char local_20c [260];
  char local_108 [260];
  uint local_4;
  
  local_4 = __security_cookie ^ (uint)&local_318;
  iVar2 = zixIsFileInIndex(missionName);
  if (iVar2 == 0) {
    DEBUG_systemWarning("Could not load terrain %s");
    iVar2 = 0;
  }
  else {
    iVar2 = GetINIInt("World","MusicTrack",-1,missionName);
    InitMusic(iVar2);
    GetINIString("World","IntroMovie","",local_20c,0x104,missionName);
    iVar2 = 0;
    do {
      cVar1 = local_20c[iVar2];
      IntroMovie.dosName[iVar2] = cVar1;
      iVar2 = iVar2 + 1;
    } while (cVar1 != '\0');
    GetINIString("World","OutroMovie","",local_20c,0x104,missionName);
    iVar2 = 0;
    do {
      cVar1 = local_20c[iVar2];
      OutroMovie.dosName[iVar2] = cVar1;
      iVar2 = iVar2 + 1;
    } while (cVar1 != '\0');
    TimeOfDay = GetINIInt("NormalView","Time",0x4b0,missionName);
    Init_Light_Model(TimeOfDay / 100);
    lavaMat = GetINIInt("NormalView","Lava",-1,missionName);
    waveMat = GetINIInt("NormalView","Wave",-1,missionName);
    GetINIString("Color","Palette","",local_108,0x104,missionName);
    GetINIString("Color","Luma","",local_310,0x104,missionName);
    local_314 = UseItem(local_108);
    if (local_314 == (RGB *)0x0) {
      DEBUG_systemWarning("Error loading palette %s");
    }
    local_318 = UseItem(local_310);
    if (local_318 == (char *)0x0) {
      DEBUG_systemWarning("Error loading luminance table %s");
    }
    if (local_314 != (RGB *)0x0) {
      pRVar4 = local_314;
      puVar5 = (undefined4 *)&Default_Palette;
      for (iVar2 = 0xc0; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *(undefined4 *)pRVar4;
        pRVar4 = (RGB *)&pRVar4[1].g;
        puVar5 = puVar5 + 1;
      }
      WritePaletteEntries(local_314,local_318);
      UnlockItem(local_108);
    }
    if (local_318 != (char *)0x0) {
      UnlockItem(local_310);
    }
    GetINIString("Color","Translucency","",local_310,0x104,missionName);
    local_318 = UseItem(local_310);
    if (local_318 == (char *)0x0) {
      DEBUG_systemWarning("Translucency table %s not found; disabled");
    }
    else {
      Device_Init_Chrome_Key_Table(&Device);
      memcpy(Translucency_Table,local_318,0x10000);
      UnlockItem(local_310);
    }
    Device_Set_Chrome_Key(&Device,0xff);
    GetINIString("Color","Alpha","",local_310,0x104,missionName);
    pvVar3 = UseItem(local_310);
    if (pvVar3 == (void *)0x0) {
      DEBUG_systemWarning("Alpha table %s not found; disabled");
    }
    else {
      Device_Init_Chrome_Key_Table(&Device);
      memcpy(Headlight_Mask_Luma,pvVar3,0x10000);
      UnlockItem(local_310);
    }
    iVar2 = 1;
  }
  return iVar2;
}
