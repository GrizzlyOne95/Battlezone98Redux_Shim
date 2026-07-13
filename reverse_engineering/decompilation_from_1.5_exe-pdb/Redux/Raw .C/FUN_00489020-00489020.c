
basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *
FUN_00489020(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_1)

{
  char cVar1;
  int iVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_48 [12];
  undefined4 uStack_3c;
  undefined1 *puStack_38;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00849088;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  puStack_38 = &stack0x00000008;
  uStack_3c = 0x489061;
  cVar1 = FUN_00427310();
  if (cVar1 == '\0') {
    puStack_38 = &stack0x00000008;
    uStack_3c = 0x4890a6;
    cVar1 = FUN_00427310();
    if (cVar1 == '\0') {
      puStack_38 = &stack0x00000008;
      uStack_3c = 0x4890eb;
      cVar1 = FUN_00427310();
      if (cVar1 == '\0') {
        puStack_38 = &stack0x00000008;
        uStack_3c = 0x489130;
        cVar1 = FUN_00427310();
        if (cVar1 == '\0') {
          puStack_38 = &stack0x00000008;
          uStack_3c = 0x489175;
          cVar1 = FUN_00427310();
          if (cVar1 == '\0') {
            std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                      (abStack_48,
                       (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                        *)&stack0x00000008);
            FUN_00488ec0();
            std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                      ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                        *)&stack0xffffffb4,
                       (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                        *)&stack0x00000008);
            iVar2 = FUN_004880e0();
            puStack_38 = (undefined1 *)0x4891fb;
            std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                      (param_1,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                *)(iVar2 + 0x30));
            local_8 = 0xffffffff;
            ~basic_string<>();
          }
          else {
            puStack_38 = (undefined1 *)0x48918c;
            basic_string<>();
            local_8 = 0xffffffff;
            ~basic_string<>();
          }
        }
        else {
          puStack_38 = (undefined1 *)0x489147;
          basic_string<>();
          local_8 = 0xffffffff;
          ~basic_string<>();
        }
      }
      else {
        puStack_38 = (undefined1 *)0x489102;
        basic_string<>();
        local_8 = 0xffffffff;
        ~basic_string<>();
      }
    }
    else {
      puStack_38 = (undefined1 *)0x4890bd;
      basic_string<>();
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
  }
  else {
    puStack_38 = (undefined1 *)0x489078;
    basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  return param_1;
}

