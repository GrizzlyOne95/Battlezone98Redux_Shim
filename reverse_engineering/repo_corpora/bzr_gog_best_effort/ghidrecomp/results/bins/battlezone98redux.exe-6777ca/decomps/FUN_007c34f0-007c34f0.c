
undefined1 FUN_007c34f0(int param_1,int param_2)

{
  char cVar1;
  float local_20;
  float local_1c;
  undefined4 local_18;
  undefined1 *local_14;
  undefined4 local_10;
  undefined1 *local_c;
  int *local_8;
  
  local_1c = 1.1406616e-38;
  cVar1 = FUN_007d3360();
  if ((cVar1 != '\0') && ((char)local_8[0x78] != '\0')) {
    local_1c = (float)param_2;
    local_20 = (float)param_1;
    cVar1 = FUN_007d2810();
    if (cVar1 == '\0') {
      if ((char)local_8[0x51] != '\0') {
        *(undefined1 *)(local_8 + 0x51) = 0;
        if ((local_8[5] & 0x10U) == 0) {
          local_1c = 0.0;
          local_20 = 1.1407017e-38;
          (**(code **)(*local_8 + 0x24))();
        }
        else {
          local_14 = (undefined1 *)&local_20;
          local_18 = FUN_004498d0(local_8 + 0x45);
          FUN_007d2b70();
        }
      }
    }
    else if ((char)local_8[0x51] == '\0') {
      *(undefined1 *)(local_8 + 0x51) = 1;
      if ((local_8[5] & 0x100U) != 0) {
        local_c = (undefined1 *)&local_20;
        local_10 = FUN_004498d0(local_8 + 0x52);
        FUN_007d2b70();
      }
      if ((char)local_8[0x56] != '\0') {
        local_1c = 0.0;
        local_20 = 0.0;
        FUN_0043aa30(local_8 + 0x56,0);
        local_1c = 0.0;
        local_20 = 1.1406889e-38;
        FUN_0043a170();
      }
    }
  }
  return (char)local_8[0x51];
}

