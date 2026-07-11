;; Scheduling description for CoreLab Juniper.

;; CoreLab Juniper is a dual-issue, superscalar, 8-stage processor.

;; -----------------------------------------------------
;; CoreLab Juniper Core units
;; 1*jmp + 2*alu + 1*mdu + 1*fpu + 2*ld + 1*st
;; -----------------------------------------------------

(define_automaton "cl_juniper")

(define_cpu_unit "cl_juniper_jmp" "cl_juniper")
(define_reservation "cl_juniper_jmp_rs" "cl_juniper_jmp")

(define_cpu_unit "cl_juniper_alu_0, cl_juniper_alu_1" "cl_juniper")
(define_reservation "cl_juniper_alu_rs" "cl_juniper_alu_0 | cl_juniper_alu_1")

(define_cpu_unit "cl_juniper_mul_0" "cl_juniper")
(define_cpu_unit "cl_juniper_div_0" "cl_juniper")
(define_reservation "cl_juniper_mdu_rs" "cl_juniper_mul_0 + cl_juniper_div_0")

(define_cpu_unit "cl_juniper_fpu_0" "cl_juniper")
(define_reservation "cl_juniper_fmisc_rs" "cl_juniper_fpu_0")

(define_cpu_unit "cl_juniper_ag_0, cl_juniper_ag_1" "cl_juniper")
(define_cpu_unit "cl_juniper_ld_0, cl_juniper_ld_1" "cl_juniper")
(define_cpu_unit "cl_juniper_st_0" "cl_juniper")
(define_reservation "cl_juniper_ag_rs" "cl_juniper_ag_0 | cl_juniper_ag_1")
(define_reservation "cl_juniper_ld_rs" "cl_juniper_ld_0, cl_juniper_ld_1")
(define_reservation "cl_juniper_st_rs" "cl_juniper_st_0")

;; ----------------------------------------------------
;; Memory (load/store)
;; ----------------------------------------------------

(define_insn_reservation "cl_juniper_load" 2
  (and (eq_attr "tune" "cl_juniper")
       (eq_attr "type" "load"))
  "cl_juniper_ag_rs,cl_juniper_ld_rs")

(define_insn_reservation "cl_juniper_store" 2
  (and (eq_attr "tune" "cl_juniper")
       (eq_attr "type" "store"))
  "cl_juniper_ag_rs,cl_juniper_st_rs")

(define_insn_reservation "cl_juniper_fpload_s" 2
  (and (eq_attr "tune" "cl_juniper")
       (eq_attr "type" "fpload")
       (eq_attr "mode" "SF"))
  "cl_juniper_ag_rs,cl_juniper_ld_rs")

(define_insn_reservation "cl_juniper_fpload_d" 3
  (and (eq_attr "tune" "cl_juniper")
       (eq_attr "type" "fpload")
       (eq_attr "mode" "DF"))
  "cl_juniper_ag_rs,cl_juniper_ld_rs*2")

(define_insn_reservation "cl_juniper_fpstore_s" 2
  (and (eq_attr "tune" "cl_juniper")
       (eq_attr "type" "fpstore")
       (eq_attr "mode" "SF"))
  "cl_juniper_ag_rs,cl_juniper_st_rs")

(define_insn_reservation "cl_juniper_fpstore_d" 3
  (and (eq_attr "tune" "cl_juniper")
       (eq_attr "type" "fpstore")
       (eq_attr "mode" "DF"))
  "cl_juniper_ag_rs,cl_juniper_st_rs*2")

;; ----------------------------------------------------
;; Int
;; ----------------------------------------------------

(define_insn_reservation "cl_juniper_jump" 1
  (and (eq_attr "tune" "cl_juniper")
       (eq_attr "type" "jump,call,auipc,unknown,branch,jalr,ret,sfb_alu"))
  "cl_juniper_jmp_rs")

(define_insn_reservation "cl_juniper_alu" 1
  (and (eq_attr "tune" "cl_juniper")
       (eq_attr "type" "nop,const,arith,shift,slt,multi,logical,move,bitmanip"))
  "cl_juniper_alu_rs")

(define_insn_reservation "cl_juniper_mul" 2
  (and (eq_attr "tune" "cl_juniper")
       (eq_attr "type" "imul"))
  "cl_juniper_mdu_rs")

(define_insn_reservation "cl_juniper_div" 6
  (and (eq_attr "tune" "cl_juniper")
       (eq_attr "type" "idiv"))
  "cl_juniper_mdu_rs")

;; ----------------------------------------------------
;; Float
;; ----------------------------------------------------
(define_insn_reservation "cl_juniper_fadd" 2
  (and (eq_attr "tune" "cl_juniper")
       (eq_attr "type" "fadd"))
  "cl_juniper_fmisc_rs")

(define_insn_reservation "cl_juniper_fmul_s" 2
  (and (eq_attr "tune" "cl_juniper")
       (eq_attr "type" "fmul")
       (eq_attr "mode" "SF"))
  "cl_juniper_fmisc_rs")

(define_insn_reservation "cl_juniper_fmul_d" 4
  (and (eq_attr "tune" "cl_juniper")
       (eq_attr "type" "fmul")
       (eq_attr "mode" "DF"))
  "cl_juniper_fmisc_rs")

(define_insn_reservation "cl_juniper_fmadd_s" 2
  (and (eq_attr "tune" "cl_juniper")
       (eq_attr "type" "fmadd")
       (eq_attr "mode" "SF"))
  "cl_juniper_fmisc_rs")

(define_insn_reservation "cl_juniper_fmadd_d" 4
  (and (eq_attr "tune" "cl_juniper")
       (eq_attr "type" "fmadd")
       (eq_attr "mode" "DF"))
  "cl_juniper_fmisc_rs")

(define_insn_reservation "cl_juniper_fdiv_s" 15
  (and (eq_attr "tune" "cl_juniper")
       (eq_attr "type" "fdiv")
       (eq_attr "mode" "SF"))
  "cl_juniper_fmisc_rs")

(define_insn_reservation "cl_juniper_fdiv_d" 22
  (and (eq_attr "tune" "cl_juniper")
       (eq_attr "type" "fdiv")
       (eq_attr "mode" "DF"))
  "cl_juniper_fmisc_rs")

(define_insn_reservation "cl_juniper_fsqrt_s" 15
  (and (eq_attr "tune" "cl_juniper")
       (eq_attr "type" "fsqrt")
       (eq_attr "mode" "SF"))
  "cl_juniper_fmisc_rs")

(define_insn_reservation "cl_juniper_fsqrt_d" 22
  (and (eq_attr "tune" "cl_juniper")
       (eq_attr "type" "fsqrt")
       (eq_attr "mode" "DF"))
  "cl_juniper_fmisc_rs")

(define_insn_reservation "cl_juniper_fcmp" 2
  (and (eq_attr "tune" "cl_juniper")
       (eq_attr "type" "fcmp"))
  "cl_juniper_fmisc_rs")

(define_insn_reservation "cl_juniper_fcvt" 2
  (and (eq_attr "tune" "cl_juniper")
       (eq_attr "type" "fcvt"))
  "cl_juniper_fmisc_rs")

(define_insn_reservation "cl_juniper_fmove" 2
  (and (eq_attr "tune" "cl_juniper")
       (eq_attr "type" "fmove"))
  "cl_juniper_fmisc_rs")

