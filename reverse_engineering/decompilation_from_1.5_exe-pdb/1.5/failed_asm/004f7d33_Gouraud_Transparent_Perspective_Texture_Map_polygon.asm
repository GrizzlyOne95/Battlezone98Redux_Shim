; Entry: 004f7d33
; Name: Gouraud_Transparent_Perspective_Texture_Map_polygon
; Signature: void Gouraud_Transparent_Perspective_Texture_Map_polygon(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
; Stop: 0x004f86e3
; Reason: Exception while decompiling 004f7d33: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x004f7d33 --stop-address=0x004f86e3 C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  4f7d33:      	pushl	%ebp
  4f7d34:      	movl	%esp, %ebp
  4f7d36:      	pushl	%ebx
  4f7d37:      	pushl	%esi
  4f7d38:      	pushl	%edi
  4f7d39:      	movl	0x14(%ebp), %ebx
  4f7d3c:      	pushl	%ebp
  4f7d3d:      	movl	0xcfdbc0, %eax
  4f7d42:      	subl	$0x6f8, %esp            # imm = 0x6F8
  4f7d48:      	cmpl	%ebx, %eax
  4f7d4a:      	je	0x4f7dba <.text+0xf6dba>
  4f7d4c:      	movl	%ebx, 0xcfdbc0
  4f7d52:      	leal	0xcfdbd8, %edx
  4f7d58:      	movl	(%ebx), %eax
  4f7d5a:      	movl	0x4(%ebx), %ecx
  4f7d5d:      	leal	0x8(%ebx), %esi
  4f7d60:      	movl	%ecx, 0x4(%esp)
  4f7d64:      	movl	%eax, %edi
  4f7d66:      	addl	$0x3, %ecx
  4f7d69:      	addl	%esi, %edi
  4f7d6b:      	leal	(%esi,%eax,2), %ebx
  4f7d6e:      	leal	(%eax,%eax,2), %eax
  4f7d71:      	movl	%esi, -0x4(%edx)
  4f7d74:      	movl	%esi, -0x8(%edx)
  4f7d77:      	movl	%esi, -0xc(%edx)
  4f7d7a:      	movl	%esi, -0x10(%edx)
  4f7d7d:      	movl	%esi, (%edx)
  4f7d7f:      	movl	%edi, 0x4(%edx)
  4f7d82:      	movl	%ebx, 0x8(%edx)
  4f7d85:      	addl	%eax, %esi
  4f7d87:      	addl	%eax, %edi
  4f7d89:      	addl	%eax, %ebx
  4f7d8b:      	addl	$0xc, %edx
  4f7d8e:      	subl	$0x3, %ecx
  4f7d91:      	jge	0x4f7d7d <.text+0xf6d7d>
  4f7d93:      	movl	0x4(%esp), %edx
  4f7d97:      	movl	0xcfdbd4(,%edx,4), %eax
  4f7d9e:      	movl	%eax, 0xcfdbd8(,%edx,4)
  4f7da5:      	movl	%eax, 0xcfdbdc(,%edx,4)
  4f7dac:      	movl	%eax, 0xcfdbe0(,%edx,4)
  4f7db3:      	movl	%eax, 0xcfdbe4(,%edx,4)
  4f7dba:      	movl	0x14(%ebp), %ebx
  4f7dbd:      	movl	$0x186a0, %edx          # imm = 0x186A0
  4f7dc2:      	movl	0xc(%ebp), %esi
  4f7dc5:      	movl	0x10(%ebp), %eax
  4f7dc8:      	fildl	0x4(%ebx)
  4f7dcb:      	movl	(%ebx), %ecx
  4f7dcd:      	movl	%esi, (%esp)
  4f7dd0:      	shll	$0x3, %eax
  4f7dd3:      	leal	0x8(%ebx), %edi
  4f7dd6:      	fsubs	0x62c808
  4f7ddc:      	fildl	(%ebx)
  4f7dde:      	movl	%ecx, 0x10(%esp)
  4f7de2:      	leal	(%eax,%eax,2), %ecx
  4f7de5:      	xorl	%eax, %eax
  4f7de7:      	movl	%edi, 0x1c(%esp)
  4f7deb:      	fsubs	0x62c808
  4f7df1:      	flds	0x62c808
  4f7df7:      	fsubs	0x14(%esi,%eax)
  4f7dfb:      	flds	0x4(%esi,%eax)
  4f7dff:      	faddl	0x632380
  4f7e05:      	fxch	%st(1)
  4f7e07:      	flds	0xc(%esi,%eax)
  4f7e0b:      	fmul	%st(3), %st
  4f7e0d:      	flds	0x10(%esi,%eax)
  4f7e11:      	fmul	%st(5), %st
  4f7e13:      	fxch	%st(3)
  4f7e15:      	fstpl	0x640(%esp)
  4f7e1c:      	fxch	%st(1)
  4f7e1e:      	fmuls	0x62c810
  4f7e24:      	fxch	%st(2)
  4f7e26:      	fstps	0x10(%esi,%eax)
  4f7e2a:      	fstps	0xc(%esi,%eax)
  4f7e2e:      	fstps	0x14(%esi,%eax)
  4f7e32:      	movl	0x640(%esp), %edi
  4f7e39:      	movl	%eax, 0x320(%esp,%eax)
  4f7e40:      	movl	%eax, 0x50(%esp,%eax)
  4f7e44:      	movl	%edi, 0x33c(%esp,%eax)
  4f7e4b:      	addl	$0x18, %eax
  4f7e4e:      	cmpl	%edx, %edi
  4f7e50:      	jg	0x4f7e56 <.text+0xf6e56>
  4f7e52:      	movl	%eax, %ebx
  4f7e54:      	movl	%edi, %edx
  4f7e56:      	cmpl	%ecx, %eax
  4f7e58:      	jne	0x4f7df1 <.text+0xf6df1>
  4f7e5a:      	subl	$0x18, %ebx
  4f7e5d:      	leal	-0x18(%eax), %ecx
  4f7e60:      	fcompp
  4f7e62:      	movl	$0x0, 0x320(%esp,%eax)
  4f7e6d:      	movl	%ecx, 0x38(%esp)
  4f7e71:      	movl	0x8(%ebp), %edi
  4f7e74:      	movl	%ebx, 0x6c8(%esp)
  4f7e7b:      	movl	%ebx, 0x698(%esp)
  4f7e82:      	movl	%ebx, 0x6cc(%esp)
  4f7e89:      	movl	%esi, %ebp
  4f7e8b:      	movl	0x20(%edi), %eax
  4f7e8e:      	movl	(%edi), %ecx
  4f7e90:      	addl	%edx, %eax
  4f7e92:      	movl	0x14(%edi), %esi
  4f7e95:      	movl	0x1c(%edi), %edi
  4f7e98:      	imull	%ecx
  4f7e9a:      	addl	%edi, %esi
  4f7e9c:      	movl	%ecx, 0xc(%esp)
  4f7ea0:      	addl	%eax, %esi
  4f7ea2:      	movl	0x33c(%esp,%ebx), %edi
  4f7ea9:      	movl	%esi, 0x18(%esp)
  4f7ead:      	movl	%ebx, 0x69c(%esp)
  4f7eb4:      	movl	0x6cc(%esp), %ecx
  4f7ebb:      	movl	0x33c(%esp,%ecx), %eax
  4f7ec2:      	movl	%edi, 0x4(%esp)
  4f7ec6:      	cmpl	%eax, %edi
  4f7ec8:      	jl	0x4f7ff7 <.text+0xf6ff7>
  4f7ece:      	movl	0x338(%esp,%ecx), %edx
  4f7ed5:      	movl	%ecx, %eax
  4f7ed7:      	movl	%edx, 0x6cc(%esp)
  4f7ede:      	cmpl	0x698(%esp), %edx
  4f7ee5:      	je	0x4f86d7 <.text+0xf76d7>
  4f7eeb:      	movl	0x33c(%esp,%edx), %esi
  4f7ef2:      	movl	%edx, %ecx
  4f7ef4:      	cmpl	%esi, %edi
  4f7ef6:      	jge	0x4f7ece <.text+0xf6ece>
  4f7ef8:      	flds	0x14(%ebp,%edx)
  4f7efc:      	fsubs	0x14(%ebp,%eax)
  4f7f00:      	flds	0x4(%ebp,%edx)
  4f7f04:      	fsubs	0x4(%ebp,%eax)
  4f7f08:      	flds	0x10(%ebp,%edx)
  4f7f0c:      	fsubs	0x10(%ebp,%eax)
  4f7f10:      	fxch	%st(1)
  4f7f12:      	fdivrs	0x62c808
  4f7f18:      	flds	0xc(%ebp,%edx)
  4f7f1c:      	fsubs	0xc(%ebp,%eax)
  4f7f20:      	fxch	%st(1)
  4f7f22:      	fmul	%st, %st(2)
  4f7f24:      	flds	0x8(%ebp,%edx)
  4f7f28:      	fsubs	0x8(%ebp,%eax)
  4f7f2c:      	fxch	%st(2)
  4f7f2e:      	fmul	%st(1), %st
  4f7f30:      	flds	(%ebp,%edx)
  4f7f34:      	fsubs	(%ebp,%eax)
  4f7f38:      	fxch	%st(3)
  4f7f3a:      	fmul	%st(2), %st
  4f7f3c:      	fxch	%st(4)
  4f7f3e:      	fstps	0x6e8(%esp)
  4f7f45:      	fstps	0x6e4(%esp)
  4f7f4c:      	fmul	%st, %st(3)
  4f7f4e:      	flds	0x4(%ebp,%eax)
  4f7f52:      	faddl	0x632380
  4f7f58:      	fxch	%st(2)
  4f7f5a:      	fmulp	%st, %st(1)
  4f7f5c:      	fxch	%st(3)
  4f7f5e:      	fstps	0x6f4(%esp)
  4f7f65:      	fstpl	0x640(%esp)
  4f7f6c:      	fstps	0x6f0(%esp)
  4f7f73:      	fildl	0x640(%esp)
  4f7f7a:      	fxch	%st(1)
  4f7f7c:      	fstps	0x6ec(%esp)
  4f7f83:      	fsubs	0x4(%ebp,%eax)
  4f7f87:      	flds	0x6ec(%esp)
  4f7f8e:      	flds	0x6f0(%esp)
  4f7f95:      	fmul	%st(2), %st
  4f7f97:      	flds	0x6e4(%esp)
  4f7f9e:      	fmul	%st(3), %st
  4f7fa0:      	flds	0x6f4(%esp)
  4f7fa7:      	fmul	%st(4), %st
  4f7fa9:      	fxch	%st(2)
  4f7fab:      	fadds	0x8(%ebp,%eax)
  4f7faf:      	flds	0x6e8(%esp)
  4f7fb6:      	fmul	%st(5), %st
  4f7fb8:      	fxch	%st(2)
  4f7fba:      	fadds	0xc(%ebp,%eax)
  4f7fbe:      	fxch	%st(4)
  4f7fc0:      	fmulp	%st, %st(5)
  4f7fc2:      	fstps	0x6d4(%esp)
  4f7fc9:      	fadds	0x10(%ebp,%eax)
  4f7fcd:      	fxch	%st(3)
  4f7fcf:      	fadds	(%ebp,%eax)
  4f7fd3:      	fxch	%st(2)
  4f7fd5:      	fstps	0x6d8(%esp)
  4f7fdc:      	fadds	0x14(%ebp,%eax)
  4f7fe0:      	fxch	%st(2)
  4f7fe2:      	fstps	0x6dc(%esp)
  4f7fe9:      	fstps	0x6d0(%esp)
  4f7ff0:      	fstps	0x6e0(%esp)
  4f7ff7:      	movl	0x69c(%esp), %ecx
  4f7ffe:      	cmpl	0x33c(%esp,%ecx), %edi
  4f8005:      	jl	0x4f8122 <.text+0xf7122>
  4f800b:      	movl	0x38(%esp,%ecx), %edx
  4f800f:      	movl	%ecx, %eax
  4f8011:      	movl	%edx, 0x69c(%esp)
  4f8018:      	movl	%edx, %ecx
  4f801a:      	cmpl	0x33c(%esp,%edx), %edi
  4f8021:      	jge	0x4f800b <.text+0xf700b>
  4f8023:      	flds	0x14(%ebp,%edx)
  4f8027:      	fsubs	0x14(%ebp,%eax)
  4f802b:      	flds	0x4(%ebp,%edx)
  4f802f:      	fsubs	0x4(%ebp,%eax)
  4f8033:      	flds	0x10(%ebp,%edx)
  4f8037:      	fsubs	0x10(%ebp,%eax)
  4f803b:      	fxch	%st(1)
  4f803d:      	fdivrs	0x62c808
  4f8043:      	flds	0xc(%ebp,%edx)
  4f8047:      	fsubs	0xc(%ebp,%eax)
  4f804b:      	fxch	%st(1)
  4f804d:      	fmul	%st, %st(2)
  4f804f:      	flds	0x8(%ebp,%edx)
  4f8053:      	fsubs	0x8(%ebp,%eax)
  4f8057:      	fxch	%st(2)
  4f8059:      	fmul	%st(1), %st
  4f805b:      	flds	(%ebp,%edx)
  4f805f:      	fsubs	(%ebp,%eax)
  4f8063:      	fxch	%st(3)
  4f8065:      	fmul	%st(2), %st
  4f8067:      	fxch	%st(4)
  4f8069:      	fstps	0x6b8(%esp)
  4f8070:      	fstps	0x6b4(%esp)
  4f8077:      	fmul	%st, %st(3)
  4f8079:      	flds	0x4(%ebp,%eax)
  4f807d:      	faddl	0x632380
  4f8083:      	fxch	%st(2)
  4f8085:      	fmulp	%st, %st(1)
  4f8087:      	fxch	%st(3)
  4f8089:      	fstps	0x6c4(%esp)
  4f8090:      	fstpl	0x640(%esp)
  4f8097:      	fstps	0x6c0(%esp)
  4f809e:      	fildl	0x640(%esp)
  4f80a5:      	fxch	%st(1)
  4f80a7:      	fstps	0x6bc(%esp)
  4f80ae:      	fsubs	0x4(%ebp,%eax)
  4f80b2:      	flds	0x6bc(%esp)
  4f80b9:      	flds	0x6c0(%esp)
  4f80c0:      	fmul	%st(2), %st
  4f80c2:      	flds	0x6b4(%esp)
  4f80c9:      	fmul	%st(3), %st
  4f80cb:      	flds	0x6c4(%esp)
  4f80d2:      	fmul	%st(4), %st
  4f80d4:      	fxch	%st(2)
  4f80d6:      	fadds	0x8(%ebp,%eax)
  4f80da:      	flds	0x6b8(%esp)
  4f80e1:      	fmul	%st(5), %st
  4f80e3:      	fxch	%st(2)
  4f80e5:      	fadds	0xc(%ebp,%eax)
  4f80e9:      	fxch	%st(4)
  4f80eb:      	fmulp	%st, %st(5)
  4f80ed:      	fstps	0x6a4(%esp)
  4f80f4:      	fadds	0x10(%ebp,%eax)
  4f80f8:      	fxch	%st(3)
  4f80fa:      	fadds	(%ebp,%eax)
  4f80fe:      	fxch	%st(2)
  4f8100:      	fstps	0x6a8(%esp)
  4f8107:      	fadds	0x14(%ebp,%eax)
  4f810b:      	fxch	%st(2)
  4f810d:      	fstps	0x6ac(%esp)
  4f8114:      	fstps	0x6a0(%esp)
  4f811b:      	fstps	0x6b0(%esp)
  4f8122:      	flds	0x6d0(%esp)
  4f8129:      	faddl	0x632380
  4f812f:      	flds	0x6a0(%esp)
  4f8136:      	faddl	0x632380
  4f813c:      	fxch	%st(1)
  4f813e:      	fstpl	0x650(%esp)
  4f8145:      	fstpl	0x648(%esp)
  4f814c:      	movl	0x650(%esp), %edx
  4f8153:      	movl	0x648(%esp), %ebx
  4f815a:      	cmpl	%edx, %ebx
  4f815c:      	je	0x4f85e6 <.text+0xf75e6>
  4f8162:      	jl	0x4f8247 <.text+0xf7247>
  4f8168:      	flds	0x6b0(%esp)
  4f816f:      	fsubs	0x6e0(%esp)
  4f8176:      	flds	0x6a0(%esp)
  4f817d:      	fsubs	0x6d0(%esp)
  4f8184:      	flds	0x6ac(%esp)
  4f818b:      	fsubs	0x6dc(%esp)
  4f8192:      	fxch	%st(1)
  4f8194:      	fdivrs	0x62c808
  4f819a:      	flds	0x6a8(%esp)
  4f81a1:      	fsubs	0x6d8(%esp)
  4f81a8:      	fxch	%st(2)
  4f81aa:      	fmul	%st(1), %st
  4f81ac:      	flds	0x6a4(%esp)
  4f81b3:      	fsubs	0x6d4(%esp)
  4f81ba:      	fxch	%st(3)
  4f81bc:      	fmul	%st(2), %st
  4f81be:      	fxch	%st(1)
  4f81c0:      	fstps	0x24(%esp)
  4f81c4:      	fxch	%st(1)
  4f81c6:      	fmul	%st, %st(2)
  4f81c8:      	fxch	%st(1)
  4f81ca:      	fstps	0x20(%esp)
  4f81ce:      	fmulp	%st, %st(2)
  4f81d0:      	fildl	0x650(%esp)
  4f81d7:      	fxch	%st(1)
  4f81d9:      	fstps	0x28(%esp)
  4f81dd:      	fsubs	0x6d0(%esp)
  4f81e4:      	fld	%st(1)
  4f81e6:      	faddl	0x632380
  4f81ec:      	fxch	%st(2)
  4f81ee:      	fmul	%st(1), %st
  4f81f0:      	flds	0x24(%esp)
  4f81f4:      	fxch	%st(3)
  4f81f6:      	fstpl	0x690(%esp)
  4f81fd:      	fadds	0x6e0(%esp)
  4f8204:      	fxch	%st(2)
  4f8206:      	flds	0x20(%esp)
  4f820a:      	fmul	%st(2), %st
  4f820c:      	fxch	%st(3)
  4f820e:      	faddl	0x632380
  4f8214:      	fxch	%st(3)
  4f8216:      	flds	0x28(%esp)
  4f821a:      	fmul	%st(3), %st
  4f821c:      	fxch	%st(4)
  4f821e:      	fstpl	0x678(%esp)
  4f8225:      	fadds	0x6d8(%esp)
  4f822c:      	fxch	%st(2)
  4f822e:      	fmulp	%st, %st(1)
  4f8230:      	fxch	%st(2)
  4f8232:      	fadds	0x6d4(%esp)
  4f8239:      	fxch	%st(2)
  4f823b:      	fadds	0x6dc(%esp)
  4f8242:      	jmp	0x4f8331 <.text+0xf7331>
  4f8247:      	movl	%ebx, 0x650(%esp)
  4f824e:      	movl	%edx, %ebx
  4f8250:      	movl	0x650(%esp), %edx
  4f8257:      	flds	0x6e0(%esp)
  4f825e:      	fsubs	0x6b0(%esp)
  4f8265:      	flds	0x6d0(%esp)
  4f826c:      	fsubs	0x6a0(%esp)
  4f8273:      	flds	0x6dc(%esp)
  4f827a:      	fsubs	0x6ac(%esp)
  4f8281:      	fxch	%st(1)
  4f8283:      	fdivrs	0x62c808
  4f8289:      	flds	0x6d8(%esp)
  4f8290:      	fsubs	0x6a8(%esp)
  4f8297:      	fxch	%st(2)
  4f8299:      	fmul	%st(1), %st
  4f829b:      	flds	0x6d4(%esp)
  4f82a2:      	fsubs	0x6a4(%esp)
  4f82a9:      	fxch	%st(3)
  4f82ab:      	fmul	%st(2), %st
  4f82ad:      	fxch	%st(1)
  4f82af:      	fstps	0x24(%esp)
  4f82b3:      	fxch	%st(1)
  4f82b5:      	fmul	%st, %st(2)
  4f82b7:      	fxch	%st(1)
  4f82b9:      	fstps	0x20(%esp)
  4f82bd:      	fmulp	%st, %st(2)
  4f82bf:      	fildl	0x650(%esp)
  4f82c6:      	fxch	%st(1)
  4f82c8:      	fstps	0x28(%esp)
  4f82cc:      	fsubs	0x6a0(%esp)
  4f82d3:      	fld	%st(1)
  4f82d5:      	faddl	0x632380
  4f82db:      	fxch	%st(2)
  4f82dd:      	fmul	%st(1), %st
  4f82df:      	flds	0x24(%esp)
  4f82e3:      	fxch	%st(3)
  4f82e5:      	fstpl	0x690(%esp)
  4f82ec:      	fadds	0x6b0(%esp)
  4f82f3:      	fxch	%st(2)
  4f82f5:      	flds	0x20(%esp)
  4f82f9:      	fmul	%st(2), %st
  4f82fb:      	fxch	%st(3)
  4f82fd:      	faddl	0x632380
  4f8303:      	fxch	%st(3)
  4f8305:      	flds	0x28(%esp)
  4f8309:      	fmul	%st(3), %st
  4f830b:      	fxch	%st(4)
  4f830d:      	fstpl	0x678(%esp)
  4f8314:      	fadds	0x6a8(%esp)
  4f831b:      	fxch	%st(2)
  4f831d:      	fmulp	%st, %st(1)
  4f831f:      	fxch	%st(2)
  4f8321:      	fadds	0x6a4(%esp)
  4f8328:      	fxch	%st(2)
  4f832a:      	fadds	0x6ac(%esp)
  4f8331:      	movl	0x690(%esp), %eax
  4f8338:      	movl	0x18(%esp), %edi
  4f833c:      	andl	$0xffff, %eax           # imm = 0xFFFF
  4f8341:      	subl	%edx, %ebx
  4f8343:      	orl	$0xfffe0000, %eax       # imm = 0xFFFE0000
  4f8348:      	addl	%edx, %edi
  4f834a:      	movl	%eax, 0x690(%esp)
  4f8351:      	flds	0x20(%esp)
  4f8355:      	fmuls	0x62c814
  4f835b:      	flds	0x24(%esp)
  4f835f:      	fmuls	0x62c814
  4f8365:      	flds	0x28(%esp)
  4f8369:      	fmuls	0x62c814
  4f836f:      	fxch	%st(2)
  4f8371:      	fstps	0x2c(%esp)
  4f8375:      	fstps	0x30(%esp)
  4f8379:      	fstps	0x34(%esp)
  4f837d:      	fxch	%st(2)
  4f837f:      	flds	0x62c80c
  4f8385:      	fdiv	%st(1), %st
  4f8387:      	fld	%st(3)
  4f8389:      	fmul	%st(1), %st
  4f838b:      	fld	%st(3)
  4f838d:      	fmulp	%st, %st(2)
  4f838f:      	faddl	0x632380
  4f8395:      	fxch	%st(1)
  4f8397:      	faddl	0x632380
  4f839d:      	fxch	%st(2)
  4f839f:      	fadds	0x34(%esp)
  4f83a3:      	fxch	%st(1)
  4f83a5:      	fstpl	0x660(%esp)
  4f83ac:      	fxch	%st(1)
  4f83ae:      	fstpl	0x658(%esp)
  4f83b5:      	flds	0x62c80c
  4f83bb:      	fdiv	%st(1), %st
  4f83bd:      	decl	%ebx
  4f83be:      	jmp	0x4f84c2 <.text+0xf74c2>
  4f83c3:      	flds	0x2c(%esp)
  4f83c7:      	faddp	%st, %st(3)
  4f83c9:      	flds	0x30(%esp)
  4f83cd:      	faddp	%st, %st(4)
  4f83cf:      	fld	%st(2)
  4f83d1:      	fmul	%st(1), %st
  4f83d3:      	flds	0x34(%esp)
  4f83d7:      	fxch	%st(2)
  4f83d9:      	fmul	%st(5), %st
  4f83db:      	fxch	%st(2)
  4f83dd:      	faddp	%st, %st(3)
  4f83df:      	faddl	0x632380
  4f83e5:      	fxch	%st(1)
  4f83e7:      	faddl	0x632380
  4f83ed:      	fld	%st(2)
  4f83ef:      	fxch	%st(2)
  4f83f1:      	fstpl	0x668(%esp)
  4f83f8:      	fstpl	0x670(%esp)
  4f83ff:      	fdivrs	0x62c80c
  4f8405:      	movl	0x660(%esp), %ebp
  4f840c:      	movl	0x658(%esp), %esi
  4f8413:      	movl	0x670(%esp), %eax
  4f841a:      	movl	0x668(%esp), %edx
  4f8421:      	subl	%ebp, %eax
  4f8423:      	subl	%esi, %edx
  4f8425:      	sarl	$0x4, %eax
  4f8428:      	movl	%ebx, 0x8(%esp)
  4f842c:      	sarl	$0x4, %edx
  4f842f:      	movl	0x678(%esp), %ebx
  4f8436:      	movl	%edx, 0x680(%esp)
  4f843d:      	andl	$0xffff, %ebx           # imm = 0xFFFF
  4f8443:      	movl	%eax, 0x688(%esp)
  4f844a:      	orl	$0x1e0000, %ebx         # imm = 0x1E0000
  4f8450:      	movl	%ebp, %eax
  4f8452:      	movl	%esi, %edx
  4f8454:      	sarl	$0x10, %eax
  4f8457:      	movl	0x688(%esp), %ecx
  4f845e:      	sarl	$0x10, %edx
  4f8461:      	addl	%ecx, %ebp
  4f8463:      	movl	0xcfdbd8(,%eax,4), %eax
  4f846a:      	movl	0x680(%esp), %ecx
  4f8471:      	movb	(%eax,%edx), %dl
  4f8474:      	incl	%edi
  4f8475:      	movb	%bh, %dh
  4f8477:      	addl	%ecx, %esi
  4f8479:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  4f847f:      	movl	0x690(%esp), %ecx
  4f8486:      	cmpb	$-0x1, %dl
  4f8489:      	je	0x4f8494 <.text+0xf7494>
  4f848b:      	movb	0xd1e480(%edx), %al
  4f8491:      	movb	%al, -0x1(%edi)
  4f8494:      	addl	%ecx, %ebx
  4f8496:      	jge	0x4f8450 <.text+0xf7450>
  4f8498:      	movl	%ebx, 0x678(%esp)
  4f849f:      	movl	0x8(%esp), %ebx
  4f84a3:      	movl	0x668(%esp), %eax
  4f84aa:      	movl	0x670(%esp), %edx
  4f84b1:      	movl	%eax, 0x658(%esp)
  4f84b8:      	movl	%edx, 0x660(%esp)
  4f84bf:      	subl	$0x10, %ebx
  4f84c2:      	cmpl	$0x10, %ebx
  4f84c5:      	jge	0x4f83c3 <.text+0xf73c3>
  4f84cb:      	movl	0x678(%esp), %eax
  4f84d2:      	movl	%ebx, %ecx
  4f84d4:      	decl	%ebx
  4f84d5:      	movl	0x660(%esp), %ebp
  4f84dc:      	shll	$0x11, %ebx
  4f84df:      	andl	$0xffff, %eax           # imm = 0xFFFF
  4f84e4:      	movl	0x658(%esp), %esi
  4f84eb:      	orl	%eax, %ebx
  4f84ed:      	cmpl	$0x0, %ecx
  4f84f0:      	je	0x4f85c1 <.text+0xf75c1>
  4f84f6:      	fxch	%st(1)
  4f84f8:      	fsubs	0x34(%esp)
  4f84fc:      	flds	0x28(%esp)
  4f8500:      	fmuls	0x62c810(,%ecx,8)
  4f8507:      	flds	0x20(%esp)
  4f850b:      	fmuls	0x62c810(,%ecx,8)
  4f8512:      	flds	0x24(%esp)
  4f8516:      	fmuls	0x62c810(,%ecx,8)
  4f851d:      	fxch	%st(2)
  4f851f:      	faddp	%st, %st(3)
  4f8521:      	faddp	%st, %st(4)
  4f8523:      	faddp	%st, %st(4)
  4f8525:      	fdivrs	0x62c80c
  4f852b:      	fmul	%st, %st(2)
  4f852d:      	fildl	0x658(%esp)
  4f8534:      	fxch	%st(1)
  4f8536:      	fmul	%st(4), %st
  4f8538:      	fildl	0x660(%esp)
  4f853f:      	fxch	%st(2)
  4f8541:      	fsubrp	%st, %st(4)
  4f8543:      	fsubp	%st, %st(1)
  4f8545:      	fxch	%st(2)
  4f8547:      	fmuls	0x62c814(,%ecx,8)
  4f854e:      	fxch	%st(2)
  4f8550:      	fmuls	0x62c814(,%ecx,8)
  4f8557:      	fxch	%st(2)
  4f8559:      	faddl	0x632380
  4f855f:      	fxch	%st(2)
  4f8561:      	faddl	0x632380
  4f8567:      	fxch	%st(2)
  4f8569:      	fstl	0x680(%esp)
  4f8570:      	fxch	%st(2)
  4f8572:      	fstl	0x688(%esp)
  4f8579:      	movl	%ebp, %eax
  4f857b:      	movl	%esi, %edx
  4f857d:      	sarl	$0x10, %eax
  4f8580:      	movl	0x688(%esp), %ecx
  4f8587:      	sarl	$0x10, %edx
  4f858a:      	addl	%ecx, %ebp
  4f858c:      	movl	0xcfdbd8(,%eax,4), %eax
  4f8593:      	movl	0x680(%esp), %ecx
  4f859a:      	movb	(%eax,%edx), %dl
  4f859d:      	incl	%edi
  4f859e:      	movb	%bh, %dh
  4f85a0:      	addl	%ecx, %esi
  4f85a2:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  4f85a8:      	movl	0x690(%esp), %ecx
  4f85af:      	cmpb	$-0x1, %dl
  4f85b2:      	je	0x4f85bd <.text+0xf75bd>
  4f85b4:      	movb	0xd1e480(%edx), %al
  4f85ba:      	movb	%al, -0x1(%edi)
  4f85bd:      	addl	%ecx, %ebx
  4f85bf:      	jge	0x4f8579 <.text+0xf7579>
  4f85c1:      	sarl	$0x10, %ebp
  4f85c4:      	xorl	%edx, %edx
  4f85c6:      	sarl	$0x10, %esi
  4f85c9:      	movb	%bh, %dh
  4f85cb:      	movl	0xcfdbd8(,%ebp,4), %eax
  4f85d2:      	fcompp
  4f85d4:      	movb	(%eax,%esi), %dl
  4f85d7:      	fcompp
  4f85d9:      	cmpb	$-0x1, %dl
  4f85dc:      	je	0x4f85e6 <.text+0xf75e6>
  4f85de:      	movb	0xd1e480(%edx), %al
  4f85e4:      	movb	%al, (%edi)
  4f85e6:      	flds	0x6b0(%esp)
  4f85ed:      	fadds	0x6c4(%esp)
  4f85f4:      	flds	0x6a4(%esp)
  4f85fb:      	fadds	0x6c0(%esp)
  4f8602:      	flds	0x6ac(%esp)
  4f8609:      	fadds	0x6b8(%esp)
  4f8610:      	flds	0x6a8(%esp)
  4f8617:      	fadds	0x6b4(%esp)
  4f861e:      	flds	0x6a0(%esp)
  4f8625:      	fadds	0x6bc(%esp)
  4f862c:      	fxch	%st(3)
  4f862e:      	fstps	0x6a4(%esp)
  4f8635:      	fstps	0x6a8(%esp)
  4f863c:      	fstps	0x6ac(%esp)
  4f8643:      	fstps	0x6a0(%esp)
  4f864a:      	fstps	0x6b0(%esp)
  4f8651:      	flds	0x6e0(%esp)
  4f8658:      	fadds	0x6f4(%esp)
  4f865f:      	flds	0x6d4(%esp)
  4f8666:      	fadds	0x6f0(%esp)
  4f866d:      	flds	0x6dc(%esp)
  4f8674:      	fadds	0x6e8(%esp)
  4f867b:      	flds	0x6d8(%esp)
  4f8682:      	fadds	0x6e4(%esp)
  4f8689:      	flds	0x6d0(%esp)
  4f8690:      	fadds	0x6ec(%esp)
  4f8697:      	fxch	%st(3)
  4f8699:      	fstps	0x6d4(%esp)
  4f86a0:      	fstps	0x6d8(%esp)
  4f86a7:      	fstps	0x6dc(%esp)
  4f86ae:      	fstps	0x6d0(%esp)
  4f86b5:      	fstps	0x6e0(%esp)
  4f86bc:      	movl	0x18(%esp), %esi
  4f86c0:      	movl	0xc(%esp), %eax
  4f86c4:      	movl	(%esp), %ebp
  4f86c7:      	addl	%eax, %esi
  4f86c9:      	movl	0x4(%esp), %edi
  4f86cd:      	movl	%esi, 0x18(%esp)
  4f86d1:      	incl	%edi
  4f86d2:      	jmp	0x4f7eb4 <.text+0xf6eb4>
  4f86d7:      	addl	$0x6f8, %esp            # imm = 0x6F8
  4f86dd:      	popl	%ebp
  4f86de:      	popl	%edi
  4f86df:      	popl	%esi
  4f86e0:      	popl	%ebx
  4f86e1:      	popl	%ebp
  4f86e2:      	retl
