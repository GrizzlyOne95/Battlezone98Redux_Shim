
void __fastcall FUN_007d3380(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 local_c;
  
  FUN_007d14b0(*(undefined4 *)(param_1 + 0xec),*(undefined4 *)(param_1 + 0xf0),
               *(undefined4 *)(param_1 + 0xf4),*(undefined4 *)(param_1 + 0xf8));
  if (*(int *)(param_1 + 0x120) != 0) {
    (**(code **)(**(int **)(param_1 + 0x120) + 0x118))(0);
    FUN_007d2e20();
    (**(code **)(**(int **)(param_1 + 0x120) + 0x16c))();
  }
  local_c = 0;
  while( true ) {
    iVar1 = size();
    if (iVar1 <= local_c) break;
    puVar2 = (undefined4 *)FUN_004200d0(local_c);
    (**(code **)(*(int *)*puVar2 + 0x30))();
    local_c = local_c + 1;
  }
  return;
}

