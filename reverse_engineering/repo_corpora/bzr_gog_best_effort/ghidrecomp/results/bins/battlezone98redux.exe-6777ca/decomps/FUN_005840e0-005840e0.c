
void FUN_005840e0(float param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined1 local_c [4];
  int *local_8;
  
  FUN_0042d8c0(local_c);
  while( true ) {
    uVar2 = FID_conflict_begin(local_10);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 == '\0') break;
    FUN_00438c10(local_14,0);
    local_8 = (int *)FUN_0042de50();
    local_8 = (int *)*local_8;
    local_8[4] = (int)((float)local_8[4] + param_1);
    if (0.0 < (float)local_8[4]) {
      (**(code **)(*local_8 + 0x10))(local_8[4]);
      FUN_006809f0(local_8);
      local_8[4] = 0;
    }
    FUN_0044dca0(local_8[5] + 0x20);
  }
  return;
}

