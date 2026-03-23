
void FUN_005cdc40(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_00462630(param_1);
  if (iVar1 != 0) {
    puVar2 = (undefined4 *)FUN_00462400();
    local_18 = *puVar2;
    local_14 = puVar2[1];
    local_10 = puVar2[2];
    local_c = puVar2[3];
    uVar3 = FUN_0045c4d0();
    FUN_00820180(&local_18,&local_18,1,uVar3);
    FUN_00660960(&local_18,param_2,1);
  }
  FUN_0083e885();
  return;
}

