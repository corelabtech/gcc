;; Scheduling description for CoreLab Cypress.

;; CoreLab Cypress is a dual-issue, superscalar, 6-stage processor.

;; -----------------------------------------------------
;; CoreLab Cypress Core units
;; 1*jmp + 2*alu + 1*mdu + 1*fpu + 2*ld + 1*st + 1*p
;; -----------------------------------------------------

(define_automaton "cl_cypress")

(define_cpu_unit "cl_cypress_jmp" "cl_cypress")
(define_reservation "cl_cypress_jmp_rs" "cl_cypress_jmp")

(define_cpu_unit "cl_cypress_alu_0, cl_cypress_alu_1" "cl_cypress")
(define_reservation "cl_cypress_alu_rs" "cl_cypress_alu_0 | cl_cypress_alu_1")

(define_cpu_unit "cl_cypress_mul_0" "cl_cypress")
(define_cpu_unit "cl_cypress_div_0" "cl_cypress")
(define_reservation "cl_cypress_mdu_rs" "cl_cypress_mul_0 + cl_cypress_div_0")

(define_cpu_unit "cl_cypress_fpu_0" "cl_cypress")
(define_reservation "cl_cypress_fmisc_rs" "cl_cypress_fpu_0")

(define_cpu_unit "cl_cypress_ag_0, cl_cypress_ag_1" "cl_cypress")
(define_cpu_unit "cl_cypress_ld_0, cl_cypress_ld_1" "cl_cypress")
(define_cpu_unit "cl_cypress_st_0" "cl_cypress")
(define_reservation "cl_cypress_ag_rs" "cl_cypress_ag_0 | cl_cypress_ag_1")
(define_reservation "cl_cypress_ld_rs" "cl_cypress_ld_0, cl_cypress_ld_1")
(define_reservation "cl_cypress_st_rs" "cl_cypress_st_0")

(define_cpu_unit "cl_cypress_p_0" "cl_cypress")
(define_reservation "cl_cypress_p_rs" "cl_cypress_p_0")

;; ----------------------------------------------------
;; Memory (load/store)
;; ----------------------------------------------------

(define_insn_reservation "cl_cypress_load" 2
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "load"))
  "cl_cypress_ag_rs,cl_cypress_ld_rs")

(define_insn_reservation "cl_cypress_store" 2
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "store"))
  "cl_cypress_ag_rs,cl_cypress_st_rs")

(define_insn_reservation "cl_cypress_fpload_s" 2
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "fpload")
       (eq_attr "mode" "SF"))
  "cl_cypress_ag_rs,cl_cypress_ld_rs")

(define_insn_reservation "cl_cypress_fpload_d" 3
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "fpload")
       (eq_attr "mode" "DF"))
  "cl_cypress_ag_rs,cl_cypress_ld_rs*2")

(define_insn_reservation "cl_cypress_fpstore_s" 2
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "fpstore")
       (eq_attr "mode" "SF"))
  "cl_cypress_ag_rs,cl_cypress_st_rs")

(define_insn_reservation "cl_cypress_fpstore_d" 3
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "fpstore")
       (eq_attr "mode" "DF"))
  "cl_cypress_ag_rs,cl_cypress_st_rs*2")

;; ----------------------------------------------------
;; Int
;; ----------------------------------------------------

(define_insn_reservation "cl_cypress_jump" 1
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "jump,call,auipc,unknown,branch,jalr,ret,sfb_alu"))
  "cl_cypress_jmp_rs")

(define_insn_reservation "cl_cypress_alu" 1
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "nop,const,arith,shift,slt,multi,logical,move,bitmanip"))
  "cl_cypress_alu_rs")

(define_insn_reservation "cl_cypress_mul" 2
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "imul"))
  "cl_cypress_mdu_rs")

(define_insn_reservation "cl_cypress_div" 6
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "idiv"))
  "cl_cypress_mdu_rs")

;; ----------------------------------------------------
;; Float
;; ----------------------------------------------------
(define_insn_reservation "cl_cypress_fadd" 2
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "fadd"))
  "cl_cypress_fmisc_rs")

(define_insn_reservation "cl_cypress_fmul_s" 2
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "fmul")
       (eq_attr "mode" "SF"))
  "cl_cypress_fmisc_rs")

(define_insn_reservation "cl_cypress_fmul_d" 4
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "fmul")
       (eq_attr "mode" "DF"))
  "cl_cypress_fmisc_rs")

(define_insn_reservation "cl_cypress_fmadd_s" 2
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "fmadd")
       (eq_attr "mode" "SF"))
  "cl_cypress_fmisc_rs")

(define_insn_reservation "cl_cypress_fmadd_d" 4
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "fmadd")
       (eq_attr "mode" "DF"))
  "cl_cypress_fmisc_rs")

(define_insn_reservation "cl_cypress_fdiv_s" 15
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "fdiv")
       (eq_attr "mode" "SF"))
  "cl_cypress_fmisc_rs")

(define_insn_reservation "cl_cypress_fdiv_d" 22
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "fdiv")
       (eq_attr "mode" "DF"))
  "cl_cypress_fmisc_rs")

(define_insn_reservation "cl_cypress_fsqrt_s" 15
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "fsqrt")
       (eq_attr "mode" "SF"))
  "cl_cypress_fmisc_rs")

(define_insn_reservation "cl_cypress_fsqrt_d" 22
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "fsqrt")
       (eq_attr "mode" "DF"))
  "cl_cypress_fmisc_rs")

(define_insn_reservation "cl_cypress_fcmp" 2
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "fcmp"))
  "cl_cypress_fmisc_rs")

(define_insn_reservation "cl_cypress_fcvt" 2
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "fcvt"))
  "cl_cypress_fmisc_rs")

(define_insn_reservation "cl_cypress_fmove" 2
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "fmove"))
  "cl_cypress_fmisc_rs")

;; ----------------------------------------------------
;; P extension
;; ----------------------------------------------------

(define_insn_reservation "cl_cypress_maddr32" 2
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "maddr32")
       (eq_attr "mode" "SI"))
  "cl_cypress_p_rs")

(define_insn_reservation "cl_cypress_msubr32" 2
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "msubr32")
       (eq_attr "mode" "SI"))
  "cl_cypress_p_rs")

(define_insn_reservation "cl_cypress_pmul" 2
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "pmul"))
  "cl_cypress_p_rs")

(define_insn_reservation "cl_cypress_simd" 1
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "simd"))
  "cl_cypress_p_rs")

(define_insn_reservation "cl_cypress_dsp" 1
  (and (eq_attr "tune" "cl_cypress")
       (eq_attr "type" "dsp"))
  "cl_cypress_p_rs")
