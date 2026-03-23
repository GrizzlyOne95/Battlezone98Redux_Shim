
undefined4 FUN_00489b60(void)

{
  byte in_stack_0000001c;
  char *in_stack_00000020;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_58 [24];
  uint uStack_40;
  uint uStack_3c;
  char *local_38;
  undefined4 local_34;
  undefined1 *local_30;
  undefined4 local_2c;
  int local_28;
  int local_24;
  char *local_20;
  char *local_1c;
  int local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008490e8;
  local_10 = ExceptionList;
  uStack_3c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  uStack_40 = (uint)in_stack_0000001c;
  local_30 = abStack_58;
  local_34 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       (abStack_58,
                        (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)&stack0x00000004);
  local_28 = FUN_004880e0();
  local_18 = *(int *)(local_28 + 0x78) + -1;
  local_24 = local_28;
  switch(local_18) {
  case 0:
    builtin_strncpy(in_stack_00000020,"moon.txt",9);
    break;
  case 1:
    builtin_strncpy(in_stack_00000020,"mars.txt",9);
    break;
  case 2:
    builtin_strncpy(in_stack_00000020,"venus.txt",10);
    break;
  case 3:
    builtin_strncpy(in_stack_00000020,"io.txt",7);
    break;
  case 4:
    builtin_strncpy(in_stack_00000020,"europa.txt",0xb);
    break;
  case 5:
    builtin_strncpy(in_stack_00000020,"titan.txt",10);
    break;
  case 6:
    builtin_strncpy(in_stack_00000020,"achilles.txt",0xd);
    break;
  case 7:
    builtin_strncpy(in_stack_00000020,"ganymede.txt",0xd);
    break;
  case 8:
    builtin_strncpy(in_stack_00000020,"elysium.txt",0xc);
    break;
  default:
    uStack_40 = 0x489d31;
    local_20 = (char *)FUN_0041f870();
    local_1c = in_stack_00000020;
    local_38 = in_stack_00000020;
    do {
      local_11 = *local_20;
      *local_1c = local_11;
      local_20 = local_20 + 1;
      local_1c = local_1c + 1;
    } while (local_11 != '\0');
  }
  local_2c = 1;
  local_8 = 0xffffffff;
  uStack_40 = 0x489d7e;
  ~basic_string<>();
  ExceptionList = local_10;
  return local_2c;
}

