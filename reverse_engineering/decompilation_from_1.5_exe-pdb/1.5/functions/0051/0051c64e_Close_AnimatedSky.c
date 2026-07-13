/*
 * Entry: 0051c64e
 * Name: Close_AnimatedSky
 * Namespace: Global
 * Signature: void Close_AnimatedSky(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl Close_AnimatedSky(void)

{
  char cVar1;
  bool bVar2;
  char *pcVar3;
  int *piVar4;
  int iVar5;
  int local_1c;
  char local_18 [16];
  undefined4 local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if ((SkySet.bitmaps[0] != (TEXTURE **)0x0) && (hDefaultHeap != (void *)0x0)) {
    free(SkySet.bitmaps[0]);
  }
  local_1c = 0;
  piVar4 = SkySet.frames;
  do {
    pcVar3 = SkySet.name[0] + local_1c;
    if ((pcVar3 != (char *)0x0) && (*pcVar3 != '\0')) {
      do {
        cVar1 = *pcVar3;
        pcVar3[(int)(&stack0xff3bdfc4 + -local_1c)] = cVar1;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
      pcVar3 = local_18;
      do {
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
      if (0 < *piVar4) {
        iVar5 = 1;
        do {
          (&stack0xffffffe2)[(int)(pcVar3 + (0x17 - (int)&stack0x00000000))] =
               (char)(iVar5 / 10) + '0';
          (&stack0xffffffe3)[(int)(pcVar3 + (0x17 - (int)&stack0x00000000))] =
               (char)(iVar5 % 10) + '0';
          TexCache_UnlockTexture(local_18);
          bVar2 = iVar5 < *piVar4;
          iVar5 = iVar5 + 1;
        } while (bVar2);
      }
    }
    local_1c = local_1c + 0x10;
    piVar4 = piVar4 + 1;
  } while ((int)piVar4 < 0xc42144);
  memset();
  memset();
  return;
}
