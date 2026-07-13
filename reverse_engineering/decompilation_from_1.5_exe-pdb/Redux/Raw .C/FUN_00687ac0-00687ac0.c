
void FUN_00687ac0(void)

{
  char cVar1;
  undefined8 uVar2;
  char *local_10;
  int local_c;
  
  for (local_c = 0; local_c < 200; local_c = local_c + 1) {
    if (*(int *)(&DAT_02b7a4ac + local_c * 0x97c) != 0) {
      local_10 = &DAT_02b79b40 + local_c * 0x97c;
      do {
        cVar1 = *local_10;
        local_10 = local_10 + 1;
      } while (cVar1 != '\0');
      if (local_10 != &DAT_02b79b41 + local_c * 0x97c) {
        DAT_00920c6f = (&DAT_02b7a4b0)[local_c * 0x97c];
        uVar2 = FUN_00689eb0();
        FUN_00689ec0((float)uVar2 * *(float *)(&DAT_02b7a4a8 + local_c * 0x97c),
                     (float)((ulonglong)uVar2 >> 0x20) * *(float *)(&DAT_02b7a4a8 + local_c * 0x97c)
                    );
        DAT_00920ef4 = 0;
        std::_Init_atomic_counter(DAT_0091552c,*(ulong *)(&DAT_02b7a4a0 + local_c * 0x97c));
        FUN_00689d10(DAT_0091552c,&DAT_02cecee0,*(undefined4 *)(&DAT_02b79b38 + local_c * 0x97c),
                     *(undefined4 *)(&DAT_02b79b3c + local_c * 0x97c),
                     &DAT_02b79b40 + local_c * 0x97c);
        FUN_00689ec0(uVar2);
      }
    }
  }
  return;
}

