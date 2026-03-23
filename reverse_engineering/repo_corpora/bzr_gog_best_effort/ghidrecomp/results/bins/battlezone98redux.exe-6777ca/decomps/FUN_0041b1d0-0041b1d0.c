
void __fastcall FUN_0041b1d0(int *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined1 local_10 [4];
  undefined1 local_c [4];
  int *local_8;
  
  local_8 = param_1;
  if ((*(char *)((int)param_1 + 0x5d) == '\0') ||
     (cVar1 = (**(code **)(*param_1 + 0x14))(), cVar1 == '\0')) {
    local_8[2] = 0;
  }
  else if (local_8[2] == 0) {
    local_8[2] = 1;
    if ((char)local_8[0x26] == '\0') {
      *(undefined1 *)(local_8 + 0x26) = 1;
      local_8[0x18] = local_8[0x29];
      FID_conflict_begin(local_c);
      FID_conflict_end(local_10);
      while (cVar1 = FID_conflict_operator__(local_10), cVar1 != '\0') {
        puVar2 = (undefined4 *)FUN_00421ec0();
        if ((int *)*puVar2 != local_8) {
          FUN_00421ec0();
          FUN_0041b180();
          return;
        }
        FUN_00421ee0();
      }
    }
    else {
      *(undefined1 *)(local_8 + 0x26) = 0;
      local_8[0x18] = local_8[0x28];
    }
  }
  return;
}

