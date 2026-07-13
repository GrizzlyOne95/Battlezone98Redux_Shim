
void __thiscall FUN_005e07b0(int param_1,float param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 local_90 [64];
  int local_50;
  int local_4c;
  undefined4 local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_4c = param_1;
  if (*(int *)(param_1 + 0xf0) == 0) {
    FUN_005bd060(param_2);
  }
  else {
    local_50 = FUN_004da060(*(undefined4 *)(param_1 + 0xf0));
    if (local_50 == 0) {
      *(uint *)(*(int *)(local_4c + 0x14) + 0x14) =
           *(uint *)(*(int *)(local_4c + 0x14) + 0x14) | 0x200;
    }
    else {
      *(float *)(local_4c + 0x78) = *(float *)(local_4c + 0x78) - param_2;
      if (0.0 < *(float *)(local_4c + 0x78)) {
        uVar1 = FUN_0045c4d0();
        puVar2 = (undefined4 *)FUN_0081fe60(local_90,local_4c + 0xf8,uVar1);
        puVar4 = local_48;
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar4 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar4 = puVar4 + 1;
        }
        puVar2 = local_48;
        puVar4 = (undefined4 *)(*(int *)(local_4c + 0x14) + 0x20);
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar4 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar4 = puVar4 + 1;
        }
      }
      else {
        *(uint *)(*(int *)(local_4c + 0x14) + 0x14) =
             *(uint *)(*(int *)(local_4c + 0x14) + 0x14) | 0x200;
      }
    }
  }
  FUN_0083e885();
  return;
}

