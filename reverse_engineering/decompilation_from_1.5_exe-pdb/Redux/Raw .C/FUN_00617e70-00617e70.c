
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00617e70(void)

{
  float fVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = FUN_00439e60();
  fVar1 = DAT_00920ef4;
  FUN_00617b20();
  if ((DAT_009183c0 != 0) && (DAT_00918310 == 0)) {
    iVar3 = *(int *)(*(int *)(iVar2 + 0x38) + 0x10) - _DAT_02a13e78;
    std::_Init_atomic_counter(DAT_0091552c,DAT_02ceef84);
    DAT_00920ef4 = fVar1 + 0.01;
    FUN_0068af70(*(undefined4 *)(iVar2 + 0x38),iVar3,0,*(int *)(*(int *)(iVar2 + 0x38) + 0x10) + -1,
                 DAT_02a13df8 + 4,DAT_02ceef88,0);
    DAT_00920ef4 = fVar1;
    FUN_00689d10(DAT_0091552c,*(undefined4 *)(iVar2 + 0x38),iVar3 + 2,2,&DAT_02a13e38);
  }
  return;
}

