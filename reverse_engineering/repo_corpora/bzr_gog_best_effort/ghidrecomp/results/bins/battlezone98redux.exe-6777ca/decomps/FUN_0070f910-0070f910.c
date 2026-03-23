
void FUN_0070f910(void)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  byte *pbVar4;
  int in_stack_00000010;
  uint in_stack_00000014;
  uint local_8;
  
  local_8 = in_stack_00000014;
  while( true ) {
    local_8 = local_8 % 4;
    cVar3 = FID_conflict_operator__(&stack0x00000008);
    if (cVar3 == '\0') break;
    pbVar4 = (byte *)get();
    bVar1 = *pbVar4;
    bVar2 = *(byte *)(in_stack_00000010 + local_8);
    pbVar4 = (byte *)FUN_00421ec0();
    *pbVar4 = bVar1 ^ bVar2;
    local_8 = local_8 + 1;
    FUN_004f5330();
    std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
    operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *)
               &stack0x00000004);
  }
  return;
}

