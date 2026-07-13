
void __fastcall FUN_007c1920(int param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint local_c;
  
  local_c = 0;
  while( true ) {
    uVar2 = size();
    if (uVar2 <= local_c) break;
    puVar3 = (undefined4 *)FUN_004200d0(local_c);
    (**(code **)(*(int *)*puVar3 + 0x34))();
    local_c = local_c + 1;
  }
  if (*(int *)(param_1 + 0x148) != 0) {
    cVar1 = FUN_007d3d60();
    if (cVar1 != '\0') {
      FUN_007c12a0();
    }
  }
  return;
}

