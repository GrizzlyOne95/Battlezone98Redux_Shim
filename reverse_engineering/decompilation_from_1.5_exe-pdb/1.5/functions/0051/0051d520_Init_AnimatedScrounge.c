/*
 * Entry: 0051d520
 * Name: Init_AnimatedScrounge
 * Namespace: Global
 * Signature: void Init_AnimatedScrounge(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl Init_AnimatedScrounge(void)

{
  char *pcVar1;
  char cVar2;
  char cVar3;
  int iVar4;
  long *plVar5;
  TEXTURE **ppTVar6;
  TEXTURE *pTVar7;
  tagAnimSet *ptVar8;
  int iVar9;
  char *pcVar10;
  long *plVar11;
  int iVar12;
  char local_30;
  tagAnimSet *local_28;
  int local_24;
  undefined4 local_20;
  int local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  memset();
  memset();
  memset();
  GetINIString("AnimatedScrounge","Type0","",AnimNames[0],0x10,missionName);
  GetINIString("AnimatedScrounge","Type1","",AnimNames[1],0x10,missionName);
  GetINIString("AnimatedScrounge","Type2","",AnimNames[2],0x10,missionName);
  GetINIString("AnimatedScrounge","Type3","",AnimNames[3],0x10,missionName);
  GetINIString("AnimatedScrounge","Type4","",AnimNames[4],0x10,missionName);
  GetINIString("AnimatedScrounge","Type5","",AnimNames[5],0x10,missionName);
  GetINIString("AnimatedScrounge","Type6","",AnimNames[6],0x10,missionName);
  GetINIString("AnimatedScrounge","Type7","",AnimNames[7],0x10,missionName);
  animRate = GetINIInt("AnimatedScrounge","Rate",animRate,missionName);
  animSize = GetINIInt("AnimatedScrounge","Size",animSize,missionName);
  animCount = GetINIInt("AnimatedScrounge","Count",animCount,missionName);
  animDiam = GetINIInt("AnimatedScrounge","Diameter",animDiam,missionName);
  if ((animCount < 1) || (0x40 < animCount)) {
    animCount = 0x20;
  }
  iVar9 = 0;
  local_1c = 0;
  ptVar8 = AnimSet;
  do {
    pcVar10 = AnimNames[0] + local_1c;
    if ((pcVar10 != (char *)0x0) && (*pcVar10 != '\0')) {
      iVar12 = -local_1c;
      do {
        cVar2 = *pcVar10;
        pcVar10[(int)(&stack0xff3bae60 + iVar12)] = cVar2;
        pcVar10 = pcVar10 + 1;
      } while (cVar2 != '\0');
      pcVar10 = local_18;
      pcVar1 = local_18 + 1;
      do {
        cVar2 = *pcVar10;
        pcVar10 = pcVar10 + 1;
      } while (cVar2 != '\0');
      cVar2 = pcVar10[(int)&local_20 + (2 - (int)pcVar1)];
      cVar3 = pcVar10[(int)&local_20 + (3 - (int)pcVar1)];
      ptVar8->anims = pcVar10[(int)&local_20 + (1 - (int)pcVar1)] + -0x2f;
      plVar11 = ptVar8->frames;
      *plVar11 = cVar2 * 10 + -0x20f + (int)cVar3;
      iVar12 = 0;
      plVar5 = plVar11;
      do {
        if (iVar12 < ptVar8->anims) {
          iVar4 = *plVar11;
          *plVar5 = iVar4;
          iVar9 = iVar9 + iVar4;
        }
        else {
          *plVar5 = 0;
        }
        iVar12 = iVar12 + 1;
        plVar5 = plVar5 + 1;
      } while (iVar12 < 8);
      if (8 < ptVar8->anims) {
        ptVar8->anims = 8;
      }
    }
    local_1c = local_1c + 0x10;
    ptVar8 = ptVar8 + 1;
  } while ((int)ptVar8 < 0xc45188);
  if ((0 < iVar9) && (ppTVar6 = malloc(iVar9 << 2), ppTVar6 != (TEXTURE **)0x0)) {
    local_1c = 0;
    local_24 = 0;
    local_28 = AnimSet;
    AnimSet[0].bitmaps[0] = ppTVar6;
    do {
      pcVar10 = AnimNames[0] + local_24;
      if ((pcVar10 != (char *)0x0) && (*pcVar10 != '\0')) {
        do {
          cVar2 = *pcVar10;
          pcVar10[(int)(&stack0xff3bae60 + -local_24)] = cVar2;
          pcVar10 = pcVar10 + 1;
        } while (cVar2 != '\0');
        pcVar10 = local_18;
        pcVar1 = local_18 + 1;
        do {
          cVar2 = *pcVar10;
          pcVar10 = pcVar10 + 1;
        } while (cVar2 != '\0');
        local_20 = 0;
        ptVar8 = local_28;
        if (0 < local_28->anims) {
          do {
            plVar11 = ptVar8->frames;
            iVar9 = 0;
            ptVar8->bitmaps[0] = ppTVar6 + local_1c;
            if (0 < *plVar11) {
              iVar12 = local_20 % 10;
              do {
                pcVar10[(int)&local_20 + (2 - (int)pcVar1)] = (char)(iVar9 / 10) + '0';
                local_30 = (char)iVar12;
                pcVar10[(int)&local_20 + (1 - (int)pcVar1)] = local_30 + '0';
                pcVar10[(int)&local_20 + (3 - (int)pcVar1)] = (char)(iVar9 % 10) + '0';
                pTVar7 = TexCache_UseTexture(local_18);
                ppTVar6[local_1c] = pTVar7;
                if (pTVar7 == (TEXTURE *)0x0) {
                  DEBUG_systemWarning("Anim Texture not found, Animated scrounge will be off");
                  Close_AnimatedScrounge();
                  return;
                }
                local_1c = local_1c + 1;
                iVar9 = iVar9 + 1;
              } while (iVar9 < *plVar11);
            }
            local_20 = local_20 + 1;
            ptVar8 = (tagAnimSet *)plVar11;
          } while (local_20 < local_28->anims);
        }
      }
      local_24 = local_24 + 0x10;
      local_28 = local_28 + 1;
    } while ((int)local_28 < 0xc45188);
  }
  return;
}
