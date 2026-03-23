
void FUN_00692a10(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  int local_14;
  int local_10;
  int local_c;
  
  iVar1 = *(int *)(DAT_00920f04 + param_1 * 4);
  FUN_006a5fd0("CreditSubtract Team %d Credits %d\n",param_1,param_2);
  FUN_006a5fd0("  BudgetValid  %d\n",*(undefined4 *)(iVar1 + 0x240));
  if ((param_2 != 0) &&
     (*(int *)(iVar1 + 0xbc) = *(int *)(iVar1 + 0xbc) - param_2, *(int *)(iVar1 + 0x240) != 0)) {
    while (param_2 != 0) {
      FUN_006a5fd0("     Removing credits %d\n",param_2);
      local_c = 1;
      bVar3 = false;
      do {
        iVar2 = *(int *)(iVar1 + 0xbc + local_c * 4);
        if ((iVar2 != 0) && ((!bVar3 || (local_14 < iVar2)))) {
          local_10 = local_c;
          bVar3 = true;
          local_14 = iVar2;
        }
        local_c = local_c + 1;
      } while (local_c < 0x20);
      if (bVar3) {
        FUN_006a5fd0("    Found Account %d with %d credits\n",local_10,local_14);
      }
      else {
        FUN_006a5fd0("    No account found with cash in it\n");
      }
      if (local_14 < param_2) {
        FUN_006a5fd0("    Emptying account %d\n",local_10);
        *(undefined4 *)(iVar1 + 0xbc + local_10 * 4) = 0;
        param_2 = param_2 - local_14;
      }
      else {
        FUN_006a5fd0("   Taking only from account %d\n",local_10);
        *(int *)(iVar1 + 0xbc + local_10 * 4) = local_14 - param_2;
        param_2 = 0;
      }
    }
  }
  return;
}

