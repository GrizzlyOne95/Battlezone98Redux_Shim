
undefined1 __fastcall FUN_005c16a0(int param_1)

{
  float fVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  float10 fVar5;
  double dVar6;
  
  iVar3 = FUN_0045c4d0();
  iVar4 = (*(code *)**(undefined4 **)(*(int *)(param_1 + 0x10) + 0x18))();
  fVar1 = *(float *)(iVar4 + 0x34c);
  fVar5 = (float10)FUN_007855e0(*(undefined8 *)(iVar3 + 0x28),*(undefined8 *)(iVar3 + 0x38));
  dVar6 = (double)((float)fVar5 + fVar1) - *(double *)(iVar3 + 0x30);
  *(double *)(iVar3 + 0x30) = *(double *)(iVar3 + 0x30) + dVar6;
  if (*(int *)(param_1 + 0xb4) != 0) {
    *(double *)(*(int *)(param_1 + 0xb4) + 0x58) =
         *(double *)(*(int *)(param_1 + 0xb4) + 0x58) + dVar6;
  }
  uVar2 = FUN_00603ad0();
  *(double *)(iVar3 + 0x30) = *(double *)(iVar3 + 0x30) - dVar6;
  if (*(int *)(param_1 + 0xb4) != 0) {
    *(double *)(*(int *)(param_1 + 0xb4) + 0x58) =
         *(double *)(*(int *)(param_1 + 0xb4) + 0x58) - dVar6;
  }
  return uVar2;
}

