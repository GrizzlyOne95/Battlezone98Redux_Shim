/*
 * Entry: 0051ca51
 * Name: Init_Clouds
 * Namespace: Global
 * Signature: int Init_Clouds(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl Init_Clouds(void)

{
  int iVar1;
  TEXTURE *pTVar2;
  int extraout_EAX;
  int extraout_EAX_00;
  code *pcVar3;
  int iVar4;
  int *piVar5;
  int local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  memset(&CloudSet,0,0xf0);
  memset(VisibleCloud,0,0x280);
  CloudSet.cloudCount = GetINIInt(sectionStr,"Count",0,missionName);
  iVar1 = GetINIInt(sectionStr,"TileSize",100,missionName);
  CloudSet.tileSize = (float)iVar1;
  CloudSet.cloudType = GetINIInt(sectionStr,"Type",0,missionName);
  if (0 < CloudSet.cloudCount) {
    if (0x20 < CloudSet.cloudCount) {
      CloudSet.cloudCount = 0x20;
    }
    local_1c = 0;
    do {
      sprintf(local_18,"Texture%d",local_1c);
      GetINIString(sectionStr,local_18,"",CloudSet.name[CloudSet.typeCount],0x10,missionName);
      sprintf(local_18,"Size%d",local_1c);
      iVar1 = GetINIInt(sectionStr,local_18,100,missionName);
      CloudSet.size[CloudSet.typeCount] = (float)iVar1;
      sprintf(local_18,"Height%d",local_1c);
      iVar1 = GetINIInt(sectionStr,local_18,100,missionName);
      CloudSet.height[CloudSet.typeCount] = (float)iVar1 + (float)local_1c;
      if (CloudSet.name[CloudSet.typeCount][0] != '\0') {
        pTVar2 = TexCache_UseTexture(CloudSet.name[CloudSet.typeCount]);
        CloudSet.texture[CloudSet.typeCount] = pTVar2;
        if (CloudSet.texture[CloudSet.typeCount] != (TEXTURE *)0x0) {
          CloudSet.typeCount = CloudSet.typeCount + 1;
        }
      }
      local_1c = local_1c + 1;
    } while (local_1c < 8);
    if (0 < CloudSet.typeCount) {
      local_1c = 0;
      if (CloudSet.cloudCount < 1) {
        return CloudSet.cloudCount;
      }
      pcVar3 = rand_exref;
      piVar5 = &VisibleCloud[0].type;
      do {
        iVar1 = (*pcVar3)();
        iVar4 = iVar1 * CloudSet.typeCount >> 0xf;
        iVar1 = (*pcVar3)();
        piVar5[1] = (iVar1 << 2) >> 0xf;
        *piVar5 = iVar4;
        iVar1 = (*pcVar3)();
        _ftol2_sse();
        pcVar3 = rand_exref;
        ((tagVisibleCloud *)(piVar5 + -3))->x = (float)(iVar1 * extraout_EAX >> 0xf);
        piVar5[-2] = (int)CloudSet.height[iVar4];
        iVar4 = rand();
        _ftol2_sse();
        iVar1 = CloudSet.cloudCount;
        local_1c = local_1c + 1;
        piVar5[-1] = (int)(float)(iVar4 * extraout_EAX_00 >> 0xf);
        piVar5 = piVar5 + 5;
      } while (local_1c < iVar1);
      return iVar1;
    }
  }
  CloudSet.cloudCount = 0;
  return 0;
}
