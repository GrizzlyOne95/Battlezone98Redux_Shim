
void __fastcall FUN_00478a50(int param_1)

{
  char cVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined8 local_68;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  undefined4 local_1c;
  int *local_18;
  int local_14;
  int local_10;
  char local_b;
  undefined1 local_a;
  char local_9;
  int local_8;
  
  if (*(int *)(param_1 + 8) == 0xd) {
    return;
  }
  local_8 = param_1;
  uVar3 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
  *(undefined4 *)(local_8 + 0x18) = uVar3;
  if (*(int *)(local_8 + 0x14) == *(int *)(local_8 + 0x24)) {
    if ((*(int *)(local_8 + 0x18) == 0) || (iVar4 = FUN_00417ca0(), iVar4 == 0)) {
      *(undefined4 *)(local_8 + 0xc) = 0xd;
      return;
    }
    cVar1 = FUN_004db510(*(undefined4 *)(local_8 + 0x18));
    if ((cVar1 == '\0') ||
       ((*(int *)(*(int *)(local_8 + 0x10) + 0xac) == 4 &&
        (*(int *)(*(int *)(local_8 + 0x10) + 0xa8) != 0)))) {
      local_1c = 1;
    }
    else {
      local_1c = 0;
    }
    local_b = (char)local_1c;
    if ((char)local_1c == '\0') {
      *(undefined4 *)(local_8 + 0xc) = 0xd;
      return;
    }
  }
  else if (*(int *)(local_8 + 0x18) == 0) {
    *(undefined4 *)(local_8 + 0xc) = 1;
    return;
  }
  cVar1 = FUN_00603a70();
  if (cVar1 != '\0') {
    FUN_00477ce0();
    local_80 = 0;
    local_7c = 0x14;
    local_78 = 0;
    local_74 = 0;
    local_68 = 0;
    FUN_004dbaf0(&local_80);
    *(undefined4 *)(local_8 + 8) = 0xd;
    *(undefined4 *)(local_8 + 0xc) = 0xd;
  }
  uVar3 = (**(code **)(*(int *)(*(int *)(local_8 + 0x10) + 0x18) + 0xc))();
  uVar3 = FUN_00463fc0(*(undefined4 *)(local_8 + 0x10),uVar3);
  *(undefined4 *)(local_8 + 0x7c) = uVar3;
  *(undefined1 *)(local_8 + 0xc4) = 0;
  local_10 = *(int *)(*(int *)(local_8 + 0x10) + 0x230) + 0xc4;
  local_14 = *(int *)(local_8 + 8) + -2;
  switch(local_14) {
  case 0:
    uVar2 = FUN_00603ad0();
    *(undefined1 *)(local_8 + 0xc4) = uVar2;
    if (*(char *)(local_8 + 0xc4) == '\0') {
      cVar1 = FUN_006027f0();
      if (cVar1 == '\0') {
        uVar3 = (**(code **)(*(int *)(*(int *)(local_8 + 0x18) + 0x18) + 0xc))(local_8 + 0x28);
        fVar6 = (float10)FUN_00462010(uVar3);
        local_28 = (float)fVar6;
        if (local_28 <= 10000.0) {
          uVar3 = (**(code **)(*(int *)(*(int *)(local_8 + 0x10) + 0x18) + 0xc))(local_8 + 0x34);
          fVar6 = (float10)FUN_00462010(uVar3);
          local_2c = (float)fVar6;
          if (100.0 <= local_2c) {
            FUN_00601250();
          }
          else {
            *(undefined4 *)(local_8 + 0xc) = 2;
          }
        }
        else {
          *(undefined4 *)(local_8 + 0xc) = 2;
        }
      }
      else {
        *(undefined4 *)(local_8 + 0xc) = 3;
      }
    }
    else {
      *(undefined4 *)(local_8 + 0xc) = 10;
    }
    break;
  case 1:
    FUN_006029b0();
    break;
  case 2:
    cVar1 = FUN_004786c0();
    if (cVar1 == '\0') {
      uVar3 = (**(code **)(*(int *)(*(int *)(local_8 + 0x18) + 0x18) + 0xc))();
      uVar3 = (**(code **)(*(int *)(*(int *)(local_8 + 0x10) + 0x18) + 0xc))(uVar3);
      fVar6 = (float10)FUN_00462010(uVar3);
      local_34 = (float)fVar6;
      if (local_34 <= 10000.0) {
        cVar1 = FUN_006027f0();
        if (cVar1 == '\0') {
          FUN_00607db0();
        }
        else {
          *(undefined4 *)(local_8 + 0xc) = 3;
        }
      }
      else {
        puVar5 = (undefined4 *)(**(code **)(*(int *)(*(int *)(local_8 + 0x18) + 0x18) + 0xc))();
        *(undefined4 *)(local_8 + 0x28) = *puVar5;
        *(undefined4 *)(local_8 + 0x2c) = puVar5[1];
        *(undefined4 *)(local_8 + 0x30) = puVar5[2];
        *(undefined4 *)(local_8 + 0xc) = 0xc;
      }
    }
    break;
  case 3:
    uVar2 = FUN_00603ad0();
    *(undefined1 *)(local_8 + 0xc4) = uVar2;
    if (*(char *)(local_8 + 0xc4) == '\0') {
      *(undefined4 *)(local_8 + 0xc) = 2;
    }
    else {
      FUN_00605f70();
    }
    break;
  case 4:
    cVar1 = FUN_004784b0();
    if (cVar1 == '\0') {
      FUN_00602420();
    }
    break;
  case 5:
    uVar2 = FUN_00603ad0();
    *(undefined1 *)(local_8 + 0xc4) = uVar2;
    uVar3 = (**(code **)(*(int *)(*(int *)(local_8 + 0x18) + 0x18) + 0xc))();
    uVar3 = (**(code **)(*(int *)(*(int *)(local_8 + 0x10) + 0x18) + 0xc))(uVar3);
    fVar6 = (float10)FUN_00462010(uVar3);
    local_48 = (float)fVar6;
    if (local_48 < *(float *)(local_8 + 0xa0) || local_48 == *(float *)(local_8 + 0xa0)) {
      uVar3 = (**(code **)(*(int *)(*(int *)(local_8 + 0x18) + 0x18) + 0x30))();
      iVar4 = FUN_00477d70(uVar3);
      if (iVar4 == 0) {
        fVar6 = (float10)FUN_00822d80();
        local_30 = (float)fVar6;
        if (local_30 <= *(float *)(local_8 + 0x100) + 10.0) {
          cVar1 = FUN_006027f0();
          if (cVar1 == '\0') {
            if (*(char *)(local_8 + 0xc4) == '\0') {
              FUN_00606e20();
              fVar6 = (float10)FUN_0045c420(*(undefined4 *)(local_8 + 0x4c),
                                            *(undefined4 *)(local_8 + 0x50),
                                            *(undefined4 *)(local_8 + 0x54));
              local_24 = (float)fVar6;
              if (local_24 < 5.0) {
                *(undefined4 *)(local_8 + 0xc) = 10;
              }
            }
            else {
              uVar3 = (**(code **)(*(int *)(*(int *)(local_8 + 0x18) + 0x18) + 0x30))();
              uVar3 = (**(code **)(*(int *)(*(int *)(local_8 + 0x10) + 0x18) + 0x30))(uVar3);
              cVar1 = FUN_004788d0(uVar3);
              if (cVar1 == '\0') {
                *(undefined4 *)(local_8 + 0xc) = 10;
              }
              else {
                *(undefined4 *)(local_8 + 0xc) = 8;
              }
            }
          }
          else {
            *(undefined4 *)(local_8 + 0xc) = 3;
          }
        }
        else {
          *(undefined4 *)(local_8 + 0xc) = 2;
        }
      }
      else {
        *(undefined4 *)(local_8 + 0xc) = 10;
      }
    }
    else {
      *(undefined4 *)(local_8 + 0xc) = 2;
    }
    break;
  case 6:
    uVar2 = FUN_00603ad0();
    *(undefined1 *)(local_8 + 0xc4) = uVar2;
    fVar6 = (float10)FUN_0046d040();
    local_38 = (float)fVar6;
    if (local_38 < *(float *)(local_8 + 0x100) || local_38 == *(float *)(local_8 + 0x100)) {
      if (*(char *)(local_8 + 0xc4) == '\0') {
        *(undefined4 *)(local_8 + 0xc) = 7;
      }
      else {
        fVar6 = (float10)FUN_00822d80();
        local_50 = (float)fVar6;
        if (local_50 <= *(float *)(local_8 + 0x100) + 8.0) {
          FUN_006057e0();
        }
        else {
          *(undefined4 *)(local_8 + 0xc) = 9;
          uVar3 = FUN_00462380();
          *(undefined4 *)(local_8 + 0x13c) = uVar3;
        }
      }
    }
    else {
      uVar3 = FUN_00462530();
      *(undefined4 *)(local_8 + 0x13c) = uVar3;
      *(undefined4 *)(local_8 + 0xc) = 9;
    }
    break;
  case 7:
    uVar2 = FUN_00603ad0();
    *(undefined1 *)(local_8 + 0xc4) = uVar2;
    uVar3 = FUN_00462630(*(undefined4 *)(local_8 + 0x13c));
    *(undefined4 *)(local_8 + 0x18) = uVar3;
    if (*(int *)(local_8 + 0x18) == 0) {
      *(undefined4 *)(local_8 + 0xc) = 7;
    }
    else {
      uVar3 = (**(code **)(*(int *)(*(int *)(local_8 + 0x18) + 0x18) + 0xc))();
      uVar3 = (**(code **)(*(int *)(*(int *)(local_8 + 0x10) + 0x18) + 0xc))(uVar3);
      fVar6 = (float10)FUN_00462010(uVar3);
      local_40 = (float)fVar6;
      if (local_40 <= 5625.0) {
        cVar1 = FUN_006027f0();
        if (cVar1 == '\0') {
          FUN_00607520();
          fVar6 = (float10)FUN_00822d80();
          local_60 = (float)fVar6;
          if (*(float *)(local_8 + 0x100) + 3.0 < local_60) {
            *(undefined4 *)(local_8 + 0xc) = 10;
          }
        }
        else {
          *(undefined4 *)(local_8 + 0xc) = 10;
        }
      }
      else {
        *(undefined4 *)(local_8 + 0xc) = 7;
      }
    }
    break;
  case 8:
    uVar2 = FUN_00603ad0();
    *(undefined1 *)(local_8 + 0xc4) = uVar2;
    fVar6 = (float10)FUN_0046d040();
    local_58 = (float)fVar6;
    if (local_58 < *(float *)(local_8 + 0x100) || local_58 == *(float *)(local_8 + 0x100)) {
      if (*(char *)(local_8 + 0xc4) == '\0') {
        uVar3 = (**(code **)(*(int *)(*(int *)(local_8 + 0x18) + 0x18) + 0x30))();
        iVar4 = FUN_00477d70(uVar3);
        if (iVar4 == 0) {
          *(undefined4 *)(local_8 + 0xc) = 7;
        }
        else {
          *(undefined4 *)(local_8 + 0xc) = 2;
        }
      }
      else {
        FUN_00605f70();
      }
    }
    else {
      uVar3 = FUN_00462530();
      *(undefined4 *)(local_8 + 0x13c) = uVar3;
      *(undefined4 *)(local_8 + 0xc) = 9;
    }
    break;
  case 9:
    uVar3 = (**(code **)(*(int *)(*(int *)(local_8 + 0x10) + 0x18) + 0xc))(local_8 + 0x28);
    fVar6 = (float10)FUN_00462010(uVar3);
    local_3c = (float)fVar6;
    if (*(float *)(local_8 + 0x138) <= local_3c) {
      cVar1 = FUN_006027f0();
      if (cVar1 == '\0') {
        uVar3 = (**(code **)(*(int *)(*(int *)(local_8 + 0x18) + 0x18) + 0xc))(local_8 + 0x28);
        fVar6 = (float10)FUN_00462010(uVar3);
        local_44 = (float)fVar6;
        if (local_44 <= 10000.0) {
          FUN_00601250();
        }
        else {
          *(undefined4 *)(local_8 + 0xc) = 0xb;
        }
      }
      else {
        *(undefined4 *)(local_8 + 0xc) = 3;
      }
    }
    else {
      *(undefined4 *)(local_8 + 0xc) = 6;
    }
    break;
  case 10:
    cVar1 = FUN_004786c0();
    if (cVar1 == '\0') {
      uVar3 = (**(code **)(*(int *)(*(int *)(local_8 + 0x18) + 0x18) + 0xc))();
      uVar3 = (**(code **)(*(int *)(*(int *)(local_8 + 0x10) + 0x18) + 0xc))(uVar3);
      fVar6 = (float10)FUN_00462010(uVar3);
      local_4c = (float)fVar6;
      if (2500.0 <= local_4c) {
        uVar3 = (**(code **)(*(int *)(*(int *)(local_8 + 0x18) + 0x18) + 0xc))(local_8 + 0x28);
        fVar6 = (float10)FUN_00462010(uVar3);
        local_54 = (float)fVar6;
        if (local_54 <= 10000.0) {
          cVar1 = FUN_006027f0();
          if (cVar1 == '\0') {
            uVar3 = (**(code **)(*(int *)(*(int *)(local_8 + 0x10) + 0x18) + 0xc))(local_8 + 0x34);
            fVar6 = (float10)FUN_00462010(uVar3);
            local_5c = (float)fVar6;
            if (225.0 <= local_5c) {
              FUN_00601250();
              if (*(float *)(local_10 + 0xc) == 1.0) {
                *(undefined4 *)(local_10 + 0x10) = 1;
              }
              else {
                *(undefined4 *)(local_10 + 0x10) = 0;
              }
            }
            else {
              *(undefined4 *)(local_8 + 0xc) = 0xc;
            }
          }
          else {
            *(undefined4 *)(local_8 + 0xc) = 3;
          }
        }
        else {
          *(undefined4 *)(local_8 + 0xc) = 0xc;
        }
      }
      else {
        *(undefined4 *)(local_8 + 0xc) = 4;
      }
    }
  }
  if (*(char *)(local_8 + 0xc4) == '\0') {
    FUN_00604130(0);
  }
  else {
    local_9 = FUN_00462b60(*(undefined4 *)(local_8 + 0x10),*(undefined4 *)(local_8 + 0xd4),
                           0x3e99999a,0x3f800000);
    local_18 = (int *)FUN_00477980(*(undefined4 *)(local_8 + 0x10));
    local_20 = 1e+30;
    if (local_18 != (int *)0x0) {
      uVar3 = (**(code **)(*(int *)(*local_18 + 0x18) + 0xc))();
      uVar3 = (**(code **)(*(int *)(*(int *)(local_8 + 0x10) + 0x18) + 0xc))(uVar3);
      fVar6 = (float10)FUN_00462010(uVar3);
      local_20 = (float)fVar6;
    }
    if (25.0 <= local_20) {
      if (local_9 != '\0') {
        fVar6 = (float10)FUN_00456080(*(float *)(local_10 + 8) + 0.25,0x3f800000);
        *(float *)(local_10 + 8) = (float)fVar6;
      }
    }
    else {
      *(undefined4 *)(local_10 + 8) = 0x3f800000;
    }
    if ((local_9 == '\0') && (cVar1 = FUN_00608460(), cVar1 == '\0')) {
      if (*(int *)(local_8 + 0x18) != 0) {
        local_a = local_9 == '\0';
        FUN_00604130(local_a);
      }
    }
    else {
      cVar1 = FUN_00608490();
      if (cVar1 != '\0') {
        FUN_006084c0();
      }
    }
  }
  FUN_00605560();
  return;
}

