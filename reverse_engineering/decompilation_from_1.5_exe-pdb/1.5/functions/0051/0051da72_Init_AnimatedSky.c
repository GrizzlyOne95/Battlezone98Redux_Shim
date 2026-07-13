/*
 * Entry: 0051da72
 * Name: Init_AnimatedSky
 * Namespace: Global
 * Signature: void Init_AnimatedSky(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl Init_AnimatedSky(void)

{
  char cVar1;
  bool bVar2;
  ulong uVar3;
  int iVar4;
  char *pcVar5;
  TEXTURE **ppTVar6;
  char (*pacVar7) [16];
  TEXTURE *pTVar8;
  int *piVar9;
  char (*local_38) [16];
  undefined1 *local_34;
  char (*local_30) [16];
  char (*local_2c) [16];
  char local_28 [11];
  char local_1d [5];
  char local_18 [16];
  undefined4 local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  memset();
  memset();
  SkySet.anims = GetINIInt(sectionStr,"Count",0x20,missionName);
  SkySet.animDiam = GetINIInt(sectionStr,"Diameter",400,missionName);
  SkySet.minDelay = GetINIInt(sectionStr,"minDelay",100,missionName);
  SkySet.maxDelay = GetINIInt(sectionStr,"maxDelay",500,missionName);
  if ((SkySet.anims < 1) || (0x20 < SkySet.anims)) {
    SkySet.anims = 0x10;
  }
  local_2c = (char (*) [16])0x0;
  local_30 = SkySet.name;
  do {
    sprintf(local_28,"Anim%d");
    GetINIString(sectionStr,local_28,"",*local_30,0x10,missionName);
    sprintf(local_28,"Rate%d");
    uVar3 = GetINIInt(sectionStr,local_28,100,missionName);
    SkySet.animRate[(int)local_2c] = uVar3;
    sprintf(local_28,"Size%d");
    iVar4 = GetINIInt(sectionStr,local_28,0x244,missionName);
    local_30 = local_30 + 1;
    SkySet.animSize[(int)local_2c] = iVar4;
    local_2c = (char (*) [16])((int)local_2c + 1);
  } while ((int)local_30 < 0xc420a4);
  local_30 = (char (*) [16])0x0;
  piVar9 = SkySet.frames;
  local_2c = SkySet.name;
  local_34 = &stack0xff3bdfc4;
  do {
    if ((local_2c != (char (*) [16])0x0) && (pacVar7 = local_2c, (*local_2c)[0] != '\0')) {
      do {
        cVar1 = (*pacVar7)[0];
        local_34[(int)pacVar7] = cVar1;
        pacVar7 = (char (*) [16])(*pacVar7 + 1);
      } while (cVar1 != '\0');
      pcVar5 = local_18;
      do {
        cVar1 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar1 != '\0');
      iVar4 = pcVar5[(int)(local_28 + (10 - (int)(local_18 + 1)))] * 10 + -0x210 +
              (int)pcVar5[(int)(local_1d + -(int)(local_18 + 1))];
      local_30 = (char (*) [16])((int)local_30 + iVar4);
      *piVar9 = iVar4;
    }
    local_2c = local_2c + 1;
    local_34 = local_34 + -0x10;
    piVar9 = piVar9 + 1;
  } while ((int)local_2c < 0xc420a4);
  if ((0 < (int)local_30) && (ppTVar6 = malloc((int)local_30 << 2), ppTVar6 != (TEXTURE **)0x0)) {
    local_30 = (char (*) [16])0x0;
    local_2c = (char (*) [16])SkySet.frames;
    local_38 = SkySet.name;
    SkySet.bitmaps[0] = ppTVar6;
    local_34 = &stack0xff3bdfc4;
    do {
      if ((local_38 != (char (*) [16])0x0) && (pacVar7 = local_38, (*local_38)[0] != '\0')) {
        do {
          cVar1 = (*pacVar7)[0];
          local_34[(int)pacVar7] = cVar1;
          pacVar7 = (char (*) [16])(*pacVar7 + 1);
        } while (cVar1 != '\0');
        pcVar5 = local_18;
        do {
          cVar1 = *pcVar5;
          pcVar5 = pcVar5 + 1;
        } while (cVar1 != '\0');
        *(TEXTURE ***)((int)local_2c + 0x20) = ppTVar6 + (int)local_30;
        if (0 < *(int *)local_2c) {
          iVar4 = 1;
          do {
            (local_28 + 10)[(int)(pcVar5 + (0x17 - (int)&stack0x00000000))] =
                 (char)(iVar4 / 10) + '0';
            local_1d[(int)(pcVar5 + (0x17 - (int)&stack0x00000000))] = (char)(iVar4 % 10) + '0';
            pTVar8 = TexCache_UseTexture(local_18);
            ppTVar6[(int)local_30] = pTVar8;
            if (pTVar8 == (TEXTURE *)0x0) {
              DEBUG_systemWarning("Texture not found, Animated sky will be turned off");
              Close_AnimatedSky();
              return;
            }
            local_30 = (char (*) [16])((int)local_30 + 1);
            bVar2 = iVar4 < *(int *)local_2c;
            iVar4 = iVar4 + 1;
          } while (bVar2);
        }
      }
      local_34 = local_34 + -0x10;
      local_38 = local_38 + 1;
      local_2c = (char (*) [16])((int)local_2c + 4);
    } while ((int)local_38 < 0xc420a4);
  }
  return;
}
