
void __thiscall FUN_00577900(int param_1,uint param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  int local_c;
  undefined1 local_8 [4];
  
  if (*(byte *)(param_1 + 0x68) != param_2) {
    local_c = param_1;
    FUN_007d6a70("NetPlayer::SetTeam team=%d prev=%d\n",param_2,*(undefined1 *)(param_1 + 0x68));
    *(undefined1 *)(local_c + 0x68) = (undefined1)param_2;
    memset(&DAT_009180e8,0,0x40);
    FUN_00420260(local_8);
    while( true ) {
      uVar2 = FID_conflict_begin(local_14);
      cVar1 = FUN_00420f10(uVar2);
      if (cVar1 == '\0') break;
      iVar3 = FUN_00422150();
      if (*(char *)(*(int *)(iVar3 + 0x10) + 0x68) != '\0') {
        iVar3 = FUN_00422150();
        iVar4 = FUN_00422150();
        *(undefined4 *)(&DAT_009180e8 + (uint)*(byte *)(*(int *)(iVar4 + 0x10) + 0x68) * 4) =
             *(undefined4 *)(iVar3 + 0x10);
      }
      FUN_004305b0(local_10,0);
    }
  }
  return;
}

