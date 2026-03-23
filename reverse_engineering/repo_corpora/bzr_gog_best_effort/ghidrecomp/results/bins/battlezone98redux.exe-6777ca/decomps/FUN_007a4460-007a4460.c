
void FUN_007a4460(undefined4 param_1)

{
  char cVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_44 [12];
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined1 *puStack_30;
  undefined4 local_2c;
  undefined1 *local_28;
  undefined4 local_24;
  undefined1 *local_20;
  undefined1 local_1c [4];
  undefined4 local_18;
  undefined4 local_14;
  undefined1 local_10 [4];
  int local_c;
  int local_8;
  
  local_c = 0;
  puStack_30 = local_10;
  uStack_34 = 0x7a447f;
  FID_conflict_begin();
  while( true ) {
    puStack_30 = local_1c;
    uStack_34 = 0x7a4498;
    puStack_30 = (undefined1 *)FID_conflict_end();
    uStack_34 = 0x7a44a1;
    cVar1 = FUN_007a45e0();
    if (cVar1 == '\0') {
      puStack_30 = (undefined1 *)local_c;
      uStack_34 = 0x7a4567;
      pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               FUN_006cf480();
      local_28 = abStack_44;
      local_2c = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           (abStack_44,pbVar2);
      FUN_00752a50();
      *(undefined4 *)(local_8 + 0x38) = 0xffffffff;
      puStack_30 = (undefined1 *)0x7a4598;
      FUN_007cb5c0();
      puStack_30 = (undefined1 *)0x7a45a0;
      FUN_007a4400();
      puStack_30 = (undefined1 *)0x7a45a8;
      FUN_007a4260();
      puStack_30 = (undefined1 *)0x7a45b0;
      cVar1 = FUN_0041f890();
      if (cVar1 == '\0') {
        puStack_30 = (undefined1 *)0x7a45c8;
        local_18 = FUN_0041f870();
      }
      else {
        local_18 = 0;
      }
      puStack_30 = (undefined1 *)local_18;
      uStack_34 = 0x7a45d7;
      FUN_007a3d80();
      return;
    }
    puStack_30 = (undefined1 *)0x7a44b4;
    puStack_30 = (undefined1 *)FUN_00421ec0();
    uStack_34 = param_1;
    uStack_38 = 0x7a44be;
    cVar1 = FUN_00427310();
    if (cVar1 != '\0') break;
    local_c = local_c + 1;
    puStack_30 = (undefined1 *)0x7a4489;
    FUN_0076fa50();
  }
  puStack_30 = (undefined1 *)local_c;
  uStack_34 = 0x7a44d8;
  pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           FUN_006cf480();
  local_20 = abStack_44;
  local_24 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       (abStack_44,pbVar2);
  FUN_00752a50();
  *(undefined4 *)(local_8 + 0x38) = 0xffffffff;
  puStack_30 = (undefined1 *)0x7a4509;
  FUN_007cb5c0();
  puStack_30 = (undefined1 *)0x7a4511;
  FUN_007a4400();
  puStack_30 = (undefined1 *)0x7a4519;
  FUN_007a4260();
  puStack_30 = (undefined1 *)0x7a4521;
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    puStack_30 = (undefined1 *)0x7a4539;
    local_14 = FUN_0041f870();
  }
  else {
    local_14 = 0;
  }
  puStack_30 = (undefined1 *)local_14;
  uStack_34 = 0x7a4548;
  FUN_007a3d80();
  return;
}

