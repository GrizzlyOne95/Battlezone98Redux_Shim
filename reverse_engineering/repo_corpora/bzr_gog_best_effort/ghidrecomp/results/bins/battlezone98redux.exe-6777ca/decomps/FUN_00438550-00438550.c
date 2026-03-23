
void __fastcall FUN_00438550(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  char *local_64;
  char *local_60;
  undefined1 local_50 [16];
  undefined4 local_40;
  code *local_28;
  undefined1 local_24 [4];
  undefined4 local_20;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ((*(char *)(param_1 + 0x34) == '\0') && (cVar1 = FUN_0042d8f0(), cVar1 == '\0')) {
    puVar2 = (undefined4 *)FUN_00438b60();
    puVar2 = (undefined4 *)*puVar2;
    FUN_0043a990(local_50);
    FUN_0043a9e0(local_24);
    local_28 = FUN_00438530;
    local_40 = 0x25;
    local_20 = 10000;
    uVar3 = FUN_0043aa30(*puVar2,0,local_50,local_24);
    *(undefined4 *)(param_1 + 0x38) = uVar3;
    if (*(int *)(param_1 + 0x38) == 0) {
      FUN_007d6a70("AudioMessage %s - not played\n",*puVar2);
      operator_delete(puVar2);
      FUN_00438bb0();
    }
    else {
      local_64 = (char *)*puVar2;
      local_60 = (char *)(param_1 + 0x40);
      do {
        cVar1 = *local_64;
        *local_60 = cVar1;
        local_64 = local_64 + 1;
        local_60 = local_60 + 1;
      } while (cVar1 != '\0');
      *(undefined **)(*(int *)(param_1 + 0x38) + 0x74) = &DAT_00946aa8;
      *(undefined4 *)(param_1 + 0x3c) = puVar2[1];
      *(undefined1 *)(param_1 + 0x34) = 1;
    }
  }
  FUN_0083e885();
  return;
}

