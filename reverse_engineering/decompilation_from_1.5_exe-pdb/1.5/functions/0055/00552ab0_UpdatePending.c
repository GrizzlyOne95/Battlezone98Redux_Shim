/*
 * Entry: 00552ab0
 * Name: UpdatePending
 * Namespace: Global
 * Signature: void UpdatePending(dp_stat_t * param_1, TextLabel * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl UpdatePending(dp_stat_t *param_1,TextLabel *param_2)

{
  int iVar1;
  int *piVar2;
  int local_a4 [6];
  TextLabel *local_8c;
  char local_88 [20];
  undefined1 local_74 [44];
  char local_48 [64];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_74;
  local_8c = param_2;
  dpGetStats(Net::dp,5,local_a4,0x18);
  if (local_a4[3] != param_1->waiting) {
    if ((int)((uint)(param_1->waiting < local_a4[3]) * 2) < local_a4[3]) {
      builtin_strncpy(local_48,"Pending: %d",0xc);
      memset(local_48 + 0xc,0,0x34);
      read_text_label("multi_common","pending",local_48);
      sprintf(local_88,local_48,local_a4[3]);
      TextLabel::SetLabelText(local_8c,local_88);
      TextLabel::ShowLabelText(local_8c,1);
    }
    else if (param_2->textData[0] != '\0') {
      TextLabel::SetLabelText(param_2,"");
      TextLabel::HideLabelText(param_2,1);
    }
    piVar2 = local_a4;
    for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
      param_1->in = *piVar2;
      piVar2 = piVar2 + 1;
      param_1 = (dp_stat_t *)&param_1->out;
    }
  }
  return;
}
