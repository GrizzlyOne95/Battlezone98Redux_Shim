
void __fastcall FUN_005b9d90(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  float10 fVar4;
  
  if (*(int *)(param_1 + 8) != 0xd) {
    uVar2 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
    *(undefined4 *)(param_1 + 0x18) = uVar2;
    if (*(int *)(param_1 + 0x18) == 0) {
      *(undefined4 *)(param_1 + 0xc) = 0xd;
    }
    else {
      uVar2 = FUN_004643e0(*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x18));
      *(undefined4 *)(param_1 + 0x7c) = uVar2;
      uVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))();
      uVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(uVar2);
      fVar4 = (float10)FUN_00462010(uVar2);
      switch(*(undefined4 *)(param_1 + 8)) {
      case 1:
        FUN_00602420();
        break;
      case 2:
        uVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))();
        uVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(uVar2);
        fVar4 = (float10)FUN_00462010(uVar2);
        if (2500.0 <= (float)fVar4) {
          uVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))(param_1 + 0x28);
          fVar4 = (float10)FUN_00462010(uVar2);
          if ((float)fVar4 <= 10000.0) {
            cVar1 = FUN_006027f0();
            if (cVar1 == '\0') {
              uVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(param_1 + 0x34)
              ;
              fVar4 = (float10)FUN_00462010(uVar2);
              if (225.0 <= (float)fVar4) {
                FUN_00601250();
              }
              else {
                *(undefined4 *)(param_1 + 0xc) = 2;
                puVar3 = (undefined4 *)
                         (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))();
                *(undefined4 *)(param_1 + 0x28) = *puVar3;
                *(undefined4 *)(param_1 + 0x2c) = puVar3[1];
                *(undefined4 *)(param_1 + 0x30) = puVar3[2];
              }
            }
            else {
              *(undefined4 *)(param_1 + 0xc) = 3;
            }
          }
          else {
            *(undefined4 *)(param_1 + 0xc) = 2;
            puVar3 = (undefined4 *)(**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))();
            *(undefined4 *)(param_1 + 0x28) = *puVar3;
            *(undefined4 *)(param_1 + 0x2c) = puVar3[1];
            *(undefined4 *)(param_1 + 0x30) = puVar3[2];
          }
        }
        else {
          *(undefined4 *)(param_1 + 0xc) = 4;
        }
        break;
      case 3:
        FUN_006029b0();
        break;
      case 4:
        if (900.0 <= (float)fVar4) {
          uVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))();
          uVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(uVar2);
          fVar4 = (float10)FUN_00462010(uVar2);
          if ((float)fVar4 <= 10000.0) {
            cVar1 = FUN_006027f0();
            if (cVar1 == '\0') {
              FUN_00607db0();
            }
            else {
              *(undefined4 *)(param_1 + 0xc) = 3;
            }
          }
          else {
            puVar3 = (undefined4 *)(**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))();
            *(undefined4 *)(param_1 + 0x28) = *puVar3;
            *(undefined4 *)(param_1 + 0x2c) = puVar3[1];
            *(undefined4 *)(param_1 + 0x30) = puVar3[2];
            *(undefined4 *)(param_1 + 0xc) = 2;
          }
        }
        else {
          fVar4 = (float10)FUN_00822da0();
          *(float *)(param_1 + 0x120) = (float)fVar4 + 1.0;
          *(undefined4 *)(param_1 + 0xc) = 6;
        }
        break;
      case 6:
        fVar4 = (float10)FUN_00822da0();
        if ((float)fVar4 < *(float *)(param_1 + 0x120) ||
            (float)fVar4 == *(float *)(param_1 + 0x120)) {
          FUN_00602420();
        }
        else {
          *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x10) + 0x230) + 0xe4) = 1;
          *(undefined4 *)(param_1 + 0xc) = 0xd;
        }
      }
    }
  }
  return;
}

