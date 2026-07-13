
void __thiscall FUN_00765de0(undefined1 *param_1,int *param_2,char param_3)

{
  undefined4 uVar1;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar2;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar3;
  int iVar4;
  code *pcVar5;
  undefined1 auStack_6e4 [176];
  undefined1 auStack_634 [176];
  undefined1 auStack_584 [176];
  undefined1 auStack_4d4 [160];
  undefined4 local_434;
  undefined1 *local_430;
  undefined4 *local_42c;
  int *local_428;
  undefined1 *local_424;
  undefined1 *local_420;
  undefined1 *local_41c;
  undefined1 *local_418;
  undefined1 local_414 [1024];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085d19c;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_41c = param_1;
  if (param_3 == '\0') {
    *param_1 = 0;
    if (*param_2 == 1) {
      local_428 = (int *)FUN_006aa1b0(local_14);
      (**(code **)(*local_428 + 0x54))(local_414,0x400,&local_434);
      local_42c = (undefined4 *)FUN_006aa1d0();
      uVar1 = (**(code **)*local_42c)();
      FUN_00764b30(local_414,local_434,uVar1);
    }
    else if (*param_2 == 0x19) {
      FUN_00574400(3,1);
      local_8 = 0;
      if (&stack0x00000000 == (undefined1 *)0x6f4) {
        local_430 = (undefined1 *)0x0;
      }
      else {
        local_430 = auStack_6e4;
      }
      pcVar5 = FUN_004bc8c0;
      pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)
               FUN_004bc590(local_430,
                            "Calling RequestEncryptedAppTicket more than once per minute returns this error : k_EResultLimitExceeded"
                           );
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pcVar5);
      pbVar3 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
      FUN_0081e820();
      pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pbVar3);
      local_8 = 0xffffffff;
      FUN_00417f10();
    }
    else if (*param_2 == 0x1d) {
      FUN_00574400(3,1);
      local_8 = 1;
      if (&stack0x00000000 == (undefined1 *)0x644) {
        local_424 = (undefined1 *)0x0;
      }
      else {
        local_424 = auStack_634;
      }
      pcVar5 = FUN_004bc8c0;
      pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)
               FUN_004bc590(local_424,
                            "Calling RequestEncryptedAppTicket while there is already a pending request results in this error : k_EResultDuplicateRequest"
                           );
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pcVar5);
      pbVar3 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
      FUN_0081e820();
      pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pbVar3);
      local_8 = 0xffffffff;
      FUN_00417f10();
    }
    else if (*param_2 == 3) {
      *param_1 = 1;
      FUN_00574400(3,1);
      local_8 = 2;
      if (&stack0x00000000 == (undefined1 *)0x4e4) {
        local_420 = (undefined1 *)0x0;
      }
      else {
        local_420 = auStack_4d4;
      }
      pcVar5 = FUN_004bc8c0;
      pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)
               FUN_004bc590(local_420,
                            "Calling RequestEncryptedAppTicket while not connected to steam results in this error : k_EResultNoConnection"
                           );
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pcVar5);
      pbVar3 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
      FUN_0081e820();
      pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pbVar3);
      local_8 = 0xffffffff;
      FUN_00417f10();
    }
    else {
      FUN_00574400(3,1);
      local_8 = 3;
      if (&stack0x00000000 == (undefined1 *)0x594) {
        local_418 = (undefined1 *)0x0;
      }
      else {
        local_418 = auStack_584;
      }
      pcVar5 = FUN_004bc8c0;
      iVar4 = *param_2;
      pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)
               FUN_004bc590(local_418,"Calling RequestEncryptedAppTicket failure type : ");
      pbVar2 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,iVar4);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pcVar5);
      pbVar3 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
      FUN_0081e820();
      pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pbVar3);
      local_8 = 0xffffffff;
      FUN_00417f10();
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

