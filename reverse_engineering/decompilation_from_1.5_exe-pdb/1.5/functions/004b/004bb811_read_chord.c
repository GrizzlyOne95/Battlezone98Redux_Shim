/*
 * Entry: 004bb811
 * Name: read_chord
 * Namespace: Global
 * Signature: int read_chord(_iobuf * param_1, int * param_2, DISCRETE_STATE * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl read_chord(_iobuf *param_1,int *param_2,DISCRETE_STATE *param_3)

{
  int iVar1;
  int local_14c;
  char local_148 [4];
  char local_144 [116];
  undefined1 local_d0 [140];
  char local_44 [40];
  char local_1c [20];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_d0;
  local_14c = 0;
  *param_2 = 0;
  iVar1 = getNonBlankLine(local_144,0xff,param_1);
  do {
    if ((iVar1 == 0) || (local_144[0] == '}')) goto LAB_004bb95b;
    iVar1 = sscanf(local_144," %1[+-] %s %s",local_148,local_44,local_1c);
    if (iVar1 == 3) {
      if (7 < *param_2) {
        DEBUG_systemWarning("%s line %d: chord too big");
LAB_004bb95b:
        return (uint)(local_14c != -1);
      }
      iVar1 = get_device_num_from_name(local_44);
      local_14c = get_discrete_num(iVar1,local_1c);
      if (local_14c != -1) {
        param_3[*param_2].type = (uint)(local_148[0] == '-');
        param_3[*param_2].from = (long *)((iVar1 * 0x14 + (local_14c >> 5)) * 4 + 0xb0ff08);
        param_3[*param_2].mask = 1 << ((byte)local_14c & 0x1f);
        *param_2 = *param_2 + 1;
      }
    }
    else {
      DEBUG_systemWarning("%s line %d: invalid chord entry");
    }
    iVar1 = getNonBlankLine(local_144,0xff,param_1);
  } while( true );
}
