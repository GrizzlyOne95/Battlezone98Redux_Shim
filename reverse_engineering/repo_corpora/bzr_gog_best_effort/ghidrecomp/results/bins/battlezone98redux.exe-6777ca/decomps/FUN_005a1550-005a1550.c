
void FUN_005a1550(int param_1,undefined4 *param_2)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined1 local_e0 [72];
  undefined1 local_98 [12];
  undefined4 local_8c;
  float local_88;
  undefined4 local_84;
  undefined4 *local_80;
  uint *local_7c;
  int *local_78;
  undefined4 *local_74;
  int local_70;
  int *local_6c;
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
  cVar1 = FUN_004b9830();
  if ((((cVar1 == '\0') && ((*(uint *)(*(int *)(local_70 + 0xf4) + 0x14) & 0x20) == 0)) &&
      ((*(uint *)(*(int *)(local_70 + 0xf4) + 0x14) & 0x1000200) == 0)) &&
     (iVar2 = FUN_0045bdf0(), iVar2 != 0)) {
    if (*(int *)(param_1 + 0x78) != 0) {
      param_1 = FUN_0062e050(param_1);
    }
    iVar2 = FUN_00417e20(param_1);
    if ((iVar2 != 0) && ((*(uint *)(param_1 + 0x14) & 0x200) == 0)) {
      local_6c = (int *)FUN_00479f30(param_1);
      iVar2 = FUN_0045bdf0();
      if ((iVar2 == 0) && (iVar2 = (**(code **)local_6c[6])(), 0 < *(int *)(iVar2 + 0x50))) {
        iVar2 = FUN_00572a70();
        if (iVar2 != 0) {
          FUN_0049f300(0);
          FUN_004b8460();
        }
        cVar1 = FUN_004db5b0(local_6c);
        if (cVar1 != '\0') {
          FUN_004dbc00();
          FUN_004dbce0(0);
        }
        local_8c = (**(code **)(local_6c[6] + 4))();
        (**(code **)(local_6c[6] + 8))(*(undefined4 *)(local_70 + 0x174));
        local_6c[0x3b] = *(int *)(local_70 + 0xf8);
        if (local_70 == DAT_00917afc) {
          (**(code **)(*local_6c + 0xc))();
        }
        else {
          local_78 = (int *)FUN_0045ca50();
          (**(code **)(*local_78 + 0x1c))(local_6c);
        }
        FUN_004db4f0(local_8c);
        iVar2 = FUN_00572a70();
        if (iVar2 != 0) {
          iVar2 = (**(code **)(local_6c[6] + 0x30))();
          local_7c = (uint *)(iVar2 + 0x14);
          *local_7c = *local_7c & 0xfffffffb;
        }
        if (*(int *)(local_70 + 0xfc) != 0) {
          local_80 = *(undefined4 **)(local_70 + 0xfc);
          local_74 = local_80;
          if (local_80 == (undefined4 *)0x0) {
            local_84 = 0;
          }
          else {
            local_84 = (**(code **)*local_80)(1);
          }
          *(undefined4 *)(local_70 + 0xfc) = 0;
        }
        FUN_0062de40(*(undefined4 *)(local_70 + 0xf4),0x201);
        goto LAB_005a188b;
      }
    }
    puVar3 = param_2;
    puVar4 = (undefined4 *)(*(int *)(local_70 + 0x230) + 0x4c);
    for (iVar2 = 0x1e; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    puVar3 = (undefined4 *)FUN_0062bf70(local_e0,param_1);
    puVar4 = local_68;
    for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    puVar3 = (undefined4 *)
             FUN_004401a0(local_98,local_50,local_4c,local_48,*(undefined4 *)(local_70 + 300),
                          *(undefined4 *)(local_70 + 0x130),*(undefined4 *)(local_70 + 0x134));
    local_20 = *puVar3;
    local_1c = puVar3[1];
    local_18 = puVar3[2];
    local_14 = local_20;
    local_10 = local_1c;
    local_c = local_18;
    fVar5 = (float10)FUN_004428b0(&local_20,param_2 + 0x1b);
    local_88 = (float)fVar5;
    if (1.0 < local_88) {
      FUN_008245f0(*(undefined4 *)(local_70 + 0xf4),param_1,&local_20,param_2 + 0x1b,param_2 + 0x15)
      ;
    }
  }
LAB_005a188b:
  FUN_0083e885();
  return;
}

