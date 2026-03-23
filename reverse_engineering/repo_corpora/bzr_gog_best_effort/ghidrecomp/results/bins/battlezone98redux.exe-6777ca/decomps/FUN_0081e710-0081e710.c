
/* WARNING: Removing unreachable block (ram,0x0081e775) */

void FUN_0081e710(int param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  undefined1 *puVar3;
  char *local_7e0;
  char local_7d8;
  undefined1 auStack_7d7 [1998];
  undefined1 uStack_9;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  _vsnprintf(&local_7d8,2000,param_2,&stack0x0000000c);
  uStack_9 = 0;
  FUN_0081e660();
  local_7e0 = &local_7d8;
  puVar3 = auStack_7d7;
  do {
    cVar1 = *local_7e0;
    local_7e0 = local_7e0 + 1;
  } while (cVar1 != '\0');
  iVar2 = (int)local_7e0 - (int)puVar3;
  std::basic_ostream<char,struct_std::char_traits<char>_>::write
            ((basic_ostream<char,struct_std::char_traits<char>_> *)(param_1 + 0x10),&local_7d8,
             ZEXT48(puVar3) << 0x20);
  std::basic_ostream<char,struct_std::char_traits<char>_>::flush
            ((basic_ostream<char,struct_std::char_traits<char>_> *)(param_1 + 0x10));
  FUN_0083e885(puVar3,iVar2);
  return;
}

