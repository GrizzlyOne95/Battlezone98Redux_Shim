
void __fastcall FUN_005f8880(int param_1)

{
  char cVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  int *piVar6;
  float10 fVar7;
  float local_1c;
  
  if (*(int *)(param_1 + 8) != 0xd) {
    uVar3 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
    *(undefined4 *)(param_1 + 0x18) = uVar3;
    if (*(int *)(param_1 + 0x14) == *(int *)(param_1 + 0x24)) {
      if (((*(int *)(param_1 + 0x18) == 0) ||
          (cVar1 = FUN_004db510(*(undefined4 *)(param_1 + 0x18)), cVar1 != '\0')) ||
         (iVar4 = FUN_00417ca0(), iVar4 == 0)) {
        *(undefined4 *)(param_1 + 0xc) = 0xd;
        return;
      }
    }
    else if (*(int *)(param_1 + 0x18) == 0) {
      *(undefined4 *)(param_1 + 0xc) = 1;
      return;
    }
    uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))();
    uVar3 = FUN_00463fc0(*(undefined4 *)(param_1 + 0x10),uVar3);
    *(undefined4 *)(param_1 + 0x7c) = uVar3;
    *(undefined1 *)(param_1 + 0xc4) = 0;
    iVar4 = *(int *)(*(int *)(param_1 + 0x10) + 0x230);
    switch(*(undefined4 *)(param_1 + 8)) {
    case 2:
      uVar2 = FUN_00603ad0();
      *(undefined1 *)(param_1 + 0xc4) = uVar2;
      if (*(char *)(param_1 + 0xc4) == '\0') {
        cVar1 = FUN_006027f0();
        if (cVar1 == '\0') {
          uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))(param_1 + 0x28);
          fVar7 = (float10)FUN_00462010(uVar3);
          if ((float)fVar7 <= 10000.0) {
            uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(param_1 + 0x34);
            fVar7 = (float10)FUN_00462010(uVar3);
            if (100.0 <= (float)fVar7) {
              FUN_00601250();
            }
            else {
              *(undefined4 *)(param_1 + 0xc) = 2;
            }
          }
          else {
            *(undefined4 *)(param_1 + 0xc) = 2;
          }
        }
        else {
          *(undefined4 *)(param_1 + 0xc) = 3;
        }
      }
      else {
        *(undefined4 *)(param_1 + 0xc) = 10;
      }
      break;
    case 3:
      FUN_006029b0();
      break;
    case 4:
      cVar1 = FUN_005f8660();
      if (cVar1 == '\0') {
        uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))();
        uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(uVar3);
        fVar7 = (float10)FUN_00462010(uVar3);
        if ((float)fVar7 <= 10000.0) {
          cVar1 = FUN_006027f0();
          if (cVar1 == '\0') {
            FUN_00607db0();
          }
          else {
            *(undefined4 *)(param_1 + 0xc) = 3;
          }
        }
        else {
          puVar5 = (undefined4 *)(**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))();
          *(undefined4 *)(param_1 + 0x28) = *puVar5;
          *(undefined4 *)(param_1 + 0x2c) = puVar5[1];
          *(undefined4 *)(param_1 + 0x30) = puVar5[2];
          *(undefined4 *)(param_1 + 0xc) = 0xc;
        }
      }
      break;
    case 5:
      uVar2 = FUN_00603ad0();
      *(undefined1 *)(param_1 + 0xc4) = uVar2;
      if ((*(char *)(param_1 + 0xc4) == '\0') &&
         (cVar1 = (**(code **)(**(int **)(param_1 + 0x10) + 0x68))(), cVar1 == '\0')) {
        *(undefined4 *)(param_1 + 0xc) = 2;
      }
      else {
        FUN_00605f70();
      }
      break;
    case 6:
      cVar1 = FUN_005f83d0();
      if (cVar1 == '\0') {
        FUN_00602420();
      }
      break;
    case 8:
      uVar2 = FUN_00603ad0();
      *(undefined1 *)(param_1 + 0xc4) = uVar2;
      fVar7 = (float10)FUN_0046d040();
      if ((float)fVar7 < *(float *)(param_1 + 0x100) || (float)fVar7 == *(float *)(param_1 + 0x100))
      {
        FUN_006057e0();
      }
      else {
        *(undefined4 *)(param_1 + 0xc) = 9;
      }
      break;
    case 10:
      uVar2 = FUN_00603ad0();
      *(undefined1 *)(param_1 + 0xc4) = uVar2;
      FUN_00605f70();
      break;
    case 0xb:
      uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(param_1 + 0x28);
      fVar7 = (float10)FUN_00462010(uVar3);
      if (*(float *)(param_1 + 0x138) <= (float)fVar7) {
        cVar1 = FUN_006027f0();
        if (cVar1 == '\0') {
          uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))(param_1 + 0x28);
          fVar7 = (float10)FUN_00462010(uVar3);
          if ((float)fVar7 <= 10000.0) {
            FUN_00601250();
          }
          else {
            *(undefined4 *)(param_1 + 0xc) = 0xb;
          }
        }
        else {
          *(undefined4 *)(param_1 + 0xc) = 3;
        }
      }
      else {
        *(undefined4 *)(param_1 + 0xc) = 6;
      }
      break;
    case 0xc:
      cVar1 = FUN_005f8660();
      if (cVar1 == '\0') {
        uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))();
        uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(uVar3);
        fVar7 = (float10)FUN_00462010(uVar3);
        if (2500.0 <= (float)fVar7) {
          uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))(param_1 + 0x28);
          fVar7 = (float10)FUN_00462010(uVar3);
          if ((float)fVar7 <= 10000.0) {
            cVar1 = FUN_006027f0();
            if (cVar1 == '\0') {
              uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(param_1 + 0x34)
              ;
              fVar7 = (float10)FUN_00462010(uVar3);
              if (225.0 <= (float)fVar7) {
                FUN_00601250();
                if (*(float *)(iVar4 + 0xd0) == 1.0) {
                  *(undefined4 *)(iVar4 + 0xd4) = 1;
                }
                else {
                  *(undefined4 *)(iVar4 + 0xd4) = 0;
                }
              }
              else {
                *(undefined4 *)(param_1 + 0xc) = 0xc;
              }
            }
            else {
              *(undefined4 *)(param_1 + 0xc) = 3;
            }
          }
          else {
            *(undefined4 *)(param_1 + 0xc) = 0xc;
          }
        }
        else {
          *(undefined4 *)(param_1 + 0xc) = 4;
        }
      }
    }
    if (*(char *)(param_1 + 0xc4) == '\0') {
      FUN_00604130(0);
    }
    else {
      cVar1 = FUN_00462b60(*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0xd4),
                           0x3e99999a,0x3f800000);
      piVar6 = (int *)FUN_00477980(*(undefined4 *)(param_1 + 0x10));
      local_1c = 1e+30;
      if (piVar6 != (int *)0x0) {
        uVar3 = (**(code **)(*(int *)(*piVar6 + 0x18) + 0xc))();
        uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(uVar3);
        fVar7 = (float10)FUN_00462010(uVar3);
        local_1c = (float)fVar7;
      }
      if (25.0 <= local_1c) {
        if (cVar1 == '\0') {
          *(undefined4 *)(iVar4 + 0xcc) = 0;
        }
        else {
          *(undefined4 *)(iVar4 + 0xcc) = 0x3e800000;
        }
      }
      else {
        *(undefined4 *)(iVar4 + 0xcc) = 0x3f800000;
      }
      if ((cVar1 == '\0') && (cVar1 = FUN_00608460(), cVar1 == '\0')) {
        FUN_00604130(1);
      }
      else {
        cVar1 = FUN_00608490();
        if (cVar1 != '\0') {
          FUN_006084c0();
        }
      }
    }
    FUN_00605560();
  }
  return;
}

