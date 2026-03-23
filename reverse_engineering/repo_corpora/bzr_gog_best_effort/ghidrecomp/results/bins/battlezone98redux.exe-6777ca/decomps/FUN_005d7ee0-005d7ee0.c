
void __fastcall FUN_005d7ee0(int param_1)

{
  char cVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  undefined4 *puVar6;
  float10 fVar7;
  float local_20;
  
  if (*(int *)(param_1 + 8) != 0xd) {
    uVar3 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
    *(undefined4 *)(param_1 + 0x18) = uVar3;
    if (((*(int *)(param_1 + 0x18) == 0) ||
        (cVar1 = FUN_004db510(*(undefined4 *)(param_1 + 0x18)), cVar1 != '\0')) ||
       (iVar4 = FUN_00417ca0(), iVar4 == 0)) {
      *(undefined4 *)(param_1 + 0xc) = 0xd;
    }
    else {
      uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))();
      uVar3 = FUN_00463fc0(*(undefined4 *)(param_1 + 0x10),uVar3);
      *(undefined4 *)(param_1 + 0x7c) = uVar3;
      *(undefined1 *)(param_1 + 0xc4) = 0;
      switch(*(undefined4 *)(param_1 + 8)) {
      case 2:
        cVar1 = FUN_00603ad0();
        if (cVar1 == '\0') {
          cVar1 = FUN_006027f0();
          if (cVar1 == '\0') {
            uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))(param_1 + 0x28);
            fVar7 = (float10)FUN_00462010(uVar3);
            if ((float)fVar7 <= 10000.0) {
              uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(param_1 + 0x34)
              ;
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
          *(undefined4 *)(param_1 + 0xc) = 5;
        }
        break;
      case 3:
        FUN_006029b0();
        break;
      case 4:
        puVar6 = (undefined4 *)FUN_00477980(*(undefined4 *)(param_1 + 0x10));
        if (puVar6 == (undefined4 *)0x0) {
          *(undefined4 *)(param_1 + 0xc) = 2;
        }
        else {
          iVar4 = FUN_004714e0(puVar6[1]);
          if (iVar4 == 2) {
            *(undefined4 *)(param_1 + 0x18) = *puVar6;
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
          iVar4 = *(int *)(*(int *)(param_1 + 0x10) + 0x230);
          cVar1 = FUN_00462b60(*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0xd4),
                               0x3e99999a,0x3f800000);
          piVar5 = (int *)FUN_00477980(*(undefined4 *)(param_1 + 0x10));
          local_20 = 1e+30;
          if (piVar5 != (int *)0x0) {
            uVar3 = (**(code **)(*(int *)(*piVar5 + 0x18) + 0xc))();
            uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(uVar3);
            fVar7 = (float10)FUN_00462010(uVar3);
            local_20 = (float)fVar7;
          }
          if (25.0 <= local_20) {
            if (cVar1 != '\0') {
              fVar7 = (float10)FUN_00456080(*(float *)(iVar4 + 0xcc) + 0.25,0x3f800000);
              *(float *)(iVar4 + 0xcc) = (float)fVar7;
            }
          }
          else {
            *(undefined4 *)(iVar4 + 0xcc) = 0x3f800000;
          }
          if ((cVar1 == '\0') && (cVar2 = FUN_00608460(), cVar2 == '\0')) {
            FUN_00604130(1);
          }
          else {
            cVar2 = FUN_00608490();
            if (cVar2 != '\0') {
              FUN_006084c0();
            }
          }
          FUN_00604130(cVar1 == '\0');
        }
      }
    }
  }
  return;
}

