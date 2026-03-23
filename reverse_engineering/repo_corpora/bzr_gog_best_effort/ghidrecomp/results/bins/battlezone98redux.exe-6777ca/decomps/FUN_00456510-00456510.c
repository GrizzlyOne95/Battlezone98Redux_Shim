
void FUN_00456510(void)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_8c [12];
  undefined1 local_80 [12];
  undefined1 local_74 [12];
  undefined1 local_68 [12];
  undefined1 local_5c [4];
  undefined4 *local_58;
  undefined4 *local_54;
  undefined4 local_50;
  float local_4c;
  undefined1 local_48 [4];
  int local_44;
  undefined4 *local_40;
  undefined4 *local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00447e20(local_48);
  while( true ) {
    iVar1 = FUN_00447e70();
    FUN_00447e50(local_5c);
    iVar2 = FUN_00447e70();
    if (iVar1 == iVar2) break;
    local_58 = (undefined4 *)FUN_00447e70();
    local_3c = local_58;
    FUN_00447e90();
    if (*(char *)(local_3c + 7) == '\0') {
      local_54 = local_3c;
      local_40 = local_3c;
      if (local_3c == (undefined4 *)0x0) {
        local_50 = 0;
      }
      else {
        local_50 = (**(code **)*local_3c)(1);
      }
    }
    else {
      puVar3 = (undefined4 *)FUN_004560b0(local_80,local_3c + 8);
      local_2c = *puVar3;
      local_28 = puVar3[1];
      local_24 = puVar3[2];
      puVar3 = (undefined4 *)FUN_00439de0(local_68,local_3c + 8);
      local_38 = *puVar3;
      local_34 = puVar3[1];
      local_30 = puVar3[2];
      puVar3 = (undefined4 *)
               FUN_004401a0(local_74,local_38,local_34,local_30,local_3c[0x1c],local_3c[0x1d],
                            local_3c[0x1e]);
      local_20 = *puVar3;
      local_1c = puVar3[1];
      local_18 = puVar3[2];
      fVar4 = (float10)FUN_004428b0(&local_20,&local_2c);
      local_4c = (float)fVar4;
      local_3c[0x1f] = local_4c + (float)local_3c[0x1f];
      fVar4 = (float10)FUN_00456080(local_3c[0x1f],*(undefined4 *)(local_44 + 0x17c));
      local_3c[0x1f] = (float)fVar4;
      puVar3 = (undefined4 *)FUN_00439de0(local_8c,local_3c + 8);
      local_14 = *puVar3;
      local_10 = puVar3[1];
      local_c = puVar3[2];
      local_3c[0x1c] = local_14;
      local_3c[0x1d] = local_10;
      local_3c[0x1e] = local_c;
    }
  }
  FUN_0083e885();
  return;
}

