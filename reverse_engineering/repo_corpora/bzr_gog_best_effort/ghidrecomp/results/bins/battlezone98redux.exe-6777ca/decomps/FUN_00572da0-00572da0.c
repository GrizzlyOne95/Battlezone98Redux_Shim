
void FUN_00572da0(char *param_1)

{
  char cVar1;
  char *local_11c;
  undefined2 local_114;
  char local_112;
  undefined1 auStack_111 [265];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_11c = &local_112;
  local_114 = 0x4350;
  _vsnprintf(local_11c,0x10a,param_1,&stack0x00000008);
  do {
    cVar1 = *local_11c;
    local_11c = local_11c + 1;
  } while (cVar1 != '\0');
  FUN_00575890(&local_114,local_11c + (3 - (int)auStack_111),1,1);
  FUN_0083e885();
  return;
}

