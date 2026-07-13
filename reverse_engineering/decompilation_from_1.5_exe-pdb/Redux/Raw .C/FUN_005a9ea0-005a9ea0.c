
void FUN_005a9ea0(int param_1,undefined4 *param_2)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  float10 fVar6;
  undefined1 local_b4 [12];
  undefined1 local_a8 [12];
  undefined1 local_9c [12];
  undefined1 local_90 [12];
  undefined1 local_84 [12];
  float local_78;
  undefined4 *local_74;
  float local_70;
  undefined4 *local_6c;
  undefined2 *local_68;
  int local_64;
  int *local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  int local_44;
  int local_40;
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c;
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
  local_64 = FUN_00479f30(param_1);
  if (((((*(uint *)(local_60[0x8a] + 0x114) & 4) == 0) ||
       ((*(uint *)(local_60[0x8a] + 0x114) & 8) == 0)) ||
      (iVar2 = FUN_004b0400(), local_64 != iVar2)) &&
     ((((*(uint *)(local_60[0x8a] + 0x114) & 4) == 0 || (*(int *)(param_1 + 0x84) != 3)) ||
      (iVar2 = FUN_0045c4f0(param_1), (*(uint *)(iVar2 + 0x114) & 4) == 0)))) {
    fVar6 = (float10)FUN_004428b0(local_60 + 0x4b,param_2 + 0x1b,param_2[0x1b],param_2[0x1c],
                                  param_2[0x1d]);
    local_78 = (float)fVar6;
    piVar3 = (int *)FUN_00459570(local_84,0x3f000000,local_60[0x4b],local_60[0x4c],local_60[0x4d],
                                 -local_78);
    local_44 = *piVar3;
    local_40 = piVar3[1];
    local_3c = piVar3[2];
    local_60[0x4b] = local_44;
    local_60[0x4c] = local_40;
    local_60[0x4d] = local_3c;
    iVar2 = local_60[0x3c];
    puVar4 = (undefined4 *)
             FUN_004401a0(local_a8,param_2[0x15],param_2[0x16],param_2[0x17],
                          *(undefined4 *)(iVar2 + 8),*(undefined4 *)(iVar2 + 0xc),
                          *(undefined4 *)(iVar2 + 0x10));
    local_38 = *puVar4;
    local_34 = puVar4[1];
    local_30 = puVar4[2];
    local_20 = local_38;
    local_1c = local_34;
    local_18 = local_30;
    puVar4 = (undefined4 *)FUN_00440300(local_90,param_2 + 0x18,local_60[0x3d] + 0x20);
    local_50 = *puVar4;
    local_4c = puVar4[1];
    local_48 = puVar4[2];
    local_14 = local_50;
    local_10 = local_4c;
    local_c = local_48;
    puVar4 = (undefined4 *)FUN_004440d0(local_9c,&local_50,&local_38);
    local_5c = *puVar4;
    local_58 = puVar4[1];
    local_54 = puVar4[2];
    fVar6 = (float10)FUN_004428b0(&local_38,&local_38,local_5c,local_58,local_54);
    local_70 = (float)fVar6;
    piVar3 = (int *)FUN_00439d00(local_b4,local_60[0x4e],local_60[0x4f],local_60[0x50],
                                 0.2 / local_70);
    local_2c = *piVar3;
    local_28 = piVar3[1];
    local_24 = piVar3[2];
    local_60[0x4e] = local_2c;
    local_60[0x4f] = local_28;
    local_60[0x50] = local_24;
    if (((*(uint *)(local_60[0x3d] + 0x14) & 0x1000200) == 0) &&
       ((((*(int *)(param_1 + 0x84) == 1 || (*(int *)(param_1 + 0x84) == 6)) ||
         (*(int *)(param_1 + 0x84) == 2)) &&
        ((((local_64 != 0 && (cVar1 = FUN_004b9830(), cVar1 == '\0')) &&
          (cVar1 = (**(code **)(*local_60 + 100))(local_64), cVar1 != '\0')) &&
         (cVar1 = FUN_00571c40(), cVar1 != '\0')))))) {
      iVar2 = (**(code **)local_60[6])();
      if ((*(int *)(iVar2 + 0x14) != 0x414d4d4f) &&
         (iVar2 = (**(code **)local_60[6])(), *(int *)(iVar2 + 0x14) != 0x524b4954)) {
        local_68 = &DAT_009175c0;
        local_6c = &DAT_009175c2;
        local_74 = (undefined4 *)&DAT_009175c6;
        DAT_009175c0 = 0x4752;
        uVar5 = FUN_004b9a90();
        *local_6c = uVar5;
        uVar5 = FUN_004b9a90();
        *local_74 = uVar5;
        FUN_00575890(&DAT_009175c0,10,1,1);
      }
      FUN_004b9940();
    }
    else {
      puVar4 = (undefined4 *)(local_60[0x8a] + 0x4c);
      for (iVar2 = 0x1e; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = *param_2;
        param_2 = param_2 + 1;
        puVar4 = puVar4 + 1;
      }
    }
  }
  FUN_0083e885();
  return;
}

