; Entry: 004faaa7
; Name: Solid_Perspective_Texture_Map_polygon
; Signature: void Solid_Perspective_Texture_Map_polygon(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
; Stop: 0x004fb2c1
; Reason: Exception while decompiling 004faaa7: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x004faaa7 --stop-address=0x004fb2c1 C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  4faaa7:      	pushl	%ebp
  4faaa8:      	movl	%esp, %ebp
  4faaaa:      	pushl	%ebx
  4faaab:      	pushl	%esi
  4faaac:      	pushl	%edi
  4faaad:      	movl	0x14(%ebp), %ebx
  4faab0:      	pushl	%ebp
  4faab1:      	movl	0xcfdbc0, %eax
  4faab6:      	subl	$0x6d8, %esp            # imm = 0x6D8
  4faabc:      	cmpl	%ebx, %eax
  4faabe:      	je	0x4fab2e <.text+0xf9b2e>
  4faac0:      	movl	%ebx, 0xcfdbc0
  4faac6:      	leal	0xcfdbd8, %edx
  4faacc:      	movl	(%ebx), %eax
  4faace:      	movl	0x4(%ebx), %ecx
  4faad1:      	leal	0x8(%ebx), %esi
  4faad4:      	movl	%ecx, 0x4(%esp)
  4faad8:      	movl	%eax, %edi
  4faada:      	addl	$0x3, %ecx
  4faadd:      	addl	%esi, %edi
  4faadf:      	leal	(%esi,%eax,2), %ebx
  4faae2:      	leal	(%eax,%eax,2), %eax
  4faae5:      	movl	%esi, -0x4(%edx)
  4faae8:      	movl	%esi, -0x8(%edx)
  4faaeb:      	movl	%esi, -0xc(%edx)
  4faaee:      	movl	%esi, -0x10(%edx)
  4faaf1:      	movl	%esi, (%edx)
  4faaf3:      	movl	%edi, 0x4(%edx)
  4faaf6:      	movl	%ebx, 0x8(%edx)
  4faaf9:      	addl	%eax, %esi
  4faafb:      	addl	%eax, %edi
  4faafd:      	addl	%eax, %ebx
  4faaff:      	addl	$0xc, %edx
  4fab02:      	subl	$0x3, %ecx
  4fab05:      	jge	0x4faaf1 <.text+0xf9af1>
  4fab07:      	movl	0x4(%esp), %edx
  4fab0b:      	movl	0xcfdbd4(,%edx,4), %eax
  4fab12:      	movl	%eax, 0xcfdbd8(,%edx,4)
  4fab19:      	movl	%eax, 0xcfdbdc(,%edx,4)
  4fab20:      	movl	%eax, 0xcfdbe0(,%edx,4)
  4fab27:      	movl	%eax, 0xcfdbe4(,%edx,4)
  4fab2e:      	movl	0x14(%ebp), %ebx
  4fab31:      	movl	$0x186a0, %edx          # imm = 0x186A0
  4fab36:      	movl	0xc(%ebp), %esi
  4fab39:      	movl	0x10(%ebp), %eax
  4fab3c:      	fildl	0x4(%ebx)
  4fab3f:      	movl	(%ebx), %ecx
  4fab41:      	movl	%esi, (%esp)
  4fab44:      	shll	$0x3, %eax
  4fab47:      	leal	0x8(%ebx), %edi
  4fab4a:      	fsubs	0x62c808
  4fab50:      	fildl	(%ebx)
  4fab52:      	movl	%ecx, 0x10(%esp)
  4fab56:      	leal	(%eax,%eax,2), %ecx
  4fab59:      	xorl	%eax, %eax
  4fab5b:      	movl	%edi, 0x1c(%esp)
  4fab5f:      	fsubs	0x62c808
  4fab65:      	flds	0x4(%esi,%eax)
  4fab69:      	faddl	0x632380
  4fab6f:      	flds	0xc(%esi,%eax)
  4fab73:      	fmul	%st(2), %st
  4fab75:      	flds	0x10(%esi,%eax)
  4fab79:      	fmul	%st(4), %st
  4fab7b:      	fxch	%st(2)
  4fab7d:      	fstpl	0x640(%esp)
  4fab84:      	fstps	0xc(%esi,%eax)
  4fab88:      	fstps	0x10(%esi,%eax)
  4fab8c:      	movl	0x640(%esp), %edi
  4fab93:      	movl	%eax, 0x320(%esp,%eax)
  4fab9a:      	movl	%eax, 0x50(%esp,%eax)
  4fab9e:      	movl	%edi, 0x33c(%esp,%eax)
  4faba5:      	addl	$0x18, %eax
  4faba8:      	cmpl	%edx, %edi
  4fabaa:      	jg	0x4fabb0 <.text+0xf9bb0>
  4fabac:      	movl	%eax, %ebx
  4fabae:      	movl	%edi, %edx
  4fabb0:      	cmpl	%ecx, %eax
  4fabb2:      	jne	0x4fab65 <.text+0xf9b65>
  4fabb4:      	subl	$0x18, %ebx
  4fabb7:      	leal	-0x18(%eax), %ecx
  4fabba:      	fcompp
  4fabbc:      	movl	$0x0, 0x320(%esp,%eax)
  4fabc7:      	movl	%ecx, 0x38(%esp)
  4fabcb:      	movl	0x8(%ebp), %edi
  4fabce:      	movl	%ebx, 0x6b0(%esp)
  4fabd5:      	movl	%ebx, 0x688(%esp)
  4fabdc:      	movl	%ebx, 0x6b4(%esp)
  4fabe3:      	movl	%esi, %ebp
  4fabe5:      	movl	0x20(%edi), %eax
  4fabe8:      	movl	(%edi), %ecx
  4fabea:      	addl	%edx, %eax
  4fabec:      	movl	0x14(%edi), %esi
  4fabef:      	movl	0x1c(%edi), %edi
  4fabf2:      	imull	%ecx
  4fabf4:      	addl	%edi, %esi
  4fabf6:      	movl	%ecx, 0xc(%esp)
  4fabfa:      	addl	%eax, %esi
  4fabfc:      	movl	0x33c(%esp,%ebx), %edi
  4fac03:      	movl	%esi, 0x18(%esp)
  4fac07:      	movl	%ebx, 0x68c(%esp)
  4fac0e:      	movl	0x6b4(%esp), %ecx
  4fac15:      	movl	0x33c(%esp,%ecx), %eax
  4fac1c:      	movl	%edi, 0x4(%esp)
  4fac20:      	cmpl	%eax, %edi
  4fac22:      	jl	0x4fad2c <.text+0xf9d2c>
  4fac28:      	movl	0x338(%esp,%ecx), %edx
  4fac2f:      	movl	%ecx, %eax
  4fac31:      	movl	%edx, 0x6b4(%esp)
  4fac38:      	cmpl	0x688(%esp), %edx
  4fac3f:      	je	0x4fb2b5 <.text+0xfa2b5>
  4fac45:      	movl	0x33c(%esp,%edx), %esi
  4fac4c:      	movl	%edx, %ecx
  4fac4e:      	cmpl	%esi, %edi
  4fac50:      	jge	0x4fac28 <.text+0xf9c28>
  4fac52:      	flds	0x4(%ebp,%edx)
  4fac56:      	fsubs	0x4(%ebp,%eax)
  4fac5a:      	flds	0x10(%ebp,%edx)
  4fac5e:      	fsubs	0x10(%ebp,%eax)
  4fac62:      	fxch	%st(1)
  4fac64:      	fdivrs	0x62c808
  4fac6a:      	flds	0xc(%ebp,%edx)
  4fac6e:      	fsubs	0xc(%ebp,%eax)
  4fac72:      	fxch	%st(1)
  4fac74:      	fmul	%st, %st(2)
  4fac76:      	flds	0x8(%ebp,%edx)
  4fac7a:      	fsubs	0x8(%ebp,%eax)
  4fac7e:      	fxch	%st(2)
  4fac80:      	fmul	%st(1), %st
  4fac82:      	flds	(%ebp,%edx)
  4fac86:      	fsubs	(%ebp,%eax)
  4fac8a:      	fxch	%st(3)
  4fac8c:      	fmul	%st(2), %st
  4fac8e:      	fxch	%st(4)
  4fac90:      	fstps	0x6cc(%esp)
  4fac97:      	flds	0x4(%ebp,%eax)
  4fac9b:      	faddl	0x632380
  4faca1:      	fxch	%st(3)
  4faca3:      	fmulp	%st, %st(2)
  4faca5:      	fstps	0x6c8(%esp)
  4facac:      	fxch	%st(1)
  4facae:      	fstpl	0x640(%esp)
  4facb5:      	fstps	0x6d0(%esp)
  4facbc:      	fildl	0x640(%esp)
  4facc3:      	fxch	%st(1)
  4facc5:      	fstps	0x6d4(%esp)
  4faccc:      	fsubs	0x4(%ebp,%eax)
  4facd0:      	flds	0x6d0(%esp)
  4facd7:      	flds	0x6d4(%esp)
  4facde:      	fmul	%st(2), %st
  4face0:      	flds	0x6c8(%esp)
  4face7:      	fmul	%st(3), %st
  4face9:      	fxch	%st(1)
  4faceb:      	fadds	0x8(%ebp,%eax)
  4facef:      	flds	0x6cc(%esp)
  4facf6:      	fmul	%st(4), %st
  4facf8:      	fxch	%st(2)
  4facfa:      	fadds	0xc(%ebp,%eax)
  4facfe:      	fxch	%st(3)
  4fad00:      	fmulp	%st, %st(4)
  4fad02:      	fstps	0x6bc(%esp)
  4fad09:      	fadds	0x10(%ebp,%eax)
  4fad0d:      	fxch	%st(2)
  4fad0f:      	fadds	(%ebp,%eax)
  4fad13:      	fxch	%st(1)
  4fad15:      	fstps	0x6c0(%esp)
  4fad1c:      	fxch	%st(1)
  4fad1e:      	fstps	0x6c4(%esp)
  4fad25:      	fstps	0x6b8(%esp)
  4fad2c:      	movl	0x68c(%esp), %ecx
  4fad33:      	cmpl	0x33c(%esp,%ecx), %edi
  4fad3a:      	jl	0x4fae32 <.text+0xf9e32>
  4fad40:      	movl	0x38(%esp,%ecx), %edx
  4fad44:      	movl	%ecx, %eax
  4fad46:      	movl	%edx, 0x68c(%esp)
  4fad4d:      	movl	%edx, %ecx
  4fad4f:      	cmpl	0x33c(%esp,%edx), %edi
  4fad56:      	jge	0x4fad40 <.text+0xf9d40>
  4fad58:      	flds	0x4(%ebp,%edx)
  4fad5c:      	fsubs	0x4(%ebp,%eax)
  4fad60:      	flds	0x10(%ebp,%edx)
  4fad64:      	fsubs	0x10(%ebp,%eax)
  4fad68:      	fxch	%st(1)
  4fad6a:      	fdivrs	0x62c808
  4fad70:      	flds	0xc(%ebp,%edx)
  4fad74:      	fsubs	0xc(%ebp,%eax)
  4fad78:      	fxch	%st(1)
  4fad7a:      	fmul	%st, %st(2)
  4fad7c:      	flds	0x8(%ebp,%edx)
  4fad80:      	fsubs	0x8(%ebp,%eax)
  4fad84:      	fxch	%st(2)
  4fad86:      	fmul	%st(1), %st
  4fad88:      	flds	(%ebp,%edx)
  4fad8c:      	fsubs	(%ebp,%eax)
  4fad90:      	fxch	%st(3)
  4fad92:      	fmul	%st(2), %st
  4fad94:      	fxch	%st(4)
  4fad96:      	fstps	0x6a4(%esp)
  4fad9d:      	flds	0x4(%ebp,%eax)
  4fada1:      	faddl	0x632380
  4fada7:      	fxch	%st(3)
  4fada9:      	fmulp	%st, %st(2)
  4fadab:      	fstps	0x6a0(%esp)
  4fadb2:      	fxch	%st(1)
  4fadb4:      	fstpl	0x640(%esp)
  4fadbb:      	fstps	0x6a8(%esp)
  4fadc2:      	fildl	0x640(%esp)
  4fadc9:      	fxch	%st(1)
  4fadcb:      	fstps	0x6ac(%esp)
  4fadd2:      	fsubs	0x4(%ebp,%eax)
  4fadd6:      	flds	0x6a8(%esp)
  4faddd:      	flds	0x6ac(%esp)
  4fade4:      	fmul	%st(2), %st
  4fade6:      	flds	0x6a0(%esp)
  4faded:      	fmul	%st(3), %st
  4fadef:      	fxch	%st(1)
  4fadf1:      	fadds	0x8(%ebp,%eax)
  4fadf5:      	flds	0x6a4(%esp)
  4fadfc:      	fmul	%st(4), %st
  4fadfe:      	fxch	%st(2)
  4fae00:      	fadds	0xc(%ebp,%eax)
  4fae04:      	fxch	%st(3)
  4fae06:      	fmulp	%st, %st(4)
  4fae08:      	fstps	0x694(%esp)
  4fae0f:      	fadds	0x10(%ebp,%eax)
  4fae13:      	fxch	%st(2)
  4fae15:      	fadds	(%ebp,%eax)
  4fae19:      	fxch	%st(1)
  4fae1b:      	fstps	0x698(%esp)
  4fae22:      	fxch	%st(1)
  4fae24:      	fstps	0x69c(%esp)
  4fae2b:      	fstps	0x690(%esp)
  4fae32:      	flds	0x6b8(%esp)
  4fae39:      	faddl	0x632380
  4fae3f:      	flds	0x690(%esp)
  4fae46:      	faddl	0x632380
  4fae4c:      	fxch	%st(1)
  4fae4e:      	fstpl	0x650(%esp)
  4fae55:      	fstpl	0x648(%esp)
  4fae5c:      	movl	0x650(%esp), %edx
  4fae63:      	movl	0x648(%esp), %ebx
  4fae6a:      	cmpl	%edx, %ebx
  4fae6c:      	je	0x4fb1ee <.text+0xfa1ee>
  4fae72:      	jl	0x4faf14 <.text+0xf9f14>
  4fae78:      	flds	0x690(%esp)
  4fae7f:      	fsubs	0x6b8(%esp)
  4fae86:      	flds	0x69c(%esp)
  4fae8d:      	fsubs	0x6c4(%esp)
  4fae94:      	fxch	%st(1)
  4fae96:      	fdivrs	0x62c808
  4fae9c:      	flds	0x698(%esp)
  4faea3:      	fsubs	0x6c0(%esp)
  4faeaa:      	fxch	%st(2)
  4faeac:      	fmul	%st(1), %st
  4faeae:      	flds	0x694(%esp)
  4faeb5:      	fsubs	0x6bc(%esp)
  4faebc:      	fxch	%st(3)
  4faebe:      	fmul	%st(2), %st
  4faec0:      	fxch	%st(1)
  4faec2:      	fstps	0x24(%esp)
  4faec6:      	fxch	%st(1)
  4faec8:      	fmulp	%st, %st(2)
  4faeca:      	fstps	0x20(%esp)
  4faece:      	fildl	0x650(%esp)
  4faed5:      	fxch	%st(1)
  4faed7:      	fstps	0x28(%esp)
  4faedb:      	fsubs	0x6b8(%esp)
  4faee2:      	flds	0x24(%esp)
  4faee6:      	flds	0x20(%esp)
  4faeea:      	fmul	%st(2), %st
  4faeec:      	flds	0x28(%esp)
  4faef0:      	fmul	%st(3), %st
  4faef2:      	fxch	%st(1)
  4faef4:      	fadds	0x6c0(%esp)
  4faefb:      	fxch	%st(3)
  4faefd:      	fmulp	%st, %st(2)
  4faeff:      	fadds	0x6bc(%esp)
  4faf06:      	fxch	%st(1)
  4faf08:      	fadds	0x6c4(%esp)
  4faf0f:      	jmp	0x4fafbb <.text+0xf9fbb>
  4faf14:      	movl	%ebx, 0x650(%esp)
  4faf1b:      	movl	%edx, %ebx
  4faf1d:      	movl	0x650(%esp), %edx
  4faf24:      	flds	0x6b8(%esp)
  4faf2b:      	fsubs	0x690(%esp)
  4faf32:      	flds	0x6c4(%esp)
  4faf39:      	fsubs	0x69c(%esp)
  4faf40:      	fxch	%st(1)
  4faf42:      	fdivrs	0x62c808
  4faf48:      	flds	0x6c0(%esp)
  4faf4f:      	fsubs	0x698(%esp)
  4faf56:      	fxch	%st(2)
  4faf58:      	fmul	%st(1), %st
  4faf5a:      	flds	0x6bc(%esp)
  4faf61:      	fsubs	0x694(%esp)
  4faf68:      	fxch	%st(3)
  4faf6a:      	fmul	%st(2), %st
  4faf6c:      	fxch	%st(1)
  4faf6e:      	fstps	0x24(%esp)
  4faf72:      	fxch	%st(1)
  4faf74:      	fmulp	%st, %st(2)
  4faf76:      	fstps	0x20(%esp)
  4faf7a:      	fildl	0x650(%esp)
  4faf81:      	fxch	%st(1)
  4faf83:      	fstps	0x28(%esp)
  4faf87:      	fsubs	0x690(%esp)
  4faf8e:      	flds	0x24(%esp)
  4faf92:      	flds	0x20(%esp)
  4faf96:      	fmul	%st(2), %st
  4faf98:      	flds	0x28(%esp)
  4faf9c:      	fmul	%st(3), %st
  4faf9e:      	fxch	%st(1)
  4fafa0:      	fadds	0x698(%esp)
  4fafa7:      	fxch	%st(3)
  4fafa9:      	fmulp	%st, %st(2)
  4fafab:      	fadds	0x694(%esp)
  4fafb2:      	fxch	%st(1)
  4fafb4:      	fadds	0x69c(%esp)
  4fafbb:      	movl	0x18(%esp), %edi
  4fafbf:      	subl	%edx, %ebx
  4fafc1:      	addl	%edx, %edi
  4fafc3:      	flds	0x20(%esp)
  4fafc7:      	fmuls	0x62c814
  4fafcd:      	flds	0x24(%esp)
  4fafd1:      	fmuls	0x62c814
  4fafd7:      	flds	0x28(%esp)
  4fafdb:      	fmuls	0x62c814
  4fafe1:      	fxch	%st(2)
  4fafe3:      	fstps	0x2c(%esp)
  4fafe7:      	fstps	0x30(%esp)
  4fafeb:      	fstps	0x34(%esp)
  4fafef:      	fxch	%st(1)
  4faff1:      	flds	0x62c80c
  4faff7:      	fdiv	%st(1), %st
  4faff9:      	fld	%st(2)
  4faffb:      	fmul	%st(1), %st
  4faffd:      	fld	%st(4)
  4fafff:      	fmulp	%st, %st(2)
  4fb001:      	faddl	0x632380
  4fb007:      	fxch	%st(1)
  4fb009:      	faddl	0x632380
  4fb00f:      	fxch	%st(2)
  4fb011:      	fadds	0x34(%esp)
  4fb015:      	fxch	%st(1)
  4fb017:      	fstpl	0x680(%esp)
  4fb01e:      	fxch	%st(1)
  4fb020:      	fstpl	0x678(%esp)
  4fb027:      	fxch	%st(2)
  4fb029:      	flds	0x62c80c
  4fb02f:      	fdiv	%st(3), %st
  4fb031:      	decl	%ebx
  4fb032:      	jmp	0x4fb107 <.text+0xfa107>
  4fb037:      	flds	0x2c(%esp)
  4fb03b:      	faddp	%st, %st(2)
  4fb03d:      	flds	0x30(%esp)
  4fb041:      	faddp	%st, %st(3)
  4fb043:      	fld	%st(1)
  4fb045:      	fmul	%st(1), %st
  4fb047:      	flds	0x34(%esp)
  4fb04b:      	fxch	%st(2)
  4fb04d:      	fmul	%st(4), %st
  4fb04f:      	fxch	%st(2)
  4fb051:      	faddp	%st, %st(5)
  4fb053:      	faddl	0x632380
  4fb059:      	fxch	%st(1)
  4fb05b:      	faddl	0x632380
  4fb061:      	fld	%st(4)
  4fb063:      	fxch	%st(2)
  4fb065:      	fstpl	0x658(%esp)
  4fb06c:      	fstpl	0x668(%esp)
  4fb073:      	fdivrs	0x62c80c
  4fb079:      	movl	0x680(%esp), %ebp
  4fb080:      	movl	0x678(%esp), %esi
  4fb087:      	movl	0x668(%esp), %eax
  4fb08e:      	movl	0x658(%esp), %edx
  4fb095:      	subl	%ebp, %eax
  4fb097:      	subl	%esi, %edx
  4fb099:      	sarl	$0x4, %eax
  4fb09c:      	movl	%ebx, 0x8(%esp)
  4fb0a0:      	sarl	$0x4, %edx
  4fb0a3:      	movl	%eax, 0x670(%esp)
  4fb0aa:      	movl	%edx, 0x660(%esp)
  4fb0b1:      	movl	$0x10, %ebx
  4fb0b6:      	movb	(%edi), %cl
  4fb0b8:      	movl	%ebp, %eax
  4fb0ba:      	movl	%esi, %edx
  4fb0bc:      	sarl	$0x10, %eax
  4fb0bf:      	movl	0x670(%esp), %ecx
  4fb0c6:      	sarl	$0x10, %edx
  4fb0c9:      	addl	%ecx, %ebp
  4fb0cb:      	movl	0xcfdbd8(,%eax,4), %eax
  4fb0d2:      	movl	0x660(%esp), %ecx
  4fb0d9:      	movb	(%eax,%edx), %al
  4fb0dc:      	addl	%ecx, %esi
  4fb0de:      	movb	%al, (%edi)
  4fb0e0:      	incl	%edi
  4fb0e1:      	decl	%ebx
  4fb0e2:      	jne	0x4fb0b8 <.text+0xfa0b8>
  4fb0e4:      	movl	0x8(%esp), %ebx
  4fb0e8:      	movl	0x658(%esp), %eax
  4fb0ef:      	movl	0x668(%esp), %edx
  4fb0f6:      	movl	%eax, 0x678(%esp)
  4fb0fd:      	movl	%edx, 0x680(%esp)
  4fb104:      	subl	$0x10, %ebx
  4fb107:      	cmpl	$0x10, %ebx
  4fb10a:      	jge	0x4fb037 <.text+0xfa037>
  4fb110:      	cmpl	$0x0, %ebx
  4fb113:      	movl	0x680(%esp), %ebp
  4fb11a:      	movl	0x678(%esp), %esi
  4fb121:      	je	0x4fb1d8 <.text+0xfa1d8>
  4fb127:      	fxch	%st(3)
  4fb129:      	fsubs	0x34(%esp)
  4fb12d:      	flds	0x28(%esp)
  4fb131:      	fmuls	0x62c810(,%ebx,8)
  4fb138:      	flds	0x20(%esp)
  4fb13c:      	fmuls	0x62c810(,%ebx,8)
  4fb143:      	flds	0x24(%esp)
  4fb147:      	fmuls	0x62c810(,%ebx,8)
  4fb14e:      	fxch	%st(2)
  4fb150:      	faddp	%st, %st(3)
  4fb152:      	faddp	%st, %st(3)
  4fb154:      	faddp	%st, %st(3)
  4fb156:      	fdivrs	0x62c80c
  4fb15c:      	fmul	%st, %st(1)
  4fb15e:      	fildl	0x678(%esp)
  4fb165:      	fxch	%st(1)
  4fb167:      	fmul	%st(3), %st
  4fb169:      	fildl	0x680(%esp)
  4fb170:      	fxch	%st(2)
  4fb172:      	fsubrp	%st, %st(3)
  4fb174:      	fsubp	%st, %st(1)
  4fb176:      	fxch	%st(1)
  4fb178:      	fmuls	0x62c814(,%ebx,8)
  4fb17f:      	fxch	%st(1)
  4fb181:      	fmuls	0x62c814(,%ebx,8)
  4fb188:      	fxch	%st(1)
  4fb18a:      	faddl	0x632380
  4fb190:      	fxch	%st(1)
  4fb192:      	faddl	0x632380
  4fb198:      	fxch	%st(1)
  4fb19a:      	fstl	0x660(%esp)
  4fb1a1:      	fxch	%st(1)
  4fb1a3:      	fstl	0x670(%esp)
  4fb1aa:      	movb	(%edi), %cl
  4fb1ac:      	movl	%ebp, %eax
  4fb1ae:      	movl	%esi, %edx
  4fb1b0:      	sarl	$0x10, %eax
  4fb1b3:      	movl	0x670(%esp), %ecx
  4fb1ba:      	sarl	$0x10, %edx
  4fb1bd:      	addl	%ecx, %ebp
  4fb1bf:      	movl	0xcfdbd8(,%eax,4), %eax
  4fb1c6:      	movl	0x660(%esp), %ecx
  4fb1cd:      	movb	(%eax,%edx), %al
  4fb1d0:      	addl	%ecx, %esi
  4fb1d2:      	movb	%al, (%edi)
  4fb1d4:      	incl	%edi
  4fb1d5:      	decl	%ebx
  4fb1d6:      	jne	0x4fb1ac <.text+0xfa1ac>
  4fb1d8:      	sarl	$0x10, %ebp
  4fb1db:      	sarl	$0x10, %esi
  4fb1de:      	fcompp
  4fb1e0:      	movl	0xcfdbd8(,%ebp,4), %eax
  4fb1e7:      	fcompp
  4fb1e9:      	movb	(%eax,%esi), %al
  4fb1ec:      	movb	%al, (%edi)
  4fb1ee:      	flds	0x694(%esp)
  4fb1f5:      	fadds	0x6ac(%esp)
  4fb1fc:      	flds	0x69c(%esp)
  4fb203:      	fadds	0x6a4(%esp)
  4fb20a:      	flds	0x698(%esp)
  4fb211:      	fadds	0x6a0(%esp)
  4fb218:      	flds	0x690(%esp)
  4fb21f:      	fadds	0x6a8(%esp)
  4fb226:      	fxch	%st(3)
  4fb228:      	fstps	0x694(%esp)
  4fb22f:      	fstps	0x698(%esp)
  4fb236:      	fstps	0x69c(%esp)
  4fb23d:      	fstps	0x690(%esp)
  4fb244:      	flds	0x6bc(%esp)
  4fb24b:      	fadds	0x6d4(%esp)
  4fb252:      	flds	0x6c4(%esp)
  4fb259:      	fadds	0x6cc(%esp)
  4fb260:      	flds	0x6c0(%esp)
  4fb267:      	fadds	0x6c8(%esp)
  4fb26e:      	flds	0x6b8(%esp)
  4fb275:      	fadds	0x6d0(%esp)
  4fb27c:      	fxch	%st(3)
  4fb27e:      	fstps	0x6bc(%esp)
  4fb285:      	fstps	0x6c0(%esp)
  4fb28c:      	fstps	0x6c4(%esp)
  4fb293:      	fstps	0x6b8(%esp)
  4fb29a:      	movl	0x18(%esp), %esi
  4fb29e:      	movl	0xc(%esp), %eax
  4fb2a2:      	movl	(%esp), %ebp
  4fb2a5:      	addl	%eax, %esi
  4fb2a7:      	movl	0x4(%esp), %edi
  4fb2ab:      	movl	%esi, 0x18(%esp)
  4fb2af:      	incl	%edi
  4fb2b0:      	jmp	0x4fac0e <.text+0xf9c0e>
  4fb2b5:      	addl	$0x6d8, %esp            # imm = 0x6D8
  4fb2bb:      	popl	%ebp
  4fb2bc:      	popl	%edi
  4fb2bd:      	popl	%esi
  4fb2be:      	popl	%ebx
  4fb2bf:      	popl	%ebp
  4fb2c0:      	retl
