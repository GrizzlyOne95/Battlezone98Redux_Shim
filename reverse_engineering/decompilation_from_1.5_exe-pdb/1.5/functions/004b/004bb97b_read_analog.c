/*
 * Entry: 004bb97b
 * Name: read_analog
 * Namespace: Global
 * Signature: int read_analog(_iobuf * param_1, FIELD_DESC * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl read_analog(_iobuf *param_1,FIELD_DESC *param_2)

{
  int iVar1;
  char *pcVar2;
  char local_148 [4];
  char local_144 [256];
  char local_44 [40];
  char local_1c [20];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar1 = getNonBlankLine(local_144,0xff,param_1);
  if (iVar1 == 0) {
    pcVar2 = "%s line %d: unexpected end of file.";
  }
  else {
    iVar1 = sscanf(local_144," %1[+-] %s %s",local_148,local_44,local_1c);
    if (iVar1 == 3) {
      pcVar2 = local_1c;
      iVar1 = get_device_num_from_name(local_44);
      iVar1 = get_analog_num(iVar1,pcVar2);
      if (iVar1 == -1) {
        return 0;
      }
      iVar1 = add_analog_channel(param_2,local_44,iVar1);
      if (iVar1 < 0) {
        return 0;
      }
      analog_map[iVar1].sign = (uint)(local_148[0] != '-') * 2 + -1;
      iVar1 = read_chord(param_1,&analog_map[iVar1].chord_size,analog_map[iVar1].chord);
      return (uint)(iVar1 != 0);
    }
    pcVar2 = "%s line %d: invalid analog entry.";
  }
  DEBUG_systemWarning(pcVar2);
  return 0;
}
