/*
 * Entry: 005823dc
 * Name: TextInput_AllowInput
 * Namespace: Global
 * Signature: void TextInput_AllowInput(void * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl TextInput_AllowInput(void *param_1,int param_2)

{
  uint *puVar1;
  int iVar2;
  BOOL BVar3;
  wrap_struct *pwVar4;
  tagMSG local_20;
  
  iVar2 = *(int *)((int)param_1 + 8);
  pwVar4 = region_list;
  if (param_2 != 0) {
    for (; pwVar4 != (wrap_struct *)0x0; pwVar4 = pwVar4->next) {
      puVar1 = (uint *)((int)pwVar4->ptr + 0x124);
      *puVar1 = *puVar1 & 0xfffffeff;
    }
  }
  puVar1 = (uint *)(iVar2 + 0x124);
  *puVar1 = -(uint)(param_2 != 0) & 0x100 | *puVar1 & 0xfffffeff;
  do {
    BVar3 = PeekMessageA(&local_20,(HWND)0x0,0x100,0x100,1);
  } while (BVar3 != 0);
  do {
    BVar3 = PeekMessageA(&local_20,(HWND)0x0,0x102,0x102,1);
  } while (BVar3 != 0);
  return;
}
