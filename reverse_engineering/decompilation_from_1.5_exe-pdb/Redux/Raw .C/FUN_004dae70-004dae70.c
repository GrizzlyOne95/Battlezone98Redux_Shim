
void __fastcall FUN_004dae70(int param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  int local_c;
  
  if (*(int *)(*(int *)(param_1 + 0xd8) + 0x9c) != 0) {
    puVar1 = *(undefined4 **)(*(int *)(param_1 + 0xd8) + 0x9c);
    if (puVar1 != (undefined4 *)0x0) {
      (**(code **)*puVar1)(1);
    }
    *(undefined4 *)(*(int *)(param_1 + 0xd8) + 0x9c) = 0;
  }
  if (*(int *)(*(int *)(param_1 + 0xd8) + 0xa0) != 0) {
    puVar1 = *(undefined4 **)(*(int *)(param_1 + 0xd8) + 0xa0);
    if (puVar1 != (undefined4 *)0x0) {
      (**(code **)*puVar1)(1);
    }
    *(undefined4 *)(*(int *)(param_1 + 0xd8) + 0xa0) = 0;
  }
  if (*(int *)(*(int *)(param_1 + 0xd8) + 0x94) != 0) {
    FUN_0067e550(*(undefined4 *)(*(int *)(param_1 + 0xd8) + 0x98));
  }
  if (*(int *)(*(int *)(param_1 + 0xd8) + 0xc0) != 0) {
    FUN_0067e550(*(undefined4 *)(*(int *)(param_1 + 0xd8) + 200));
  }
  piVar2 = (int *)FUN_0045ca50();
  if (piVar2 != (int *)0x0) {
    (**(code **)(*piVar2 + 0x20))(param_1 + -0x18);
  }
  FUN_004d4b40(param_1 + -0x18);
  FUN_0062de40(*(undefined4 *)(param_1 + 0xdc),0x200);
  FUN_004b7ab0();
  if (*(int *)(param_1 + 0xe4) == 1) {
    *(undefined4 *)(param_1 + 0xe4) = 0;
  }
  else if ((*(int *)(param_1 + 0xe4) != 0) &&
          (*(undefined4 **)(param_1 + 0xe4) != (undefined4 *)0x0)) {
    (**(code **)**(undefined4 **)(param_1 + 0xe4))(1);
  }
  if (*(int *)(param_1 + 0x188) != 0) {
    for (local_c = 0; local_c < 5; local_c = local_c + 1) {
      iVar3 = FUN_00417f60(local_c);
      if (iVar3 != 0) {
        FUN_004a77a0(local_c,0);
        FUN_00611590();
      }
    }
    operator_delete(*(void **)(param_1 + 0x188));
    *(undefined4 *)(param_1 + 0x188) = 0;
  }
  (**(code **)(*(int *)(param_1 + -0x18) + 8))();
  if (*(int *)(param_1 + 0xd8) != 0) {
    FUN_0062c7d0(*(undefined4 *)(param_1 + 0xd8));
  }
  FUN_0062d200(*(undefined4 *)(param_1 + 0xdc),"fun3d\\GameObject.cpp");
  return;
}

