
SOCKET FUN_006af3f0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  char local_c [4];
  SOCKET local_8;
  
  FUN_006ae8d0();
  puVar2 = param_4;
  uVar1 = WSASocketW(param_1,param_2,param_3,0,0,1);
  local_8 = FUN_006d8d90(uVar1,puVar2);
  if (local_8 != 0xffffffff) {
    if (param_1 == 0x17) {
      local_c[0] = '\0';
      local_c[1] = '\0';
      local_c[2] = '\0';
      local_c[3] = '\0';
      setsockopt(local_8,0x29,0x1b,local_c,4);
    }
    puVar2 = (undefined4 *)FUN_004fbb60();
    uVar1 = puVar2[1];
    *param_4 = *puVar2;
    param_4[1] = uVar1;
  }
  return local_8;
}

