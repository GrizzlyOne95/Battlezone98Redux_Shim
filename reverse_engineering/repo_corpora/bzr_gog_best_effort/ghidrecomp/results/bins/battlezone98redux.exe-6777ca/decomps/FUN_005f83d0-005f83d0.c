
uint __fastcall FUN_005f83d0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  float10 extraout_ST0;
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  float local_20;
  int local_1c;
  int local_18;
  int local_14;
  undefined1 local_10 [4];
  int *local_c;
  int local_8;
  
  local_8 = param_1;
  cVar1 = (**(code **)(**(int **)(param_1 + 0x10) + 0x68))();
  if (cVar1 == '\0') {
    local_14 = *(int *)(local_8 + 0x104) + 8;
    FUN_0042d8c0(local_10);
    while( true ) {
      uVar2 = FID_conflict_begin(local_28);
      cVar1 = FUN_00420f10(uVar2);
      if (cVar1 == '\0') break;
      local_c = (int *)FUN_0042de50();
      local_18 = *(int *)(local_c[1] + 8);
      if (((local_18 == 4) || (local_18 == 0xc)) &&
         (local_1c = FUN_00473940(), local_1c == *(int *)(local_8 + 0x10))) {
        uVar2 = (**(code **)(*(int *)(*local_c + 0x18) + 0xc))();
        uVar2 = (**(code **)(*(int *)(*(int *)(local_8 + 0x10) + 0x18) + 0xc))(uVar2);
        uVar3 = FUN_00462010(uVar2);
        local_20 = (float)extraout_ST0;
        if (2500.0 <= local_20) {
          return uVar3 & 0xffffff00;
        }
      }
      FUN_00438c10(local_24,0);
    }
    *(undefined4 *)(local_8 + 0xc) = 2;
    uVar3 = 1;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

