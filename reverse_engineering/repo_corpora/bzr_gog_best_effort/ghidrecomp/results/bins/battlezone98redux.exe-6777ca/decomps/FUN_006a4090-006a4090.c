
void FUN_006a4090(void)

{
  undefined4 *puVar1;
  void *pvVar2;
  uint local_8;
  
  DAT_009310c4 = size();
  DAT_0093101c = (void *)FUN_0083d92c(-(uint)((int)((ulonglong)DAT_009310c4 * 0x80 >> 0x20) != 0) |
                                      (uint)((ulonglong)DAT_009310c4 * 0x80));
  memset(DAT_0093101c,0,DAT_009310c4 << 7);
  for (local_8 = 0; (int)local_8 < (int)DAT_009310c4; local_8 = local_8 + 1) {
    pvVar2 = (void *)(local_8 * 0x80 + (int)DAT_0093101c);
    puVar1 = (undefined4 *)FUN_004200d0(local_8);
    FUN_006a12b0(*(undefined4 *)*puVar1,pvVar2);
    *(uint *)((int)DAT_0093101c + local_8 * 0x80 + 0x24) =
         *(uint *)((int)DAT_0093101c + local_8 * 0x80 + 0x24) & 0xfffc03ff | (local_8 & 0xff) << 10;
  }
  return;
}

