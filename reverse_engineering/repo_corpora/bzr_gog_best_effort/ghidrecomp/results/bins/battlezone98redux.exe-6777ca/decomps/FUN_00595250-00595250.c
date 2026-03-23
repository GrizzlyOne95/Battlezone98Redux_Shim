
void __fastcall FUN_00595250(int param_1)

{
  if (*(int *)(param_1 + 0x6c) == 0) {
    if (DAT_00919879 == '\0') {
      if (DAT_0091987a == '\0') {
        if (DAT_0091987b == '\0') {
          if (DAT_0091987c == '\0') {
            if (DAT_0091987d == '\0') {
              if (DAT_0091987e != '\0') {
                *(undefined4 *)(param_1 + 0x6c) = 6;
                DAT_0091987e = '\0';
              }
            }
            else {
              *(undefined4 *)(param_1 + 0x6c) = 5;
              DAT_0091987d = '\0';
            }
          }
          else {
            *(undefined4 *)(param_1 + 0x6c) = 3;
            DAT_0091987c = '\0';
          }
        }
        else {
          *(undefined4 *)(param_1 + 0x6c) = 4;
          DAT_0091987b = '\0';
        }
      }
      else {
        *(undefined4 *)(param_1 + 0x6c) = 2;
        DAT_0091987a = '\0';
      }
    }
    else {
      *(undefined4 *)(param_1 + 0x6c) = 1;
      DAT_00919879 = '\0';
    }
  }
  FUN_00597fb0();
  FUN_005973d0();
  FUN_0059bec0();
  FUN_00597710();
  FUN_0059b550();
  FUN_0059b980();
  return;
}

