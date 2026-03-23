
void __thiscall FUN_005e16f0(int param_1,float param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
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
    if (local_50 != 0) {
      iVar1 = (**(code **)(*(int *)(local_50 + 0x18) + 4))();
      if (-1 < iVar1) {
        uVar2 = FUN_0045c4b0();
        if ((uVar2 & 0x200) == 0) {
          uVar3 = FUN_0045c4d0();
          puVar4 = (undefined4 *)FUN_0081fe60(local_90,local_4c + 0xf8,uVar3);
          puVar5 = local_48;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar5 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar5 = puVar5 + 1;
          }
          puVar4 = local_48;
          puVar5 = (undefined4 *)(*(int *)(local_4c + 0x14) + 0x20);
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar5 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar5 = puVar5 + 1;
          }
          iVar1 = (**(code **)(*(int *)(local_50 + 0x18) + 4))();
          if (iVar1 != *(int *)(local_4c + 0x138)) {
            uVar3 = (**(code **)(*(int *)(local_50 + 0x18) + 4))();
            *(undefined4 *)(local_4c + 0x13c) = uVar3;
            (**(code **)(*(int *)(local_50 + 0x18) + 8))(*(undefined4 *)(local_4c + 0x138));
          }
          *(float *)(local_4c + 0x78) = *(float *)(local_4c + 0x78) - param_2;
          if (0.0 < *(float *)(local_4c + 0x78)) {
            *(uint *)(*(int *)(local_4c + 0x14) + 0x14) =
                 *(uint *)(*(int *)(local_4c + 0x14) + 0x14) & 0xfffffdff;
          }
          else {
            (**(code **)(*(int *)(local_50 + 0x18) + 8))(*(undefined4 *)(local_4c + 0x13c));
            *(uint *)(*(int *)(local_4c + 0x14) + 0x14) =
                 *(uint *)(*(int *)(local_4c + 0x14) + 0x14) | 0x200;
          }
          goto LAB_005e188b;
        }
      }
    }
    *(uint *)(*(int *)(local_4c + 0x14) + 0x14) =
         *(uint *)(*(int *)(local_4c + 0x14) + 0x14) | 0x200;
  }
LAB_005e188b:
  FUN_0083e885();
  return;
}

