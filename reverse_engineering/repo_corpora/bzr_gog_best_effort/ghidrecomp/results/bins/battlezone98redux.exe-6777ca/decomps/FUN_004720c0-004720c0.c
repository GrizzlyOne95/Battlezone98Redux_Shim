
void __fastcall FUN_004720c0(int param_1)

{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  float10 fVar5;
  
  if (*(int *)(param_1 + 8) != 0xd) {
    uVar3 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
    *(undefined4 *)(param_1 + 0x18) = uVar3;
    if (*(int *)(param_1 + 0x18) == 0) {
      *(undefined4 *)(param_1 + 0xc) = 0xd;
    }
    else {
      uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))();
      uVar3 = FUN_00463fc0(*(undefined4 *)(param_1 + 0x10),uVar3);
      *(undefined4 *)(param_1 + 0x7c) = uVar3;
      iVar1 = *(int *)(param_1 + 8);
      if (iVar1 == 2) {
        if (*(int *)(*(int *)(param_1 + 0x10) + 0x300) < 1) {
          *(undefined4 *)(param_1 + 0xc) = 0xd;
        }
        else {
          uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))();
          uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(uVar3);
          fVar5 = (float10)FUN_00462010(uVar3);
          if (5625.0 <= (float)fVar5) {
            cVar2 = FUN_006027f0();
            if (cVar2 == '\0') {
              uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))(param_1 + 0x28)
              ;
              fVar5 = (float10)FUN_00462010(uVar3);
              if ((float)fVar5 <= 10000.0) {
                uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))
                                  (param_1 + 0x34);
                fVar5 = (float10)FUN_00462010(uVar3);
                if (100.0 <= (float)fVar5) {
                  FUN_00601250();
                }
                else {
                  puVar4 = (undefined4 *)
                           (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))();
                  *(undefined4 *)(param_1 + 0x28) = *puVar4;
                  *(undefined4 *)(param_1 + 0x2c) = puVar4[1];
                  *(undefined4 *)(param_1 + 0x30) = puVar4[2];
                  *(undefined4 *)(param_1 + 0xc) = 2;
                }
              }
              else {
                puVar4 = (undefined4 *)
                         (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))();
                *(undefined4 *)(param_1 + 0x28) = *puVar4;
                *(undefined4 *)(param_1 + 0x2c) = puVar4[1];
                *(undefined4 *)(param_1 + 0x30) = puVar4[2];
                *(undefined4 *)(param_1 + 0xc) = 2;
              }
            }
            else {
              *(undefined4 *)(param_1 + 0xc) = 3;
            }
          }
          else {
            (**(code **)(**(int **)(param_1 + 0x10) + 0x60))();
            *(undefined4 *)(param_1 + 0xc) = 5;
          }
        }
      }
      else if (iVar1 == 3) {
        FUN_006029b0();
      }
      else if (iVar1 == 5) {
        if (*(int *)(*(int *)(param_1 + 0x10) + 0x300) < 1) {
          *(undefined4 *)(param_1 + 0xc) = 0xd;
        }
        else {
          iVar1 = *(int *)(*(int *)(param_1 + 0x10) + 0x230);
          *(undefined4 *)(iVar1 + 0xd0) = 0;
          *(undefined4 *)(iVar1 + 0xc4) = 0;
          *(undefined4 *)(iVar1 + 200) = 0;
          *(undefined4 *)(iVar1 + 0xd4) = 0;
        }
      }
    }
  }
  return;
}

