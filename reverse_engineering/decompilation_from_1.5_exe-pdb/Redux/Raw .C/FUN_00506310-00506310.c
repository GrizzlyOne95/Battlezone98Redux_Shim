
/* WARNING: Removing unreachable block (ram,0x00506371) */

void FUN_00506310(undefined4 param_1)

{
  char cVar1;
  uint uVar2;
  char *_Source;
  int iVar3;
  undefined4 uVar4;
  undefined4 local_34;
  char *local_2c;
  char local_24;
  undefined1 auStack_23 [14];
  undefined1 uStack_15;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084aaa1;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  _Source = (char *)FUN_0082ba59(param_1,1,0,uVar2);
  strncpy(&local_24,_Source,0x10);
  uStack_15 = 0;
  iVar3 = FUN_00434140(&local_24,0x2e);
  if (iVar3 == 0) {
    local_2c = &local_24;
    do {
      cVar1 = *local_2c;
      local_2c = local_2c + 1;
    } while (cVar1 != '\0');
    strncat(&local_24,".odf",0x10 - ((int)local_2c - (int)auStack_23));
  }
  uVar4 = FUN_0082cac6(param_1,4);
  iVar3 = forward<>(4,uVar4);
  local_8 = 0;
  if (iVar3 == 0) {
    local_34 = 0;
  }
  else {
    local_34 = FUN_00589430(&local_24);
  }
  local_8 = 0xffffffff;
  FUN_0082c82c(param_1,0xffffd8f0,"ParameterDB",uVar2,local_34);
  FUN_0082d16f(param_1,0xfffffffe);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

