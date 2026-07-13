
void FUN_006949b0(void)

{
  int iVar1;
  float10 fVar2;
  int local_8;
  
  FUN_006a5fd0();
  local_8 = 0;
  while( true ) {
    iVar1 = FUN_006a4030();
    if (iVar1 <= local_8) break;
    FUN_006a4040();
    fVar2 = (float10)FUN_006948f0();
    *(float *)(&DAT_02bfeff8 + local_8 * 4) = (float)fVar2;
    iVar1 = FUN_006a4040(local_8,(double)*(float *)(&DAT_02bfeff8 + local_8 * 4));
    iVar1 = FUN_006a4040(local_8,iVar1 + 0x34);
    FUN_006a5fd0("Unit Name \'%s\' Symbol \'%s\' strength %4.4f\n",iVar1 + 0x14);
    local_8 = local_8 + 1;
  }
  return;
}

