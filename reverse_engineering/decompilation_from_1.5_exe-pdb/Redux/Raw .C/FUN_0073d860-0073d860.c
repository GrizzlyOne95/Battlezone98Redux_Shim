
void FUN_0073d860(char param_1)

{
  char cVar1;
  int iVar2;
  undefined8 uVar3;
  undefined1 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined1 auStack_17c [160];
  undefined1 local_dc [16];
  undefined4 local_cc;
  undefined4 local_c8;
  undefined8 *local_c4;
  undefined1 local_c0 [4];
  undefined1 *local_bc;
  int local_b8;
  int local_b4;
  uint local_b0;
  char local_a9;
  int local_a8;
  char *local_a4;
  undefined1 local_a0 [4];
  int *local_9c;
  undefined1 local_98 [24];
  undefined1 local_80 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_68 [24];
  undefined1 local_50 [24];
  undefined1 local_38 [24];
  undefined1 local_20;
  undefined1 local_1f;
  undefined8 local_1e;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085ac56;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_a8 = FUN_0056f900(local_14);
  if ((local_a8 != 0) && (local_b4 = FUN_007659f0(), local_b4 != 0)) {
    FUN_0042d8c0(local_a0);
    FID_conflict_begin(local_c0);
    local_c4 = &local_1e;
    uVar3 = FUN_0056f760(0);
    *local_c4 = uVar3;
    local_20 = 1;
    local_1f = 1;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_68,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)(local_a8 + 0x30));
    local_8 = 0;
    FUN_00745480(0);
    (**(code **)(*local_9c + 0x38))(local_dc);
    while (cVar1 = FUN_00420f10(local_c0), cVar1 != '\0') {
      if (param_1 != '\0') {
        uVar6 = 0;
        uVar5 = 10;
        puVar4 = &local_20;
        iVar2 = FUN_0042da60(puVar4,10,0);
        FUN_00759710(iVar2 + 8,puVar4,uVar5,uVar6);
      }
      local_b8 = -1;
      basic_string<>(&DAT_008757b0);
      local_8._0_1_ = 1;
      iVar2 = FUN_0042da60(local_50);
      local_a4 = (char *)(**(code **)(*local_9c + 0x28))(local_a8 + 0x10,iVar2 + 8);
      local_8 = (uint)local_8._1_3_ << 8;
      ~basic_string<>();
      if ((local_a4 != (char *)0x0) && (*local_a4 != '\0')) {
        local_b8 = atoi(local_a4);
      }
      local_b0 = 0;
      basic_string<>("miniid");
      local_8._0_1_ = 2;
      iVar2 = FUN_0042da60(local_80);
      local_a4 = (char *)(**(code **)(*local_9c + 0x28))(local_a8 + 0x10,iVar2 + 8);
      local_8 = (uint)local_8._1_3_ << 8;
      ~basic_string<>();
      if ((local_a4 != (char *)0x0) && (*local_a4 != '\0')) {
        local_b0 = atoi(local_a4);
      }
      iVar2 = FUN_0042da60();
      if ((((*(int *)(iVar2 + 0x80) == local_b8) &&
           (iVar2 = FUN_0042da60(), *(ushort *)(iVar2 + 0x28) == local_b0)) &&
          (iVar2 = FUN_0042da60(), 0 < *(int *)(iVar2 + 0x80))) &&
         (iVar2 = FUN_0042da60(), *(short *)(iVar2 + 0x28) != 0)) {
        puVar4 = local_dc;
        FUN_0042da60(puVar4);
        cVar1 = FUN_0073ba10(puVar4);
        if (cVar1 != '\0') {
          basic_string<>("knownPlayers");
          local_8._0_1_ = 3;
          iVar2 = FUN_0042da60(local_38);
          local_a4 = (char *)(**(code **)(*local_9c + 0x28))(local_a8 + 0x10,iVar2 + 8);
          local_8 = (uint)local_8._1_3_ << 8;
          ~basic_string<>();
          if ((local_a4 == (char *)0x0) ||
             (cVar1 = operator!=<>(local_a8 + 0x30,local_a4), cVar1 != '\0')) {
            FUN_00574400(3,1);
            local_8._0_1_ = 4;
            if (&stack0x00000000 == (undefined1 *)0x18c) {
              local_bc = (undefined1 *)0x0;
            }
            else {
              local_bc = auStack_17c;
            }
            iVar2 = FUN_0042da60();
            uVar5 = FUN_004bc590(local_bc,PTR_DAT_008eda34,&DAT_0089abd4,PTR_DAT_008eda34,iVar2 + 8)
            ;
            uVar5 = FUN_004bc590(uVar5);
            uVar5 = FUN_004bc590(uVar5);
            FUN_0073ba70(uVar5);
            local_cc = GetPolicy(local_98);
            local_8._0_1_ = 5;
            local_c8 = local_cc;
            local_a9 = FUN_007458a0(local_cc);
            local_8 = CONCAT31(local_8._1_3_,4);
            ~basic_string<>();
            if (local_a9 != '\0') {
              FUN_007476a0();
            }
            local_8 = local_8 & 0xffffff00;
            FUN_00417f10();
          }
        }
      }
      else {
        uVar5 = FUN_0042de50();
        FUN_007467b0(uVar5);
      }
      FUN_0042da80();
    }
    cVar1 = operator!=<>(local_68,local_a8 + 0x30);
    if (cVar1 != '\0') {
      FUN_007476a0();
    }
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

