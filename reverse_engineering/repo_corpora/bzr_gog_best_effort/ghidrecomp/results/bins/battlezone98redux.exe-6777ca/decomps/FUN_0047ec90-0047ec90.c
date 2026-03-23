
int * FUN_0047ec90(int param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  int *local_c;
  
  local_c = (int *)FUN_004e0f70(*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc));
  if (local_c == (int *)0x0) {
    FUN_007d6a70("Building::Init - bad building class (%.8s)\n",param_1 + 8);
    local_c = &DAT_0094fb10;
  }
  piVar2 = (int *)(**(code **)(*local_c + 4))(param_1);
  puVar1 = *(undefined4 **)(param_1 + 0x88);
  *puVar1 = piVar2;
  puVar1[1] = param_1;
  iVar3 = FUN_0062e050(param_1);
  piVar2[0x8a] = iVar3;
  uVar4 = FUN_0047e9a0(param_1);
  (**(code **)(*piVar2 + 4))(uVar4);
  return piVar2;
}

