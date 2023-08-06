typedef struct
{
    double p;
    double T;
    double v;
    double d;
    double h;
    double s;
    double u;
    double cp;
    double cv;
    double w;
    double k;
    double alfav;
    double kt;

} propD;

typedef struct
{
    double p;
    double h;
    double T;
} prop_phT;

typedef struct
{
    double p;
    double s;
    double T;
} prop_psT;

typedef struct
{
    double p;
    double h;
    double T;
    double v;
} prop_phTv;

typedef struct
{
    double p;
    double s;
    double T;
    double v;
} prop_psTv;

typedef struct
{
    double h;
    double s;
    double p;

} prop_hsP;

typedef struct
{
    double h;
    double s;
    double p;
    double T;

} prop_hsPT;

typedef struct
{
    double h;
    double s;
    double T;

} prop_hsT;

const propD r1_pT[] = {
    {.p = 3.0,
     .T = 300.0,
     .v = 0.100215168e-2,
     .h = 0.115331273e+3,
     .u = 0.112324818e3,
     .s = 0.392294792,
     .cp = 0.417301218e1,
     .cv = 0.412120160e1,
     .w = 0.150773921e4,
     .k = 0.756132220e3,
     .alfav = 0.277354533e-3,
     .kt = 0.446382123e-3

    },
    {
        .p = 80.0,
        .T = 300.0,
        .v = 0.971180894e-3,
        .h = 0.184142828e+3,
        .u = 0.106448356e3,
        .s = 0.368563852,
        .cp = 0.401008987e1,
        .cv = 0.391736606e1,
        .w = 0.163469054e4,
        .k = 0.343938651e2,
        .alfav = 0.344095831e-3,
        .kt = 0.372039437e-3,
    },
    {.p = 3.0,
     .T = 500.0,
     .v = 0.120241800e-2,
     .h = 0.975542239e+3,
     .u = 0.971934985e3,
     .s = 0.258041912e1,
     .cp = 0.465580682e1,
     .cv = 0.322139223e1,
     .w = 0.124071337e4,
     .k = 0.426742799e3,
     .alfav = 0.164118128e-2,
     .kt = 0.112892188e-2},
};

const propD r2_pT[] = {
    {.p = 0.0035,
     .T = 300.0,
     .v = 0.394913866E+02,
     .h = 0.254991145E+04,
     .u = 0.241169160E+04,
     .s = 0.852238967E+01,
     .cp = 0.191300162E+01,
     .w = 0.427920172E+03},
    {.p = 0.0035,
     .T = 700,
     .v = 0.923015898E+02,
     .h = 0.333568375E+04,
     .u = 0.301262819E+04,
     .s = 0.101749996E+02,
     .cp = 0.208141274E+01,
     .w = 0.644289068E+03},
    {.p = 30,
     .T = 700,
     .v = 0.542946619E-02,
     .h = 0.263149474E+04,
     .u = 0.246861076E+04,
     .s = 0.517540298E+01,
     .cp = 0.103505092E+02,
     .w = 0.480386523E+03}};

const prop_phT r1_phT[] = {
    {.p = 3.0, .h = 0.115331273e+3, .T = 300.0},
    {.p = 80.0, .h = 0.184142828e+3, .T = 300.0},
    {.p = 3.0, .h = 0.975542239e+3, .T = 500.0}};

const prop_psT r1_psT[] = {
    {.p = 3.0, .s = 0.392294792, .T = 300.0},
    {.p = 80.0, .s = 0.368563852, .T = 300.0},
    {.p = 3.0, .s = 0.258041912e1, .T = 500.0}};

const prop_hsPT r1_hspT[] = {
    {.h = 0.115331273e+3, .s = 0.392294792, .p = 3.0, .T = 300.0},
    {.h = 0.184142828e+3, .s = 0.368563852, .p = 80.0, .T = 300.0},
    {.h = 0.975542239e+3, .s = 0.258041912e1, .p = 3.0, .T = 500.0},
};

//------------------------ region 2 --------------------------------------

// table24 a，Page25: p,h,T
const prop_phT r2a_phT[] = {{.p = 0.001, .h = 3000, .T = 0.534433241E+03},
                            {.p = 3, .h = 3000, .T = 0.575373370E+03},
                            {.p = 3, .h = 4000, .T = 0.101077577E+04}};

// table24 b，Page25: p,h,T
const prop_phT r2b_phT[] = {{.p = 5, .h = 3500, .T = 0.801299102E+03},
                            {.p = 5, .h = 4000, .T = 0.101531583E+04},
                            {.p = 25, .h = 3500, .T = 0.875279054E+03}};

// table24 c，Page25: p,h,T
const prop_phT r2c_phT[] = {{.p = 40, .h = 2700, .T = 0.743056411E+03},
                            {.p = 60, .h = 2700, .T = 0.791137067E+03},
                            {.p = 60, .h = 3200, .T = 0.882756860E+03}};

// table29 a，Page29: p,s,T
const prop_psT r2a_psT[] = {{.p = 0.1, .s = 7.5, .T = 0.399517097E+03},
                            {.p = 0.1, .s = 8, .T = 0.514127081E+03},
                            {.p = 2.5, .s = 8, .T = 0.103984917E+04}};

// table29 b，Page29: p,s,T
const prop_psT r2b_psT[] = {{.p = 8, .s = 6, .T = 0.600484040E+03},
                            {.p = 8, .s = 7.5, .T = 0.106495556E+04},
                            {.p = 90, .s = 6, .T = 0.103801126E+04}};

// table29 c，Page29: p,s,T
const prop_psT r2c_psT[] = {{.p = 20, .s = 5.75, .T = 0.697992849E+03},
                            {.p = 80, .s = 5.25, .T = 0.854011484E+03},
                            {.p = 80, .s = 5.75, .T = 0.949017998E+03}};

// Supp-PHS12-2014 ,table9 a，Page10: h,s,p
const prop_hsP r2a_hsP[] = {
    {.h = 2800.0, .s = 6.5, .p = 1.371012767},
    {.h = 2800.0, .s = 9.5, .p = 1.879743844e-03},
    {.h = 4100.0, .s = 9.5, .p = 1.024788997e-01},
};

// Supp-PHS12-2014 ,table9 b，Page10: h,s,p
const prop_hsP r2b_hsP[] = {
    {.h = 2800.0, .s = 6.0, .p = 4.793911442},
    {.h = 3600.0, .s = 6.0, .p = 8.395519209e+01},
    {.h = 3600.0, .s = 7.0, .p = 7.527161441},
};

// Supp-PHS12-2014 ,table9 c Page10: h,s,p
const prop_hsP r2c_hsP[] = {
    {.h = 2800.0, .s = 5.1, .p = 9.439202060E+01},
    {.h = 2800.0, .s = 5.8, .p = 8.414574124},
    {.h = 3400.0, .s = 5.8, .p = 8.376903879e+01},
};

// ------------------ region 3 --------------------------------------------------------

//  Table 33. Thermodynamic property values calculated from Eq. (28) for selected values of T and  a
// T,d,p,h,u,s,cp,w
const propD r3_Td[] = {
    {.T = 650., .d = 500., .p = 0.255837018E2, .h = 0.186343019E4, .u = 0.181226279E4, .s = 0.405427273E1, .cp = 0.138935717E2, .w = 0.502005554E3},
    {.T = 650., .d = 200., .p = 0.222930643E2, .h = 0.237512401E4, .u = 0.226365868E4, .s = 0.485438792E1, .cp = 0.446579342E2, .w = 0.383444594E3},
    {.T = 750., .d = 500., .p = 0.783095639E2, .h = 0.225868845E4, .u = 0.210206932E4, .s = 0.446971906E1, .cp = 0.634165359E1, .w = 0.760696041E3}};

// p,h,t,v
const prop_phTv r3a_phTv[] = {
    {.p = 20., .h = 1700., .T = 6.293083892e2, .v = 1.749903962e-3},
    {.p = 50., .h = 2000., .T = 6.905718338e2, .v = 1.908139035e-3},
    {.p = 100., .h = 2100., .T = 7.336163014e2, .v = 1.676229776e-3}};

const prop_phTv r3b_phTv[] = {
    {.p = 20., .h = 2500., .T = 6.418418053e2, .v = 6.670547043e-3},
    {.p = 50., .h = 2400., .T = 7.351848618e2, .v = 2.801244590e-3},
    {.p = 100., .h = 2700., .T = 8.420460876e2, .v = 2.404234998e-3}};

// p.s.t.v
const prop_psTv r3a_psTv[] = {
    {.p = 20., .s = 3.8, .T = 6.282959869e2, .v = 1.733791463e-3},
    {.p = 50., .s = 3.6, .T = 6.297158726e2, .v = 1.469680170e-3},
    {.p = 100., .s = 4.0, .T = 7.056880237e2, .v = 1.555893131e-3}};

const prop_psTv r3b_psTv[] = {
    {.p = 20., .s = 5.0, .T = 6.401176443e2, .v = 6.262101987e-3},
    {.p = 50., .s = 4.5, .T = 7.163687517e2, .v = 2.332634294e-3},
    {.p = 100., .s = 5.0, .T = 8.474332825e2, .v = 2.449610757e-3}};

//_Backward3_P_hs Table 5 pag 10
const prop_hsP r3a_hsP[] = {
    {.h = 1700, .s = 3.8, .p = 25.5570324620},
    {.h = 2000, .s = 4.2, .p = 45.40873468},
    {.h = 2100, .s = 4.3, .p = 60.78123340100}};

const prop_hsP r3b_hsP[] = {
    {.h = 2600, .s = 5.1, .p = 34.34999263},
    {.h = 2400, .s = 4.7, .p = 63.6392488750},
    {.h = 2700, .s = 5.0, .p = 88.3904328}};

// -------------- region4    ------------------------------------------------------

typedef struct
{
    double p;
    double T;
} prop_pT;

// saturation T,p Table 35
const prop_pT r4_Tp[] = {
    {.T = 300, .p = 0.00353658941},
    {.T = 500, .p = 2.63889776},
    {.T = 600, .p = 12.3443146}};

// saturation p,T Table 36
const prop_pT r4_pT[] = {
    {.p = 0.1, .T = 372.755919},
    {.p = 1, .T = 453.035632},
    {.p = 10, .T = 584.149488}};

const prop_hsT r4_hsT[] = {
    {.h = 1800, .s = 5.3, .T = 346.8475498},
    {.h = 2400, .s = 6.0, .T = 425.1373305},
    {.h = 2500, .s = 5.5, .T = 522.5579013}};

// -------------- region 5    ------------------------------------------------------

// Table 42, page 40 T,p  v,h,u,s,cp,w
const propD r5_pT[] = {
    {.T = 1500, .p = 0.5, .v = 1.38455090, .h = 0.521976855e+4, .u = 4527.49310, .s = 9.65408875, .cp = 2.61609445, .w = 917.068690},
    {.T = 1500, .p = 30, .v = 0.0230761299, .h = 5167.23514, .u = 4474.95124, .s = 7.72970133, .cp = 2.72724317, .w = 928.548002},
    {.T = 2000, .p = 30, .v = 0.0311385219, .h = 6571.22604, .u = 5637.07038, .s = 8.53640523, .cp = 2.88569882, .w = 1067.36948}};

typedef struct
{
    double p;
    double T;
    double v;

} prop_pTv;

//__Backward3_PT v， p,T 52

const prop_pTv r3_pTv[] = {
    {.v = 1.470853100e-3, .p = 50, .T = 630}, // a
    {.v = 1.503831359e-3, .p = 80, .T = 670},
    {.v = 2.204728587e-3, .p = 50, .T = 710}, // b
    {.v = 1.973692940e-3, .p = 80, .T = 750},
    {.v = 1.761696406e-3, .p = 20, .T = 630}, // c
    {.v = 1.819560617e-3, .p = 30, .T = 650},
    {.v = 2.245587720e-3, .p = 26, .T = 656}, // d
    {.v = 2.506897702e-3, .p = 30, .T = 670},
    {.v = 2.970225962e-3, .p = 26, .T = 661}, // e
    {.v = 3.004627086e-3, .p = 30, .T = 675},
    {.v = 5.019029401e-3, .p = 26, .T = 671}, // f
    {.v = 4.656470142e-3, .p = 30, .T = 690},
    {.v = 2.163198378e-3, .p = 23.6, .T = 649}, // g
    {.v = 2.166044161e-3, .p = 24, .T = 650},
    {.v = 2.651081407e-3, .p = 23.6, .T = 652}, // h
    {.v = 2.967802335e-3, .p = 24, .T = 654},
    {.v = 3.273916816e-3, .p = 23.6, .T = 653}, // i
    {.v = 3.550329864e-3, .p = 24, .T = 655},
    {.v = 4.545001142e-3, .p = 23.5, .T = 655}, // j
    {.v = 5.100267704e-3, .p = 24, .T = 660},
    {.v = 6.109525997e-3, .p = 23, .T = 660}, // k
    {.v = 6.427325645e-3, .p = 24, .T = 670},
    {.v = 2.117860851e-3, .p = 22.6, .T = 646}, // l
    {.v = 2.062374674e-3, .p = 23, .T = 646},
    {.v = 2.533063780e-3, .p = 22.6, .T = 648.6}, // m
    {.v = 2.572971781e-3, .p = 22.8, .T = 649.3},
    {.v = 2.923432711e-3, .p = 22.6, .T = 649.0}, // n
    {.v = 2.913311494e-3, .p = 22.8, .T = 649.7},
    {.v = 3.131208996e-3, .p = 22.6, .T = 649.1}, // o
    {.v = 3.221160278e-3, .p = 22.8, .T = 649.9},
    {.v = 3.715596186e-3, .p = 22.6, .T = 649.4}, // p
    {.v = 3.664754790e-3, .p = 22.8, .T = 650.2},
    {.v = 1.970999272e-3, .p = 21.1, .T = 640}, // q
    {.v = 2.043919161e-3, .p = 21.8, .T = 643},
    {.v = 5.251009921e-3, .p = 21.1, .T = 644}, // r
    {.v = 5.256844741e-3, .p = 21.8, .T = 648},
    {.v = 1.932829079e-3, .p = 19.1, .T = 635}, // s
    {.v = 1.985387227e-3, .p = 20, .T = 638},
    {.v = 8.483262001e-3, .p = 17, .T = 626}, // t
    {.v = 6.227528101e-3, .p = 20, .T = 640},
    {.v = 2.268366647e-3, .p = 21.5, .T = 644.6}, // u
    {.v = 2.296350553e-3, .p = 22, .T = 646.1},
    {.v = 2.832373260e-3, .p = 22.5, .T = 648.6}, // v
    {.v = 2.811424405e-3, .p = 22.3, .T = 647.9},
    {.v = 3.694032281e-3, .p = 22.15, .T = 647.5}, // w
    {.v = 3.622226305e-3, .p = 22.3, .T = 648.1},
    {.v = 4.528072649e-3, .p = 22.11, .T = 648}, // x
    {.v = 4.556905799e-3, .p = 22.3, .T = 649},
    {.v = 2.698354719e-3, .p = 22, .T = 646.84}, // y
    {.v = 2.717655648e-3, .p = 22.064, .T = 647.05},
    {.v = 3.798732962e-3, .p = 22, .T = 646.89}, // z
    {.v = 3.701940010e-3, .p = 22.064, .T = 647.15}

};