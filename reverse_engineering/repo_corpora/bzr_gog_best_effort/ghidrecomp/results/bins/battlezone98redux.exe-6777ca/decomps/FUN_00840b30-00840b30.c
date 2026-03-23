
bool FUN_00840b30(ushort *param_1,uint param_2)

{
  ushort uVar1;
  ushort *puVar2;
  uint uVar3;
  
  if (param_2 != 0) {
    do {
      puVar2 = param_1;
      if (7 < *(uint *)(param_1 + 10)) {
        puVar2 = *(ushort **)param_1;
      }
    } while (((puVar2[param_2 - 1] == 0x2f) || (puVar2[param_2 - 1] == 0x5c)) &&
            (param_2 = param_2 - 1, param_2 != 0));
    if (param_2 != 0) {
      if (param_2 == 2) {
        puVar2 = param_1;
        if (7 < *(uint *)(param_1 + 10)) {
          puVar2 = *(ushort **)param_1;
        }
        uVar1 = *puVar2;
        if (((0x60 < uVar1) && (uVar1 < 0x7b)) || ((ushort)(uVar1 - 0x41) < 0x1a)) {
          if (7 < *(uint *)(param_1 + 10)) {
            param_1 = *(ushort **)param_1;
          }
          if (param_1[1] == 0x3a) {
            return true;
          }
        }
      }
      else if (2 < param_2) {
        puVar2 = param_1;
        if (7 < *(uint *)(param_1 + 10)) {
          puVar2 = *(ushort **)param_1;
        }
        if ((*puVar2 == 0x2f) || (*puVar2 == 0x5c)) {
          if (7 < *(uint *)(param_1 + 10)) {
            param_1 = *(ushort **)param_1;
          }
          if ((param_1[1] == 0x2f) || (param_1[1] == 0x5c)) {
            uVar3 = FUN_00840890(&DAT_00870c04,2);
            return uVar3 == param_2;
          }
        }
      }
      return false;
    }
  }
  return true;
}

