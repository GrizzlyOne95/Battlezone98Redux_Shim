
void __thiscall FUN_00701ce0(int param_1,undefined4 param_2)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_00856820;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 1;
  cVar1 = FUN_006ab7d0(uVar2);
  if (cVar1 != '\0') {
    cVar1 = FUN_006ab7d0(uVar2);
    if (cVar1 != '\0') {
      FUN_00421ec0();
      iVar3 = FUN_006cc050();
      if (iVar3 == 1) {
        FUN_00421ec0();
        uVar4 = FUN_006cc070();
        cVar1 = FUN_006bb9a0(uVar4);
        if (cVar1 == '\0') {
          make_error_code(param_2,5);
          local_8 = local_8 & 0xffffff00;
          FUN_006ca8c0();
          local_8 = 0xffffffff;
          FUN_006ca8c0();
        }
        else {
          uVar5 = basic_string<>(param_1 + 0xc,1);
          local_8._0_1_ = 2;
          FUN_00421ec0(uVar5);
          FUN_007051e0(uVar5);
          local_8._0_1_ = 1;
          ~basic_string<>();
          FUN_00421ec0(uVar4);
          FUN_00705200(uVar4);
          uVar4 = basic_string<>(param_1 + 0xd,1);
          local_8._0_1_ = 3;
          FUN_00421ec0(uVar4);
          FUN_006e1ac0(uVar4);
          local_8._0_1_ = 1;
          ~basic_string<>();
          uVar4 = 1;
          FUN_00421ec0(1);
          FUN_00705160(uVar4);
          FUN_006ab750();
          local_8 = (uint)local_8._1_3_ << 8;
          FUN_006ca8c0();
          local_8 = 0xffffffff;
          FUN_006ca8c0();
        }
      }
      else {
        make_error_code(param_2,7);
        local_8 = local_8 & 0xffffff00;
        FUN_006ca8c0();
        local_8 = 0xffffffff;
        FUN_006ca8c0();
      }
      goto LAB_00701ec0;
    }
  }
  make_error_code(param_2,6);
  local_8 = local_8 & 0xffffff00;
  FUN_006ca8c0();
  local_8 = 0xffffffff;
  FUN_006ca8c0();
LAB_00701ec0:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

