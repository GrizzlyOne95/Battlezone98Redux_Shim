
void FUN_0083524f(undefined4 param_1)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  int local_334;
  int local_330;
  char *local_32c;
  int local_328;
  undefined1 **local_324 [131];
  undefined1 *local_118;
  undefined1 *local_114;
  undefined4 local_110;
  undefined4 local_10c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_330 = 1;
  puVar1 = (undefined1 *)FUN_0082ba59(param_1,1,&local_334);
  local_32c = (char *)FUN_0082ba59(param_1,2,0);
  iVar2 = FUN_0082d490(param_1,3);
  iVar3 = FUN_0082c1fd(param_1,4,local_334 + 1);
  if (*local_32c == '^') {
    local_32c = local_32c + 1;
  }
  else {
    local_330 = 0;
  }
  local_328 = 0;
  if ((((iVar2 != 3) && (iVar2 != 4)) && (iVar2 != 6)) && (iVar2 != 5)) {
    FUN_0082b8e4(param_1,3,"string/function/table expected");
  }
  FUN_0082b98a(param_1,local_324);
  local_114 = puVar1 + local_334;
  local_110 = param_1;
  puVar4 = puVar1;
  local_118 = puVar1;
  if (iVar3 < 1) {
LAB_008353d2:
    FUN_0082b81b(local_324,puVar4,(int)local_114 - (int)puVar4);
    FUN_0082c2cb(local_324);
    FUN_0082ccca(param_1,local_328);
    FUN_0083e885();
    return;
  }
  do {
    local_10c = 0;
    puVar4 = (undefined1 *)FUN_00835b72(&local_118,puVar1,local_32c);
    if (puVar4 == (undefined1 *)0x0) {
LAB_00835379:
      puVar4 = puVar1;
      if (local_114 <= puVar1) goto LAB_008353d2;
      if (&local_118 <= local_324[0]) {
        FUN_0082c2ac(local_324);
      }
      *(undefined1 *)local_324[0] = *puVar1;
      local_324[0] = (undefined1 **)((int)local_324[0] + 1);
      puVar4 = puVar1 + 1;
    }
    else {
      local_328 = local_328 + 1;
      FUN_0083574a(&local_118,local_324,puVar1,puVar4);
      if (puVar4 <= puVar1) goto LAB_00835379;
    }
    if ((local_330 != 0) || (puVar1 = puVar4, iVar3 <= local_328)) goto LAB_008353d2;
  } while( true );
}

