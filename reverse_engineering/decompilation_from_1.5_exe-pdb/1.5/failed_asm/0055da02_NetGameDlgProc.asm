; Entry: 0055da02
; Name: NetGameDlgProc
; Signature: int NetGameDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
; Stop: 0x00563039
; Reason: Exception while decompiling 0055da02: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x0055da02 --stop-address=0x00563039 C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  55da02:      	subl	$0x2f0, %esp            # imm = 0x2F0
  55da08:      	movl	0x64d8e0, %eax
  55da0d:      	xorl	%esp, %eax
  55da0f:      	movl	%eax, 0x2ec(%esp)
  55da16:      	movl	0x2f8(%esp), %eax
  55da1d:      	pushl	%ebx
  55da1e:      	movl	0x2f8(%esp), %ebx
  55da25:      	pushl	%ebp
  55da26:      	pushl	%esi
  55da27:      	movl	0x30c(%esp), %esi
  55da2e:      	movl	$0x113, %ecx            # imm = 0x113
  55da33:      	pushl	%edi
  55da34:      	movl	0x30c(%esp), %edi
  55da3b:      	cmpl	%ecx, %eax
  55da3d:      	ja	0x561e45 <.text+0x160e45>
  55da43:      	je	0x560cdf <.text+0x15fcdf>
  55da49:      	cmpl	$0x2b, %eax
  55da4c:      	ja	0x55eae0 <.text+0x15dae0>
  55da52:      	je	0x55e46e <.text+0x15d46e>
  55da58:      	decl	%eax
  55da59:      	decl	%eax
  55da5a:      	je	0x55dde3 <.text+0x15cde3>
  55da60:      	subl	$0xd, %eax
  55da63:      	je	0x55da8e <.text+0x15ca8e>
  55da65:      	subl	$0x5, %eax
  55da68:      	je	0x560d63 <.text+0x15fd63>
  55da6e:      	subl	$0xc, %eax
  55da71:      	jne	0x55eb35 <.text+0x15db35>
  55da77:      	pushl	%eax
  55da78:      	calll	0x571075 <.text+0x170075>
  55da7d:      	popl	%ecx
  55da7e:      	pushl	$0x1
  55da80:      	pushl	$0x0
  55da82:      	pushl	%ebx
  55da83:      	calll	*0x5ce564
  55da89:      	jmp	0x560d63 <.text+0x15fd63>
  55da8e:      	leal	0x258(%esp), %eax
  55da95:      	pushl	%eax
  55da96:      	pushl	%ebx
  55da97:      	calll	*0x5ce5e4
  55da9d:      	movl	0xc701e8, %ecx
  55daa3:      	movl	%eax, %esi
  55daa5:      	pushl	%esi
  55daa6:      	calll	0x56f834 <.text+0x16e834>
  55daab:      	movl	0xc701e4, %eax
  55dab0:      	movl	0x1c(%eax), %ecx
  55dab3:      	xorl	%edi, %edi
  55dab5:      	cmpl	%edi, %ecx
  55dab7:      	je	0x55dabf <.text+0x15cabf>
  55dab9:      	pushl	%esi
  55daba:      	calll	0x56f834 <.text+0x16e834>
  55dabf:      	movl	0xc701e0, %ecx
  55dac5:      	pushl	%esi
  55dac6:      	calll	0x571711 <.text+0x170711>
  55dacb:      	movl	0xc701dc, %ecx
  55dad1:      	pushl	%esi
  55dad2:      	calll	0x571711 <.text+0x170711>
  55dad7:      	movl	0xc701d8, %ecx
  55dadd:      	pushl	%esi
  55dade:      	calll	0x571711 <.text+0x170711>
  55dae3:      	movl	0xc701d4, %ecx
  55dae9:      	pushl	%esi
  55daea:      	calll	0x571711 <.text+0x170711>
  55daef:      	movl	0xc701d0, %ecx
  55daf5:      	pushl	%esi
  55daf6:      	calll	0x571711 <.text+0x170711>
  55dafb:      	movl	0xc701cc, %ecx
  55db01:      	pushl	%esi
  55db02:      	calll	0x571711 <.text+0x170711>
  55db07:      	movl	0xc701c8, %ecx
  55db0d:      	cmpl	%edi, %ecx
  55db0f:      	je	0x55db17 <.text+0x15cb17>
  55db11:      	pushl	%esi
  55db12:      	calll	0x571711 <.text+0x170711>
  55db17:      	movl	0xc701c4, %ecx
  55db1d:      	cmpl	%edi, %ecx
  55db1f:      	je	0x55db27 <.text+0x15cb27>
  55db21:      	pushl	%esi
  55db22:      	calll	0x571711 <.text+0x170711>
  55db27:      	movl	0xc701c0, %ecx
  55db2d:      	cmpl	%edi, %ecx
  55db2f:      	je	0x55db37 <.text+0x15cb37>
  55db31:      	pushl	%esi
  55db32:      	calll	0x571711 <.text+0x170711>
  55db37:      	movl	0xc701bc, %ecx
  55db3d:      	cmpl	%edi, %ecx
  55db3f:      	je	0x55db47 <.text+0x15cb47>
  55db41:      	pushl	%esi
  55db42:      	calll	0x571711 <.text+0x170711>
  55db47:      	movl	0xc701b8, %ecx
  55db4d:      	pushl	%esi
  55db4e:      	calll	0x571711 <.text+0x170711>
  55db53:      	movl	0xc701b4, %ecx
  55db59:      	pushl	%esi
  55db5a:      	calll	0x571711 <.text+0x170711>
  55db5f:      	movl	0xc701b0, %ecx
  55db65:      	pushl	%esi
  55db66:      	calll	0x571711 <.text+0x170711>
  55db6b:      	movl	0xc701ac, %ecx
  55db71:      	pushl	%esi
  55db72:      	calll	0x571711 <.text+0x170711>
  55db77:      	movl	0xc701a8, %ecx
  55db7d:      	pushl	%esi
  55db7e:      	calll	0x571711 <.text+0x170711>
  55db83:      	movl	0xc701a4, %ecx
  55db89:      	pushl	%esi
  55db8a:      	calll	0x571711 <.text+0x170711>
  55db8f:      	movl	0xc701a0, %ecx
  55db95:      	pushl	%esi
  55db96:      	calll	0x571711 <.text+0x170711>
  55db9b:      	movl	0xc7019c, %ecx
  55dba1:      	pushl	%esi
  55dba2:      	calll	0x571711 <.text+0x170711>
  55dba7:      	movl	0xc70198, %ecx
  55dbad:      	pushl	%esi
  55dbae:      	calll	0x571711 <.text+0x170711>
  55dbb3:      	movl	0xc70194, %ecx
  55dbb9:      	pushl	%esi
  55dbba:      	calll	0x571711 <.text+0x170711>
  55dbbf:      	movl	0xc70190, %ecx
  55dbc5:      	pushl	%esi
  55dbc6:      	calll	0x571711 <.text+0x170711>
  55dbcb:      	movl	0xc7018c, %ecx
  55dbd1:      	pushl	%esi
  55dbd2:      	calll	0x571711 <.text+0x170711>
  55dbd7:      	movl	0xc70188, %ecx
  55dbdd:      	pushl	%esi
  55dbde:      	calll	0x571711 <.text+0x170711>
  55dbe3:      	movl	0xc70184, %ecx
  55dbe9:      	pushl	%esi
  55dbea:      	calll	0x571711 <.text+0x170711>
  55dbef:      	movl	0xc70180, %ecx
  55dbf5:      	pushl	%esi
  55dbf6:      	calll	0x571711 <.text+0x170711>
  55dbfb:      	movl	0xc7017c, %ecx
  55dc01:      	pushl	%esi
  55dc02:      	calll	0x571711 <.text+0x170711>
  55dc07:      	movl	0xc70178, %ecx
  55dc0d:      	pushl	%esi
  55dc0e:      	calll	0x571711 <.text+0x170711>
  55dc13:      	movl	0xc70174, %ecx
  55dc19:      	pushl	%esi
  55dc1a:      	calll	0x571711 <.text+0x170711>
  55dc1f:      	movl	0xc70170, %ecx
  55dc25:      	pushl	%esi
  55dc26:      	calll	0x571711 <.text+0x170711>
  55dc2b:      	movl	0xc7016c, %ecx
  55dc31:      	pushl	%esi
  55dc32:      	calll	0x5717d4 <.text+0x1707d4>
  55dc37:      	movl	0xc6fdb8, %ecx
  55dc3d:      	pushl	%esi
  55dc3e:      	calll	0x5717d4 <.text+0x1707d4>
  55dc43:      	movl	0xc70168, %ecx
  55dc49:      	pushl	%esi
  55dc4a:      	calll	0x5717d4 <.text+0x1707d4>
  55dc4f:      	movl	0xc70164, %ecx
  55dc55:      	pushl	%esi
  55dc56:      	calll	0x5717d4 <.text+0x1707d4>
  55dc5b:      	movl	0xc70160, %ecx
  55dc61:      	pushl	%esi
  55dc62:      	calll	0x5717d4 <.text+0x1707d4>
  55dc67:      	movl	0xc7015c, %ecx
  55dc6d:      	pushl	%esi
  55dc6e:      	calll	0x5717d4 <.text+0x1707d4>
  55dc73:      	movl	0xc70158, %ecx
  55dc79:      	pushl	%esi
  55dc7a:      	calll	0x5717d4 <.text+0x1707d4>
  55dc7f:      	movl	0xc70154, %ecx
  55dc85:      	pushl	%esi
  55dc86:      	calll	0x5717d4 <.text+0x1707d4>
  55dc8b:      	movl	0xc70150, %ecx
  55dc91:      	pushl	%esi
  55dc92:      	calll	0x5717d4 <.text+0x1707d4>
  55dc97:      	movl	0xc7014c, %ecx
  55dc9d:      	pushl	%esi
  55dc9e:      	calll	0x5717d4 <.text+0x1707d4>
  55dca3:      	movl	0xc70148, %ecx
  55dca9:      	pushl	%esi
  55dcaa:      	calll	0x5717d4 <.text+0x1707d4>
  55dcaf:      	movl	0xc70144, %ecx
  55dcb5:      	pushl	%esi
  55dcb6:      	calll	0x5717d4 <.text+0x1707d4>
  55dcbb:      	movl	0xc70140, %ecx
  55dcc1:      	pushl	%edi
  55dcc2:      	pushl	%edi
  55dcc3:      	pushl	%esi
  55dcc4:      	calll	0x570320 <.text+0x16f320>
  55dcc9:      	movl	0xc7013c, %ecx
  55dccf:      	pushl	%edi
  55dcd0:      	pushl	%edi
  55dcd1:      	pushl	%esi
  55dcd2:      	calll	0x570320 <.text+0x16f320>
  55dcd7:      	movl	0xc70138, %ecx
  55dcdd:      	pushl	%edi
  55dcde:      	pushl	%edi
  55dcdf:      	pushl	%esi
  55dce0:      	calll	0x570320 <.text+0x16f320>
  55dce5:      	movl	0xc70134, %ecx
  55dceb:      	pushl	%edi
  55dcec:      	pushl	%edi
  55dced:      	pushl	%esi
  55dcee:      	calll	0x570320 <.text+0x16f320>
  55dcf3:      	movl	0xc70130, %ecx
  55dcf9:      	pushl	%edi
  55dcfa:      	pushl	%edi
  55dcfb:      	pushl	%esi
  55dcfc:      	calll	0x570320 <.text+0x16f320>
  55dd01:      	movl	0xc70198, %eax
  55dd06:      	cmpl	%edi, 0x84(%eax)
  55dd0c:      	jne	0x55dd2a <.text+0x15cd2a>
  55dd0e:      	movl	0xc7012c, %ecx
  55dd14:      	pushl	%edi
  55dd15:      	pushl	%edi
  55dd16:      	pushl	%esi
  55dd17:      	calll	0x570320 <.text+0x16f320>
  55dd1c:      	movl	0xc70128, %ecx
  55dd22:      	pushl	%edi
  55dd23:      	pushl	%edi
  55dd24:      	pushl	%esi
  55dd25:      	calll	0x570320 <.text+0x16f320>
  55dd2a:      	movl	0xc70124, %ecx
  55dd30:      	pushl	%edi
  55dd31:      	pushl	%edi
  55dd32:      	pushl	%esi
  55dd33:      	calll	0x570320 <.text+0x16f320>
  55dd38:      	movl	0xc70120, %ecx
  55dd3e:      	pushl	%edi
  55dd3f:      	pushl	%edi
  55dd40:      	pushl	%esi
  55dd41:      	calll	0x570320 <.text+0x16f320>
  55dd46:      	movl	0xc7011c, %ecx
  55dd4c:      	pushl	%edi
  55dd4d:      	pushl	%edi
  55dd4e:      	pushl	%esi
  55dd4f:      	calll	0x570320 <.text+0x16f320>
  55dd54:      	movl	0xc70118, %ecx
  55dd5a:      	pushl	%edi
  55dd5b:      	pushl	%edi
  55dd5c:      	pushl	%esi
  55dd5d:      	calll	0x570320 <.text+0x16f320>
  55dd62:      	movl	0xc70114, %ecx
  55dd68:      	pushl	%edi
  55dd69:      	pushl	%edi
  55dd6a:      	pushl	%esi
  55dd6b:      	calll	0x570320 <.text+0x16f320>
  55dd70:      	movl	0xc70110, %ecx
  55dd76:      	pushl	%edi
  55dd77:      	pushl	%edi
  55dd78:      	pushl	%esi
  55dd79:      	calll	0x570320 <.text+0x16f320>
  55dd7e:      	movl	0xc7010c, %ecx
  55dd84:      	pushl	%edi
  55dd85:      	pushl	%edi
  55dd86:      	pushl	%esi
  55dd87:      	calll	0x570320 <.text+0x16f320>
  55dd8c:      	movl	0xc70108, %ecx
  55dd92:      	movl	(%ecx), %eax
  55dd94:      	pushl	%edi
  55dd95:      	pushl	%esi
  55dd96:      	calll	*(%eax)
  55dd98:      	movl	0xc70104, %ecx
  55dd9e:      	movl	(%ecx), %eax
  55dda0:      	pushl	%edi
  55dda1:      	pushl	%esi
  55dda2:      	calll	*(%eax)
  55dda4:      	movl	0xc70100, %ecx
  55ddaa:      	pushl	%edi
  55ddab:      	pushl	%edi
  55ddac:      	pushl	%esi
  55ddad:      	calll	0x570320 <.text+0x16f320>
  55ddb2:      	movl	0xc700fc, %ecx
  55ddb8:      	cmpl	%edi, %ecx
  55ddba:      	je	0x55ddc4 <.text+0x15cdc4>
  55ddbc:      	pushl	%edi
  55ddbd:      	pushl	%edi
  55ddbe:      	pushl	%esi
  55ddbf:      	calll	0x570320 <.text+0x16f320>
  55ddc4:      	movl	0xc701e4, %ecx
  55ddca:      	calll	0x551d61 <.text+0x150d61>
  55ddcf:      	leal	0x258(%esp), %eax
  55ddd6:      	pushl	%eax
  55ddd7:      	pushl	%ebx
  55ddd8:      	calll	*0x5ce5e8
  55ddde:      	jmp	0x55eb35 <.text+0x15db35>
  55dde3:      	movl	0xc700f8, %eax
  55dde8:      	xorl	%edi, %edi
  55ddea:      	cmpl	%edi, %eax
  55ddec:      	je	0x55ddfc <.text+0x15cdfc>
  55ddee:      	pushl	%eax
  55ddef:      	pushl	%ebx
  55ddf0:      	calll	*0x5ce538
  55ddf6:      	movl	%edi, 0xc700f8
  55ddfc:      	movl	%edi, 0xc6fdc4
  55de02:      	calll	0x552c81 <.text+0x151c81>
  55de07:      	movl	0xc701e4, %ecx
  55de0d:      	cmpl	%edi, %ecx
  55de0f:      	je	0x55de18 <.text+0x15ce18>
  55de11:      	pushl	$0x1
  55de13:      	calll	0x5570f0 <.text+0x1560f0>
  55de18:      	movl	0xc700f4, %ecx
  55de1e:      	movl	%edi, 0xc701e4
  55de24:      	cmpl	%edi, %ecx
  55de26:      	je	0x55de36 <.text+0x15ce36>
  55de28:      	movl	%ecx, %esi
  55de2a:      	calll	0x5566d9 <.text+0x1556d9>
  55de2f:      	pushl	%esi
  55de30:      	calll	0x5c6d00 <.text+0x1c5d00>
  55de35:      	popl	%ecx
  55de36:      	pushl	$0x5598e5               # imm = 0x5598E5
  55de3b:      	pushl	%edi
  55de3c:      	pushl	%edi
  55de3d:      	pushl	0xba7724
  55de43:      	movl	$0xc6fef8, %esi         # imm = 0xC6FEF8
  55de48:      	pushl	%edi
  55de49:      	movl	%esi, %ecx
  55de4b:      	movl	%edi, 0xc700f4
  55de51:      	calll	0x550bd0 <.text+0x14fbd0>
  55de56:      	movl	%edi, 0xc6ff34
  55de5c:      	calll	0x582000 <.text+0x181000>
  55de61:      	movl	%esi, %ecx
  55de63:      	movl	%eax, 0xc6ff38
  55de68:      	calll	0x55b669 <.text+0x15a669>
  55de6d:      	calll	0x570daa <.text+0x16fdaa>
  55de72:      	calll	0x570d92 <.text+0x16fd92>
  55de77:      	movl	0xc701e8, %ecx
  55de7d:      	movl	%ecx, %esi
  55de7f:      	cmpl	%edi, %ecx
  55de81:      	je	0x55de8f <.text+0x15ce8f>
  55de83:      	calll	0x56f7bb <.text+0x16e7bb>
  55de88:      	pushl	%esi
  55de89:      	calll	0x5c6d00 <.text+0x1c5d00>
  55de8e:      	popl	%ecx
  55de8f:      	movl	0xc701e0, %ecx
  55de95:      	movl	%ecx, %esi
  55de97:      	cmpl	%edi, %ecx
  55de99:      	je	0x55dea7 <.text+0x15cea7>
  55de9b:      	calll	0x56f3bb <.text+0x16e3bb>
  55dea0:      	pushl	%esi
  55dea1:      	calll	0x5c6d00 <.text+0x1c5d00>
  55dea6:      	popl	%ecx
  55dea7:      	movl	0xc701dc, %ecx
  55dead:      	movl	%ecx, %esi
  55deaf:      	cmpl	%edi, %ecx
  55deb1:      	je	0x55debf <.text+0x15cebf>
  55deb3:      	calll	0x56f3bb <.text+0x16e3bb>
  55deb8:      	pushl	%esi
  55deb9:      	calll	0x5c6d00 <.text+0x1c5d00>
  55debe:      	popl	%ecx
  55debf:      	movl	0xc701d8, %ecx
  55dec5:      	movl	%ecx, %esi
  55dec7:      	cmpl	%edi, %ecx
  55dec9:      	je	0x55ded7 <.text+0x15ced7>
  55decb:      	calll	0x56f3bb <.text+0x16e3bb>
  55ded0:      	pushl	%esi
  55ded1:      	calll	0x5c6d00 <.text+0x1c5d00>
  55ded6:      	popl	%ecx
  55ded7:      	movl	0xc701d4, %ecx
  55dedd:      	movl	%ecx, %esi
  55dedf:      	cmpl	%edi, %ecx
  55dee1:      	je	0x55deef <.text+0x15ceef>
  55dee3:      	calll	0x56f3bb <.text+0x16e3bb>
  55dee8:      	pushl	%esi
  55dee9:      	calll	0x5c6d00 <.text+0x1c5d00>
  55deee:      	popl	%ecx
  55deef:      	movl	0xc701d0, %ecx
  55def5:      	movl	%ecx, %esi
  55def7:      	cmpl	%edi, %ecx
  55def9:      	je	0x55df07 <.text+0x15cf07>
  55defb:      	calll	0x56f3bb <.text+0x16e3bb>
  55df00:      	pushl	%esi
  55df01:      	calll	0x5c6d00 <.text+0x1c5d00>
  55df06:      	popl	%ecx
  55df07:      	movl	0xc701cc, %ecx
  55df0d:      	movl	%ecx, %esi
  55df0f:      	cmpl	%edi, %ecx
  55df11:      	je	0x55df1f <.text+0x15cf1f>
  55df13:      	calll	0x56f3bb <.text+0x16e3bb>
  55df18:      	pushl	%esi
  55df19:      	calll	0x5c6d00 <.text+0x1c5d00>
  55df1e:      	popl	%ecx
  55df1f:      	movl	0xc701c8, %ecx
  55df25:      	cmpl	%edi, %ecx
  55df27:      	je	0x55df37 <.text+0x15cf37>
  55df29:      	movl	%ecx, %esi
  55df2b:      	calll	0x56f3bb <.text+0x16e3bb>
  55df30:      	pushl	%esi
  55df31:      	calll	0x5c6d00 <.text+0x1c5d00>
  55df36:      	popl	%ecx
  55df37:      	movl	0xc701c4, %ecx
  55df3d:      	movl	%edi, 0xc701c8
  55df43:      	cmpl	%edi, %ecx
  55df45:      	je	0x55df55 <.text+0x15cf55>
  55df47:      	movl	%ecx, %esi
  55df49:      	calll	0x56f3bb <.text+0x16e3bb>
  55df4e:      	pushl	%esi
  55df4f:      	calll	0x5c6d00 <.text+0x1c5d00>
  55df54:      	popl	%ecx
  55df55:      	movl	0xc701c0, %ecx
  55df5b:      	movl	%edi, 0xc701c4
  55df61:      	cmpl	%edi, %ecx
  55df63:      	je	0x55df73 <.text+0x15cf73>
  55df65:      	movl	%ecx, %esi
  55df67:      	calll	0x56f3bb <.text+0x16e3bb>
  55df6c:      	pushl	%esi
  55df6d:      	calll	0x5c6d00 <.text+0x1c5d00>
  55df72:      	popl	%ecx
  55df73:      	movl	0xc701bc, %ecx
  55df79:      	movl	%edi, 0xc701c0
  55df7f:      	cmpl	%edi, %ecx
  55df81:      	je	0x55df91 <.text+0x15cf91>
  55df83:      	movl	%ecx, %esi
  55df85:      	calll	0x56f3bb <.text+0x16e3bb>
  55df8a:      	pushl	%esi
  55df8b:      	calll	0x5c6d00 <.text+0x1c5d00>
  55df90:      	popl	%ecx
  55df91:      	movl	0xc70190, %ecx
  55df97:      	movl	%edi, 0xc701bc
  55df9d:      	movl	%ecx, %esi
  55df9f:      	cmpl	%edi, %ecx
  55dfa1:      	je	0x55dfaf <.text+0x15cfaf>
  55dfa3:      	calll	0x56f3bb <.text+0x16e3bb>
  55dfa8:      	pushl	%esi
  55dfa9:      	calll	0x5c6d00 <.text+0x1c5d00>
  55dfae:      	popl	%ecx
  55dfaf:      	movl	0xc7018c, %ecx
  55dfb5:      	movl	%ecx, %esi
  55dfb7:      	cmpl	%edi, %ecx
  55dfb9:      	je	0x55dfc7 <.text+0x15cfc7>
  55dfbb:      	calll	0x56f3bb <.text+0x16e3bb>
  55dfc0:      	pushl	%esi
  55dfc1:      	calll	0x5c6d00 <.text+0x1c5d00>
  55dfc6:      	popl	%ecx
  55dfc7:      	movl	0xc70188, %ecx
  55dfcd:      	movl	%ecx, %esi
  55dfcf:      	cmpl	%edi, %ecx
  55dfd1:      	je	0x55dfdf <.text+0x15cfdf>
  55dfd3:      	calll	0x56f3bb <.text+0x16e3bb>
  55dfd8:      	pushl	%esi
  55dfd9:      	calll	0x5c6d00 <.text+0x1c5d00>
  55dfde:      	popl	%ecx
  55dfdf:      	movl	0xc70184, %ecx
  55dfe5:      	movl	%ecx, %esi
  55dfe7:      	cmpl	%edi, %ecx
  55dfe9:      	je	0x55dff7 <.text+0x15cff7>
  55dfeb:      	calll	0x56f3bb <.text+0x16e3bb>
  55dff0:      	pushl	%esi
  55dff1:      	calll	0x5c6d00 <.text+0x1c5d00>
  55dff6:      	popl	%ecx
  55dff7:      	movl	0xc7017c, %ecx
  55dffd:      	movl	%ecx, %esi
  55dfff:      	cmpl	%edi, %ecx
  55e001:      	je	0x55e00f <.text+0x15d00f>
  55e003:      	calll	0x56f3bb <.text+0x16e3bb>
  55e008:      	pushl	%esi
  55e009:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e00e:      	popl	%ecx
  55e00f:      	movl	0xc70180, %ecx
  55e015:      	movl	%ecx, %esi
  55e017:      	cmpl	%edi, %ecx
  55e019:      	je	0x55e027 <.text+0x15d027>
  55e01b:      	calll	0x56f3bb <.text+0x16e3bb>
  55e020:      	pushl	%esi
  55e021:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e026:      	popl	%ecx
  55e027:      	movl	0xc70174, %ecx
  55e02d:      	movl	%ecx, %esi
  55e02f:      	cmpl	%edi, %ecx
  55e031:      	je	0x55e03f <.text+0x15d03f>
  55e033:      	calll	0x56f3bb <.text+0x16e3bb>
  55e038:      	pushl	%esi
  55e039:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e03e:      	popl	%ecx
  55e03f:      	movl	0xc70178, %ecx
  55e045:      	movl	%ecx, %esi
  55e047:      	cmpl	%edi, %ecx
  55e049:      	je	0x55e057 <.text+0x15d057>
  55e04b:      	calll	0x56f3bb <.text+0x16e3bb>
  55e050:      	pushl	%esi
  55e051:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e056:      	popl	%ecx
  55e057:      	movl	0xc70170, %ecx
  55e05d:      	movl	%ecx, %esi
  55e05f:      	cmpl	%edi, %ecx
  55e061:      	je	0x55e06f <.text+0x15d06f>
  55e063:      	calll	0x56f3bb <.text+0x16e3bb>
  55e068:      	pushl	%esi
  55e069:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e06e:      	popl	%ecx
  55e06f:      	movl	0xc701b8, %ecx
  55e075:      	movl	%ecx, %esi
  55e077:      	cmpl	%edi, %ecx
  55e079:      	je	0x55e087 <.text+0x15d087>
  55e07b:      	calll	0x56f3bb <.text+0x16e3bb>
  55e080:      	pushl	%esi
  55e081:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e086:      	popl	%ecx
  55e087:      	movl	0xc701b4, %ecx
  55e08d:      	movl	%ecx, %esi
  55e08f:      	cmpl	%edi, %ecx
  55e091:      	je	0x55e09f <.text+0x15d09f>
  55e093:      	calll	0x56f3bb <.text+0x16e3bb>
  55e098:      	pushl	%esi
  55e099:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e09e:      	popl	%ecx
  55e09f:      	movl	0xc701b0, %ecx
  55e0a5:      	movl	%ecx, %esi
  55e0a7:      	cmpl	%edi, %ecx
  55e0a9:      	je	0x55e0b7 <.text+0x15d0b7>
  55e0ab:      	calll	0x56f3bb <.text+0x16e3bb>
  55e0b0:      	pushl	%esi
  55e0b1:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e0b6:      	popl	%ecx
  55e0b7:      	movl	0xc701ac, %ecx
  55e0bd:      	movl	%ecx, %esi
  55e0bf:      	cmpl	%edi, %ecx
  55e0c1:      	je	0x55e0cf <.text+0x15d0cf>
  55e0c3:      	calll	0x56f3bb <.text+0x16e3bb>
  55e0c8:      	pushl	%esi
  55e0c9:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e0ce:      	popl	%ecx
  55e0cf:      	movl	0xc701a8, %ecx
  55e0d5:      	movl	%ecx, %esi
  55e0d7:      	cmpl	%edi, %ecx
  55e0d9:      	je	0x55e0e7 <.text+0x15d0e7>
  55e0db:      	calll	0x56f3bb <.text+0x16e3bb>
  55e0e0:      	pushl	%esi
  55e0e1:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e0e6:      	popl	%ecx
  55e0e7:      	movl	0xc701a4, %ecx
  55e0ed:      	movl	%ecx, %esi
  55e0ef:      	cmpl	%edi, %ecx
  55e0f1:      	je	0x55e0ff <.text+0x15d0ff>
  55e0f3:      	calll	0x56f3bb <.text+0x16e3bb>
  55e0f8:      	pushl	%esi
  55e0f9:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e0fe:      	popl	%ecx
  55e0ff:      	movl	0xc701a0, %ecx
  55e105:      	movl	%ecx, %esi
  55e107:      	cmpl	%edi, %ecx
  55e109:      	je	0x55e117 <.text+0x15d117>
  55e10b:      	calll	0x56f3bb <.text+0x16e3bb>
  55e110:      	pushl	%esi
  55e111:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e116:      	popl	%ecx
  55e117:      	movl	0xc7019c, %ecx
  55e11d:      	movl	%ecx, %esi
  55e11f:      	cmpl	%edi, %ecx
  55e121:      	je	0x55e12f <.text+0x15d12f>
  55e123:      	calll	0x56f3bb <.text+0x16e3bb>
  55e128:      	pushl	%esi
  55e129:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e12e:      	popl	%ecx
  55e12f:      	movl	0xc7016c, %ecx
  55e135:      	movl	%ecx, %esi
  55e137:      	cmpl	%edi, %ecx
  55e139:      	je	0x55e147 <.text+0x15d147>
  55e13b:      	calll	0x5717b4 <.text+0x1707b4>
  55e140:      	pushl	%esi
  55e141:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e146:      	popl	%ecx
  55e147:      	movl	0xc6fdb8, %ecx
  55e14d:      	movl	%ecx, %esi
  55e14f:      	cmpl	%edi, %ecx
  55e151:      	je	0x55e15f <.text+0x15d15f>
  55e153:      	calll	0x5717b4 <.text+0x1707b4>
  55e158:      	pushl	%esi
  55e159:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e15e:      	popl	%ecx
  55e15f:      	movl	0xc70168, %ecx
  55e165:      	movl	%edi, 0xc6fdb8
  55e16b:      	movl	%ecx, %esi
  55e16d:      	cmpl	%edi, %ecx
  55e16f:      	je	0x55e17d <.text+0x15d17d>
  55e171:      	calll	0x5717b4 <.text+0x1707b4>
  55e176:      	pushl	%esi
  55e177:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e17c:      	popl	%ecx
  55e17d:      	movl	0xc70164, %ecx
  55e183:      	movl	%ecx, %esi
  55e185:      	cmpl	%edi, %ecx
  55e187:      	je	0x55e195 <.text+0x15d195>
  55e189:      	calll	0x5717b4 <.text+0x1707b4>
  55e18e:      	pushl	%esi
  55e18f:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e194:      	popl	%ecx
  55e195:      	movl	0xc70160, %ecx
  55e19b:      	movl	%ecx, %esi
  55e19d:      	cmpl	%edi, %ecx
  55e19f:      	je	0x55e1ad <.text+0x15d1ad>
  55e1a1:      	calll	0x5717b4 <.text+0x1707b4>
  55e1a6:      	pushl	%esi
  55e1a7:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e1ac:      	popl	%ecx
  55e1ad:      	movl	0xc7015c, %ecx
  55e1b3:      	movl	%ecx, %esi
  55e1b5:      	cmpl	%edi, %ecx
  55e1b7:      	je	0x55e1c5 <.text+0x15d1c5>
  55e1b9:      	calll	0x5717b4 <.text+0x1707b4>
  55e1be:      	pushl	%esi
  55e1bf:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e1c4:      	popl	%ecx
  55e1c5:      	movl	0xc70158, %ecx
  55e1cb:      	movl	%ecx, %esi
  55e1cd:      	cmpl	%edi, %ecx
  55e1cf:      	je	0x55e1dd <.text+0x15d1dd>
  55e1d1:      	calll	0x5717b4 <.text+0x1707b4>
  55e1d6:      	pushl	%esi
  55e1d7:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e1dc:      	popl	%ecx
  55e1dd:      	movl	0xc70154, %ecx
  55e1e3:      	movl	%ecx, %esi
  55e1e5:      	cmpl	%edi, %ecx
  55e1e7:      	je	0x55e1f5 <.text+0x15d1f5>
  55e1e9:      	calll	0x5717b4 <.text+0x1707b4>
  55e1ee:      	pushl	%esi
  55e1ef:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e1f4:      	popl	%ecx
  55e1f5:      	movl	0xc70150, %ecx
  55e1fb:      	movl	%ecx, %esi
  55e1fd:      	cmpl	%edi, %ecx
  55e1ff:      	je	0x55e20d <.text+0x15d20d>
  55e201:      	calll	0x5717b4 <.text+0x1707b4>
  55e206:      	pushl	%esi
  55e207:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e20c:      	popl	%ecx
  55e20d:      	movl	0xc7014c, %ecx
  55e213:      	movl	%ecx, %esi
  55e215:      	cmpl	%edi, %ecx
  55e217:      	je	0x55e225 <.text+0x15d225>
  55e219:      	calll	0x5717b4 <.text+0x1707b4>
  55e21e:      	pushl	%esi
  55e21f:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e224:      	popl	%ecx
  55e225:      	movl	0xc70144, %ecx
  55e22b:      	movl	%ecx, %esi
  55e22d:      	cmpl	%edi, %ecx
  55e22f:      	je	0x55e23d <.text+0x15d23d>
  55e231:      	calll	0x5717b4 <.text+0x1707b4>
  55e236:      	pushl	%esi
  55e237:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e23c:      	popl	%ecx
  55e23d:      	movl	0xc70140, %ecx
  55e243:      	movl	%ecx, %esi
  55e245:      	cmpl	%edi, %ecx
  55e247:      	je	0x55e255 <.text+0x15d255>
  55e249:      	calll	0x570263 <.text+0x16f263>
  55e24e:      	pushl	%esi
  55e24f:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e254:      	popl	%ecx
  55e255:      	movl	0xc7013c, %ecx
  55e25b:      	movl	%ecx, %esi
  55e25d:      	cmpl	%edi, %ecx
  55e25f:      	je	0x55e26d <.text+0x15d26d>
  55e261:      	calll	0x570263 <.text+0x16f263>
  55e266:      	pushl	%esi
  55e267:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e26c:      	popl	%ecx
  55e26d:      	movl	0xc70138, %ecx
  55e273:      	movl	%ecx, %esi
  55e275:      	cmpl	%edi, %ecx
  55e277:      	je	0x55e285 <.text+0x15d285>
  55e279:      	calll	0x570263 <.text+0x16f263>
  55e27e:      	pushl	%esi
  55e27f:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e284:      	popl	%ecx
  55e285:      	movl	0xc70134, %ecx
  55e28b:      	movl	%ecx, %esi
  55e28d:      	cmpl	%edi, %ecx
  55e28f:      	je	0x55e29d <.text+0x15d29d>
  55e291:      	calll	0x570263 <.text+0x16f263>
  55e296:      	pushl	%esi
  55e297:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e29c:      	popl	%ecx
  55e29d:      	movl	0xc70130, %ecx
  55e2a3:      	movl	%ecx, %esi
  55e2a5:      	cmpl	%edi, %ecx
  55e2a7:      	je	0x55e2b5 <.text+0x15d2b5>
  55e2a9:      	calll	0x570263 <.text+0x16f263>
  55e2ae:      	pushl	%esi
  55e2af:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e2b4:      	popl	%ecx
  55e2b5:      	movl	0xc7012c, %ecx
  55e2bb:      	movl	%ecx, %esi
  55e2bd:      	cmpl	%edi, %ecx
  55e2bf:      	je	0x55e2cd <.text+0x15d2cd>
  55e2c1:      	calll	0x570263 <.text+0x16f263>
  55e2c6:      	pushl	%esi
  55e2c7:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e2cc:      	popl	%ecx
  55e2cd:      	movl	0xc70128, %ecx
  55e2d3:      	movl	%ecx, %esi
  55e2d5:      	cmpl	%edi, %ecx
  55e2d7:      	je	0x55e2e5 <.text+0x15d2e5>
  55e2d9:      	calll	0x570263 <.text+0x16f263>
  55e2de:      	pushl	%esi
  55e2df:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e2e4:      	popl	%ecx
  55e2e5:      	movl	0xc70124, %ecx
  55e2eb:      	movl	%ecx, %esi
  55e2ed:      	cmpl	%edi, %ecx
  55e2ef:      	je	0x55e2fd <.text+0x15d2fd>
  55e2f1:      	calll	0x570263 <.text+0x16f263>
  55e2f6:      	pushl	%esi
  55e2f7:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e2fc:      	popl	%ecx
  55e2fd:      	movl	0xc70120, %ecx
  55e303:      	movl	%ecx, %esi
  55e305:      	cmpl	%edi, %ecx
  55e307:      	je	0x55e315 <.text+0x15d315>
  55e309:      	calll	0x570263 <.text+0x16f263>
  55e30e:      	pushl	%esi
  55e30f:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e314:      	popl	%ecx
  55e315:      	movl	0xc7011c, %ecx
  55e31b:      	movl	%ecx, %esi
  55e31d:      	cmpl	%edi, %ecx
  55e31f:      	je	0x55e32d <.text+0x15d32d>
  55e321:      	calll	0x570263 <.text+0x16f263>
  55e326:      	pushl	%esi
  55e327:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e32c:      	popl	%ecx
  55e32d:      	movl	0xc70118, %ecx
  55e333:      	movl	%ecx, %esi
  55e335:      	cmpl	%edi, %ecx
  55e337:      	je	0x55e345 <.text+0x15d345>
  55e339:      	calll	0x570263 <.text+0x16f263>
  55e33e:      	pushl	%esi
  55e33f:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e344:      	popl	%ecx
  55e345:      	movl	0xc70114, %ecx
  55e34b:      	movl	%ecx, %esi
  55e34d:      	cmpl	%edi, %ecx
  55e34f:      	je	0x55e35d <.text+0x15d35d>
  55e351:      	calll	0x570263 <.text+0x16f263>
  55e356:      	pushl	%esi
  55e357:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e35c:      	popl	%ecx
  55e35d:      	movl	0xc70110, %ecx
  55e363:      	movl	%ecx, %esi
  55e365:      	cmpl	%edi, %ecx
  55e367:      	je	0x55e375 <.text+0x15d375>
  55e369:      	calll	0x570263 <.text+0x16f263>
  55e36e:      	pushl	%esi
  55e36f:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e374:      	popl	%ecx
  55e375:      	movl	0xc7010c, %ecx
  55e37b:      	movl	%ecx, %esi
  55e37d:      	cmpl	%edi, %ecx
  55e37f:      	je	0x55e38d <.text+0x15d38d>
  55e381:      	calll	0x570263 <.text+0x16f263>
  55e386:      	pushl	%esi
  55e387:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e38c:      	popl	%ecx
  55e38d:      	movl	0xc700fc, %ecx
  55e393:      	cmpl	%edi, %ecx
  55e395:      	je	0x55e3a5 <.text+0x15d3a5>
  55e397:      	movl	%ecx, %esi
  55e399:      	calll	0x570263 <.text+0x16f263>
  55e39e:      	pushl	%esi
  55e39f:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e3a4:      	popl	%ecx
  55e3a5:      	movl	0xc70108, %ecx
  55e3ab:      	movl	%edi, 0xc700fc
  55e3b1:      	movl	%ecx, %esi
  55e3b3:      	cmpl	%edi, %ecx
  55e3b5:      	je	0x55e3c3 <.text+0x15d3c3>
  55e3b7:      	calll	0x570499 <.text+0x16f499>
  55e3bc:      	pushl	%esi
  55e3bd:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e3c2:      	popl	%ecx
  55e3c3:      	movl	0xc70104, %ecx
  55e3c9:      	movl	%ecx, %esi
  55e3cb:      	cmpl	%edi, %ecx
  55e3cd:      	je	0x55e3db <.text+0x15d3db>
  55e3cf:      	calll	0x570499 <.text+0x16f499>
  55e3d4:      	pushl	%esi
  55e3d5:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e3da:      	popl	%ecx
  55e3db:      	movl	0xc70100, %ecx
  55e3e1:      	movl	%ecx, %esi
  55e3e3:      	cmpl	%edi, %ecx
  55e3e5:      	je	0x55e3f3 <.text+0x15d3f3>
  55e3e7:      	calll	0x570263 <.text+0x16f263>
  55e3ec:      	pushl	%esi
  55e3ed:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e3f2:      	popl	%ecx
  55e3f3:      	movl	0xc70198, %ecx
  55e3f9:      	movl	%ecx, %esi
  55e3fb:      	cmpl	%edi, %ecx
  55e3fd:      	je	0x55e40b <.text+0x15d40b>
  55e3ff:      	calll	0x56f3bb <.text+0x16e3bb>
  55e404:      	pushl	%esi
  55e405:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e40a:      	popl	%ecx
  55e40b:      	movl	0xc70194, %ecx
  55e411:      	movl	%ecx, %esi
  55e413:      	cmpl	%edi, %ecx
  55e415:      	je	0x55e423 <.text+0x15d423>
  55e417:      	calll	0x56f3bb <.text+0x16e3bb>
  55e41c:      	pushl	%esi
  55e41d:      	calll	0x5c6d00 <.text+0x1c5d00>
  55e422:      	popl	%ecx
  55e423:      	pushl	0xc700f0
  55e429:      	movl	0x5ce054, %esi
  55e42f:      	calll	*%esi
  55e431:      	pushl	0xc700ec
  55e437:      	calll	*%esi
  55e439:      	pushl	0xc700e8
  55e43f:      	calll	*%esi
  55e441:      	pushl	0xc700e4
  55e447:      	calll	*%esi
  55e449:      	pushl	0xc700d0(%edi)
  55e44f:      	calll	*%esi
  55e451:      	addl	$0x4, %edi
  55e454:      	cmpl	$0x14, %edi
  55e457:      	jb	0x55e449 <.text+0x15d449>
  55e459:      	pushl	0xc700cc
  55e45f:      	calll	*%esi
  55e461:      	pushl	0xc700c8
  55e467:      	calll	*%esi
  55e469:      	jmp	0x55eb35 <.text+0x15db35>
  55e46e:      	cmpl	$-0x1, 0x8(%esi)
  55e472:      	je	0x55eb35 <.text+0x15db35>
  55e478:      	movl	0xc(%esi), %eax
  55e47b:      	decl	%eax
  55e47c:      	cmpl	$0x1, %eax
  55e47f:      	ja	0x560d63 <.text+0x15fd63>
  55e485:      	movl	0x5ce53c, %ebp
  55e48b:      	movl	0x14(%esi), %edi
  55e48e:      	pushl	$0x7e5                  # imm = 0x7E5
  55e493:      	pushl	%ebx
  55e494:      	calll	*%ebp
  55e496:      	cmpl	%eax, %edi
  55e498:      	jne	0x55e633 <.text+0x15d633>
  55e49e:      	xorl	%ebx, %ebx
  55e4a0:      	pushl	%ebx
  55e4a1:      	pushl	0x8(%esi)
  55e4a4:      	pushl	$0x199                  # imm = 0x199
  55e4a9:      	pushl	%edi
  55e4aa:      	calll	*0x5ce558
  55e4b0:      	movl	%eax, 0x14(%esp)
  55e4b4:      	leal	0x258(%esp), %eax
  55e4bb:      	pushl	%eax
  55e4bc:      	pushl	0x18(%esi)
  55e4bf:      	calll	*0x5ce084
  55e4c5:      	movl	0x20(%esi), %edi
  55e4c8:      	movl	0x28(%esi), %ecx
  55e4cb:      	movl	%edi, %eax
  55e4cd:      	subl	0x258(%esp), %eax
  55e4d4:      	addl	%ecx, %eax
  55e4d6:      	cltd
  55e4d7:      	subl	%edx, %eax
  55e4d9:      	movl	%eax, %ebp
  55e4db:      	movl	0x1c(%esi), %eax
  55e4de:      	sarl	%ebp
  55e4e0:      	testb	$0x1, 0x10(%esi)
  55e4e4:      	je	0x55e52a <.text+0x15d52a>
  55e4e6:      	movl	%eax, 0x20(%esp)
  55e4ea:      	movl	0x24(%esi), %eax
  55e4ed:      	movl	%eax, 0x28(%esp)
  55e4f1:      	leal	0x20(%esp), %eax
  55e4f5:      	pushl	%eax
  55e4f6:      	pushl	0x18(%esi)
  55e4f9:      	movl	%edi, 0x2c(%esp)
  55e4fd:      	movl	%ecx, 0x34(%esp)
  55e501:      	calll	*0x5ce524
  55e507:      	leal	0x4c(%esp), %eax
  55e50b:      	pushl	%eax
  55e50c:      	movl	%ebx, 0x50(%esp)
  55e510:      	movl	$0x6400, 0x54(%esp)     # imm = 0x6400
  55e518:      	movl	%ebx, 0x58(%esp)
  55e51c:      	calll	*0x5ce088
  55e522:      	movl	%eax, %edi
  55e524:      	leal	0x20(%esp), %eax
  55e528:      	jmp	0x55e55a <.text+0x15d55a>
  55e52a:      	movl	%eax, 0x3c(%esp)
  55e52e:      	movl	0x24(%esi), %eax
  55e531:      	movl	%eax, 0x44(%esp)
  55e535:      	leal	0x4c(%esp), %eax
  55e539:      	pushl	%eax
  55e53a:      	movl	%edi, 0x44(%esp)
  55e53e:      	movl	%ecx, 0x4c(%esp)
  55e542:      	movl	%ebx, 0x50(%esp)
  55e546:      	movl	%ebx, 0x54(%esp)
  55e54a:      	movl	%ebx, 0x58(%esp)
  55e54e:      	calll	*0x5ce088
  55e554:      	movl	%eax, %edi
  55e556:      	leal	0x3c(%esp), %eax
  55e55a:      	pushl	%edi
  55e55b:      	pushl	%eax
  55e55c:      	pushl	0x18(%esi)
  55e55f:      	calll	*0x5ce528
  55e565:      	cmpl	%ebx, %edi
  55e567:      	je	0x55e570 <.text+0x15d570>
  55e569:      	pushl	%edi
  55e56a:      	calll	*0x5ce054
  55e570:      	pushl	0x18(%esi)
  55e573:      	calll	*0x5ce0d0
  55e579:      	pushl	0x14(%esp)
  55e57d:      	movl	0xc701e4, %ecx
  55e583:      	movl	%eax, %edi
  55e585:      	movl	%ebx, 0x1c(%esp)
  55e589:      	calll	0x551cf8 <.text+0x150cf8>
  55e58e:      	xorl	%ecx, %ecx
  55e590:      	movl	$0x633b00, %edx         # imm = 0x633B00
  55e595:      	movl	0x5ce050, %ebx
  55e59b:      	cmpb	(%edx), %al
  55e59d:      	je	0x55e5aa <.text+0x15d5aa>
  55e59f:      	incl	%ecx
  55e5a0:      	addl	$0x10, %edx
  55e5a3:      	cmpl	$0x5, %ecx
  55e5a6:      	jb	0x55e595 <.text+0x15d595>
  55e5a8:      	jmp	0x55e5b8 <.text+0x15d5b8>
  55e5aa:      	pushl	0xc700d0(,%ecx,4)
  55e5b1:      	pushl	%edi
  55e5b2:      	calll	*%ebx
  55e5b4:      	movl	%eax, 0x18(%esp)
  55e5b8:      	movl	0x20(%esi), %eax
  55e5bb:      	movl	0x28(%esi), %edx
  55e5be:      	movl	0x1c(%esi), %ecx
  55e5c1:      	pushl	$0xcc0020               # imm = 0xCC0020
  55e5c6:      	pushl	$0x0
  55e5c8:      	pushl	$0x0
  55e5ca:      	subl	%eax, %edx
  55e5cc:      	pushl	%edi
  55e5cd:      	subl	$0x3, %edx
  55e5d0:      	pushl	%edx
  55e5d1:      	movl	0x24(%esi), %edx
  55e5d4:      	subl	%ecx, %edx
  55e5d6:      	decl	%edx
  55e5d7:      	decl	%edx
  55e5d8:      	pushl	%edx
  55e5d9:      	addl	$0x3, %eax
  55e5dc:      	pushl	%eax
  55e5dd:      	addl	$0x2, %ecx
  55e5e0:      	pushl	%ecx
  55e5e1:      	pushl	0x18(%esi)
  55e5e4:      	calll	*0x5ce08c
  55e5ea:      	pushl	0x18(%esp)
  55e5ee:      	pushl	%edi
  55e5ef:      	calll	*%ebx
  55e5f1:      	pushl	%edi
  55e5f2:      	calll	*0x5ce03c
  55e5f8:      	movl	0xc701e4, %edi
  55e5fe:      	pushl	0x14(%esp)
  55e602:      	movl	%edi, %ecx
  55e604:      	calll	0x551d3e <.text+0x150d3e>
  55e609:      	leal	0x1(%eax), %ecx
  55e60c:      	movb	(%eax), %dl
  55e60e:      	incl	%eax
  55e60f:      	testb	%dl, %dl
  55e611:      	jne	0x55e60c <.text+0x15d60c>
  55e613:      	subl	%ecx, %eax
  55e615:      	pushl	%eax
  55e616:      	pushl	0x18(%esp)
  55e61a:      	movl	%edi, %ecx
  55e61c:      	calll	0x551d3e <.text+0x150d3e>
  55e621:      	pushl	%eax
  55e622:      	pushl	%ebp
  55e623:      	pushl	$0xe
  55e625:      	pushl	0x18(%esi)
  55e628:      	calll	*0x5ce0a8
  55e62e:      	jmp	0x560d63 <.text+0x15fd63>
  55e633:      	movl	0x14(%esi), %edi
  55e636:      	pushl	$0x822                  # imm = 0x822
  55e63b:      	pushl	%ebx
  55e63c:      	calll	*%ebp
  55e63e:      	cmpl	%eax, %edi
  55e640:      	jne	0x560d63 <.text+0x15fd63>
  55e646:      	xorl	%ebp, %ebp
  55e648:      	pushl	%ebp
  55e649:      	pushl	0x8(%esi)
  55e64c:      	pushl	$0x199                  # imm = 0x199
  55e651:      	pushl	%edi
  55e652:      	calll	*0x5ce558
  55e658:      	pushl	%eax
  55e659:      	movl	$0xc6fef8, %ecx         # imm = 0xC6FEF8
  55e65e:      	calll	0x558bff <.text+0x157bff>
  55e663:      	movl	%eax, %ebx
  55e665:      	cmpl	%ebp, %ebx
  55e667:      	je	0x560d63 <.text+0x15fd63>
  55e66d:      	leal	0x258(%esp), %eax
  55e674:      	pushl	%eax
  55e675:      	pushl	0x18(%esi)
  55e678:      	calll	*0x5ce084
  55e67e:      	movl	0x20(%esi), %edi
  55e681:      	movl	0x28(%esi), %ecx
  55e684:      	movl	%edi, %eax
  55e686:      	subl	0x258(%esp), %eax
  55e68d:      	movl	%edi, 0x40(%esp)
  55e691:      	addl	%ecx, %eax
  55e693:      	cltd
  55e694:      	subl	%edx, %eax
  55e696:      	sarl	%eax
  55e698:      	testb	$0x1, 0x10(%esi)
  55e69c:      	movl	%eax, 0x14(%esp)
  55e6a0:      	movl	0x1c(%esi), %eax
  55e6a3:      	movl	%eax, 0x3c(%esp)
  55e6a7:      	movl	0x24(%esi), %eax
  55e6aa:      	movl	%ecx, 0x48(%esp)
  55e6ae:      	movl	%eax, 0x44(%esp)
  55e6b2:      	je	0x55e6cc <.text+0x15d6cc>
  55e6b4:      	leal	0x3c(%esp), %eax
  55e6b8:      	pushl	%eax
  55e6b9:      	pushl	0x18(%esi)
  55e6bc:      	calll	*0x5ce524
  55e6c2:      	movl	$0x6400, 0x34(%esp)     # imm = 0x6400
  55e6ca:      	jmp	0x55e6d0 <.text+0x15d6d0>
  55e6cc:      	movl	%ebp, 0x34(%esp)
  55e6d0:      	leal	0x30(%esp), %eax
  55e6d4:      	pushl	%eax
  55e6d5:      	movl	%ebp, 0x34(%esp)
  55e6d9:      	movl	%ebp, 0x3c(%esp)
  55e6dd:      	calll	*0x5ce088
  55e6e3:      	movl	%eax, %edi
  55e6e5:      	pushl	%edi
  55e6e6:      	leal	0x40(%esp), %eax
  55e6ea:      	pushl	%eax
  55e6eb:      	pushl	0x18(%esi)
  55e6ee:      	calll	*0x5ce528
  55e6f4:      	cmpl	%ebp, %edi
  55e6f6:      	je	0x55e6ff <.text+0x15d6ff>
  55e6f8:      	pushl	%edi
  55e6f9:      	calll	*0x5ce054
  55e6ff:      	movzwl	0x22(%ebx), %eax
  55e703:      	pushl	%eax
  55e704:      	movl	$0xc6fef8, %ecx         # imm = 0xC6FEF8
  55e709:      	calll	0x558c66 <.text+0x157c66>
  55e70e:      	movl	0x5ce050, %edi
  55e714:      	movl	0x5ce08c, %ebp
  55e71a:      	testb	%al, %al
  55e71c:      	je	0x55e778 <.text+0x15d778>
  55e71e:      	pushl	0x18(%esi)
  55e721:      	calll	*0x5ce0d0
  55e727:      	pushl	0xc700f0
  55e72d:      	movl	%eax, 0x14(%esp)
  55e731:      	pushl	%eax
  55e732:      	calll	*%edi
  55e734:      	movl	0x28(%esi), %edx
  55e737:      	movl	0x1c(%esi), %ecx
  55e73a:      	pushl	$0xcc0020               # imm = 0xCC0020
  55e73f:      	pushl	$0x0
  55e741:      	pushl	$0x0
  55e743:      	pushl	0x1c(%esp)
  55e747:      	movl	%eax, 0x28(%esp)
  55e74b:      	movl	0x20(%esi), %eax
  55e74e:      	subl	%eax, %edx
  55e750:      	subl	$0x3, %edx
  55e753:      	pushl	%edx
  55e754:      	movl	0x24(%esi), %edx
  55e757:      	subl	%ecx, %edx
  55e759:      	pushl	%edx
  55e75a:      	addl	$0x3, %eax
  55e75d:      	pushl	%eax
  55e75e:      	pushl	%ecx
  55e75f:      	pushl	0x18(%esi)
  55e762:      	calll	*%ebp
  55e764:      	pushl	0x18(%esp)
  55e768:      	pushl	0x14(%esp)
  55e76c:      	calll	*%edi
  55e76e:      	pushl	0x10(%esp)
  55e772:      	calll	*0x5ce03c
  55e778:      	movzwl	0x22(%ebx), %eax
  55e77c:      	pushl	%eax
  55e77d:      	movl	$0xc6fef8, %ecx         # imm = 0xC6FEF8
  55e782:      	calll	0x558d24 <.text+0x157d24>
  55e787:      	testb	%al, %al
  55e789:      	je	0x55e7e5 <.text+0x15d7e5>
  55e78b:      	pushl	0x18(%esi)
  55e78e:      	calll	*0x5ce0d0
  55e794:      	pushl	0xc700ec
  55e79a:      	movl	%eax, 0x14(%esp)
  55e79e:      	pushl	%eax
  55e79f:      	calll	*%edi
  55e7a1:      	movl	0x28(%esi), %edx
  55e7a4:      	movl	0x1c(%esi), %ecx
  55e7a7:      	pushl	$0xcc0020               # imm = 0xCC0020
  55e7ac:      	pushl	$0x0
  55e7ae:      	pushl	$0x0
  55e7b0:      	pushl	0x1c(%esp)
  55e7b4:      	movl	%eax, 0x28(%esp)
  55e7b8:      	movl	0x20(%esi), %eax
  55e7bb:      	subl	%eax, %edx
  55e7bd:      	subl	$0x3, %edx
  55e7c0:      	pushl	%edx
  55e7c1:      	movl	0x24(%esi), %edx
  55e7c4:      	subl	%ecx, %edx
  55e7c6:      	pushl	%edx
  55e7c7:      	addl	$0x3, %eax
  55e7ca:      	pushl	%eax
  55e7cb:      	pushl	%ecx
  55e7cc:      	pushl	0x18(%esi)
  55e7cf:      	calll	*%ebp
  55e7d1:      	pushl	0x18(%esp)
  55e7d5:      	pushl	0x14(%esp)
  55e7d9:      	calll	*%edi
  55e7db:      	pushl	0x10(%esp)
  55e7df:      	calll	*0x5ce03c
  55e7e5:      	pushl	0xba7724
  55e7eb:      	calll	0x54fd98 <.text+0x14ed98>
  55e7f0:      	popl	%ecx
  55e7f1:      	testb	%al, %al
  55e7f3:      	je	0x55e863 <.text+0x15d863>
  55e7f5:      	pushl	0x18(%esi)
  55e7f8:      	calll	*0x5ce0d0
  55e7fe:      	cmpb	$0x0, 0x2c(%ebx)
  55e802:      	movl	%eax, 0x10(%esp)
  55e806:      	movl	0xc700e8, %eax
  55e80b:      	jne	0x55e812 <.text+0x15d812>
  55e80d:      	movl	0xc700e4, %eax
  55e812:      	pushl	%eax
  55e813:      	pushl	0x14(%esp)
  55e817:      	calll	*%edi
  55e819:      	movl	0x28(%esi), %edx
  55e81c:      	movl	0x1c(%esi), %ecx
  55e81f:      	pushl	$0xcc0020               # imm = 0xCC0020
  55e824:      	pushl	$0x0
  55e826:      	pushl	$0x0
  55e828:      	pushl	0x1c(%esp)
  55e82c:      	movl	%eax, 0x28(%esp)
  55e830:      	movl	0x20(%esi), %eax
  55e833:      	subl	%eax, %edx
  55e835:      	subl	$0x3, %edx
  55e838:      	pushl	%edx
  55e839:      	movl	0x24(%esi), %edx
  55e83c:      	subl	%ecx, %edx
  55e83e:      	subl	$0xb, %edx
  55e841:      	pushl	%edx
  55e842:      	addl	$0x3, %eax
  55e845:      	pushl	%eax
  55e846:      	addl	$0xb, %ecx
  55e849:      	pushl	%ecx
  55e84a:      	pushl	0x18(%esi)
  55e84d:      	calll	*%ebp
  55e84f:      	pushl	0x18(%esp)
  55e853:      	pushl	0x14(%esp)
  55e857:      	calll	*%edi
  55e859:      	pushl	0x10(%esp)
  55e85d:      	calll	*0x5ce03c
  55e863:      	pushl	0x18(%esi)
  55e866:      	calll	*0x5ce090
  55e86c:      	pushl	0x18(%esi)
  55e86f:      	movl	%eax, 0x20(%esp)
  55e873:      	calll	0x5711bd <.text+0x1701bd>
  55e878:      	movl	$0xff00, (%esp)         # imm = 0xFF00
  55e87f:      	pushl	0x18(%esi)
  55e882:      	calll	*0x5ce04c
  55e888:      	movl	0x20(%esi), %eax
  55e88b:      	movl	%eax, 0x24(%esp)
  55e88f:      	movl	0x28(%esi), %eax
  55e892:      	movl	%eax, 0x2c(%esp)
  55e896:      	movl	%ebx, %eax
  55e898:      	movl	$0x16, 0x20(%esp)
  55e8a0:      	movl	$0x7f, 0x28(%esp)
  55e8a8:      	leal	0x1(%eax), %ecx
  55e8ab:      	movb	(%eax), %dl
  55e8ad:      	incl	%eax
  55e8ae:      	testb	%dl, %dl
  55e8b0:      	jne	0x55e8ab <.text+0x15d8ab>
  55e8b2:      	pushl	$0x0
  55e8b4:      	subl	%ecx, %eax
  55e8b6:      	pushl	%eax
  55e8b7:      	pushl	%ebx
  55e8b8:      	leal	0x2c(%esp), %eax
  55e8bc:      	pushl	%eax
  55e8bd:      	pushl	$0x4
  55e8bf:      	pushl	0x28(%esp)
  55e8c3:      	pushl	$0x16
  55e8c5:      	pushl	0x18(%esi)
  55e8c8:      	calll	*0x5ce094
  55e8ce:      	pushl	0x1c(%esp)
  55e8d2:      	pushl	0x18(%esi)
  55e8d5:      	calll	*0x5ce04c
  55e8db:      	pushl	0x18(%esi)
  55e8de:      	calll	*0x5ce0d0
  55e8e4:      	cmpb	$0x0, 0x2d(%ebx)
  55e8e8:      	movl	%eax, 0x10(%esp)
  55e8ec:      	movl	0xc700cc, %eax
  55e8f1:      	jne	0x55e8f8 <.text+0x15d8f8>
  55e8f3:      	movl	0xc700c8, %eax
  55e8f8:      	pushl	%eax
  55e8f9:      	pushl	0x14(%esp)
  55e8fd:      	calll	*%edi
  55e8ff:      	movl	0x28(%esi), %edx
  55e902:      	movl	0x1c(%esi), %ecx
  55e905:      	pushl	$0xcc0020               # imm = 0xCC0020
  55e90a:      	pushl	$0x0
  55e90c:      	pushl	$0x0
  55e90e:      	pushl	0x1c(%esp)
  55e912:      	movl	%eax, 0x28(%esp)
  55e916:      	movl	0x20(%esi), %eax
  55e919:      	subl	%eax, %edx
  55e91b:      	subl	$0x3, %edx
  55e91e:      	pushl	%edx
  55e91f:      	movl	0x24(%esi), %edx
  55e922:      	subl	%ecx, %edx
  55e924:      	addl	$-0x80, %edx
  55e927:      	pushl	%edx
  55e928:      	addl	$0x3, %eax
  55e92b:      	pushl	%eax
  55e92c:      	subl	$-0x80, %ecx
  55e92f:      	pushl	%ecx
  55e930:      	pushl	0x18(%esi)
  55e933:      	calll	*%ebp
  55e935:      	pushl	0x18(%esp)
  55e939:      	pushl	0x14(%esp)
  55e93d:      	calll	*%edi
  55e93f:      	pushl	0x10(%esp)
  55e943:      	calll	*0x5ce03c
  55e949:      	movl	0xc701e4, %eax
  55e94e:      	cmpl	$0x0, 0x10(%eax)
  55e952:      	je	0x55e964 <.text+0x15d964>
  55e954:      	leal	0x31(%ebx), %ecx
  55e957:      	pushl	%ecx
  55e958:      	movl	0x10(%eax), %ecx
  55e95b:      	calll	0x55164d <.text+0x15064d>
  55e960:      	movl	%eax, %ebp
  55e962:      	jmp	0x55e966 <.text+0x15d966>
  55e964:      	xorl	%ebp, %ebp
  55e966:      	testl	%ebp, %ebp
  55e968:      	je	0x55e9b2 <.text+0x15d9b2>
  55e96a:      	movl	0x20(%esi), %eax
  55e96d:      	movl	%eax, 0x24(%esp)
  55e971:      	movl	0x28(%esi), %eax
  55e974:      	movl	$0x9a, %edi
  55e979:      	movl	%ebp, %ecx
  55e97b:      	movl	%eax, 0x2c(%esp)
  55e97f:      	movl	%edi, 0x20(%esp)
  55e983:      	movl	$0xe8, 0x28(%esp)
  55e98b:      	leal	0x1(%ecx), %eax
  55e98e:      	movb	(%ecx), %dl
  55e990:      	incl	%ecx
  55e991:      	testb	%dl, %dl
  55e993:      	jne	0x55e98e <.text+0x15d98e>
  55e995:      	pushl	$0x0
  55e997:      	subl	%eax, %ecx
  55e999:      	pushl	%ecx
  55e99a:      	pushl	%ebp
  55e99b:      	leal	0x2c(%esp), %eax
  55e99f:      	pushl	%eax
  55e9a0:      	pushl	$0x4
  55e9a2:      	pushl	0x28(%esp)
  55e9a6:      	pushl	%edi
  55e9a7:      	pushl	0x18(%esi)
  55e9aa:      	calll	*0x5ce094
  55e9b0:      	jmp	0x55e9cb <.text+0x15d9cb>
  55e9b2:      	pushl	$0x1
  55e9b4:      	pushl	$0x5f0874               # imm = 0x5F0874
  55e9b9:      	pushl	0x1c(%esp)
  55e9bd:      	pushl	$0x9a
  55e9c2:      	pushl	0x18(%esi)
  55e9c5:      	calll	*0x5ce0a8
  55e9cb:      	movw	0x22(%ebx), %ax
  55e9cf:      	cmpw	0x62aea4, %ax
  55e9d6:      	je	0x55eacc <.text+0x15dacc>
  55e9dc:      	pushl	0x18(%esi)
  55e9df:      	calll	*0x5ce098
  55e9e5:      	pushl	$0x2
  55e9e7:      	pushl	0x18(%esi)
  55e9ea:      	movl	%eax, 0x20(%esp)
  55e9ee:      	calll	*0x5ce09c
  55e9f4:      	movl	0x18(%ebx), %eax
  55e9f7:      	cmpl	$0x3e8, %eax            # imm = 0x3E8
  55e9fc:      	movl	$0xff, %ebp
  55ea01:      	jle	0x55ea06 <.text+0x15da06>
  55ea03:      	pushl	%ebp
  55ea04:      	jmp	0x55ea19 <.text+0x15da19>
  55ea06:      	cmpl	$0x1f4, %eax            # imm = 0x1F4
  55ea0b:      	jle	0x55ea14 <.text+0x15da14>
  55ea0d:      	pushl	$0xffff                 # imm = 0xFFFF
  55ea12:      	jmp	0x55ea19 <.text+0x15da19>
  55ea14:      	pushl	$0xff00                 # imm = 0xFF00
  55ea19:      	pushl	0x18(%esi)
  55ea1c:      	movl	0x5ce04c, %edi
  55ea22:      	calll	*%edi
  55ea24:      	pushl	0x18(%ebx)
  55ea27:      	leal	0x50(%esp), %eax
  55ea2b:      	pushl	$0x5df2a4               # imm = 0x5DF2A4
  55ea30:      	pushl	%eax
  55ea31:      	calll	*0x5ce49c
  55ea37:      	leal	0x58(%esp), %eax
  55ea3b:      	addl	$0xc, %esp
  55ea3e:      	leal	0x1(%eax), %ecx
  55ea41:      	movb	(%eax), %dl
  55ea43:      	incl	%eax
  55ea44:      	testb	%dl, %dl
  55ea46:      	jne	0x55ea41 <.text+0x15da41>
  55ea48:      	subl	%ecx, %eax
  55ea4a:      	pushl	%eax
  55ea4b:      	leal	0x50(%esp), %eax
  55ea4f:      	pushl	%eax
  55ea50:      	pushl	0x1c(%esp)
  55ea54:      	pushl	%ebp
  55ea55:      	pushl	0x18(%esi)
  55ea58:      	calll	*0x5ce0a8
  55ea5e:      	movl	0x1c(%ebx), %eax
  55ea61:      	cmpl	$0x32, %eax
  55ea64:      	jle	0x55ea69 <.text+0x15da69>
  55ea66:      	pushl	%ebp
  55ea67:      	jmp	0x55ea7a <.text+0x15da7a>
  55ea69:      	cmpl	$0x19, %eax
  55ea6c:      	jle	0x55ea75 <.text+0x15da75>
  55ea6e:      	pushl	$0xffff                 # imm = 0xFFFF
  55ea73:      	jmp	0x55ea7a <.text+0x15da7a>
  55ea75:      	pushl	$0xff00                 # imm = 0xFF00
  55ea7a:      	pushl	0x18(%esi)
  55ea7d:      	calll	*%edi
  55ea7f:      	pushl	0x1c(%ebx)
  55ea82:      	leal	0x50(%esp), %eax
  55ea86:      	pushl	$0x5df2a4               # imm = 0x5DF2A4
  55ea8b:      	pushl	%eax
  55ea8c:      	calll	*0x5ce49c
  55ea92:      	leal	0x58(%esp), %eax
  55ea96:      	addl	$0xc, %esp
  55ea99:      	leal	0x1(%eax), %ecx
  55ea9c:      	movb	(%eax), %dl
  55ea9e:      	incl	%eax
  55ea9f:      	testb	%dl, %dl
  55eaa1:      	jne	0x55ea9c <.text+0x15da9c>
  55eaa3:      	subl	%ecx, %eax
  55eaa5:      	pushl	%eax
  55eaa6:      	leal	0x50(%esp), %eax
  55eaaa:      	pushl	%eax
  55eaab:      	pushl	0x1c(%esp)
  55eaaf:      	pushl	$0x11c                  # imm = 0x11C
  55eab4:      	pushl	0x18(%esi)
  55eab7:      	calll	*0x5ce0a8
  55eabd:      	pushl	0x18(%esp)
  55eac1:      	pushl	0x18(%esi)
  55eac4:      	calll	*0x5ce09c
  55eaca:      	jmp	0x55ead2 <.text+0x15dad2>
  55eacc:      	movl	0x5ce04c, %edi
  55ead2:      	pushl	0x1c(%esp)
  55ead6:      	pushl	0x18(%esi)
  55ead9:      	calll	*%edi
  55eadb:      	jmp	0x560d63 <.text+0x15fd63>
  55eae0:      	subl	$0x2c, %eax
  55eae3:      	je	0x560cd3 <.text+0x15fcd3>
  55eae9:      	subl	$0xe4, %eax
  55eaee:      	je	0x55eccc <.text+0x15dccc>
  55eaf4:      	decl	%eax
  55eaf5:      	jne	0x55eb35 <.text+0x15db35>
  55eaf7:      	movzwl	%di, %eax
  55eafa:      	decl	%eax
  55eafb:      	je	0x55ec94 <.text+0x15dc94>
  55eb01:      	subl	$0x7e4, %eax            # imm = 0x7E4
  55eb06:      	je	0x55eb2f <.text+0x15db2f>
  55eb08:      	subl	$0x3d, %eax
  55eb0b:      	jne	0x55eb35 <.text+0x15db35>
  55eb0d:      	shrl	$0x10, %edi
  55eb10:      	decl	%edi
  55eb11:      	jne	0x55eb35 <.text+0x15db35>
  55eb13:      	movl	0xc6ff04, %eax
  55eb18:      	testl	%eax, %eax
  55eb1a:      	je	0x560d63 <.text+0x15fd63>
  55eb20:      	pushl	$0x1
  55eb22:      	pushl	%edi
  55eb23:      	pushl	%eax
  55eb24:      	calll	*0x5ce550
  55eb2a:      	jmp	0x560d63 <.text+0x15fd63>
  55eb2f:      	shrl	$0x10, %edi
  55eb32:      	decl	%edi
  55eb33:      	je	0x55eb3c <.text+0x15db3c>
  55eb35:      	xorl	%eax, %eax
  55eb37:      	jmp	0x56301e <.text+0x16201e>
  55eb3c:      	movl	0xc701e4, %ecx
  55eb42:      	calll	0x5598ef <.text+0x1588ef>
  55eb47:      	movl	0xc701e4, %ecx
  55eb4d:      	calll	0x551d61 <.text+0x150d61>
  55eb52:      	movl	0xc701e4, %ecx
  55eb58:      	calll	0x551d18 <.text+0x150d18>
  55eb5d:      	subl	$0x0, %eax
  55eb60:      	pushl	$0x1
  55eb62:      	popl	%esi
  55eb63:      	je	0x55ebff <.text+0x15dbff>
  55eb69:      	decl	%eax
  55eb6a:      	jne	0x561361 <.text+0x160361>
  55eb70:      	movl	0xc7018c, %ecx
  55eb76:      	pushl	%esi
  55eb77:      	calll	0x56f435 <.text+0x16e435>
  55eb7c:      	movl	0xc7015c, %ecx
  55eb82:      	pushl	%esi
  55eb83:      	calll	0x57403d <.text+0x17303d>
  55eb88:      	movl	0xc70188, %ecx
  55eb8e:      	pushl	%esi
  55eb8f:      	calll	0x56f435 <.text+0x16e435>
  55eb94:      	movl	0xc70158, %ecx
  55eb9a:      	pushl	%esi
  55eb9b:      	calll	0x57403d <.text+0x17303d>
  55eba0:      	movl	0xc701bc, %ecx
  55eba6:      	pushl	%esi
  55eba7:      	calll	0x573f6e <.text+0x172f6e>
  55ebac:      	movl	0xc70164, %ecx
  55ebb2:      	pushl	%esi
  55ebb3:      	calll	0x574011 <.text+0x173011>
  55ebb8:      	movl	0xc701c8, %ecx
  55ebbe:      	pushl	%esi
  55ebbf:      	calll	0x573f6e <.text+0x172f6e>
  55ebc4:      	movl	0xc7016c, %ecx
  55ebca:      	pushl	%esi
  55ebcb:      	calll	0x574011 <.text+0x173011>
  55ebd0:      	movl	0xc701c0, %ecx
  55ebd6:      	pushl	%esi
  55ebd7:      	calll	0x573f6e <.text+0x172f6e>
  55ebdc:      	movl	0xc70168, %ecx
  55ebe2:      	pushl	%esi
  55ebe3:      	calll	0x574011 <.text+0x173011>
  55ebe8:      	movl	0xc70180, %ecx
  55ebee:      	pushl	%esi
  55ebef:      	calll	0x573f6e <.text+0x172f6e>
  55ebf4:      	movl	0xc70150, %ecx
  55ebfa:      	jmp	0x55ec89 <.text+0x15dc89>
  55ebff:      	movl	0xc701c8, %ecx
  55ec05:      	pushl	%esi
  55ec06:      	calll	0x56f435 <.text+0x16e435>
  55ec0b:      	movl	0xc7016c, %ecx
  55ec11:      	pushl	%esi
  55ec12:      	calll	0x57403d <.text+0x17303d>
  55ec17:      	movl	0xc701c0, %ecx
  55ec1d:      	pushl	%esi
  55ec1e:      	calll	0x56f435 <.text+0x16e435>
  55ec23:      	movl	0xc70168, %ecx
  55ec29:      	pushl	%esi
  55ec2a:      	calll	0x57403d <.text+0x17303d>
  55ec2f:      	movl	0xc701bc, %ecx
  55ec35:      	pushl	%esi
  55ec36:      	calll	0x56f435 <.text+0x16e435>
  55ec3b:      	movl	0xc70164, %ecx
  55ec41:      	pushl	%esi
  55ec42:      	calll	0x57403d <.text+0x17303d>
  55ec47:      	movl	0xc70180, %ecx
  55ec4d:      	pushl	%esi
  55ec4e:      	calll	0x56f435 <.text+0x16e435>
  55ec53:      	movl	0xc70150, %ecx
  55ec59:      	pushl	%esi
  55ec5a:      	calll	0x57403d <.text+0x17303d>
  55ec5f:      	movl	0xc7018c, %ecx
  55ec65:      	pushl	%esi
  55ec66:      	calll	0x573f6e <.text+0x172f6e>
  55ec6b:      	movl	0xc7015c, %ecx
  55ec71:      	pushl	%esi
  55ec72:      	calll	0x574011 <.text+0x173011>
  55ec77:      	movl	0xc70188, %ecx
  55ec7d:      	pushl	%esi
  55ec7e:      	calll	0x573f6e <.text+0x172f6e>
  55ec83:      	movl	0xc70158, %ecx
  55ec89:      	pushl	%esi
  55ec8a:      	calll	0x574011 <.text+0x173011>
  55ec8f:      	jmp	0x561361 <.text+0x160361>
  55ec94:      	movzwl	0x62aea4, %eax
  55ec9b:      	pushl	$0xc6fef8               # imm = 0xC6FEF8
  55eca0:      	pushl	$0xc6f870               # imm = 0xC6F870
  55eca5:      	pushl	%eax
  55eca6:      	pushl	0xba7724
  55ecac:      	pushl	$0x825                  # imm = 0x825
  55ecb1:      	pushl	%ebx
  55ecb2:      	calll	*0x5ce53c
  55ecb8:      	movl	$0xc6f4a0, %edx         # imm = 0xC6F4A0
  55ecbd:      	movl	%eax, %ecx
  55ecbf:      	calll	0x559a14 <.text+0x158a14>
  55ecc4:      	addl	$0x10, %esp
  55ecc7:      	jmp	0x560d63 <.text+0x15fd63>
  55eccc:      	pushl	%ebx
  55eccd:      	calll	0x572080 <.text+0x171080>
  55ecd2:      	orl	$-0x1, 0x62a990
  55ecd9:      	xorl	%edi, %edi
  55ecdb:      	pushl	$0x2
  55ecdd:      	movl	%edi, 0xc6fdc4
  55ece3:      	calll	0x571075 <.text+0x170075>
  55ece8:      	fldz
  55ecea:      	popl	%ecx
  55eceb:      	fstps	0xc6fdb4
  55ecf1:      	popl	%ecx
  55ecf2:      	movl	%edi, 0xc701e4
  55ecf8:      	movb	$0x1, 0x62a99e
  55ecff:      	movb	$0x1, 0x62a99f
  55ed06:      	movb	$0x1, 0x62aa04
  55ed0d:      	movl	$0x1, 0xc700c4
  55ed17:      	movb	$0x0, 0xc700c0
  55ed1e:      	movb	$0x0, 0xc6fca6
  55ed25:      	movb	$0x0, 0xc6f4b7
  55ed2c:      	movb	$0x0, 0xc6f4b6
  55ed33:      	movb	$0x0, 0xc6f4b5
  55ed3a:      	calll	0x570ef7 <.text+0x16fef7>
  55ed3f:      	movb	$0x0, 0xc6fd96
  55ed46:      	movb	$0x0, 0xc6fd95
  55ed4d:      	movb	$0x0, 0xc6fd94
  55ed54:      	movb	$0x0, 0xc6fca7
  55ed5b:      	movb	$0x0, 0xc6fd97
  55ed62:      	movb	$0x0, 0xc6fda8
  55ed69:      	cmpl	%edi, 0xa0f254
  55ed6f:      	je	0x55ed78 <.text+0x15dd78>
  55ed71:      	movb	$0x1, 0xc6fda8
  55ed78:      	pushl	%ebx
  55ed79:      	movl	%esi, 0xc700bc
  55ed7f:      	calll	0x56ea7b <.text+0x16da7b>
  55ed84:      	pushl	%ebx
  55ed85:      	calll	0x56eaea <.text+0x16daea>
  55ed8a:      	cmpb	$0x0, 0xc6f4b4
  55ed91:      	popl	%ecx
  55ed92:      	popl	%ecx
  55ed93:      	pushl	$0x20
  55ed95:      	je	0x55edb1 <.text+0x15ddb1>
  55ed97:      	calll	0x5c6d12 <.text+0x1c5d12>
  55ed9c:      	popl	%ecx
  55ed9d:      	cmpl	%edi, %eax
  55ed9f:      	je	0x55edc4 <.text+0x15ddc4>
  55eda1:      	pushl	%edi
  55eda2:      	pushl	%edi
  55eda3:      	pushl	$0x5f0860               # imm = 0x5F0860
  55eda8:      	movl	%eax, %ecx
  55edaa:      	calll	0x56f633 <.text+0x16e633>
  55edaf:      	jmp	0x55edc6 <.text+0x15ddc6>
  55edb1:      	calll	0x5c6d12 <.text+0x1c5d12>
  55edb6:      	popl	%ecx
  55edb7:      	cmpl	%edi, %eax
  55edb9:      	je	0x55edc4 <.text+0x15ddc4>
  55edbb:      	pushl	%edi
  55edbc:      	pushl	%edi
  55edbd:      	pushl	$0x5f084c               # imm = 0x5F084C
  55edc2:      	jmp	0x55eda8 <.text+0x15dda8>
  55edc4:      	xorl	%eax, %eax
  55edc6:      	pushl	%eax
  55edc7:      	pushl	%ebx
  55edc8:      	movl	%eax, 0xc701e8
  55edcd:      	calll	0x570cce <.text+0x16fcce>
  55edd2:      	movl	$0x110, %ebp            # imm = 0x110
  55edd7:      	pushl	%ebp
  55edd8:      	calll	0x5c6d12 <.text+0x1c5d12>
  55eddd:      	addl	$0xc, %esp
  55ede0:      	leal	-0x78(%ebp), %esi
  55ede3:      	cmpl	%edi, %eax
  55ede5:      	je	0x55ee18 <.text+0x15de18>
  55ede7:      	pushl	$0x5f0844               # imm = 0x5F0844
  55edec:      	pushl	$0x1
  55edee:      	pushl	$0x22
  55edf0:      	pushl	%esi
  55edf1:      	pushl	%edi
  55edf2:      	pushl	$0x1
  55edf4:      	pushl	$0x104                  # imm = 0x104
  55edf9:      	pushl	$0x102                  # imm = 0x102
  55edfe:      	pushl	$0x103                  # imm = 0x103
  55ee03:      	pushl	0xc6f4bc
  55ee09:      	movl	%eax, %ecx
  55ee0b:      	pushl	%ebx
  55ee0c:      	calll	0x5715a0 <.text+0x1705a0>
  55ee11:      	movl	%eax, 0xc701e0
  55ee16:      	jmp	0x55ee1e <.text+0x15de1e>
  55ee18:      	movl	%edi, 0xc701e0
  55ee1e:      	pushl	%ebp
  55ee1f:      	calll	0x5c6d12 <.text+0x1c5d12>
  55ee24:      	popl	%ecx
  55ee25:      	cmpl	%edi, %eax
  55ee27:      	je	0x55ee5d <.text+0x15de5d>
  55ee29:      	pushl	$0x5cf490               # imm = 0x5CF490
  55ee2e:      	pushl	$0x1
  55ee30:      	pushl	$0x22
  55ee32:      	pushl	%esi
  55ee33:      	pushl	%edi
  55ee34:      	pushl	$0x1e8                  # imm = 0x1E8
  55ee39:      	pushl	$0xcb
  55ee3e:      	pushl	$0xc9
  55ee43:      	pushl	$0xca
  55ee48:      	pushl	0xc6f4bc
  55ee4e:      	movl	%eax, %ecx
  55ee50:      	pushl	%ebx
  55ee51:      	calll	0x5715a0 <.text+0x1705a0>
  55ee56:      	movl	%eax, 0xc701dc
  55ee5b:      	jmp	0x55ee63 <.text+0x15de63>
  55ee5d:      	movl	%edi, 0xc701dc
  55ee63:      	pushl	%ebp
  55ee64:      	calll	0x5c6d12 <.text+0x1c5d12>
  55ee69:      	popl	%ecx
  55ee6a:      	movl	$0xc7, %edx
  55ee6f:      	cmpl	%edi, %eax
  55ee71:      	je	0x55eea4 <.text+0x15dea4>
  55ee73:      	pushl	$0x5f083c               # imm = 0x5F083C
  55ee78:      	pushl	$0x1
  55ee7a:      	pushl	$0x22
  55ee7c:      	pushl	%edx
  55ee7d:      	pushl	$0x1bd                  # imm = 0x1BD
  55ee82:      	pushl	$0x1
  55ee84:      	pushl	$0xc8
  55ee89:      	pushl	$0xc6
  55ee8e:      	pushl	%edx
  55ee8f:      	pushl	0xc6f4bc
  55ee95:      	movl	%eax, %ecx
  55ee97:      	pushl	%ebx
  55ee98:      	calll	0x5715a0 <.text+0x1705a0>
  55ee9d:      	movl	%eax, 0xc701d8
  55eea2:      	jmp	0x55eeaa <.text+0x15deaa>
  55eea4:      	movl	%edi, 0xc701d8
  55eeaa:      	movl	0xc701e0, %ecx
  55eeb0:      	pushl	$0x17
  55eeb2:      	pushl	$0x58
  55eeb4:      	pushl	$0x4
  55eeb6:      	pushl	$0x2f
  55eeb8:      	calll	0x5724d7 <.text+0x1714d7>
  55eebd:      	movl	0xc701dc, %ecx
  55eec3:      	pushl	$0x17
  55eec5:      	pushl	$0x58
  55eec7:      	pushl	$0x4
  55eec9:      	pushl	$0x1fb                  # imm = 0x1FB
  55eece:      	calll	0x5724d7 <.text+0x1714d7>
  55eed3:      	movl	0xc701d8, %ecx
  55eed9:      	pushl	$0x17
  55eedb:      	pushl	$0x58
  55eedd:      	pushl	$0x1c6                  # imm = 0x1C6
  55eee2:      	pushl	$0x2f
  55eee4:      	calll	0x5724d7 <.text+0x1714d7>
  55eee9:      	pushl	%ebp
  55eeea:      	calll	0x5c6d12 <.text+0x1c5d12>
  55eeef:      	popl	%ecx
  55eef0:      	movl	$0x81a, %esi            # imm = 0x81A
  55eef5:      	cmpl	%edi, %eax
  55eef7:      	je	0x55ef22 <.text+0x15df22>
  55eef9:      	pushl	$0x5f0838               # imm = 0x5F0838
  55eefe:      	pushl	$0x1
  55ef00:      	pushl	$0x12
  55ef02:      	pushl	$0x13
  55ef04:      	pushl	$0x1a7                  # imm = 0x1A7
  55ef09:      	pushl	$0x1f
  55ef0b:      	pushl	$0x7fa                  # imm = 0x7FA
  55ef10:      	pushl	%esi
  55ef11:      	pushl	%edi
  55ef12:      	pushl	0xc6f4bc
  55ef18:      	movl	%eax, %ecx
  55ef1a:      	pushl	%ebx
  55ef1b:      	calll	0x5715a0 <.text+0x1705a0>
  55ef20:      	jmp	0x55ef24 <.text+0x15df24>
  55ef22:      	xorl	%eax, %eax
  55ef24:      	pushl	$0x5f0828               # imm = 0x5F0828
  55ef29:      	pushl	$0x5f081c               # imm = 0x5F081C
  55ef2e:      	movl	%eax, %ecx
  55ef30:      	movl	%eax, 0xc701d4
  55ef35:      	calll	0x56f4cb <.text+0x16e4cb>
  55ef3a:      	pushl	%ebp
  55ef3b:      	calll	0x5c6d12 <.text+0x1c5d12>
  55ef40:      	popl	%ecx
  55ef41:      	cmpl	%edi, %eax
  55ef43:      	je	0x55ef6e <.text+0x15df6e>
  55ef45:      	pushl	$0x5f0818               # imm = 0x5F0818
  55ef4a:      	pushl	$0x1
  55ef4c:      	pushl	$0x12
  55ef4e:      	pushl	$0x13
  55ef50:      	pushl	$0x1a7                  # imm = 0x1A7
  55ef55:      	pushl	$0x47
  55ef57:      	pushl	$0x7fa                  # imm = 0x7FA
  55ef5c:      	pushl	%esi
  55ef5d:      	pushl	%edi
  55ef5e:      	pushl	0xc6f4bc
  55ef64:      	movl	%eax, %ecx
  55ef66:      	pushl	%ebx
  55ef67:      	calll	0x5715a0 <.text+0x1705a0>
  55ef6c:      	jmp	0x55ef70 <.text+0x15df70>
  55ef6e:      	xorl	%eax, %eax
  55ef70:      	pushl	$0x5f0828               # imm = 0x5F0828
  55ef75:      	pushl	$0x5f081c               # imm = 0x5F081C
  55ef7a:      	movl	%eax, %ecx
  55ef7c:      	movl	%eax, 0xc701d0
  55ef81:      	calll	0x56f4cb <.text+0x16e4cb>
  55ef86:      	pushl	%ebp
  55ef87:      	calll	0x5c6d12 <.text+0x1c5d12>
  55ef8c:      	popl	%ecx
  55ef8d:      	cmpl	%edi, %eax
  55ef8f:      	je	0x55efba <.text+0x15dfba>
  55ef91:      	pushl	$0x5e83d8               # imm = 0x5E83D8
  55ef96:      	pushl	$0x1
  55ef98:      	pushl	$0x12
  55ef9a:      	pushl	$0x13
  55ef9c:      	pushl	$0x1a7                  # imm = 0x1A7
  55efa1:      	pushl	$0x33
  55efa3:      	pushl	$0x7fa                  # imm = 0x7FA
  55efa8:      	pushl	%esi
  55efa9:      	pushl	%edi
  55efaa:      	pushl	0xc6f4bc
  55efb0:      	movl	%eax, %ecx
  55efb2:      	pushl	%ebx
  55efb3:      	calll	0x5715a0 <.text+0x1705a0>
  55efb8:      	jmp	0x55efbc <.text+0x15dfbc>
  55efba:      	xorl	%eax, %eax
  55efbc:      	pushl	$0x5f0828               # imm = 0x5F0828
  55efc1:      	pushl	$0x5f081c               # imm = 0x5F081C
  55efc6:      	movl	%eax, %ecx
  55efc8:      	movl	%eax, 0xc701cc
  55efcd:      	calll	0x56f4cb <.text+0x16e4cb>
  55efd2:      	pushl	%ebp
  55efd3:      	calll	0x5c6d12 <.text+0x1c5d12>
  55efd8:      	popl	%ecx
  55efd9:      	movl	$0xb3, %esi
  55efde:      	cmpl	%edi, %eax
  55efe0:      	je	0x55f00b <.text+0x15e00b>
  55efe2:      	pushl	%edi
  55efe3:      	pushl	%edi
  55efe4:      	pushl	$0x12
  55efe6:      	pushl	$0x13
  55efe8:      	pushl	$0x77
  55efea:      	pushl	%esi
  55efeb:      	pushl	$0x7ff                  # imm = 0x7FF
  55eff0:      	pushl	$0x819                  # imm = 0x819
  55eff5:      	pushl	%edi
  55eff6:      	pushl	0xc6f4bc
  55effc:      	movl	%eax, %ecx
  55effe:      	pushl	%ebx
  55efff:      	calll	0x5715a0 <.text+0x1705a0>
  55f004:      	movl	%eax, 0xc701b8
  55f009:      	jmp	0x55f011 <.text+0x15e011>
  55f00b:      	movl	%edi, 0xc701b8
  55f011:      	pushl	%ebp
  55f012:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f017:      	popl	%ecx
  55f018:      	cmpl	%edi, %eax
  55f01a:      	je	0x55f048 <.text+0x15e048>
  55f01c:      	pushl	%edi
  55f01d:      	pushl	%edi
  55f01e:      	pushl	$0x12
  55f020:      	pushl	$0x13
  55f022:      	pushl	$0x89
  55f027:      	pushl	%esi
  55f028:      	pushl	$0x800                  # imm = 0x800
  55f02d:      	pushl	$0x818                  # imm = 0x818
  55f032:      	pushl	%edi
  55f033:      	pushl	0xc6f4bc
  55f039:      	movl	%eax, %ecx
  55f03b:      	pushl	%ebx
  55f03c:      	calll	0x5715a0 <.text+0x1705a0>
  55f041:      	movl	%eax, 0xc701b4
  55f046:      	jmp	0x55f04e <.text+0x15e04e>
  55f048:      	movl	%edi, 0xc701b4
  55f04e:      	pushl	%ebp
  55f04f:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f054:      	popl	%ecx
  55f055:      	movl	$0xba, %esi
  55f05a:      	cmpl	%edi, %eax
  55f05c:      	je	0x55f08a <.text+0x15e08a>
  55f05e:      	pushl	%edi
  55f05f:      	pushl	%edi
  55f060:      	pushl	$0x13
  55f062:      	pushl	$0x12
  55f064:      	pushl	%esi
  55f065:      	pushl	$0x1c5                  # imm = 0x1C5
  55f06a:      	pushl	$0x801                  # imm = 0x801
  55f06f:      	pushl	$0x817                  # imm = 0x817
  55f074:      	pushl	%edi
  55f075:      	pushl	0xc6f4bc
  55f07b:      	movl	%eax, %ecx
  55f07d:      	pushl	%ebx
  55f07e:      	calll	0x5715a0 <.text+0x1705a0>
  55f083:      	movl	%eax, 0xc701b0
  55f088:      	jmp	0x55f090 <.text+0x15e090>
  55f08a:      	movl	%edi, 0xc701b0
  55f090:      	pushl	%ebp
  55f091:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f096:      	popl	%ecx
  55f097:      	cmpl	%edi, %eax
  55f099:      	je	0x55f0c7 <.text+0x15e0c7>
  55f09b:      	pushl	%edi
  55f09c:      	pushl	%edi
  55f09d:      	pushl	$0x13
  55f09f:      	pushl	$0x12
  55f0a1:      	pushl	%esi
  55f0a2:      	pushl	$0x1d7                  # imm = 0x1D7
  55f0a7:      	pushl	$0x802                  # imm = 0x802
  55f0ac:      	pushl	$0x816                  # imm = 0x816
  55f0b1:      	pushl	%edi
  55f0b2:      	pushl	0xc6f4bc
  55f0b8:      	movl	%eax, %ecx
  55f0ba:      	pushl	%ebx
  55f0bb:      	calll	0x5715a0 <.text+0x1705a0>
  55f0c0:      	movl	%eax, 0xc701ac
  55f0c5:      	jmp	0x55f0cd <.text+0x15e0cd>
  55f0c7:      	movl	%edi, 0xc701ac
  55f0cd:      	pushl	%ebp
  55f0ce:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f0d3:      	popl	%ecx
  55f0d4:      	movl	$0x249, %esi            # imm = 0x249
  55f0d9:      	cmpl	%edi, %eax
  55f0db:      	je	0x55f109 <.text+0x15e109>
  55f0dd:      	pushl	%edi
  55f0de:      	pushl	%edi
  55f0df:      	pushl	$0x12
  55f0e1:      	pushl	$0x13
  55f0e3:      	pushl	$0x176                  # imm = 0x176
  55f0e8:      	pushl	%esi
  55f0e9:      	pushl	$0x7ff                  # imm = 0x7FF
  55f0ee:      	pushl	$0x819                  # imm = 0x819
  55f0f3:      	pushl	%edi
  55f0f4:      	pushl	0xc6f4bc
  55f0fa:      	movl	%eax, %ecx
  55f0fc:      	pushl	%ebx
  55f0fd:      	calll	0x5715a0 <.text+0x1705a0>
  55f102:      	movl	%eax, 0xc701a8
  55f107:      	jmp	0x55f10f <.text+0x15e10f>
  55f109:      	movl	%edi, 0xc701a8
  55f10f:      	pushl	%ebp
  55f110:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f115:      	popl	%ecx
  55f116:      	cmpl	%edi, %eax
  55f118:      	je	0x55f146 <.text+0x15e146>
  55f11a:      	pushl	%edi
  55f11b:      	pushl	%edi
  55f11c:      	pushl	$0x12
  55f11e:      	pushl	$0x13
  55f120:      	pushl	$0x188                  # imm = 0x188
  55f125:      	pushl	%esi
  55f126:      	pushl	$0x800                  # imm = 0x800
  55f12b:      	pushl	$0x818                  # imm = 0x818
  55f130:      	pushl	%edi
  55f131:      	pushl	0xc6f4bc
  55f137:      	movl	%eax, %ecx
  55f139:      	pushl	%ebx
  55f13a:      	calll	0x5715a0 <.text+0x1705a0>
  55f13f:      	movl	%eax, 0xc701a4
  55f144:      	jmp	0x55f14c <.text+0x15e14c>
  55f146:      	movl	%edi, 0xc701a4
  55f14c:      	pushl	%ebp
  55f14d:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f152:      	popl	%ecx
  55f153:      	movl	$0x12f, %esi            # imm = 0x12F
  55f158:      	cmpl	%edi, %eax
  55f15a:      	je	0x55f188 <.text+0x15e188>
  55f15c:      	pushl	%edi
  55f15d:      	pushl	%edi
  55f15e:      	pushl	$0x12
  55f160:      	pushl	$0x13
  55f162:      	pushl	$0x196                  # imm = 0x196
  55f167:      	pushl	%esi
  55f168:      	pushl	$0x7ff                  # imm = 0x7FF
  55f16d:      	pushl	$0x819                  # imm = 0x819
  55f172:      	pushl	%edi
  55f173:      	pushl	0xc6f4bc
  55f179:      	movl	%eax, %ecx
  55f17b:      	pushl	%ebx
  55f17c:      	calll	0x5715a0 <.text+0x1705a0>
  55f181:      	movl	%eax, 0xc701a0
  55f186:      	jmp	0x55f18e <.text+0x15e18e>
  55f188:      	movl	%edi, 0xc701a0
  55f18e:      	pushl	%ebp
  55f18f:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f194:      	popl	%ecx
  55f195:      	cmpl	%edi, %eax
  55f197:      	je	0x55f1c5 <.text+0x15e1c5>
  55f199:      	pushl	%edi
  55f19a:      	pushl	%edi
  55f19b:      	pushl	$0x12
  55f19d:      	pushl	$0x13
  55f19f:      	pushl	$0x1a8                  # imm = 0x1A8
  55f1a4:      	pushl	%esi
  55f1a5:      	pushl	$0x800                  # imm = 0x800
  55f1aa:      	pushl	$0x818                  # imm = 0x818
  55f1af:      	pushl	%edi
  55f1b0:      	pushl	0xc6f4bc
  55f1b6:      	movl	%eax, %ecx
  55f1b8:      	pushl	%ebx
  55f1b9:      	calll	0x5715a0 <.text+0x1705a0>
  55f1be:      	movl	%eax, 0xc7019c
  55f1c3:      	jmp	0x55f1cb <.text+0x15e1cb>
  55f1c5:      	movl	%edi, 0xc7019c
  55f1cb:      	pushl	%ebp
  55f1cc:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f1d1:      	popl	%ecx
  55f1d2:      	movl	$0x7fe, %esi            # imm = 0x7FE
  55f1d7:      	cmpl	%edi, %eax
  55f1d9:      	je	0x55f200 <.text+0x15e200>
  55f1db:      	pushl	$0x5f080c               # imm = 0x5F080C
  55f1e0:      	pushl	$0x1
  55f1e2:      	pushl	$0x15
  55f1e4:      	pushl	$0x71
  55f1e6:      	pushl	$0xeb
  55f1eb:      	pushl	$0x1e
  55f1ed:      	pushl	%esi
  55f1ee:      	pushl	%esi
  55f1ef:      	pushl	%edi
  55f1f0:      	pushl	0xc6f4bc
  55f1f6:      	movl	%eax, %ecx
  55f1f8:      	pushl	%ebx
  55f1f9:      	calll	0x5715a0 <.text+0x1705a0>
  55f1fe:      	jmp	0x55f202 <.text+0x15e202>
  55f200:      	xorl	%eax, %eax
  55f202:      	pushl	$0x5f0828               # imm = 0x5F0828
  55f207:      	pushl	$0x5f081c               # imm = 0x5F081C
  55f20c:      	movl	%eax, %ecx
  55f20e:      	movl	%eax, 0xc701c4
  55f213:      	calll	0x56f4cb <.text+0x16e4cb>
  55f218:      	pushl	%ebp
  55f219:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f21e:      	popl	%ecx
  55f21f:      	cmpl	%edi, %eax
  55f221:      	je	0x55f248 <.text+0x15e248>
  55f223:      	pushl	$0x5e5508               # imm = 0x5E5508
  55f228:      	pushl	$0x1
  55f22a:      	pushl	$0x15
  55f22c:      	pushl	$0x71
  55f22e:      	pushl	$0x100                  # imm = 0x100
  55f233:      	pushl	$0x1e
  55f235:      	pushl	%esi
  55f236:      	pushl	%esi
  55f237:      	pushl	%edi
  55f238:      	pushl	0xc6f4bc
  55f23e:      	movl	%eax, %ecx
  55f240:      	pushl	%ebx
  55f241:      	calll	0x5715a0 <.text+0x1705a0>
  55f246:      	jmp	0x55f24a <.text+0x15e24a>
  55f248:      	xorl	%eax, %eax
  55f24a:      	pushl	$0x5f0828               # imm = 0x5F0828
  55f24f:      	pushl	$0x5f081c               # imm = 0x5F081C
  55f254:      	movl	%eax, %ecx
  55f256:      	movl	%eax, 0xc70178
  55f25b:      	calll	0x56f4cb <.text+0x16e4cb>
  55f260:      	movl	0xc70178, %ecx
  55f266:      	calll	0x56f4c1 <.text+0x16e4c1>
  55f26b:      	pushl	%ebp
  55f26c:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f271:      	popl	%ecx
  55f272:      	movl	$0x7fd, %esi            # imm = 0x7FD
  55f277:      	cmpl	%edi, %eax
  55f279:      	je	0x55f2a3 <.text+0x15e2a3>
  55f27b:      	pushl	$0x5f0800               # imm = 0x5F0800
  55f280:      	pushl	$0x1
  55f282:      	pushl	$0x15
  55f284:      	pushl	$0x5b
  55f286:      	pushl	$0xeb
  55f28b:      	pushl	$0xc6
  55f290:      	pushl	%esi
  55f291:      	pushl	%esi
  55f292:      	pushl	%edi
  55f293:      	pushl	0xc6f4bc
  55f299:      	movl	%eax, %ecx
  55f29b:      	pushl	%ebx
  55f29c:      	calll	0x5715a0 <.text+0x1705a0>
  55f2a1:      	jmp	0x55f2a5 <.text+0x15e2a5>
  55f2a3:      	xorl	%eax, %eax
  55f2a5:      	pushl	$0x5f0828               # imm = 0x5F0828
  55f2aa:      	pushl	$0x5f081c               # imm = 0x5F081C
  55f2af:      	movl	%eax, %ecx
  55f2b1:      	movl	%eax, 0xc701c8
  55f2b6:      	calll	0x56f4cb <.text+0x16e4cb>
  55f2bb:      	pushl	%ebp
  55f2bc:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f2c1:      	popl	%ecx
  55f2c2:      	cmpl	%edi, %eax
  55f2c4:      	je	0x55f2ee <.text+0x15e2ee>
  55f2c6:      	pushl	$0x5f07f4               # imm = 0x5F07F4
  55f2cb:      	pushl	$0x1
  55f2cd:      	pushl	$0x15
  55f2cf:      	pushl	$0x5b
  55f2d1:      	pushl	$0x100                  # imm = 0x100
  55f2d6:      	pushl	$0xc6
  55f2db:      	pushl	%esi
  55f2dc:      	pushl	%esi
  55f2dd:      	pushl	%edi
  55f2de:      	pushl	0xc6f4bc
  55f2e4:      	movl	%eax, %ecx
  55f2e6:      	pushl	%ebx
  55f2e7:      	calll	0x5715a0 <.text+0x1705a0>
  55f2ec:      	jmp	0x55f2f0 <.text+0x15e2f0>
  55f2ee:      	xorl	%eax, %eax
  55f2f0:      	pushl	$0x5f0828               # imm = 0x5F0828
  55f2f5:      	pushl	$0x5f081c               # imm = 0x5F081C
  55f2fa:      	movl	%eax, %ecx
  55f2fc:      	movl	%eax, 0xc701c0
  55f301:      	calll	0x56f4cb <.text+0x16e4cb>
  55f306:      	pushl	%ebp
  55f307:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f30c:      	popl	%ecx
  55f30d:      	cmpl	%edi, %eax
  55f30f:      	je	0x55f339 <.text+0x15e339>
  55f311:      	pushl	$0x5f07e8               # imm = 0x5F07E8
  55f316:      	pushl	$0x1
  55f318:      	pushl	$0x15
  55f31a:      	pushl	$0x5b
  55f31c:      	pushl	$0xeb
  55f321:      	pushl	$0x1e1                  # imm = 0x1E1
  55f326:      	pushl	%esi
  55f327:      	pushl	%esi
  55f328:      	pushl	%edi
  55f329:      	pushl	0xc6f4bc
  55f32f:      	movl	%eax, %ecx
  55f331:      	pushl	%ebx
  55f332:      	calll	0x5715a0 <.text+0x1705a0>
  55f337:      	jmp	0x55f33b <.text+0x15e33b>
  55f339:      	xorl	%eax, %eax
  55f33b:      	pushl	$0x5f0828               # imm = 0x5F0828
  55f340:      	pushl	$0x5f081c               # imm = 0x5F081C
  55f345:      	movl	%eax, %ecx
  55f347:      	movl	%eax, 0xc701bc
  55f34c:      	calll	0x56f4cb <.text+0x16e4cb>
  55f351:      	pushl	%ebp
  55f352:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f357:      	popl	%ecx
  55f358:      	cmpl	%edi, %eax
  55f35a:      	je	0x55f384 <.text+0x15e384>
  55f35c:      	pushl	$0x5f07dc               # imm = 0x5F07DC
  55f361:      	pushl	$0x1
  55f363:      	pushl	$0x15
  55f365:      	pushl	$0x5b
  55f367:      	pushl	$0xd6
  55f36c:      	pushl	$0x155                  # imm = 0x155
  55f371:      	pushl	%esi
  55f372:      	pushl	%esi
  55f373:      	pushl	%edi
  55f374:      	pushl	0xc6f4bc
  55f37a:      	movl	%eax, %ecx
  55f37c:      	pushl	%ebx
  55f37d:      	calll	0x5715a0 <.text+0x1705a0>
  55f382:      	jmp	0x55f386 <.text+0x15e386>
  55f384:      	xorl	%eax, %eax
  55f386:      	pushl	$0x5f0828               # imm = 0x5F0828
  55f38b:      	pushl	$0x5f081c               # imm = 0x5F081C
  55f390:      	movl	%eax, %ecx
  55f392:      	movl	%eax, 0xc7018c
  55f397:      	calll	0x56f4cb <.text+0x16e4cb>
  55f39c:      	pushl	%ebp
  55f39d:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f3a2:      	popl	%ecx
  55f3a3:      	cmpl	%edi, %eax
  55f3a5:      	je	0x55f3cf <.text+0x15e3cf>
  55f3a7:      	pushl	$0x5f07cc               # imm = 0x5F07CC
  55f3ac:      	pushl	$0x1
  55f3ae:      	pushl	$0x15
  55f3b0:      	pushl	$0x5b
  55f3b2:      	pushl	$0xeb
  55f3b7:      	pushl	$0x155                  # imm = 0x155
  55f3bc:      	pushl	%esi
  55f3bd:      	pushl	%esi
  55f3be:      	pushl	%edi
  55f3bf:      	pushl	0xc6f4bc
  55f3c5:      	movl	%eax, %ecx
  55f3c7:      	pushl	%ebx
  55f3c8:      	calll	0x5715a0 <.text+0x1705a0>
  55f3cd:      	jmp	0x55f3d1 <.text+0x15e3d1>
  55f3cf:      	xorl	%eax, %eax
  55f3d1:      	pushl	$0x5f0828               # imm = 0x5F0828
  55f3d6:      	pushl	$0x5f081c               # imm = 0x5F081C
  55f3db:      	movl	%eax, %ecx
  55f3dd:      	movl	%eax, 0xc70190
  55f3e2:      	calll	0x56f4cb <.text+0x16e4cb>
  55f3e7:      	pushl	%ebp
  55f3e8:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f3ed:      	popl	%ecx
  55f3ee:      	cmpl	%edi, %eax
  55f3f0:      	je	0x55f41a <.text+0x15e41a>
  55f3f2:      	pushl	$0x5f07c0               # imm = 0x5F07C0
  55f3f7:      	pushl	$0x1
  55f3f9:      	pushl	$0x15
  55f3fb:      	pushl	$0x5b
  55f3fd:      	pushl	$0x100                  # imm = 0x100
  55f402:      	pushl	$0x155                  # imm = 0x155
  55f407:      	pushl	%esi
  55f408:      	pushl	%esi
  55f409:      	pushl	%edi
  55f40a:      	pushl	0xc6f4bc
  55f410:      	movl	%eax, %ecx
  55f412:      	pushl	%ebx
  55f413:      	calll	0x5715a0 <.text+0x1705a0>
  55f418:      	jmp	0x55f41c <.text+0x15e41c>
  55f41a:      	xorl	%eax, %eax
  55f41c:      	pushl	$0x5f0828               # imm = 0x5F0828
  55f421:      	pushl	$0x5f081c               # imm = 0x5F081C
  55f426:      	movl	%eax, %ecx
  55f428:      	movl	%eax, 0xc70174
  55f42d:      	calll	0x56f4cb <.text+0x16e4cb>
  55f432:      	pushl	%ebp
  55f433:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f438:      	popl	%ecx
  55f439:      	cmpl	%edi, %eax
  55f43b:      	je	0x55f465 <.text+0x15e465>
  55f43d:      	pushl	$0x5f07b4               # imm = 0x5F07B4
  55f442:      	pushl	$0x1
  55f444:      	pushl	$0x15
  55f446:      	pushl	$0x5b
  55f448:      	pushl	$0xeb
  55f44d:      	pushl	$0x1e1                  # imm = 0x1E1
  55f452:      	pushl	%esi
  55f453:      	pushl	%esi
  55f454:      	pushl	%edi
  55f455:      	pushl	0xc6f4bc
  55f45b:      	movl	%eax, %ecx
  55f45d:      	pushl	%ebx
  55f45e:      	calll	0x5715a0 <.text+0x1705a0>
  55f463:      	jmp	0x55f467 <.text+0x15e467>
  55f465:      	xorl	%eax, %eax
  55f467:      	pushl	$0x5f0828               # imm = 0x5F0828
  55f46c:      	pushl	$0x5f081c               # imm = 0x5F081C
  55f471:      	movl	%eax, %ecx
  55f473:      	movl	%eax, 0xc70188
  55f478:      	calll	0x56f4cb <.text+0x16e4cb>
  55f47d:      	pushl	%ebp
  55f47e:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f483:      	popl	%ecx
  55f484:      	cmpl	%edi, %eax
  55f486:      	je	0x55f4b0 <.text+0x15e4b0>
  55f488:      	pushl	$0x5f07a8               # imm = 0x5F07A8
  55f48d:      	pushl	$0x1
  55f48f:      	pushl	$0x15
  55f491:      	pushl	$0x5b
  55f493:      	pushl	$0x100                  # imm = 0x100
  55f498:      	pushl	$0x1e1                  # imm = 0x1E1
  55f49d:      	pushl	%esi
  55f49e:      	pushl	%esi
  55f49f:      	pushl	%edi
  55f4a0:      	pushl	0xc6f4bc
  55f4a6:      	movl	%eax, %ecx
  55f4a8:      	pushl	%ebx
  55f4a9:      	calll	0x5715a0 <.text+0x1705a0>
  55f4ae:      	jmp	0x55f4b2 <.text+0x15e4b2>
  55f4b0:      	xorl	%eax, %eax
  55f4b2:      	pushl	$0x5f0828               # imm = 0x5F0828
  55f4b7:      	pushl	$0x5f081c               # imm = 0x5F081C
  55f4bc:      	movl	%eax, %ecx
  55f4be:      	movl	%eax, 0xc70184
  55f4c3:      	calll	0x56f4cb <.text+0x16e4cb>
  55f4c8:      	movl	0xc70184, %ecx
  55f4ce:      	pushl	%edi
  55f4cf:      	calll	0x56f435 <.text+0x16e435>
  55f4d4:      	movl	0xc70184, %ecx
  55f4da:      	calll	0x56f4c1 <.text+0x16e4c1>
  55f4df:      	pushl	%ebp
  55f4e0:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f4e5:      	popl	%ecx
  55f4e6:      	cmpl	%edi, %eax
  55f4e8:      	je	0x55f512 <.text+0x15e512>
  55f4ea:      	pushl	$0x5f0798               # imm = 0x5F0798
  55f4ef:      	pushl	$0x1
  55f4f1:      	pushl	$0x15
  55f4f3:      	pushl	$0x5b
  55f4f5:      	pushl	$0xd6
  55f4fa:      	pushl	$0x155                  # imm = 0x155
  55f4ff:      	pushl	%esi
  55f500:      	pushl	%esi
  55f501:      	pushl	%edi
  55f502:      	pushl	0xc6f4bc
  55f508:      	movl	%eax, %ecx
  55f50a:      	pushl	%ebx
  55f50b:      	calll	0x5715a0 <.text+0x1705a0>
  55f510:      	jmp	0x55f514 <.text+0x15e514>
  55f512:      	xorl	%eax, %eax
  55f514:      	pushl	$0x5f0828               # imm = 0x5F0828
  55f519:      	pushl	$0x5f081c               # imm = 0x5F081C
  55f51e:      	movl	%eax, %ecx
  55f520:      	movl	%eax, 0xc70180
  55f525:      	calll	0x56f4cb <.text+0x16e4cb>
  55f52a:      	pushl	%ebp
  55f52b:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f530:      	popl	%ecx
  55f531:      	cmpl	%edi, %eax
  55f533:      	je	0x55f55d <.text+0x15e55d>
  55f535:      	pushl	$0x5f0790               # imm = 0x5F0790
  55f53a:      	pushl	$0x1
  55f53c:      	pushl	$0x15
  55f53e:      	pushl	$0x5b
  55f540:      	pushl	$0xd6
  55f545:      	pushl	$0x1e1                  # imm = 0x1E1
  55f54a:      	pushl	%esi
  55f54b:      	pushl	%esi
  55f54c:      	pushl	%edi
  55f54d:      	pushl	0xc6f4bc
  55f553:      	movl	%eax, %ecx
  55f555:      	pushl	%ebx
  55f556:      	calll	0x5715a0 <.text+0x1705a0>
  55f55b:      	jmp	0x55f55f <.text+0x15e55f>
  55f55d:      	xorl	%eax, %eax
  55f55f:      	pushl	$0x5f0828               # imm = 0x5F0828
  55f564:      	pushl	$0x5f081c               # imm = 0x5F081C
  55f569:      	movl	%eax, %ecx
  55f56b:      	movl	%eax, 0xc7017c
  55f570:      	calll	0x56f4cb <.text+0x16e4cb>
  55f575:      	pushl	%ebp
  55f576:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f57b:      	popl	%ecx
  55f57c:      	cmpl	%edi, %eax
  55f57e:      	je	0x55f5a7 <.text+0x15e5a7>
  55f580:      	pushl	$0x5df2cc               # imm = 0x5DF2CC
  55f585:      	pushl	$0x1
  55f587:      	pushl	$0xf
  55f589:      	pushl	$0x60
  55f58b:      	pushl	$0x2b
  55f58d:      	pushl	$0x64
  55f58f:      	movl	$0x81e, %edx            # imm = 0x81E
  55f594:      	pushl	%edx
  55f595:      	pushl	%edx
  55f596:      	pushl	%edi
  55f597:      	pushl	0xc6f4bc
  55f59d:      	movl	%eax, %ecx
  55f59f:      	pushl	%ebx
  55f5a0:      	calll	0x5715a0 <.text+0x1705a0>
  55f5a5:      	jmp	0x55f5a9 <.text+0x15e5a9>
  55f5a7:      	xorl	%eax, %eax
  55f5a9:      	movl	0xc6fdac, %ecx
  55f5af:      	imull	$0xc, %ecx, %ecx
  55f5b2:      	pushl	0x633a90(%ecx)
  55f5b8:      	movl	%eax, %ecx
  55f5ba:      	movl	%eax, 0xc70170
  55f5bf:      	calll	0x56f585 <.text+0x16e585>
  55f5c4:      	movl	0xc70170, %eax
  55f5c9:      	addl	$0x20, %eax
  55f5cc:      	pushl	%eax
  55f5cd:      	movl	0xc6fdac, %eax
  55f5d2:      	imull	$0xc, %eax, %eax
  55f5d5:      	pushl	0x633a94(%eax)
  55f5db:      	movl	$0x5ef488, %esi         # imm = 0x5EF488
  55f5e0:      	pushl	%esi
  55f5e1:      	calll	0x4ba7c3 <.text+0xb97c3>
  55f5e6:      	movl	0xc70170, %ecx
  55f5ec:      	addl	$0xc, %esp
  55f5ef:      	pushl	$0x5f0828               # imm = 0x5F0828
  55f5f4:      	pushl	$0x5f081c               # imm = 0x5F081C
  55f5f9:      	calll	0x56f4cb <.text+0x16e4cb>
  55f5fe:      	pushl	%ebp
  55f5ff:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f604:      	popl	%ecx
  55f605:      	movl	$0x828, %edx            # imm = 0x828
  55f60a:      	cmpl	%edi, %eax
  55f60c:      	je	0x55f636 <.text+0x15e636>
  55f60e:      	pushl	$0x5f0780               # imm = 0x5F0780
  55f613:      	pushl	$0x1
  55f615:      	pushl	$0x19
  55f617:      	pushl	$0xe8
  55f61c:      	pushl	$0x4
  55f61e:      	pushl	$0x9f
  55f623:      	pushl	%edx
  55f624:      	pushl	%edx
  55f625:      	pushl	%edx
  55f626:      	pushl	0xc6f4bc
  55f62c:      	movl	%eax, %ecx
  55f62e:      	pushl	%ebx
  55f62f:      	calll	0x5715a0 <.text+0x1705a0>
  55f634:      	jmp	0x55f638 <.text+0x15e638>
  55f636:      	xorl	%eax, %eax
  55f638:      	pushl	%edi
  55f639:      	movl	%eax, %ecx
  55f63b:      	movl	%eax, 0xc70198
  55f640:      	calll	0x56f435 <.text+0x16e435>
  55f645:      	movl	0xc70198, %ecx
  55f64b:      	pushl	%edi
  55f64c:      	pushl	$0xff
  55f651:      	calll	0x573f55 <.text+0x172f55>
  55f656:      	pushl	%ebp
  55f657:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f65c:      	popl	%ecx
  55f65d:      	movl	$0x82b, %edx            # imm = 0x82B
  55f662:      	cmpl	%edi, %eax
  55f664:      	je	0x55f68f <.text+0x15e68f>
  55f666:      	pushl	$0x5e4474               # imm = 0x5E4474
  55f66b:      	pushl	$0x1
  55f66d:      	pushl	$0x19
  55f66f:      	pushl	$0x5c
  55f671:      	pushl	$0x4
  55f673:      	pushl	$0x187                  # imm = 0x187
  55f678:      	pushl	%edx
  55f679:      	pushl	%edx
  55f67a:      	pushl	$0x82a                  # imm = 0x82A
  55f67f:      	pushl	0xc6f4bc
  55f685:      	movl	%eax, %ecx
  55f687:      	pushl	%ebx
  55f688:      	calll	0x5715a0 <.text+0x1705a0>
  55f68d:      	jmp	0x55f691 <.text+0x15e691>
  55f68f:      	xorl	%eax, %eax
  55f691:      	pushl	$0x5f0828               # imm = 0x5F0828
  55f696:      	pushl	$0x5f081c               # imm = 0x5F081C
  55f69b:      	movl	%eax, %ecx
  55f69d:      	movl	%eax, 0xc70194
  55f6a2:      	calll	0x56f4cb <.text+0x16e4cb>
  55f6a7:      	movl	0xc70194, %ecx
  55f6ad:      	pushl	%edi
  55f6ae:      	calll	0x56f435 <.text+0x16e435>
  55f6b3:      	movl	0xc70194, %ecx
  55f6b9:      	pushl	%edi
  55f6ba:      	pushl	$0xff
  55f6bf:      	calll	0x573f55 <.text+0x172f55>
  55f6c4:      	movl	$0x32ec, %ebp           # imm = 0x32EC
  55f6c9:      	pushl	%ebp
  55f6ca:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f6cf:      	popl	%ecx
  55f6d0:      	cmpl	%edi, %eax
  55f6d2:      	je	0x55f6ee <.text+0x15e6ee>
  55f6d4:      	pushl	$0xf
  55f6d6:      	pushl	$0x1c
  55f6d8:      	pushl	$0xee
  55f6dd:      	pushl	$0x123                  # imm = 0x123
  55f6e2:      	pushl	$0x2
  55f6e4:      	pushl	%ebx
  55f6e5:      	movl	%eax, %ecx
  55f6e7:      	calll	0x573f95 <.text+0x172f95>
  55f6ec:      	jmp	0x55f6f0 <.text+0x15e6f0>
  55f6ee:      	xorl	%eax, %eax
  55f6f0:      	pushl	%edi
  55f6f1:      	pushl	$0x633f18               # imm = 0x633F18
  55f6f6:      	pushl	%edi
  55f6f7:      	movl	%eax, %ecx
  55f6f9:      	movl	%eax, 0xc7016c
  55f6fe:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f703:      	movl	0xc7016c, %ecx
  55f709:      	pushl	$0x1
  55f70b:      	pushl	$0x633f28               # imm = 0x633F28
  55f710:      	pushl	$0x1
  55f712:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f717:      	movzbl	0x62a99e, %eax
  55f71e:      	movl	0xc7016c, %ecx
  55f724:      	pushl	%eax
  55f725:      	calll	0x572575 <.text+0x171575>
  55f72a:      	pushl	%ebp
  55f72b:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f730:      	popl	%ecx
  55f731:      	cmpl	%edi, %eax
  55f733:      	je	0x55f74f <.text+0x15e74f>
  55f735:      	pushl	$0xf
  55f737:      	pushl	$0x1c
  55f739:      	pushl	$0x103                  # imm = 0x103
  55f73e:      	pushl	$0x123                  # imm = 0x123
  55f743:      	pushl	$0x2
  55f745:      	pushl	%ebx
  55f746:      	movl	%eax, %ecx
  55f748:      	calll	0x573f95 <.text+0x172f95>
  55f74d:      	jmp	0x55f751 <.text+0x15e751>
  55f74f:      	xorl	%eax, %eax
  55f751:      	pushl	%edi
  55f752:      	pushl	$0x633f18               # imm = 0x633F18
  55f757:      	pushl	%edi
  55f758:      	movl	%eax, %ecx
  55f75a:      	movl	%eax, 0xc70168
  55f75f:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f764:      	movl	0xc70168, %ecx
  55f76a:      	pushl	$0x1
  55f76c:      	pushl	$0x633f28               # imm = 0x633F28
  55f771:      	pushl	$0x1
  55f773:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f778:      	movzbl	0x62a99f, %eax
  55f77f:      	movl	0xc70168, %ecx
  55f785:      	pushl	%eax
  55f786:      	calll	0x572575 <.text+0x171575>
  55f78b:      	pushl	%ebp
  55f78c:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f791:      	popl	%ecx
  55f792:      	cmpl	%edi, %eax
  55f794:      	je	0x55f7b0 <.text+0x15e7b0>
  55f796:      	pushl	$0xf
  55f798:      	pushl	$0x1c
  55f79a:      	pushl	$0xee
  55f79f:      	pushl	$0x23e                  # imm = 0x23E
  55f7a4:      	pushl	$0x2
  55f7a6:      	pushl	%ebx
  55f7a7:      	movl	%eax, %ecx
  55f7a9:      	calll	0x573f95 <.text+0x172f95>
  55f7ae:      	jmp	0x55f7b2 <.text+0x15e7b2>
  55f7b0:      	xorl	%eax, %eax
  55f7b2:      	pushl	%edi
  55f7b3:      	pushl	$0x633f18               # imm = 0x633F18
  55f7b8:      	pushl	%edi
  55f7b9:      	movl	%eax, %ecx
  55f7bb:      	movl	%eax, 0xc70164
  55f7c0:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f7c5:      	movl	0xc70164, %ecx
  55f7cb:      	pushl	$0x1
  55f7cd:      	pushl	$0x633f28               # imm = 0x633F28
  55f7d2:      	pushl	$0x1
  55f7d4:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f7d9:      	movzbl	0x62aa04, %eax
  55f7e0:      	movl	0xc70164, %ecx
  55f7e6:      	pushl	%eax
  55f7e7:      	calll	0x572575 <.text+0x171575>
  55f7ec:      	pushl	%ebp
  55f7ed:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f7f2:      	popl	%ecx
  55f7f3:      	cmpl	%edi, %eax
  55f7f5:      	je	0x55f811 <.text+0x15e811>
  55f7f7:      	pushl	$0xf
  55f7f9:      	pushl	$0x1c
  55f7fb:      	pushl	$0xee
  55f800:      	pushl	$0x91
  55f805:      	pushl	$0x2
  55f807:      	pushl	%ebx
  55f808:      	movl	%eax, %ecx
  55f80a:      	calll	0x573f95 <.text+0x172f95>
  55f80f:      	jmp	0x55f813 <.text+0x15e813>
  55f811:      	xorl	%eax, %eax
  55f813:      	pushl	%edi
  55f814:      	pushl	$0x633f18               # imm = 0x633F18
  55f819:      	pushl	%edi
  55f81a:      	movl	%eax, %ecx
  55f81c:      	movl	%eax, 0xc6fdb8
  55f821:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f826:      	movl	0xc6fdb8, %ecx
  55f82c:      	pushl	$0x1
  55f82e:      	pushl	$0x633f28               # imm = 0x633F28
  55f833:      	pushl	$0x1
  55f835:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f83a:      	pushl	%ebp
  55f83b:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f840:      	popl	%ecx
  55f841:      	cmpl	%edi, %eax
  55f843:      	je	0x55f85f <.text+0x15e85f>
  55f845:      	pushl	$0xf
  55f847:      	pushl	$0x1c
  55f849:      	pushl	$0xd9
  55f84e:      	pushl	$0x23e                  # imm = 0x23E
  55f853:      	pushl	$0x2
  55f855:      	pushl	%ebx
  55f856:      	movl	%eax, %ecx
  55f858:      	calll	0x573f95 <.text+0x172f95>
  55f85d:      	jmp	0x55f861 <.text+0x15e861>
  55f85f:      	xorl	%eax, %eax
  55f861:      	pushl	%edi
  55f862:      	pushl	$0x633f18               # imm = 0x633F18
  55f867:      	pushl	%edi
  55f868:      	movl	%eax, %ecx
  55f86a:      	movl	%eax, 0xc7014c
  55f86f:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f874:      	movl	0xc7014c, %ecx
  55f87a:      	pushl	$0x1
  55f87c:      	pushl	$0x633f28               # imm = 0x633F28
  55f881:      	pushl	$0x1
  55f883:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f888:      	movl	0xc7014c, %ecx
  55f88e:      	pushl	$0x1
  55f890:      	calll	0x572575 <.text+0x171575>
  55f895:      	pushl	%ebp
  55f896:      	calll	0x5c6d12 <.text+0x1c5d12>
  55f89b:      	popl	%ecx
  55f89c:      	cmpl	%edi, %eax
  55f89e:      	je	0x55f8ba <.text+0x15e8ba>
  55f8a0:      	pushl	$0xf
  55f8a2:      	pushl	$0x1c
  55f8a4:      	pushl	$0xee
  55f8a9:      	pushl	$0x1b2                  # imm = 0x1B2
  55f8ae:      	pushl	$0x15
  55f8b0:      	pushl	%ebx
  55f8b1:      	movl	%eax, %ecx
  55f8b3:      	calll	0x573f95 <.text+0x172f95>
  55f8b8:      	jmp	0x55f8bc <.text+0x15e8bc>
  55f8ba:      	xorl	%eax, %eax
  55f8bc:      	pushl	$0x16
  55f8be:      	pushl	$0x633f18               # imm = 0x633F18
  55f8c3:      	pushl	%edi
  55f8c4:      	movl	%eax, %ecx
  55f8c6:      	movl	%eax, 0xc70160
  55f8cb:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f8d0:      	movl	0xc70160, %ecx
  55f8d6:      	pushl	$0x2
  55f8d8:      	pushl	$0x5f077c               # imm = 0x5F077C
  55f8dd:      	pushl	$0x1
  55f8df:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f8e4:      	movl	0xc70160, %ecx
  55f8ea:      	pushl	$0x3
  55f8ec:      	pushl	$0x5f0778               # imm = 0x5F0778
  55f8f1:      	pushl	$0x2
  55f8f3:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f8f8:      	movl	0xc70160, %ecx
  55f8fe:      	pushl	$0x4
  55f900:      	pushl	$0x5f0774               # imm = 0x5F0774
  55f905:      	pushl	$0x3
  55f907:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f90c:      	movl	0xc70160, %ecx
  55f912:      	pushl	$0x5
  55f914:      	pushl	$0x5f0770               # imm = 0x5F0770
  55f919:      	pushl	$0x4
  55f91b:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f920:      	movl	0xc70160, %ecx
  55f926:      	pushl	$0x6
  55f928:      	pushl	$0x5f076c               # imm = 0x5F076C
  55f92d:      	pushl	$0x5
  55f92f:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f934:      	movl	0xc70160, %ecx
  55f93a:      	pushl	$0x7
  55f93c:      	pushl	$0x5f0768               # imm = 0x5F0768
  55f941:      	pushl	$0x6
  55f943:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f948:      	movl	0xc70160, %ecx
  55f94e:      	pushl	$0x8
  55f950:      	pushl	$0x5f0764               # imm = 0x5F0764
  55f955:      	pushl	$0x7
  55f957:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f95c:      	movl	0xc70160, %ecx
  55f962:      	pushl	$0x9
  55f964:      	pushl	$0x5f0760               # imm = 0x5F0760
  55f969:      	pushl	$0x8
  55f96b:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f970:      	movl	0xc70160, %ecx
  55f976:      	pushl	$0xa
  55f978:      	pushl	$0x5f075c               # imm = 0x5F075C
  55f97d:      	pushl	$0x9
  55f97f:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f984:      	movl	0xc70160, %ecx
  55f98a:      	pushl	$0xb
  55f98c:      	pushl	$0x5f0758               # imm = 0x5F0758
  55f991:      	pushl	$0xa
  55f993:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f998:      	movl	0xc70160, %ecx
  55f99e:      	pushl	$0xc
  55f9a0:      	pushl	$0x5f0754               # imm = 0x5F0754
  55f9a5:      	pushl	$0xb
  55f9a7:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f9ac:      	movl	0xc70160, %ecx
  55f9b2:      	pushl	$0xd
  55f9b4:      	pushl	$0x5f0750               # imm = 0x5F0750
  55f9b9:      	pushl	$0xc
  55f9bb:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f9c0:      	movl	0xc70160, %ecx
  55f9c6:      	pushl	$0xe
  55f9c8:      	pushl	$0x5f074c               # imm = 0x5F074C
  55f9cd:      	pushl	$0xd
  55f9cf:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f9d4:      	movl	0xc70160, %ecx
  55f9da:      	pushl	$0xf
  55f9dc:      	pushl	$0x5f0748               # imm = 0x5F0748
  55f9e1:      	pushl	$0xe
  55f9e3:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f9e8:      	movl	0xc70160, %ecx
  55f9ee:      	pushl	$0x10
  55f9f0:      	pushl	$0x5f0744               # imm = 0x5F0744
  55f9f5:      	pushl	$0xf
  55f9f7:      	calll	0x56f5c7 <.text+0x16e5c7>
  55f9fc:      	movl	0xc70160, %ecx
  55fa02:      	pushl	$0x11
  55fa04:      	pushl	$0x5f0740               # imm = 0x5F0740
  55fa09:      	pushl	$0x10
  55fa0b:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fa10:      	movl	0xc70160, %ecx
  55fa16:      	pushl	$0x12
  55fa18:      	pushl	$0x5f073c               # imm = 0x5F073C
  55fa1d:      	pushl	$0x11
  55fa1f:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fa24:      	movl	0xc70160, %ecx
  55fa2a:      	pushl	$0x13
  55fa2c:      	pushl	$0x5f0738               # imm = 0x5F0738
  55fa31:      	pushl	$0x12
  55fa33:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fa38:      	movl	0xc70160, %ecx
  55fa3e:      	pushl	$0x14
  55fa40:      	pushl	$0x5f0734               # imm = 0x5F0734
  55fa45:      	pushl	$0x13
  55fa47:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fa4c:      	movl	0xc70160, %ecx
  55fa52:      	pushl	$0x15
  55fa54:      	pushl	$0x5f0730               # imm = 0x5F0730
  55fa59:      	pushl	$0x14
  55fa5b:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fa60:      	pushl	%ebp
  55fa61:      	calll	0x5c6d12 <.text+0x1c5d12>
  55fa66:      	popl	%ecx
  55fa67:      	cmpl	%edi, %eax
  55fa69:      	je	0x55fa85 <.text+0x15ea85>
  55fa6b:      	pushl	$0xf
  55fa6d:      	pushl	$0x1c
  55fa6f:      	pushl	$0xd9
  55fa74:      	pushl	$0x1b2                  # imm = 0x1B2
  55fa79:      	pushl	$0xc
  55fa7b:      	pushl	%ebx
  55fa7c:      	movl	%eax, %ecx
  55fa7e:      	calll	0x573f95 <.text+0x172f95>
  55fa83:      	jmp	0x55fa87 <.text+0x15ea87>
  55fa85:      	xorl	%eax, %eax
  55fa87:      	pushl	%edi
  55fa88:      	pushl	$0x633f18               # imm = 0x633F18
  55fa8d:      	pushl	%edi
  55fa8e:      	movl	%eax, %ecx
  55fa90:      	movl	%eax, 0xc7015c
  55fa95:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fa9a:      	movl	0xc7015c, %ecx
  55faa0:      	pushl	$0x5
  55faa2:      	pushl	$0x5f0728               # imm = 0x5F0728
  55faa7:      	pushl	$0x1
  55faa9:      	calll	0x56f5c7 <.text+0x16e5c7>
  55faae:      	movl	0xc7015c, %ecx
  55fab4:      	pushl	$0xa
  55fab6:      	pushl	$0x5f0720               # imm = 0x5F0720
  55fabb:      	pushl	$0x2
  55fabd:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fac2:      	movl	0xc7015c, %ecx
  55fac8:      	pushl	$0xf
  55faca:      	pushl	$0x5f0718               # imm = 0x5F0718
  55facf:      	pushl	$0x3
  55fad1:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fad6:      	movl	0xc7015c, %ecx
  55fadc:      	pushl	$0x14
  55fade:      	pushl	$0x5f0710               # imm = 0x5F0710
  55fae3:      	pushl	$0x4
  55fae5:      	calll	0x56f5c7 <.text+0x16e5c7>
  55faea:      	movl	0xc7015c, %ecx
  55faf0:      	pushl	$0x1e
  55faf2:      	pushl	$0x5f0708               # imm = 0x5F0708
  55faf7:      	pushl	$0x5
  55faf9:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fafe:      	movl	0xc7015c, %ecx
  55fb04:      	pushl	$0x28
  55fb06:      	pushl	$0x5f0700               # imm = 0x5F0700
  55fb0b:      	pushl	$0x6
  55fb0d:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fb12:      	movl	0xc7015c, %ecx
  55fb18:      	pushl	$0x32
  55fb1a:      	pushl	$0x5f06f8               # imm = 0x5F06F8
  55fb1f:      	pushl	$0x7
  55fb21:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fb26:      	movl	0xc7015c, %ecx
  55fb2c:      	pushl	$0x3c
  55fb2e:      	pushl	$0x5f06f0               # imm = 0x5F06F0
  55fb33:      	pushl	$0x8
  55fb35:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fb3a:      	movl	0xc7015c, %ecx
  55fb40:      	pushl	$0x5a
  55fb42:      	pushl	$0x5f06e8               # imm = 0x5F06E8
  55fb47:      	pushl	$0x9
  55fb49:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fb4e:      	movl	0xc7015c, %ecx
  55fb54:      	pushl	$0x78
  55fb56:      	pushl	$0x5f06e0               # imm = 0x5F06E0
  55fb5b:      	pushl	$0xa
  55fb5d:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fb62:      	movl	0xc7015c, %ecx
  55fb68:      	pushl	$0xb4
  55fb6d:      	pushl	$0x5f06d8               # imm = 0x5F06D8
  55fb72:      	pushl	$0xb
  55fb74:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fb79:      	pushl	%ebp
  55fb7a:      	calll	0x5c6d12 <.text+0x1c5d12>
  55fb7f:      	popl	%ecx
  55fb80:      	cmpl	%edi, %eax
  55fb82:      	je	0x55fb9e <.text+0x15eb9e>
  55fb84:      	pushl	$0xf
  55fb86:      	pushl	$0x1c
  55fb88:      	pushl	$0xee
  55fb8d:      	pushl	$0x23e                  # imm = 0x23E
  55fb92:      	pushl	$0xb
  55fb94:      	pushl	%ebx
  55fb95:      	movl	%eax, %ecx
  55fb97:      	calll	0x573f95 <.text+0x172f95>
  55fb9c:      	jmp	0x55fba0 <.text+0x15eba0>
  55fb9e:      	xorl	%eax, %eax
  55fba0:      	pushl	%edi
  55fba1:      	pushl	$0x633f18               # imm = 0x633F18
  55fba6:      	pushl	%edi
  55fba7:      	movl	%eax, %ecx
  55fba9:      	movl	%eax, 0xc70158
  55fbae:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fbb3:      	movl	0xc70158, %ecx
  55fbb9:      	pushl	$0xa
  55fbbb:      	pushl	$0x5f075c               # imm = 0x5F075C
  55fbc0:      	pushl	$0x1
  55fbc2:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fbc7:      	movl	0xc70158, %ecx
  55fbcd:      	pushl	$0x14
  55fbcf:      	pushl	$0x5f0734               # imm = 0x5F0734
  55fbd4:      	pushl	$0x2
  55fbd6:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fbdb:      	movl	0xc70158, %ecx
  55fbe1:      	pushl	$0x1e
  55fbe3:      	pushl	$0x5f06d4               # imm = 0x5F06D4
  55fbe8:      	pushl	$0x3
  55fbea:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fbef:      	movl	0xc70158, %ecx
  55fbf5:      	pushl	$0x28
  55fbf7:      	pushl	$0x5f06d0               # imm = 0x5F06D0
  55fbfc:      	pushl	$0x4
  55fbfe:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fc03:      	movl	0xc70158, %ecx
  55fc09:      	pushl	$0x32
  55fc0b:      	pushl	$0x5f06cc               # imm = 0x5F06CC
  55fc10:      	pushl	$0x5
  55fc12:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fc17:      	movl	0xc70158, %ecx
  55fc1d:      	pushl	$0x3c
  55fc1f:      	pushl	$0x5f06c8               # imm = 0x5F06C8
  55fc24:      	pushl	$0x6
  55fc26:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fc2b:      	movl	0xc70158, %ecx
  55fc31:      	pushl	$0x46
  55fc33:      	pushl	$0x5f06c4               # imm = 0x5F06C4
  55fc38:      	pushl	$0x7
  55fc3a:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fc3f:      	movl	0xc70158, %ecx
  55fc45:      	pushl	$0x50
  55fc47:      	pushl	$0x5f06c0               # imm = 0x5F06C0
  55fc4c:      	pushl	$0x8
  55fc4e:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fc53:      	movl	0xc70158, %ecx
  55fc59:      	pushl	$0x5a
  55fc5b:      	pushl	$0x5f06bc               # imm = 0x5F06BC
  55fc60:      	pushl	$0x9
  55fc62:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fc67:      	movl	0xc70158, %ecx
  55fc6d:      	pushl	$0x64
  55fc6f:      	pushl	$0x5d7828               # imm = 0x5D7828
  55fc74:      	pushl	$0xa
  55fc76:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fc7b:      	pushl	%ebp
  55fc7c:      	calll	0x5c6d12 <.text+0x1c5d12>
  55fc81:      	popl	%ecx
  55fc82:      	cmpl	%edi, %eax
  55fc84:      	je	0x55fca0 <.text+0x15eca0>
  55fc86:      	pushl	$0xf
  55fc88:      	pushl	$0x1c
  55fc8a:      	pushl	$0x103                  # imm = 0x103
  55fc8f:      	pushl	$0x23e                  # imm = 0x23E
  55fc94:      	pushl	$0xb
  55fc96:      	pushl	%ebx
  55fc97:      	movl	%eax, %ecx
  55fc99:      	calll	0x573f95 <.text+0x172f95>
  55fc9e:      	jmp	0x55fca2 <.text+0x15eca2>
  55fca0:      	xorl	%eax, %eax
  55fca2:      	pushl	%edi
  55fca3:      	pushl	$0x633f18               # imm = 0x633F18
  55fca8:      	pushl	%edi
  55fca9:      	movl	%eax, %ecx
  55fcab:      	movl	%eax, 0xc70154
  55fcb0:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fcb5:      	movl	0xc70154, %ecx
  55fcbb:      	pushl	$0x1
  55fcbd:      	pushl	$0x5ef0a8               # imm = 0x5EF0A8
  55fcc2:      	pushl	$0x1
  55fcc4:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fcc9:      	movl	0xc70154, %ecx
  55fccf:      	pushl	$0x2
  55fcd1:      	pushl	$0x5f077c               # imm = 0x5F077C
  55fcd6:      	pushl	$0x2
  55fcd8:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fcdd:      	movl	0xc70154, %ecx
  55fce3:      	pushl	$0x3
  55fce5:      	pushl	$0x5f0778               # imm = 0x5F0778
  55fcea:      	pushl	$0x3
  55fcec:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fcf1:      	movl	0xc70154, %ecx
  55fcf7:      	pushl	$0x4
  55fcf9:      	pushl	$0x5f0774               # imm = 0x5F0774
  55fcfe:      	pushl	$0x4
  55fd00:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fd05:      	movl	0xc70154, %ecx
  55fd0b:      	pushl	$0x5
  55fd0d:      	pushl	$0x5f0770               # imm = 0x5F0770
  55fd12:      	pushl	$0x5
  55fd14:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fd19:      	movl	0xc70154, %ecx
  55fd1f:      	pushl	$0x6
  55fd21:      	pushl	$0x5f076c               # imm = 0x5F076C
  55fd26:      	pushl	$0x6
  55fd28:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fd2d:      	movl	0xc70154, %ecx
  55fd33:      	pushl	$0x7
  55fd35:      	pushl	$0x5f0768               # imm = 0x5F0768
  55fd3a:      	pushl	$0x7
  55fd3c:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fd41:      	movl	0xc70154, %ecx
  55fd47:      	pushl	$0x8
  55fd49:      	pushl	$0x5f0764               # imm = 0x5F0764
  55fd4e:      	pushl	$0x8
  55fd50:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fd55:      	movl	0xc70154, %ecx
  55fd5b:      	pushl	$0x9
  55fd5d:      	pushl	$0x5f0760               # imm = 0x5F0760
  55fd62:      	pushl	$0x9
  55fd64:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fd69:      	movl	0xc70154, %ecx
  55fd6f:      	pushl	$0xa
  55fd71:      	pushl	$0x5f075c               # imm = 0x5F075C
  55fd76:      	pushl	$0xa
  55fd78:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fd7d:      	movl	0xc70154, %ecx
  55fd83:      	pushl	%edi
  55fd84:      	calll	0x57403d <.text+0x17303d>
  55fd89:      	pushl	%ebp
  55fd8a:      	calll	0x5c6d12 <.text+0x1c5d12>
  55fd8f:      	popl	%ecx
  55fd90:      	cmpl	%edi, %eax
  55fd92:      	je	0x55fdae <.text+0x15edae>
  55fd94:      	pushl	$0xf
  55fd96:      	pushl	$0x1c
  55fd98:      	pushl	$0xd9
  55fd9d:      	pushl	$0x1b2                  # imm = 0x1B2
  55fda2:      	pushl	$0x5
  55fda4:      	pushl	%ebx
  55fda5:      	movl	%eax, %ecx
  55fda7:      	calll	0x573f95 <.text+0x172f95>
  55fdac:      	jmp	0x55fdb0 <.text+0x15edb0>
  55fdae:      	xorl	%eax, %eax
  55fdb0:      	pushl	$0x1
  55fdb2:      	pushl	$0x5ef0a8               # imm = 0x5EF0A8
  55fdb7:      	pushl	%edi
  55fdb8:      	movl	%eax, %ecx
  55fdba:      	movl	%eax, 0xc70150
  55fdbf:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fdc4:      	movl	0xc70150, %ecx
  55fdca:      	pushl	$0x2
  55fdcc:      	pushl	$0x5f077c               # imm = 0x5F077C
  55fdd1:      	pushl	$0x1
  55fdd3:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fdd8:      	movl	0xc70150, %ecx
  55fdde:      	pushl	$0x3
  55fde0:      	pushl	$0x5f0778               # imm = 0x5F0778
  55fde5:      	pushl	$0x2
  55fde7:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fdec:      	movl	0xc70150, %ecx
  55fdf2:      	pushl	$0x4
  55fdf4:      	pushl	$0x5f0774               # imm = 0x5F0774
  55fdf9:      	pushl	$0x3
  55fdfb:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fe00:      	movl	0xc70150, %ecx
  55fe06:      	pushl	$0x5
  55fe08:      	pushl	$0x5f0770               # imm = 0x5F0770
  55fe0d:      	pushl	$0x4
  55fe0f:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fe14:      	movl	0xc70150, %ecx
  55fe1a:      	pushl	$0x3
  55fe1c:      	calll	0x572575 <.text+0x171575>
  55fe21:      	pushl	%ebp
  55fe22:      	calll	0x5c6d12 <.text+0x1c5d12>
  55fe27:      	popl	%ecx
  55fe28:      	cmpl	%edi, %eax
  55fe2a:      	je	0x55fe46 <.text+0x15ee46>
  55fe2c:      	pushl	$0xf
  55fe2e:      	pushl	$0x1c
  55fe30:      	pushl	$0x103                  # imm = 0x103
  55fe35:      	pushl	$0x91
  55fe3a:      	pushl	$0xf
  55fe3c:      	pushl	%ebx
  55fe3d:      	movl	%eax, %ecx
  55fe3f:      	calll	0x573f95 <.text+0x172f95>
  55fe44:      	jmp	0x55fe48 <.text+0x15ee48>
  55fe46:      	xorl	%eax, %eax
  55fe48:      	pushl	$0x1
  55fe4a:      	pushl	$0x5ef0a8               # imm = 0x5EF0A8
  55fe4f:      	pushl	%edi
  55fe50:      	movl	%eax, %ecx
  55fe52:      	movl	%eax, 0xc70144
  55fe57:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fe5c:      	movl	0xc70144, %ecx
  55fe62:      	pushl	$0x2
  55fe64:      	pushl	$0x5f077c               # imm = 0x5F077C
  55fe69:      	pushl	$0x1
  55fe6b:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fe70:      	movl	0xc70144, %ecx
  55fe76:      	pushl	$0x3
  55fe78:      	pushl	$0x5f0778               # imm = 0x5F0778
  55fe7d:      	pushl	$0x2
  55fe7f:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fe84:      	movl	0xc70144, %ecx
  55fe8a:      	pushl	$0x4
  55fe8c:      	pushl	$0x5f0774               # imm = 0x5F0774
  55fe91:      	pushl	$0x3
  55fe93:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fe98:      	movl	0xc70144, %ecx
  55fe9e:      	pushl	$0x5
  55fea0:      	pushl	$0x5f0770               # imm = 0x5F0770
  55fea5:      	pushl	$0x4
  55fea7:      	calll	0x56f5c7 <.text+0x16e5c7>
  55feac:      	movl	0xc70144, %ecx
  55feb2:      	pushl	$0x6
  55feb4:      	pushl	$0x5f076c               # imm = 0x5F076C
  55feb9:      	pushl	$0x5
  55febb:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fec0:      	movl	0xc70144, %ecx
  55fec6:      	pushl	$0x7
  55fec8:      	pushl	$0x5f0768               # imm = 0x5F0768
  55fecd:      	pushl	$0x6
  55fecf:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fed4:      	movl	0xc70144, %ecx
  55feda:      	pushl	$0x8
  55fedc:      	pushl	$0x5f0764               # imm = 0x5F0764
  55fee1:      	pushl	$0x7
  55fee3:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fee8:      	movl	0xc70144, %ecx
  55feee:      	pushl	$0x9
  55fef0:      	pushl	$0x5f0760               # imm = 0x5F0760
  55fef5:      	pushl	$0x8
  55fef7:      	calll	0x56f5c7 <.text+0x16e5c7>
  55fefc:      	movl	0xc70144, %ecx
  55ff02:      	pushl	$0xa
  55ff04:      	pushl	$0x5f075c               # imm = 0x5F075C
  55ff09:      	pushl	$0x9
  55ff0b:      	calll	0x56f5c7 <.text+0x16e5c7>
  55ff10:      	movl	0xc70144, %ecx
  55ff16:      	pushl	$0xb
  55ff18:      	pushl	$0x5f0758               # imm = 0x5F0758
  55ff1d:      	pushl	$0xa
  55ff1f:      	calll	0x56f5c7 <.text+0x16e5c7>
  55ff24:      	movl	0xc70144, %ecx
  55ff2a:      	pushl	$0xc
  55ff2c:      	pushl	$0x5f0754               # imm = 0x5F0754
  55ff31:      	pushl	$0xb
  55ff33:      	calll	0x56f5c7 <.text+0x16e5c7>
  55ff38:      	movl	0xc70144, %ecx
  55ff3e:      	pushl	$0xd
  55ff40:      	pushl	$0x5f0750               # imm = 0x5F0750
  55ff45:      	pushl	$0xc
  55ff47:      	calll	0x56f5c7 <.text+0x16e5c7>
  55ff4c:      	movl	0xc70144, %ecx
  55ff52:      	pushl	$0xe
  55ff54:      	pushl	$0x5f074c               # imm = 0x5F074C
  55ff59:      	pushl	$0xd
  55ff5b:      	calll	0x56f5c7 <.text+0x16e5c7>
  55ff60:      	movl	0xc70144, %ecx
  55ff66:      	pushl	$0xf
  55ff68:      	pushl	$0x5f0748               # imm = 0x5F0748
  55ff6d:      	pushl	$0xe
  55ff6f:      	calll	0x56f5c7 <.text+0x16e5c7>
  55ff74:      	pushl	%ebp
  55ff75:      	calll	0x5c6d12 <.text+0x1c5d12>
  55ff7a:      	popl	%ecx
  55ff7b:      	cmpl	%edi, %eax
  55ff7d:      	je	0x55ff99 <.text+0x15ef99>
  55ff7f:      	pushl	$0xf
  55ff81:      	pushl	$0x1c
  55ff83:      	pushl	$0x103                  # imm = 0x103
  55ff88:      	pushl	$0x1b2                  # imm = 0x1B2
  55ff8d:      	pushl	$0x2
  55ff8f:      	pushl	%ebx
  55ff90:      	movl	%eax, %ecx
  55ff92:      	calll	0x573f95 <.text+0x172f95>
  55ff97:      	jmp	0x55ff9b <.text+0x15ef9b>
  55ff99:      	xorl	%eax, %eax
  55ff9b:      	pushl	%edi
  55ff9c:      	pushl	$0x633f18               # imm = 0x633F18
  55ffa1:      	pushl	%edi
  55ffa2:      	movl	%eax, %ecx
  55ffa4:      	movl	%eax, 0xc70148
  55ffa9:      	calll	0x56f5c7 <.text+0x16e5c7>
  55ffae:      	movl	0xc70148, %ecx
  55ffb4:      	pushl	$0x1
  55ffb6:      	pushl	$0x633f28               # imm = 0x633F28
  55ffbb:      	pushl	$0x1
  55ffbd:      	calll	0x56f5c7 <.text+0x16e5c7>
  55ffc2:      	pushl	$0x5f06b0               # imm = 0x5F06B0
  55ffc7:      	pushl	%ebx
  55ffc8:      	calll	0x571f12 <.text+0x170f12>
  55ffcd:      	pushl	$0x5f06a4               # imm = 0x5F06A4
  55ffd2:      	pushl	%ebx
  55ffd3:      	movl	%eax, 0xc700f0
  55ffd8:      	calll	0x571f12 <.text+0x170f12>
  55ffdd:      	pushl	$0x5f0698               # imm = 0x5F0698
  55ffe2:      	pushl	%ebx
  55ffe3:      	movl	%eax, 0xc700ec
  55ffe8:      	calll	0x571f12 <.text+0x170f12>
  55ffed:      	pushl	$0x5f068c               # imm = 0x5F068C
  55fff2:      	pushl	%ebx
  55fff3:      	movl	%eax, 0xc700e8
  55fff8:      	calll	0x571f12 <.text+0x170f12>
  55fffd:      	addl	$0x20, %esp
  560000:      	movl	%eax, 0xc700e4
  560005:      	movl	$0xc700d0, 0x14(%esp)   # imm = 0xC700D0
  56000d:      	xorl	%ebp, %ebp
  56000f:      	pushl	0x633b04(%ebp)
  560015:      	pushl	%ebx
  560016:      	calll	0x571f12 <.text+0x170f12>
  56001b:      	popl	%ecx
  56001c:      	popl	%ecx
  56001d:      	movl	0x14(%esp), %ecx
  560021:      	movl	%eax, (%ecx)
  560023:      	cmpl	%edi, %eax
  560025:      	jne	0x56003b <.text+0x15f03b>
  560027:      	pushl	0x633b08(%ebp)
  56002d:      	pushl	%ebx
  56002e:      	calll	0x571f12 <.text+0x170f12>
  560033:      	popl	%ecx
  560034:      	popl	%ecx
  560035:      	movl	0x14(%esp), %ecx
  560039:      	movl	%eax, (%ecx)
  56003b:      	addl	$0x4, 0x14(%esp)
  560040:      	addl	$0x10, %ebp
  560043:      	cmpl	$0x50, %ebp
  560046:      	jb	0x56000f <.text+0x15f00f>
  560048:      	pushl	$0x5f0684               # imm = 0x5F0684
  56004d:      	pushl	%ebx
  56004e:      	calll	0x571f12 <.text+0x170f12>
  560053:      	pushl	$0x5f067c               # imm = 0x5F067C
  560058:      	pushl	%ebx
  560059:      	movl	%eax, 0xc700cc
  56005e:      	calll	0x571f12 <.text+0x170f12>
  560063:      	pushl	$0x5d2afc               # imm = 0x5D2AFC
  560068:      	movl	%eax, 0xc700c8
  56006d:      	leal	0x2d0(%esp), %eax
  560074:      	pushl	$0x5ef8c8               # imm = 0x5EF8C8
  560079:      	pushl	%eax
  56007a:      	calll	*0x5ce49c
  560080:      	movl	$0x128, %ebp            # imm = 0x128
  560085:      	pushl	%ebp
  560086:      	calll	0x5c6d12 <.text+0x1c5d12>
  56008b:      	addl	$0x20, %esp
  56008e:      	cmpl	%edi, %eax
  560090:      	je	0x5600b8 <.text+0x15f0b8>
  560092:      	pushl	%edi
  560093:      	pushl	$0xc
  560095:      	pushl	$0xa0
  56009a:      	pushl	$0x4
  56009c:      	pushl	$0xf0
  5600a1:      	leal	0x2d0(%esp), %ecx
  5600a8:      	pushl	%ecx
  5600a9:      	pushl	%ebx
  5600aa:      	movl	%eax, %ecx
  5600ac:      	calll	0x572841 <.text+0x171841>
  5600b1:      	movl	%eax, 0xc7012c
  5600b6:      	jmp	0x5600be <.text+0x15f0be>
  5600b8:      	movl	%edi, 0xc7012c
  5600be:      	pushl	%ebp
  5600bf:      	calll	0x5c6d12 <.text+0x1c5d12>
  5600c4:      	popl	%ecx
  5600c5:      	cmpl	%edi, %eax
  5600c7:      	je	0x5600ec <.text+0x15f0ec>
  5600c9:      	pushl	%edi
  5600ca:      	pushl	$0xc
  5600cc:      	pushl	$0xa0
  5600d1:      	pushl	$0x10
  5600d3:      	pushl	$0xf0
  5600d8:      	pushl	$0x5d0e3a               # imm = 0x5D0E3A
  5600dd:      	pushl	%ebx
  5600de:      	movl	%eax, %ecx
  5600e0:      	calll	0x572841 <.text+0x171841>
  5600e5:      	movl	%eax, 0xc70128
  5600ea:      	jmp	0x5600f2 <.text+0x15f0f2>
  5600ec:      	movl	%edi, 0xc70128
  5600f2:      	pushl	%ebp
  5600f3:      	calll	0x5c6d12 <.text+0x1c5d12>
  5600f8:      	popl	%ecx
  5600f9:      	cmpl	%edi, %eax
  5600fb:      	je	0x56011a <.text+0x15f11a>
  5600fd:      	pushl	%edi
  5600fe:      	pushl	$0xd
  560100:      	pushl	$0x34
  560102:      	pushl	$0x2c
  560104:      	pushl	$0x2d
  560106:      	pushl	$0x5f0674               # imm = 0x5F0674
  56010b:      	pushl	%ebx
  56010c:      	movl	%eax, %ecx
  56010e:      	calll	0x572841 <.text+0x171841>
  560113:      	movl	%eax, 0xc70124
  560118:      	jmp	0x560120 <.text+0x15f120>
  56011a:      	movl	%edi, 0xc70124
  560120:      	pushl	%ebp
  560121:      	calll	0x5c6d12 <.text+0x1c5d12>
  560126:      	popl	%ecx
  560127:      	cmpl	%edi, %eax
  560129:      	je	0x56014b <.text+0x15f14b>
  56012b:      	pushl	%edi
  56012c:      	pushl	$0xd
  56012e:      	pushl	$0x62
  560130:      	pushl	$0x2c
  560132:      	pushl	$0xc7
  560137:      	pushl	$0x5f0668               # imm = 0x5F0668
  56013c:      	pushl	%ebx
  56013d:      	movl	%eax, %ecx
  56013f:      	calll	0x572841 <.text+0x171841>
  560144:      	movl	%eax, 0xc70120
  560149:      	jmp	0x560151 <.text+0x15f151>
  56014b:      	movl	%edi, 0xc70120
  560151:      	pushl	%ebp
  560152:      	calll	0x5c6d12 <.text+0x1c5d12>
  560157:      	popl	%ecx
  560158:      	cmpl	%edi, %eax
  56015a:      	je	0x56017f <.text+0x15f17f>
  56015c:      	pushl	%edi
  56015d:      	pushl	$0xf
  56015f:      	pushl	$0x104                  # imm = 0x104
  560164:      	pushl	$0x122                  # imm = 0x122
  560169:      	pushl	$0x2e
  56016b:      	pushl	$0x5f0658               # imm = 0x5F0658
  560170:      	pushl	%ebx
  560171:      	movl	%eax, %ecx
  560173:      	calll	0x572841 <.text+0x171841>
  560178:      	movl	%eax, 0xc7011c
  56017d:      	jmp	0x560185 <.text+0x15f185>
  56017f:      	movl	%edi, 0xc7011c
  560185:      	pushl	%ebp
  560186:      	calll	0x5c6d12 <.text+0x1c5d12>
  56018b:      	popl	%ecx
  56018c:      	cmpl	%edi, %eax
  56018e:      	je	0x5601b3 <.text+0x15f1b3>
  560190:      	pushl	%edi
  560191:      	pushl	$0xf
  560193:      	pushl	$0x8c
  560198:      	pushl	$0x2b
  56019a:      	pushl	$0x15b                  # imm = 0x15B
  56019f:      	pushl	$0x5f0650               # imm = 0x5F0650
  5601a4:      	pushl	%ebx
  5601a5:      	movl	%eax, %ecx
  5601a7:      	calll	0x572841 <.text+0x171841>
  5601ac:      	movl	%eax, 0xc70118
  5601b1:      	jmp	0x5601b9 <.text+0x15f1b9>
  5601b3:      	movl	%edi, 0xc70118
  5601b9:      	pushl	%ebp
  5601ba:      	calll	0x5c6d12 <.text+0x1c5d12>
  5601bf:      	popl	%ecx
  5601c0:      	cmpl	%edi, %eax
  5601c2:      	je	0x5601e4 <.text+0x15f1e4>
  5601c4:      	pushl	%edi
  5601c5:      	pushl	$0xf
  5601c7:      	pushl	$0x64
  5601c9:      	pushl	$0x2b
  5601cb:      	pushl	$0x1ef                  # imm = 0x1EF
  5601d0:      	pushl	$0x5f0644               # imm = 0x5F0644
  5601d5:      	pushl	%ebx
  5601d6:      	movl	%eax, %ecx
  5601d8:      	calll	0x572841 <.text+0x171841>
  5601dd:      	movl	%eax, 0xc70114
  5601e2:      	jmp	0x5601ea <.text+0x15f1ea>
  5601e4:      	movl	%edi, 0xc70114
  5601ea:      	pushl	%ebp
  5601eb:      	calll	0x5c6d12 <.text+0x1c5d12>
  5601f0:      	popl	%ecx
  5601f1:      	cmpl	%edi, %eax
  5601f3:      	je	0x560218 <.text+0x15f218>
  5601f5:      	pushl	%edi
  5601f6:      	pushl	$0xd
  5601f8:      	pushl	$0x77
  5601fa:      	pushl	$0xbd
  5601ff:      	pushl	$0x14d                  # imm = 0x14D
  560204:      	pushl	$0x5f0634               # imm = 0x5F0634
  560209:      	pushl	%ebx
  56020a:      	movl	%eax, %ecx
  56020c:      	calll	0x572841 <.text+0x171841>
  560211:      	movl	%eax, 0xc70110
  560216:      	jmp	0x56021e <.text+0x15f21e>
  560218:      	movl	%edi, 0xc70110
  56021e:      	pushl	$0x18
  560220:      	calll	0x5c6d12 <.text+0x1c5d12>
  560225:      	popl	%ecx
  560226:      	cmpl	%edi, %eax
  560228:      	je	0x560238 <.text+0x15f238>
  56022a:      	movl	%eax, %ecx
  56022c:      	calll	0x556633 <.text+0x155633>
  560231:      	movl	%eax, 0xc700f4
  560236:      	jmp	0x56023e <.text+0x15f23e>
  560238:      	movl	%edi, 0xc700f4
  56023e:      	pushl	%ebp
  56023f:      	calll	0x5c6d12 <.text+0x1c5d12>
  560244:      	popl	%ecx
  560245:      	cmpl	%edi, %eax
  560247:      	je	0x56026c <.text+0x15f26c>
  560249:      	pushl	%edi
  56024a:      	pushl	$0xf
  56024c:      	pushl	$0x46
  56024e:      	pushl	$0x122                  # imm = 0x122
  560253:      	pushl	$0x16a                  # imm = 0x16A
  560258:      	pushl	$0x5ef36c               # imm = 0x5EF36C
  56025d:      	pushl	%ebx
  56025e:      	movl	%eax, %ecx
  560260:      	calll	0x572841 <.text+0x171841>
  560265:      	movl	%eax, 0xc7010c
  56026a:      	jmp	0x560272 <.text+0x15f272>
  56026c:      	movl	%edi, 0xc7010c
  560272:      	pushl	%ebp
  560273:      	calll	0x5c6d12 <.text+0x1c5d12>
  560278:      	popl	%ecx
  560279:      	cmpl	%edi, %eax
  56027b:      	je	0x56029e <.text+0x15f29e>
  56027d:      	pushl	%edi
  56027e:      	pushl	$0x11
  560280:      	pushl	$0xcd
  560285:      	pushl	$0x1c2                  # imm = 0x1C2
  56028a:      	pushl	$0xd8
  56028f:      	pushl	$0x5df2cc               # imm = 0x5DF2CC
  560294:      	pushl	%ebx
  560295:      	movl	%eax, %ecx
  560297:      	calll	0x572841 <.text+0x171841>
  56029c:      	jmp	0x5602a0 <.text+0x15f2a0>
  56029e:      	xorl	%eax, %eax
  5602a0:      	pushl	$0x1
  5602a2:      	movl	%eax, %ecx
  5602a4:      	movl	%eax, 0xc70100
  5602a9:      	calll	0x572935 <.text+0x171935>
  5602ae:      	pushl	%ebp
  5602af:      	calll	0x5c6d12 <.text+0x1c5d12>
  5602b4:      	popl	%ecx
  5602b5:      	cmpl	%edi, %eax
  5602b7:      	je	0x5602d4 <.text+0x15f2d4>
  5602b9:      	pushl	%edi
  5602ba:      	pushl	$0xd
  5602bc:      	pushl	$0x14
  5602be:      	pushl	$0x136                  # imm = 0x136
  5602c3:      	pushl	$0x3c
  5602c5:      	pushl	$0x5e655c               # imm = 0x5E655C
  5602ca:      	pushl	%ebx
  5602cb:      	movl	%eax, %ecx
  5602cd:      	calll	0x572841 <.text+0x171841>
  5602d2:      	jmp	0x5602d6 <.text+0x15f2d6>
  5602d4:      	xorl	%eax, %eax
  5602d6:      	pushl	0x633b90
  5602dc:      	movl	$0x633b50, %ebp         # imm = 0x633B50
  5602e1:      	pushl	%ebp
  5602e2:      	movl	%eax, %ecx
  5602e4:      	movl	%eax, 0xc70140
  5602e9:      	calll	0x571b60 <.text+0x170b60>
  5602ee:      	pushl	$0x128                  # imm = 0x128
  5602f3:      	calll	0x5c6d12 <.text+0x1c5d12>
  5602f8:      	popl	%ecx
  5602f9:      	cmpl	%edi, %eax
  5602fb:      	je	0x56031b <.text+0x15f31b>
  5602fd:      	pushl	%edi
  5602fe:      	pushl	$0xd
  560300:      	pushl	$0x14
  560302:      	pushl	$0x136                  # imm = 0x136
  560307:      	pushl	$0x9c
  56030c:      	pushl	$0x5f062c               # imm = 0x5F062C
  560311:      	pushl	%ebx
  560312:      	movl	%eax, %ecx
  560314:      	calll	0x572841 <.text+0x171841>
  560319:      	jmp	0x56031d <.text+0x15f31d>
  56031b:      	xorl	%eax, %eax
  56031d:      	pushl	0x633b90
  560323:      	movl	%eax, %ecx
  560325:      	pushl	%ebp
  560326:      	movl	%eax, 0xc7013c
  56032b:      	calll	0x571b60 <.text+0x170b60>
  560330:      	pushl	$0x128                  # imm = 0x128
  560335:      	calll	0x5c6d12 <.text+0x1c5d12>
  56033a:      	popl	%ecx
  56033b:      	cmpl	%edi, %eax
  56033d:      	je	0x56035d <.text+0x15f35d>
  56033f:      	pushl	%edi
  560340:      	pushl	$0xd
  560342:      	pushl	$0x14
  560344:      	pushl	$0x136                  # imm = 0x136
  560349:      	pushl	$0xc3
  56034e:      	pushl	$0x5f0650               # imm = 0x5F0650
  560353:      	pushl	%ebx
  560354:      	movl	%eax, %ecx
  560356:      	calll	0x572841 <.text+0x171841>
  56035b:      	jmp	0x56035f <.text+0x15f35f>
  56035d:      	xorl	%eax, %eax
  56035f:      	pushl	0x633b90
  560365:      	movl	%eax, %ecx
  560367:      	pushl	%ebp
  560368:      	movl	%eax, 0xc70138
  56036d:      	calll	0x571b60 <.text+0x170b60>
  560372:      	pushl	$0x128                  # imm = 0x128
  560377:      	calll	0x5c6d12 <.text+0x1c5d12>
  56037c:      	popl	%ecx
  56037d:      	cmpl	%edi, %eax
  56037f:      	je	0x56039f <.text+0x15f39f>
  560381:      	pushl	%edi
  560382:      	pushl	$0xd
  560384:      	pushl	$0x14
  560386:      	pushl	$0x136                  # imm = 0x136
  56038b:      	pushl	$0x10d                  # imm = 0x10D
  560390:      	pushl	$0x5e6534               # imm = 0x5E6534
  560395:      	pushl	%ebx
  560396:      	movl	%eax, %ecx
  560398:      	calll	0x572841 <.text+0x171841>
  56039d:      	jmp	0x5603a1 <.text+0x15f3a1>
  56039f:      	xorl	%eax, %eax
  5603a1:      	pushl	0x633b90
  5603a7:      	movl	%eax, %ecx
  5603a9:      	pushl	%ebp
  5603aa:      	movl	%eax, 0xc70134
  5603af:      	calll	0x571b60 <.text+0x170b60>
  5603b4:      	pushl	$0x128                  # imm = 0x128
  5603b9:      	calll	0x5c6d12 <.text+0x1c5d12>
  5603be:      	popl	%ecx
  5603bf:      	cmpl	%edi, %eax
  5603c1:      	je	0x5603e1 <.text+0x15f3e1>
  5603c3:      	pushl	%edi
  5603c4:      	pushl	$0xd
  5603c6:      	pushl	$0x14
  5603c8:      	pushl	$0x136                  # imm = 0x136
  5603cd:      	pushl	$0x129                  # imm = 0x129
  5603d2:      	pushl	$0x5f0624               # imm = 0x5F0624
  5603d7:      	pushl	%ebx
  5603d8:      	movl	%eax, %ecx
  5603da:      	calll	0x572841 <.text+0x171841>
  5603df:      	jmp	0x5603e3 <.text+0x15f3e3>
  5603e1:      	xorl	%eax, %eax
  5603e3:      	pushl	0x633b90
  5603e9:      	movl	%eax, %ecx
  5603eb:      	pushl	%ebp
  5603ec:      	movl	%eax, 0xc70130
  5603f1:      	calll	0x571b60 <.text+0x170b60>
  5603f6:      	pushl	$0x1f438                # imm = 0x1F438
  5603fb:      	calll	0x5c6d12 <.text+0x1c5d12>
  560400:      	popl	%ecx
  560401:      	cmpl	%edi, %eax
  560403:      	je	0x560423 <.text+0x15f423>
  560405:      	pushl	%edi
  560406:      	pushl	$0x38
  560408:      	pushl	$0x115                  # imm = 0x115
  56040d:      	pushl	$0xa0
  560412:      	pushl	$0x21
  560414:      	pushl	$0x5df2cc               # imm = 0x5DF2CC
  560419:      	pushl	%ebx
  56041a:      	movl	%eax, %ecx
  56041c:      	calll	0x5729a2 <.text+0x1719a2>
  560421:      	jmp	0x560425 <.text+0x15f425>
  560423:      	xorl	%eax, %eax
  560425:      	pushl	0x633b94
  56042b:      	movl	%eax, %ecx
  56042d:      	pushl	%ebp
  56042e:      	movl	%eax, 0xc70108
  560433:      	calll	0x571bfe <.text+0x170bfe>
  560438:      	pushl	$0x1f438                # imm = 0x1F438
  56043d:      	calll	0x5c6d12 <.text+0x1c5d12>
  560442:      	popl	%ecx
  560443:      	cmpl	%edi, %eax
  560445:      	je	0x560462 <.text+0x15f462>
  560447:      	pushl	%edi
  560448:      	pushl	$0x76
  56044a:      	pushl	$0x69
  56044c:      	pushl	$0x3e
  56044e:      	pushl	$0x1ef                  # imm = 0x1EF
  560453:      	pushl	$0x5df2cc               # imm = 0x5DF2CC
  560458:      	pushl	%ebx
  560459:      	movl	%eax, %ecx
  56045b:      	calll	0x5729a2 <.text+0x1719a2>
  560460:      	jmp	0x560464 <.text+0x15f464>
  560462:      	xorl	%eax, %eax
  560464:      	pushl	0x633b94
  56046a:      	movl	%eax, %ecx
  56046c:      	pushl	%ebp
  56046d:      	movl	%eax, 0xc70104
  560472:      	calll	0x571bfe <.text+0x170bfe>
  560477:      	movl	0xc70140, %eax
  56047c:      	addl	$0x4, %eax
  56047f:      	pushl	%eax
  560480:      	pushl	$0x5e6524               # imm = 0x5E6524
  560485:      	movl	$0x5e5c9c, %edi         # imm = 0x5E5C9C
  56048a:      	pushl	%edi
  56048b:      	calll	0x4ba7c3 <.text+0xb97c3>
  560490:      	movl	0xc7013c, %eax
  560495:      	addl	$0x4, %eax
  560498:      	pushl	%eax
  560499:      	pushl	$0x5f061c               # imm = 0x5F061C
  56049e:      	pushl	%edi
  56049f:      	calll	0x4ba7c3 <.text+0xb97c3>
  5604a4:      	movl	0xc70138, %eax
  5604a9:      	addl	$0x4, %eax
  5604ac:      	pushl	%eax
  5604ad:      	movl	$0x5f0614, %ebp         # imm = 0x5F0614
  5604b2:      	pushl	%ebp
  5604b3:      	pushl	%edi
  5604b4:      	calll	0x4ba7c3 <.text+0xb97c3>
  5604b9:      	movl	0xc70134, %eax
  5604be:      	addl	$0x4, %eax
  5604c1:      	pushl	%eax
  5604c2:      	pushl	$0x5e6504               # imm = 0x5E6504
  5604c7:      	pushl	%esi
  5604c8:      	calll	0x4ba7c3 <.text+0xb97c3>
  5604cd:      	movl	0xc70130, %eax
  5604d2:      	addl	$0x4, %eax
  5604d5:      	pushl	%eax
  5604d6:      	pushl	$0x5e64fc               # imm = 0x5E64FC
  5604db:      	pushl	%edi
  5604dc:      	calll	0x4ba7c3 <.text+0xb97c3>
  5604e1:      	movl	0xc701e0, %eax
  5604e6:      	addl	$0x20, %eax
  5604e9:      	pushl	%eax
  5604ea:      	pushl	$0x5f060c               # imm = 0x5F060C
  5604ef:      	pushl	%edi
  5604f0:      	calll	0x4ba7c3 <.text+0xb97c3>
  5604f5:      	movl	0xc701dc, %eax
  5604fa:      	addl	$0x48, %esp
  5604fd:      	addl	$0x20, %eax
  560500:      	pushl	%eax
  560501:      	pushl	$0x5f0604               # imm = 0x5F0604
  560506:      	pushl	%edi
  560507:      	calll	0x4ba7c3 <.text+0xb97c3>
  56050c:      	movl	0xc701d8, %eax
  560511:      	addl	$0x20, %eax
  560514:      	pushl	%eax
  560515:      	pushl	$0x5f05fc               # imm = 0x5F05FC
  56051a:      	pushl	%edi
  56051b:      	calll	0x4ba7c3 <.text+0xb97c3>
  560520:      	movl	0xc701d4, %eax
  560525:      	addl	$0x20, %eax
  560528:      	pushl	%eax
  560529:      	pushl	$0x5f05f4               # imm = 0x5F05F4
  56052e:      	pushl	%edi
  56052f:      	calll	0x4ba7c3 <.text+0xb97c3>
  560534:      	movl	0xc701cc, %eax
  560539:      	addl	$0x20, %eax
  56053c:      	pushl	%eax
  56053d:      	pushl	$0x5f05ec               # imm = 0x5F05EC
  560542:      	pushl	%edi
  560543:      	calll	0x4ba7c3 <.text+0xb97c3>
  560548:      	movl	0xc701d0, %eax
  56054d:      	addl	$0x20, %eax
  560550:      	pushl	%eax
  560551:      	pushl	$0x5f05e4               # imm = 0x5F05E4
  560556:      	pushl	%edi
  560557:      	calll	0x4ba7c3 <.text+0xb97c3>
  56055c:      	movl	0xc70190, %eax
  560561:      	addl	$0x20, %eax
  560564:      	pushl	%eax
  560565:      	pushl	$0x5f05d4               # imm = 0x5F05D4
  56056a:      	pushl	%esi
  56056b:      	calll	0x4ba7c3 <.text+0xb97c3>
  560570:      	addl	$0x48, %esp
  560573:      	movl	0xc7018c, %eax
  560578:      	addl	$0x20, %eax
  56057b:      	pushl	%eax
  56057c:      	pushl	$0x5f05c8               # imm = 0x5F05C8
  560581:      	pushl	%esi
  560582:      	calll	0x4ba7c3 <.text+0xb97c3>
  560587:      	movl	0xc70188, %eax
  56058c:      	addl	$0x20, %eax
  56058f:      	pushl	%eax
  560590:      	pushl	$0x5f05bc               # imm = 0x5F05BC
  560595:      	pushl	%esi
  560596:      	calll	0x4ba7c3 <.text+0xb97c3>
  56059b:      	movl	0xc70174, %eax
  5605a0:      	addl	$0x20, %eax
  5605a3:      	pushl	%eax
  5605a4:      	pushl	$0x5f05b4               # imm = 0x5F05B4
  5605a9:      	pushl	%esi
  5605aa:      	calll	0x4ba7c3 <.text+0xb97c3>
  5605af:      	movl	0xc70124, %eax
  5605b4:      	addl	$0x4, %eax
  5605b7:      	pushl	%eax
  5605b8:      	pushl	$0x5f05ac               # imm = 0x5F05AC
  5605bd:      	pushl	%esi
  5605be:      	calll	0x4ba7c3 <.text+0xb97c3>
  5605c3:      	movl	0xc70120, %eax
  5605c8:      	addl	$0x4, %eax
  5605cb:      	pushl	%eax
  5605cc:      	pushl	$0x5f05a0               # imm = 0x5F05A0
  5605d1:      	pushl	%esi
  5605d2:      	calll	0x4ba7c3 <.text+0xb97c3>
  5605d7:      	movl	0xc70178, %eax
  5605dc:      	addl	$0x20, %eax
  5605df:      	pushl	%eax
  5605e0:      	pushl	$0x5cf148               # imm = 0x5CF148
  5605e5:      	pushl	%esi
  5605e6:      	calll	0x4ba7c3 <.text+0xb97c3>
  5605eb:      	movl	0xc70118, %eax
  5605f0:      	addl	$0x48, %esp
  5605f3:      	addl	$0x4, %eax
  5605f6:      	pushl	%eax
  5605f7:      	pushl	%ebp
  5605f8:      	pushl	%esi
  5605f9:      	calll	0x4ba7c3 <.text+0xb97c3>
  5605fe:      	movl	0xc70114, %eax
  560603:      	addl	$0x4, %eax
  560606:      	pushl	%eax
  560607:      	pushl	$0x5f0594               # imm = 0x5F0594
  56060c:      	pushl	%esi
  56060d:      	calll	0x4ba7c3 <.text+0xb97c3>
  560612:      	movl	0xc7011c, %eax
  560617:      	addl	$0x4, %eax
  56061a:      	pushl	%eax
  56061b:      	pushl	$0x5f058c               # imm = 0x5F058C
  560620:      	pushl	%edi
  560621:      	calll	0x4ba7c3 <.text+0xb97c3>
  560626:      	movl	0xc7010c, %eax
  56062b:      	addl	$0x4, %eax
  56062e:      	pushl	%eax
  56062f:      	pushl	$0x5f0584               # imm = 0x5F0584
  560634:      	pushl	%edi
  560635:      	calll	0x4ba7c3 <.text+0xb97c3>
  56063a:      	movl	0xc701c4, %eax
  56063f:      	addl	$0x20, %eax
  560642:      	pushl	%eax
  560643:      	pushl	$0x5f0578               # imm = 0x5F0578
  560648:      	pushl	%esi
  560649:      	calll	0x4ba7c3 <.text+0xb97c3>
  56064e:      	movl	0xc701c8, %eax
  560653:      	addl	$0x20, %eax
  560656:      	pushl	%eax
  560657:      	pushl	$0x5f056c               # imm = 0x5F056C
  56065c:      	pushl	%esi
  56065d:      	calll	0x4ba7c3 <.text+0xb97c3>
  560662:      	movl	0xc701c0, %eax
  560667:      	addl	$0x48, %esp
  56066a:      	addl	$0x20, %eax
  56066d:      	pushl	%eax
  56066e:      	pushl	$0x5dd500               # imm = 0x5DD500
  560673:      	pushl	%esi
  560674:      	calll	0x4ba7c3 <.text+0xb97c3>
  560679:      	movl	0xc701bc, %eax
  56067e:      	addl	$0x20, %eax
  560681:      	pushl	%eax
  560682:      	pushl	$0x5ecda4               # imm = 0x5ECDA4
  560687:      	pushl	%esi
  560688:      	calll	0x4ba7c3 <.text+0xb97c3>
  56068d:      	movl	0xc70180, %eax
  560692:      	addl	$0x20, %eax
  560695:      	pushl	%eax
  560696:      	pushl	$0x5ef430               # imm = 0x5EF430
  56069b:      	pushl	%esi
  56069c:      	calll	0x4ba7c3 <.text+0xb97c3>
  5606a1:      	movl	0xc7017c, %eax
  5606a6:      	addl	$0x20, %eax
  5606a9:      	pushl	%eax
  5606aa:      	pushl	$0x5f0564               # imm = 0x5F0564
  5606af:      	pushl	%esi
  5606b0:      	calll	0x4ba7c3 <.text+0xb97c3>
  5606b5:      	movl	0xc70198, %eax
  5606ba:      	addl	$0x20, %eax
  5606bd:      	pushl	%eax
  5606be:      	pushl	$0x5f055c               # imm = 0x5F055C
  5606c3:      	pushl	%esi
  5606c4:      	calll	0x4ba7c3 <.text+0xb97c3>
  5606c9:      	movl	0xc70194, %eax
  5606ce:      	addl	$0x20, %eax
  5606d1:      	pushl	%eax
  5606d2:      	pushl	$0x5ef4c4               # imm = 0x5EF4C4
  5606d7:      	pushl	$0x5ef4d4               # imm = 0x5EF4D4
  5606dc:      	calll	0x4ba7c3 <.text+0xb97c3>
  5606e1:      	movl	0xc70114, %eax
  5606e6:      	addl	$0x48, %esp
  5606e9:      	addl	$0x4, %eax
  5606ec:      	pushl	%eax
  5606ed:      	pushl	$0x5f0550               # imm = 0x5F0550
  5606f2:      	pushl	$0x5f0544               # imm = 0x5F0544
  5606f7:      	calll	0x4ba7c3 <.text+0xb97c3>
  5606fc:      	pushl	$0x633c18               # imm = 0x633C18
  560701:      	pushl	$0x5f0534               # imm = 0x5F0534
  560706:      	pushl	$0x5e5b64               # imm = 0x5E5B64
  56070b:      	calll	0x4ba7c3 <.text+0xb97c3>
  560710:      	movl	0x5ce53c, %ebp
  560716:      	addl	$0x18, %esp
  560719:      	pushl	$0x1
  56071b:      	pushl	$0x5a
  56071d:      	pushl	$0x91
  560722:      	pushl	$0x3f
  560724:      	pushl	$0x21
  560726:      	pushl	$0x7e5                  # imm = 0x7E5
  56072b:      	pushl	%ebx
  56072c:      	calll	*%ebp
  56072e:      	movl	0x5ce548, %esi
  560734:      	pushl	%eax
  560735:      	calll	*%esi
  560737:      	pushl	$0x1
  560739:      	pushl	$0x4c
  56073b:      	pushl	$0x121                  # imm = 0x121
  560740:      	pushl	$0x147                  # imm = 0x147
  560745:      	pushl	$0x20
  560747:      	pushl	$0x822                  # imm = 0x822
  56074c:      	pushl	%ebx
  56074d:      	calll	*%ebp
  56074f:      	pushl	%eax
  560750:      	calll	*%esi
  560752:      	pushl	$0x1
  560754:      	pushl	$0x10
  560756:      	pushl	$0x105                  # imm = 0x105
  56075b:      	pushl	$0x1a6                  # imm = 0x1A6
  560760:      	pushl	$0x154                  # imm = 0x154
  560765:      	movl	$0x825, %edi            # imm = 0x825
  56076a:      	pushl	%edi
  56076b:      	pushl	%ebx
  56076c:      	calll	*%ebp
  56076e:      	pushl	%eax
  56076f:      	calll	*%esi
  560771:      	pushl	$0x0
  560773:      	pushl	$0xf1
  560778:      	pushl	$0xc5
  56077d:      	pushl	%edi
  56077e:      	pushl	%ebx
  56077f:      	calll	*0x5ce52c
  560785:      	pushl	$0x1
  560787:      	pushl	$0x62
  560789:      	pushl	$0xfa
  56078e:      	pushl	$0x135                  # imm = 0x135
  560793:      	pushl	$0x14c                  # imm = 0x14C
  560798:      	pushl	$0x826                  # imm = 0x826
  56079d:      	pushl	%ebx
  56079e:      	calll	*%ebp
  5607a0:      	pushl	%eax
  5607a1:      	calll	*%esi
  5607a3:      	pushl	$0x1
  5607a5:      	pushl	$0xf
  5607a7:      	pushl	$0x1c
  5607a9:      	pushl	$0xd6
  5607ae:      	pushl	$0x1b2                  # imm = 0x1B2
  5607b3:      	pushl	$0x828                  # imm = 0x828
  5607b8:      	pushl	%ebx
  5607b9:      	calll	*%ebp
  5607bb:      	pushl	%eax
  5607bc:      	calll	*%esi
  5607be:      	pushl	$0x1
  5607c0:      	pushl	$0xf
  5607c2:      	pushl	$0x1c
  5607c4:      	pushl	$0xee
  5607c9:      	pushl	$0x23e                  # imm = 0x23E
  5607ce:      	addl	$0x4, %edi
  5607d1:      	pushl	%edi
  5607d2:      	pushl	%ebx
  5607d3:      	calll	*%ebp
  5607d5:      	pushl	%eax
  5607d6:      	calll	*%esi
  5607d8:      	pushl	$0x1
  5607da:      	pushl	$0xf
  5607dc:      	pushl	$0x1c
  5607de:      	pushl	$0x103                  # imm = 0x103
  5607e3:      	pushl	$0x23e                  # imm = 0x23E
  5607e8:      	pushl	$0x82a                  # imm = 0x82A
  5607ed:      	pushl	%ebx
  5607ee:      	calll	*%ebp
  5607f0:      	pushl	%eax
  5607f1:      	calll	*%esi
  5607f3:      	pushl	$0x1
  5607f5:      	pushl	$0xf
  5607f7:      	pushl	$0x1c
  5607f9:      	pushl	$0xee
  5607fe:      	pushl	$0x1b2                  # imm = 0x1B2
  560803:      	pushl	$0x82b                  # imm = 0x82B
  560808:      	pushl	%ebx
  560809:      	calll	*%ebp
  56080b:      	pushl	%eax
  56080c:      	calll	*%esi
  56080e:      	pushl	$0x1
  560810:      	pushl	$0xf
  560812:      	pushl	$0x1c
  560814:      	pushl	$0x103                  # imm = 0x103
  560819:      	pushl	$0x97
  56081e:      	pushl	$0x82c                  # imm = 0x82C
  560823:      	pushl	%ebx
  560824:      	calll	*%ebp
  560826:      	pushl	%eax
  560827:      	calll	*%esi
  560829:      	orl	$-0x1, 0xc700b8
  560830:      	andl	$0x0, 0xc700b4
  560837:      	xorl	%esi, %esi
  560839:      	cmpb	$0x0, 0xc6f4b4
  560840:      	jne	0x5609de <.text+0x15f9de>
  560846:      	pushl	%esi
  560847:      	pushl	$0x7e5                  # imm = 0x7E5
  56084c:      	pushl	%ebx
  56084d:      	calll	*%ebp
  56084f:      	pushl	%eax
  560850:      	calll	*0x5ce614
  560856:      	pushl	$0x128                  # imm = 0x128
  56085b:      	calll	0x5c6d12 <.text+0x1c5d12>
  560860:      	popl	%ecx
  560861:      	cmpl	%esi, %eax
  560863:      	je	0x560880 <.text+0x15f880>
  560865:      	pushl	%esi
  560866:      	pushl	$0x5a
  560868:      	pushl	$0x91
  56086d:      	pushl	$0x3f
  56086f:      	pushl	$0x21
  560871:      	pushl	$0x5f052c               # imm = 0x5F052C
  560876:      	pushl	%ebx
  560877:      	movl	%eax, %ecx
  560879:      	calll	0x572841 <.text+0x171841>
  56087e:      	jmp	0x560882 <.text+0x15f882>
  560880:      	xorl	%eax, %eax
  560882:      	movl	%eax, 0xc700fc
  560887:      	addl	$0x4, %eax
  56088a:      	pushl	%eax
  56088b:      	pushl	$0x5ced84               # imm = 0x5CED84
  560890:      	pushl	$0x5e5b64               # imm = 0x5E5B64
  560895:      	calll	0x4ba7c3 <.text+0xb97c3>
  56089a:      	movl	0xc701c4, %ecx
  5608a0:      	addl	$0xc, %esp
  5608a3:      	calll	0x56f4c1 <.text+0x16e4c1>
  5608a8:      	movl	0xc701c8, %ecx
  5608ae:      	calll	0x56f4c1 <.text+0x16e4c1>
  5608b3:      	movl	0xc701c0, %ecx
  5608b9:      	calll	0x56f4c1 <.text+0x16e4c1>
  5608be:      	movl	0xc701bc, %ecx
  5608c4:      	calll	0x56f4c1 <.text+0x16e4c1>
  5608c9:      	movl	0xc70190, %ecx
  5608cf:      	calll	0x56f4c1 <.text+0x16e4c1>
  5608d4:      	movl	0xc7018c, %ecx
  5608da:      	calll	0x56f4c1 <.text+0x16e4c1>
  5608df:      	movl	0xc70188, %ecx
  5608e5:      	calll	0x56f4c1 <.text+0x16e4c1>
  5608ea:      	movl	0xc70174, %ecx
  5608f0:      	calll	0x56f4c1 <.text+0x16e4c1>
  5608f5:      	movl	0xc70180, %ecx
  5608fb:      	calll	0x56f4c1 <.text+0x16e4c1>
  560900:      	movl	0xc7017c, %ecx
  560906:      	calll	0x56f4c1 <.text+0x16e4c1>
  56090b:      	movl	0xc701d0, %ecx
  560911:      	pushl	%esi
  560912:      	calll	0x56f435 <.text+0x16e435>
  560917:      	movl	0xc70170, %ecx
  56091d:      	pushl	%esi
  56091e:      	calll	0x56f435 <.text+0x16e435>
  560923:      	movl	0xc701b8, %ecx
  560929:      	pushl	%esi
  56092a:      	calll	0x56f435 <.text+0x16e435>
  56092f:      	movl	0xc701b4, %ecx
  560935:      	pushl	%esi
  560936:      	calll	0x56f435 <.text+0x16e435>
  56093b:      	pushl	%esi
  56093c:      	pushl	$0x82b                  # imm = 0x82B
  560941:      	pushl	%ebx
  560942:      	calll	*%ebp
  560944:      	pushl	%eax
  560945:      	calll	*0x5ce530
  56094b:      	pushl	%esi
  56094c:      	pushl	$0x828                  # imm = 0x828
  560951:      	pushl	%ebx
  560952:      	calll	*%ebp
  560954:      	pushl	%eax
  560955:      	calll	*0x5ce530
  56095b:      	pushl	%esi
  56095c:      	pushl	%edi
  56095d:      	pushl	%ebx
  56095e:      	calll	*%ebp
  560960:      	movl	0x5ce530, %edi
  560966:      	pushl	%eax
  560967:      	calll	*%edi
  560969:      	pushl	%esi
  56096a:      	pushl	$0x82a                  # imm = 0x82A
  56096f:      	pushl	%ebx
  560970:      	calll	*%ebp
  560972:      	pushl	%eax
  560973:      	calll	*%edi
  560975:      	cmpl	%esi, 0xa0f254
  56097b:      	jne	0x5609de <.text+0x15f9de>
  56097d:      	movl	$0x5f051c, %esi         # imm = 0x5F051C
  560982:      	leal	0x58(%esp), %edi
  560986:      	movsl	(%esi), %es:(%edi)
  560987:      	movsl	(%esi), %es:(%edi)
  560988:      	movsl	(%esi), %es:(%edi)
  560989:      	pushl	$0xf0
  56098e:      	leal	0x6c(%esp), %eax
  560992:      	pushl	$0x0
  560994:      	pushl	%eax
  560995:      	movsl	(%esi), %es:(%edi)
  560996:      	calll	0x5c6dfc <.text+0x1c5dfc>
  56099b:      	leal	0x64(%esp), %eax
  56099f:      	pushl	%eax
  5609a0:      	pushl	$0x5f050c               # imm = 0x5F050C
  5609a5:      	pushl	$0x5e5b64               # imm = 0x5E5B64
  5609aa:      	calll	0x4ba7c3 <.text+0xb97c3>
  5609af:      	addl	$0x18, %esp
  5609b2:      	leal	0x58(%esp), %eax
  5609b6:      	pushl	%eax
  5609b7:      	pushl	0x633bb4
  5609bd:      	movl	$0xc6f4a0, %ecx         # imm = 0xC6F4A0
  5609c2:      	calll	0x55041d <.text+0x14f41d>
  5609c7:      	pushl	0xc701e8
  5609cd:      	movb	$0x1, 0xc6f4b6
  5609d4:      	pushl	%ebx
  5609d5:      	calll	0x570cce <.text+0x16fcce>
  5609da:      	popl	%ecx
  5609db:      	popl	%ecx
  5609dc:      	xorl	%esi, %esi
  5609de:      	pushl	$0x94
  5609e3:      	calll	0x5c6d12 <.text+0x1c5d12>
  5609e8:      	movl	%eax, %edi
  5609ea:      	popl	%ecx
  5609eb:      	cmpl	%esi, %edi
  5609ed:      	je	0x560a07 <.text+0x15fa07>
  5609ef:      	pushl	$0x822                  # imm = 0x822
  5609f4:      	pushl	%ebx
  5609f5:      	calll	*%ebp
  5609f7:      	pushl	%eax
  5609f8:      	pushl	%ebx
  5609f9:      	movl	%edi, %ecx
  5609fb:      	calll	0x551c69 <.text+0x150c69>
  560a00:      	movl	%eax, 0xc701e4
  560a05:      	jmp	0x560a0d <.text+0x15fa0d>
  560a07:      	movl	%esi, 0xc701e4
  560a0d:      	pushl	0xc70104
  560a13:      	movl	0xc700f4, %ecx
  560a19:      	pushl	0xc70110
  560a1f:      	calll	0x55665a <.text+0x15565a>
  560a24:      	cmpb	$0x0, 0xba76e2
  560a2b:      	je	0x560a40 <.text+0x15fa40>
  560a2d:      	movl	$0x5ef600, %edi         # imm = 0x5EF600
  560a32:      	pushl	%edi
  560a33:      	calll	0x4839c7 <.text+0x829c7>
  560a38:      	popl	%ecx
  560a39:      	testl	%eax, %eax
  560a3b:      	je	0x560a40 <.text+0x15fa40>
  560a3d:      	pushl	%edi
  560a3e:      	jmp	0x560a45 <.text+0x15fa45>
  560a40:      	pushl	$0x5ef5f4               # imm = 0x5EF5F4
  560a45:      	movl	0xc700f4, %ecx
  560a4b:      	calll	0x55684f <.text+0x15584f>
  560a50:      	pushl	0xc70128
  560a56:      	pushl	0xc70160
  560a5c:      	pushl	0xc70104
  560a62:      	pushl	0xc700f4
  560a68:      	pushl	0xc70110
  560a6e:      	pushl	$0x82b                  # imm = 0x82B
  560a73:      	pushl	%ebx
  560a74:      	calll	*%ebp
  560a76:      	pushl	%eax
  560a77:      	pushl	0xc70108
  560a7d:      	pushl	$0x7e5                  # imm = 0x7E5
  560a82:      	pushl	%ebx
  560a83:      	calll	*%ebp
  560a85:      	movl	0xc701e4, %ecx
  560a8b:      	pushl	%eax
  560a8c:      	calll	0x55b984 <.text+0x15a984>
  560a91:      	cmpb	$0x0, 0xc6f4b4
  560a98:      	je	0x560ab6 <.text+0x15fab6>
  560a9a:      	pushl	0xc6fdac
  560aa0:      	movl	0xc701e4, %ecx
  560aa6:      	calll	0x551e24 <.text+0x150e24>
  560aab:      	movl	0xc701e4, %ecx
  560ab1:      	calll	0x5598ef <.text+0x1588ef>
  560ab6:      	movl	0xc701e4, %ecx
  560abc:      	pushl	0x88(%ecx)
  560ac2:      	calll	0x5520a2 <.text+0x1510a2>
  560ac7:      	movl	0xc701dc, %ecx
  560acd:      	pushl	%esi
  560ace:      	testl	%eax, %eax
  560ad0:      	je	0x560ad9 <.text+0x15fad9>
  560ad2:      	calll	0x573f6e <.text+0x172f6e>
  560ad7:      	jmp	0x560ade <.text+0x15fade>
  560ad9:      	calll	0x56f435 <.text+0x16e435>
  560ade:      	movl	0xc701e4, %ecx
  560ae4:      	calll	0x551d18 <.text+0x150d18>
  560ae9:      	subl	%esi, %eax
  560aeb:      	je	0x560b87 <.text+0x15fb87>
  560af1:      	decl	%eax
  560af2:      	jne	0x560c17 <.text+0x15fc17>
  560af8:      	movl	0xc7018c, %ecx
  560afe:      	pushl	%esi
  560aff:      	calll	0x56f435 <.text+0x16e435>
  560b04:      	movl	0xc7015c, %ecx
  560b0a:      	pushl	%esi
  560b0b:      	calll	0x57403d <.text+0x17303d>
  560b10:      	movl	0xc70188, %ecx
  560b16:      	pushl	%esi
  560b17:      	calll	0x56f435 <.text+0x16e435>
  560b1c:      	movl	0xc70158, %ecx
  560b22:      	pushl	%esi
  560b23:      	calll	0x57403d <.text+0x17303d>
  560b28:      	movl	0xc701bc, %ecx
  560b2e:      	pushl	%esi
  560b2f:      	calll	0x573f6e <.text+0x172f6e>
  560b34:      	movl	0xc70164, %ecx
  560b3a:      	pushl	%esi
  560b3b:      	calll	0x574011 <.text+0x173011>
  560b40:      	movl	0xc701c8, %ecx
  560b46:      	pushl	%esi
  560b47:      	calll	0x573f6e <.text+0x172f6e>
  560b4c:      	movl	0xc7016c, %ecx
  560b52:      	pushl	%esi
  560b53:      	calll	0x574011 <.text+0x173011>
  560b58:      	movl	0xc701c0, %ecx
  560b5e:      	pushl	%esi
  560b5f:      	calll	0x573f6e <.text+0x172f6e>
  560b64:      	movl	0xc70168, %ecx
  560b6a:      	pushl	%esi
  560b6b:      	calll	0x574011 <.text+0x173011>
  560b70:      	movl	0xc70180, %ecx
  560b76:      	pushl	%esi
  560b77:      	calll	0x573f6e <.text+0x172f6e>
  560b7c:      	movl	0xc70150, %ecx
  560b82:      	jmp	0x560c11 <.text+0x15fc11>
  560b87:      	movl	0xc701c8, %ecx
  560b8d:      	pushl	%esi
  560b8e:      	calll	0x56f435 <.text+0x16e435>
  560b93:      	movl	0xc7016c, %ecx
  560b99:      	pushl	%esi
  560b9a:      	calll	0x57403d <.text+0x17303d>
  560b9f:      	movl	0xc701c0, %ecx
  560ba5:      	pushl	%esi
  560ba6:      	calll	0x56f435 <.text+0x16e435>
  560bab:      	movl	0xc70168, %ecx
  560bb1:      	pushl	%esi
  560bb2:      	calll	0x57403d <.text+0x17303d>
  560bb7:      	movl	0xc701bc, %ecx
  560bbd:      	pushl	%esi
  560bbe:      	calll	0x56f435 <.text+0x16e435>
  560bc3:      	movl	0xc70164, %ecx
  560bc9:      	pushl	%esi
  560bca:      	calll	0x57403d <.text+0x17303d>
  560bcf:      	movl	0xc70180, %ecx
  560bd5:      	pushl	%esi
  560bd6:      	calll	0x56f435 <.text+0x16e435>
  560bdb:      	movl	0xc70150, %ecx
  560be1:      	pushl	%esi
  560be2:      	calll	0x57403d <.text+0x17303d>
  560be7:      	movl	0xc7018c, %ecx
  560bed:      	pushl	%esi
  560bee:      	calll	0x573f6e <.text+0x172f6e>
  560bf3:      	movl	0xc7015c, %ecx
  560bf9:      	pushl	%esi
  560bfa:      	calll	0x574011 <.text+0x173011>
  560bff:      	movl	0xc70188, %ecx
  560c05:      	pushl	%esi
  560c06:      	calll	0x573f6e <.text+0x172f6e>
  560c0b:      	movl	0xc70158, %ecx
  560c11:      	pushl	%esi
  560c12:      	calll	0x574011 <.text+0x173011>
  560c17:      	movl	0xc70110, %ecx
  560c1d:      	pushl	%esi
  560c1e:      	pushl	%esi
  560c1f:      	calll	0x571bcc <.text+0x170bcc>
  560c24:      	movl	0xc70104, %ecx
  560c2a:      	movl	(%ecx), %eax
  560c2c:      	pushl	%esi
  560c2d:      	calll	*0x4(%eax)
  560c30:      	movl	$0xc8, %eax
  560c35:      	movl	%eax, 0x44(%esp)
  560c39:      	movl	%eax, 0x48(%esp)
  560c3d:      	pushl	%esi
  560c3e:      	leal	0x40(%esp), %eax
  560c42:      	pushl	%eax
  560c43:      	pushl	%ebx
  560c44:      	movl	%esi, 0x48(%esp)
  560c48:      	movl	%esi, 0x4c(%esp)
  560c4c:      	calll	*0x5ce550
  560c52:      	pushl	$0x826                  # imm = 0x826
  560c57:      	pushl	%ebx
  560c58:      	calll	*%ebp
  560c5a:      	movl	$0xc6f4a0, %edi         # imm = 0xC6F4A0
  560c5f:      	pushl	%eax
  560c60:      	movl	%edi, %ecx
  560c62:      	calll	0x5503a3 <.text+0x14f3a3>
  560c67:      	pushl	$0x633c18               # imm = 0x633C18
  560c6c:      	pushl	%edi
  560c6d:      	calll	0x555cce <.text+0x154cce>
  560c72:      	popl	%ecx
  560c73:      	popl	%ecx
  560c74:      	movl	$0xc6fef8, %edi         # imm = 0xC6FEF8
  560c79:      	movl	%edi, %ecx
  560c7b:      	calll	0x55b669 <.text+0x15a669>
  560c80:      	pushl	%esi
  560c81:      	pushl	$0x5598e5               # imm = 0x5598E5
  560c86:      	pushl	$0xc6f4a0               # imm = 0xC6F4A0
  560c8b:      	pushl	$0x825                  # imm = 0x825
  560c90:      	pushl	%ebx
  560c91:      	calll	*%ebp
  560c93:      	pushl	%eax
  560c94:      	pushl	0xba7724
  560c9a:      	pushl	$0x822                  # imm = 0x822
  560c9f:      	pushl	%ebx
  560ca0:      	calll	*%ebp
  560ca2:      	pushl	%eax
  560ca3:      	movl	%edi, %ecx
  560ca5:      	calll	0x550cce <.text+0x14fcce>
  560caa:      	movl	%edi, %ecx
  560cac:      	calll	0x55cfa0 <.text+0x15bfa0>
  560cb1:      	pushl	$0x6
  560cb3:      	popl	%ecx
  560cb4:      	pushl	%esi
  560cb5:      	pushl	$0x64
  560cb7:      	pushl	$0x1
  560cb9:      	xorl	%eax, %eax
  560cbb:      	movl	$0xc7009c, %edi         # imm = 0xC7009C
  560cc0:      	pushl	%ebx
  560cc1:      	rep		stosl	%eax, %es:(%edi)
  560cc3:      	calll	*0x5ce534
  560cc9:      	movl	%eax, 0xc700f8
  560cce:      	jmp	0x560d63 <.text+0x15fd63>
  560cd3:      	movl	$0x10, 0x10(%esi)
  560cda:      	jmp	0x560d63 <.text+0x15fd63>
  560cdf:      	movl	0xc700f8, %eax
  560ce4:      	xorl	%edi, %edi
  560ce6:      	cmpl	%edi, %eax
  560ce8:      	je	0x560cf8 <.text+0x15fcf8>
  560cea:      	pushl	%eax
  560ceb:      	pushl	%ebx
  560cec:      	calll	*0x5ce538
  560cf2:      	movl	%edi, 0xc700f8
  560cf8:      	movl	0x5ce530, %esi
  560cfe:      	pushl	%edi
  560cff:      	pushl	%ebx
  560d00:      	calll	*%esi
  560d02:      	cmpb	$0x0, 0xc6f4b6
  560d09:      	jne	0x560d14 <.text+0x15fd14>
  560d0b:      	cmpb	$0x0, 0xc6f4b5
  560d12:      	je	0x560d29 <.text+0x15fd29>
  560d14:      	pushl	$0x5f0508               # imm = 0x5F0508
  560d19:      	pushl	0x633bb4
  560d1f:      	movl	$0xc6f4a0, %ecx         # imm = 0xC6F4A0
  560d24:      	calll	0x55041d <.text+0x14f41d>
  560d29:      	movl	$0xc6fef8, %ebp         # imm = 0xC6FEF8
  560d2e:      	movl	%ebp, %ecx
  560d30:      	calll	0x55cfa0 <.text+0x15bfa0>
  560d35:      	movl	%ebp, %ecx
  560d37:      	calll	0x55985e <.text+0x15885e>
  560d3c:      	cmpb	$0x0, 0xc6fd96
  560d43:      	je	0x560d6b <.text+0x15fd6b>
  560d45:      	cmpl	%edi, 0xc700c4
  560d4b:      	je	0x560d52 <.text+0x15fd52>
  560d4d:      	pushl	$0x1
  560d4f:      	pushl	%ebx
  560d50:      	calll	*%esi
  560d52:      	pushl	%edi
  560d53:      	pushl	%ebx
  560d54:      	calll	0x56e64a <.text+0x16d64a>
  560d59:      	pushl	$0x1
  560d5b:      	calll	0x571075 <.text+0x170075>
  560d60:      	addl	$0xc, %esp
  560d63:      	xorl	%eax, %eax
  560d65:      	incl	%eax
  560d66:      	jmp	0x56301e <.text+0x16201e>
  560d6b:      	cmpb	$0x0, 0xc6fca7
  560d72:      	je	0x560dc6 <.text+0x15fdc6>
  560d74:      	pushl	$0x5
  560d76:      	popl	%ecx
  560d77:      	pushl	$0xec
  560d7c:      	leal	0x70(%esp), %eax
  560d80:      	pushl	$0x0
  560d82:      	movl	$0x5f04f4, %esi         # imm = 0x5F04F4
  560d87:      	leal	0x60(%esp), %edi
  560d8b:      	pushl	%eax
  560d8c:      	rep		movsl	(%esi), %es:(%edi)
  560d8e:      	calll	0x5c6dfc <.text+0x1c5dfc>
  560d93:      	leal	0x64(%esp), %eax
  560d97:      	pushl	%eax
  560d98:      	pushl	$0x5f04ec               # imm = 0x5F04EC
  560d9d:      	pushl	$0x5ef520               # imm = 0x5EF520
  560da2:      	calll	0x4ba7c3 <.text+0xb97c3>
  560da7:      	leal	0x70(%esp), %eax
  560dab:      	pushl	%eax
  560dac:      	pushl	%ebx
  560dad:      	calll	0x553e75 <.text+0x152e75>
  560db2:      	pushl	$0x0
  560db4:      	pushl	%ebx
  560db5:      	calll	0x56e64a <.text+0x16d64a>
  560dba:      	pushl	$0x1
  560dbc:      	calll	0x571075 <.text+0x170075>
  560dc1:      	addl	$0x2c, %esp
  560dc4:      	jmp	0x560d63 <.text+0x15fd63>
  560dc6:      	cmpb	$0x0, 0xc6fd94
  560dcd:      	je	0x560dfc <.text+0x15fdfc>
  560dcf:      	pushl	$0x8
  560dd1:      	popl	%ecx
  560dd2:      	movl	$0x5f04c8, %esi         # imm = 0x5F04C8
  560dd7:      	leal	0x58(%esp), %edi
  560ddb:      	rep		movsl	(%esi), %es:(%edi)
  560ddd:      	pushl	$0xde
  560de2:      	leal	0x7e(%esp), %eax
  560de6:      	pushl	$0x0
  560de8:      	pushl	%eax
  560de9:      	movsw	(%esi), %es:(%edi)
  560deb:      	calll	0x5c6dfc <.text+0x1c5dfc>
  560df0:      	leal	0x64(%esp), %eax
  560df4:      	pushl	%eax
  560df5:      	pushl	$0x5f04b8               # imm = 0x5F04B8
  560dfa:      	jmp	0x560d9d <.text+0x15fd9d>
  560dfc:      	cmpb	$0x0, 0xc6fd95
  560e03:      	je	0x560e5d <.text+0x15fe5d>
  560e05:      	calll	0x4dd321 <.text+0xdc321>
  560e0a:      	pushl	$0x5
  560e0c:      	popl	%ecx
  560e0d:      	movl	$0x5f04a0, %esi         # imm = 0x5F04A0
  560e12:      	leal	0x58(%esp), %edi
  560e16:      	rep		movsl	(%esi), %es:(%edi)
  560e18:      	movsw	(%esi), %es:(%edi)
  560e1a:      	movsb	(%esi), %es:(%edi)
  560e1b:      	pushl	$0xe9
  560e20:      	xorl	%esi, %esi
  560e22:      	leal	0x73(%esp), %eax
  560e26:      	pushl	%esi
  560e27:      	pushl	%eax
  560e28:      	calll	0x5c6dfc <.text+0x1c5dfc>
  560e2d:      	leal	0x64(%esp), %eax
  560e31:      	pushl	%eax
  560e32:      	pushl	$0x5f048c               # imm = 0x5F048C
  560e37:      	pushl	$0x5ef520               # imm = 0x5EF520
  560e3c:      	calll	0x4ba7c3 <.text+0xb97c3>
  560e41:      	leal	0x70(%esp), %eax
  560e45:      	pushl	%eax
  560e46:      	pushl	%ebx
  560e47:      	calll	0x553e75 <.text+0x152e75>
  560e4c:      	addl	$0x20, %esp
  560e4f:      	pushl	%esi
  560e50:      	pushl	%ebx
  560e51:      	calll	*0x5ce530
  560e57:      	pushl	%esi
  560e58:      	jmp	0x560d53 <.text+0x15fd53>
  560e5d:      	movw	0x62aea4, %ax
  560e63:      	movl	$0xfa01, %ecx           # imm = 0xFA01
  560e68:      	movl	$0x5ef600, %edi         # imm = 0x5EF600
  560e6d:      	cmpw	%ax, %cx
  560e70:      	je	0x5610fa <.text+0x1600fa>
  560e76:      	movzwl	%ax, %eax
  560e79:      	pushl	%eax
  560e7a:      	movl	%ebp, %ecx
  560e7c:      	calll	0x558c66 <.text+0x157c66>
  560e81:      	testb	%al, %al
  560e83:      	je	0x5610fa <.text+0x1600fa>
  560e89:      	movl	0xc7015c, %ecx
  560e8f:      	calll	0x56f59e <.text+0x16e59e>
  560e94:      	movl	0xc70158, %ecx
  560e9a:      	movl	%eax, 0xba72d4
  560e9f:      	calll	0x56f59e <.text+0x16e59e>
  560ea4:      	movl	0xc70154, %ecx
  560eaa:      	movl	%eax, 0xba76d8
  560eaf:      	calll	0x56f59e <.text+0x16e59e>
  560eb4:      	movl	0xc70150, %ecx
  560eba:      	movl	%eax, 0xba76dc
  560ebf:      	calll	0x56f59e <.text+0x16e59e>
  560ec4:      	movl	0xc70150, %ecx
  560eca:      	movl	%eax, 0x62a990
  560ecf:      	calll	0x56f59e <.text+0x16e59e>
  560ed4:      	movl	0xc7014c, %ecx
  560eda:      	movl	%eax, 0xba72a0
  560edf:      	calll	0x56f59e <.text+0x16e59e>
  560ee4:      	movl	0xc70148, %ecx
  560eea:      	testl	%eax, %eax
  560eec:      	setne	%al
  560eef:      	movb	%al, 0xba76e0
  560ef4:      	calll	0x56f59e <.text+0x16e59e>
  560ef9:      	testl	%eax, %eax
  560efb:      	setne	%al
  560efe:      	cmpb	%al, 0xba76e2
  560f04:      	je	0x560f60 <.text+0x15ff60>
  560f06:      	movl	0xc70148, %ecx
  560f0c:      	calll	0x56f59e <.text+0x16e59e>
  560f11:      	testl	%eax, %eax
  560f13:      	setne	%al
  560f16:      	movb	%al, 0xba76e2
  560f1b:      	testb	%al, %al
  560f1d:      	je	0x560f2d <.text+0x15ff2d>
  560f1f:      	pushl	%edi
  560f20:      	calll	0x4839c7 <.text+0x829c7>
  560f25:      	popl	%ecx
  560f26:      	testl	%eax, %eax
  560f28:      	je	0x560f2d <.text+0x15ff2d>
  560f2a:      	pushl	%edi
  560f2b:      	jmp	0x560f32 <.text+0x15ff32>
  560f2d:      	pushl	$0x5ef5f4               # imm = 0x5EF5F4
  560f32:      	movl	0xc700f4, %ecx
  560f38:      	calll	0x55684f <.text+0x15584f>
  560f3d:      	pushl	0xba7724
  560f43:      	calll	0x550103 <.text+0x14f103>
  560f48:      	popl	%ecx
  560f49:      	movl	0xc700f4, %ecx
  560f4f:      	pushl	%eax
  560f50:      	calll	0x556753 <.text+0x155753>
  560f55:      	movl	0xc701e4, %ecx
  560f5b:      	calll	0x556a71 <.text+0x155a71>
  560f60:      	movzwl	0x62aea4, %eax
  560f67:      	pushl	%eax
  560f68:      	pushl	0xba7724
  560f6e:      	calll	0x4de670 <.text+0xdd670>
  560f73:      	popl	%ecx
  560f74:      	popl	%ecx
  560f75:      	movl	%ebp, %ecx
  560f77:      	calll	0x55972c <.text+0x15872c>
  560f7c:      	testb	%al, %al
  560f7e:      	je	0x560ff7 <.text+0x15fff7>
  560f80:      	movl	0xc6ff1c, %esi
  560f86:      	subl	0xc6ff18, %esi
  560f8c:      	pushl	0xba7724
  560f92:      	sarl	$0x2, %esi
  560f95:      	calll	0x5501b9 <.text+0x14f1b9>
  560f9a:      	cmpl	%eax, %esi
  560f9c:      	popl	%ecx
  560f9d:      	jle	0x560ff7 <.text+0x15fff7>
  560f9f:      	cmpb	$0x0, 0xc700c0
  560fa6:      	jne	0x560ff7 <.text+0x15fff7>
  560fa8:      	pushl	$0x6
  560faa:      	popl	%ecx
  560fab:      	movl	$0x5f0470, %esi         # imm = 0x5F0470
  560fb0:      	leal	0x58(%esp), %edi
  560fb4:      	rep		movsl	(%esi), %es:(%edi)
  560fb6:      	pushl	$0xe6
  560fbb:      	leal	0x76(%esp), %eax
  560fbf:      	pushl	$0x0
  560fc1:      	pushl	%eax
  560fc2:      	movsw	(%esi), %es:(%edi)
  560fc4:      	calll	0x5c6dfc <.text+0x1c5dfc>
  560fc9:      	leal	0x64(%esp), %eax
  560fcd:      	pushl	%eax
  560fce:      	pushl	$0x5f045c               # imm = 0x5F045C
  560fd3:      	pushl	$0x5ef520               # imm = 0x5EF520
  560fd8:      	calll	0x4ba7c3 <.text+0xb97c3>
  560fdd:      	leal	0x70(%esp), %eax
  560fe1:      	pushl	%eax
  560fe2:      	pushl	%ebx
  560fe3:      	calll	0x553e75 <.text+0x152e75>
  560fe8:      	addl	$0x20, %esp
  560feb:      	movl	%ebp, %ecx
  560fed:      	calll	0x5597f5 <.text+0x1587f5>
  560ff2:      	jmp	0x5610f5 <.text+0x1600f5>
  560ff7:      	movl	%ebp, %ecx
  560ff9:      	calll	0x55972c <.text+0x15872c>
  560ffe:      	testb	%al, %al
  561000:      	je	0x56120b <.text+0x16020b>
  561006:      	movl	0xc6ff1c, %eax
  56100b:      	subl	0xc6ff18, %eax
  561011:      	andl	$-0x4, %eax
  561014:      	cmpl	$0x4, %eax
  561017:      	jne	0x56120b <.text+0x16020b>
  56101d:      	cmpb	$0x0, 0xc700c0
  561024:      	jne	0x56120b <.text+0x16020b>
  56102a:      	pushl	$0x7
  56102c:      	popl	%ecx
  56102d:      	movl	$0x5f043c, %esi         # imm = 0x5F043C
  561032:      	leal	0x58(%esp), %edi
  561036:      	rep		movsl	(%esi), %es:(%edi)
  561038:      	pushl	$0xe3
  56103d:      	leal	0x79(%esp), %eax
  561041:      	pushl	$0x0
  561043:      	pushl	%eax
  561044:      	movsb	(%esi), %es:(%edi)
  561045:      	calll	0x5c6dfc <.text+0x1c5dfc>
  56104a:      	leal	0x64(%esp), %eax
  56104e:      	pushl	%eax
  56104f:      	pushl	$0x5f0428               # imm = 0x5F0428
  561054:      	pushl	$0x5ef520               # imm = 0x5EF520
  561059:      	calll	0x4ba7c3 <.text+0xb97c3>
  56105e:      	leal	0x70(%esp), %eax
  561062:      	pushl	%eax
  561063:      	pushl	%ebx
  561064:      	calll	0x553e75 <.text+0x152e75>
  561069:      	addl	$0x20, %esp
  56106c:      	movl	%ebp, %ecx
  56106e:      	calll	0x5597f5 <.text+0x1587f5>
  561073:      	movl	0xc70194, %ecx
  561079:      	xorl	%edi, %edi
  56107b:      	pushl	%edi
  56107c:      	xorl	%esi, %esi
  56107e:      	pushl	%edi
  56107f:      	incl	%esi
  561080:      	pushl	%esi
  561081:      	calll	0x57231f <.text+0x17131f>
  561086:      	movl	0xc70194, %ecx
  56108c:      	pushl	%esi
  56108d:      	calll	0x56f435 <.text+0x16e435>
  561092:      	movl	0xc70198, %ecx
  561098:      	pushl	%esi
  561099:      	calll	0x56f435 <.text+0x16e435>
  56109e:      	movl	0xc70194, %ecx
  5610a4:      	calll	0x5722e9 <.text+0x1712e9>
  5610a9:      	movl	0xc70198, %ecx
  5610af:      	calll	0x5722e9 <.text+0x1712e9>
  5610b4:      	movl	0xc7012c, %ecx
  5610ba:      	pushl	%esi
  5610bb:      	calll	0x57295a <.text+0x17195a>
  5610c0:      	movl	0xc70128, %ecx
  5610c6:      	pushl	%esi
  5610c7:      	calll	0x57295a <.text+0x17195a>
  5610cc:      	pushl	%edi
  5610cd:      	leal	0x40(%esp), %eax
  5610d1:      	pushl	%eax
  5610d2:      	pushl	%ebx
  5610d3:      	movl	$0x96, 0x48(%esp)
  5610db:      	movl	%edi, 0x4c(%esp)
  5610df:      	movl	$0x1f4, 0x50(%esp)      # imm = 0x1F4
  5610e7:      	movl	$0x1e, 0x54(%esp)
  5610ef:      	calll	*0x5ce550
  5610f5:      	movl	$0x5ef600, %edi         # imm = 0x5EF600
  5610fa:      	movzwl	0x62aea4, %eax
  561101:      	pushl	%eax
  561102:      	movl	%ebp, %ecx
  561104:      	calll	0x558c66 <.text+0x157c66>
  561109:      	testb	%al, %al
  56110b:      	jne	0x5616cb <.text+0x1606cb>
  561111:      	movl	0xc7015c, %ecx
  561117:      	calll	0x56f59e <.text+0x16e59e>
  56111c:      	movl	0xba72d4, %ecx
  561122:      	cmpl	%eax, %ecx
  561124:      	je	0x561132 <.text+0x160132>
  561126:      	pushl	%ecx
  561127:      	movl	0xc7015c, %ecx
  56112d:      	calll	0x572575 <.text+0x171575>
  561132:      	movl	0xc70158, %ecx
  561138:      	calll	0x56f59e <.text+0x16e59e>
  56113d:      	movl	0xba76d8, %ecx
  561143:      	cmpl	%eax, %ecx
  561145:      	je	0x561153 <.text+0x160153>
  561147:      	pushl	%ecx
  561148:      	movl	0xc70158, %ecx
  56114e:      	calll	0x572575 <.text+0x171575>
  561153:      	movl	0xc70154, %ecx
  561159:      	calll	0x56f59e <.text+0x16e59e>
  56115e:      	movl	0xba76dc, %ecx
  561164:      	cmpl	%eax, %ecx
  561166:      	je	0x561174 <.text+0x160174>
  561168:      	pushl	%ecx
  561169:      	movl	0xc70154, %ecx
  56116f:      	calll	0x572575 <.text+0x171575>
  561174:      	movl	0xc70150, %ecx
  56117a:      	calll	0x56f59e <.text+0x16e59e>
  56117f:      	movl	0xba72a0, %ecx
  561185:      	cmpl	%eax, %ecx
  561187:      	je	0x561195 <.text+0x160195>
  561189:      	pushl	%ecx
  56118a:      	movl	0xc70150, %ecx
  561190:      	calll	0x572575 <.text+0x171575>
  561195:      	movl	0xc7014c, %ecx
  56119b:      	calll	0x56f59e <.text+0x16e59e>
  5611a0:      	testl	%eax, %eax
  5611a2:      	movb	0xba76e0, %al
  5611a7:      	setne	%cl
  5611aa:      	cmpb	%cl, %al
  5611ac:      	je	0x5611bd <.text+0x1601bd>
  5611ae:      	movl	0xc7014c, %ecx
  5611b4:      	movzbl	%al, %eax
  5611b7:      	pushl	%eax
  5611b8:      	calll	0x572575 <.text+0x171575>
  5611bd:      	movl	0xc70148, %ecx
  5611c3:      	calll	0x56f59e <.text+0x16e59e>
  5611c8:      	testl	%eax, %eax
  5611ca:      	movb	0xba76e2, %al
  5611cf:      	setne	%cl
  5611d2:      	cmpb	%cl, %al
  5611d4:      	je	0x56139b <.text+0x16039b>
  5611da:      	movl	0xc70148, %ecx
  5611e0:      	movzbl	%al, %eax
  5611e3:      	pushl	%eax
  5611e4:      	calll	0x572575 <.text+0x171575>
  5611e9:      	cmpb	$0x0, 0xba76e2
  5611f0:      	je	0x561368 <.text+0x160368>
  5611f6:      	pushl	%edi
  5611f7:      	calll	0x4839c7 <.text+0x829c7>
  5611fc:      	popl	%ecx
  5611fd:      	testl	%eax, %eax
  5611ff:      	je	0x561368 <.text+0x160368>
  561205:      	pushl	%edi
  561206:      	jmp	0x56136d <.text+0x16036d>
  56120b:      	movl	0xc701e4, %ecx
  561211:      	pushl	0x88(%ecx)
  561217:      	calll	0x5520a2 <.text+0x1510a2>
  56121c:      	testl	%eax, %eax
  56121e:      	je	0x5610fa <.text+0x1600fa>
  561224:      	movl	%ebp, %ecx
  561226:      	calll	0x55972c <.text+0x15872c>
  56122b:      	testb	%al, %al
  56122d:      	jne	0x56123b <.text+0x16023b>
  56122f:      	cmpb	%al, 0xc700c0
  561235:      	je	0x5610fa <.text+0x1600fa>
  56123b:      	movl	0xc701e4, %ecx
  561241:      	pushl	0x88(%ecx)
  561247:      	calll	0x5520a2 <.text+0x1510a2>
  56124c:      	pushl	%eax
  56124d:      	pushl	0xba7724
  561253:      	calll	0x550056 <.text+0x14f056>
  561258:      	movl	0xc701e4, %esi
  56125e:      	popl	%ecx
  56125f:      	popl	%ecx
  561260:      	pushl	0x88(%esi)
  561266:      	movl	%esi, %ecx
  561268:      	calll	0x5520a2 <.text+0x1510a2>
  56126d:      	movl	$0xd42330, %edx         # imm = 0xD42330
  561272:      	movb	(%eax), %cl
  561274:      	incl	%eax
  561275:      	movb	%cl, (%edx)
  561277:      	incl	%edx
  561278:      	testb	%cl, %cl
  56127a:      	jne	0x561272 <.text+0x160272>
  56127c:      	pushl	0x88(%esi)
  561282:      	movl	%esi, %ecx
  561284:      	calll	0x5520a2 <.text+0x1510a2>
  561289:      	pushl	%eax
  56128a:      	calll	0x4dd403 <.text+0xdc403>
  56128f:      	movl	0xc701e4, %eax
  561294:      	xorl	%edi, %edi
  561296:      	popl	%ecx
  561297:      	cmpl	%edi, 0x10(%eax)
  56129a:      	je	0x5612a6 <.text+0x1602a6>
  56129c:      	movl	0x10(%eax), %ecx
  56129f:      	calll	0x551729 <.text+0x150729>
  5612a4:      	jmp	0x5612ab <.text+0x1602ab>
  5612a6:      	movl	$0x5d0e3a, %eax         # imm = 0x5D0E3A
  5612ab:      	pushl	%eax
  5612ac:      	calll	0x4dd8fe <.text+0xdc8fe>
  5612b1:      	xorl	%esi, %esi
  5612b3:      	incl	%esi
  5612b4:      	pushl	%esi
  5612b5:      	calll	0x4dd8d5 <.text+0xdc8d5>
  5612ba:      	pushl	%esi
  5612bb:      	calll	0x4dd8e3 <.text+0xdc8e3>
  5612c0:      	pushl	0xba7724
  5612c6:      	movb	$0x1, 0xba72d3
  5612cd:      	calll	0x54fd98 <.text+0x14ed98>
  5612d2:      	pushl	%esi
  5612d3:      	pushl	0xba7724
  5612d9:      	movb	%al, 0xba72d1
  5612de:      	calll	0x54fdde <.text+0x14edde>
  5612e3:      	movl	$0x4c53, %eax           # imm = 0x4C53
  5612e8:      	movw	%ax, 0x54(%esp)
  5612ed:      	movl	0xba721c, %eax
  5612f2:      	pushl	$0xa
  5612f4:      	movl	%eax, 0x5a(%esp)
  5612f8:      	leal	0x58(%esp), %eax
  5612fc:      	pushl	%eax
  5612fd:      	movzwl	0x62aea4, %eax
  561304:      	pushl	%esi
  561305:      	pushl	%edi
  561306:      	pushl	%eax
  561307:      	pushl	0xba7724
  56130d:      	calll	0x4ddade <.text+0xdcade>
  561312:      	pushl	0xba7724
  561318:      	movl	%eax, 0xc6f4b0
  56131d:      	calll	0x54fd98 <.text+0x14ed98>
  561322:      	addl	$0x34, %esp
  561325:      	testb	%al, %al
  561327:      	je	0x56132c <.text+0x16032c>
  561329:      	pushl	%edi
  56132a:      	jmp	0x56132d <.text+0x16032d>
  56132c:      	pushl	%esi
  56132d:      	pushl	0xba7724
  561333:      	calll	0x5860fa <.text+0x1850fa>
  561338:      	popl	%ecx
  561339:      	popl	%ecx
  56133a:      	pushl	$0x5
  56133c:      	movl	%eax, 0xc6f4b0
  561341:      	calll	0x4788e6 <.text+0x778e6>
  561346:      	movl	%edi, 0xc70520
  56134c:      	calll	0x54fc4f <.text+0x14ec4f>
  561351:      	pushl	%esi
  561352:      	pushl	%ebx
  561353:      	calll	0x56e64a <.text+0x16d64a>
  561358:      	pushl	%esi
  561359:      	calll	0x571075 <.text+0x170075>
  56135e:      	addl	$0x10, %esp
  561361:      	movl	%esi, %eax
  561363:      	jmp	0x56301e <.text+0x16201e>
  561368:      	pushl	$0x5ef5f4               # imm = 0x5EF5F4
  56136d:      	movl	0xc700f4, %ecx
  561373:      	calll	0x55684f <.text+0x15584f>
  561378:      	pushl	0xba7724
  56137e:      	calll	0x550103 <.text+0x14f103>
  561383:      	popl	%ecx
  561384:      	movl	0xc700f4, %ecx
  56138a:      	pushl	%eax
  56138b:      	calll	0x556753 <.text+0x155753>
  561390:      	movl	0xc701e4, %ecx
  561396:      	calll	0x556a71 <.text+0x155a71>
  56139b:      	pushl	0xba7724
  5613a1:      	calll	0x54fd98 <.text+0x14ed98>
  5613a6:      	popl	%ecx
  5613a7:      	movl	0xc6fdb8, %ecx
  5613ad:      	testb	%al, %al
  5613af:      	je	0x5613bf <.text+0x1603bf>
  5613b1:      	calll	0x56f59e <.text+0x16e59e>
  5613b6:      	cmpl	$0x1, %eax
  5613b9:      	je	0x5613d5 <.text+0x1603d5>
  5613bb:      	pushl	$0x1
  5613bd:      	jmp	0x5613ca <.text+0x1603ca>
  5613bf:      	calll	0x56f59e <.text+0x16e59e>
  5613c4:      	testl	%eax, %eax
  5613c6:      	je	0x5613d5 <.text+0x1603d5>
  5613c8:      	pushl	$0x0
  5613ca:      	movl	0xc6fdb8, %ecx
  5613d0:      	calll	0x572575 <.text+0x171575>
  5613d5:      	pushl	0xba7724
  5613db:      	calll	0x54fed4 <.text+0x14eed4>
  5613e0:      	testb	%al, %al
  5613e2:      	popl	%ecx
  5613e3:      	movl	0xc7016c, %ecx
  5613e9:      	setne	%al
  5613ec:      	movb	%al, 0x62a99e
  5613f1:      	calll	0x56f59e <.text+0x16e59e>
  5613f6:      	testl	%eax, %eax
  5613f8:      	movb	0x62a99e, %al
  5613fd:      	setne	%cl
  561400:      	cmpb	%al, %cl
  561402:      	je	0x561413 <.text+0x160413>
  561404:      	movl	0xc7016c, %ecx
  56140a:      	movzbl	%al, %eax
  56140d:      	pushl	%eax
  56140e:      	calll	0x572575 <.text+0x171575>
  561413:      	pushl	0xba7724
  561419:      	calll	0x54ff72 <.text+0x14ef72>
  56141e:      	testb	%al, %al
  561420:      	popl	%ecx
  561421:      	movl	0xc70168, %ecx
  561427:      	setne	%al
  56142a:      	movb	%al, 0x62a99f
  56142f:      	calll	0x56f59e <.text+0x16e59e>
  561434:      	testl	%eax, %eax
  561436:      	movb	0x62a99f, %al
  56143b:      	setne	%cl
  56143e:      	cmpb	%al, %cl
  561440:      	je	0x561451 <.text+0x160451>
  561442:      	movl	0xc70168, %ecx
  561448:      	movzbl	%al, %eax
  56144b:      	pushl	%eax
  56144c:      	calll	0x572575 <.text+0x171575>
  561451:      	pushl	0xba7724
  561457:      	calll	0x550010 <.text+0x14f010>
  56145c:      	testb	%al, %al
  56145e:      	popl	%ecx
  56145f:      	movl	0xc70164, %ecx
  561465:      	setne	%al
  561468:      	movb	%al, 0x62aa04
  56146d:      	calll	0x56f59e <.text+0x16e59e>
  561472:      	testl	%eax, %eax
  561474:      	movb	0x62aa04, %al
  561479:      	setne	%cl
  56147c:      	cmpb	%al, %cl
  56147e:      	je	0x56148f <.text+0x16048f>
  561480:      	movl	0xc70164, %ecx
  561486:      	movzbl	%al, %eax
  561489:      	pushl	%eax
  56148a:      	calll	0x572575 <.text+0x171575>
  56148f:      	pushl	0xba7724
  561495:      	calll	0x550103 <.text+0x14f103>
  56149a:      	movl	%eax, %esi
  56149c:      	pushl	$0x811c9dc5             # imm = 0x811C9DC5
  5614a1:      	pushl	%esi
  5614a2:      	calll	0x4166b8 <.text+0x156b8>
  5614a7:      	movl	0xc701e4, %ecx
  5614ad:      	addl	$0xc, %esp
  5614b0:      	pushl	%esi
  5614b1:      	movl	%eax, %ebp
  5614b3:      	calll	0x551df0 <.text+0x150df0>
  5614b8:      	movl	0xc701e4, %ecx
  5614be:      	pushl	0x88(%ecx)
  5614c4:      	movl	%eax, 0x20(%esp)
  5614c8:      	calll	0x5520d1 <.text+0x1510d1>
  5614cd:      	pushl	0xba7724
  5614d3:      	movl	%eax, %edi
  5614d5:      	calll	0x5501b9 <.text+0x14f1b9>
  5614da:      	cmpl	%eax, %edi
  5614dc:      	popl	%ecx
  5614dd:      	jle	0x5614e1 <.text+0x1604e1>
  5614df:      	movl	%eax, %edi
  5614e1:      	movl	0xc70160, %ecx
  5614e7:      	calll	0x56f59e <.text+0x16e59e>
  5614ec:      	cmpl	%eax, %edi
  5614ee:      	je	0x5614fc <.text+0x1604fc>
  5614f0:      	movl	0xc70160, %ecx
  5614f6:      	pushl	%edi
  5614f7:      	calll	0x572575 <.text+0x171575>
  5614fc:      	movl	0xc700fc, %ecx
  561502:      	xorl	%edi, %edi
  561504:      	cmpl	%edi, %ecx
  561506:      	jne	0x561553 <.text+0x160553>
  561508:      	pushl	$0x128                  # imm = 0x128
  56150d:      	calll	0x5c6d12 <.text+0x1c5d12>
  561512:      	popl	%ecx
  561513:      	cmpl	%edi, %eax
  561515:      	je	0x561536 <.text+0x160536>
  561517:      	pushl	%edi
  561518:      	pushl	$0x59
  56151a:      	pushl	$0x8a
  56151f:      	pushl	$0x3f
  561521:      	pushl	$0x26
  561523:      	pushl	0x30(%esp)
  561527:      	movl	%eax, %ecx
  561529:      	pushl	%ebx
  56152a:      	calll	0x572841 <.text+0x171841>
  56152f:      	movl	%eax, 0xc700fc
  561534:      	jmp	0x56153c <.text+0x16053c>
  561536:      	movl	%edi, 0xc700fc
  56153c:      	movl	0xc701e4, %ecx
  561542:      	pushl	%esi
  561543:      	movl	%ebp, 0xc700b4
  561549:      	calll	0x557ab8 <.text+0x156ab8>
  56154e:      	jmp	0x561774 <.text+0x160774>
  561553:      	cmpl	0xc700b4, %ebp
  561559:      	je	0x561774 <.text+0x160774>
  56155f:      	pushl	0x1c(%esp)
  561563:      	movl	%ebp, 0xc700b4
  561569:      	calll	0x570307 <.text+0x16f307>
  56156e:      	movl	0xc700fc, %ecx
  561574:      	pushl	%edi
  561575:      	pushl	%edi
  561576:      	calll	0x571bcc <.text+0x170bcc>
  56157b:      	movl	0xc701e4, %ecx
  561581:      	pushl	%esi
  561582:      	calll	0x557ab8 <.text+0x156ab8>
  561587:      	movl	0xc701e4, %ecx
  56158d:      	calll	0x551d18 <.text+0x150d18>
  561592:      	subl	%edi, %eax
  561594:      	je	0x561633 <.text+0x160633>
  56159a:      	decl	%eax
  56159b:      	jne	0x561774 <.text+0x160774>
  5615a1:      	movl	0xc7018c, %ecx
  5615a7:      	xorl	%esi, %esi
  5615a9:      	incl	%esi
  5615aa:      	pushl	%esi
  5615ab:      	calll	0x56f435 <.text+0x16e435>
  5615b0:      	movl	0xc7015c, %ecx
  5615b6:      	pushl	%esi
  5615b7:      	calll	0x57403d <.text+0x17303d>
  5615bc:      	movl	0xc70188, %ecx
  5615c2:      	pushl	%esi
  5615c3:      	calll	0x56f435 <.text+0x16e435>
  5615c8:      	movl	0xc70158, %ecx
  5615ce:      	pushl	%esi
  5615cf:      	calll	0x57403d <.text+0x17303d>
  5615d4:      	movl	0xc701bc, %ecx
  5615da:      	pushl	%esi
  5615db:      	calll	0x573f6e <.text+0x172f6e>
  5615e0:      	movl	0xc70164, %ecx
  5615e6:      	pushl	%esi
  5615e7:      	calll	0x574011 <.text+0x173011>
  5615ec:      	movl	0xc701c8, %ecx
  5615f2:      	pushl	%esi
  5615f3:      	calll	0x573f6e <.text+0x172f6e>
  5615f8:      	movl	0xc7016c, %ecx
  5615fe:      	pushl	%esi
  5615ff:      	calll	0x574011 <.text+0x173011>
  561604:      	movl	0xc701c0, %ecx
  56160a:      	pushl	%esi
  56160b:      	calll	0x573f6e <.text+0x172f6e>
  561610:      	movl	0xc70168, %ecx
  561616:      	pushl	%esi
  561617:      	calll	0x574011 <.text+0x173011>
  56161c:      	movl	0xc70180, %ecx
  561622:      	pushl	%esi
  561623:      	calll	0x573f6e <.text+0x172f6e>
  561628:      	movl	0xc70150, %ecx
  56162e:      	jmp	0x5616c0 <.text+0x1606c0>
  561633:      	movl	0xc701c8, %ecx
  561639:      	xorl	%esi, %esi
  56163b:      	incl	%esi
  56163c:      	pushl	%esi
  56163d:      	calll	0x56f435 <.text+0x16e435>
  561642:      	movl	0xc7016c, %ecx
  561648:      	pushl	%esi
  561649:      	calll	0x57403d <.text+0x17303d>
  56164e:      	movl	0xc701c0, %ecx
  561654:      	pushl	%esi
  561655:      	calll	0x56f435 <.text+0x16e435>
  56165a:      	movl	0xc70168, %ecx
  561660:      	pushl	%esi
  561661:      	calll	0x57403d <.text+0x17303d>
  561666:      	movl	0xc701bc, %ecx
  56166c:      	pushl	%esi
  56166d:      	calll	0x56f435 <.text+0x16e435>
  561672:      	movl	0xc70164, %ecx
  561678:      	pushl	%esi
  561679:      	calll	0x57403d <.text+0x17303d>
  56167e:      	movl	0xc70180, %ecx
  561684:      	pushl	%esi
  561685:      	calll	0x56f435 <.text+0x16e435>
  56168a:      	movl	0xc70150, %ecx
  561690:      	pushl	%esi
  561691:      	calll	0x57403d <.text+0x17303d>
  561696:      	movl	0xc7018c, %ecx
  56169c:      	pushl	%esi
  56169d:      	calll	0x573f6e <.text+0x172f6e>
  5616a2:      	movl	0xc7015c, %ecx
  5616a8:      	pushl	%esi
  5616a9:      	calll	0x574011 <.text+0x173011>
  5616ae:      	movl	0xc70188, %ecx
  5616b4:      	pushl	%esi
  5616b5:      	calll	0x573f6e <.text+0x172f6e>
  5616ba:      	movl	0xc70158, %ecx
  5616c0:      	pushl	%esi
  5616c1:      	calll	0x574011 <.text+0x173011>
  5616c6:      	jmp	0x561774 <.text+0x160774>
  5616cb:      	cmpl	$0x0, 0xc701c4
  5616d2:      	jne	0x561774 <.text+0x160774>
  5616d8:      	xorl	%ecx, %ecx
  5616da:      	calll	0x56f4b7 <.text+0x16e4b7>
  5616df:      	movl	0xc701c0, %ecx
  5616e5:      	calll	0x56f4b7 <.text+0x16e4b7>
  5616ea:      	movl	0xc701bc, %ecx
  5616f0:      	calll	0x56f4b7 <.text+0x16e4b7>
  5616f5:      	movl	0xc701c8, %ecx
  5616fb:      	calll	0x56f4b7 <.text+0x16e4b7>
  561700:      	movl	0xc70190, %ecx
  561706:      	calll	0x56f4b7 <.text+0x16e4b7>
  56170b:      	movl	0xc7018c, %ecx
  561711:      	calll	0x56f4b7 <.text+0x16e4b7>
  561716:      	movl	0xc70188, %ecx
  56171c:      	calll	0x56f4b7 <.text+0x16e4b7>
  561721:      	movl	0xc70174, %ecx
  561727:      	calll	0x56f4b7 <.text+0x16e4b7>
  56172c:      	movl	0xc70180, %ecx
  561732:      	calll	0x56f4b7 <.text+0x16e4b7>
  561737:      	movl	0xc7017c, %ecx
  56173d:      	calll	0x56f4b7 <.text+0x16e4b7>
  561742:      	movl	0xc701d0, %ecx
  561748:      	xorl	%esi, %esi
  56174a:      	pushl	%esi
  56174b:      	calll	0x573f6e <.text+0x172f6e>
  561750:      	movl	0xc70170, %ecx
  561756:      	pushl	%esi
  561757:      	calll	0x573f6e <.text+0x172f6e>
  56175c:      	movl	0xc701b8, %ecx
  561762:      	pushl	%esi
  561763:      	calll	0x573f6e <.text+0x172f6e>
  561768:      	movl	0xc701b4, %ecx
  56176e:      	pushl	%esi
  56176f:      	calll	0x573f6e <.text+0x172f6e>
  561774:      	movl	0xba729c, %eax
  561779:      	cmpl	%eax, 0xc700b8
  56177f:      	je	0x5617c9 <.text+0x1607c9>
  561781:      	movl	0xc70144, %ecx
  561787:      	pushl	%eax
  561788:      	movl	%eax, 0xc700b8
  56178d:      	calll	0x572575 <.text+0x171575>
  561792:      	movl	0xc701e4, %eax
  561797:      	cmpl	$0x0, 0x10(%eax)
  56179b:      	je	0x5617a7 <.text+0x1607a7>
  56179d:      	movl	0x10(%eax), %ecx
  5617a0:      	calll	0x551729 <.text+0x150729>
  5617a5:      	jmp	0x5617ac <.text+0x1607ac>
  5617a7:      	movl	$0x5d0e3a, %eax         # imm = 0x5D0E3A
  5617ac:      	pushl	0xba729c
  5617b2:      	pushl	%eax
  5617b3:      	movzwl	0x62aea4, %eax
  5617ba:      	pushl	%eax
  5617bb:      	pushl	0xba7724
  5617c1:      	calll	0x54fcda <.text+0x14ecda>
  5617c6:      	addl	$0x10, %esp
  5617c9:      	calll	0x55aa74 <.text+0x159a74>
  5617ce:      	cmpb	$0x0, 0xc6f4b7
  5617d5:      	je	0x561806 <.text+0x160806>
  5617d7:      	pushl	$0x6
  5617d9:      	popl	%ecx
  5617da:      	movl	$0x5f0410, %esi         # imm = 0x5F0410
  5617df:      	leal	0x58(%esp), %edi
  5617e3:      	rep		movsl	(%esi), %es:(%edi)
  5617e5:      	pushl	$0xe8
  5617ea:      	xorl	%esi, %esi
  5617ec:      	leal	0x74(%esp), %eax
  5617f0:      	pushl	%esi
  5617f1:      	pushl	%eax
  5617f2:      	calll	0x5c6dfc <.text+0x1c5dfc>
  5617f7:      	leal	0x64(%esp), %eax
  5617fb:      	pushl	%eax
  5617fc:      	pushl	$0x5f03fc               # imm = 0x5F03FC
  561801:      	jmp	0x560e37 <.text+0x15fe37>
  561806:      	cmpb	$0x0, 0xc6fca6
  56180d:      	je	0x561841 <.text+0x160841>
  56180f:      	pushl	$0x5
  561811:      	popl	%ecx
  561812:      	movl	$0x5f03e4, %esi         # imm = 0x5F03E4
  561817:      	leal	0x58(%esp), %edi
  56181b:      	rep		movsl	(%esi), %es:(%edi)
  56181d:      	movsw	(%esi), %es:(%edi)
  56181f:      	movsb	(%esi), %es:(%edi)
  561820:      	pushl	$0xe9
  561825:      	xorl	%esi, %esi
  561827:      	leal	0x73(%esp), %eax
  56182b:      	pushl	%esi
  56182c:      	pushl	%eax
  56182d:      	calll	0x5c6dfc <.text+0x1c5dfc>
  561832:      	leal	0x64(%esp), %eax
  561836:      	pushl	%eax
  561837:      	pushl	$0x5f03d0               # imm = 0x5F03D0
  56183c:      	jmp	0x560e37 <.text+0x15fe37>
  561841:      	fldz
  561843:      	flds	0xc6fdb4
  561849:      	fcom	%st(1)
  56184b:      	fnstsw	%ax
  56184d:      	fstp	%st(1)
  56184f:      	testb	$0x1, %ah
  561852:      	jne	0x5619a1 <.text+0x1609a1>
  561858:      	flds	0x5f03cc
  56185e:      	fcomp	%st(1)
  561860:      	fnstsw	%ax
  561862:      	testb	$0x1, %ah
  561865:      	jne	0x5619a1 <.text+0x1609a1>
  56186b:      	cmpl	$0x0, 0xc7011c
  561872:      	je	0x5619a1 <.text+0x1609a1>
  561878:      	flds	0x5f03c8
  56187e:      	fmul	%st(1), %st
  561880:      	calll	0x5c6e10 <.text+0x1c5e10>
  561885:      	flds	0x5f03c4
  56188b:      	movl	%eax, %esi
  56188d:      	fmul	%st(1), %st
  56188f:      	movl	%esi, 0x14(%esp)
  561893:      	calll	0x5c6e10 <.text+0x1c5e10>
  561898:      	movl	%esi, %ebp
  56189a:      	imull	$0x3c, %esi, %esi
  56189d:      	imull	$-0x3c, %ebp, %ebp
  5618a0:      	subl	%eax, %ebp
  5618a2:      	addl	%ebp, %esi
  5618a4:      	imull	$0x3c, %esi, %esi
  5618a7:      	calll	0x5c6e10 <.text+0x1c5e10>
  5618ac:      	subl	%esi, %eax
  5618ae:      	movl	$0x5f0658, %esi         # imm = 0x5F0658
  5618b3:      	leal	0x158(%esp), %edi
  5618ba:      	movsl	(%esi), %es:(%edi)
  5618bb:      	movsl	(%esi), %es:(%edi)
  5618bc:      	movsl	(%esi), %es:(%edi)
  5618bd:      	pushl	$0xf2
  5618c2:      	movl	%eax, 0x20(%esp)
  5618c6:      	leal	0x16a(%esp), %eax
  5618cd:      	pushl	$0x0
  5618cf:      	pushl	%eax
  5618d0:      	movsw	(%esi), %es:(%edi)
  5618d2:      	calll	0x5c6dfc <.text+0x1c5dfc>
  5618d7:      	movl	$0x5f03b8, %esi         # imm = 0x5F03B8
  5618dc:      	leal	0x64(%esp), %edi
  5618e0:      	movsl	(%esi), %es:(%edi)
  5618e1:      	movsl	(%esi), %es:(%edi)
  5618e2:      	pushl	$0xf6
  5618e7:      	leal	0x72(%esp), %eax
  5618eb:      	pushl	$0x0
  5618ed:      	pushl	%eax
  5618ee:      	movsw	(%esi), %es:(%edi)
  5618f0:      	calll	0x5c6dfc <.text+0x1c5dfc>
  5618f5:      	leal	0x170(%esp), %eax
  5618fc:      	pushl	%eax
  5618fd:      	pushl	$0x5f03a8               # imm = 0x5F03A8
  561902:      	movl	$0x5e5c9c, %edi         # imm = 0x5E5C9C
  561907:      	pushl	%edi
  561908:      	calll	0x4ba7c3 <.text+0xb97c3>
  56190d:      	leal	0x7c(%esp), %eax
  561911:      	pushl	%eax
  561912:      	pushl	$0x5f039c               # imm = 0x5F039C
  561917:      	pushl	%edi
  561918:      	calll	0x4ba7c3 <.text+0xb97c3>
  56191d:      	pushl	0x4c(%esp)
  561921:      	leal	0x8c(%esp), %eax
  561928:      	pushl	%ebp
  561929:      	pushl	0x4c(%esp)
  56192d:      	pushl	%eax
  56192e:      	leal	0x198(%esp), %eax
  561935:      	pushl	%eax
  561936:      	leal	0x29c(%esp), %eax
  56193d:      	pushl	$0x5f037c               # imm = 0x5F037C
  561942:      	pushl	%eax
  561943:      	calll	*0x5ce49c
  561949:      	movl	0xc7011c, %edi
  56194f:      	addl	$0x4c, %esp
  561952:      	leal	0x4(%edi), %esi
  561955:      	leal	0x258(%esp), %eax
  56195c:      	movb	(%eax), %cl
  56195e:      	cmpb	(%esi), %cl
  561960:      	jne	0x56197a <.text+0x16097a>
  561962:      	testb	%cl, %cl
  561964:      	je	0x561976 <.text+0x160976>
  561966:      	movb	0x1(%eax), %cl
  561969:      	cmpb	0x1(%esi), %cl
  56196c:      	jne	0x56197a <.text+0x16097a>
  56196e:      	incl	%eax
  56196f:      	incl	%eax
  561970:      	incl	%esi
  561971:      	incl	%esi
  561972:      	testb	%cl, %cl
  561974:      	jne	0x56195c <.text+0x16095c>
  561976:      	xorl	%eax, %eax
  561978:      	jmp	0x56197f <.text+0x16097f>
  56197a:      	sbbl	%eax, %eax
  56197c:      	sbbl	$-0x1, %eax
  56197f:      	testl	%eax, %eax
  561981:      	je	0x5619a3 <.text+0x1609a3>
  561983:      	leal	0x258(%esp), %eax
  56198a:      	pushl	%eax
  56198b:      	movl	%edi, %ecx
  56198d:      	calll	0x570307 <.text+0x16f307>
  561992:      	movl	0xc7011c, %ecx
  561998:      	pushl	$0x1
  56199a:      	calll	0x57295a <.text+0x17195a>
  56199f:      	jmp	0x5619a3 <.text+0x1609a3>
  5619a1:      	fstp	%st(0)
  5619a3:      	xorl	%ebp, %ebp
  5619a5:      	cmpl	%ebp, 0xc6fdc4
  5619ab:      	je	0x561a77 <.text+0x160a77>
  5619b1:      	calll	0x4dd321 <.text+0xdc321>
  5619b6:      	movl	0xc6fdc4, %eax
  5619bb:      	cmpl	$0x1, %eax
  5619be:      	jne	0x5619f4 <.text+0x1609f4>
  5619c0:      	pushl	$0x6
  5619c2:      	popl	%ecx
  5619c3:      	movl	$0x5f0360, %esi         # imm = 0x5F0360
  5619c8:      	leal	0x158(%esp), %edi
  5619cf:      	rep		movsl	(%esi), %es:(%edi)
  5619d1:      	pushl	$0xe7
  5619d6:      	leal	0x175(%esp), %eax
  5619dd:      	pushl	%ebp
  5619de:      	pushl	%eax
  5619df:      	movsb	(%esi), %es:(%edi)
  5619e0:      	calll	0x5c6dfc <.text+0x1c5dfc>
  5619e5:      	leal	0x164(%esp), %eax
  5619ec:      	pushl	%eax
  5619ed:      	pushl	$0x5f0354               # imm = 0x5F0354
  5619f2:      	jmp	0x561a2b <.text+0x160a2b>
  5619f4:      	cmpl	$0x2, %eax
  5619f7:      	jne	0x561a46 <.text+0x160a46>
  5619f9:      	pushl	$0x9
  5619fb:      	popl	%ecx
  5619fc:      	movl	$0x5f032c, %esi         # imm = 0x5F032C
  561a01:      	leal	0x158(%esp), %edi
  561a08:      	rep		movsl	(%esi), %es:(%edi)
  561a0a:      	pushl	$0xdb
  561a0f:      	leal	0x181(%esp), %eax
  561a16:      	pushl	%ebp
  561a17:      	pushl	%eax
  561a18:      	movsb	(%esi), %es:(%edi)
  561a19:      	calll	0x5c6dfc <.text+0x1c5dfc>
  561a1e:      	leal	0x164(%esp), %eax
  561a25:      	pushl	%eax
  561a26:      	pushl	$0x5f0320               # imm = 0x5F0320
  561a2b:      	pushl	$0x5ef520               # imm = 0x5EF520
  561a30:      	calll	0x4ba7c3 <.text+0xb97c3>
  561a35:      	leal	0x170(%esp), %eax
  561a3c:      	pushl	%eax
  561a3d:      	pushl	%ebx
  561a3e:      	calll	0x553e75 <.text+0x152e75>
  561a43:      	addl	$0x20, %esp
  561a46:      	xorl	%esi, %esi
  561a48:      	incl	%esi
  561a49:      	movl	%esi, 0xc7052c
  561a4f:      	movl	%ebp, 0xc70520
  561a55:      	calll	0x56e644 <.text+0x16d644>
  561a5a:      	cmpl	%ebx, %eax
  561a5c:      	jne	0x561361 <.text+0x160361>
  561a62:      	pushl	%ebp
  561a63:      	pushl	%ebx
  561a64:      	calll	0x56e64a <.text+0x16d64a>
  561a69:      	pushl	%esi
  561a6a:      	calll	0x571075 <.text+0x170075>
  561a6f:      	addl	$0xc, %esp
  561a72:      	jmp	0x561361 <.text+0x160361>
  561a77:      	movw	0x62aea4, %ax
  561a7d:      	movl	$0xfa01, %ecx           # imm = 0xFA01
  561a82:      	cmpw	%ax, %cx
  561a85:      	je	0x561cc5 <.text+0x160cc5>
  561a8b:      	movzwl	%ax, %eax
  561a8e:      	movl	$0xc6fef8, %esi         # imm = 0xC6FEF8
  561a93:      	pushl	%eax
  561a94:      	movl	%esi, %ecx
  561a96:      	calll	0x55969a <.text+0x15869a>
  561a9b:      	testb	%al, %al
  561a9d:      	je	0x561cc5 <.text+0x160cc5>
  561aa3:      	movzwl	0x62aea4, %eax
  561aaa:      	pushl	%eax
  561aab:      	movl	%esi, %ecx
  561aad:      	calll	0x558c66 <.text+0x157c66>
  561ab2:      	testb	%al, %al
  561ab4:      	jne	0x561cc5 <.text+0x160cc5>
  561aba:      	pushl	0xba7724
  561ac0:      	calll	0x550103 <.text+0x14f103>
  561ac5:      	movl	$0xd42330, %ebp         # imm = 0xD42330
  561aca:      	popl	%ecx
  561acb:      	movl	%ebp, %edx
  561acd:      	movb	(%eax), %cl
  561acf:      	incl	%eax
  561ad0:      	movb	%cl, (%edx)
  561ad2:      	incl	%edx
  561ad3:      	testb	%cl, %cl
  561ad5:      	jne	0x561acd <.text+0x160acd>
  561ad7:      	movl	%ebp, %edi
  561ad9:      	decl	%edi
  561ada:      	movb	0x1(%edi), %al
  561add:      	incl	%edi
  561ade:      	testb	%al, %al
  561ae0:      	jne	0x561ada <.text+0x160ada>
  561ae2:      	movl	$0x5eec1c, %esi         # imm = 0x5EEC1C
  561ae7:      	movsl	(%esi), %es:(%edi)
  561ae8:      	pushl	%ebp
  561ae9:      	movsb	(%esi), %es:(%edi)
  561aea:      	calll	0x4dd403 <.text+0xdc403>
  561aef:      	popl	%ecx
  561af0:      	fldz
  561af2:      	fcomps	0xc6fdb4
  561af8:      	fnstsw	%ax
  561afa:      	testb	$0x5, %ah
  561afd:      	jnp	0x561b21 <.text+0x160b21>
  561aff:      	pushl	0xba7724
  561b05:      	calll	0x54fe36 <.text+0x14ee36>
  561b0a:      	popl	%ecx
  561b0b:      	testb	%al, %al
  561b0d:      	jne	0x561b21 <.text+0x160b21>
  561b0f:      	movl	$0xc6fef8, %ecx         # imm = 0xC6FEF8
  561b14:      	calll	0x5596b7 <.text+0x1586b7>
  561b19:      	testb	%al, %al
  561b1b:      	je	0x561cc3 <.text+0x160cc3>
  561b21:      	pushl	0xba7724
  561b27:      	calll	0x54fd98 <.text+0x14ed98>
  561b2c:      	testb	%al, %al
  561b2e:      	setne	%al
  561b31:      	movb	%al, 0xba72d1
  561b36:      	movl	$0x5ef34c, (%esp)       # imm = 0x5EF34C
  561b3d:      	calll	0x546add <.text+0x145add>
  561b42:      	pushl	0xba7724
  561b48:      	calll	0x550103 <.text+0x14f103>
  561b4d:      	pushl	%eax
  561b4e:      	calll	0x546d28 <.text+0x145d28>
  561b53:      	movl	%eax, %esi
  561b55:      	calll	0x546ac4 <.text+0x145ac4>
  561b5a:      	pushl	0xba7724
  561b60:      	calll	0x5501fd <.text+0x14f1fd>
  561b65:      	addl	$0x10, %esp
  561b68:      	cmpl	%eax, %esi
  561b6a:      	je	0x561c5f <.text+0x160c5f>
  561b70:      	cmpl	0xba721c, %esi
  561b76:      	je	0x561c5f <.text+0x160c5f>
  561b7c:      	pushl	0xba7724
  561b82:      	calll	0x550103 <.text+0x14f103>
  561b87:      	pushl	%eax
  561b88:      	calll	0x546eb3 <.text+0x145eb3>
  561b8d:      	popl	%ecx
  561b8e:      	popl	%ecx
  561b8f:      	testl	%eax, %eax
  561b91:      	je	0x561be2 <.text+0x160be2>
  561b93:      	pushl	$0xa
  561b95:      	popl	%ecx
  561b96:      	pushl	$0xd8
  561b9b:      	leal	0x184(%esp), %eax
  561ba2:      	pushl	$0x0
  561ba4:      	movl	$0x5f02f8, %esi         # imm = 0x5F02F8
  561ba9:      	leal	0x160(%esp), %edi
  561bb0:      	pushl	%eax
  561bb1:      	rep		movsl	(%esi), %es:(%edi)
  561bb3:      	calll	0x5c6dfc <.text+0x1c5dfc>
  561bb8:      	leal	0x164(%esp), %eax
  561bbf:      	pushl	%eax
  561bc0:      	pushl	$0x5f02e4               # imm = 0x5F02E4
  561bc5:      	pushl	$0x5ef520               # imm = 0x5EF520
  561bca:      	calll	0x4ba7c3 <.text+0xb97c3>
  561bcf:      	leal	0x170(%esp), %eax
  561bd6:      	pushl	%eax
  561bd7:      	pushl	%ebx
  561bd8:      	calll	0x553e75 <.text+0x152e75>
  561bdd:      	addl	$0x20, %esp
  561be0:      	jmp	0x561c3c <.text+0x160c3c>
  561be2:      	pushl	$0x5
  561be4:      	popl	%ecx
  561be5:      	movl	$0x5ef6fc, %esi         # imm = 0x5EF6FC
  561bea:      	leal	0x158(%esp), %edi
  561bf1:      	rep		movsl	(%esi), %es:(%edi)
  561bf3:      	pushl	$0xeb
  561bf8:      	leal	0x171(%esp), %eax
  561bff:      	pushl	$0x0
  561c01:      	pushl	%eax
  561c02:      	movsb	(%esi), %es:(%edi)
  561c03:      	calll	0x5c6dfc <.text+0x1c5dfc>
  561c08:      	leal	0x164(%esp), %eax
  561c0f:      	pushl	%eax
  561c10:      	pushl	$0x5f02d0               # imm = 0x5F02D0
  561c15:      	pushl	$0x5ef520               # imm = 0x5EF520
  561c1a:      	calll	0x4ba7c3 <.text+0xb97c3>
  561c1f:      	pushl	0xba7724
  561c25:      	calll	0x550103 <.text+0x14f103>
  561c2a:      	pushl	%eax
  561c2b:      	leal	0x178(%esp), %eax
  561c32:      	pushl	%eax
  561c33:      	pushl	%ebx
  561c34:      	calll	0x553e75 <.text+0x152e75>
  561c39:      	addl	$0x28, %esp
  561c3c:      	cmpl	$0x0, 0xc704f4
  561c43:      	jne	0x561c5f <.text+0x160c5f>
  561c45:      	pushl	$0x1
  561c47:      	pushl	%ebx
  561c48:      	movl	$0xe, 0xc70520
  561c52:      	calll	*0x5ce530
  561c58:      	pushl	$0x0
  561c5a:      	jmp	0x560d53 <.text+0x15fd53>
  561c5f:      	pushl	$0xc6f606               # imm = 0xC6F606
  561c64:      	calll	0x4dd8f9 <.text+0xdc8f9>
  561c69:      	movl	0xc701e4, %eax
  561c6e:      	xorl	%edi, %edi
  561c70:      	popl	%ecx
  561c71:      	cmpl	%edi, 0x10(%eax)
  561c74:      	je	0x561c80 <.text+0x160c80>
  561c76:      	movl	0x10(%eax), %ecx
  561c79:      	calll	0x551729 <.text+0x150729>
  561c7e:      	jmp	0x561c85 <.text+0x160c85>
  561c80:      	movl	$0x5d0e3a, %eax         # imm = 0x5D0E3A
  561c85:      	pushl	%eax
  561c86:      	calll	0x4dd8fe <.text+0xdc8fe>
  561c8b:      	xorl	%esi, %esi
  561c8d:      	incl	%esi
  561c8e:      	pushl	%esi
  561c8f:      	calll	0x4dd8d5 <.text+0xdc8d5>
  561c94:      	pushl	%edi
  561c95:      	calll	0x4dd8e3 <.text+0xdc8e3>
  561c9a:      	pushl	$0x5
  561c9c:      	movb	$0x1, 0xba72d3
  561ca3:      	calll	0x4788e6 <.text+0x778e6>
  561ca8:      	pushl	%esi
  561ca9:      	pushl	%ebx
  561caa:      	movl	%edi, 0xc70520
  561cb0:      	calll	0x56e64a <.text+0x16d64a>
  561cb5:      	pushl	%esi
  561cb6:      	calll	0x571075 <.text+0x170075>
  561cbb:      	addl	$0x1c, %esp
  561cbe:      	jmp	0x561361 <.text+0x160361>
  561cc3:      	xorl	%ebp, %ebp
  561cc5:      	cmpb	$0x0, 0xc6e673
  561ccc:      	je	0x561db4 <.text+0x160db4>
  561cd2:      	movl	$0x5f02bc, %esi         # imm = 0x5F02BC
  561cd7:      	leal	0x158(%esp), %edi
  561cde:      	movsl	(%esi), %es:(%edi)
  561cdf:      	movsl	(%esi), %es:(%edi)
  561ce0:      	movsl	(%esi), %es:(%edi)
  561ce1:      	movsl	(%esi), %es:(%edi)
  561ce2:      	pushl	$0xee
  561ce7:      	leal	0x16e(%esp), %eax
  561cee:      	pushl	%ebp
  561cef:      	pushl	%eax
  561cf0:      	movb	$0x1, 0xc6f4b5
  561cf7:      	movsw	(%esi), %es:(%edi)
  561cf9:      	calll	0x5c6dfc <.text+0x1c5dfc>
  561cfe:      	leal	0x164(%esp), %eax
  561d05:      	pushl	%eax
  561d06:      	pushl	$0x5f02ac               # imm = 0x5F02AC
  561d0b:      	pushl	$0x5e5b64               # imm = 0x5E5B64
  561d10:      	calll	0x4ba7c3 <.text+0xb97c3>
  561d15:      	addl	$0x18, %esp
  561d18:      	leal	0x158(%esp), %eax
  561d1f:      	pushl	%eax
  561d20:      	pushl	0x633bb4
  561d26:      	movl	$0xc6f4a0, %ecx         # imm = 0xC6F4A0
  561d2b:      	calll	0x55041d <.text+0x14f41d>
  561d30:      	pushl	$0xc6f870               # imm = 0xC6F870
  561d35:      	pushl	%ebp
  561d36:      	pushl	$0x556d3c               # imm = 0x556D3C
  561d3b:      	pushl	0xba7724
  561d41:      	movb	$0x0, 0xc6e673
  561d48:      	movb	$0x1, 0xc6e672
  561d4f:      	calll	0x5860f4 <.text+0x1850f4>
  561d54:      	addl	$0x10, %esp
  561d57:      	movl	%eax, 0xc6f4b0
  561d5c:      	cmpl	%ebp, %eax
  561d5e:      	je	0x561db4 <.text+0x160db4>
  561d60:      	calll	0x4dd321 <.text+0xdc321>
  561d65:      	pushl	$0x6
  561d67:      	popl	%ecx
  561d68:      	pushl	$0xe8
  561d6d:      	leal	0x174(%esp), %eax
  561d74:      	pushl	%ebp
  561d75:      	movl	$0x5f0294, %esi         # imm = 0x5F0294
  561d7a:      	leal	0x160(%esp), %edi
  561d81:      	pushl	%eax
  561d82:      	rep		movsl	(%esi), %es:(%edi)
  561d84:      	calll	0x5c6dfc <.text+0x1c5dfc>
  561d89:      	leal	0x164(%esp), %eax
  561d90:      	pushl	%eax
  561d91:      	pushl	$0x5f048c               # imm = 0x5F048C
  561d96:      	pushl	$0x5ef520               # imm = 0x5EF520
  561d9b:      	calll	0x4ba7c3 <.text+0xb97c3>
  561da0:      	leal	0x170(%esp), %eax
  561da7:      	pushl	%eax
  561da8:      	pushl	%ebx
  561da9:      	calll	0x553e75 <.text+0x152e75>
  561dae:      	pushl	%ebp
  561daf:      	jmp	0x560db4 <.text+0x15fdb4>
  561db4:      	cmpb	$0x0, 0xc6fd97
  561dbb:      	je	0x561e08 <.text+0x160e08>
  561dbd:      	movl	0xc701e4, %eax
  561dc2:      	movb	$0x0, 0xc6fd97
  561dc9:      	cmpl	%ebp, 0x10(%eax)
  561dcc:      	je	0x561dd8 <.text+0x160dd8>
  561dce:      	movl	0x10(%eax), %ecx
  561dd1:      	calll	0x551729 <.text+0x150729>
  561dd6:      	jmp	0x561ddd <.text+0x160ddd>
  561dd8:      	movl	$0x5d0e3a, %eax         # imm = 0x5D0E3A
  561ddd:      	pushl	0xba729c
  561de3:      	pushl	%eax
  561de4:      	movzwl	0x62aea4, %eax
  561deb:      	pushl	%eax
  561dec:      	pushl	0xba7724
  561df2:      	calll	0x54fcda <.text+0x14ecda>
  561df7:      	pushl	$0x1
  561df9:      	calll	0x571075 <.text+0x170075>
  561dfe:      	addl	$0x14, %esp
  561e01:      	movb	$0x1, 0xc6fda8
  561e08:      	pushl	0xc70100
  561e0e:      	pushl	$0xc7009c               # imm = 0xC7009C
  561e13:      	calll	0x552ab0 <.text+0x151ab0>
  561e18:      	popl	%ecx
  561e19:      	popl	%ecx
  561e1a:      	pushl	%ebp
  561e1b:      	pushl	$0x64
  561e1d:      	pushl	$0x1
  561e1f:      	pushl	%ebx
  561e20:      	calll	*0x5ce534
  561e26:      	movl	%eax, 0xc700f8
  561e2b:      	cmpl	%ebp, 0xc700c4
  561e31:      	je	0x560d63 <.text+0x15fd63>
  561e37:      	pushl	$0x1
  561e39:      	pushl	%ebx
  561e3a:      	calll	*0x5ce530
  561e40:      	jmp	0x560d63 <.text+0x15fd63>
  561e45:      	subl	$0x133, %eax            # imm = 0x133
  561e4a:      	je	0x563001 <.text+0x162001>
  561e50:      	decl	%eax
  561e51:      	je	0x563001 <.text+0x162001>
  561e57:      	pushl	$0x2
  561e59:      	popl	%ebp
  561e5a:      	subl	%ebp, %eax
  561e5c:      	je	0x563016 <.text+0x162016>
  561e62:      	subl	%ebp, %eax
  561e64:      	je	0x562fe2 <.text+0x161fe2>
  561e6a:      	subl	$0xc8, %eax
  561e6f:      	je	0x562b6a <.text+0x161b6a>
  561e75:      	decl	%eax
  561e76:      	je	0x562860 <.text+0x161860>
  561e7c:      	decl	%eax
  561e7d:      	jne	0x55eb35 <.text+0x15db35>
  561e83:      	movl	0xc701dc, %ecx
  561e89:      	movl	%esi, %edi
  561e8b:      	shrl	$0x10, %edi
  561e8e:      	movzwl	%si, %esi
  561e91:      	pushl	%edi
  561e92:      	pushl	%esi
  561e93:      	calll	0x56f3dc <.text+0x16e3dc>
  561e98:      	testl	%eax, %eax
  561e9a:      	je	0x561f46 <.text+0x160f46>
  561ea0:      	movl	0xc701e4, %ecx
  561ea6:      	calll	0x551cd5 <.text+0x150cd5>
  561eab:      	cmpb	$0x44, %al
  561ead:      	je	0x561ebe <.text+0x160ebe>
  561eaf:      	pushl	%ebx
  561eb0:      	calll	0x56e640 <.text+0x16d640>
  561eb5:      	popl	%ecx
  561eb6:      	testl	%eax, %eax
  561eb8:      	je	0x55eb35 <.text+0x15db35>
  561ebe:      	cmpb	$0x0, 0xc6fda8
  561ec5:      	je	0x55eb35 <.text+0x15db35>
  561ecb:      	movzwl	0x62aea4, %eax
  561ed2:      	movl	$0xc6fef8, %esi         # imm = 0xC6FEF8
  561ed7:      	pushl	%eax
  561ed8:      	movl	%esi, %ecx
  561eda:      	calll	0x559521 <.text+0x158521>
  561edf:      	pushl	0xba7724
  561ee5:      	calll	0x54fd98 <.text+0x14ed98>
  561eea:      	popl	%ecx
  561eeb:      	testb	%al, %al
  561eed:      	jne	0x561f0e <.text+0x160f0e>
  561eef:      	movzwl	0x62aea4, %eax
  561ef6:      	pushl	%eax
  561ef7:      	movl	%esi, %ecx
  561ef9:      	calll	0x558c66 <.text+0x157c66>
  561efe:      	testb	%al, %al
  561f00:      	je	0x561f0e <.text+0x160f0e>
  561f02:      	movb	$0x1, 0xc700c0
  561f09:      	jmp	0x55eb35 <.text+0x15db35>
  561f0e:      	movl	0xc7012c, %ecx
  561f14:      	xorl	%esi, %esi
  561f16:      	incl	%esi
  561f17:      	pushl	%esi
  561f18:      	calll	0x572935 <.text+0x171935>
  561f1d:      	movl	0xc70128, %ecx
  561f23:      	pushl	%esi
  561f24:      	calll	0x572935 <.text+0x171935>
  561f29:      	movl	0xc70198, %ecx
  561f2f:      	pushl	%esi
  561f30:      	calll	0x573f6e <.text+0x172f6e>
  561f35:      	movl	0xc70194, %ecx
  561f3b:      	pushl	%esi
  561f3c:      	calll	0x573f6e <.text+0x172f6e>
  561f41:      	jmp	0x55eb35 <.text+0x15db35>
  561f46:      	movl	0xc701e0, %ecx
  561f4c:      	pushl	%edi
  561f4d:      	pushl	%esi
  561f4e:      	calll	0x56f3dc <.text+0x16e3dc>
  561f53:      	testl	%eax, %eax
  561f55:      	je	0x561f8b <.text+0x160f8b>
  561f57:      	movl	0xc700f8, %eax
  561f5c:      	xorl	%esi, %esi
  561f5e:      	cmpl	%esi, %eax
  561f60:      	je	0x561f70 <.text+0x160f70>
  561f62:      	pushl	%eax
  561f63:      	pushl	%ebx
  561f64:      	calll	*0x5ce538
  561f6a:      	movl	%esi, 0xc700f8
  561f70:      	pushl	%esi
  561f71:      	pushl	%ebx
  561f72:      	calll	*0x5ce530
  561f78:      	calll	0x4dd321 <.text+0xdc321>
  561f7d:      	pushl	%esi
  561f7e:      	pushl	%ebx
  561f7f:      	calll	0x56e64a <.text+0x16d64a>
  561f84:      	popl	%ecx
  561f85:      	popl	%ecx
  561f86:      	jmp	0x560d63 <.text+0x15fd63>
  561f8b:      	movl	0xc701d8, %ecx
  561f91:      	pushl	%edi
  561f92:      	pushl	%esi
  561f93:      	calll	0x56f3dc <.text+0x16e3dc>
  561f98:      	testl	%eax, %eax
  561f9a:      	je	0x56200a <.text+0x16100a>
  561f9c:      	movl	0x5ce614, %esi
  561fa2:      	xorl	%ebp, %ebp
  561fa4:      	pushl	%ebp
  561fa5:      	pushl	%ebx
  561fa6:      	calll	*%esi
  561fa8:      	movl	0x5ce530, %edi
  561fae:      	pushl	%ebp
  561faf:      	pushl	%ebx
  561fb0:      	calll	*%edi
  561fb2:      	pushl	%ebp
  561fb3:      	movl	%ebp, 0xc700c4
  561fb9:      	calll	0x57be22 <.text+0x17ae22>
  561fbe:      	popl	%ecx
  561fbf:      	cmpl	%ebp, 0xc6fdc4
  561fc5:      	je	0x561fe6 <.text+0x160fe6>
  561fc7:      	movl	0xc700f8, %eax
  561fcc:      	cmpl	%ebp, %eax
  561fce:      	je	0x561fde <.text+0x160fde>
  561fd0:      	pushl	%eax
  561fd1:      	pushl	%ebx
  561fd2:      	calll	*0x5ce538
  561fd8:      	movl	%ebp, 0xc700f8
  561fde:      	calll	0x4dd321 <.text+0xdc321>
  561fe3:      	pushl	%ebp
  561fe4:      	jmp	0x561f7e <.text+0x160f7e>
  561fe6:      	pushl	0xc701e8
  561fec:      	pushl	%ebx
  561fed:      	calll	0x570cce <.text+0x16fcce>
  561ff2:      	popl	%ecx
  561ff3:      	xorl	%eax, %eax
  561ff5:      	popl	%ecx
  561ff6:      	incl	%eax
  561ff7:      	pushl	%eax
  561ff8:      	pushl	%ebx
  561ff9:      	movl	%eax, 0xc700c4
  561ffe:      	calll	*%edi
  562000:      	pushl	$0x5
  562002:      	pushl	%ebx
  562003:      	calll	*%esi
  562005:      	jmp	0x55eb35 <.text+0x15db35>
  56200a:      	movl	0xc701d4, %ecx
  562010:      	pushl	%edi
  562011:      	pushl	%esi
  562012:      	calll	0x56f3dc <.text+0x16e3dc>
  562017:      	testl	%eax, %eax
  562019:      	je	0x562050 <.text+0x161050>
  56201b:      	movl	0xc701d4, %ecx
  562021:      	pushl	$0x0
  562023:      	pushl	$0x0
  562025:      	pushl	$0x1
  562027:      	calll	0x57231f <.text+0x17131f>
  56202c:      	movzwl	0x62aea4, %eax
  562033:      	pushl	%eax
  562034:      	pushl	$0x825                  # imm = 0x825
  562039:      	pushl	%ebx
  56203a:      	calll	*0x5ce53c
  562040:      	pushl	%eax
  562041:      	movl	$0xc6fef8, %ecx         # imm = 0xC6FEF8
  562046:      	calll	0x558fd8 <.text+0x157fd8>
  56204b:      	jmp	0x55eb35 <.text+0x15db35>
  562050:      	movl	0xc701d0, %ecx
  562056:      	pushl	%edi
  562057:      	pushl	%esi
  562058:      	calll	0x56f3dc <.text+0x16e3dc>
  56205d:      	testl	%eax, %eax
  56205f:      	je	0x562081 <.text+0x161081>
  562061:      	movl	0xc701d0, %ecx
  562067:      	pushl	$0x0
  562069:      	pushl	$0x0
  56206b:      	pushl	$0x1
  56206d:      	calll	0x57231f <.text+0x17131f>
  562072:      	movl	$0xc6fef8, %ecx         # imm = 0xC6FEF8
  562077:      	calll	0x559091 <.text+0x158091>
  56207c:      	jmp	0x55eb35 <.text+0x15db35>
  562081:      	movl	0xc701cc, %ecx
  562087:      	pushl	%edi
  562088:      	pushl	%esi
  562089:      	calll	0x56f3dc <.text+0x16e3dc>
  56208e:      	testl	%eax, %eax
  562090:      	je	0x5620b2 <.text+0x1610b2>
  562092:      	movl	0xc701cc, %ecx
  562098:      	pushl	$0x0
  56209a:      	pushl	$0x0
  56209c:      	pushl	$0x1
  56209e:      	calll	0x57231f <.text+0x17131f>
  5620a3:      	movl	$0xc6fef8, %ecx         # imm = 0xC6FEF8
  5620a8:      	calll	0x55b6cc <.text+0x15a6cc>
  5620ad:      	jmp	0x55eb35 <.text+0x15db35>
  5620b2:      	movl	0xc70170, %ecx
  5620b8:      	pushl	%edi
  5620b9:      	pushl	%esi
  5620ba:      	calll	0x56f3dc <.text+0x16e3dc>
  5620bf:      	testl	%eax, %eax
  5620c1:      	je	0x5622e9 <.text+0x1612e9>
  5620c7:      	movl	0xc70170, %ecx
  5620cd:      	xorl	%edi, %edi
  5620cf:      	pushl	%edi
  5620d0:      	calll	0x56f435 <.text+0x16e435>
  5620d5:      	movl	0x5ce530, %ebp
  5620db:      	pushl	%edi
  5620dc:      	pushl	%ebx
  5620dd:      	calll	*%ebp
  5620df:      	movl	%edi, 0xc700c4
  5620e5:      	calll	0x553483 <.text+0x152483>
  5620ea:      	pushl	0xc6fdac
  5620f0:      	movl	0xc701e4, %ecx
  5620f6:      	calll	0x551e24 <.text+0x150e24>
  5620fb:      	movl	0xc701e4, %ecx
  562101:      	calll	0x551d61 <.text+0x150d61>
  562106:      	movl	0xc701e4, %ecx
  56210c:      	calll	0x5598ef <.text+0x1588ef>
  562111:      	movl	0xc701e4, %ecx
  562117:      	pushl	0x88(%ecx)
  56211d:      	calll	0x5520a2 <.text+0x1510a2>
  562122:      	movl	0xc701dc, %ecx
  562128:      	pushl	%edi
  562129:      	testl	%eax, %eax
  56212b:      	je	0x562134 <.text+0x161134>
  56212d:      	calll	0x573f6e <.text+0x172f6e>
  562132:      	jmp	0x562139 <.text+0x161139>
  562134:      	calll	0x56f435 <.text+0x16e435>
  562139:      	pushl	0xc701e8
  56213f:      	pushl	%ebx
  562140:      	calll	0x570cce <.text+0x16fcce>
  562145:      	movl	0xc6fdac, %eax
  56214a:      	imull	$0xc, %eax, %eax
  56214d:      	popl	%ecx
  56214e:      	popl	%ecx
  56214f:      	pushl	0x633a90(%eax)
  562155:      	movl	0xc70170, %ecx
  56215b:      	calll	0x56f585 <.text+0x16e585>
  562160:      	movl	0xc70170, %eax
  562165:      	addl	$0x20, %eax
  562168:      	pushl	%eax
  562169:      	movl	0xc6fdac, %eax
  56216e:      	imull	$0xc, %eax, %eax
  562171:      	pushl	0x633a94(%eax)
  562177:      	pushl	$0x5ef488               # imm = 0x5EF488
  56217c:      	calll	0x4ba7c3 <.text+0xb97c3>
  562181:      	movl	0xc70170, %ecx
  562187:      	addl	$0xc, %esp
  56218a:      	pushl	%edi
  56218b:      	calll	0x573f6e <.text+0x172f6e>
  562190:      	movl	0xc70170, %ecx
  562196:      	pushl	%edi
  562197:      	xorl	%esi, %esi
  562199:      	incl	%esi
  56219a:      	pushl	%esi
  56219b:      	pushl	%edi
  56219c:      	calll	0x57231f <.text+0x17131f>
  5621a1:      	movl	0xc701e4, %ecx
  5621a7:      	calll	0x551d18 <.text+0x150d18>
  5621ac:      	subl	%edi, %eax
  5621ae:      	je	0x56224a <.text+0x16124a>
  5621b4:      	decl	%eax
  5621b5:      	jne	0x5622da <.text+0x1612da>
  5621bb:      	movl	0xc7018c, %ecx
  5621c1:      	pushl	%esi
  5621c2:      	calll	0x56f435 <.text+0x16e435>
  5621c7:      	movl	0xc7015c, %ecx
  5621cd:      	pushl	%esi
  5621ce:      	calll	0x57403d <.text+0x17303d>
  5621d3:      	movl	0xc70188, %ecx
  5621d9:      	pushl	%esi
  5621da:      	calll	0x56f435 <.text+0x16e435>
  5621df:      	movl	0xc70158, %ecx
  5621e5:      	pushl	%esi
  5621e6:      	calll	0x57403d <.text+0x17303d>
  5621eb:      	movl	0xc701bc, %ecx
  5621f1:      	pushl	%esi
  5621f2:      	calll	0x573f6e <.text+0x172f6e>
  5621f7:      	movl	0xc70164, %ecx
  5621fd:      	pushl	%esi
  5621fe:      	calll	0x574011 <.text+0x173011>
  562203:      	movl	0xc701c8, %ecx
  562209:      	pushl	%esi
  56220a:      	calll	0x573f6e <.text+0x172f6e>
  56220f:      	movl	0xc7016c, %ecx
  562215:      	pushl	%esi
  562216:      	calll	0x574011 <.text+0x173011>
  56221b:      	movl	0xc701c0, %ecx
  562221:      	pushl	%esi
  562222:      	calll	0x573f6e <.text+0x172f6e>
  562227:      	movl	0xc70168, %ecx
  56222d:      	pushl	%esi
  56222e:      	calll	0x574011 <.text+0x173011>
  562233:      	movl	0xc70180, %ecx
  562239:      	pushl	%esi
  56223a:      	calll	0x573f6e <.text+0x172f6e>
  56223f:      	movl	0xc70150, %ecx
  562245:      	jmp	0x5622d4 <.text+0x1612d4>
  56224a:      	movl	0xc701c8, %ecx
  562250:      	pushl	%esi
  562251:      	calll	0x56f435 <.text+0x16e435>
  562256:      	movl	0xc7016c, %ecx
  56225c:      	pushl	%esi
  56225d:      	calll	0x57403d <.text+0x17303d>
  562262:      	movl	0xc701c0, %ecx
  562268:      	pushl	%esi
  562269:      	calll	0x56f435 <.text+0x16e435>
  56226e:      	movl	0xc70168, %ecx
  562274:      	pushl	%esi
  562275:      	calll	0x57403d <.text+0x17303d>
  56227a:      	movl	0xc701bc, %ecx
  562280:      	pushl	%esi
  562281:      	calll	0x56f435 <.text+0x16e435>
  562286:      	movl	0xc70164, %ecx
  56228c:      	pushl	%esi
  56228d:      	calll	0x57403d <.text+0x17303d>
  562292:      	movl	0xc70180, %ecx
  562298:      	pushl	%esi
  562299:      	calll	0x56f435 <.text+0x16e435>
  56229e:      	movl	0xc70150, %ecx
  5622a4:      	pushl	%esi
  5622a5:      	calll	0x57403d <.text+0x17303d>
  5622aa:      	movl	0xc7018c, %ecx
  5622b0:      	pushl	%esi
  5622b1:      	calll	0x573f6e <.text+0x172f6e>
  5622b6:      	movl	0xc7015c, %ecx
  5622bc:      	pushl	%esi
  5622bd:      	calll	0x574011 <.text+0x173011>
  5622c2:      	movl	0xc70188, %ecx
  5622c8:      	pushl	%esi
  5622c9:      	calll	0x573f6e <.text+0x172f6e>
  5622ce:      	movl	0xc70158, %ecx
  5622d4:      	pushl	%esi
  5622d5:      	calll	0x574011 <.text+0x173011>
  5622da:      	pushl	%esi
  5622db:      	pushl	%ebx
  5622dc:      	calll	*%ebp
  5622de:      	movl	%esi, 0xc700c4
  5622e4:      	jmp	0x55eb35 <.text+0x15db35>
  5622e9:      	movl	0xc701c8, %ecx
  5622ef:      	xorl	%ebp, %ebp
  5622f1:      	cmpl	%ebp, %ecx
  5622f3:      	je	0x562349 <.text+0x161349>
  5622f5:      	pushl	%edi
  5622f6:      	pushl	%esi
  5622f7:      	calll	0x56f3dc <.text+0x16e3dc>
  5622fc:      	testl	%eax, %eax
  5622fe:      	je	0x562349 <.text+0x161349>
  562300:      	movl	0xc701c8, %ecx
  562306:      	pushl	%ebp
  562307:      	pushl	%ebp
  562308:      	pushl	$0x1
  56230a:      	calll	0x57231f <.text+0x17131f>
  56230f:      	movl	0xc7016c, %ecx
  562315:      	calll	0x56f5b9 <.text+0x16e5b9>
  56231a:      	testl	%eax, %eax
  56231c:      	je	0x562328 <.text+0x161328>
  56231e:      	movb	$0x0, 0x62a99e
  562325:      	pushl	%ebp
  562326:      	jmp	0x562331 <.text+0x161331>
  562328:      	movb	$0x1, 0x62a99e
  56232f:      	pushl	$0x1
  562331:      	pushl	0xba7724
  562337:      	calll	0x54fe7c <.text+0x14ee7c>
  56233c:      	popl	%ecx
  56233d:      	popl	%ecx
  56233e:      	movl	0xc7016c, %ecx
  562344:      	jmp	0x562625 <.text+0x161625>
  562349:      	movl	0xc701c4, %ecx
  56234f:      	cmpl	%ebp, %ecx
  562351:      	je	0x5623d2 <.text+0x1613d2>
  562353:      	pushl	%edi
  562354:      	pushl	%esi
  562355:      	calll	0x56f3dc <.text+0x16e3dc>
  56235a:      	testl	%eax, %eax
  56235c:      	je	0x5623d2 <.text+0x1613d2>
  56235e:      	movl	0xc701c4, %ecx
  562364:      	pushl	%ebp
  562365:      	pushl	%ebp
  562366:      	pushl	$0x1
  562368:      	calll	0x57231f <.text+0x17131f>
  56236d:      	movzwl	0x62aea4, %eax
  562374:      	movl	$0xc6fef8, %esi         # imm = 0xC6FEF8
  562379:      	pushl	%eax
  56237a:      	movl	%esi, %ecx
  56237c:      	calll	0x558c66 <.text+0x157c66>
  562381:      	testb	%al, %al
  562383:      	je	0x55eb35 <.text+0x15db35>
  562389:      	pushl	0xba7724
  56238f:      	calll	0x54fd98 <.text+0x14ed98>
  562394:      	popl	%ecx
  562395:      	testb	%al, %al
  562397:      	je	0x5623aa <.text+0x1613aa>
  562399:      	pushl	%ebp
  56239a:      	pushl	0xba7724
  5623a0:      	calll	0x54fd40 <.text+0x14ed40>
  5623a5:      	popl	%ecx
  5623a6:      	popl	%ecx
  5623a7:      	pushl	%ebp
  5623a8:      	jmp	0x5623bb <.text+0x1613bb>
  5623aa:      	pushl	$0x1
  5623ac:      	pushl	0xba7724
  5623b2:      	calll	0x54fd40 <.text+0x14ed40>
  5623b7:      	popl	%ecx
  5623b8:      	popl	%ecx
  5623b9:      	pushl	$0x1
  5623bb:      	movl	0xc6fdb8, %ecx
  5623c1:      	calll	0x572529 <.text+0x171529>
  5623c6:      	movl	%esi, %ecx
  5623c8:      	calll	0x559791 <.text+0x158791>
  5623cd:      	jmp	0x55eb35 <.text+0x15db35>
  5623d2:      	movl	0xc701c0, %ecx
  5623d8:      	cmpl	%ebp, %ecx
  5623da:      	je	0x562430 <.text+0x161430>
  5623dc:      	pushl	%edi
  5623dd:      	pushl	%esi
  5623de:      	calll	0x56f3dc <.text+0x16e3dc>
  5623e3:      	testl	%eax, %eax
  5623e5:      	je	0x562430 <.text+0x161430>
  5623e7:      	movl	0xc701c0, %ecx
  5623ed:      	pushl	%ebp
  5623ee:      	pushl	%ebp
  5623ef:      	pushl	$0x1
  5623f1:      	calll	0x57231f <.text+0x17131f>
  5623f6:      	movl	0xc70168, %ecx
  5623fc:      	calll	0x56f5b9 <.text+0x16e5b9>
  562401:      	testl	%eax, %eax
  562403:      	je	0x56240f <.text+0x16140f>
  562405:      	movb	$0x0, 0x62a99f
  56240c:      	pushl	%ebp
  56240d:      	jmp	0x562418 <.text+0x161418>
  56240f:      	movb	$0x1, 0x62a99f
  562416:      	pushl	$0x1
  562418:      	pushl	0xba7724
  56241e:      	calll	0x54ff1a <.text+0x14ef1a>
  562423:      	popl	%ecx
  562424:      	popl	%ecx
  562425:      	movl	0xc70168, %ecx
  56242b:      	jmp	0x562625 <.text+0x161625>
  562430:      	movl	0xc701bc, %ecx
  562436:      	cmpl	%ebp, %ecx
  562438:      	je	0x56248e <.text+0x16148e>
  56243a:      	pushl	%edi
  56243b:      	pushl	%esi
  56243c:      	calll	0x56f3dc <.text+0x16e3dc>
  562441:      	testl	%eax, %eax
  562443:      	je	0x56248e <.text+0x16148e>
  562445:      	movl	0xc701bc, %ecx
  56244b:      	pushl	%ebp
  56244c:      	pushl	%ebp
  56244d:      	pushl	$0x1
  56244f:      	calll	0x57231f <.text+0x17131f>
  562454:      	movl	0xc70164, %ecx
  56245a:      	calll	0x56f5b9 <.text+0x16e5b9>
  56245f:      	testl	%eax, %eax
  562461:      	je	0x56246d <.text+0x16146d>
  562463:      	movb	$0x0, 0x62aa04
  56246a:      	pushl	%ebp
  56246b:      	jmp	0x562476 <.text+0x161476>
  56246d:      	movb	$0x1, 0x62aa04
  562474:      	pushl	$0x1
  562476:      	pushl	0xba7724
  56247c:      	calll	0x54ffb8 <.text+0x14efb8>
  562481:      	popl	%ecx
  562482:      	popl	%ecx
  562483:      	movl	0xc70164, %ecx
  562489:      	jmp	0x562625 <.text+0x161625>
  56248e:      	movl	0xc70190, %ecx
  562494:      	pushl	%edi
  562495:      	pushl	%esi
  562496:      	calll	0x56f3dc <.text+0x16e3dc>
  56249b:      	testl	%eax, %eax
  56249d:      	je	0x56252f <.text+0x16152f>
  5624a3:      	movl	0xc70190, %ecx
  5624a9:      	pushl	%ebp
  5624aa:      	pushl	%ebp
  5624ab:      	pushl	$0x1
  5624ad:      	calll	0x57231f <.text+0x17131f>
  5624b2:      	movl	0xc70160, %ecx
  5624b8:      	calll	0x5725e0 <.text+0x1715e0>
  5624bd:      	movl	0xc701e4, %ecx
  5624c3:      	pushl	0x88(%ecx)
  5624c9:      	calll	0x5520d1 <.text+0x1510d1>
  5624ce:      	movl	0xc70160, %ecx
  5624d4:      	movl	%eax, %esi
  5624d6:      	calll	0x56f59e <.text+0x16e59e>
  5624db:      	cmpl	%esi, %eax
  5624dd:      	jle	0x5624ec <.text+0x1614ec>
  5624df:      	movl	0xc70160, %ecx
  5624e5:      	pushl	$0x2
  5624e7:      	calll	0x572575 <.text+0x171575>
  5624ec:      	movl	0xc70160, %ecx
  5624f2:      	calll	0x56f59e <.text+0x16e59e>
  5624f7:      	pushl	%eax
  5624f8:      	pushl	0xba7724
  5624fe:      	calll	0x55016c <.text+0x14f16c>
  562503:      	popl	%ecx
  562504:      	popl	%ecx
  562505:      	movl	0xc70160, %ecx
  56250b:      	calll	0x56f59e <.text+0x16e59e>
  562510:      	cmpl	$0x6, %eax
  562513:      	jle	0x55eb35 <.text+0x15db35>
  562519:      	pushl	$0x633c18               # imm = 0x633C18
  56251e:      	pushl	$0xc6f4a0               # imm = 0xC6F4A0
  562523:      	calll	0x555cce <.text+0x154cce>
  562528:      	popl	%ecx
  562529:      	popl	%ecx
  56252a:      	jmp	0x55eb35 <.text+0x15db35>
  56252f:      	movl	0xc7018c, %ecx
  562535:      	pushl	%edi
  562536:      	pushl	%esi
  562537:      	calll	0x56f3dc <.text+0x16e3dc>
  56253c:      	testl	%eax, %eax
  56253e:      	je	0x56255a <.text+0x16155a>
  562540:      	movl	0xc7018c, %ecx
  562546:      	pushl	%ebp
  562547:      	pushl	%ebp
  562548:      	pushl	$0x1
  56254a:      	calll	0x57231f <.text+0x17131f>
  56254f:      	movl	0xc7015c, %ecx
  562555:      	jmp	0x562625 <.text+0x161625>
  56255a:      	movl	0xc70188, %ecx
  562560:      	pushl	%edi
  562561:      	pushl	%esi
  562562:      	calll	0x56f3dc <.text+0x16e3dc>
  562567:      	testl	%eax, %eax
  562569:      	je	0x562585 <.text+0x161585>
  56256b:      	movl	0xc70188, %ecx
  562571:      	pushl	%ebp
  562572:      	pushl	%ebp
  562573:      	pushl	$0x1
  562575:      	calll	0x57231f <.text+0x17131f>
  56257a:      	movl	0xc70158, %ecx
  562580:      	jmp	0x562625 <.text+0x161625>
  562585:      	movl	0xc70184, %ecx
  56258b:      	pushl	%edi
  56258c:      	pushl	%esi
  56258d:      	calll	0x56f3dc <.text+0x16e3dc>
  562592:      	testl	%eax, %eax
  562594:      	jne	0x55eb35 <.text+0x15db35>
  56259a:      	movl	0xc7017c, %ecx
  5625a0:      	pushl	%edi
  5625a1:      	pushl	%esi
  5625a2:      	calll	0x56f3dc <.text+0x16e3dc>
  5625a7:      	testl	%eax, %eax
  5625a9:      	je	0x5625c2 <.text+0x1615c2>
  5625ab:      	movl	0xc7017c, %ecx
  5625b1:      	pushl	%ebp
  5625b2:      	pushl	%ebp
  5625b3:      	pushl	$0x1
  5625b5:      	calll	0x57231f <.text+0x17131f>
  5625ba:      	movl	0xc7014c, %ecx
  5625c0:      	jmp	0x562625 <.text+0x161625>
  5625c2:      	movl	0xc70180, %ecx
  5625c8:      	pushl	%edi
  5625c9:      	pushl	%esi
  5625ca:      	calll	0x56f3dc <.text+0x16e3dc>
  5625cf:      	testl	%eax, %eax
  5625d1:      	je	0x5625ea <.text+0x1615ea>
  5625d3:      	movl	0xc70180, %ecx
  5625d9:      	pushl	%ebp
  5625da:      	pushl	%ebp
  5625db:      	pushl	$0x1
  5625dd:      	calll	0x57231f <.text+0x17131f>
  5625e2:      	movl	0xc70150, %ecx
  5625e8:      	jmp	0x562625 <.text+0x161625>
  5625ea:      	movl	0xc70178, %ecx
  5625f0:      	pushl	%edi
  5625f1:      	pushl	%esi
  5625f2:      	calll	0x56f3dc <.text+0x16e3dc>
  5625f7:      	testl	%eax, %eax
  5625f9:      	jne	0x55eb35 <.text+0x15db35>
  5625ff:      	movl	0xc70174, %ecx
  562605:      	pushl	%edi
  562606:      	pushl	%esi
  562607:      	calll	0x56f3dc <.text+0x16e3dc>
  56260c:      	testl	%eax, %eax
  56260e:      	je	0x56262f <.text+0x16162f>
  562610:      	movl	0xc70174, %ecx
  562616:      	pushl	%ebp
  562617:      	pushl	%ebp
  562618:      	pushl	$0x1
  56261a:      	calll	0x57231f <.text+0x17131f>
  56261f:      	movl	0xc70148, %ecx
  562625:      	calll	0x5725e0 <.text+0x1715e0>
  56262a:      	jmp	0x55eb35 <.text+0x15db35>
  56262f:      	movl	0xc701a8, %ecx
  562635:      	pushl	%edi
  562636:      	pushl	%esi
  562637:      	calll	0x56f3dc <.text+0x16e3dc>
  56263c:      	testl	%eax, %eax
  56263e:      	je	0x562653 <.text+0x161653>
  562640:      	movl	0xc701a8, %ecx
  562646:      	pushl	%ebp
  562647:      	pushl	%ebp
  562648:      	pushl	$0x1
  56264a:      	calll	0x57231f <.text+0x17131f>
  56264f:      	pushl	%ebp
  562650:      	pushl	%ebp
  562651:      	jmp	0x562676 <.text+0x161676>
  562653:      	movl	0xc701a4, %ecx
  562659:      	pushl	%edi
  56265a:      	pushl	%esi
  56265b:      	calll	0x56f3dc <.text+0x16e3dc>
  562660:      	testl	%eax, %eax
  562662:      	je	0x56268c <.text+0x16168c>
  562664:      	movl	0xc701a4, %ecx
  56266a:      	pushl	%ebp
  56266b:      	pushl	%ebp
  56266c:      	pushl	$0x1
  56266e:      	calll	0x57231f <.text+0x17131f>
  562673:      	pushl	%ebp
  562674:      	pushl	$0x1
  562676:      	pushl	$0xb5
  56267b:      	pushl	$0x826                  # imm = 0x826
  562680:      	pushl	%ebx
  562681:      	calll	*0x5ce52c
  562687:      	jmp	0x55eb35 <.text+0x15db35>
  56268c:      	movl	0xc701a0, %ecx
  562692:      	pushl	%edi
  562693:      	pushl	%esi
  562694:      	calll	0x56f3dc <.text+0x16e3dc>
  562699:      	testl	%eax, %eax
  56269b:      	je	0x5626bb <.text+0x1616bb>
  56269d:      	movl	0xc701a0, %ecx
  5626a3:      	pushl	%ebp
  5626a4:      	pushl	%ebp
  5626a5:      	pushl	$0x1
  5626a7:      	calll	0x57231f <.text+0x17131f>
  5626ac:      	movl	$0xc6fef8, %ecx         # imm = 0xC6FEF8
  5626b1:      	calll	0x550b6b <.text+0x14fb6b>
  5626b6:      	jmp	0x55eb35 <.text+0x15db35>
  5626bb:      	movl	0xc7019c, %ecx
  5626c1:      	pushl	%edi
  5626c2:      	pushl	%esi
  5626c3:      	calll	0x56f3dc <.text+0x16e3dc>
  5626c8:      	testl	%eax, %eax
  5626ca:      	je	0x5626ea <.text+0x1616ea>
  5626cc:      	movl	0xc7019c, %ecx
  5626d2:      	pushl	%ebp
  5626d3:      	pushl	%ebp
  5626d4:      	pushl	$0x1
  5626d6:      	calll	0x57231f <.text+0x17131f>
  5626db:      	movl	$0xc6fef8, %ecx         # imm = 0xC6FEF8
  5626e0:      	calll	0x550ba1 <.text+0x14fba1>
  5626e5:      	jmp	0x55eb35 <.text+0x15db35>
  5626ea:      	movl	0xc701b8, %ecx
  5626f0:      	pushl	%edi
  5626f1:      	pushl	%esi
  5626f2:      	calll	0x56f3dc <.text+0x16e3dc>
  5626f7:      	testl	%eax, %eax
  5626f9:      	je	0x56271a <.text+0x16171a>
  5626fb:      	movl	0xc701b8, %ecx
  562701:      	pushl	%ebp
  562702:      	pushl	%ebp
  562703:      	pushl	$0x1
  562705:      	calll	0x57231f <.text+0x17131f>
  56270a:      	movl	0xc701e4, %ecx
  562710:      	calll	0x551f77 <.text+0x150f77>
  562715:      	jmp	0x55eb35 <.text+0x15db35>
  56271a:      	movl	0xc701b4, %ecx
  562720:      	pushl	%edi
  562721:      	pushl	%esi
  562722:      	calll	0x56f3dc <.text+0x16e3dc>
  562727:      	testl	%eax, %eax
  562729:      	je	0x56274a <.text+0x16174a>
  56272b:      	movl	0xc701b4, %ecx
  562731:      	pushl	%ebp
  562732:      	pushl	%ebp
  562733:      	pushl	$0x1
  562735:      	calll	0x57231f <.text+0x17131f>
  56273a:      	movl	0xc701e4, %ecx
  562740:      	calll	0x551fa4 <.text+0x150fa4>
  562745:      	jmp	0x55eb35 <.text+0x15db35>
  56274a:      	movl	0xc701b0, %ecx
  562750:      	pushl	%edi
  562751:      	pushl	%esi
  562752:      	calll	0x56f3dc <.text+0x16e3dc>
  562757:      	testl	%eax, %eax
  562759:      	je	0x562777 <.text+0x161777>
  56275b:      	movl	0xc701b0, %ecx
  562761:      	pushl	%ebp
  562762:      	pushl	%ebp
  562763:      	pushl	$0x1
  562765:      	calll	0x57231f <.text+0x17131f>
  56276a:      	movl	0xc701e4, %ecx
  562770:      	calll	0x556b6b <.text+0x155b6b>
  562775:      	jmp	0x5627a2 <.text+0x1617a2>
  562777:      	movl	0xc701ac, %ecx
  56277d:      	pushl	%edi
  56277e:      	pushl	%esi
  56277f:      	calll	0x56f3dc <.text+0x16e3dc>
  562784:      	testl	%eax, %eax
  562786:      	je	0x5627b4 <.text+0x1617b4>
  562788:      	movl	0xc701ac, %ecx
  56278e:      	pushl	%ebp
  56278f:      	pushl	%ebp
  562790:      	pushl	$0x1
  562792:      	calll	0x57231f <.text+0x17131f>
  562797:      	movl	0xc701e4, %ecx
  56279d:      	calll	0x556b82 <.text+0x155b82>
  5627a2:      	movl	0xc70104, %ecx
  5627a8:      	pushl	$0x1
  5627aa:      	calll	0x57059e <.text+0x16f59e>
  5627af:      	jmp	0x55eb35 <.text+0x15db35>
  5627b4:      	movl	0xc70194, %ecx
  5627ba:      	pushl	%edi
  5627bb:      	pushl	%esi
  5627bc:      	calll	0x56f3dc <.text+0x16e3dc>
  5627c1:      	testl	%eax, %eax
  5627c3:      	je	0x55eb35 <.text+0x15db35>
  5627c9:      	movzwl	0x62aea4, %eax
  5627d0:      	pushl	%eax
  5627d1:      	movl	$0xc6fef8, %ecx         # imm = 0xC6FEF8
  5627d6:      	calll	0x559577 <.text+0x158577>
  5627db:      	movl	0xc70194, %ecx
  5627e1:      	pushl	%ebp
  5627e2:      	xorl	%esi, %esi
  5627e4:      	pushl	%ebp
  5627e5:      	incl	%esi
  5627e6:      	pushl	%esi
  5627e7:      	calll	0x57231f <.text+0x17131f>
  5627ec:      	movl	0xc70194, %ecx
  5627f2:      	pushl	%esi
  5627f3:      	calll	0x56f435 <.text+0x16e435>
  5627f8:      	movl	0xc70198, %ecx
  5627fe:      	pushl	%esi
  5627ff:      	calll	0x56f435 <.text+0x16e435>
  562804:      	movl	0xc70194, %ecx
  56280a:      	calll	0x5722e9 <.text+0x1712e9>
  56280f:      	movl	0xc70198, %ecx
  562815:      	calll	0x5722e9 <.text+0x1712e9>
  56281a:      	movl	0xc7012c, %ecx
  562820:      	pushl	%esi
  562821:      	calll	0x57295a <.text+0x17195a>
  562826:      	movl	0xc70128, %ecx
  56282c:      	pushl	%esi
  56282d:      	calll	0x57295a <.text+0x17195a>
  562832:      	pushl	%ebp
  562833:      	leal	0x40(%esp), %eax
  562837:      	pushl	%eax
  562838:      	pushl	%ebx
  562839:      	movl	$0x96, 0x48(%esp)
  562841:      	movl	%ebp, 0x4c(%esp)
  562845:      	movl	$0x1f4, 0x50(%esp)      # imm = 0x1F4
  56284d:      	movl	$0x1e, 0x54(%esp)
  562855:      	calll	*0x5ce550
  56285b:      	jmp	0x55eb35 <.text+0x15db35>
  562860:      	movl	0xc701dc, %ecx
  562866:      	movl	%esi, %edi
  562868:      	shrl	$0x10, %edi
  56286b:      	movzwl	%si, %esi
  56286e:      	pushl	%edi
  56286f:      	pushl	%esi
  562870:      	calll	0x56f3dc <.text+0x16e3dc>
  562875:      	testl	%eax, %eax
  562877:      	je	0x562886 <.text+0x161886>
  562879:      	movl	0xc701dc, %ecx
  56287f:      	pushl	$0x0
  562881:      	jmp	0x562b5d <.text+0x161b5d>
  562886:      	movl	0xc701e0, %ecx
  56288c:      	pushl	%edi
  56288d:      	pushl	%esi
  56288e:      	calll	0x56f3dc <.text+0x16e3dc>
  562893:      	testl	%eax, %eax
  562895:      	je	0x5628a4 <.text+0x1618a4>
  562897:      	movl	0xc701e0, %ecx
  56289d:      	pushl	$0x0
  56289f:      	jmp	0x562b5d <.text+0x161b5d>
  5628a4:      	movl	0xc701d8, %ecx
  5628aa:      	pushl	%edi
  5628ab:      	pushl	%esi
  5628ac:      	calll	0x56f3dc <.text+0x16e3dc>
  5628b1:      	testl	%eax, %eax
  5628b3:      	je	0x5628c2 <.text+0x1618c2>
  5628b5:      	movl	0xc701d8, %ecx
  5628bb:      	pushl	$0x0
  5628bd:      	jmp	0x562b5d <.text+0x161b5d>
  5628c2:      	movl	0xc701d4, %ecx
  5628c8:      	pushl	%edi
  5628c9:      	pushl	%esi
  5628ca:      	calll	0x56f3dc <.text+0x16e3dc>
  5628cf:      	testl	%eax, %eax
  5628d1:      	je	0x5628e0 <.text+0x1618e0>
  5628d3:      	movl	0xc701d4, %ecx
  5628d9:      	pushl	$0x0
  5628db:      	jmp	0x562b5d <.text+0x161b5d>
  5628e0:      	movl	0xc701d0, %ecx
  5628e6:      	pushl	%edi
  5628e7:      	pushl	%esi
  5628e8:      	calll	0x56f3dc <.text+0x16e3dc>
  5628ed:      	testl	%eax, %eax
  5628ef:      	je	0x5628fe <.text+0x1618fe>
  5628f1:      	movl	0xc701d0, %ecx
  5628f7:      	pushl	$0x0
  5628f9:      	jmp	0x562b5d <.text+0x161b5d>
  5628fe:      	movl	0xc701cc, %ecx
  562904:      	pushl	%edi
  562905:      	pushl	%esi
  562906:      	calll	0x56f3dc <.text+0x16e3dc>
  56290b:      	testl	%eax, %eax
  56290d:      	je	0x56291c <.text+0x16191c>
  56290f:      	movl	0xc701cc, %ecx
  562915:      	pushl	$0x0
  562917:      	jmp	0x562b5d <.text+0x161b5d>
  56291c:      	movl	0xc701c8, %ecx
  562922:      	xorl	%ebx, %ebx
  562924:      	cmpl	%ebx, %ecx
  562926:      	je	0x56293e <.text+0x16193e>
  562928:      	pushl	%edi
  562929:      	pushl	%esi
  56292a:      	calll	0x56f3dc <.text+0x16e3dc>
  56292f:      	testl	%eax, %eax
  562931:      	je	0x56293e <.text+0x16193e>
  562933:      	movl	0xc701c8, %ecx
  562939:      	jmp	0x562b5c <.text+0x161b5c>
  56293e:      	movl	0xc701c4, %ecx
  562944:      	cmpl	%ebx, %ecx
  562946:      	je	0x56295e <.text+0x16195e>
  562948:      	pushl	%edi
  562949:      	pushl	%esi
  56294a:      	calll	0x56f3dc <.text+0x16e3dc>
  56294f:      	testl	%eax, %eax
  562951:      	je	0x56295e <.text+0x16195e>
  562953:      	movl	0xc701c4, %ecx
  562959:      	jmp	0x562b5c <.text+0x161b5c>
  56295e:      	movl	0xc701c0, %ecx
  562964:      	cmpl	%ebx, %ecx
  562966:      	je	0x56297e <.text+0x16197e>
  562968:      	pushl	%edi
  562969:      	pushl	%esi
  56296a:      	calll	0x56f3dc <.text+0x16e3dc>
  56296f:      	testl	%eax, %eax
  562971:      	je	0x56297e <.text+0x16197e>
  562973:      	movl	0xc701c0, %ecx
  562979:      	jmp	0x562b5c <.text+0x161b5c>
  56297e:      	movl	0xc701bc, %ecx
  562984:      	cmpl	%ebx, %ecx
  562986:      	je	0x56299e <.text+0x16199e>
  562988:      	pushl	%edi
  562989:      	pushl	%esi
  56298a:      	calll	0x56f3dc <.text+0x16e3dc>
  56298f:      	testl	%eax, %eax
  562991:      	je	0x56299e <.text+0x16199e>
  562993:      	movl	0xc701bc, %ecx
  562999:      	jmp	0x562b5c <.text+0x161b5c>
  56299e:      	movl	0xc70190, %ecx
  5629a4:      	pushl	%edi
  5629a5:      	pushl	%esi
  5629a6:      	calll	0x56f3dc <.text+0x16e3dc>
  5629ab:      	testl	%eax, %eax
  5629ad:      	je	0x5629ba <.text+0x1619ba>
  5629af:      	movl	0xc70190, %ecx
  5629b5:      	jmp	0x562b5c <.text+0x161b5c>
  5629ba:      	movl	0xc7018c, %ecx
  5629c0:      	pushl	%edi
  5629c1:      	pushl	%esi
  5629c2:      	calll	0x56f3dc <.text+0x16e3dc>
  5629c7:      	testl	%eax, %eax
  5629c9:      	je	0x5629d6 <.text+0x1619d6>
  5629cb:      	movl	0xc7018c, %ecx
  5629d1:      	jmp	0x562b5c <.text+0x161b5c>
  5629d6:      	movl	0xc70188, %ecx
  5629dc:      	pushl	%edi
  5629dd:      	pushl	%esi
  5629de:      	calll	0x56f3dc <.text+0x16e3dc>
  5629e3:      	testl	%eax, %eax
  5629e5:      	je	0x5629f2 <.text+0x1619f2>
  5629e7:      	movl	0xc70188, %ecx
  5629ed:      	jmp	0x562b5c <.text+0x161b5c>
  5629f2:      	movl	0xc70184, %ecx
  5629f8:      	pushl	%edi
  5629f9:      	pushl	%esi
  5629fa:      	calll	0x56f3dc <.text+0x16e3dc>
  5629ff:      	testl	%eax, %eax
  562a01:      	jne	0x55eb35 <.text+0x15db35>
  562a07:      	movl	0xc70180, %ecx
  562a0d:      	pushl	%edi
  562a0e:      	pushl	%esi
  562a0f:      	calll	0x56f3dc <.text+0x16e3dc>
  562a14:      	testl	%eax, %eax
  562a16:      	je	0x562a23 <.text+0x161a23>
  562a18:      	movl	0xc70180, %ecx
  562a1e:      	jmp	0x562b5c <.text+0x161b5c>
  562a23:      	movl	0xc7017c, %ecx
  562a29:      	pushl	%edi
  562a2a:      	pushl	%esi
  562a2b:      	calll	0x56f3dc <.text+0x16e3dc>
  562a30:      	testl	%eax, %eax
  562a32:      	je	0x562a3f <.text+0x161a3f>
  562a34:      	movl	0xc7017c, %ecx
  562a3a:      	jmp	0x562b5c <.text+0x161b5c>
  562a3f:      	movl	0xc70178, %ecx
  562a45:      	pushl	%edi
  562a46:      	pushl	%esi
  562a47:      	calll	0x56f3dc <.text+0x16e3dc>
  562a4c:      	testl	%eax, %eax
  562a4e:      	jne	0x55eb35 <.text+0x15db35>
  562a54:      	movl	0xc70174, %ecx
  562a5a:      	pushl	%edi
  562a5b:      	pushl	%esi
  562a5c:      	calll	0x56f3dc <.text+0x16e3dc>
  562a61:      	testl	%eax, %eax
  562a63:      	je	0x562a70 <.text+0x161a70>
  562a65:      	movl	0xc70174, %ecx
  562a6b:      	jmp	0x562b5c <.text+0x161b5c>
  562a70:      	movl	0xc701b8, %ecx
  562a76:      	pushl	%edi
  562a77:      	pushl	%esi
  562a78:      	calll	0x56f3dc <.text+0x16e3dc>
  562a7d:      	testl	%eax, %eax
  562a7f:      	je	0x562a8c <.text+0x161a8c>
  562a81:      	movl	0xc701b8, %ecx
  562a87:      	jmp	0x562b5c <.text+0x161b5c>
  562a8c:      	movl	0xc701b4, %ecx
  562a92:      	pushl	%edi
  562a93:      	pushl	%esi
  562a94:      	calll	0x56f3dc <.text+0x16e3dc>
  562a99:      	testl	%eax, %eax
  562a9b:      	je	0x562aa8 <.text+0x161aa8>
  562a9d:      	movl	0xc701b4, %ecx
  562aa3:      	jmp	0x562b5c <.text+0x161b5c>
  562aa8:      	movl	0xc701b0, %ecx
  562aae:      	pushl	%edi
  562aaf:      	pushl	%esi
  562ab0:      	calll	0x56f3dc <.text+0x16e3dc>
  562ab5:      	testl	%eax, %eax
  562ab7:      	je	0x562ac4 <.text+0x161ac4>
  562ab9:      	movl	0xc701b0, %ecx
  562abf:      	jmp	0x562b5c <.text+0x161b5c>
  562ac4:      	movl	0xc701ac, %ecx
  562aca:      	pushl	%edi
  562acb:      	pushl	%esi
  562acc:      	calll	0x56f3dc <.text+0x16e3dc>
  562ad1:      	testl	%eax, %eax
  562ad3:      	je	0x562add <.text+0x161add>
  562ad5:      	movl	0xc701ac, %ecx
  562adb:      	jmp	0x562b5c <.text+0x161b5c>
  562add:      	movl	0xc701a8, %ecx
  562ae3:      	pushl	%edi
  562ae4:      	pushl	%esi
  562ae5:      	calll	0x56f3dc <.text+0x16e3dc>
  562aea:      	testl	%eax, %eax
  562aec:      	je	0x562af6 <.text+0x161af6>
  562aee:      	movl	0xc701a8, %ecx
  562af4:      	jmp	0x562b5c <.text+0x161b5c>
  562af6:      	movl	0xc701a4, %ecx
  562afc:      	pushl	%edi
  562afd:      	pushl	%esi
  562afe:      	calll	0x56f3dc <.text+0x16e3dc>
  562b03:      	testl	%eax, %eax
  562b05:      	je	0x562b0f <.text+0x161b0f>
  562b07:      	movl	0xc701a4, %ecx
  562b0d:      	jmp	0x562b5c <.text+0x161b5c>
  562b0f:      	movl	0xc701a0, %ecx
  562b15:      	pushl	%edi
  562b16:      	pushl	%esi
  562b17:      	calll	0x56f3dc <.text+0x16e3dc>
  562b1c:      	testl	%eax, %eax
  562b1e:      	je	0x562b28 <.text+0x161b28>
  562b20:      	movl	0xc701a0, %ecx
  562b26:      	jmp	0x562b5c <.text+0x161b5c>
  562b28:      	movl	0xc7019c, %ecx
  562b2e:      	pushl	%edi
  562b2f:      	pushl	%esi
  562b30:      	calll	0x56f3dc <.text+0x16e3dc>
  562b35:      	testl	%eax, %eax
  562b37:      	je	0x562b41 <.text+0x161b41>
  562b39:      	movl	0xc7019c, %ecx
  562b3f:      	jmp	0x562b5c <.text+0x161b5c>
  562b41:      	movl	0xc70194, %ecx
  562b47:      	pushl	%edi
  562b48:      	pushl	%esi
  562b49:      	calll	0x56f3dc <.text+0x16e3dc>
  562b4e:      	testl	%eax, %eax
  562b50:      	je	0x55eb35 <.text+0x15db35>
  562b56:      	movl	0xc70194, %ecx
  562b5c:      	pushl	%ebx
  562b5d:      	pushl	$0x1
  562b5f:      	pushl	%ebp
  562b60:      	calll	0x57231f <.text+0x17131f>
  562b65:      	jmp	0x55eb35 <.text+0x15db35>
  562b6a:      	movl	0xc701e0, %ecx
  562b70:      	xorl	%ebp, %ebp
  562b72:      	pushl	%ebp
  562b73:      	xorl	%ebx, %ebx
  562b75:      	movl	%esi, %edi
  562b77:      	incl	%ebx
  562b78:      	pushl	%ebx
  562b79:      	shrl	$0x10, %edi
  562b7c:      	movzwl	%si, %esi
  562b7f:      	pushl	%edi
  562b80:      	pushl	%esi
  562b81:      	calll	0x56f3dc <.text+0x16e3dc>
  562b86:      	movl	0xc701e0, %ecx
  562b8c:      	pushl	%eax
  562b8d:      	calll	0x57231f <.text+0x17131f>
  562b92:      	movl	0xc701dc, %ecx
  562b98:      	pushl	%ebp
  562b99:      	pushl	%ebx
  562b9a:      	pushl	%edi
  562b9b:      	pushl	%esi
  562b9c:      	calll	0x56f3dc <.text+0x16e3dc>
  562ba1:      	movl	0xc701dc, %ecx
  562ba7:      	pushl	%eax
  562ba8:      	calll	0x57231f <.text+0x17131f>
  562bad:      	movl	0xc701d8, %ecx
  562bb3:      	pushl	%ebp
  562bb4:      	pushl	%ebx
  562bb5:      	pushl	%edi
  562bb6:      	pushl	%esi
  562bb7:      	calll	0x56f3dc <.text+0x16e3dc>
  562bbc:      	movl	0xc701d8, %ecx
  562bc2:      	pushl	%eax
  562bc3:      	calll	0x57231f <.text+0x17131f>
  562bc8:      	movl	0xc701d0, %ecx
  562bce:      	pushl	%ebp
  562bcf:      	pushl	%ebx
  562bd0:      	pushl	%edi
  562bd1:      	pushl	%esi
  562bd2:      	calll	0x56f3dc <.text+0x16e3dc>
  562bd7:      	movl	0xc701d0, %ecx
  562bdd:      	pushl	%eax
  562bde:      	calll	0x57231f <.text+0x17131f>
  562be3:      	pushl	$0x5f05e4               # imm = 0x5F05E4
  562be8:      	pushl	$0x5f0278               # imm = 0x5F0278
  562bed:      	pushl	0xc70100
  562bf3:      	pushl	0xc701d0
  562bf9:      	calll	0x572c2d <.text+0x171c2d>
  562bfe:      	movl	0xc701cc, %ecx
  562c04:      	addl	$0x10, %esp
  562c07:      	pushl	%ebp
  562c08:      	pushl	%ebx
  562c09:      	pushl	%edi
  562c0a:      	pushl	%esi
  562c0b:      	calll	0x56f3dc <.text+0x16e3dc>
  562c10:      	movl	0xc701cc, %ecx
  562c16:      	pushl	%eax
  562c17:      	calll	0x57231f <.text+0x17131f>
  562c1c:      	pushl	$0x5f05ec               # imm = 0x5F05EC
  562c21:      	pushl	$0x5f0260               # imm = 0x5F0260
  562c26:      	pushl	0xc70100
  562c2c:      	pushl	0xc701cc
  562c32:      	calll	0x572c2d <.text+0x171c2d>
  562c37:      	movl	0xc701d4, %ecx
  562c3d:      	addl	$0x10, %esp
  562c40:      	pushl	%ebp
  562c41:      	pushl	%ebx
  562c42:      	pushl	%edi
  562c43:      	pushl	%esi
  562c44:      	calll	0x56f3dc <.text+0x16e3dc>
  562c49:      	movl	0xc701d4, %ecx
  562c4f:      	pushl	%eax
  562c50:      	calll	0x57231f <.text+0x17131f>
  562c55:      	pushl	$0x5f05f4               # imm = 0x5F05F4
  562c5a:      	pushl	$0x5f0240               # imm = 0x5F0240
  562c5f:      	pushl	0xc70100
  562c65:      	pushl	0xc701d4
  562c6b:      	calll	0x572c2d <.text+0x171c2d>
  562c70:      	addl	$0x10, %esp
  562c73:      	pushl	%ebp
  562c74:      	pushl	%ebx
  562c75:      	pushl	%edi
  562c76:      	movl	0xc701c8, %ecx
  562c7c:      	pushl	%esi
  562c7d:      	calll	0x56f3dc <.text+0x16e3dc>
  562c82:      	movl	0xc701c8, %ecx
  562c88:      	pushl	%eax
  562c89:      	calll	0x57231f <.text+0x17131f>
  562c8e:      	pushl	$0x5f0238               # imm = 0x5F0238
  562c93:      	pushl	$0x5f0210               # imm = 0x5F0210
  562c98:      	pushl	0xc70100
  562c9e:      	pushl	0xc701c8
  562ca4:      	calll	0x572c2d <.text+0x171c2d>
  562ca9:      	movl	0xc701c4, %ecx
  562caf:      	addl	$0x10, %esp
  562cb2:      	pushl	%ebp
  562cb3:      	pushl	%ebx
  562cb4:      	pushl	%edi
  562cb5:      	pushl	%esi
  562cb6:      	calll	0x56f3dc <.text+0x16e3dc>
  562cbb:      	movl	0xc701c4, %ecx
  562cc1:      	pushl	%eax
  562cc2:      	calll	0x57231f <.text+0x17131f>
  562cc7:      	pushl	$0x5f0208               # imm = 0x5F0208
  562ccc:      	pushl	$0x5f01e4               # imm = 0x5F01E4
  562cd1:      	pushl	0xc70100
  562cd7:      	pushl	0xc701c4
  562cdd:      	calll	0x572c2d <.text+0x171c2d>
  562ce2:      	movl	0xc701c0, %ecx
  562ce8:      	addl	$0x10, %esp
  562ceb:      	pushl	%ebp
  562cec:      	pushl	%ebx
  562ced:      	pushl	%edi
  562cee:      	pushl	%esi
  562cef:      	calll	0x56f3dc <.text+0x16e3dc>
  562cf4:      	movl	0xc701c0, %ecx
  562cfa:      	pushl	%eax
  562cfb:      	calll	0x57231f <.text+0x17131f>
  562d00:      	pushl	$0x5f01dc               # imm = 0x5F01DC
  562d05:      	pushl	$0x5f01bc               # imm = 0x5F01BC
  562d0a:      	pushl	0xc70100
  562d10:      	pushl	0xc701c0
  562d16:      	calll	0x572c2d <.text+0x171c2d>
  562d1b:      	movl	0xc701bc, %ecx
  562d21:      	addl	$0x10, %esp
  562d24:      	pushl	%ebp
  562d25:      	pushl	%ebx
  562d26:      	pushl	%edi
  562d27:      	pushl	%esi
  562d28:      	calll	0x56f3dc <.text+0x16e3dc>
  562d2d:      	movl	0xc701bc, %ecx
  562d33:      	pushl	%eax
  562d34:      	calll	0x57231f <.text+0x17131f>
  562d39:      	pushl	$0x5ecda4               # imm = 0x5ECDA4
  562d3e:      	pushl	$0x5f01a8               # imm = 0x5F01A8
  562d43:      	pushl	0xc70100
  562d49:      	pushl	0xc701bc
  562d4f:      	calll	0x572c2d <.text+0x171c2d>
  562d54:      	movl	0xc70190, %ecx
  562d5a:      	addl	$0x10, %esp
  562d5d:      	pushl	%ebp
  562d5e:      	pushl	%ebx
  562d5f:      	pushl	%edi
  562d60:      	pushl	%esi
  562d61:      	calll	0x56f3dc <.text+0x16e3dc>
  562d66:      	movl	0xc70190, %ecx
  562d6c:      	pushl	%eax
  562d6d:      	calll	0x57231f <.text+0x17131f>
  562d72:      	pushl	$0x5f01a0               # imm = 0x5F01A0
  562d77:      	pushl	$0x5f0184               # imm = 0x5F0184
  562d7c:      	pushl	0xc70100
  562d82:      	pushl	0xc70190
  562d88:      	calll	0x572c2d <.text+0x171c2d>
  562d8d:      	movl	0xc7018c, %ecx
  562d93:      	addl	$0x10, %esp
  562d96:      	pushl	%ebp
  562d97:      	pushl	%ebx
  562d98:      	pushl	%edi
  562d99:      	pushl	%esi
  562d9a:      	calll	0x56f3dc <.text+0x16e3dc>
  562d9f:      	movl	0xc7018c, %ecx
  562da5:      	pushl	%eax
  562da6:      	calll	0x57231f <.text+0x17131f>
  562dab:      	pushl	$0x5f017c               # imm = 0x5F017C
  562db0:      	pushl	$0x5f0160               # imm = 0x5F0160
  562db5:      	pushl	0xc70100
  562dbb:      	pushl	0xc7018c
  562dc1:      	calll	0x572c2d <.text+0x171c2d>
  562dc6:      	movl	0xc70188, %ecx
  562dcc:      	addl	$0x10, %esp
  562dcf:      	pushl	%ebp
  562dd0:      	pushl	%ebx
  562dd1:      	pushl	%edi
  562dd2:      	pushl	%esi
  562dd3:      	calll	0x56f3dc <.text+0x16e3dc>
  562dd8:      	movl	0xc70188, %ecx
  562dde:      	pushl	%eax
  562ddf:      	calll	0x57231f <.text+0x17131f>
  562de4:      	pushl	$0x5f0158               # imm = 0x5F0158
  562de9:      	pushl	$0x5f0140               # imm = 0x5F0140
  562dee:      	pushl	0xc70100
  562df4:      	pushl	0xc70188
  562dfa:      	calll	0x572c2d <.text+0x171c2d>
  562dff:      	movl	0xc70180, %ecx
  562e05:      	addl	$0x10, %esp
  562e08:      	pushl	%ebp
  562e09:      	pushl	%ebx
  562e0a:      	pushl	%edi
  562e0b:      	pushl	%esi
  562e0c:      	calll	0x56f3dc <.text+0x16e3dc>
  562e11:      	movl	0xc70180, %ecx
  562e17:      	pushl	%eax
  562e18:      	calll	0x57231f <.text+0x17131f>
  562e1d:      	pushl	$0x5ef430               # imm = 0x5EF430
  562e22:      	pushl	$0x5f011c               # imm = 0x5F011C
  562e27:      	pushl	0xc70100
  562e2d:      	pushl	0xc70180
  562e33:      	calll	0x572c2d <.text+0x171c2d>
  562e38:      	movl	0xc7017c, %ecx
  562e3e:      	addl	$0x10, %esp
  562e41:      	pushl	%ebp
  562e42:      	pushl	%ebx
  562e43:      	pushl	%edi
  562e44:      	pushl	%esi
  562e45:      	calll	0x56f3dc <.text+0x16e3dc>
  562e4a:      	movl	0xc7017c, %ecx
  562e50:      	pushl	%eax
  562e51:      	calll	0x57231f <.text+0x17131f>
  562e56:      	pushl	$0x5f0564               # imm = 0x5F0564
  562e5b:      	pushl	$0x5f0104               # imm = 0x5F0104
  562e60:      	pushl	0xc70100
  562e66:      	pushl	0xc7017c
  562e6c:      	calll	0x572c2d <.text+0x171c2d>
  562e71:      	movl	0xc70174, %ecx
  562e77:      	addl	$0x10, %esp
  562e7a:      	pushl	%ebp
  562e7b:      	pushl	%ebx
  562e7c:      	pushl	%edi
  562e7d:      	pushl	%esi
  562e7e:      	calll	0x56f3dc <.text+0x16e3dc>
  562e83:      	movl	0xc70174, %ecx
  562e89:      	pushl	%eax
  562e8a:      	calll	0x57231f <.text+0x17131f>
  562e8f:      	pushl	$0x5f00fc               # imm = 0x5F00FC
  562e94:      	pushl	$0x5f00e4               # imm = 0x5F00E4
  562e99:      	pushl	0xc70100
  562e9f:      	pushl	0xc70174
  562ea5:      	calll	0x572c2d <.text+0x171c2d>
  562eaa:      	movl	0xc70170, %ecx
  562eb0:      	addl	$0x10, %esp
  562eb3:      	pushl	%ebp
  562eb4:      	pushl	%ebx
  562eb5:      	pushl	%edi
  562eb6:      	pushl	%esi
  562eb7:      	calll	0x56f3dc <.text+0x16e3dc>
  562ebc:      	movl	0xc70170, %ecx
  562ec2:      	pushl	%eax
  562ec3:      	calll	0x57231f <.text+0x17131f>
  562ec8:      	movl	0xc701b8, %ecx
  562ece:      	pushl	%ebp
  562ecf:      	pushl	%ebx
  562ed0:      	pushl	%edi
  562ed1:      	pushl	%esi
  562ed2:      	calll	0x56f3dc <.text+0x16e3dc>
  562ed7:      	movl	0xc701b8, %ecx
  562edd:      	pushl	%eax
  562ede:      	calll	0x57231f <.text+0x17131f>
  562ee3:      	movl	0xc701b4, %ecx
  562ee9:      	pushl	%ebp
  562eea:      	pushl	%ebx
  562eeb:      	pushl	%edi
  562eec:      	pushl	%esi
  562eed:      	calll	0x56f3dc <.text+0x16e3dc>
  562ef2:      	movl	0xc701b4, %ecx
  562ef8:      	pushl	%eax
  562ef9:      	calll	0x57231f <.text+0x17131f>
  562efe:      	movl	0xc701b0, %ecx
  562f04:      	pushl	%ebp
  562f05:      	pushl	%ebx
  562f06:      	pushl	%edi
  562f07:      	pushl	%esi
  562f08:      	calll	0x56f3dc <.text+0x16e3dc>
  562f0d:      	movl	0xc701b0, %ecx
  562f13:      	pushl	%eax
  562f14:      	calll	0x57231f <.text+0x17131f>
  562f19:      	movl	0xc701ac, %ecx
  562f1f:      	pushl	%ebp
  562f20:      	pushl	%ebx
  562f21:      	pushl	%edi
  562f22:      	pushl	%esi
  562f23:      	calll	0x56f3dc <.text+0x16e3dc>
  562f28:      	movl	0xc701ac, %ecx
  562f2e:      	pushl	%eax
  562f2f:      	calll	0x57231f <.text+0x17131f>
  562f34:      	movl	0xc701a8, %ecx
  562f3a:      	pushl	%ebp
  562f3b:      	pushl	%ebx
  562f3c:      	pushl	%edi
  562f3d:      	pushl	%esi
  562f3e:      	calll	0x56f3dc <.text+0x16e3dc>
  562f43:      	movl	0xc701a8, %ecx
  562f49:      	pushl	%eax
  562f4a:      	calll	0x57231f <.text+0x17131f>
  562f4f:      	movl	0xc701a4, %ecx
  562f55:      	pushl	%ebp
  562f56:      	pushl	%ebx
  562f57:      	pushl	%edi
  562f58:      	pushl	%esi
  562f59:      	calll	0x56f3dc <.text+0x16e3dc>
  562f5e:      	movl	0xc701a4, %ecx
  562f64:      	pushl	%eax
  562f65:      	calll	0x57231f <.text+0x17131f>
  562f6a:      	movl	0xc701a0, %ecx
  562f70:      	pushl	%ebp
  562f71:      	pushl	%ebx
  562f72:      	pushl	%edi
  562f73:      	pushl	%esi
  562f74:      	calll	0x56f3dc <.text+0x16e3dc>
  562f79:      	movl	0xc701a0, %ecx
  562f7f:      	pushl	%eax
  562f80:      	calll	0x57231f <.text+0x17131f>
  562f85:      	movl	0xc7019c, %ecx
  562f8b:      	pushl	%ebp
  562f8c:      	pushl	%ebx
  562f8d:      	pushl	%edi
  562f8e:      	pushl	%esi
  562f8f:      	calll	0x56f3dc <.text+0x16e3dc>
  562f94:      	movl	0xc7019c, %ecx
  562f9a:      	pushl	%eax
  562f9b:      	calll	0x57231f <.text+0x17131f>
  562fa0:      	movl	0xc70194, %ecx
  562fa6:      	pushl	%ebp
  562fa7:      	pushl	%ebx
  562fa8:      	pushl	%edi
  562fa9:      	pushl	%esi
  562faa:      	calll	0x56f3dc <.text+0x16e3dc>
  562faf:      	movl	0xc70194, %ecx
  562fb5:      	pushl	%eax
  562fb6:      	calll	0x57231f <.text+0x17131f>
  562fbb:      	movl	0xc70100, %eax
  562fc0:      	pushl	$0x5
  562fc2:      	movl	$0x5df2cc, %edi         # imm = 0x5DF2CC
  562fc7:      	leal	0x4(%eax), %esi
  562fca:      	popl	%ecx
  562fcb:      	xorl	%edx, %edx
  562fcd:      	rep		cmpsb	%es:(%edi), (%esi)
  562fcf:      	jne	0x55eb35 <.text+0x15db35>
  562fd5:      	pushl	%ebx
  562fd6:      	movl	%eax, %ecx
  562fd8:      	calll	0x572935 <.text+0x171935>
  562fdd:      	jmp	0x55eb35 <.text+0x15db35>
  562fe2:      	pushl	$0x200ff00              # imm = 0x200FF00
  562fe7:      	pushl	%edi
  562fe8:      	calll	*0x5ce04c
  562fee:      	pushl	%ebp
  562fef:      	pushl	%edi
  562ff0:      	calll	*0x5ce048
  562ff6:      	pushl	$0x0
  562ff8:      	pushl	%edi
  562ff9:      	calll	*0x5ce0d8
  562fff:      	jmp	0x563016 <.text+0x162016>
  563001:      	pushl	$0xff00                 # imm = 0xFF00
  563006:      	pushl	%edi
  563007:      	calll	*0x5ce04c
  56300d:      	pushl	$0x1
  56300f:      	pushl	%edi
  563010:      	calll	*0x5ce048
  563016:      	pushl	$0x4
  563018:      	calll	*0x5ce040
  56301e:      	movl	0x2fc(%esp), %ecx
  563025:      	popl	%edi
  563026:      	popl	%esi
  563027:      	popl	%ebp
  563028:      	popl	%ebx
  563029:      	xorl	%esp, %ecx
  56302b:      	calll	0x5c6d18 <.text+0x1c5d18>
  563030:      	addl	$0x2f0, %esp            # imm = 0x2F0
  563036:      	retl	$0x10
