
void __fastcall FUN_005a5c00(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float local_20;
  
  if (*(int *)(param_1 + 8) != 0xd) {
    uVar2 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
    *(undefined4 *)(param_1 + 0x18) = uVar2;
    if (((*(int *)(param_1 + 0x18) == 0) ||
        (cVar1 = FUN_004db510(*(undefined4 *)(param_1 + 0x18)), cVar1 != '\0')) ||
       (iVar3 = FUN_00417ca0(), iVar3 == 0)) {
      *(undefined4 *)(param_1 + 0xc) = 0xd;
    }
    else {
      uVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))();
      uVar2 = FUN_00463fc0(*(undefined4 *)(param_1 + 0x10),uVar2);
      *(undefined4 *)(param_1 + 0x7c) = uVar2;
      *(undefined1 *)(param_1 + 0xc4) = 0;
      switch(*(undefined4 *)(param_1 + 8)) {
      case 2:
        cVar1 = FUN_00603ad0();
        if (cVar1 == '\0') {
          cVar1 = FUN_006027f0();
          if (cVar1 == '\0') {
            uVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))(param_1 + 0x28);
            fVar6 = (float10)FUN_00462010(uVar2);
            if ((float)fVar6 <= 10000.0) {
              uVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(param_1 + 0x34)
              ;
              fVar6 = (float10)FUN_00462010(uVar2);
              if (100.0 <= (float)fVar6) {
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
          *(undefined4 *)(param_1 + 0xc) = 5;
        }
        break;
      case 3:
        FUN_006029b0();
        break;
      case 4:
        puVar5 = (undefined4 *)FUN_00477980(*(undefined4 *)(param_1 + 0x10));
        if (puVar5 == (undefined4 *)0x0) {
          *(undefined4 *)(param_1 + 0xc) = 2;
        }
        else {
          iVar3 = FUN_004714e0(puVar5[1]);
          if (iVar3 == 2) {
            *(undefined4 *)(param_1 + 0x18) = *puVar5;
            FUN_00607db0();
          }
          else {
            *(undefined4 *)(param_1 + 0xc) = 2;
          }
        }
        break;
      case 5:
        cVar1 = FUN_00603ad0();
        if (cVar1 == '\0') {
          *(undefined4 *)(param_1 + 0xc) = 2;
        }
        else {
          FUN_00605f70();
          iVar3 = *(int *)(*(int *)(param_1 + 0x10) + 0x230);
          cVar1 = FUN_00462b60(*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0xd4),
                               0x3e99999a,0x3f800000);
          piVar4 = (int *)FUN_00477980(*(undefined4 *)(param_1 + 0x10));
          local_20 = 1e+30;
          if (piVar4 != (int *)0x0) {
            uVar2 = (**(code **)(*(int *)(*piVar4 + 0x18) + 0xc))();
            uVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(uVar2);
            fVar6 = (float10)FUN_00462010(uVar2);
            local_20 = (float)fVar6;
          }
          if (25.0 <= local_20) {
            if (cVar1 != '\0') {
              fVar6 = (float10)FUN_00456080(*(float *)(iVar3 + 0xcc) + 0.25,0x3f800000);
              *(float *)(iVar3 + 0xcc) = (float)fVar6;
            }
          }
          else {
            *(undefined4 *)(iVar3 + 0xcc) = 0x3f800000;
          }
          FUN_00604130(cVar1 == '\0');
          cVar1 = FUN_00608490();
          if (cVar1 != '\0') {
            FUN_006084c0();
          }
        }
      }
    }
  }
  return;
}

