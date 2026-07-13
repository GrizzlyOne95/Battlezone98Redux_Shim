
void FUN_006d62e0(void)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 in_stack_0000002c;
  undefined1 *puVar6;
  undefined1 local_98 [16];
  undefined1 local_88 [8];
  undefined1 local_80 [8];
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00853530;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 2;
  local_14 = uVar2;
  FUN_006d8cc0(0x3e3,0);
  cVar1 = FUN_006ab920(in_stack_0000002c,local_80,uVar2);
  if (cVar1 == '\0') {
    puVar6 = local_98;
    FUN_00421ec0(puVar6);
    puVar3 = (undefined4 *)FUN_006d7120(puVar6);
    cVar1 = FUN_006de530(*puVar3,puVar3[1]);
    if (cVar1 == '\0') {
      FUN_00421ec0();
      FUN_006d70d0();
      iVar4 = FUN_00667170();
      if (iVar4 == 0) {
        cVar1 = FUN_006d4590(0x400);
        if (cVar1 != '\0') {
          puVar6 = local_2c;
          FUN_00421ec0(puVar6);
          local_78 = FUN_006d7550(puVar6);
          local_8._0_1_ = 3;
          local_74 = local_78;
          local_6c = FUN_006dd7f0(local_44,"Async connect to ",local_78);
          local_8._0_1_ = 4;
          local_68 = local_6c;
          local_70 = FUN_0045f170(local_5c,local_6c," successful.");
          local_8._0_1_ = 5;
          local_64 = local_70;
          FUN_006d4480(0x400,local_70);
          local_8._0_1_ = 4;
          ~basic_string<>();
          local_8._0_1_ = 3;
          ~basic_string<>();
          local_8 = CONCAT31(local_8._1_3_,2);
          ~basic_string<>();
        }
        uVar5 = FUN_006ab750();
        FUN_006cadd0(uVar5);
        local_8._0_1_ = 1;
        FUN_006ca8c0();
        local_8 = (uint)local_8._1_3_ << 8;
        FUN_006ca8c0();
        local_8 = 0xffffffff;
        std::function<void___cdecl(void)>::~function<void___cdecl(void)>
                  ((function<void___cdecl(void)> *)&stack0x00000014);
      }
      else {
        FUN_006de570(4,"asio async_connect",in_stack_0000002c);
        uVar5 = make_error_code(local_88,3);
        FUN_006cadd0(uVar5);
        local_8._0_1_ = 1;
        FUN_006ca8c0();
        local_8 = (uint)local_8._1_3_ << 8;
        FUN_006ca8c0();
        local_8 = 0xffffffff;
        std::function<void___cdecl(void)>::~function<void___cdecl(void)>
                  ((function<void___cdecl(void)> *)&stack0x00000014);
      }
      goto LAB_006d650e;
    }
  }
  FUN_006d08b0(0x400,"async_connect cancelled");
  local_8._0_1_ = 1;
  FUN_006ca8c0();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006ca8c0();
  local_8 = 0xffffffff;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x00000014);
LAB_006d650e:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

