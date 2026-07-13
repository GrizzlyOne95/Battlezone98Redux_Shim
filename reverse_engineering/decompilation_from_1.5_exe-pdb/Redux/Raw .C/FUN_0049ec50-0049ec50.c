
uint __fastcall FUN_0049ec50(uint param_1)

{
  char cVar1;
  bool bVar2;
  uint uVar3;
  undefined4 uVar4;
  float10 fVar5;
  
  cVar1 = (**(code **)(**(int **)(param_1 + 0x10) + 0x6c))();
  if (cVar1 == '\0') {
    cVar1 = (**(code **)(**(int **)(param_1 + 0x10) + 0x68))();
    uVar3 = 0;
    if (cVar1 != '\0') {
      if (*(int *)(param_1 + 0x15c) == 0) {
        FUN_0049cd50(*(undefined4 *)(param_1 + 0x18));
        *(undefined4 *)(param_1 + 0x15c) = 1;
      }
      uVar3 = param_1;
      if (*(int *)(param_1 + 0x15c) == 1) {
        fVar5 = (float10)FUN_00822d60();
        FUN_0049cdf0((float)fVar5);
        bVar2 = Concurrency::_Order_node_base<enum_Concurrency::agent_status>::has_value
                          (*(_Order_node_base<enum_Concurrency::agent_status> **)(param_1 + 0x10));
        uVar3 = (uint)bVar2;
        if (bVar2 == 0) {
          *(undefined4 *)(param_1 + 0x15c) = 2;
          (**(code **)(**(int **)(param_1 + 0x10) + 100))();
          uVar4 = FUN_00462380();
          FUN_0049dae0(uVar4);
          *(undefined4 *)(param_1 + 0xc) = 0xd;
          uVar3 = param_1;
        }
      }
    }
  }
  else {
    uVar3 = (**(code **)(**(int **)(param_1 + 0x10) + 0x60))();
    *(float *)(param_1 + 0x14c) = *(float *)(param_1 + 0x14c) * 2.0;
  }
  return uVar3 & 0xffffff00;
}

