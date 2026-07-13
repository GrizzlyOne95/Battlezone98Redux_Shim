; Entry: 00503b19
; Name: Transparent_Perspective_Texture_Map_polygon
; Signature: void Transparent_Perspective_Texture_Map_polygon(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
; Stop: 0x0050434b
; Reason: Exception while decompiling 00503b19: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x00503b19 --stop-address=0x0050434b C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  503b19:      	pushl	%ebp
  503b1a:      	movl	%esp, %ebp
  503b1c:      	pushl	%ebx
  503b1d:      	pushl	%esi
  503b1e:      	pushl	%edi
  503b1f:      	movl	0x14(%ebp), %ebx
  503b22:      	pushl	%ebp
  503b23:      	movl	0xcfdbc0, %eax
  503b28:      	subl	$0x6d8, %esp            # imm = 0x6D8
  503b2e:      	cmpl	%ebx, %eax
  503b30:      	je	0x503ba0 <.text+0x102ba0>
  503b32:      	movl	%ebx, 0xcfdbc0
  503b38:      	leal	0xcfdbd8, %edx
  503b3e:      	movl	(%ebx), %eax
  503b40:      	movl	0x4(%ebx), %ecx
  503b43:      	leal	0x8(%ebx), %esi
  503b46:      	movl	%ecx, 0x4(%esp)
  503b4a:      	movl	%eax, %edi
  503b4c:      	addl	$0x3, %ecx
  503b4f:      	addl	%esi, %edi
  503b51:      	leal	(%esi,%eax,2), %ebx
  503b54:      	leal	(%eax,%eax,2), %eax
  503b57:      	movl	%esi, -0x4(%edx)
  503b5a:      	movl	%esi, -0x8(%edx)
  503b5d:      	movl	%esi, -0xc(%edx)
  503b60:      	movl	%esi, -0x10(%edx)
  503b63:      	movl	%esi, (%edx)
  503b65:      	movl	%edi, 0x4(%edx)
  503b68:      	movl	%ebx, 0x8(%edx)
  503b6b:      	addl	%eax, %esi
  503b6d:      	addl	%eax, %edi
  503b6f:      	addl	%eax, %ebx
  503b71:      	addl	$0xc, %edx
  503b74:      	subl	$0x3, %ecx
  503b77:      	jge	0x503b63 <.text+0x102b63>
  503b79:      	movl	0x4(%esp), %edx
  503b7d:      	movl	0xcfdbd4(,%edx,4), %eax
  503b84:      	movl	%eax, 0xcfdbd8(,%edx,4)
  503b8b:      	movl	%eax, 0xcfdbdc(,%edx,4)
  503b92:      	movl	%eax, 0xcfdbe0(,%edx,4)
  503b99:      	movl	%eax, 0xcfdbe4(,%edx,4)
  503ba0:      	movl	0x14(%ebp), %ebx
  503ba3:      	movl	$0x186a0, %edx          # imm = 0x186A0
  503ba8:      	movl	0xc(%ebp), %esi
  503bab:      	movl	0x10(%ebp), %eax
  503bae:      	fildl	0x4(%ebx)
  503bb1:      	movl	(%ebx), %ecx
  503bb3:      	movl	%esi, (%esp)
  503bb6:      	shll	$0x3, %eax
  503bb9:      	leal	0x8(%ebx), %edi
  503bbc:      	fsubs	0x62c808
  503bc2:      	fildl	(%ebx)
  503bc4:      	movl	%ecx, 0x10(%esp)
  503bc8:      	leal	(%eax,%eax,2), %ecx
  503bcb:      	xorl	%eax, %eax
  503bcd:      	movl	%edi, 0x1c(%esp)
  503bd1:      	fsubs	0x62c808
  503bd7:      	flds	0x4(%esi,%eax)
  503bdb:      	faddl	0x632380
  503be1:      	flds	0xc(%esi,%eax)
  503be5:      	fmul	%st(2), %st
  503be7:      	flds	0x10(%esi,%eax)
  503beb:      	fmul	%st(4), %st
  503bed:      	fxch	%st(2)
  503bef:      	fstpl	0x640(%esp)
  503bf6:      	fstps	0xc(%esi,%eax)
  503bfa:      	fstps	0x10(%esi,%eax)
  503bfe:      	movl	0x640(%esp), %edi
  503c05:      	movl	%eax, 0x320(%esp,%eax)
  503c0c:      	movl	%eax, 0x50(%esp,%eax)
  503c10:      	movl	%edi, 0x33c(%esp,%eax)
  503c17:      	addl	$0x18, %eax
  503c1a:      	cmpl	%edx, %edi
  503c1c:      	jg	0x503c22 <.text+0x102c22>
  503c1e:      	movl	%eax, %ebx
  503c20:      	movl	%edi, %edx
  503c22:      	cmpl	%ecx, %eax
  503c24:      	jne	0x503bd7 <.text+0x102bd7>
  503c26:      	subl	$0x18, %ebx
  503c29:      	leal	-0x18(%eax), %ecx
  503c2c:      	fcompp
  503c2e:      	movl	$0x0, 0x320(%esp,%eax)
  503c39:      	movl	%ecx, 0x38(%esp)
  503c3d:      	movl	0x8(%ebp), %edi
  503c40:      	movl	%ebx, 0x6b0(%esp)
  503c47:      	movl	%ebx, 0x688(%esp)
  503c4e:      	movl	%ebx, 0x6b4(%esp)
  503c55:      	movl	%esi, %ebp
  503c57:      	movl	0x20(%edi), %eax
  503c5a:      	movl	(%edi), %ecx
  503c5c:      	addl	%edx, %eax
  503c5e:      	movl	0x14(%edi), %esi
  503c61:      	movl	0x1c(%edi), %edi
  503c64:      	imull	%ecx
  503c66:      	addl	%edi, %esi
  503c68:      	movl	%ecx, 0xc(%esp)
  503c6c:      	addl	%eax, %esi
  503c6e:      	movl	0x33c(%esp,%ebx), %edi
  503c75:      	movl	%esi, 0x18(%esp)
  503c79:      	movl	%ebx, 0x68c(%esp)
  503c80:      	movl	0x6b4(%esp), %ecx
  503c87:      	movl	0x33c(%esp,%ecx), %eax
  503c8e:      	movl	%edi, 0x4(%esp)
  503c92:      	cmpl	%eax, %edi
  503c94:      	jl	0x503d9e <.text+0x102d9e>
  503c9a:      	movl	0x338(%esp,%ecx), %edx
  503ca1:      	movl	%ecx, %eax
  503ca3:      	movl	%edx, 0x6b4(%esp)
  503caa:      	cmpl	0x688(%esp), %edx
  503cb1:      	je	0x50433f <.text+0x10333f>
  503cb7:      	movl	0x33c(%esp,%edx), %esi
  503cbe:      	movl	%edx, %ecx
  503cc0:      	cmpl	%esi, %edi
  503cc2:      	jge	0x503c9a <.text+0x102c9a>
  503cc4:      	flds	0x4(%ebp,%edx)
  503cc8:      	fsubs	0x4(%ebp,%eax)
  503ccc:      	flds	0x10(%ebp,%edx)
  503cd0:      	fsubs	0x10(%ebp,%eax)
  503cd4:      	fxch	%st(1)
  503cd6:      	fdivrs	0x62c808
  503cdc:      	flds	0xc(%ebp,%edx)
  503ce0:      	fsubs	0xc(%ebp,%eax)
  503ce4:      	fxch	%st(1)
  503ce6:      	fmul	%st, %st(2)
  503ce8:      	flds	0x8(%ebp,%edx)
  503cec:      	fsubs	0x8(%ebp,%eax)
  503cf0:      	fxch	%st(2)
  503cf2:      	fmul	%st(1), %st
  503cf4:      	flds	(%ebp,%edx)
  503cf8:      	fsubs	(%ebp,%eax)
  503cfc:      	fxch	%st(3)
  503cfe:      	fmul	%st(2), %st
  503d00:      	fxch	%st(4)
  503d02:      	fstps	0x6cc(%esp)
  503d09:      	flds	0x4(%ebp,%eax)
  503d0d:      	faddl	0x632380
  503d13:      	fxch	%st(3)
  503d15:      	fmulp	%st, %st(2)
  503d17:      	fstps	0x6c8(%esp)
  503d1e:      	fxch	%st(1)
  503d20:      	fstpl	0x640(%esp)
  503d27:      	fstps	0x6d0(%esp)
  503d2e:      	fildl	0x640(%esp)
  503d35:      	fxch	%st(1)
  503d37:      	fstps	0x6d4(%esp)
  503d3e:      	fsubs	0x4(%ebp,%eax)
  503d42:      	flds	0x6d0(%esp)
  503d49:      	flds	0x6d4(%esp)
  503d50:      	fmul	%st(2), %st
  503d52:      	flds	0x6c8(%esp)
  503d59:      	fmul	%st(3), %st
  503d5b:      	fxch	%st(1)
  503d5d:      	fadds	0x8(%ebp,%eax)
  503d61:      	flds	0x6cc(%esp)
  503d68:      	fmul	%st(4), %st
  503d6a:      	fxch	%st(2)
  503d6c:      	fadds	0xc(%ebp,%eax)
  503d70:      	fxch	%st(3)
  503d72:      	fmulp	%st, %st(4)
  503d74:      	fstps	0x6bc(%esp)
  503d7b:      	fadds	0x10(%ebp,%eax)
  503d7f:      	fxch	%st(2)
  503d81:      	fadds	(%ebp,%eax)
  503d85:      	fxch	%st(1)
  503d87:      	fstps	0x6c0(%esp)
  503d8e:      	fxch	%st(1)
  503d90:      	fstps	0x6c4(%esp)
  503d97:      	fstps	0x6b8(%esp)
  503d9e:      	movl	0x68c(%esp), %ecx
  503da5:      	cmpl	0x33c(%esp,%ecx), %edi
  503dac:      	jl	0x503ea4 <.text+0x102ea4>
  503db2:      	movl	0x38(%esp,%ecx), %edx
  503db6:      	movl	%ecx, %eax
  503db8:      	movl	%edx, 0x68c(%esp)
  503dbf:      	movl	%edx, %ecx
  503dc1:      	cmpl	0x33c(%esp,%edx), %edi
  503dc8:      	jge	0x503db2 <.text+0x102db2>
  503dca:      	flds	0x4(%ebp,%edx)
  503dce:      	fsubs	0x4(%ebp,%eax)
  503dd2:      	flds	0x10(%ebp,%edx)
  503dd6:      	fsubs	0x10(%ebp,%eax)
  503dda:      	fxch	%st(1)
  503ddc:      	fdivrs	0x62c808
  503de2:      	flds	0xc(%ebp,%edx)
  503de6:      	fsubs	0xc(%ebp,%eax)
  503dea:      	fxch	%st(1)
  503dec:      	fmul	%st, %st(2)
  503dee:      	flds	0x8(%ebp,%edx)
  503df2:      	fsubs	0x8(%ebp,%eax)
  503df6:      	fxch	%st(2)
  503df8:      	fmul	%st(1), %st
  503dfa:      	flds	(%ebp,%edx)
  503dfe:      	fsubs	(%ebp,%eax)
  503e02:      	fxch	%st(3)
  503e04:      	fmul	%st(2), %st
  503e06:      	fxch	%st(4)
  503e08:      	fstps	0x6a4(%esp)
  503e0f:      	flds	0x4(%ebp,%eax)
  503e13:      	faddl	0x632380
  503e19:      	fxch	%st(3)
  503e1b:      	fmulp	%st, %st(2)
  503e1d:      	fstps	0x6a0(%esp)
  503e24:      	fxch	%st(1)
  503e26:      	fstpl	0x640(%esp)
  503e2d:      	fstps	0x6a8(%esp)
  503e34:      	fildl	0x640(%esp)
  503e3b:      	fxch	%st(1)
  503e3d:      	fstps	0x6ac(%esp)
  503e44:      	fsubs	0x4(%ebp,%eax)
  503e48:      	flds	0x6a8(%esp)
  503e4f:      	flds	0x6ac(%esp)
  503e56:      	fmul	%st(2), %st
  503e58:      	flds	0x6a0(%esp)
  503e5f:      	fmul	%st(3), %st
  503e61:      	fxch	%st(1)
  503e63:      	fadds	0x8(%ebp,%eax)
  503e67:      	flds	0x6a4(%esp)
  503e6e:      	fmul	%st(4), %st
  503e70:      	fxch	%st(2)
  503e72:      	fadds	0xc(%ebp,%eax)
  503e76:      	fxch	%st(3)
  503e78:      	fmulp	%st, %st(4)
  503e7a:      	fstps	0x694(%esp)
  503e81:      	fadds	0x10(%ebp,%eax)
  503e85:      	fxch	%st(2)
  503e87:      	fadds	(%ebp,%eax)
  503e8b:      	fxch	%st(1)
  503e8d:      	fstps	0x698(%esp)
  503e94:      	fxch	%st(1)
  503e96:      	fstps	0x69c(%esp)
  503e9d:      	fstps	0x690(%esp)
  503ea4:      	flds	0x6b8(%esp)
  503eab:      	faddl	0x632380
  503eb1:      	flds	0x690(%esp)
  503eb8:      	faddl	0x632380
  503ebe:      	fxch	%st(1)
  503ec0:      	fstpl	0x650(%esp)
  503ec7:      	fstpl	0x648(%esp)
  503ece:      	movl	0x650(%esp), %edx
  503ed5:      	movl	0x648(%esp), %ebx
  503edc:      	cmpl	%edx, %ebx
  503ede:      	je	0x504278 <.text+0x103278>
  503ee4:      	jl	0x503f86 <.text+0x102f86>
  503eea:      	flds	0x690(%esp)
  503ef1:      	fsubs	0x6b8(%esp)
  503ef8:      	flds	0x69c(%esp)
  503eff:      	fsubs	0x6c4(%esp)
  503f06:      	fxch	%st(1)
  503f08:      	fdivrs	0x62c808
  503f0e:      	flds	0x698(%esp)
  503f15:      	fsubs	0x6c0(%esp)
  503f1c:      	fxch	%st(2)
  503f1e:      	fmul	%st(1), %st
  503f20:      	flds	0x694(%esp)
  503f27:      	fsubs	0x6bc(%esp)
  503f2e:      	fxch	%st(3)
  503f30:      	fmul	%st(2), %st
  503f32:      	fxch	%st(1)
  503f34:      	fstps	0x24(%esp)
  503f38:      	fxch	%st(1)
  503f3a:      	fmulp	%st, %st(2)
  503f3c:      	fstps	0x20(%esp)
  503f40:      	fildl	0x650(%esp)
  503f47:      	fxch	%st(1)
  503f49:      	fstps	0x28(%esp)
  503f4d:      	fsubs	0x6b8(%esp)
  503f54:      	flds	0x24(%esp)
  503f58:      	flds	0x20(%esp)
  503f5c:      	fmul	%st(2), %st
  503f5e:      	flds	0x28(%esp)
  503f62:      	fmul	%st(3), %st
  503f64:      	fxch	%st(1)
  503f66:      	fadds	0x6c0(%esp)
  503f6d:      	fxch	%st(3)
  503f6f:      	fmulp	%st, %st(2)
  503f71:      	fadds	0x6bc(%esp)
  503f78:      	fxch	%st(1)
  503f7a:      	fadds	0x6c4(%esp)
  503f81:      	jmp	0x50402d <.text+0x10302d>
  503f86:      	movl	%ebx, 0x650(%esp)
  503f8d:      	movl	%edx, %ebx
  503f8f:      	movl	0x650(%esp), %edx
  503f96:      	flds	0x6b8(%esp)
  503f9d:      	fsubs	0x690(%esp)
  503fa4:      	flds	0x6c4(%esp)
  503fab:      	fsubs	0x69c(%esp)
  503fb2:      	fxch	%st(1)
  503fb4:      	fdivrs	0x62c808
  503fba:      	flds	0x6c0(%esp)
  503fc1:      	fsubs	0x698(%esp)
  503fc8:      	fxch	%st(2)
  503fca:      	fmul	%st(1), %st
  503fcc:      	flds	0x6bc(%esp)
  503fd3:      	fsubs	0x694(%esp)
  503fda:      	fxch	%st(3)
  503fdc:      	fmul	%st(2), %st
  503fde:      	fxch	%st(1)
  503fe0:      	fstps	0x24(%esp)
  503fe4:      	fxch	%st(1)
  503fe6:      	fmulp	%st, %st(2)
  503fe8:      	fstps	0x20(%esp)
  503fec:      	fildl	0x650(%esp)
  503ff3:      	fxch	%st(1)
  503ff5:      	fstps	0x28(%esp)
  503ff9:      	fsubs	0x690(%esp)
  504000:      	flds	0x24(%esp)
  504004:      	flds	0x20(%esp)
  504008:      	fmul	%st(2), %st
  50400a:      	flds	0x28(%esp)
  50400e:      	fmul	%st(3), %st
  504010:      	fxch	%st(1)
  504012:      	fadds	0x698(%esp)
  504019:      	fxch	%st(3)
  50401b:      	fmulp	%st, %st(2)
  50401d:      	fadds	0x694(%esp)
  504024:      	fxch	%st(1)
  504026:      	fadds	0x69c(%esp)
  50402d:      	movl	0x18(%esp), %edi
  504031:      	subl	%edx, %ebx
  504033:      	addl	%edx, %edi
  504035:      	flds	0x20(%esp)
  504039:      	fmuls	0x62c814
  50403f:      	flds	0x24(%esp)
  504043:      	fmuls	0x62c814
  504049:      	flds	0x28(%esp)
  50404d:      	fmuls	0x62c814
  504053:      	fxch	%st(2)
  504055:      	fstps	0x2c(%esp)
  504059:      	fstps	0x30(%esp)
  50405d:      	fstps	0x34(%esp)
  504061:      	fxch	%st(1)
  504063:      	flds	0x62c80c
  504069:      	fdiv	%st(1), %st
  50406b:      	fld	%st(2)
  50406d:      	fmul	%st(1), %st
  50406f:      	fld	%st(4)
  504071:      	fmulp	%st, %st(2)
  504073:      	faddl	0x632380
  504079:      	fxch	%st(1)
  50407b:      	faddl	0x632380
  504081:      	fxch	%st(2)
  504083:      	fadds	0x34(%esp)
  504087:      	fxch	%st(1)
  504089:      	fstpl	0x680(%esp)
  504090:      	fxch	%st(1)
  504092:      	fstpl	0x678(%esp)
  504099:      	fxch	%st(2)
  50409b:      	flds	0x62c80c
  5040a1:      	fdiv	%st(3), %st
  5040a3:      	decl	%ebx
  5040a4:      	jmp	0x504180 <.text+0x103180>
  5040a9:      	flds	0x2c(%esp)
  5040ad:      	faddp	%st, %st(2)
  5040af:      	flds	0x30(%esp)
  5040b3:      	faddp	%st, %st(3)
  5040b5:      	fld	%st(1)
  5040b7:      	fmul	%st(1), %st
  5040b9:      	flds	0x34(%esp)
  5040bd:      	fxch	%st(2)
  5040bf:      	fmul	%st(4), %st
  5040c1:      	fxch	%st(2)
  5040c3:      	faddp	%st, %st(5)
  5040c5:      	faddl	0x632380
  5040cb:      	fxch	%st(1)
  5040cd:      	faddl	0x632380
  5040d3:      	fld	%st(4)
  5040d5:      	fxch	%st(2)
  5040d7:      	fstpl	0x658(%esp)
  5040de:      	fstpl	0x668(%esp)
  5040e5:      	fdivrs	0x62c80c
  5040eb:      	movl	0x680(%esp), %ebp
  5040f2:      	movl	0x678(%esp), %esi
  5040f9:      	movl	0x668(%esp), %eax
  504100:      	movl	0x658(%esp), %edx
  504107:      	subl	%ebp, %eax
  504109:      	subl	%esi, %edx
  50410b:      	sarl	$0x4, %eax
  50410e:      	movl	%ebx, 0x8(%esp)
  504112:      	sarl	$0x4, %edx
  504115:      	movl	%eax, 0x670(%esp)
  50411c:      	movl	%edx, 0x660(%esp)
  504123:      	movl	$0x10, %ebx
  504128:      	movl	%ebp, %eax
  50412a:      	movl	%esi, %edx
  50412c:      	sarl	$0x10, %eax
  50412f:      	movl	0x670(%esp), %ecx
  504136:      	sarl	$0x10, %edx
  504139:      	addl	%ecx, %ebp
  50413b:      	movl	0xcfdbd8(,%eax,4), %eax
  504142:      	movl	0x660(%esp), %ecx
  504149:      	movb	(%eax,%edx), %dh
  50414c:      	addl	%ecx, %esi
  50414e:      	movb	(%edi), %dl
  504150:      	incl	%edi
  504151:      	movb	0xcfe440(%edx), %al
  504157:      	decl	%ebx
  504158:      	movb	%al, -0x1(%edi)
  50415b:      	jne	0x504128 <.text+0x103128>
  50415d:      	movl	0x8(%esp), %ebx
  504161:      	movl	0x658(%esp), %eax
  504168:      	movl	0x668(%esp), %edx
  50416f:      	movl	%eax, 0x678(%esp)
  504176:      	movl	%edx, 0x680(%esp)
  50417d:      	subl	$0x10, %ebx
  504180:      	cmpl	$0x10, %ebx
  504183:      	jge	0x5040a9 <.text+0x1030a9>
  504189:      	cmpl	$0x0, %ebx
  50418c:      	movl	0x680(%esp), %ebp
  504193:      	movl	0x678(%esp), %esi
  50419a:      	je	0x504258 <.text+0x103258>
  5041a0:      	fxch	%st(3)
  5041a2:      	fsubs	0x34(%esp)
  5041a6:      	flds	0x28(%esp)
  5041aa:      	fmuls	0x62c810(,%ebx,8)
  5041b1:      	flds	0x20(%esp)
  5041b5:      	fmuls	0x62c810(,%ebx,8)
  5041bc:      	flds	0x24(%esp)
  5041c0:      	fmuls	0x62c810(,%ebx,8)
  5041c7:      	fxch	%st(2)
  5041c9:      	faddp	%st, %st(3)
  5041cb:      	faddp	%st, %st(3)
  5041cd:      	faddp	%st, %st(3)
  5041cf:      	fdivrs	0x62c80c
  5041d5:      	fmul	%st, %st(1)
  5041d7:      	fildl	0x678(%esp)
  5041de:      	fxch	%st(1)
  5041e0:      	fmul	%st(3), %st
  5041e2:      	fildl	0x680(%esp)
  5041e9:      	fxch	%st(2)
  5041eb:      	fsubrp	%st, %st(3)
  5041ed:      	fsubp	%st, %st(1)
  5041ef:      	fxch	%st(1)
  5041f1:      	fmuls	0x62c814(,%ebx,8)
  5041f8:      	fxch	%st(1)
  5041fa:      	fmuls	0x62c814(,%ebx,8)
  504201:      	fxch	%st(1)
  504203:      	faddl	0x632380
  504209:      	fxch	%st(1)
  50420b:      	faddl	0x632380
  504211:      	fxch	%st(1)
  504213:      	fstl	0x660(%esp)
  50421a:      	fxch	%st(1)
  50421c:      	fstl	0x670(%esp)
  504223:      	movl	%ebp, %eax
  504225:      	movl	%esi, %edx
  504227:      	sarl	$0x10, %eax
  50422a:      	movl	0x670(%esp), %ecx
  504231:      	sarl	$0x10, %edx
  504234:      	addl	%ecx, %ebp
  504236:      	movl	0xcfdbd8(,%eax,4), %eax
  50423d:      	movl	0x660(%esp), %ecx
  504244:      	movb	(%eax,%edx), %dh
  504247:      	addl	%ecx, %esi
  504249:      	movb	(%edi), %dl
  50424b:      	incl	%edi
  50424c:      	movb	0xcfe440(%edx), %al
  504252:      	decl	%ebx
  504253:      	movb	%al, -0x1(%edi)
  504256:      	jne	0x504223 <.text+0x103223>
  504258:      	sarl	$0x10, %ebp
  50425b:      	xorl	%edx, %edx
  50425d:      	sarl	$0x10, %esi
  504260:      	movb	(%edi), %dl
  504262:      	movl	0xcfdbd8(,%ebp,4), %eax
  504269:      	fcompp
  50426b:      	movb	(%eax,%esi), %dh
  50426e:      	fcompp
  504270:      	movb	0xcfe440(%edx), %al
  504276:      	movb	%al, (%edi)
  504278:      	flds	0x694(%esp)
  50427f:      	fadds	0x6ac(%esp)
  504286:      	flds	0x69c(%esp)
  50428d:      	fadds	0x6a4(%esp)
  504294:      	flds	0x698(%esp)
  50429b:      	fadds	0x6a0(%esp)
  5042a2:      	flds	0x690(%esp)
  5042a9:      	fadds	0x6a8(%esp)
  5042b0:      	fxch	%st(3)
  5042b2:      	fstps	0x694(%esp)
  5042b9:      	fstps	0x698(%esp)
  5042c0:      	fstps	0x69c(%esp)
  5042c7:      	fstps	0x690(%esp)
  5042ce:      	flds	0x6bc(%esp)
  5042d5:      	fadds	0x6d4(%esp)
  5042dc:      	flds	0x6c4(%esp)
  5042e3:      	fadds	0x6cc(%esp)
  5042ea:      	flds	0x6c0(%esp)
  5042f1:      	fadds	0x6c8(%esp)
  5042f8:      	flds	0x6b8(%esp)
  5042ff:      	fadds	0x6d0(%esp)
  504306:      	fxch	%st(3)
  504308:      	fstps	0x6bc(%esp)
  50430f:      	fstps	0x6c0(%esp)
  504316:      	fstps	0x6c4(%esp)
  50431d:      	fstps	0x6b8(%esp)
  504324:      	movl	0x18(%esp), %esi
  504328:      	movl	0xc(%esp), %eax
  50432c:      	movl	(%esp), %ebp
  50432f:      	addl	%eax, %esi
  504331:      	movl	0x4(%esp), %edi
  504335:      	movl	%esi, 0x18(%esp)
  504339:      	incl	%edi
  50433a:      	jmp	0x503c80 <.text+0x102c80>
  50433f:      	addl	$0x6d8, %esp            # imm = 0x6D8
  504345:      	popl	%ebp
  504346:      	popl	%edi
  504347:      	popl	%esi
  504348:      	popl	%ebx
  504349:      	popl	%ebp
  50434a:      	retl
