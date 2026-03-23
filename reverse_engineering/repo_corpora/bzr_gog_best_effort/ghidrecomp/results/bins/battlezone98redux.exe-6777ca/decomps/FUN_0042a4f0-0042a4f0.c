
void __fastcall FUN_0042a4f0(undefined4 *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_40 [4];
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined4 local_24;
  undefined4 local_20;
  void *local_1c;
  undefined4 local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 local_c [4];
  undefined4 *local_8;
  
  local_10 = (void *)*param_1;
  local_8 = param_1;
  operator_delete__(local_10);
  *local_8 = 0;
  local_8[1] = 0;
  local_8[2] = 0;
  cVar1 = FUN_004202c0();
  if (cVar1 == '\0') {
    puVar2 = (undefined4 *)FID_conflict_begin(local_28);
    local_14 = *puVar2;
    puVar2 = (undefined4 *)FUN_00420260(local_2c);
    local_18 = *puVar2;
    FUN_00428920(local_30,local_18,local_14);
  }
  cVar1 = FUN_0042d8f0();
  if (cVar1 == '\0') {
    FUN_0042d8c0(local_c);
    while( true ) {
      uVar3 = FID_conflict_begin(local_34);
      cVar1 = FUN_00420f10(uVar3);
      if (cVar1 == '\0') break;
      puVar2 = (undefined4 *)FUN_0042da60();
      local_1c = (void *)*puVar2;
      operator_delete__(local_1c);
      FUN_0042da80();
    }
    puVar2 = (undefined4 *)FID_conflict_begin(local_38);
    local_20 = *puVar2;
    puVar2 = (undefined4 *)FUN_0042d8c0(local_3c);
    local_24 = *puVar2;
    FUN_0042d970(local_40,local_24,local_20);
  }
  return;
}

