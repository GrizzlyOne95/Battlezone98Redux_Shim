
void FUN_0068f970(void)

{
  undefined4 *puVar1;
  int iVar2;
  int local_8;
  
  FUN_006a5fd0("AI::AI_Process Begins");
  for (local_8 = 0; local_8 < 0x10; local_8 = local_8 + 1) {
    puVar1 = *(undefined4 **)(DAT_00920f04 + local_8 * 4);
    if ((puVar1 != (undefined4 *)0x0) && ((&DAT_02ce9b18)[local_8 * 0x1e0] != '\0')) {
      iVar2 = FUN_0068fa90(*puVar1);
      if ((iVar2 != 0) && (*(int *)(*(int *)(DAT_00920f04 + local_8 * 4) + 0x60) != 0)) {
        FUN_00696380(DAT_00920f04,local_8);
        FUN_006927b0(puVar1);
      }
    }
  }
  FUN_006a5fd0("AI::AI_Process Ends");
  return;
}

