
void __fastcall FUN_004b1250(int param_1)

{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  float10 fVar5;
  float10 fVar6;
  float fVar7;
  
  uVar3 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
  *(undefined4 *)(param_1 + 0x18) = uVar3;
  if (*(int *)(param_1 + 0x18) == 0) {
    *(undefined4 *)(param_1 + 0xc) = 0xd;
    *(undefined4 *)(param_1 + 0x14) = 0;
  }
  else {
    fVar5 = (float10)FUN_00462470();
    fVar6 = (float10)FUN_00462470();
    fVar7 = (float)fVar5 + 20.0 + (float)fVar6;
    *(undefined4 *)(param_1 + 0x80) = 0;
    uVar3 = FUN_004643e0(*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x80));
    *(undefined4 *)(param_1 + 0x7c) = uVar3;
    iVar1 = *(int *)(param_1 + 8);
    if (iVar1 == 2) {
      uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(param_1 + 0x28);
      fVar5 = (float10)FUN_00462010(uVar3);
      if ((fVar7 - 10.0) * (fVar7 - 10.0) <= (float)fVar5) {
        cVar2 = FUN_006027f0();
        if (cVar2 == '\0') {
          FUN_00601250();
        }
        else {
          *(undefined4 *)(param_1 + 0xc) = 3;
        }
      }
      else {
        *(undefined4 *)(param_1 + 0xc) = 6;
      }
    }
    else if (iVar1 == 3) {
      FUN_006029b0();
    }
    else if (iVar1 == 6) {
      FUN_004b1470();
      uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))();
      uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(uVar3);
      fVar5 = (float10)FUN_00462010(uVar3);
      if ((float)fVar5 <= fVar7 * fVar7) {
        fVar5 = (float10)FUN_00822d80();
        if (*(float *)(param_1 + 0x120) <= (float)fVar5 &&
            (float)fVar5 != *(float *)(param_1 + 0x120)) {
          *(undefined4 *)(param_1 + 0xc) = 6;
        }
      }
      else {
        puVar4 = (undefined4 *)(**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))();
        *(undefined4 *)(param_1 + 0x28) = *puVar4;
        *(undefined4 *)(param_1 + 0x2c) = puVar4[1];
        *(undefined4 *)(param_1 + 0x30) = puVar4[2];
        *(undefined4 *)(param_1 + 0xc) = 2;
      }
    }
  }
  return;
}

