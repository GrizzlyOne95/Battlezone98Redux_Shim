
/* Library Function - Single Match
    public: char & __thiscall std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> >::front(void)
   
   Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release */

char * __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::front
          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this)

{
  uint uVar1;
  undefined1 local_2c [12];
  char *local_20;
  undefined4 local_1c;
  undefined4 local_18;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849ab8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = this;
  local_1c = FUN_004bb540(local_2c);
  local_8 = 0;
  local_18 = local_1c;
  local_20 = (char *)FUN_007270b0(uVar1);
  local_8 = 0xffffffff;
  FUN_004bb3b0();
  ExceptionList = local_10;
  return local_20;
}

