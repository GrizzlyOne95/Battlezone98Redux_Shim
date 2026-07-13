
void FUN_00702920(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar4;
  undefined1 local_d4 [4];
  undefined1 local_d0 [4];
  undefined1 local_cc [4];
  undefined1 local_c8 [4];
  undefined1 local_c4 [8];
  undefined4 local_bc;
  undefined4 local_b4;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  uint local_94;
  char local_8f;
  char local_8e;
  char local_8d;
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00856a48;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_94 = 0;
  iVar2 = FUN_006b8f30(local_14);
  if (iVar2 != 0x65) {
    make_error_code(param_1,0x14);
    goto LAB_00702c4e;
  }
  basic_string<>("Upgrade");
  local_8 = 0;
  local_a0 = FUN_006b7490(local_8c);
  local_8 = 0xffffffff;
  ~basic_string<>();
  local_bc = FUN_006ab6b0();
  local_8 = 1;
  local_a8 = local_bc;
  uVar3 = FUN_004fee40(local_cc);
  FUN_0070f510(local_d4,local_a0,"websocket",9,local_a8,uVar3);
  local_8d = FID_conflict_operator__(uVar3);
  local_8 = 0xffffffff;
  FUN_00417b50();
  if (local_8d != '\0') {
    make_error_code(param_1,0x15);
    goto LAB_00702c4e;
  }
  basic_string<>("Connection");
  local_8 = 2;
  local_98 = FUN_006b7490(local_74);
  local_8 = 0xffffffff;
  ~basic_string<>();
  local_b4 = FUN_006ab6b0();
  local_8 = 3;
  local_a4 = local_b4;
  uVar3 = FUN_004fee40(local_d0);
  FUN_0070f510(local_c8,local_98,"upgrade",7,local_a4,uVar3);
  local_8f = FID_conflict_operator__(uVar3);
  local_8 = 0xffffffff;
  FUN_00417b50();
  if (local_8f != '\0') {
    make_error_code(param_1,0x15);
    goto LAB_00702c4e;
  }
  basic_string<>("Sec-WebSocket-Key");
  local_8 = 4;
  pbVar4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           FUN_006b7490(local_5c);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,pbVar4);
  local_8._0_1_ = 6;
  ~basic_string<>();
  FUN_007058f0(local_c4,local_2c);
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    basic_string<>("Sec-WebSocket-Accept");
    local_8 = CONCAT31(local_8._1_3_,7);
    local_94 = local_94 | 1;
    uVar3 = FUN_006b7490(local_44);
    cVar1 = operator!=<>(local_2c,uVar3);
    if (cVar1 != '\0') goto LAB_00702bd0;
    local_9c = 0;
  }
  else {
LAB_00702bd0:
    local_9c = 1;
  }
  local_8e = (char)local_9c;
  local_8 = 6;
  if ((local_94 & 1) != 0) {
    local_94 = local_94 & 0xfffffffe;
    ~basic_string<>();
  }
  if (local_8e == '\0') {
    FUN_006ab750();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  else {
    make_error_code(param_1,0x15);
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
LAB_00702c4e:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

