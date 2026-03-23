
void FUN_005c8ec0(undefined4 *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined1 local_24 [12];
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = FUN_00462630(param_2);
  if (local_18 == 0) {
    puVar1 = (undefined4 *)FUN_00440000(local_24,0,0,0);
    local_14 = *puVar1;
    local_10 = puVar1[1];
    local_c = puVar1[2];
    *param_1 = local_14;
    param_1[1] = local_10;
    param_1[2] = local_c;
  }
  else {
    iVar2 = FUN_0045c490();
    *param_1 = *(undefined4 *)(iVar2 + 0x24);
    param_1[1] = *(undefined4 *)(iVar2 + 0x28);
    param_1[2] = *(undefined4 *)(iVar2 + 0x2c);
  }
  FUN_0083e885();
  return;
}

