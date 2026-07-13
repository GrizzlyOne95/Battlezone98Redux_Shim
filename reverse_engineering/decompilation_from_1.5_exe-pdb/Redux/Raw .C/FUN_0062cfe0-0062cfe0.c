
void FUN_0062cfe0(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  int local_10;
  int local_c;
  
  if (param_1 != (undefined4 *)0x0) {
    iVar1 = param_1[0x1e];
    if (iVar1 != 0) {
      local_10 = iVar1;
      if (param_1[0x21] == 0x28) {
        for (; local_10 != 0; local_10 = *(int *)(local_10 + 0x78)) {
          iVar2 = FUN_0045c4f0(local_10);
          if ((iVar2 != 0) && (*(undefined4 **)(iVar2 + 0xfc) == param_1)) {
            *(undefined4 *)(iVar2 + 0xfc) = 0;
          }
        }
      }
      if (*(undefined4 **)(iVar1 + 0x80) == param_1) {
        *(undefined4 *)(iVar1 + 0x80) = param_1[0x1f];
      }
      else {
        for (local_c = *(int *)(iVar1 + 0x80); local_c != 0; local_c = *(int *)(local_c + 0x7c)) {
          if (*(undefined4 **)(local_c + 0x7c) == param_1) {
            *(undefined4 *)(local_c + 0x7c) = param_1[0x1f];
            break;
          }
        }
      }
    }
    if (param_1[0x20] != 0) {
      *(undefined4 *)(param_1[0x20] + 0x78) = 0;
    }
    FUN_0062bab0(param_1[0x21],param_1[0x22]);
    param_1[0x21] = 0;
    param_1[0x22] = 0;
    FUN_004e3510(param_1);
    if ((param_1[5] & 0x800) != 0) {
      FUN_0068a2d0(param_1);
    }
    *param_1 = 0;
    param_1[0x1f] = DAT_02b3c724;
    DAT_02b3c724 = param_1;
  }
  return;
}

