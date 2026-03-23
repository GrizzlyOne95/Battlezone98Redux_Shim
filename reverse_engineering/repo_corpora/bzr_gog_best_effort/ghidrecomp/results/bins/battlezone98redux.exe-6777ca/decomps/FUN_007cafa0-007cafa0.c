
void __thiscall FUN_007cafa0(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  char cVar3;
  uint uVar4;
  undefined4 *puVar5;
  int iVar6;
  uint local_c;
  
  local_c = 0;
  while( true ) {
    uVar4 = size();
    if (uVar4 <= local_c) break;
    puVar5 = (undefined4 *)FUN_004200d0(local_c);
    (**(code **)(*(int *)*puVar5 + 0x24))(0);
    local_c = local_c + 1;
  }
  *(undefined4 *)(param_1 + 0x14c) = param_2;
  cVar3 = FUN_007d3360();
  if ((cVar3 != '\0') && (*(int *)(param_1 + 0x14c) != -1)) {
    iVar1 = *(int *)(param_1 + 0x14c);
    iVar2 = *(int *)(param_1 + 0x150);
    iVar6 = size();
    if ((iVar1 - iVar2 < iVar6) && (*(int *)(param_1 + 0x150) <= *(int *)(param_1 + 0x14c))) {
      puVar5 = (undefined4 *)FUN_004200d0(*(int *)(param_1 + 0x14c) - *(int *)(param_1 + 0x150));
      (**(code **)(*(int *)*puVar5 + 0x24))(1);
    }
  }
  return;
}

