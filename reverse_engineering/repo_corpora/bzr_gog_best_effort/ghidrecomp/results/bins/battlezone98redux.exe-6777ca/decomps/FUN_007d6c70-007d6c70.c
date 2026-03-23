
void FUN_007d6c70(char *param_1)

{
  char cVar1;
  undefined2 uVar2;
  int iVar3;
  undefined4 uVar4;
  char *local_410;
  char local_408;
  undefined1 auStack_407 [1023];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  _vsnprintf(&local_408,0x400,param_1,&stack0x00000008);
  uVar4 = 0;
  FUN_007d6260(&local_408);
  uVar2 = FUN_007d62a0();
  FUN_007d62e0(4);
  local_410 = &local_408;
  do {
    cVar1 = *local_410;
    local_410 = local_410 + 1;
  } while (cVar1 != '\0');
  iVar3 = (int)local_410 - (int)auStack_407;
  FUN_007d6270(&local_408,iVar3,auStack_407,iVar3,uVar4);
  FUN_007d62e0(uVar2);
  FUN_0081e1e0(&local_408);
  FUN_0083e885();
  return;
}

