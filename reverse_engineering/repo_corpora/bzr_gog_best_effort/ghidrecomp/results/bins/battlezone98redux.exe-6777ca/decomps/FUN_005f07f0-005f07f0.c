
void __fastcall FUN_005f07f0(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined8 uVar4;
  
  iVar1 = FUN_004625b0();
  if (*(int *)(param_1 + 0x2c8) != iVar1) {
    FUN_005f08c0();
    uVar2 = FUN_004625b0();
    *(undefined4 *)(param_1 + 0x2c8) = uVar2;
    puVar3 = (undefined4 *)(**(code **)(*(int *)(param_1 + 0x18) + 0xc))();
    uVar4 = FUN_0045c460(*puVar3,puVar3[1],puVar3[2]);
    *(undefined8 *)(param_1 + 0x2cc) = uVar4;
    FUN_00469900(*(undefined4 *)(param_1 + 0x2cc),*(undefined4 *)(param_1 + 0x2d0),0x43480000,
                 *(undefined4 *)(param_1 + 0x2c8),1);
  }
  return;
}

