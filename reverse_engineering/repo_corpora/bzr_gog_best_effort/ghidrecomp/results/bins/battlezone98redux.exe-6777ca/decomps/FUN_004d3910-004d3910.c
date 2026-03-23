
void FUN_004d3910(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined1 local_24 [12];
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_006004a0();
  if (*(int *)(local_18 + 8) == 2) {
    puVar1 = (undefined4 *)FUN_00462490();
    puVar1 = (undefined4 *)
             (**(code **)(*(int *)(*(int *)(local_18 + 0x18) + 0x18) + 0xc))
                       (0x41a00000,*puVar1,puVar1[1],puVar1[2]);
    puVar1 = (undefined4 *)FUN_00439d00(local_24,*puVar1,puVar1[1],puVar1[2]);
    local_14 = *puVar1;
    local_10 = puVar1[1];
    local_c = puVar1[2];
    uVar2 = (**(code **)(*(int *)(*(int *)(local_18 + 0x18) + 0x18) + 0xc))(&local_14,DAT_0091757c);
    FUN_004b7150(uVar2);
  }
  FUN_0083e885();
  return;
}

