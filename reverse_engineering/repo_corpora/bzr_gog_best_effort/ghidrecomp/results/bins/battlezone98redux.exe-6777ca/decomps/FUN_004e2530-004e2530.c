
void __fastcall FUN_004e2530(int param_1)

{
  char cVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined1 local_5;
  
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
      iVar4 = FUN_00462510();
      if (3 < iVar4) {
        *(undefined4 *)(param_1 + 0xf4) = 0x3f800000;
        *(undefined4 *)(param_1 + 0xf8) = 0x3f800000;
      }
      iVar4 = *(int *)(param_1 + 8);
      if (iVar4 == 2) {
        cVar1 = FUN_00603ad0();
        if (cVar1 == '\0') {
          cVar1 = FUN_006027f0();
          if (cVar1 == '\0') {
            uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))(param_1 + 0x28);
            fVar6 = (float10)FUN_00462010(uVar3);
            if ((float)fVar6 <= 10000.0) {
              uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(param_1 + 0x34)
              ;
              fVar6 = (float10)FUN_00462010(uVar3);
              if (100.0 <= (float)fVar6) {
                FUN_00601250();
              }
              else {
                puVar5 = (undefined4 *)
                         (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))();
                *(undefined4 *)(param_1 + 0x28) = *puVar5;
                *(undefined4 *)(param_1 + 0x2c) = puVar5[1];
                *(undefined4 *)(param_1 + 0x30) = puVar5[2];
                *(undefined4 *)(param_1 + 0xc) = 2;
              }
            }
            else {
              puVar5 = (undefined4 *)
                       (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))();
              *(undefined4 *)(param_1 + 0x28) = *puVar5;
              *(undefined4 *)(param_1 + 0x2c) = puVar5[1];
              *(undefined4 *)(param_1 + 0x30) = puVar5[2];
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
      }
      else if (iVar4 == 3) {
        FUN_006029b0();
      }
      else if (iVar4 == 5) {
        uVar2 = FUN_00603ad0();
        *(undefined1 *)(param_1 + 0xc4) = uVar2;
        if (*(char *)(param_1 + 0xc4) == '\0') {
          puVar5 = (undefined4 *)(**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))();
          *(undefined4 *)(param_1 + 0x28) = *puVar5;
          *(undefined4 *)(param_1 + 0x2c) = puVar5[1];
          *(undefined4 *)(param_1 + 0x30) = puVar5[2];
          *(undefined4 *)(param_1 + 0xc) = 2;
        }
        else {
          FUN_00605f70();
          cVar1 = FUN_00608460();
          if (cVar1 == '\0') {
            if ((*(char *)(param_1 + 0xc4) == '\0') ||
               (cVar1 = FUN_00462b60(*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0xd4)
                                     ,0x3e99999a,0x3f800000), cVar1 != '\0')) {
              local_5 = 0;
            }
            else {
              local_5 = 1;
            }
            FUN_00604130(local_5);
          }
          else {
            cVar1 = FUN_00608490();
            if (cVar1 != '\0') {
              FUN_006084c0();
            }
          }
        }
      }
    }
  }
  return;
}

