
void __fastcall
FUN_0048bc30(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_1)

{
  char cVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00849210;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  while( true ) {
    cVar1 = operator!=<>(&stack0x00000004,&stack0x0000000c);
    if (cVar1 == '\0') break;
    cVar1 = std::istreambuf_iterator<char,struct_std::char_traits<char>_>::operator*
                      ((istreambuf_iterator<char,struct_std::char_traits<char>_> *)&stack0x00000004)
    ;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
              (param_1,1,cVar1);
    FUN_0048ab00();
  }
  FUN_0048bcc4();
  return;
}

