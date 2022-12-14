
//extern const unsigned long far *TimeTicks;

void far *_MK_FP_(unsigned s,unsigned off);

#define  DOS8    0
#define  WIN8    1
#define  WIN12   2
#define  WIN16   3

//        0 -  8x8  DOS, ?ᥢ?????䨪?
//        1 -  8x8  Windows
//        2 - 12x12 Windows
//        3 - 16x16 Windows, ?????

struct zone_fnt {
int xx;
int yy;
int lgth;
char font;
};


void SetMFont(int font);
void SetZone(int zone,int x,int y,int lgth,int font);
void Z_MvToX(int zone,int x);
void Z_Gotox(int zone,int x);

int MmiKbhit(void);
int MmiGetch(void);
void SetDisplayPage(int page);
void MmiShowCursor(void);
void MmiCursorOff(void);
void MmiGotoxy(int x,int y);
void SetDisplayPage(int page);
void SendToMMI();
void f_MMI_KBD_ans(int ii);
void f_MMI_SetAns(int ii);
void f_MMI_Flt(int ii);

void MoveToXY(int x,int y);
void MmiPuts(char *str);
int  MmiPrintf(char *format , ...);
void MmiPutch(char ch);
void f_clr_scr_MMI();
void f_clr_scr_c_MMI();
void f_rev_scr_MMI();
int f_get_nb( long int baud);

#define n_bufcom 200  // ????? ?????? ???????

#define MMI_KBD   1
#define MMI_PG    2
#define MMI_ST    3

#define KEY_SIZE  32
#define KEY_SIZ1 (KEY_SIZE-1)
#define MMI_max_inp_err 10
#define MMI_max_out_err 10

extern int  MMI_inp_err;
extern int  MMI_out_err;

//#define size_max 29

#define ESC  'Q'

#define Prev '('
#define Next ')'
#define F1   '@'
#define F2   '#'
#define F3   '$'
#define Sht_F1   'W'
#define Sht_F2   'E'
#define Sht_F3   'R'
#define Sht_ESC  'q'

#define DEL  '\b'
#define DOT  '.'
#define ENTER '\r'
#define ARR_DN '~'
#define ARR_UP '!'
#define ARR_LFT '<'
#define ARR_RGT '>'
#define  DATA '"'
#define  DATA_ESC 0x1b
#define  PASS '&'
//------------------
#define fst_OK  10
#define fst_ESC 0x1b
//------------------

void ServiceCOM( int ii);
int ffgets_host( int port);
void f_Flt_ans(int ii);
void f_empty(int ii);

void f_MMI(void);
int f_menu_MMI();
void  f_prn_begin();
void f_prn_CRC_error();
void f_prn_error();

int f_timer(unsigned long int time_stamp,unsigned long int delay);

int fstin();
extern void (*ff_serv)();

extern char cb_COM[][n_bufcom];
extern int n_bcom[];

extern int pool_MMI;
extern int fn_MMI;

extern int mmi_key_in,mmi_key_out;

extern char MMI_str[40];
extern int mmi_page;

extern int  (*ff_gets_com[5])(int ii);
extern void (*ff_answ_com[5])(int ii);
extern void (*ff_answ_flt[5])(int ii);

extern int fl_mmi_new;

extern int x_mmi,y_mmi;
extern int mmix,mmiy;

extern int flag_mmi;
extern int flag_mmi1;

extern int sw_fst;
extern char fst_str[];
extern int  fst_n;
extern int fl_mmi_new1;
extern int mmi_sw;
extern int flag_echo_host;

extern int ttt1,ttt2,ttt3;
extern unsigned long ttt1_l,ttt2_l,ttt3_l;

#define printf  printCom4
#define getch() getch_host()
#define kbhit() IsCom(4)

//#define putch   ToCom4
#define putch  (*ff_putch[ComPortHost])

#define puts   puts_host

// ?????뢠?? ⥪?饥 ???祭?? ⠩???? ? ?।???? 1 ?? ? 100 ns ????????
// ???祭?? ?? 0 ?? 9999
#define tim1()     asm{mov dx,0ff60H;in ax, dx;mov ttt1,ax}
#define tim2()     asm{mov dx,0ff60H;in ax, dx;mov ttt2,ax}
#define tim3()     asm{mov dx,0ff60H;in ax, dx;mov ttt3,ax}
#define tim4()     asm{mov dx,0ff60H;in ax, dx;mov ttt4,ax}

//10.10.20 YN -(.)-(.)-  mks
    extern int time_s,time_b,time_3;
    #define time_s()     asm{mov dx,0ff60H;in ax, dx;mov time_s,ax}
    #define time_b()     asm{mov dx,0ff60H;in ax, dx;mov time_b,ax}
//-------- YN -//\\-

#define TimeStamp  *TimeTicks

extern int PC_mode;
extern unsigned long ToutAns[5];
extern unsigned long int time_snd[5];

extern int last_out[5];

extern unsigned long ComBaud[];
extern int Com_lgth[];
extern int Com_parity[];
extern int Com_stop[];
extern long int baudrate_val[];
extern struct s_icp_dev MMI;
extern struct COM_rqst MMI_Rqst;
extern float var[];

extern int page_MMI;
extern int page_MMI_c;
extern char sw_ver[20];
extern char sw_ver1[20];

//--------------------------------
struct dis_set_MMI  /* ????????? ??? ?⮡ࠦ????-????? ???祭?? ? MMI */
{
 char **descr;
 int ind;
 void  *op;
 float low_l;
 float high_l;
 int   type;    //T_FLOAT , T_INT ...
};
/*------------------------------*/

void PrintMmiOp(struct dis_set_MMI *ds_s,int flag_prn);
void ScanfMmiOp(struct dis_set_MMI *ds_s);

extern struct dis_set_MMI  ds_list1[];
extern struct dis_set_MMI  ds_list2[];
extern struct dis_set_MMI  ds_list3[];

extern int  flag_prn;
//extern const char *list1_dsr[];

extern int sw_mmi;
extern int max_list1;
extern int max_list2;
extern int max_list3;

extern int CRC_err;
extern unsigned long int time_rcv[];

extern int ComProt[5];

int f_cycle();
void f_time_dd();
void f_print_dd();
void f_one_sec();
void f_mmi_err();
extern long int scom_tim[5];
extern unsigned long Tm_snd[]; //extern long int Tm_snd[];

extern unsigned long int one_sec_time;
extern int flag_Serv;

extern char *list1_dsr[];
extern char *list2_dsr[];

extern int FlagWinSum;

int init_win_sum(int cor);
extern float chg_nn_par,chg_old,chg_new;

extern int un_mmi1;
extern int un_mmi2;
extern int un_mmi3;
extern char *list_un_mmi[];
extern float vBIG_P;

extern float ftmp_naMMI[2];
void f_before_MMI();
void f_after_MMI();
extern int ZeroPage;
extern int EmptPage;

extern int year,month,day,hour,min,sec;
extern float MassStamp;

extern int mode_hst;

extern int N_resv;

extern int NN_resv;
extern float ftmp_LP;

extern char mn_fnt;

void f_tbl_1();