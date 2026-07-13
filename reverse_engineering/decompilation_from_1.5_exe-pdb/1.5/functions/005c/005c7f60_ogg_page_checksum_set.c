/*
 * Entry: 005c7f60
 * Name: ogg_page_checksum_set
 * Namespace: Global
 * Signature: undefined ogg_page_checksum_set()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* ogg_page_checksum_set */

void __cdecl ogg_page_checksum_set(int *param_1)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = 0;
  if (param_1 != (int *)0x0) {
    *(undefined1 *)(*param_1 + 0x16) = 0;
    *(undefined1 *)(*param_1 + 0x17) = 0;
    *(undefined1 *)(*param_1 + 0x18) = 0;
    *(undefined1 *)(*param_1 + 0x19) = 0;
    uVar1 = 0;
    if (0 < param_1[1]) {
      do {
        uVar1 = uVar1 << 8 ^
                *(uint *)(&DAT_00623308 + ((uint)*(byte *)(*param_1 + iVar2) ^ uVar1 >> 0x18) * 4);
        iVar2 = iVar2 + 1;
      } while (iVar2 < param_1[1]);
    }
    iVar2 = 0;
    if (0 < param_1[3]) {
      do {
        uVar1 = uVar1 << 8 ^
                *(uint *)(&DAT_00623308 + ((uint)*(byte *)(param_1[2] + iVar2) ^ uVar1 >> 0x18) * 4)
        ;
        iVar2 = iVar2 + 1;
      } while (iVar2 < param_1[3]);
    }
    *(char *)(*param_1 + 0x16) = (char)uVar1;
    *(char *)(*param_1 + 0x17) = (char)(uVar1 >> 8);
    *(char *)(*param_1 + 0x18) = (char)(uVar1 >> 0x10);
    *(char *)(*param_1 + 0x19) = (char)(uVar1 >> 0x18);
  }
  return;
}
