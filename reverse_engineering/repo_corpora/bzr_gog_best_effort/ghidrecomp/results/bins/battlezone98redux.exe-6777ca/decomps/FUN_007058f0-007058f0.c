
void FUN_007058f0(undefined4 param_1,
                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                 *param_2)

{
  undefined4 uVar1;
  undefined4 extraout_var;
  undefined1 local_34 [24];
  undefined1 local_1c [20];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::assign
            (param_2,"258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
  uVar1 = FUN_004170c0(local_1c,extraout_var);
  uVar1 = FUN_0041f870(uVar1);
  FUN_006bdbf0(uVar1);
  uVar1 = FUN_006bac90(local_34,local_1c,0x14);
  FUN_0045e0f0(uVar1);
  ~basic_string<>();
  FUN_006ab750();
  FUN_0083e885();
  return;
}

