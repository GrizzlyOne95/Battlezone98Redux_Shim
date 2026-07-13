
void FUN_004ff640(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  char local_118 [256];
  char local_18 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar1 = FUN_0082d377(param_1,0xffffffff,0);
  local_18[0] = '\0';
  local_18[1] = '\0';
  local_18[2] = '\0';
  local_18[3] = '\0';
  local_18[4] = '\0';
  local_18[5] = '\0';
  local_18[6] = '\0';
  local_18[7] = '\0';
  local_18[8] = '\0';
  local_18[9] = '\0';
  local_18[10] = '\0';
  local_18[0xb] = '\0';
  local_18[0xc] = '\0';
  local_18[0xd] = '\0';
  local_18[0xe] = '\0';
  local_18[0xf] = '\0';
  sprintf(local_18,"%.11s.lua",uVar1);
  iVar2 = FUN_00481f10(local_18);
  if (iVar2 == 0) {
    _snprintf(local_118,0x100,"\n\tno asset \'%s\'",local_18);
    FUN_0082cd77(param_1,local_118);
  }
  else {
    uVar1 = FUN_00481af0(local_18);
    uVar3 = FUN_00481a60(local_18,uVar1);
    uVar1 = FUN_0082be6f(param_1,uVar1,uVar3,local_18,param_1,"Lua package load error:\n%s");
    FUN_004ff600(uVar1);
    FUN_00481990(local_18);
  }
  FUN_0083e885();
  return;
}

