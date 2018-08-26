	.file	"creosote_v2.cpp"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.section	.text.startup,"ax",@progbits
.LHOTB0:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB1310:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA1310
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movl	$_ZSt3cin, %edi
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	leaq	8(%rsp), %rsi
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
.LEHB0:
	call	_ZNSirsERi
	leaq	12(%rsp), %rsi
	movq	%rax, %rdi
	call	_ZNSirsERi
	leaq	16(%rsp), %rsi
	movq	%rax, %rdi
	call	_ZNSirsERi
	leaq	20(%rsp), %rsi
	movq	%rax, %rdi
	call	_ZNSirsERi
	movslq	8(%rsp), %rbx
	testq	%rbx, %rbx
	je	.L31
	movabsq	$4611686018427387903, %rax
	cmpq	%rax, %rbx
	ja	.L64
	leaq	0(,%rbx,4), %rdi
	call	_Znwm
.LEHE0:
	movq	%rax, %r12
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L4:
	movl	$0, (%r12,%rax,4)
	addq	$1, %rax
	cmpq	%rax, %rbx
	jne	.L4
	movslq	8(%rsp), %rbp
	testq	%rbp, %rbp
	movq	%rbp, %r10
	je	.L32
	movabsq	$4611686018427387903, %rax
	cmpq	%rax, %rbp
	ja	.L65
	leaq	0(,%rbp,4), %rdi
.LEHB1:
	call	_Znwm
.LEHE1:
	movq	%rax, %rbx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L7:
	movl	$0, (%rbx,%rax,4)
	addq	$1, %rax
	cmpq	%rax, %rbp
	jne	.L7
	movl	8(%rsp), %r10d
.L2:
	movslq	%r10d, %r13
	testq	%r13, %r13
	je	.L33
	movabsq	$2305843009213693951, %rax
	cmpq	%rax, %r13
	ja	.L66
	leaq	0(,%r13,8), %rdi
.LEHB2:
	call	_Znwm
.LEHE2:
	movq	%rax, %rbp
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L9:
	movq	$0, 0(%rbp,%rax,8)
	addq	$1, %rax
	cmpq	%rax, %r13
	jne	.L9
	movl	8(%rsp), %r10d
.L5:
	xorl	%r13d, %r13d
	testl	%r10d, %r10d
	movq	%r12, %r14
	movq	%rbx, %r15
	jle	.L10
	.p2align 4,,10
	.p2align 3
.L14:
	movq	%r14, %rsi
	movl	$_ZSt3cin, %edi
.LEHB3:
	call	_ZNSirsERi
.LEHE3:
	testl	%r13d, %r13d
	movl	(%r14), %eax
	je	.L60
	addl	-4(%r15), %eax
.L60:
	movl	%eax, (%r15)
	movl	8(%rsp), %r10d
	addl	$1, %r13d
	addq	$4, %r14
	addq	$4, %r15
	cmpl	%r13d, %r10d
	jg	.L14
.L10:
	movslq	(%rbx), %rax
	movslq	12(%rsp), %r13
	leaq	4(%rbx), %r14
	movslq	16(%rsp), %r11
	movslq	20(%rsp), %r9
	leaq	8(%rbp), %rsi
	movl	$1, %edi
	movq	%rax, %rdx
	imulq	%r13, %rdx
	addq	%r11, %rdx
	imulq	%rdx, %rax
	addq	%r9, %rax
	cmpl	$1, %r10d
	movq	%rax, 0(%rbp)
	jle	.L19
	.p2align 4,,10
	.p2align 3
.L51:
	movslq	(%r14), %rax
	movq	%r13, %rcx
	imulq	%rax, %rcx
	movq	%rax, %r8
	addq	%r11, %rcx
	imulq	%rcx, %rax
	testl	%edi, %edi
	leaq	(%rax,%r9), %rcx
	movq	%rcx, (%rsi)
	jle	.L17
	xorl	%edx, %edx
	jmp	.L18
	.p2align 4,,10
	.p2align 3
.L67:
	movq	(%rsi), %rcx
.L18:
	movl	%r8d, %eax
	subl	(%rbx,%rdx,4), %eax
	movq	%r13, %r15
	cltq
	imulq	%rax, %r15
	addq	%r11, %r15
	imulq	%r15, %rax
	addq	%r9, %rax
	addq	0(%rbp,%rdx,8), %rax
	cmpq	%rcx, %rax
	jle	.L21
	movq	%rax, (%rsi)
.L21:
	addq	$1, %rdx
	cmpl	%edx, %edi
	jg	.L67
.L17:
	addl	$1, %edi
	addq	$4, %r14
	addq	$8, %rsi
	cmpl	%r10d, %edi
	jne	.L51
.L19:
	leal	-1(%r10), %eax
	movl	$_ZSt4cout, %edi
	cltq
	movq	0(%rbp,%rax,8), %rsi
.LEHB4:
	call	_ZNSo9_M_insertIxEERSoT_
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
.LEHE4:
	movq	%rbp, %rdi
	call	_ZdlPv
	movq	%rbx, %rdi
	call	_ZdlPv
	testq	%r12, %r12
	je	.L22
	movq	%r12, %rdi
	call	_ZdlPv
.L22:
	xorl	%eax, %eax
	movq	24(%rsp), %rbx
	xorq	%fs:40, %rbx
	jne	.L68
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L31:
	.cfi_restore_state
	movq	%rbx, %r10
	xorl	%r12d, %r12d
	xorl	%ebx, %ebx
	jmp	.L2
.L33:
	xorl	%ebp, %ebp
	jmp	.L5
.L66:
.LEHB5:
	call	_ZSt17__throw_bad_allocv
.LEHE5:
.L37:
	testq	%rbp, %rbp
	movq	%rax, %r13
	je	.L24
.L25:
	movq	%rbp, %rdi
	call	_ZdlPv
.L24:
	movq	%r13, %rbp
.L26:
	testq	%rbx, %rbx
	je	.L27
	movq	%rbx, %rdi
	call	_ZdlPv
.L27:
	testq	%r12, %r12
	movq	%rbp, %rbx
	je	.L28
.L29:
	movq	%r12, %rdi
	call	_ZdlPv
.L28:
	movq	%rbx, %rdi
.LEHB6:
	call	_Unwind_Resume
.LEHE6:
.L35:
	movq	%rax, %rbp
	jmp	.L26
.L36:
	movq	%rax, %rbx
	jmp	.L29
.L65:
.LEHB7:
	call	_ZSt17__throw_bad_allocv
.LEHE7:
.L68:
	call	__stack_chk_fail
.L38:
	movq	%rax, %r13
	jmp	.L25
.L32:
	xorl	%ebx, %ebx
	xorl	%ebp, %ebp
	jmp	.L5
.L64:
.LEHB8:
	call	_ZSt17__throw_bad_allocv
.LEHE8:
	.cfi_endproc
.LFE1310:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA1310:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1310-.LLSDACSB1310
.LLSDACSB1310:
	.uleb128 .LEHB0-.LFB1310
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB1310
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L36-.LFB1310
	.uleb128 0
	.uleb128 .LEHB2-.LFB1310
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L35-.LFB1310
	.uleb128 0
	.uleb128 .LEHB3-.LFB1310
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L37-.LFB1310
	.uleb128 0
	.uleb128 .LEHB4-.LFB1310
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L38-.LFB1310
	.uleb128 0
	.uleb128 .LEHB5-.LFB1310
	.uleb128 .LEHE5-.LEHB5
	.uleb128 .L35-.LFB1310
	.uleb128 0
	.uleb128 .LEHB6-.LFB1310
	.uleb128 .LEHE6-.LEHB6
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB7-.LFB1310
	.uleb128 .LEHE7-.LEHB7
	.uleb128 .L36-.LFB1310
	.uleb128 0
	.uleb128 .LEHB8-.LFB1310
	.uleb128 .LEHE8-.LEHB8
	.uleb128 0
	.uleb128 0
.LLSDACSE1310:
	.section	.text.startup
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE0:
	.section	.text.startup
.LHOTE0:
	.section	.text.unlikely
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4,,15
	.globl	_Z8functioniiii
	.type	_Z8functioniiii, @function
_Z8functioniiii:
.LFB1311:
	.cfi_startproc
	movslq	%ecx, %rcx
	movslq	%edi, %rdi
	movslq	%esi, %rsi
	imulq	%rcx, %rdi
	movslq	%edx, %rdx
	leaq	(%rdi,%rsi), %rax
	imulq	%rax, %rcx
	leaq	(%rcx,%rdx), %rax
	ret
	.cfi_endproc
.LFE1311:
	.size	_Z8functioniiii, .-_Z8functioniiii
	.section	.text.unlikely
.LCOLDE1:
	.text
.LHOTE1:
	.section	.text.unlikely
.LCOLDB2:
	.section	.text.startup
.LHOTB2:
	.p2align 4,,15
	.type	_GLOBAL__sub_I_main, @function
_GLOBAL__sub_I_main:
.LFB1444:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	jmp	__cxa_atexit
	.cfi_endproc
.LFE1444:
	.size	_GLOBAL__sub_I_main, .-_GLOBAL__sub_I_main
	.section	.text.unlikely
.LCOLDE2:
	.section	.text.startup
.LHOTE2:
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_main
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.5) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
