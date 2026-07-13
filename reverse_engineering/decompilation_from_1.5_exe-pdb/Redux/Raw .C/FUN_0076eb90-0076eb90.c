
void FUN_0076eb90(void)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined1 *puVar3;
  char *pcVar4;
  void *_Src;
  undefined4 *local_9b8;
  uint local_9b4;
  uint local_9b0;
  uint local_9a8;
  undefined1 local_9a4 [2399];
  undefined4 uStack_45;
  undefined1 local_40 [44];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085dd48;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  local_14 = uVar2;
  for (local_9b4 = 0; (int)local_9b4 < 0x30; local_9b4 = local_9b4 + 1) {
    if (0x95f < local_9b4) {
      ___report_rangecheckfailure(uVar2);
    }
    local_9a4[local_9b4] = 0;
  }
  local_9a8 = 0;
  do {
    if (0x2f < (int)local_9a8) {
LAB_0076ecbb:
      puVar1 = &uStack_45;
      do {
        local_9b8 = puVar1;
        puVar1 = (undefined4 *)((int)local_9b8 + 1);
      } while (*(char *)((int)local_9b8 + 1) != '\0');
      *(undefined4 *)((int)local_9b8 + 1) = 0x7365642e;
      *(undefined1 *)((int)local_9b8 + 5) = 0;
      local_9b0 = FUN_00481a60((int)&uStack_45 + 1);
      if (0x960 < local_9b0) {
        local_9b0 = 0x960;
      }
      _Src = (void *)FUN_00481af0((int)&uStack_45 + 1);
      if (_Src == (void *)0x0) {
        basic_string<>(&DAT_008a1ad8);
        local_8 = 0xffffffff;
        ~basic_string<>();
      }
      else {
        memcpy(local_9a4,_Src,local_9b0);
        if (0x95f < local_9b0) {
          ___report_rangecheckfailure();
        }
        local_9a4[local_9b0] = 0;
        FUN_00481990((int)&uStack_45 + 1);
        FUN_00481ea0((int)&uStack_45 + 1);
        basic_string<>(local_9a4);
        local_8 = 0xffffffff;
        ~basic_string<>();
      }
      ExceptionList = local_10;
      FUN_0083e885();
      return;
    }
    puVar3 = (undefined1 *)FUN_00766f30(local_9a8);
    *(undefined1 *)((int)&uStack_45 + local_9a8 + 1) = *puVar3;
    pcVar4 = (char *)FUN_00766f30(local_9a8);
    if (*pcVar4 == '.') {
      if (0x2f < local_9a8) {
        ___report_rangecheckfailure();
      }
      *(undefined1 *)((int)&uStack_45 + local_9a8 + 1) = 0;
      goto LAB_0076ecbb;
    }
    local_9a8 = local_9a8 + 1;
  } while( true );
}

