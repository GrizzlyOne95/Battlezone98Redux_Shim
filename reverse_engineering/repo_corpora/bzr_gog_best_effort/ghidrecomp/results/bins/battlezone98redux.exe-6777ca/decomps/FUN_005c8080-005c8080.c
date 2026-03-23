
void FUN_005c8080(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  int iVar2;
  float10 fVar3;
  undefined1 local_34 [12];
  int local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_24 = FUN_00462630(param_3);
  if (local_24 != 0) {
    puVar1 = (undefined4 *)(**(code **)(*(int *)(local_24 + 0x18) + 0xc))();
    local_20 = *puVar1;
    local_1c = puVar1[1];
    local_18 = puVar1[2];
    iVar2 = (*(code *)**(undefined4 **)(local_24 + 0x18))();
    local_28 = *(int *)(iVar2 + 0x1c);
    if ((0 < local_28) && ((local_28 < 3 || (local_28 == 6)))) {
      puVar1 = (undefined4 *)FUN_00462490();
      fVar3 = (float10)FUN_00462470(*puVar1,puVar1[1],puVar1[2]);
      puVar1 = (undefined4 *)FUN_00439d00(local_34,local_20,local_1c,local_18,(float)fVar3);
      local_20 = *puVar1;
      local_1c = puVar1[1];
      local_18 = puVar1[2];
      local_14 = local_20;
      local_10 = local_1c;
      local_c = local_18;
    }
    FUN_005c8380(param_1,param_2,&local_20,param_4);
  }
  FUN_0083e885();
  return;
}

