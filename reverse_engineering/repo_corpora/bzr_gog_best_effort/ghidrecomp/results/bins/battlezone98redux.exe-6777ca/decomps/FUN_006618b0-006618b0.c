
void __thiscall FUN_006618b0(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  int *local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  *(undefined4 *)(param_1 + 0x10) = param_2;
  if (1.0 < *(float *)(param_1 + 0x10)) {
    *(undefined4 *)(param_1 + 0x10) = 0x3f800000;
  }
  if (*(float *)(param_1 + 0x10) <= 0.0 && *(float *)(param_1 + 0x10) != 0.0) {
    *(undefined4 *)(param_1 + 0x10) = 0;
  }
  local_8 = param_1;
  FUN_00422170();
  FUN_00422170();
  puVar2 = (undefined4 *)FID_conflict_end(local_18);
  local_10 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_begin(local_1c);
  local_c = *puVar2;
  while( true ) {
    cVar1 = FID_conflict_operator__(&local_10);
    if (cVar1 == '\0') break;
    puVar2 = (undefined4 *)FUN_00421ec0();
    local_14 = (int *)*puVar2;
    (**(code **)(*local_14 + 4))(*(undefined4 *)(local_8 + 0x10));
    FUN_00421ee0();
  }
  return;
}

