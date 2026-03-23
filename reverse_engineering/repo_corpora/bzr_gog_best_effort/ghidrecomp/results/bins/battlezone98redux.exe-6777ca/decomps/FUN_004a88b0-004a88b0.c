
void __thiscall FUN_004a88b0(int param_1,int param_2,undefined4 *param_3)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined1 local_d8 [72];
  undefined1 local_90 [12];
  int local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68 [6];
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_84 = param_1;
  if (((((*(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x20) == 0) &&
       (*(int *)(param_2 + 0x84) != 3)) &&
      ((*(int *)(param_2 + 0x84) != 4 || ((*(uint *)(param_2 + 0x14) & 0x200) == 0)))) &&
     ((((*(char *)(param_1 + 0x9c) == '\0' || (*(int *)(param_1 + 0xa0) == 0)) ||
       (iVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0xa0) + 0x18) + 0x30))(), param_2 != iVar2)
       ) && ((*(uint *)(*(int *)(local_84 + 0x230) + 0x114) & 0x20000) == 0)))) {
    puVar3 = param_3;
    puVar4 = (undefined4 *)(*(int *)(local_84 + 0x230) + 0x4c);
    for (iVar2 = 0x1e; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    iVar2 = FUN_0062e000(param_2);
    if ((iVar2 == 0) || (cVar1 = FUN_004a8850(param_2), cVar1 != '\0')) {
      *(undefined4 *)(*(int *)(local_84 + 0x230) + 0x54) = 0;
    }
    local_74 = *(undefined4 *)(local_84 + 300);
    local_70 = *(undefined4 *)(local_84 + 0x130);
    local_6c = *(undefined4 *)(local_84 + 0x134);
    puVar3 = (undefined4 *)FUN_0062bf70(local_d8,param_2);
    puVar4 = local_68;
    for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    local_80 = local_50;
    local_7c = local_4c;
    local_78 = local_48;
    puVar3 = (undefined4 *)
             FUN_004401a0(local_90,local_50,local_4c,local_48,local_74,local_70,local_6c);
    local_20 = *puVar3;
    local_1c = puVar3[1];
    local_18 = puVar3[2];
    local_14 = local_20;
    local_10 = local_1c;
    local_c = local_18;
    FUN_008245f0(*(undefined4 *)(local_84 + 0xf4),param_2,&local_20,param_3 + 0x1b,param_3 + 0x15);
  }
  FUN_0083e885();
  return;
}

