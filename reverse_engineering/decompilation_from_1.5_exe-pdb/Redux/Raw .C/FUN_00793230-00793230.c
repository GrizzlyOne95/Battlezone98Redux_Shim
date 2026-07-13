
void __fastcall FUN_00793230(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  int local_c;
  
  local_c = 0;
  while( true ) {
    iVar2 = size();
    if (iVar2 <= local_c) break;
    puVar3 = (undefined4 *)FUN_004200d0(local_c);
    (**(code **)(*(int *)*puVar3 + 0x34))();
    local_c = local_c + 1;
  }
  if (*(int *)(param_1 + 0x14c) != 0) {
    cVar1 = FUN_007d3d60();
    if (cVar1 != '\0') {
      FUN_00792d30();
    }
  }
  return;
}

