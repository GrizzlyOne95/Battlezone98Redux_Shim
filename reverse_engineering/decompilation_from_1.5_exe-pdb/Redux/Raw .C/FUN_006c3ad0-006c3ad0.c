
void FUN_006c3ad0(void)

{
  char cVar1;
  int iVar2;
  undefined4 uStack_a4;
  char *pcStack_a0;
  char *pcStack_9c;
  uint uStack_98;
  undefined1 *local_94;
  undefined4 local_90;
  undefined1 local_8c [8];
  undefined4 local_84;
  undefined4 local_80;
  int local_7c;
  int local_78;
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00851dd0;
  local_10 = ExceptionList;
  uStack_98 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  pcStack_9c = (char *)0x6c3b06;
  local_14 = uStack_98;
  cVar1 = FUN_006c3aa0();
  if (cVar1 != '\0') {
    pcStack_9c = (char *)0x6c3b16;
    local_7c = FUN_00822e60();
    if (45000 < local_7c - *(int *)(local_78 + 800)) {
      pcStack_9c = (char *)0x6c3b3f;
      cVar1 = FUN_006ab7d0();
      if ((cVar1 != '\0') && (*(char *)(local_78 + 0x31c) == '\0')) {
        *(int *)(local_78 + 800) = local_7c;
        pcStack_9c = (char *)0x6c3b73;
        FUN_006ab750();
        pcStack_9c = "";
        pcStack_a0 = (char *)0x6c3b80;
        basic_string<>();
        local_8 = 0;
        pcStack_9c = local_8c;
        pcStack_a0 = local_5c;
        uStack_a4 = 0x6c3ba0;
        FUN_00421ec0();
        uStack_a4 = 0x6c3ba7;
        FUN_006da770();
        local_8 = 0xffffffff;
        pcStack_9c = (char *)0x6c3bb6;
        ~basic_string<>();
        pcStack_9c = (char *)0x6c3bc1;
        cVar1 = FUN_006ab7d0();
        if (cVar1 != '\0') {
          pcStack_9c = local_74;
          pcStack_a0 = (char *)0x6c3bdb;
          local_84 = FUN_006ab780();
          local_8 = 1;
          pcStack_9c = (char *)0x6c3bf3;
          local_80 = local_84;
          pcStack_9c = (char *)FUN_0041f870();
          pcStack_a0 = "BZRNet Web Failed to ping webserver with error: %s\n";
          uStack_a4 = 0x6c3bfe;
          FUN_007d6a70();
          local_8 = 0xffffffff;
          pcStack_9c = (char *)0x6c3c10;
          ~basic_string<>();
          pcStack_9c = "";
          pcStack_a0 = (undefined1 *)0x6c3c1d;
          basic_string<>();
          local_8 = 2;
          pcStack_9c = local_44;
          local_94 = (undefined1 *)&uStack_a4;
          local_90 = shared_ptr<>(local_78 + 0x2e0);
          FUN_006c30f0();
          local_8 = 0xffffffff;
          pcStack_9c = (char *)0x6c3c5f;
          ~basic_string<>();
        }
      }
    }
    pcStack_9c = (char *)0x6c3c6d;
    cVar1 = FUN_006ab7d0();
    if (((cVar1 != '\0') && (*(char *)(local_78 + 0x2d8) != '\0')) &&
       (*(int *)(local_78 + 0x2dc) < local_7c)) {
      pcStack_9c = (char *)0x6c3c95;
      iVar2 = FUN_00434160();
      if (iVar2 != 2) {
        pcStack_9c = (char *)0x6c3c9f;
        iVar2 = FUN_00572a70();
        if (iVar2 != 0) goto LAB_006c3cf2;
      }
      pcStack_9c = "Leaving shutdown server";
      pcStack_a0 = (char *)0x6c3cb0;
      basic_string<>();
      local_8 = 3;
      pcStack_9c = local_2c;
      pcStack_a0 = (undefined1 *)0xbb8;
      uStack_a4 = 0x6c3cce;
      FUN_00421ec0();
      uStack_a4 = 0x6c3cd5;
      FUN_006dae30();
      local_8 = 0xffffffff;
      pcStack_9c = (char *)0x6c3ce4;
      ~basic_string<>();
      pcStack_9c = (char *)0x6c3cf2;
      std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
                ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)(local_78 + 0x2e0));
    }
  }
LAB_006c3cf2:
  pcStack_9c = (char *)0x6c3cfd;
  FUN_006ae160();
  pcStack_9c = (char *)0x6c3d0b;
  FUN_0074d110();
  ExceptionList = local_10;
  uStack_98 = 0x6c3d20;
  FUN_0083e885();
  return;
}

