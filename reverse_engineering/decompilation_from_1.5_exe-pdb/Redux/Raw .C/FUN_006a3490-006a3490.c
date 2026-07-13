
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_006a3490(void)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  int *piVar4;
  float10 fVar5;
  int local_64;
  undefined1 local_58 [80];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  fVar5 = (float10)FUN_00822d60();
  _DAT_02cc338c = (float)fVar5 + _DAT_02cc338c;
  if (0.016666 <= _DAT_02cc338c) {
    _DAT_02cc338c = 0.0;
    iVar3 = FUN_00572a70();
    if ((iVar3 == 0) || (iVar3 = FUN_00572a60(), iVar3 != 0)) {
      FUN_006a3a70(local_58);
      while (piVar4 = (int *)FUN_006a3b60(local_58), piVar4 != (int *)0x0) {
        piVar1 = (int *)*piVar4;
        if (((char)piVar4[8] == '\0') || (piVar1[0x2a] != 0)) {
          if (((char)piVar4[8] == '\0') && (0 < piVar1[0x2a])) {
            *(undefined1 *)(piVar4 + 8) = 1;
            FUN_0068fc60(piVar4);
          }
        }
        else {
          *(undefined1 *)(piVar4 + 8) = 0;
          FUN_0068fb10(piVar4);
        }
        iVar3 = (**(code **)piVar1[6])();
        if ((*(int *)(iVar3 + 0x14) == 0x434e5354) && (piVar4[0xc] != 0)) {
          cVar2 = FUN_004723d0();
          if (cVar2 == '\0') {
            if (piVar4[0xe] == 0) {
              FUN_0068fe40(piVar4);
            }
            else {
              FUN_00690770(*(undefined4 *)(DAT_00920f04 + (char)piVar4[4] * 4),piVar4);
            }
            piVar4[0xc] = 0;
            piVar4[0xd] = 0;
            piVar4[0xe] = 0;
          }
          else {
            cVar2 = (**(code **)(*piVar1 + 0x68))();
            if (cVar2 != '\0') {
              piVar4[0xe] = 1;
            }
          }
        }
      }
      FUN_006a3c10(local_58);
      do {
        iVar3 = FUN_006a3c70(local_58);
      } while (iVar3 != 0);
      for (local_64 = 1; local_64 < 0x10; local_64 = local_64 + 1) {
        if (*(int *)(DAT_00920f04 + local_64 * 4) != 0) {
          FUN_00692e70(*(undefined4 *)(DAT_00920f04 + local_64 * 4));
        }
      }
      FUN_0068f970();
      DAT_00931014 = DAT_00931014 + 1;
    }
    else {
      std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>();
    }
  }
  FUN_0083e885();
  return;
}

