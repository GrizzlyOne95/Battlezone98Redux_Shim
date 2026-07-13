
void FUN_0069feb0(char param_1)

{
  bool bVar1;
  char cVar2;
  short *local_10;
  int local_c;
  
  if (DAT_00920c9a != '\0') {
    for (local_c = 1; local_c < DAT_02ceb7fc; local_c = local_c + 1) {
      *(undefined1 *)(local_c * 0x9c + DAT_02ceb7e8 + 0x6c + (int)param_1) = 0;
      *(undefined1 *)(local_c * 0x9c + DAT_02ceb7e8 + 0x5c + (int)param_1) = 0;
      bVar1 = true;
      for (local_10 = *(short **)(DAT_02ceb7e8 + 0xc + local_c * 0x9c); *local_10 != 0;
          local_10 = local_10 + 1) {
        cVar2 = FUN_006a02b0(*local_10,param_1);
        if (cVar2 == '\0') {
          bVar1 = false;
          break;
        }
      }
      if (bVar1) {
        *(undefined1 *)(local_c * 0x9c + DAT_02ceb7e8 + 0x5c + (int)param_1) = 1;
        for (local_10 = *(short **)(DAT_02ceb7e8 + 0x14 + local_c * 0x9c); *local_10 != 0;
            local_10 = local_10 + 1) {
          cVar2 = FUN_006a02b0(*local_10,param_1);
          if (cVar2 != '\0') {
            *(undefined1 *)(local_c * 0x9c + DAT_02ceb7e8 + 0x6c + (int)param_1) = 1;
            break;
          }
        }
      }
    }
  }
  return;
}

