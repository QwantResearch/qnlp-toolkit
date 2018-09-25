/* This file was generated automatically by the Snowball to ISO C compiler */
/* http://snowballstem.org/ */

#include "../runtime/header.h"

#ifdef __cplusplus
extern "C" {
#endif
extern int kraaij_pohlmann_UTF_8_stem(struct SN_env * z);
#ifdef __cplusplus
}
#endif
static int r_measure(struct SN_env * z);
static int r_Lose_infix(struct SN_env * z);
static int r_Lose_prefix(struct SN_env * z);
static int r_Step_1c(struct SN_env * z);
static int r_Step_6(struct SN_env * z);
static int r_Step_7(struct SN_env * z);
static int r_Step_4(struct SN_env * z);
static int r_Step_3(struct SN_env * z);
static int r_Step_2(struct SN_env * z);
static int r_Step_1(struct SN_env * z);
static int r_lengthen_V(struct SN_env * z);
static int r_VX(struct SN_env * z);
static int r_V(struct SN_env * z);
static int r_C(struct SN_env * z);
static int r_R2(struct SN_env * z);
static int r_R1(struct SN_env * z);
#ifdef __cplusplus
extern "C" {
#endif


extern struct SN_env * kraaij_pohlmann_UTF_8_create_env(void);
extern void kraaij_pohlmann_UTF_8_close_env(struct SN_env * z);


#ifdef __cplusplus
}
#endif
static const symbol s_0_0[3] = { 'n', 'd', 'e' };
static const symbol s_0_1[2] = { 'e', 'n' };
static const symbol s_0_2[1] = { 's' };
static const symbol s_0_3[2] = { '\'', 's' };
static const symbol s_0_4[2] = { 'e', 's' };
static const symbol s_0_5[3] = { 'i', 'e', 's' };
static const symbol s_0_6[3] = { 'a', 'u', 's' };

static const struct among a_0[7] =
{
/*  0 */ { 3, s_0_0, -1, 7, 0},
/*  1 */ { 2, s_0_1, -1, 6, 0},
/*  2 */ { 1, s_0_2, -1, 2, 0},
/*  3 */ { 2, s_0_3, 2, 1, 0},
/*  4 */ { 2, s_0_4, 2, 4, 0},
/*  5 */ { 3, s_0_5, 4, 3, 0},
/*  6 */ { 3, s_0_6, 2, 5, 0}
};

static const symbol s_1_0[2] = { 'd', 'e' };
static const symbol s_1_1[2] = { 'g', 'e' };
static const symbol s_1_2[5] = { 'i', 's', 'c', 'h', 'e' };
static const symbol s_1_3[2] = { 'j', 'e' };
static const symbol s_1_4[5] = { 'l', 'i', 'j', 'k', 'e' };
static const symbol s_1_5[2] = { 'l', 'e' };
static const symbol s_1_6[3] = { 'e', 'n', 'e' };
static const symbol s_1_7[2] = { 'r', 'e' };
static const symbol s_1_8[2] = { 's', 'e' };
static const symbol s_1_9[2] = { 't', 'e' };
static const symbol s_1_10[4] = { 'i', 'e', 'v', 'e' };

static const struct among a_1[11] =
{
/*  0 */ { 2, s_1_0, -1, 5, 0},
/*  1 */ { 2, s_1_1, -1, 2, 0},
/*  2 */ { 5, s_1_2, -1, 4, 0},
/*  3 */ { 2, s_1_3, -1, 1, 0},
/*  4 */ { 5, s_1_4, -1, 3, 0},
/*  5 */ { 2, s_1_5, -1, 9, 0},
/*  6 */ { 3, s_1_6, -1, 10, 0},
/*  7 */ { 2, s_1_7, -1, 8, 0},
/*  8 */ { 2, s_1_8, -1, 7, 0},
/*  9 */ { 2, s_1_9, -1, 6, 0},
/* 10 */ { 4, s_1_10, -1, 11, 0}
};

static const symbol s_2_0[4] = { 'h', 'e', 'i', 'd' };
static const symbol s_2_1[3] = { 'f', 'i', 'e' };
static const symbol s_2_2[3] = { 'g', 'i', 'e' };
static const symbol s_2_3[4] = { 'a', 't', 'i', 'e' };
static const symbol s_2_4[4] = { 'i', 's', 'm', 'e' };
static const symbol s_2_5[3] = { 'i', 'n', 'g' };
static const symbol s_2_6[4] = { 'a', 'r', 'i', 'j' };
static const symbol s_2_7[4] = { 'e', 'r', 'i', 'j' };
static const symbol s_2_8[3] = { 's', 'e', 'l' };
static const symbol s_2_9[4] = { 'r', 'd', 'e', 'r' };
static const symbol s_2_10[4] = { 's', 't', 'e', 'r' };
static const symbol s_2_11[5] = { 'i', 't', 'e', 'i', 't' };
static const symbol s_2_12[3] = { 'd', 's', 't' };
static const symbol s_2_13[3] = { 't', 's', 't' };

static const struct among a_2[14] =
{
/*  0 */ { 4, s_2_0, -1, 3, 0},
/*  1 */ { 3, s_2_1, -1, 6, 0},
/*  2 */ { 3, s_2_2, -1, 7, 0},
/*  3 */ { 4, s_2_3, -1, 1, 0},
/*  4 */ { 4, s_2_4, -1, 2, 0},
/*  5 */ { 3, s_2_5, -1, 2, 0},
/*  6 */ { 4, s_2_6, -1, 5, 0},
/*  7 */ { 4, s_2_7, -1, 2, 0},
/*  8 */ { 3, s_2_8, -1, 3, 0},
/*  9 */ { 4, s_2_9, -1, 4, 0},
/* 10 */ { 4, s_2_10, -1, 3, 0},
/* 11 */ { 5, s_2_11, -1, 2, 0},
/* 12 */ { 3, s_2_12, -1, 9, 0},
/* 13 */ { 3, s_2_13, -1, 8, 0}
};

static const symbol s_3_0[3] = { 'e', 'n', 'd' };
static const symbol s_3_1[5] = { 'a', 't', 'i', 'e', 'f' };
static const symbol s_3_2[4] = { 'e', 'r', 'i', 'g' };
static const symbol s_3_3[6] = { 'a', 'c', 'h', 't', 'i', 'g' };
static const symbol s_3_4[6] = { 'i', 'o', 'n', 'e', 'e', 'l' };
static const symbol s_3_5[4] = { 'b', 'a', 'a', 'r' };
static const symbol s_3_6[4] = { 'l', 'a', 'a', 'r' };
static const symbol s_3_7[4] = { 'n', 'a', 'a', 'r' };
static const symbol s_3_8[4] = { 'r', 'a', 'a', 'r' };
static const symbol s_3_9[6] = { 'e', 'r', 'i', 'g', 'e', 'r' };
static const symbol s_3_10[8] = { 'a', 'c', 'h', 't', 'i', 'g', 'e', 'r' };
static const symbol s_3_11[6] = { 'l', 'i', 'j', 'k', 'e', 'r' };
static const symbol s_3_12[4] = { 't', 'a', 'n', 't' };
static const symbol s_3_13[6] = { 'e', 'r', 'i', 'g', 's', 't' };
static const symbol s_3_14[8] = { 'a', 'c', 'h', 't', 'i', 'g', 's', 't' };
static const symbol s_3_15[6] = { 'l', 'i', 'j', 'k', 's', 't' };

static const struct among a_3[16] =
{
/*  0 */ { 3, s_3_0, -1, 9, 0},
/*  1 */ { 5, s_3_1, -1, 2, 0},
/*  2 */ { 4, s_3_2, -1, 9, 0},
/*  3 */ { 6, s_3_3, -1, 3, 0},
/*  4 */ { 6, s_3_4, -1, 1, 0},
/*  5 */ { 4, s_3_5, -1, 3, 0},
/*  6 */ { 4, s_3_6, -1, 5, 0},
/*  7 */ { 4, s_3_7, -1, 4, 0},
/*  8 */ { 4, s_3_8, -1, 6, 0},
/*  9 */ { 6, s_3_9, -1, 9, 0},
/* 10 */ { 8, s_3_10, -1, 3, 0},
/* 11 */ { 6, s_3_11, -1, 8, 0},
/* 12 */ { 4, s_3_12, -1, 7, 0},
/* 13 */ { 6, s_3_13, -1, 9, 0},
/* 14 */ { 8, s_3_14, -1, 3, 0},
/* 15 */ { 6, s_3_15, -1, 8, 0}
};

static const symbol s_4_0[2] = { 'i', 'g' };
static const symbol s_4_1[4] = { 'i', 'g', 'e', 'r' };
static const symbol s_4_2[4] = { 'i', 'g', 's', 't' };

static const struct among a_4[3] =
{
/*  0 */ { 2, s_4_0, -1, 1, 0},
/*  1 */ { 4, s_4_1, -1, 1, 0},
/*  2 */ { 4, s_4_2, -1, 1, 0}
};

static const symbol s_5_0[2] = { 'f', 't' };
static const symbol s_5_1[2] = { 'k', 't' };
static const symbol s_5_2[2] = { 'p', 't' };

static const struct among a_5[3] =
{
/*  0 */ { 2, s_5_0, -1, 2, 0},
/*  1 */ { 2, s_5_1, -1, 1, 0},
/*  2 */ { 2, s_5_2, -1, 3, 0}
};

static const symbol s_6_0[2] = { 'b', 'b' };
static const symbol s_6_1[2] = { 'c', 'c' };
static const symbol s_6_2[2] = { 'd', 'd' };
static const symbol s_6_3[2] = { 'f', 'f' };
static const symbol s_6_4[2] = { 'g', 'g' };
static const symbol s_6_5[2] = { 'h', 'h' };
static const symbol s_6_6[2] = { 'j', 'j' };
static const symbol s_6_7[2] = { 'k', 'k' };
static const symbol s_6_8[2] = { 'l', 'l' };
static const symbol s_6_9[2] = { 'm', 'm' };
static const symbol s_6_10[2] = { 'n', 'n' };
static const symbol s_6_11[2] = { 'p', 'p' };
static const symbol s_6_12[2] = { 'q', 'q' };
static const symbol s_6_13[2] = { 'r', 'r' };
static const symbol s_6_14[2] = { 's', 's' };
static const symbol s_6_15[2] = { 't', 't' };
static const symbol s_6_16[1] = { 'v' };
static const symbol s_6_17[2] = { 'v', 'v' };
static const symbol s_6_18[2] = { 'w', 'w' };
static const symbol s_6_19[2] = { 'x', 'x' };
static const symbol s_6_20[1] = { 'z' };
static const symbol s_6_21[2] = { 'z', 'z' };

static const struct among a_6[22] =
{
/*  0 */ { 2, s_6_0, -1, 1, 0},
/*  1 */ { 2, s_6_1, -1, 2, 0},
/*  2 */ { 2, s_6_2, -1, 3, 0},
/*  3 */ { 2, s_6_3, -1, 4, 0},
/*  4 */ { 2, s_6_4, -1, 5, 0},
/*  5 */ { 2, s_6_5, -1, 6, 0},
/*  6 */ { 2, s_6_6, -1, 7, 0},
/*  7 */ { 2, s_6_7, -1, 8, 0},
/*  8 */ { 2, s_6_8, -1, 9, 0},
/*  9 */ { 2, s_6_9, -1, 10, 0},
/* 10 */ { 2, s_6_10, -1, 11, 0},
/* 11 */ { 2, s_6_11, -1, 12, 0},
/* 12 */ { 2, s_6_12, -1, 13, 0},
/* 13 */ { 2, s_6_13, -1, 14, 0},
/* 14 */ { 2, s_6_14, -1, 15, 0},
/* 15 */ { 2, s_6_15, -1, 16, 0},
/* 16 */ { 1, s_6_16, -1, 4, 0},
/* 17 */ { 2, s_6_17, 16, 17, 0},
/* 18 */ { 2, s_6_18, -1, 18, 0},
/* 19 */ { 2, s_6_19, -1, 19, 0},
/* 20 */ { 1, s_6_20, -1, 15, 0},
/* 21 */ { 2, s_6_21, 20, 20, 0}
};

static const symbol s_7_0[1] = { 'd' };
static const symbol s_7_1[1] = { 't' };

static const struct among a_7[2] =
{
/*  0 */ { 1, s_7_0, -1, 1, 0},
/*  1 */ { 1, s_7_1, -1, 2, 0}
};

static const unsigned char g_v[] = { 17, 65, 16, 1 };

static const unsigned char g_v_WX[] = { 17, 65, 208, 1 };

static const unsigned char g_AOU[] = { 1, 64, 16 };

static const unsigned char g_AIOU[] = { 1, 65, 16 };

static const symbol s_0[] = { 'i', 'j' };
static const symbol s_1[] = { 'i', 'j' };
static const symbol s_2[] = { 'i', 'j' };
static const symbol s_3[] = { 'i', 'e' };
static const symbol s_4[] = { 'a', 'r' };
static const symbol s_5[] = { 'e', 'r' };
static const symbol s_6[] = { 'e' };
static const symbol s_7[] = { 'a', 'u' };
static const symbol s_8[] = { 'h', 'e', 'd' };
static const symbol s_9[] = { 'h', 'e', 'i', 'd' };
static const symbol s_10[] = { 'n', 'd' };
static const symbol s_11[] = { 'n', 'd' };
static const symbol s_12[] = { '\'', 't' };
static const symbol s_13[] = { 'e', 't' };
static const symbol s_14[] = { 'r', 'n', 't' };
static const symbol s_15[] = { 'r', 'n' };
static const symbol s_16[] = { 'i', 'n', 'k' };
static const symbol s_17[] = { 'i', 'n', 'g' };
static const symbol s_18[] = { 'm', 'p' };
static const symbol s_19[] = { 'm' };
static const symbol s_20[] = { 'g' };
static const symbol s_21[] = { 'l', 'i', 'j', 'k' };
static const symbol s_22[] = { 'i', 's', 'c', 'h' };
static const symbol s_23[] = { 't' };
static const symbol s_24[] = { 's' };
static const symbol s_25[] = { 'r' };
static const symbol s_26[] = { 'l' };
static const symbol s_27[] = { 'e', 'n' };
static const symbol s_28[] = { 'i', 'e', 'f' };
static const symbol s_29[] = { 'e', 'e', 'r' };
static const symbol s_30[] = { 'r' };
static const symbol s_31[] = { 'a', 'a', 'r' };
static const symbol s_32[] = { 'f' };
static const symbol s_33[] = { 'g' };
static const symbol s_34[] = { 't' };
static const symbol s_35[] = { 'd' };
static const symbol s_36[] = { 'i', 'e' };
static const symbol s_37[] = { 'e', 'e', 'r' };
static const symbol s_38[] = { 'n' };
static const symbol s_39[] = { 'l' };
static const symbol s_40[] = { 'r' };
static const symbol s_41[] = { 't', 'e', 'e', 'r' };
static const symbol s_42[] = { 'l', 'i', 'j', 'k' };
static const symbol s_43[] = { 'k' };
static const symbol s_44[] = { 'f' };
static const symbol s_45[] = { 'p' };
static const symbol s_46[] = { 'b' };
static const symbol s_47[] = { 'c' };
static const symbol s_48[] = { 'd' };
static const symbol s_49[] = { 'f' };
static const symbol s_50[] = { 'g' };
static const symbol s_51[] = { 'h' };
static const symbol s_52[] = { 'j' };
static const symbol s_53[] = { 'k' };
static const symbol s_54[] = { 'l' };
static const symbol s_55[] = { 'm' };
static const symbol s_56[] = { 'n' };
static const symbol s_57[] = { 'p' };
static const symbol s_58[] = { 'q' };
static const symbol s_59[] = { 'r' };
static const symbol s_60[] = { 's' };
static const symbol s_61[] = { 't' };
static const symbol s_62[] = { 'v' };
static const symbol s_63[] = { 'w' };
static const symbol s_64[] = { 'x' };
static const symbol s_65[] = { 'z' };
static const symbol s_66[] = { 'g', 'e' };
static const symbol s_67[] = { 'g', 'e' };
static const symbol s_68[] = { 'i', 'j' };
static const symbol s_69[] = { 'i', 'j' };
static const symbol s_70[] = { 'Y' };
static const symbol s_71[] = { 'Y' };
static const symbol s_72[] = { 'y' };

static int r_R1(struct SN_env * z) { /* backwardmode */
    if (!(z->I[0] <= z->c)) return 0; /* $(<integer expression> <= <integer expression>), line 30 */
    return 1;
}

static int r_R2(struct SN_env * z) { /* backwardmode */
    if (!(z->I[1] <= z->c)) return 0; /* $(<integer expression> <= <integer expression>), line 31 */
    return 1;
}

static int r_V(struct SN_env * z) { /* backwardmode */
    {   int m_test1 = z->l - z->c; /* test, line 33 */
        {   int m2 = z->l - z->c; (void)m2; /* or, line 33 */
            if (in_grouping_b_U(z, g_v, 97, 121, 0)) goto lab1; /* grouping v, line 33 */
            goto lab0;
        lab1:
            z->c = z->l - m2;
            if (!(eq_s_b(z, 2, s_0))) return 0; /* literal, line 33 */
        }
    lab0:
        z->c = z->l - m_test1;
    }
    return 1;
}

static int r_VX(struct SN_env * z) { /* backwardmode */
    {   int m_test1 = z->l - z->c; /* test, line 34 */
        {   int ret = skip_utf8(z->p, z->c, z->lb, 0, -1);
            if (ret < 0) return 0;
            z->c = ret; /* next, line 34 */
        }
        {   int m2 = z->l - z->c; (void)m2; /* or, line 34 */
            if (in_grouping_b_U(z, g_v, 97, 121, 0)) goto lab1; /* grouping v, line 34 */
            goto lab0;
        lab1:
            z->c = z->l - m2;
            if (!(eq_s_b(z, 2, s_1))) return 0; /* literal, line 34 */
        }
    lab0:
        z->c = z->l - m_test1;
    }
    return 1;
}

static int r_C(struct SN_env * z) { /* backwardmode */
    {   int m_test1 = z->l - z->c; /* test, line 35 */
        {   int m2 = z->l - z->c; (void)m2; /* not, line 35 */
            if (!(eq_s_b(z, 2, s_2))) goto lab0; /* literal, line 35 */
            return 0;
        lab0:
            z->c = z->l - m2;
        }
        if (out_grouping_b_U(z, g_v, 97, 121, 0)) return 0; /* non v, line 35 */
        z->c = z->l - m_test1;
    }
    return 1;
}

static int r_lengthen_V(struct SN_env * z) { /* backwardmode */
    {   int m1 = z->l - z->c; (void)m1; /* do, line 37 */
        if (out_grouping_b_U(z, g_v_WX, 97, 121, 0)) goto lab0; /* non v_WX, line 38 */
        z->ket = z->c; /* [, line 38 */
        {   int m2 = z->l - z->c; (void)m2; /* or, line 38 */
            if (in_grouping_b_U(z, g_AOU, 97, 117, 0)) goto lab2; /* grouping AOU, line 38 */
            z->bra = z->c; /* ], line 38 */
            {   int m_test3 = z->l - z->c; /* test, line 38 */
                {   int m4 = z->l - z->c; (void)m4; /* or, line 38 */
                    if (out_grouping_b_U(z, g_v, 97, 121, 0)) goto lab4; /* non v, line 38 */
                    goto lab3;
                lab4:
                    z->c = z->l - m4;
                    if (z->c > z->lb) goto lab2; /* atlimit, line 38 */
                }
            lab3:
                z->c = z->l - m_test3;
            }
            goto lab1;
        lab2:
            z->c = z->l - m2;
            if (z->c <= z->lb || z->p[z->c - 1] != 'e') goto lab0; /* literal, line 39 */
            z->c--;
            z->bra = z->c; /* ], line 39 */
            {   int m_test5 = z->l - z->c; /* test, line 39 */
                {   int m6 = z->l - z->c; (void)m6; /* or, line 39 */
                    if (out_grouping_b_U(z, g_v, 97, 121, 0)) goto lab6; /* non v, line 39 */
                    goto lab5;
                lab6:
                    z->c = z->l - m6;
                    if (z->c > z->lb) goto lab0; /* atlimit, line 39 */
                }
            lab5:
                {   int m7 = z->l - z->c; (void)m7; /* not, line 40 */
                    if (in_grouping_b_U(z, g_AIOU, 97, 117, 0)) goto lab7; /* grouping AIOU, line 40 */
                    goto lab0;
                lab7:
                    z->c = z->l - m7;
                }
                {   int m8 = z->l - z->c; (void)m8; /* not, line 41 */
                    {   int ret = skip_utf8(z->p, z->c, z->lb, 0, -1);
                        if (ret < 0) goto lab8;
                        z->c = ret; /* next, line 41 */
                    }
                    if (in_grouping_b_U(z, g_AIOU, 97, 117, 0)) goto lab8; /* grouping AIOU, line 41 */
                    if (out_grouping_b_U(z, g_v, 97, 121, 0)) goto lab8; /* non v, line 41 */
                    goto lab0;
                lab8:
                    z->c = z->l - m8;
                }
                z->c = z->l - m_test5;
            }
        }
    lab1:
        z->S[0] = slice_to(z, z->S[0]); /* -> ch, line 42 */
        if (z->S[0] == 0) return -1; /* -> ch, line 42 */
        {   int ret;
            {   int saved_c = z->c;
                ret = insert_v(z, z->c, z->c, z->S[0]); /* <+ ch, line 42 */
                z->c = saved_c;
            }
            if (ret < 0) return ret;
        }
    lab0:
        z->c = z->l - m1;
    }
    return 1;
}

static int r_Step_1(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 47 */
    if (z->c <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((540704 >> (z->p[z->c - 1] & 0x1f)) & 1)) return 0; /* among, line 47 */
    among_var = find_among_b(z, a_0, 7);
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 47 */
    switch (among_var) { /* among, line 47 */
        case 1:
            {   int ret = slice_del(z); /* delete, line 49 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = r_R1(z); /* call R1, line 50 */
                if (ret <= 0) return ret;
            }
            {   int m1 = z->l - z->c; (void)m1; /* not, line 50 */
                if (z->c <= z->lb || z->p[z->c - 1] != 't') goto lab0; /* literal, line 50 */
                z->c--;
                {   int ret = r_R1(z); /* call R1, line 50 */
                    if (ret == 0) goto lab0;
                    if (ret < 0) return ret;
                }
                return 0;
            lab0:
                z->c = z->l - m1;
            }
            {   int ret = r_C(z); /* call C, line 50 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 50 */
                if (ret < 0) return ret;
            }
            break;
        case 3:
            {   int ret = r_R1(z); /* call R1, line 51 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 2, s_3); /* <-, line 51 */
                if (ret < 0) return ret;
            }
            break;
        case 4:
            {   int m2 = z->l - z->c; (void)m2; /* or, line 53 */
                if (!(eq_s_b(z, 2, s_4))) goto lab2; /* literal, line 53 */
                {   int ret = r_R1(z); /* call R1, line 53 */
                    if (ret == 0) goto lab2;
                    if (ret < 0) return ret;
                }
                {   int ret = r_C(z); /* call C, line 53 */
                    if (ret == 0) goto lab2;
                    if (ret < 0) return ret;
                }
                z->bra = z->c; /* ], line 53 */
                {   int ret = slice_del(z); /* delete, line 53 */
                    if (ret < 0) return ret;
                }
                {   int ret = r_lengthen_V(z); /* call lengthen_V, line 53 */
                    if (ret == 0) goto lab2;
                    if (ret < 0) return ret;
                }
                goto lab1;
            lab2:
                z->c = z->l - m2;
                if (!(eq_s_b(z, 2, s_5))) goto lab3; /* literal, line 54 */
                {   int ret = r_R1(z); /* call R1, line 54 */
                    if (ret == 0) goto lab3;
                    if (ret < 0) return ret;
                }
                {   int ret = r_C(z); /* call C, line 54 */
                    if (ret == 0) goto lab3;
                    if (ret < 0) return ret;
                }
                z->bra = z->c; /* ], line 54 */
                {   int ret = slice_del(z); /* delete, line 54 */
                    if (ret < 0) return ret;
                }
                goto lab1;
            lab3:
                z->c = z->l - m2;
                {   int ret = r_R1(z); /* call R1, line 55 */
                    if (ret <= 0) return ret;
                }
                {   int ret = r_C(z); /* call C, line 55 */
                    if (ret <= 0) return ret;
                }
                {   int ret = slice_from_s(z, 1, s_6); /* <-, line 55 */
                    if (ret < 0) return ret;
                }
            }
        lab1:
            break;
        case 5:
            {   int ret = r_R1(z); /* call R1, line 57 */
                if (ret <= 0) return ret;
            }
            {   int ret = r_V(z); /* call V, line 57 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 2, s_7); /* <-, line 57 */
                if (ret < 0) return ret;
            }
            break;
        case 6:
            {   int m3 = z->l - z->c; (void)m3; /* or, line 58 */
                if (!(eq_s_b(z, 3, s_8))) goto lab5; /* literal, line 58 */
                {   int ret = r_R1(z); /* call R1, line 58 */
                    if (ret == 0) goto lab5;
                    if (ret < 0) return ret;
                }
                z->bra = z->c; /* ], line 58 */
                {   int ret = slice_from_s(z, 4, s_9); /* <-, line 58 */
                    if (ret < 0) return ret;
                }
                goto lab4;
            lab5:
                z->c = z->l - m3;
                if (!(eq_s_b(z, 2, s_10))) goto lab6; /* literal, line 59 */
                {   int ret = slice_del(z); /* delete, line 59 */
                    if (ret < 0) return ret;
                }
                goto lab4;
            lab6:
                z->c = z->l - m3;
                if (z->c <= z->lb || z->p[z->c - 1] != 'd') goto lab7; /* literal, line 60 */
                z->c--;
                {   int ret = r_R1(z); /* call R1, line 60 */
                    if (ret == 0) goto lab7;
                    if (ret < 0) return ret;
                }
                {   int ret = r_C(z); /* call C, line 60 */
                    if (ret == 0) goto lab7;
                    if (ret < 0) return ret;
                }
                z->bra = z->c; /* ], line 60 */
                {   int ret = slice_del(z); /* delete, line 60 */
                    if (ret < 0) return ret;
                }
                goto lab4;
            lab7:
                z->c = z->l - m3;
                {   int m4 = z->l - z->c; (void)m4; /* or, line 61 */
                    if (z->c <= z->lb || z->p[z->c - 1] != 'i') goto lab10; /* literal, line 61 */
                    z->c--;
                    goto lab9;
                lab10:
                    z->c = z->l - m4;
                    if (z->c <= z->lb || z->p[z->c - 1] != 'j') goto lab8; /* literal, line 61 */
                    z->c--;
                }
            lab9:
                {   int ret = r_V(z); /* call V, line 61 */
                    if (ret == 0) goto lab8;
                    if (ret < 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 61 */
                    if (ret < 0) return ret;
                }
                goto lab4;
            lab8:
                z->c = z->l - m3;
                {   int ret = r_R1(z); /* call R1, line 62 */
                    if (ret <= 0) return ret;
                }
                {   int ret = r_C(z); /* call C, line 62 */
                    if (ret <= 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 62 */
                    if (ret < 0) return ret;
                }
                {   int ret = r_lengthen_V(z); /* call lengthen_V, line 62 */
                    if (ret <= 0) return ret;
                }
            }
        lab4:
            break;
        case 7:
            {   int ret = slice_from_s(z, 2, s_11); /* <-, line 63 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}

static int r_Step_2(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 69 */
    if (z->c - 1 <= z->lb || z->p[z->c - 1] != 101) return 0; /* among, line 69 */
    among_var = find_among_b(z, a_1, 11);
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 69 */
    switch (among_var) { /* among, line 69 */
        case 1:
            {   int m1 = z->l - z->c; (void)m1; /* or, line 70 */
                if (!(eq_s_b(z, 2, s_12))) goto lab1; /* literal, line 70 */
                z->bra = z->c; /* ], line 70 */
                {   int ret = slice_del(z); /* delete, line 70 */
                    if (ret < 0) return ret;
                }
                goto lab0;
            lab1:
                z->c = z->l - m1;
                if (!(eq_s_b(z, 2, s_13))) goto lab2; /* literal, line 71 */
                z->bra = z->c; /* ], line 71 */
                {   int ret = r_R1(z); /* call R1, line 71 */
                    if (ret == 0) goto lab2;
                    if (ret < 0) return ret;
                }
                {   int ret = r_C(z); /* call C, line 71 */
                    if (ret == 0) goto lab2;
                    if (ret < 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 71 */
                    if (ret < 0) return ret;
                }
                goto lab0;
            lab2:
                z->c = z->l - m1;
                if (!(eq_s_b(z, 3, s_14))) goto lab3; /* literal, line 72 */
                z->bra = z->c; /* ], line 72 */
                {   int ret = slice_from_s(z, 2, s_15); /* <-, line 72 */
                    if (ret < 0) return ret;
                }
                goto lab0;
            lab3:
                z->c = z->l - m1;
                if (z->c <= z->lb || z->p[z->c - 1] != 't') goto lab4; /* literal, line 73 */
                z->c--;
                z->bra = z->c; /* ], line 73 */
                {   int ret = r_R1(z); /* call R1, line 73 */
                    if (ret == 0) goto lab4;
                    if (ret < 0) return ret;
                }
                {   int ret = r_VX(z); /* call VX, line 73 */
                    if (ret == 0) goto lab4;
                    if (ret < 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 73 */
                    if (ret < 0) return ret;
                }
                goto lab0;
            lab4:
                z->c = z->l - m1;
                if (!(eq_s_b(z, 3, s_16))) goto lab5; /* literal, line 74 */
                z->bra = z->c; /* ], line 74 */
                {   int ret = slice_from_s(z, 3, s_17); /* <-, line 74 */
                    if (ret < 0) return ret;
                }
                goto lab0;
            lab5:
                z->c = z->l - m1;
                if (!(eq_s_b(z, 2, s_18))) goto lab6; /* literal, line 75 */
                z->bra = z->c; /* ], line 75 */
                {   int ret = slice_from_s(z, 1, s_19); /* <-, line 75 */
                    if (ret < 0) return ret;
                }
                goto lab0;
            lab6:
                z->c = z->l - m1;
                if (z->c <= z->lb || z->p[z->c - 1] != '\'') goto lab7; /* literal, line 76 */
                z->c--;
                z->bra = z->c; /* ], line 76 */
                {   int ret = r_R1(z); /* call R1, line 76 */
                    if (ret == 0) goto lab7;
                    if (ret < 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 76 */
                    if (ret < 0) return ret;
                }
                goto lab0;
            lab7:
                z->c = z->l - m1;
                z->bra = z->c; /* ], line 77 */
                {   int ret = r_R1(z); /* call R1, line 77 */
                    if (ret <= 0) return ret;
                }
                {   int ret = r_C(z); /* call C, line 77 */
                    if (ret <= 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 77 */
                    if (ret < 0) return ret;
                }
            }
        lab0:
            break;
        case 2:
            {   int ret = r_R1(z); /* call R1, line 78 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 1, s_20); /* <-, line 78 */
                if (ret < 0) return ret;
            }
            break;
        case 3:
            {   int ret = r_R1(z); /* call R1, line 79 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 4, s_21); /* <-, line 79 */
                if (ret < 0) return ret;
            }
            break;
        case 4:
            {   int ret = r_R1(z); /* call R1, line 80 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 4, s_22); /* <-, line 80 */
                if (ret < 0) return ret;
            }
            break;
        case 5:
            {   int ret = r_R1(z); /* call R1, line 81 */
                if (ret <= 0) return ret;
            }
            {   int ret = r_C(z); /* call C, line 81 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 81 */
                if (ret < 0) return ret;
            }
            break;
        case 6:
            {   int ret = r_R1(z); /* call R1, line 82 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 1, s_23); /* <-, line 82 */
                if (ret < 0) return ret;
            }
            break;
        case 7:
            {   int ret = r_R1(z); /* call R1, line 83 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 1, s_24); /* <-, line 83 */
                if (ret < 0) return ret;
            }
            break;
        case 8:
            {   int ret = r_R1(z); /* call R1, line 84 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 1, s_25); /* <-, line 84 */
                if (ret < 0) return ret;
            }
            break;
        case 9:
            {   int ret = r_R1(z); /* call R1, line 85 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 85 */
                if (ret < 0) return ret;
            }
            {   int ret;
                ret = insert_s(z, z->c, z->c, 1, s_26); /* attach, line 85 */
                if (ret < 0) return ret;
            }
            {   int ret = r_lengthen_V(z); /* call lengthen_V, line 85 */
                if (ret <= 0) return ret;
            }
            break;
        case 10:
            {   int ret = r_R1(z); /* call R1, line 86 */
                if (ret <= 0) return ret;
            }
            {   int ret = r_C(z); /* call C, line 86 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 86 */
                if (ret < 0) return ret;
            }
            {   int ret;
                ret = insert_s(z, z->c, z->c, 2, s_27); /* attach, line 86 */
                if (ret < 0) return ret;
            }
            {   int ret = r_lengthen_V(z); /* call lengthen_V, line 86 */
                if (ret <= 0) return ret;
            }
            break;
        case 11:
            {   int ret = r_R1(z); /* call R1, line 87 */
                if (ret <= 0) return ret;
            }
            {   int ret = r_C(z); /* call C, line 87 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 3, s_28); /* <-, line 87 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}

static int r_Step_3(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 93 */
    if (z->c - 2 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((1316016 >> (z->p[z->c - 1] & 0x1f)) & 1)) return 0; /* among, line 93 */
    among_var = find_among_b(z, a_2, 14);
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 93 */
    switch (among_var) { /* among, line 93 */
        case 1:
            {   int ret = r_R1(z); /* call R1, line 94 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 3, s_29); /* <-, line 94 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = r_R1(z); /* call R1, line 95 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 95 */
                if (ret < 0) return ret;
            }
            {   int ret = r_lengthen_V(z); /* call lengthen_V, line 95 */
                if (ret <= 0) return ret;
            }
            break;
        case 3:
            {   int ret = r_R1(z); /* call R1, line 98 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 98 */
                if (ret < 0) return ret;
            }
            break;
        case 4:
            {   int ret = slice_from_s(z, 1, s_30); /* <-, line 99 */
                if (ret < 0) return ret;
            }
            break;
        case 5:
            {   int ret = r_R1(z); /* call R1, line 103 */
                if (ret <= 0) return ret;
            }
            {   int ret = r_C(z); /* call C, line 103 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 3, s_31); /* <-, line 103 */
                if (ret < 0) return ret;
            }
            break;
        case 6:
            {   int ret = r_R2(z); /* call R2, line 104 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 104 */
                if (ret < 0) return ret;
            }
            {   int ret;
                ret = insert_s(z, z->c, z->c, 1, s_32); /* attach, line 104 */
                if (ret < 0) return ret;
            }
            {   int ret = r_lengthen_V(z); /* call lengthen_V, line 104 */
                if (ret <= 0) return ret;
            }
            break;
        case 7:
            {   int ret = r_R2(z); /* call R2, line 105 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_del(z); /* delete, line 105 */
                if (ret < 0) return ret;
            }
            {   int ret;
                ret = insert_s(z, z->c, z->c, 1, s_33); /* attach, line 105 */
                if (ret < 0) return ret;
            }
            {   int ret = r_lengthen_V(z); /* call lengthen_V, line 105 */
                if (ret <= 0) return ret;
            }
            break;
        case 8:
            {   int ret = r_R1(z); /* call R1, line 106 */
                if (ret <= 0) return ret;
            }
            {   int ret = r_C(z); /* call C, line 106 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 1, s_34); /* <-, line 106 */
                if (ret < 0) return ret;
            }
            break;
        case 9:
            {   int ret = r_R1(z); /* call R1, line 107 */
                if (ret <= 0) return ret;
            }
            {   int ret = r_C(z); /* call C, line 107 */
                if (ret <= 0) return ret;
            }
            {   int ret = slice_from_s(z, 1, s_35); /* <-, line 107 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}

static int r_Step_4(struct SN_env * z) { /* backwardmode */
    int among_var;
    {   int m1 = z->l - z->c; (void)m1; /* or, line 132 */
        z->ket = z->c; /* [, line 113 */
        if (z->c - 2 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((1315024 >> (z->p[z->c - 1] & 0x1f)) & 1)) goto lab1; /* among, line 113 */
        among_var = find_among_b(z, a_3, 16);
        if (!(among_var)) goto lab1;
        z->bra = z->c; /* ], line 113 */
        switch (among_var) { /* among, line 113 */
            case 1:
                {   int ret = r_R1(z); /* call R1, line 114 */
                    if (ret == 0) goto lab1;
                    if (ret < 0) return ret;
                }
                {   int ret = slice_from_s(z, 2, s_36); /* <-, line 114 */
                    if (ret < 0) return ret;
                }
                break;
            case 2:
                {   int ret = r_R1(z); /* call R1, line 115 */
                    if (ret == 0) goto lab1;
                    if (ret < 0) return ret;
                }
                {   int ret = slice_from_s(z, 3, s_37); /* <-, line 115 */
                    if (ret < 0) return ret;
                }
                break;
            case 3:
                {   int ret = r_R1(z); /* call R1, line 116 */
                    if (ret == 0) goto lab1;
                    if (ret < 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 116 */
                    if (ret < 0) return ret;
                }
                break;
            case 4:
                {   int ret = r_R1(z); /* call R1, line 117 */
                    if (ret == 0) goto lab1;
                    if (ret < 0) return ret;
                }
                {   int ret = r_V(z); /* call V, line 117 */
                    if (ret == 0) goto lab1;
                    if (ret < 0) return ret;
                }
                {   int ret = slice_from_s(z, 1, s_38); /* <-, line 117 */
                    if (ret < 0) return ret;
                }
                break;
            case 5:
                {   int ret = r_R1(z); /* call R1, line 118 */
                    if (ret == 0) goto lab1;
                    if (ret < 0) return ret;
                }
                {   int ret = r_V(z); /* call V, line 118 */
                    if (ret == 0) goto lab1;
                    if (ret < 0) return ret;
                }
                {   int ret = slice_from_s(z, 1, s_39); /* <-, line 118 */
                    if (ret < 0) return ret;
                }
                break;
            case 6:
                {   int ret = r_R1(z); /* call R1, line 119 */
                    if (ret == 0) goto lab1;
                    if (ret < 0) return ret;
                }
                {   int ret = r_V(z); /* call V, line 119 */
                    if (ret == 0) goto lab1;
                    if (ret < 0) return ret;
                }
                {   int ret = slice_from_s(z, 1, s_40); /* <-, line 119 */
                    if (ret < 0) return ret;
                }
                break;
            case 7:
                {   int ret = r_R1(z); /* call R1, line 120 */
                    if (ret == 0) goto lab1;
                    if (ret < 0) return ret;
                }
                {   int ret = slice_from_s(z, 4, s_41); /* <-, line 120 */
                    if (ret < 0) return ret;
                }
                break;
            case 8:
                {   int ret = r_R1(z); /* call R1, line 122 */
                    if (ret == 0) goto lab1;
                    if (ret < 0) return ret;
                }
                {   int ret = slice_from_s(z, 4, s_42); /* <-, line 122 */
                    if (ret < 0) return ret;
                }
                break;
            case 9:
                {   int ret = r_R1(z); /* call R1, line 129 */
                    if (ret == 0) goto lab1;
                    if (ret < 0) return ret;
                }
                {   int ret = r_C(z); /* call C, line 129 */
                    if (ret == 0) goto lab1;
                    if (ret < 0) return ret;
                }
                {   int ret = slice_del(z); /* delete, line 129 */
                    if (ret < 0) return ret;
                }
                {   int ret = r_lengthen_V(z); /* call lengthen_V, line 129 */
                    if (ret == 0) goto lab1;
                    if (ret < 0) return ret;
                }
                break;
        }
        goto lab0;
    lab1:
        z->c = z->l - m1;
        z->ket = z->c; /* [, line 133 */
        if (z->c - 1 <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((1310848 >> (z->p[z->c - 1] & 0x1f)) & 1)) return 0; /* among, line 133 */
        among_var = find_among_b(z, a_4, 3);
        if (!(among_var)) return 0;
        z->bra = z->c; /* ], line 133 */
        {   int ret = r_R1(z); /* call R1, line 136 */
            if (ret <= 0) return ret;
        }
        {   int ret = r_C(z); /* call C, line 136 */
            if (ret <= 0) return ret;
        }
        {   int ret = slice_del(z); /* delete, line 136 */
            if (ret < 0) return ret;
        }
        {   int ret = r_lengthen_V(z); /* call lengthen_V, line 136 */
            if (ret <= 0) return ret;
        }
    }
lab0:
    return 1;
}

static int r_Step_7(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 143 */
    if (z->c - 1 <= z->lb || z->p[z->c - 1] != 116) return 0; /* among, line 143 */
    among_var = find_among_b(z, a_5, 3);
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 143 */
    switch (among_var) { /* among, line 143 */
        case 1:
            {   int ret = slice_from_s(z, 1, s_43); /* <-, line 144 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = slice_from_s(z, 1, s_44); /* <-, line 145 */
                if (ret < 0) return ret;
            }
            break;
        case 3:
            {   int ret = slice_from_s(z, 1, s_45); /* <-, line 146 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}

static int r_Step_6(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 152 */
    if (z->c <= z->lb || z->p[z->c - 1] >> 5 != 3 || !((98532828 >> (z->p[z->c - 1] & 0x1f)) & 1)) return 0; /* among, line 152 */
    among_var = find_among_b(z, a_6, 22);
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 152 */
    switch (among_var) { /* among, line 152 */
        case 1:
            {   int ret = slice_from_s(z, 1, s_46); /* <-, line 153 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int ret = slice_from_s(z, 1, s_47); /* <-, line 154 */
                if (ret < 0) return ret;
            }
            break;
        case 3:
            {   int ret = slice_from_s(z, 1, s_48); /* <-, line 155 */
                if (ret < 0) return ret;
            }
            break;
        case 4:
            {   int ret = slice_from_s(z, 1, s_49); /* <-, line 156 */
                if (ret < 0) return ret;
            }
            break;
        case 5:
            {   int ret = slice_from_s(z, 1, s_50); /* <-, line 157 */
                if (ret < 0) return ret;
            }
            break;
        case 6:
            {   int ret = slice_from_s(z, 1, s_51); /* <-, line 158 */
                if (ret < 0) return ret;
            }
            break;
        case 7:
            {   int ret = slice_from_s(z, 1, s_52); /* <-, line 159 */
                if (ret < 0) return ret;
            }
            break;
        case 8:
            {   int ret = slice_from_s(z, 1, s_53); /* <-, line 160 */
                if (ret < 0) return ret;
            }
            break;
        case 9:
            {   int ret = slice_from_s(z, 1, s_54); /* <-, line 161 */
                if (ret < 0) return ret;
            }
            break;
        case 10:
            {   int ret = slice_from_s(z, 1, s_55); /* <-, line 162 */
                if (ret < 0) return ret;
            }
            break;
        case 11:
            {   int ret = slice_from_s(z, 1, s_56); /* <-, line 163 */
                if (ret < 0) return ret;
            }
            break;
        case 12:
            {   int ret = slice_from_s(z, 1, s_57); /* <-, line 164 */
                if (ret < 0) return ret;
            }
            break;
        case 13:
            {   int ret = slice_from_s(z, 1, s_58); /* <-, line 165 */
                if (ret < 0) return ret;
            }
            break;
        case 14:
            {   int ret = slice_from_s(z, 1, s_59); /* <-, line 166 */
                if (ret < 0) return ret;
            }
            break;
        case 15:
            {   int ret = slice_from_s(z, 1, s_60); /* <-, line 167 */
                if (ret < 0) return ret;
            }
            break;
        case 16:
            {   int ret = slice_from_s(z, 1, s_61); /* <-, line 168 */
                if (ret < 0) return ret;
            }
            break;
        case 17:
            {   int ret = slice_from_s(z, 1, s_62); /* <-, line 169 */
                if (ret < 0) return ret;
            }
            break;
        case 18:
            {   int ret = slice_from_s(z, 1, s_63); /* <-, line 170 */
                if (ret < 0) return ret;
            }
            break;
        case 19:
            {   int ret = slice_from_s(z, 1, s_64); /* <-, line 171 */
                if (ret < 0) return ret;
            }
            break;
        case 20:
            {   int ret = slice_from_s(z, 1, s_65); /* <-, line 172 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}

static int r_Step_1c(struct SN_env * z) { /* backwardmode */
    int among_var;
    z->ket = z->c; /* [, line 180 */
    if (z->c <= z->lb || (z->p[z->c - 1] != 100 && z->p[z->c - 1] != 116)) return 0; /* among, line 180 */
    among_var = find_among_b(z, a_7, 2);
    if (!(among_var)) return 0;
    z->bra = z->c; /* ], line 180 */
    {   int ret = r_R1(z); /* call R1, line 180 */
        if (ret <= 0) return ret;
    }
    {   int ret = r_C(z); /* call C, line 180 */
        if (ret <= 0) return ret;
    }
    switch (among_var) { /* among, line 180 */
        case 1:
            {   int m1 = z->l - z->c; (void)m1; /* not, line 181 */
                if (z->c <= z->lb || z->p[z->c - 1] != 'n') goto lab0; /* literal, line 181 */
                z->c--;
                {   int ret = r_R1(z); /* call R1, line 181 */
                    if (ret == 0) goto lab0;
                    if (ret < 0) return ret;
                }
                return 0;
            lab0:
                z->c = z->l - m1;
            }
            {   int ret = slice_del(z); /* delete, line 181 */
                if (ret < 0) return ret;
            }
            break;
        case 2:
            {   int m2 = z->l - z->c; (void)m2; /* not, line 182 */
                if (z->c <= z->lb || z->p[z->c - 1] != 'h') goto lab1; /* literal, line 182 */
                z->c--;
                {   int ret = r_R1(z); /* call R1, line 182 */
                    if (ret == 0) goto lab1;
                    if (ret < 0) return ret;
                }
                return 0;
            lab1:
                z->c = z->l - m2;
            }
            {   int ret = slice_del(z); /* delete, line 182 */
                if (ret < 0) return ret;
            }
            break;
    }
    return 1;
}

static int r_Lose_prefix(struct SN_env * z) { /* forwardmode */
    z->bra = z->c; /* [, line 188 */
    if (!(eq_s(z, 2, s_66))) return 0; /* literal, line 188 */
    z->ket = z->c; /* ], line 188 */
    {   int c_test1 = z->c; /* test, line 188 */
        {   int ret = skip_utf8(z->p, z->c, 0, z->l, + 3); /* hop, line 188 */
            if (ret < 0) return 0;
            z->c = ret;
        }
        z->c = c_test1;
    }
    if (out_grouping_U(z, g_v, 97, 121, 1) < 0) return 0; /* goto */ /* grouping v, line 188 */
    if (in_grouping_U(z, g_v, 97, 121, 1) < 0) return 0; /* goto */ /* non v, line 188 */
    z->B[2] = 1; /* set GE_removed, line 189 */
    {   int ret = slice_del(z); /* delete, line 190 */
        if (ret < 0) return ret;
    }
    return 1;
}

static int r_Lose_infix(struct SN_env * z) { /* forwardmode */
    {   int ret = skip_utf8(z->p, z->c, 0, z->l, 1);
        if (ret < 0) return 0;
        z->c = ret; /* next, line 194 */
    }
    while(1) { /* gopast, line 195 */
        z->bra = z->c; /* [, line 195 */
        if (!(eq_s(z, 2, s_67))) goto lab0; /* literal, line 195 */
        z->ket = z->c; /* ], line 195 */
        break;
    lab0:
        {   int ret = skip_utf8(z->p, z->c, 0, z->l, 1);
            if (ret < 0) return 0;
            z->c = ret; /* gopast, line 195 */
        }
    }
    {   int c_test1 = z->c; /* test, line 195 */
        {   int ret = skip_utf8(z->p, z->c, 0, z->l, + 3); /* hop, line 195 */
            if (ret < 0) return 0;
            z->c = ret;
        }
        z->c = c_test1;
    }
    if (out_grouping_U(z, g_v, 97, 121, 1) < 0) return 0; /* goto */ /* grouping v, line 195 */
    if (in_grouping_U(z, g_v, 97, 121, 1) < 0) return 0; /* goto */ /* non v, line 195 */
    z->B[2] = 1; /* set GE_removed, line 196 */
    {   int ret = slice_del(z); /* delete, line 197 */
        if (ret < 0) return ret;
    }
    return 1;
}

static int r_measure(struct SN_env * z) { /* forwardmode */
    {   int c1 = z->c; /* do, line 201 */
        z->c = z->l; /* tolimit, line 202 */
        z->I[0] = z->c; /* setmark p1, line 203 */
        z->I[1] = z->c; /* setmark p2, line 204 */
        z->c = c1;
    }
    {   int c2 = z->c; /* do, line 206 */
        while(1) { /* repeat, line 207 */
            if (out_grouping_U(z, g_v, 97, 121, 0)) goto lab2; /* non v, line 207 */
            continue;
        lab2:
            break;
        }
        {   int i = 1;
            while(1) { /* atleast, line 207 */
                int c3 = z->c;
                {   int c4 = z->c; /* or, line 207 */
                    if (!(eq_s(z, 2, s_68))) goto lab5; /* literal, line 207 */
                    goto lab4;
                lab5:
                    z->c = c4;
                    if (in_grouping_U(z, g_v, 97, 121, 0)) goto lab3; /* grouping v, line 207 */
                }
            lab4:
                i--;
                continue;
            lab3:
                z->c = c3;
                break;
            }
            if (i > 0) goto lab1;
        }
        if (out_grouping_U(z, g_v, 97, 121, 0)) goto lab1; /* non v, line 207 */
        z->I[0] = z->c; /* setmark p1, line 207 */
        while(1) { /* repeat, line 208 */
            if (out_grouping_U(z, g_v, 97, 121, 0)) goto lab6; /* non v, line 208 */
            continue;
        lab6:
            break;
        }
        {   int i = 1;
            while(1) { /* atleast, line 208 */
                int c5 = z->c;
                {   int c6 = z->c; /* or, line 208 */
                    if (!(eq_s(z, 2, s_69))) goto lab9; /* literal, line 208 */
                    goto lab8;
                lab9:
                    z->c = c6;
                    if (in_grouping_U(z, g_v, 97, 121, 0)) goto lab7; /* grouping v, line 208 */
                }
            lab8:
                i--;
                continue;
            lab7:
                z->c = c5;
                break;
            }
            if (i > 0) goto lab1;
        }
        if (out_grouping_U(z, g_v, 97, 121, 0)) goto lab1; /* non v, line 208 */
        z->I[1] = z->c; /* setmark p2, line 208 */
    lab1:
        z->c = c2;
    }
    return 1;
}

extern int kraaij_pohlmann_UTF_8_stem(struct SN_env * z) { /* forwardmode */
    z->B[0] = 0; /* unset Y_found, line 214 */
    z->B[1] = 0; /* unset stemmed, line 215 */
    {   int c1 = z->c; /* do, line 216 */
        z->bra = z->c; /* [, line 216 */
        if (z->c == z->l || z->p[z->c] != 'y') goto lab0; /* literal, line 216 */
        z->c++;
        z->ket = z->c; /* ], line 216 */
        {   int ret = slice_from_s(z, 1, s_70); /* <-, line 216 */
            if (ret < 0) return ret;
        }
        z->B[0] = 1; /* set Y_found, line 216 */
    lab0:
        z->c = c1;
    }
    {   int c2 = z->c; /* do, line 217 */
        while(1) { /* repeat, line 217 */
            int c3 = z->c;
            while(1) { /* goto, line 217 */
                int c4 = z->c;
                if (in_grouping_U(z, g_v, 97, 121, 0)) goto lab3; /* grouping v, line 217 */
                z->bra = z->c; /* [, line 217 */
                if (z->c == z->l || z->p[z->c] != 'y') goto lab3; /* literal, line 217 */
                z->c++;
                z->ket = z->c; /* ], line 217 */
                z->c = c4;
                break;
            lab3:
                z->c = c4;
                {   int ret = skip_utf8(z->p, z->c, 0, z->l, 1);
                    if (ret < 0) goto lab2;
                    z->c = ret; /* goto, line 217 */
                }
            }
            {   int ret = slice_from_s(z, 1, s_71); /* <-, line 217 */
                if (ret < 0) return ret;
            }
            z->B[0] = 1; /* set Y_found, line 217 */
            continue;
        lab2:
            z->c = c3;
            break;
        }
        z->c = c2;
    }
    {   int ret = r_measure(z); /* call measure, line 219 */
        if (ret <= 0) return ret;
    }
    z->lb = z->c; z->c = z->l; /* backwards, line 221 */

    {   int m5 = z->l - z->c; (void)m5; /* do, line 222 */
        {   int ret = r_Step_1(z); /* call Step_1, line 222 */
            if (ret == 0) goto lab4;
            if (ret < 0) return ret;
        }
        z->B[1] = 1; /* set stemmed, line 222 */
    lab4:
        z->c = z->l - m5;
    }
    {   int m6 = z->l - z->c; (void)m6; /* do, line 223 */
        {   int ret = r_Step_2(z); /* call Step_2, line 223 */
            if (ret == 0) goto lab5;
            if (ret < 0) return ret;
        }
        z->B[1] = 1; /* set stemmed, line 223 */
    lab5:
        z->c = z->l - m6;
    }
    {   int m7 = z->l - z->c; (void)m7; /* do, line 224 */
        {   int ret = r_Step_3(z); /* call Step_3, line 224 */
            if (ret == 0) goto lab6;
            if (ret < 0) return ret;
        }
        z->B[1] = 1; /* set stemmed, line 224 */
    lab6:
        z->c = z->l - m7;
    }
    {   int m8 = z->l - z->c; (void)m8; /* do, line 225 */
        {   int ret = r_Step_4(z); /* call Step_4, line 225 */
            if (ret == 0) goto lab7;
            if (ret < 0) return ret;
        }
        z->B[1] = 1; /* set stemmed, line 225 */
    lab7:
        z->c = z->l - m8;
    }
    z->c = z->lb;
    z->B[2] = 0; /* unset GE_removed, line 227 */
    {   int c9 = z->c; /* do, line 228 */
        {   int c10 = z->c; /* and, line 228 */
            {   int ret = r_Lose_prefix(z); /* call Lose_prefix, line 228 */
                if (ret == 0) goto lab8;
                if (ret < 0) return ret;
            }
            z->c = c10;
            {   int ret = r_measure(z); /* call measure, line 228 */
                if (ret == 0) goto lab8;
                if (ret < 0) return ret;
            }
        }
    lab8:
        z->c = c9;
    }
    z->lb = z->c; z->c = z->l; /* backwards, line 229 */

    {   int m11 = z->l - z->c; (void)m11; /* do, line 230 */
        if (!(z->B[2])) goto lab9; /* Boolean test GE_removed, line 230 */
        {   int ret = r_Step_1c(z); /* call Step_1c, line 230 */
            if (ret == 0) goto lab9;
            if (ret < 0) return ret;
        }
    lab9:
        z->c = z->l - m11;
    }
    z->c = z->lb;
    z->B[2] = 0; /* unset GE_removed, line 232 */
    {   int c12 = z->c; /* do, line 233 */
        {   int c13 = z->c; /* and, line 233 */
            {   int ret = r_Lose_infix(z); /* call Lose_infix, line 233 */
                if (ret == 0) goto lab10;
                if (ret < 0) return ret;
            }
            z->c = c13;
            {   int ret = r_measure(z); /* call measure, line 233 */
                if (ret == 0) goto lab10;
                if (ret < 0) return ret;
            }
        }
    lab10:
        z->c = c12;
    }
    z->lb = z->c; z->c = z->l; /* backwards, line 234 */

    {   int m14 = z->l - z->c; (void)m14; /* do, line 235 */
        if (!(z->B[2])) goto lab11; /* Boolean test GE_removed, line 235 */
        {   int ret = r_Step_1c(z); /* call Step_1c, line 235 */
            if (ret == 0) goto lab11;
            if (ret < 0) return ret;
        }
    lab11:
        z->c = z->l - m14;
    }
    z->c = z->lb;
    z->lb = z->c; z->c = z->l; /* backwards, line 237 */

    {   int m15 = z->l - z->c; (void)m15; /* do, line 238 */
        {   int ret = r_Step_7(z); /* call Step_7, line 238 */
            if (ret == 0) goto lab12;
            if (ret < 0) return ret;
        }
        z->B[1] = 1; /* set stemmed, line 238 */
    lab12:
        z->c = z->l - m15;
    }
    {   int m16 = z->l - z->c; (void)m16; /* do, line 239 */
        /* or, line 239 */
        if (!(z->B[1])) goto lab15; /* Boolean test stemmed, line 239 */
        goto lab14;
    lab15:
        if (!(z->B[2])) goto lab13; /* Boolean test GE_removed, line 239 */
    lab14:
        {   int ret = r_Step_6(z); /* call Step_6, line 239 */
            if (ret == 0) goto lab13;
            if (ret < 0) return ret;
        }
    lab13:
        z->c = z->l - m16;
    }
    z->c = z->lb;
    {   int c17 = z->c; /* do, line 241 */
        if (!(z->B[0])) goto lab16; /* Boolean test Y_found, line 241 */
        while(1) { /* repeat, line 241 */
            int c18 = z->c;
            while(1) { /* goto, line 241 */
                int c19 = z->c;
                z->bra = z->c; /* [, line 241 */
                if (z->c == z->l || z->p[z->c] != 'Y') goto lab18; /* literal, line 241 */
                z->c++;
                z->ket = z->c; /* ], line 241 */
                z->c = c19;
                break;
            lab18:
                z->c = c19;
                {   int ret = skip_utf8(z->p, z->c, 0, z->l, 1);
                    if (ret < 0) goto lab17;
                    z->c = ret; /* goto, line 241 */
                }
            }
            {   int ret = slice_from_s(z, 1, s_72); /* <-, line 241 */
                if (ret < 0) return ret;
            }
            continue;
        lab17:
            z->c = c18;
            break;
        }
    lab16:
        z->c = c17;
    }
    return 1;
}

extern struct SN_env * kraaij_pohlmann_UTF_8_create_env(void) { return SN_create_env(1, 2, 3); }

extern void kraaij_pohlmann_UTF_8_close_env(struct SN_env * z) { SN_close_env(z, 1); }

