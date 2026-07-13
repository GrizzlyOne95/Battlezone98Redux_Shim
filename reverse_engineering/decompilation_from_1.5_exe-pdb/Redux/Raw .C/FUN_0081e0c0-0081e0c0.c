
/* WARNING: Removing unreachable block (ram,0x0081e125) */

void FUN_0081e0c0(char *param_1)

{
  char cVar1;
  uint uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  int iVar3;
  char *local_7e0;
  char local_7d8;
  undefined1 auStack_7d7 [1998];
  undefined1 uStack_9;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  _vsnprintf(&local_7d8,2000,param_1,&stack0x00000008);
  uStack_9 = 0;
  uVar2 = FUN_0081e820();
  this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
  local_7e0 = &local_7d8;
  do {
    cVar1 = *local_7e0;
    local_7e0 = local_7e0 + 1;
  } while (cVar1 != '\0');
  iVar3 = (int)local_7e0 - (int)auStack_7d7;
  std::basic_ostream<char,struct_std::char_traits<char>_>::write
            (this,&local_7d8,(ulonglong)uVar2 << 0x20);
  std::basic_ostream<char,struct_std::char_traits<char>_>::flush(this);
  FUN_0083e885(uVar2,iVar3);
  return;
}

