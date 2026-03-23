
undefined4 FUN_007c3630(int param_1,int param_2)

{
  char cVar1;
  float local_18;
  float local_14;
  undefined4 local_10;
  undefined1 *local_c;
  int local_8;
  
  local_14 = 1.1407064e-38;
  cVar1 = FUN_007d3360();
  if ((cVar1 != '\0') && (*(char *)(local_8 + 0x1e0) != '\0')) {
    local_14 = (float)param_2;
    local_18 = (float)param_1;
    cVar1 = FUN_007d2810();
    if (cVar1 != '\0') {
      if (*(char *)(local_8 + 0x145) == '\0') {
        *(undefined1 *)(local_8 + 0x145) = 1;
        if ((*(uint *)(local_8 + 0x14) & 0x200) != 0) {
          local_c = (undefined1 *)&local_18;
          local_10 = FUN_004498d0(local_8 + 0x150);
          FUN_007d2b70();
        }
        if (*(char *)(local_8 + 0x198) != '\0') {
          local_14 = 0.0;
          local_18 = 0.0;
          FUN_0043aa30(local_8 + 0x198,0);
          local_14 = 0.0;
          local_18 = 1.1407337e-38;
          FUN_0043a170();
        }
      }
      return 1;
    }
  }
  return 0;
}

