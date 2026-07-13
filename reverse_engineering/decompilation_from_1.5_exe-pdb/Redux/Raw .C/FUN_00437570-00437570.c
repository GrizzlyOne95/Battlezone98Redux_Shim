
undefined4 FUN_00437570(int param_1,LONG *param_2,LONG *param_3)

{
  BOOL BVar1;
  tagPOINT local_10;
  
  if (**(int **)(param_1 + 0x1c) != 0) {
    local_10.x = *param_2;
    local_10.y = *param_3;
    BVar1 = ScreenToClient((HWND)**(undefined4 **)(param_1 + 0x1c),&local_10);
    if ((char)BVar1 != '\0') {
      *param_2 = local_10.x;
      *param_3 = local_10.y;
      return 1;
    }
  }
  return 0;
}

