

#define ICP_7017C

#define max_7017 2
//---------------
struct s_icp_dev I7017C[max_7017]=
{
// device 1
0,                // status
1,                // port
02,               // addr
"7017C",        // name[8]
06,               // baudrate_cod
0xd,              // type
0x40,             // format
0xff,             // channels
"B2.6",           // firmware
0,                // protocol
1,                // CRC_flag
400,              // pool_time
0,                // time_stamp_pool;
0,                // time_stamp_snd
0,                // time_stamp_rcv
0,                // n_transaction
0,                // n_success
0,                // n_timeout_error
0,                // n_CRC_error
&I7017_Rqst[0],   // *request
//--------------------------------
// device 2
//--------------------------------
0,                // status
1,                // port
03,               // addr
"7017C/2",        // name[8]
06,               // baudrate_cod
0xd,              // type
0x40,             // format
0xff,             // channels
"B2.6",           // firmware
0,                // protocol
1,                // CRC_flag
150,              // pool_time
0,                // time_stamp_pool
0,                // time_stamp_snd
0,                // time_stamp_rcv
0,                // n_transaction
0,                // n_success
0,                // n_timeout_error
0,                // n_CRC_error
&I7017_Rqst[1],   // *request
};
/*----------------------------*/
struct COM_rqst I7017_Rqst[max_7017]={
//----------------------
// device 1
//--------------------------
0,                     //  ?????ﭨ? ???????
ffgets_com_ICP,        //  gets_com
f_7017_rd_all_hex,     //  answ_com
f_7017_Flt,            //  answ_flt
"7017C/1",             //  name
0,                     //  n_dev ????? ???ன?⢠ ? ??㯯? ????⨯??? ???ன???
&I7017C[0],            //  *ICP_dd
READ_all_hex,          //  ⥪???? ?㭪???
100,                   //  timeout
0,                     //  time_stamp
0,                     //  com_lgth
1,                     //  CRC_flag
"",                    //  com[]
//--------------------------
// device 2
//--------------------------
0,                     //  ?????ﭨ? ???????
ffgets_com_ICP,        //  gets_com
f_7017_rd_all_hex,     //  answ_com
f_7017_Flt,            //  answ_flt
"7017C/2",             //  name
1,                     // n_dev ????? ???ன?⢠ ? ??㯯? ????⨯??? ???ன???
&I7017C[1],            //  *ICP_dd
READ_all_dat,          //  ⥪???? ?㭪???
100,                   //  timeout
0,                     //  time_stamp
0,                     //  com_lgth
1,                     //  CRC_flag
"",                    //  com[]

};
/*----------------------------*/
void f_7017C(int ii)
{
  // ii - ????? ???ன?⢠
  // ?㭪??? 諥? ?????? ?? ????祭?? ?????? ?? ???ன?⢠ ICP 7017C
  //  ( '$aaA') . ??ਮ? ???뫪? I7017C[ii].pool_time ??.
  // ? ?⢥? ?㤥? ??।??? ????ଠ??? ?  8-?? ?????????? ᨣ?????.
  //

int i;
char buf_tmp[20];


 if(I7017C[ii].status == 0) return;

 if( f_timer(I7017C[ii].time_stamp_pool,I7017C[ii].pool_time ))
 {
  if((I7017_Rqst[ii].status == Req_Flt) ||
     (I7017_Rqst[ii].status == Req_OK)) goto m1;
  else if( f_timer(I7017C[ii].time_stamp_pool,(I7017C[ii].pool_time+I7017C[ii].pool_time) ))
           goto m1;
   return;
m1:

          if(I7017_Rqst[ii].function == READ_all_hex)
            sprintf(buf_tmp,"$%02XA",I7017C[ii].addr);
          else if(I7017_Rqst[ii].function == READ_all_dat)
            sprintf(buf_tmp,"#%02X",I7017C[ii].addr);

           if(f_prepare7000(buf_tmp,I7017C[ii].CRC_flag)) return;
           strcpy(I7017_Rqst[ii].Cmd,buf_tmp);
           I7017_Rqst[ii].cmd_lgth=strlen(buf_tmp);
           I7017_Rqst[ii].time_stamp=TimeStamp;
           I7017C[ii].time_stamp_pool=TimeStamp;
           I7017C[ii].n_transaction++;
           f_queue_put(I7017C[ii].port, &I7017_Rqst[ii]);
 }
}
/*----------------------------*/
float ADC[32];
float ADC_c[32];
float ADC_c4[4];

float *i7017_dat[max_7017]={&ADC[0],&ADC[8]};
unsigned int i7017_inp_err[max_7017]={0,0};  // ????稪 ?訡?? ?????

float sc_7017= 10./3276.8; // TT= 1A
//float sc_7017=20./3276.8; // TT= 0d

long int sci_7017= 1; // TT= 1A
//long int sci_7017= 2; // TT= 0d
long int dat_i[12];  // TT= 1A

long int Lvl_7017[12]={2000,2000,2000,2000,2000,2000,2000,2000,2000,2000,2000};
unsigned int INP_7017=0;
void f_7017_rd_all_hex(int ii)
{
// ii - ????? ?????
// ??????? ?ਭ???? ?????? ? ??६????? ??? - ADC[0]...ADC[7]  - ???ன?⢮ 1
//                                            ADC[8]...ADC[15] - ???ன?⢮ 2
//
 struct COM_rqst *request;
 int i,nn,itmp;
 long int itmpl;
 float *dat;
// int dat_i[8];  // ???  TT= 0d
float dat_f[12];
 float mul_s,*t_kor,ftmp;
 int j;
 unsigned int msk_i;

// long int count;
// count=n_bcom[ii]-2;  // ????? ?????

 request=COM_que[ii].request[COM_que[ii].empt_ptr];
 nn=request->n_dev; // ????? ???ன?⢠ 7017 (0,1..)

  {
   if(I7017C[nn].CRC_flag==0) goto m1;
   if(f_check_crc_ICP(cb_COM[ii]))
   {
m1:
    dat=i7017_dat[nn];   // 㪠??⥫? ?? ????? ?????? ??????
    if(dat!= NULL)
    {
      if(request->function==READ_all_hex)
       {
 //? ?⢥? ?? $02A ???室??:
 // >0000 0000 0000 0000 0000 0000 0000 0000 3E
 //       sscanf(cb_COM[ii],">%4x%4x%4x%4x%4x%4x%4x%4x",         // ???  TT= 0d
          sscanf(cb_COM[ii],">%4lx%4lx%4lx%4lx%4lx%4lx%4lx%4lx%4lx%4lx", // ??? TT= 1A
            &dat_i[0],&dat_i[1],&dat_i[2],&dat_i[3],&dat_i[4],&dat_i[5],&dat_i[6],&dat_i[7],&dat_i[8],&dat_i[9]);
//          for(i=0;i<12;i++) dat[i]=(float)(dat_i[i]) * sc_7017;


            INP_7017=0;
              for(i=0,msk_i=1;i<12;i++,msk_i+=msk_i )
               if(dat_i[i] > Lvl_7017[i])
               {
                INP_7017 |=msk_i;
               }


//         INP_VAR &=0x00ff;
//         INP_VAR |= (INP_7017<<8) & 0xff00;
//         INP_VARi = INP_VAR ^ INP_inv;

           itmp=analog_num[0]-1;
           if(itmp>= 0)
           {
             { // ??? ⠡???? ????஢??

              ftmp=dat_i[itmp];
              ADC[0]= ftmp;
              s_MVD[0].Press= ftmp * analog_scale[0] + analog_offset[0];
             }

      //     if((Delta[0].status !=0) ||  (ComSK[0].status !=0) )
             if( *DriveStatus !=0)
                if(flag_O3) f_reg_P(); // ॣ?????? ????????

           }
           itmp=analog_num[1]-1;
           if(itmp>= 0)
           {
             { // ??? ⠡???? ????஢??
              ftmp=dat_i[itmp];
              ADC[1]= ftmp;


#if defined(BIO_1)
              P_inp= ftmp * analog_scale[1] + analog_offset[1];
#else
              s_MVD[0].TempR= ftmp * analog_scale[1] + analog_offset[1];
#endif



             }
           }
       }
      else if(request->function==READ_all_dat)
       {
//#02  >+00.000+00.000+00.000+00.000+00.000+00.000+00.000+00.00086
        sscanf(cb_COM[ii],">%f%f%f%f%f%f%f%f",
//      sscanf(cb_COM[ii],">%7f%7f%7f%7f%7f%7f%7f%7f",
//      &dat[0],&dat[1],&dat[2],&dat[3],&dat[4],&dat[5],&dat[6],&dat[7]);
         &dat_f[0],&dat_f[1],&dat_f[2],&dat_f[3],
         &dat_f[4],&dat_f[5],&dat_f[6],&dat_f[7]);
      /*
           for(i=0;i<8;i++)
            {
             if(dat_f[i] < 0) dat[i]=-0.01;
             else dat[i] = dat_f[i] * 10.;
            }
      */
       }
    }
    I7017C[nn].n_success++;
    i7017_inp_err[nn]=0;
   }
   else
   {

         i7017_inp_err[nn]++;
         if(i7017_inp_err[nn]>=I7017_max_inp_err)
         {
           i7017_inp_err[nn]=I7017_max_inp_err;
           f_icp_error(&I7017C[nn],RD_ERR );
         }
    I7017C[nn].n_CRC_error++;
   }
  }
 f_queue_free(ii,&I7017_Rqst[nn]);
}
/*-------------------------------------------*/
void f_7017_Flt(int ii)
{
 struct COM_rqst *request;
 int nn;

 request=COM_que[ii].request[COM_que[ii].empt_ptr];
 nn=request->n_dev; // ????? ???ன?⢠ 7017 (0,1..)
 I7017C[nn].time_stamp_rcv=0;
 I7017C[nn].n_timeout_error++;
 i7017_inp_err[nn]++;
 if(i7017_inp_err[nn]>=I7017_max_inp_err)
 {
   i7017_inp_err[nn]=I7017_max_inp_err;
   f_icp_error(&I7017C[nn],RD_ERR );
 }
// f_queue_free(ii,&I7017_Rqst[nn]);
 f_queue_Flt(ii);

}
/* ---------------------------------------- */