/*
 * Entry: 0051c38e
 * Name: Close_AnimatedScrounge
 * Namespace: Global
 * Signature: void Close_AnimatedScrounge(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl Close_AnimatedScrounge(void)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  tagAnimSet *ptVar6;
  tagAnimSet *local_28;
  undefined4 local_20;
  int local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if ((AnimSet[0].bitmaps[0] != (TEXTURE **)0x0) && (hDefaultHeap != (void *)0x0)) {
    free(AnimSet[0].bitmaps[0]);
  }
  local_1c = 0;
  local_28 = AnimSet;
  do {
    pcVar3 = AnimNames[0] + local_1c;
    if ((pcVar3 != (char *)0x0) && (*pcVar3 != '\0')) {
      do {
        cVar2 = *pcVar3;
        pcVar3[(int)(&stack0xff3bae60 + -local_1c)] = cVar2;
        pcVar3 = pcVar3 + 1;
      } while (cVar2 != '\0');
      pcVar3 = local_18;
      pcVar1 = local_18 + 1;
      do {
        cVar2 = *pcVar3;
        pcVar3 = pcVar3 + 1;
      } while (cVar2 != '\0');
      local_20 = 0;
      ptVar6 = local_28;
      if (0 < local_28->anims) {
        do {
          ptVar6 = (tagAnimSet *)ptVar6->frames;
          iVar5 = 0;
          if (0 < *(int *)ptVar6) {
            iVar4 = local_20 % 10;
            do {
              pcVar3[(int)&local_20 + (2 - (int)pcVar1)] = (char)(iVar5 / 10) + '0';
              pcVar3[(int)&local_20 + (1 - (int)pcVar1)] = (char)iVar4 + '0';
              pcVar3[(int)&local_20 + (3 - (int)pcVar1)] = (char)(iVar5 % 10) + '0';
              TexCache_UnlockTexture(local_18);
              iVar5 = iVar5 + 1;
            } while (iVar5 < *(int *)ptVar6);
          }
          local_20 = local_20 + 1;
        } while (local_20 < local_28->anims);
      }
    }
    local_1c = local_1c + 0x10;
    local_28 = local_28 + 1;
  } while ((int)local_28 < 0xc45188);
  memset();
  memset();
  memset();
  return;
}
