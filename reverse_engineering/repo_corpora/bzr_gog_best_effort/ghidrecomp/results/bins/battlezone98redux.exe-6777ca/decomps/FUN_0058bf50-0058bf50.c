
void FUN_0058bf50(int param_1,int param_2)

{
  uint uVar1;
  void *_Dst;
  uint uVar2;
  int iVar3;
  uint local_8;
  
  uVar1 = DAT_0091816c;
  local_8 = *(int *)(param_1 + 0x18);
  while( true ) {
    if (local_8 == -1) {
      if ((int)DAT_008e8e00 < 0) {
        if (DAT_0091813c == (void *)0x0) {
          DAT_0091816c = 0x400;
          DAT_0091813c = (void *)FUN_0083d92c(0x4000);
          for (local_8 = 0; (int)local_8 < (int)DAT_0091816c; local_8 = local_8 + 1) {
            *(uint *)((int)DAT_0091813c + local_8 * 0x10) = local_8 + 1;
          }
          *(undefined4 *)((int)DAT_0091813c + (DAT_0091816c - 1) * 0x10) = 0xffffffff;
          DAT_008e8e00 = 0;
          DAT_0091819c = DAT_0091816c * 0x10 + DAT_0091819c;
        }
        else {
          DAT_0091819c = DAT_0091819c + DAT_0091816c * -0x10;
          uVar2 = DAT_0091816c * 2;
          _Dst = (void *)FUN_0083d92c(-(uint)((int)((ulonglong)uVar2 * 0x10 >> 0x20) != 0) |
                                      (uint)((ulonglong)uVar2 * 0x10));
          memcpy(_Dst,DAT_0091813c,DAT_0091816c << 4);
          operator_delete__(DAT_0091813c);
          DAT_0091813c = _Dst;
          for (local_8 = DAT_0091816c; (int)local_8 < (int)uVar2; local_8 = local_8 + 1) {
            *(uint *)((int)DAT_0091813c + local_8 * 0x10) = local_8 + 1;
          }
          *(uint *)((int)DAT_0091813c + (uVar2 - 1) * 0x10) = DAT_008e8e00;
          DAT_008e8e00 = DAT_0091816c;
          DAT_0091819c = uVar1 * 0x20 + DAT_0091819c;
          DAT_0091816c = uVar2;
        }
      }
      uVar1 = DAT_008e8e00;
      iVar3 = DAT_008e8e00 * 0x10;
      DAT_008e8e00 = *(uint *)((int)DAT_0091813c + DAT_008e8e00 * 0x10);
      *(int *)((int)DAT_0091813c + iVar3 + 8) = param_2;
      *(undefined4 *)((int)DAT_0091813c + uVar1 * 0x10 + 0xc) = *(undefined4 *)(param_2 + 0x14);
      *(undefined4 *)((int)DAT_0091813c + uVar1 * 0x10) = *(undefined4 *)(param_1 + 0x18);
      *(uint *)(param_1 + 0x18) = uVar1;
      return;
    }
    if (*(int *)((int)DAT_0091813c + local_8 * 0x10 + 8) == param_2) break;
    local_8 = *(int *)((int)DAT_0091813c + local_8 * 0x10);
  }
  return;
}

