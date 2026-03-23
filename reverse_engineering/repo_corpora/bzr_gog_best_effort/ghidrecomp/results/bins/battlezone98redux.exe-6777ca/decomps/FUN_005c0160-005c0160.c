
void __fastcall FUN_005c0160(int param_1)

{
  int iVar1;
  char cVar2;
  char cVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  float10 fVar6;
  
  if (*(int *)(param_1 + 8) != 0xd) {
    uVar4 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
    *(undefined4 *)(param_1 + 0x18) = uVar4;
    if (*(int *)(param_1 + 0x18) == 0) {
      *(undefined4 *)(param_1 + 0xc) = 0xd;
    }
    else {
      uVar4 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))();
      uVar4 = FUN_00463fc0(*(undefined4 *)(param_1 + 0x10),uVar4);
      *(undefined4 *)(param_1 + 0x7c) = uVar4;
      cVar2 = FUN_005bf8d0(*(undefined4 *)(param_1 + 0x10));
      if ((cVar2 == '\0') && (*(char *)(param_1 + 0x1c) != '\0')) {
        FUN_00602920();
      }
      iVar1 = *(int *)(param_1 + 8);
      if (iVar1 == 2) {
        uVar4 = (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))();
        uVar4 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(uVar4);
        fVar6 = (float10)FUN_00462010(uVar4);
        if (5625.0 <= (float)fVar6) {
          if (cVar2 == '\0') {
            cVar3 = FUN_006027f0();
            if (cVar3 == '\0') {
              FUN_00601250();
            }
            else {
              *(undefined4 *)(param_1 + 0xc) = 3;
            }
          }
          else {
            FUN_00602420();
          }
        }
        else {
          *(undefined4 *)(param_1 + 0xc) = 5;
        }
      }
      else if (iVar1 == 3) {
        FUN_006029b0();
      }
      else if (iVar1 == 5) {
        uVar4 = (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))();
        uVar4 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(uVar4);
        fVar6 = (float10)FUN_00462010(uVar4);
        if ((float)fVar6 <= 10000.0) {
          cVar3 = FUN_005bf890(*(undefined4 *)(param_1 + 0x10));
          if (cVar3 == '\0') {
            FUN_00602420();
          }
          else {
            FUN_005c0380();
          }
        }
        else {
          puVar5 = (undefined4 *)(**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))();
          *(undefined4 *)(param_1 + 0x28) = *puVar5;
          *(undefined4 *)(param_1 + 0x2c) = puVar5[1];
          *(undefined4 *)(param_1 + 0x30) = puVar5[2];
          *(undefined4 *)(param_1 + 0xc) = 2;
        }
      }
      *(char *)(param_1 + 0x1c) = cVar2;
    }
  }
  return;
}

