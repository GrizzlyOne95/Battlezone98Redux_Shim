
void FUN_007205f0(undefined4 *param_1)

{
  undefined4 uVar1;
  char cVar2;
  bool bVar3;
  undefined4 *puVar4;
  int iVar5;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  char *pcStack_174;
  undefined1 auStack_158 [160];
  char local_b8 [8];
  char local_b0 [16];
  char local_a0 [8];
  error_condition local_98 [8];
  undefined1 *local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined1 *local_6c;
  undefined4 local_68;
  undefined4 local_64;
  int local_60;
  undefined1 local_44 [48];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00858bab;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  pcStack_174 = (char *)0x400;
  FUN_006d08b0();
  local_68 = *param_1;
  local_64 = param_1[1];
  cVar2 = FUN_006ab7d0();
  if (cVar2 == '\0') {
    pcStack_174 = (char *)0x720669;
    FUN_006d1110();
    local_8 = 0;
    if (*(int *)(local_60 + 0xa20) == 0) {
      if (*(int *)(local_60 + 0xa24) != 6) {
        pcStack_174 = local_b0;
        puVar4 = (undefined4 *)make_error_code();
        local_68 = *puVar4;
        local_64 = puVar4[1];
      }
    }
    else {
      if (*(int *)(local_60 + 0xa20) == 3) {
        pcStack_174 = (char *)0x400;
        FUN_006d08b0();
        local_8 = 0xffffffff;
        FUN_006d1140();
        goto LAB_007209f2;
      }
      pcStack_174 = local_a0;
      puVar4 = (undefined4 *)make_error_code();
      local_68 = *puVar4;
      local_64 = puVar4[1];
    }
    local_8 = 0xffffffff;
    FUN_006d1140();
  }
  cVar2 = FUN_006ab7d0();
  if (cVar2 == '\0') {
    cVar2 = FUN_006ab7d0();
    if (cVar2 != '\0') {
      FUN_00421ec0();
      FUN_006d70d0();
      std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
                ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)(local_60 + 0x4a58));
    }
    iVar5 = FUN_006b8f30();
    if (iVar5 == 0x65) {
      FUN_00720a50();
      *(undefined4 *)(local_60 + 0xa24) = 7;
      *(undefined4 *)(local_60 + 0xa20) = 1;
      cVar2 = FUN_006caba0();
      if (cVar2 != '\0') {
        local_90 = (undefined1 *)&pcStack_174;
        local_8c = shared_ptr<>(local_60 + 0x918);
        FUN_006e6250();
      }
      pcStack_174 = (char *)0x7209e9;
      pcStack_174 = (char *)FUN_006ab750();
      FUN_007099f0();
    }
    else {
      if (*(char *)(local_60 + 0x4c30) == '\0') {
        pcStack_174 = (char *)0x3;
        FUN_00574400();
        local_8 = 1;
        if (&stack0x00000000 == (undefined1 *)0x168) {
          local_6c = (undefined1 *)0x0;
        }
        else {
          local_6c = auStack_158;
        }
        iVar5 = FUN_006b8f30();
        pcStack_174 = "Handshake ended with HTTP error: ";
        this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(local_6c);
        pcStack_174 = (char *)0x720848;
        std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,iVar5);
        pcStack_174 = (char *)0x720857;
        local_84 = GetPolicy();
        local_8._0_1_ = 2;
        pcStack_174 = (char *)0x10;
        local_80 = local_84;
        FUN_006d46a0();
        local_8 = CONCAT31(local_8._1_3_,1);
        ~basic_string<>();
        local_8 = 0xffffffff;
        FUN_00417f10();
      }
      else {
        FUN_00727920();
        cVar2 = FUN_006ab7d0();
        if (cVar2 != '\0') {
          pcStack_174 = (char *)0x7208ca;
          local_78 = FUN_006ab780();
          local_8 = 3;
          pcStack_174 = "got to writing HTTP results with m_ec set: ";
          local_74 = local_78;
          local_88 = FUN_006dd7f0(local_44);
          local_8._0_1_ = 4;
          pcStack_174 = (char *)0x400;
          local_7c = local_88;
          FUN_006d4480();
          local_8 = CONCAT31(local_8._1_3_,3);
          ~basic_string<>();
          local_8 = 0xffffffff;
          ~basic_string<>();
        }
        pcStack_174 = local_b8;
        puVar4 = (undefined4 *)make_error_code();
        uVar1 = puVar4[1];
        *(undefined4 *)(local_60 + 0x4c28) = *puVar4;
        *(undefined4 *)(local_60 + 0x4c2c) = uVar1;
      }
      pcStack_174 = (char *)0x72096b;
      FUN_006daf10();
    }
  }
  else {
    pcStack_174 = (char *)0x720727;
    FUN_006de390();
    pcStack_174 = (char *)0x720736;
    bVar3 = std::error_condition::operator==((error_condition *)&local_68,local_98);
    if ((bVar3) && (*(int *)(local_60 + 0xa20) == 3)) {
      pcStack_174 = (char *)0x400;
      FUN_006d08b0();
    }
    else {
      pcStack_174 = "handle_write_http_response";
      FUN_006f90a0(0x10);
      pcStack_174 = (char *)0x720785;
      FUN_006daf10();
    }
  }
LAB_007209f2:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

