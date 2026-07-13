
void __fastcall FUN_004d3b80(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined1 local_48 [12];
  float local_3c;
  float local_38;
  float local_34;
  undefined4 local_30;
  float local_2c;
  int local_28;
  undefined4 local_24;
  int local_20;
  char local_1a;
  undefined1 local_19;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = param_1;
  if (*(int *)(param_1 + 8) != 0xd) {
    uVar2 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
    *(undefined4 *)(local_18 + 0x18) = uVar2;
    if (*(int *)(local_18 + 0x18) == 0) {
      *(undefined4 *)(local_18 + 0xc) = 0xd;
    }
    else {
      uVar2 = FUN_004643e0(*(undefined4 *)(local_18 + 0x10),0);
      *(undefined4 *)(local_18 + 0x7c) = uVar2;
      local_20 = *(int *)(local_18 + 8) + -1;
      switch(local_20) {
      case 0:
        FUN_00602420();
        break;
      case 1:
        uVar2 = (**(code **)(*(int *)(*(int *)(local_18 + 0x18) + 0x18) + 0xc))();
        uVar2 = (**(code **)(*(int *)(*(int *)(local_18 + 0x10) + 0x18) + 0xc))(uVar2);
        fVar5 = (float10)FUN_00462010(uVar2);
        local_38 = (float)fVar5;
        if (2500.0 <= local_38) {
          uVar2 = (**(code **)(*(int *)(*(int *)(local_18 + 0x18) + 0x18) + 0xc))(local_18 + 0x28);
          fVar5 = (float10)FUN_00462010(uVar2);
          local_34 = (float)fVar5;
          if (local_34 <= 10000.0) {
            cVar1 = FUN_006027f0();
            if (cVar1 == '\0') {
              uVar2 = (**(code **)(*(int *)(*(int *)(local_18 + 0x10) + 0x18) + 0xc))
                                (local_18 + 0x34);
              fVar5 = (float10)FUN_00462010(uVar2);
              local_3c = (float)fVar5;
              if (225.0 <= local_3c) {
                FUN_00601250();
              }
              else {
                *(undefined4 *)(local_18 + 0xc) = 2;
                puVar4 = (undefined4 *)
                         (**(code **)(*(int *)(*(int *)(local_18 + 0x18) + 0x18) + 0xc))();
                *(undefined4 *)(local_18 + 0x28) = *puVar4;
                *(undefined4 *)(local_18 + 0x2c) = puVar4[1];
                *(undefined4 *)(local_18 + 0x30) = puVar4[2];
              }
            }
            else {
              *(undefined4 *)(local_18 + 0xc) = 3;
            }
          }
          else {
            *(undefined4 *)(local_18 + 0xc) = 2;
            puVar4 = (undefined4 *)(**(code **)(*(int *)(*(int *)(local_18 + 0x18) + 0x18) + 0xc))()
            ;
            *(undefined4 *)(local_18 + 0x28) = *puVar4;
            *(undefined4 *)(local_18 + 0x2c) = puVar4[1];
            *(undefined4 *)(local_18 + 0x30) = puVar4[2];
          }
        }
        else {
          *(undefined4 *)(local_18 + 0xc) = 4;
        }
        break;
      case 2:
        FUN_006029b0();
        break;
      case 3:
        uVar2 = (**(code **)(*(int *)(*(int *)(local_18 + 0x18) + 0x18) + 0xc))();
        uVar2 = (**(code **)(*(int *)(*(int *)(local_18 + 0x10) + 0x18) + 0xc))(uVar2);
        fVar5 = (float10)FUN_00462010(uVar2);
        local_2c = (float)fVar5;
        if (local_2c <= 10000.0) {
          cVar1 = FUN_006027f0();
          if (cVar1 == '\0') {
            FUN_00607db0();
          }
          else {
            *(undefined4 *)(local_18 + 0xc) = 3;
          }
        }
        else {
          puVar4 = (undefined4 *)(**(code **)(*(int *)(*(int *)(local_18 + 0x18) + 0x18) + 0xc))();
          *(undefined4 *)(local_18 + 0x28) = *puVar4;
          *(undefined4 *)(local_18 + 0x2c) = puVar4[1];
          *(undefined4 *)(local_18 + 0x30) = puVar4[2];
          *(undefined4 *)(local_18 + 0xc) = 2;
        }
      }
      if ((*(int *)(local_18 + 8) == 4) && (iVar3 = FUN_00417ca0(), iVar3 != 0)) {
        FUN_00417ca0();
        iVar3 = FUN_00417fb0();
        if ((iVar3 != 0) && (*(int *)(*(int *)(*(int *)(local_18 + 0xb4) + 8) + 0xc) != 0x44495350))
        {
          local_24 = *(undefined4 *)(local_18 + 0xa0);
          local_28 = FUN_00463240(*(undefined4 *)(local_18 + 0x10),&local_24);
          if (local_28 != 0) {
            local_30 = *(undefined4 *)(local_18 + 0x18);
            *(int *)(local_18 + 0x18) = local_28;
            local_1a = FUN_00603ad0();
            puVar4 = (undefined4 *)
                     FUN_004462d0(local_48,*(float *)(local_18 + 0x98) * 0.5 - 0.5,
                                  *(undefined4 *)(local_18 + 0xe4),*(undefined4 *)(local_18 + 0xe8),
                                  *(undefined4 *)(local_18 + 0xec));
            local_14 = *puVar4;
            local_10 = puVar4[1];
            local_c = puVar4[2];
            FUN_00607110(local_18 + 200,&local_14);
            cVar1 = FUN_00608460();
            if (cVar1 == '\0') {
              if ((local_1a == '\0') ||
                 (cVar1 = FUN_00462b60(*(undefined4 *)(local_18 + 0x10),local_24,0x3e99999a,
                                       0x3f800000), cVar1 != '\0')) {
                local_19 = 0;
              }
              else {
                local_19 = 1;
              }
              FUN_00604130(local_19);
            }
            else {
              cVar1 = FUN_00608490();
              if (cVar1 != '\0') {
                FUN_006084c0();
              }
            }
            *(undefined4 *)(local_18 + 0x18) = local_30;
          }
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

