
#define ICP 0
#define RTU 1

// ????஢?? Reg_err
// 0x1 .... 0x4 - ????⮢?? ?訡?? ???ன??? ??
// ᯨ᪠:
//  struct s_icp_dev  *ICP_dd[]={};
// ??稭?? ?? ???ண? (WDOG[0] ?? ???⠥???)




#define  UZA_sb       0x10
#define  CONS_sb      0x20
#define  TRAP_sb      0x40
#define  ID_sb        0x80
#define  LVL_sb       0x100

#define  ES_sb        0x200
#define  MVD_com_sb   0x400
#define  MVD_cfg_sb   0x800

#define  CRC_sb       0x1000
#define  Flash_sb     0x2000

#define  WD_host_sb   0x4000
#define  OTHER_s      0x8000

#define  Hst_alm_sb        0x8010
#define  DNS_not_off_sb    0x8020
#define  No_Press_sb       0x8030
#define  DNS_st_sb         0x8040
#define  No_src_sb         0x8050
#define  Err_Key_sb        0x8060
#define  OPN_H_sb          0x8070
#define  OPN_L_sb          0x8080

#define  RD_ERR 1
#define  WR_ERR 2
#define  WD_ERR 4
#define  Drive_ERR 8
#define  EEE_CRC_error     0x1
#define  Flash_erase_error 0x2
#define  Flash_wr_error    0x4
#define  No_gas_error      0x8
#define  No_Z_mass_err     0x10
#define  No_F_dat_err      0x20
#define  exm_err           0x40
#define  DNS_not_off       0x40
#define  No_Press          0x80
#define  exp_err           0x80
#define  Gun_off           0x000
#define  WD_host           0x200
#define  No_flow           0x400
#define  DNS_st            0x400
#define  ES_off            0x800
#define  UZA_off           0x1000
#define  MVD_com           0x2000
#define  MVD_cfg           0x4000
#define  MotNotStop        0x0100
#define  DLT_off           0x0201
#define  Hst_alm           0x101
#define  No_Drv            0x401
#define  No_Src            0x8001
#define  Err_Key           0x8002
#define  OPN_H             0x8004
#define  OPN_L             0x8008

int ffgets_com_ICP( int ii);
int f_empty_gets(int ii);
int f_check_crc_ICP(char *buf);
int f_prepare7000(char *Cmd,int CRC_flag);
void f_icp_error(struct s_icp_dev *ICP_DEV,int error_type );
void f_cl_error();
int f_get_icp_error(struct s_icp_dev *ICP_DEV );
void f_icp_errS(int error_type );

extern struct s_icp_dev  *ICP_dd[];
extern int icp_lst_max;
extern struct COM_rqst Rqst_fict;
extern struct s_icp_dev ICP_fict;
extern int ICP_error[];
extern int FL_err;
//---------------
struct s_icp_dev
{
int status;        // 1 - present, 0 - not used
int port;
int addr;         //AA
char name[8];
int baudrate_cod; //CC 03...0A
int type;         //TT 0d,1a
int format;       //FF
int channels;
char firmware[6];
int protocol;
int CRC_flag;
long int pool_time;
long int time_stamp_pool;
long int time_stamp_snd;
long int time_stamp_rcv;
long int n_transaction  ;  // ???????⢮ ?࠭???権 ? ???????
long int n_success      ;  // ???????⢮ ?ᯥ???? ?࠭???権
long int n_timeout_error;  // ???.?訡?? ?? ⠩?????
long int n_CRC_error    ;  // ???. ?訡?? ????஫쭮? ?㬬?
struct COM_rqst *request;
};
//---------------

extern long int fict_long;

extern int ICP_error_c[];
extern int    Reg_err  ;

