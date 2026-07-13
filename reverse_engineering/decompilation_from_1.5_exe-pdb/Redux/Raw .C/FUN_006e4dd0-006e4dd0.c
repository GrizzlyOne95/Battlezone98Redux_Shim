
void FUN_006e4dd0(void)

{
  undefined4 uVar1;
  char cVar2;
  bool bVar3;
  uint uVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 *in_stack_00000024;
  undefined1 *puVar7;
  undefined1 local_44 [8];
  undefined1 local_3c [8];
  error_condition local_34 [8];
  undefined1 local_2c [8];
  undefined1 local_24 [8];
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_008542b0;
  local_10 = ExceptionList;
  uVar4 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 1;
  FUN_006d8cc0(0x3e3,0);
  cVar2 = FUN_006ab920(in_stack_00000024,local_24,uVar4);
  if (cVar2 == '\0') {
    puVar7 = local_3c;
    FUN_00421ec0(puVar7);
    puVar5 = (undefined4 *)FUN_006d7120(puVar7);
    cVar2 = FUN_006de530(*puVar5,puVar5[1]);
    if (cVar2 == '\0') {
      FUN_00421ec0();
      FUN_006d70d0();
      FUN_006ab750();
      iVar6 = FUN_00667170();
      if (iVar6 == 0) {
        cVar2 = FUN_006d4590(0x400);
        if (cVar2 != '\0') {
          FUN_006d08b0(0x400,"asio con handle_async_shutdown");
        }
      }
      else {
        FUN_006d8cc0(0x2749,0);
        cVar2 = FUN_006ab920(in_stack_00000024,local_2c);
        if (cVar2 == '\0') {
          puVar5 = (undefined4 *)FUN_006f1850(local_44,*in_stack_00000024,in_stack_00000024[1]);
          local_1c = *puVar5;
          local_18 = puVar5[1];
          uVar1 = in_stack_00000024[1];
          *(undefined4 *)(local_14 + 0x84) = *in_stack_00000024;
          *(undefined4 *)(local_14 + 0x88) = uVar1;
          FUN_006de390(8);
          bVar3 = std::error_condition::operator==((error_condition *)&local_1c,local_34);
          if (!bVar3) {
            FUN_006dee50(4,"asio async_shutdown",in_stack_00000024);
          }
        }
      }
      FUN_006cadd0(&local_1c);
      local_8 = local_8 & 0xffffff00;
      FUN_006ca8c0();
      local_8 = 0xffffffff;
      std::function<void___cdecl(void)>::~function<void___cdecl(void)>
                ((function<void___cdecl(void)> *)&stack0x0000000c);
      ExceptionList = local_10;
      return;
    }
  }
  FUN_006d08b0(0x400,"async_shutdown cancelled");
  local_8 = local_8 & 0xffffff00;
  FUN_006ca8c0();
  local_8 = 0xffffffff;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x0000000c);
  ExceptionList = local_10;
  return;
}

