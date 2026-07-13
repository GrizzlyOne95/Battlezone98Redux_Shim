
void __thiscall FUN_004b0610(int param_1,undefined4 param_2)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  int local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = param_1;
  if (((*(uint *)(*(int *)(param_1 + 0x228) + 0x114) & 4) != 0) &&
     ((*(uint *)(*(int *)(param_1 + 0x228) + 0x114) & 8) != 0)) {
    iVar2 = FUN_00479f30(param_2);
    iVar3 = FUN_004b0400();
    if (iVar2 == iVar3) goto LAB_004b07b7;
  }
  if ((((*(uint *)(*(int *)(local_18 + 0x228) + 0x114) & 4) != 0) &&
      (*(float *)(*(int *)(local_18 + 0xf8) + 0x170) != 0.0)) &&
     (local_1c = FUN_00479f30(param_2), local_1c != 0)) {
    local_24 = 0;
    local_20 = 0;
    local_2c = *(undefined4 *)(local_18 + 0xf4);
    local_28 = *(undefined4 *)(local_18 + 0xf4);
    uVar1 = (**(code **)(*(int *)(local_18 + 0x18) + 4))();
    local_24 = CONCAT22(local_24._2_2_,
                        (ushort)local_24 & 0xfc30 | (uVar1 & 0xf) << 6 |
                        *(ushort *)(*(int *)(local_18 + 0xf8) + 0x174) & 0xf);
    local_20 = *(undefined4 *)(*(int *)(local_18 + 0xf8) + 0x170);
    local_14 = 0;
    local_10 = 0xbf800000;
    local_c = 0;
    (**(code **)(*(int *)(local_1c + 0x18) + 0x38))(&local_2c,&local_14);
  }
  *(uint *)(*(int *)(local_18 + 0x228) + 0x114) =
       *(uint *)(*(int *)(local_18 + 0x228) + 0x114) & 0xfffffffb;
LAB_004b07b7:
  FUN_0083e885();
  return;
}

