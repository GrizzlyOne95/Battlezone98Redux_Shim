
void __fastcall
FUN_00731270(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_1)

{
  char cVar1;
  char *pcVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00859d68;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 1;
  FUN_004bbb20();
  local_8._0_1_ = 2;
  FUN_004bbb20(&stack0x00000004);
  local_8._0_1_ = 1;
  _Distance<>();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::reserve
            (param_1,0);
  local_8 = CONCAT31(local_8._1_3_,3);
  while( true ) {
    cVar1 = FID_conflict_operator__();
    if (cVar1 == '\0') break;
    pcVar2 = (char *)FUN_007270b0();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
              (param_1,1,*pcVar2);
    FUN_00732df0();
  }
  FUN_0073135b();
  return;
}

