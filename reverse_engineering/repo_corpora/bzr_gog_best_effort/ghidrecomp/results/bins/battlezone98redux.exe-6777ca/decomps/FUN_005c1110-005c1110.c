
void __fastcall FUN_005c1110(int param_1)

{
  int iVar1;
  char cVar2;
  char cVar3;
  undefined1 uVar4;
  undefined4 uVar5;
  int iVar6;
  int *piVar7;
  float10 fVar8;
  float fVar9;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x10) + 0x230);
  if (*(int *)(param_1 + 8) != 0xd) {
    uVar5 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
    *(undefined4 *)(param_1 + 0x18) = uVar5;
    if (((*(int *)(param_1 + 0x18) == 0) ||
        (cVar2 = FUN_004db510(*(undefined4 *)(param_1 + 0x18)), cVar2 != '\0')) ||
       (iVar6 = FUN_00417ca0(), iVar6 == 0)) {
      *(undefined4 *)(param_1 + 0xc) = 0xd;
    }
    else {
      uVar5 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))();
      uVar5 = FUN_00463fc0(*(undefined4 *)(param_1 + 0x10),uVar5);
      *(undefined4 *)(param_1 + 0x7c) = uVar5;
      if (*(int *)(param_1 + 0x7c) == *(int *)(param_1 + 0x18)) {
        *(undefined4 *)(param_1 + 0x7c) = 0;
      }
      cVar2 = FUN_005bf8d0(*(undefined4 *)(param_1 + 0x10));
      if ((cVar2 == '\0') && (*(char *)(param_1 + 0x1c) != '\0')) {
        FUN_00602920();
      }
      cVar3 = FUN_005bf890(*(undefined4 *)(param_1 + 0x10));
      if (cVar3 == '\0') {
        uVar4 = FUN_005c16a0();
        *(undefined1 *)(param_1 + 0xc4) = uVar4;
      }
      else {
        uVar4 = FUN_00603ad0();
        *(undefined1 *)(param_1 + 0xc4) = uVar4;
      }
      switch(*(undefined4 *)(param_1 + 8)) {
      case 2:
      case 0xf:
        cVar3 = FUN_005bf8b0(*(undefined4 *)(param_1 + 0x10));
        if (cVar3 == '\0') {
          FUN_005c0ba0();
        }
        else if (((*(int *)(param_1 + 8) != 2) || (*(char *)(param_1 + 0xc4) == '\0')) ||
                (fVar9 = *(float *)(param_1 + 0xa0) * 0.75,
                fVar9 < *(float *)(param_1 + 0xd4) || fVar9 == *(float *)(param_1 + 0xd4))) {
          uVar5 = (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))(param_1 + 0x28);
          fVar8 = (float10)FUN_00462010(uVar5);
          if ((float)fVar8 <= 10000.0) {
            uVar5 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(param_1 + 0x34);
            fVar8 = (float10)FUN_00462010(uVar5);
            if (400.0 <= (float)fVar8) {
              FUN_00601250();
            }
            else {
              *(undefined4 *)(param_1 + 0xc) = 2;
            }
          }
          else {
            *(undefined4 *)(param_1 + 0xc) = 0xf;
          }
        }
        else {
          *(undefined4 *)(param_1 + 0xc) = 5;
        }
        break;
      case 5:
        cVar3 = FUN_005bf8b0(*(undefined4 *)(param_1 + 0x10));
        if (cVar3 == '\0') {
          if (*(float *)(param_1 + 0xd4) <= *(float *)(param_1 + 0xa0) * 1.1) {
            cVar3 = FUN_005bf890(*(undefined4 *)(param_1 + 0x10));
            if (cVar3 == '\0') {
              FUN_005c0ba0();
              fVar8 = (float10)FUN_00822d80();
              *(float *)(param_1 + 0x120) = (float)fVar8 + 15.0;
              fVar8 = (float10)FUN_00822d80();
              *(float *)(param_1 + 0x108) = (float)fVar8 + 3.0;
            }
            else {
              fVar8 = (float10)FUN_00822d80();
              if ((float)fVar8 < *(float *)(param_1 + 0x120) ||
                  (float)fVar8 == *(float *)(param_1 + 0x120)) {
                FUN_006057e0();
                cVar3 = FUN_00462b60(*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0xd4)
                                     ,0x3e99999a,0x3f800000);
                if (cVar3 != '\0') {
                  *(undefined4 *)(iVar1 + 0xcc) = 0x3e800000;
                }
                if ((*(char *)(param_1 + 0xc4) == '\0') || (cVar3 != '\0')) {
                  FUN_00604130(0);
                }
                else {
                  cVar3 = FUN_00608460();
                  if (cVar3 == '\0') {
                    FUN_00604130(1);
                    fVar8 = (float10)FUN_00822d80();
                    *(float *)(param_1 + 0x108) = (float)fVar8 + 3.0;
                  }
                  else {
                    cVar3 = FUN_00608490();
                    if (cVar3 != '\0') {
                      FUN_006084c0();
                    }
                  }
                }
                fVar8 = (float10)FUN_00822d80();
                if (*(float *)(param_1 + 0x108) <= (float)fVar8 &&
                    (float)fVar8 != *(float *)(param_1 + 0x108)) {
                  *(undefined4 *)(param_1 + 0xc) = 2;
                }
              }
              else {
                *(undefined4 *)(param_1 + 0xc) = 0xe;
              }
            }
          }
          else {
            *(undefined4 *)(param_1 + 0xc) = 0xf;
          }
        }
        else {
          piVar7 = (int *)FUN_00477980(*(undefined4 *)(param_1 + 0x10));
          if (piVar7 == (int *)0x0) {
            FUN_005bf870(*(undefined4 *)(param_1 + 0x10));
          }
          else {
            FUN_00605f70();
            uVar5 = (**(code **)(*(int *)(*piVar7 + 0x18) + 0xc))();
            uVar5 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(uVar5);
            fVar8 = (float10)FUN_00462010(uVar5);
            if (1600.0 <= (float)fVar8) {
              FUN_005bf870(*(undefined4 *)(param_1 + 0x10));
            }
            else {
              *(undefined4 *)(iVar1 + 0xcc) = 0x3f800000;
            }
          }
        }
        break;
      case 0xe:
        cVar3 = FUN_005bf8b0(*(undefined4 *)(param_1 + 0x10));
        if (cVar3 == '\0') {
          FUN_005c0ba0();
        }
        else {
          if (*(char *)(param_1 + 0x1c) != '\0') {
            fVar8 = (float10)FUN_00822d80();
            *(float *)(param_1 + 0x120) = (float)fVar8 + 5.0;
          }
          fVar8 = (float10)FUN_00822d80();
          if ((float)fVar8 < *(float *)(param_1 + 0x120) ||
              (float)fVar8 == *(float *)(param_1 + 0x120)) {
            FUN_005c0ba0();
          }
          else {
            *(undefined4 *)(param_1 + 0xc) = 0xf;
          }
        }
      }
      *(char *)(param_1 + 0x1c) = cVar2;
    }
  }
  return;
}

