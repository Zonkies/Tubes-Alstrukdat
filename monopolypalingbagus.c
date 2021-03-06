#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "boolean.h"



#define C_IMax 40 //baris maksimum pada T_Pixels
#define C_JMax 74 //kolom maksimum pada T_Pixels
#define C_UKiri 1 //ujung kiri board
#define C_UKanan 72 //ujung kanan board
#define C_UAtas 1 //ujung atas board
#define C_UBawah 36 //ujung bawah board
#define C_Mark -999

typedef struct
{
    int x; //absis
    int y; //ordinat
}T_Point;

typedef struct
{
    char T[C_IMax+1][C_JMax+1];
}T_BoardPixels;

typedef struct
{
    char Nama[15];
    int Urutan;
    int HargaBeli;
    char Kompleks;
    int Pemilik;
    T_Point Letak;
}T_Tempat;

typedef struct
{
    T_Tempat T[20];
}T_TabTempat;

typedef struct
{
    char Nama[10];
    char Logo;
    int Uang;
    int Aset;
    T_Point Letak;
    int Urutan;
    boolean Kalah;
}T_Pemain;

typedef struct
{
    T_Pemain T[5];
    int JmlPemain;
    int LamaPenjara[5];
}T_TabPemain;

T_BoardPixels V_BoardPixels;

/* Modul ADT T_Giliran – Alternatif I */
/* *** Deklarasi T_Giliran yang diimplementasi dengan tabel kontigu *** */
/* *** HEAD dan TAIL adalah alamat elemen pertama dan terakhir  *** */
/* *** T_Giliran mampu menampung MaxEl buah elemen *** */

/* *** Konstanta *** */
#define C_Nil 0

/* *** Akses (selektor) *** */
#define F_Head(V_Giliran) (V_Giliran).HEAD
#define F_Tail(V_Giliran) (V_Giliran).TAIL
#define F_InfoHead(V_Giliran) (V_Giliran).T[(V_Giliran).HEAD]
#define F_InfoTail(V_Giliran) (V_Giliran).T[(V_Giliran).TAIL]
#define F_MaxEl(V_Giliran) (V_Giliran).MaxEl



/* *** Definisi elemen dan T_Address *** */
typedef int T_Info;
typedef int T_Address; /* indeks tabel */
/* *** Definisi Type T_Giliran *** */
typedef struct
{
    T_Info *T; /* tabel penyimpan elemen, tergantung bahasa */
    T_Address HEAD; /* alamat penghapusan */
    T_Address TAIL; /* alamat penambahan  */
    int MaxEl; /* maksimum banyaknya elemen queue */
}T_Giliran;
/* Definisi T_Giliran kosong: Head = C_Nil; TAIL = C_Nil. */ /* Catatan implementasi: T[0] tidak pernah dipakai */
/* Definisi akses dengan Selektor : Isilah dengan selektor yang tepat */

void P_MasukPenjara(T_TabPemain *V_TabPemain, int V_GiliranX);

/* *** Predikat Pemeriksaan Kondisi T_Giliran *** */
boolean F_IsEmpty (T_Giliran V_Giliran);/*Mengirim true jika V_Giliran kosong */
/* *** Konstruktor *** */
void P_CreateEmpty (T_Giliran *V_Giliran, int V_Max);
/* I.S. Max terdefinisi */
/* F.S. Sebuah V_Giliran kosong terbentuk dan salah satu kondisi V_Koordinatb :       */
/*      Jika aUrutan berhasil, tabel memori diaUrutan berukuran Max  */
/*      atau : jika aUrutan gagal, V_Giliran kosong dg Maksimum elemen=0     */ /* Proses : Melakukan aUrutan memori dan membuat sebuah V_Giliran kosong     */
/* *** Destruktor *** */
void P_DeAlokasi (T_Giliran *V_Giliran);
/* Proses : Mengembalikan memori V_Giliran */
/* I.S. V_Giliran pernah diaUrutan */
/* F.S. V_Giliran menjadi tidak terdefinisi lagi, MaxEl(V_Giliran) diset 0 */
/* *** Operator-Operator Dasar T_Giliran *** */
void P_Add (T_Giliran *V_Giliran, T_Info V_Info);
/* Proses : Menambahkan  X pada V_Giliran dengan aturan FIFO */
/* I.S. V_Giliran mungkin kosong, tabel penampung elemen V_Giliran TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" */
void P_Del (T_Giliran *V_Giliran, T_Info *V_Info); /* Proses: Menghapus elemen pertama pada V_Giliran dengan aturan FIFO */
/* I.S. V_Giliran tidak kosong */
/* F.S. X = nilai elemen HEAD pada I.S.,
       Jika T_Giliran masih isi : HEAD diset tetap = 1, elemen-elemen setelah HEAD yang         lama digeser ke "kiri", TAIL = TAIL – 1;        Jika T_Giliran menjadi kosong, HEAD = TAIL = C_Nil. */




boolean F_IsGedung(T_Tempat V_Tempat);
boolean F_IsPointSama(T_Point P1, T_Point P2);

void P_InsertJumlahPemain(T_TabPemain *V_TabPemain, T_Giliran *V_Giliran);
void P_PrintGame( T_TabTempat V_TabTempat, T_TabPemain V_TabPemain);

int F_GetOrdinatKotak(int i);
int F_GetAbsisKotak(int j);

void P_Delay(unsigned int mseconds);

void P_MajuSelangkah(T_Pemain *V_Pemain, int V_GiliranX);


void P_Kotak(T_Point V_Point, T_TabTempat V_TabTempat, T_TabPemain V_TabPemain);

void P_SetBoard(T_TabTempat *V_TabTempat, T_TabPemain *V_TabPemain);

void P_Inisiasi(T_TabTempat *V_TabTempat, T_TabPemain *V_TabPemain );
void P_InisiasiPemain(T_TabPemain *V_TabPemain);
void P_IsiLogo(T_TabPemain *V_TabPemain);
void P_BlankAll();

void P_SetStatus(T_TabTempat *V_TabTempat, T_TabPemain *V_TabPemain);
void P_SetStatusPemain (T_TabPemain *V_TabPemain);

T_Point F_UrutanToKoordinat(int V_UrutanGedung);
int F_KoordinatToUrutan(T_Point V_Koordinat);
boolean F_IsPemainEmpty(T_Pemain V_Pemain);
void P_StatusPemain(T_TabPemain V_TabPemain);
void P_Turn(T_TabPemain V_TabPemain, int *V_Dadu1, int *V_Dadu2, boolean *V_IsSudahKocok, int i);
void P_SetColor(int ForgC);
void P_UrutanToPixel (int V_UrutanGedung, int V_Baris, int V_Kolom, T_Point *V_Pixel);
void P_ChangeTurn(T_Giliran *V_Giliran);





int main()
{
    //kamus
    int i, j, V_Dadu1, V_Dadu2, V_SumDadu, Turns, V_GiliranX, V_LokasiPemain, V_HargaSewa, V_HargaJual, V_NilaiKoin, V_Taruhan, V_PemainTerhapus, V_Kesempatan;
    T_TabTempat V_TabTempat;
    T_Tempat V_Tempat;
    T_TabPemain V_TabPemain;
    boolean V_IsSudahKocok, V_IsKalah, V_IsAdaGedung, V_IsMenang, V_IsInjakStart, V_IsLewatStart, V_IsJalanLagi;
    char V_Pilihan;
    char V_PilihanKoin[4], V_NamaGedung[15];
    T_Point V_Pixel;
    T_Giliran V_Giliran;

    //algoritma

    srand(time(NULL));
    //P_Inisialisasi
    P_Inisiasi(&V_TabTempat, &V_TabPemain );
    P_InsertJumlahPemain(&V_TabPemain, &V_Giliran);
    P_IsiLogo(&V_TabPemain);

    P_SetBoard( &V_TabTempat,&V_TabPemain);


    //P_SetStatus(, &V_TabTempat, &V_TabPemain);
    //P_PrintGame(game, V_TabTempat, p);

    Turns=1;//P_Turn pertama
    do
    {
        V_GiliranX= F_InfoHead(V_Giliran);//((Turns-1)%V_TabPemain.JmlPemain)+1; pada P_Turn sekian, yang mainnya V_GiliranX orang keberapa
        P_PrintGame(V_TabTempat, V_TabPemain);//print boardnya
        P_StatusPemain(V_TabPemain);
        V_IsSudahKocok=false;//awalnya belum ngocok
        P_Turn(V_TabPemain, &V_Dadu1, &V_Dadu2, &V_IsSudahKocok, Turns);//nampilin keterangan di bawah tentang dadu dan sebagainya, dadu disini berarti output
        V_SumDadu=V_Dadu1+V_Dadu2;//total dua dadu
        V_IsInjakStart=false;//tidak menginjak start
        V_IsLewatStart=false;//tidak melewati start
        V_IsJalanLagi = (V_Dadu1 == V_Dadu2);

        if((V_TabPemain.LamaPenjara[V_GiliranX] > 0)&&(V_Dadu1 != V_Dadu2))
        {
            printf("%s tidak dapat bermain selama %d putaran lagi kecuali mendapatkan angka dadu yang sama.\n", V_TabPemain.T[V_GiliranX].Nama,V_TabPemain.LamaPenjara[V_GiliranX]);
            V_TabPemain.LamaPenjara[V_GiliranX] = V_TabPemain.LamaPenjara[V_GiliranX] - 1;
            P_Delay(2000);
        }
        else
        {
            if(V_TabPemain.LamaPenjara[V_GiliranX] > 0){
                V_TabPemain.LamaPenjara[V_GiliranX] = 0;
                V_IsJalanLagi = false;
            }

            /* *** KONDISI SAAT PEMAIN MAJU *** */
            for(i=1;i<=(V_SumDadu);i++)//T_Pemain maju sebanyak tdadu, tetapi satu2 agar user experience lebih terasa
            {
                P_Delay(250);
                P_MajuSelangkah(&(V_TabPemain.T[V_GiliranX]), V_GiliranX);//maju satu langkah
                if((V_TabPemain.T[V_GiliranX].Urutan==0) && (Turns>V_TabPemain.JmlPemain))//saat menginjek start, tetapi tentu saja bukan saat awal permainan
                {
                    V_IsInjakStart=true;
                }
                else if(V_IsInjakStart)//jika sudah pernah nginjek start, otomatis T_Pemain berarti melewati start
                {
                    V_IsLewatStart=true;
                }
                P_PrintGame(V_TabTempat, V_TabPemain);
            }
            P_StatusPemain(V_TabPemain);
            P_Turn(V_TabPemain, &V_Dadu1, &V_Dadu2, &V_IsSudahKocok, Turns);

            /* *** KONDISI MELEWATI START *** */
            if((V_IsInjakStart)&&(!V_IsLewatStart))//kalo cuma nginjek start tapi ga lewat
            {
                printf("%s menempati posisi Start.\n", V_TabPemain.T[V_GiliranX].Nama);
                printf("%s tidak mendapatkan gaji apapun.\n", V_TabPemain.T[V_GiliranX].Nama);
            }
            else if (V_IsLewatStart)//T_Pemain melewati start
            {
                printf("%s melewati posisi Start.\n", V_TabPemain.T[V_GiliranX].Nama);
                printf("%s mendapatkan gaji sebesar Rp 1,500,000.\n", V_TabPemain.T[V_GiliranX].Nama);
                V_TabPemain.T[V_GiliranX].Uang=V_TabPemain.T[V_GiliranX].Uang+1500000;
                V_TabPemain.T[V_GiliranX].Aset=V_TabPemain.T[V_GiliranX].Aset+1500000;
            }
            P_Delay(1000);

            /* *** KONDISI PEMAIN SAAT MEMASUKI LOKASI/ TEMPAT TERTENTU *** */
            V_LokasiPemain=V_TabPemain.T[V_GiliranX].Urutan;//Urutan T_Pemain saat ini (0..19)
            V_Tempat=V_TabTempat.T[V_LokasiPemain];
            //kalo yang di V_TabTempati gedung
            if (F_IsGedung(V_Tempat))
            {
                if(V_TabTempat.T[V_LokasiPemain].Pemilik==0)//jika tidak ada Pemiliknya berarti V_Pilihan untuk membeli gedung atau tidak
                {
                    printf("beli gedung?\n");
                    scanf(" %c", &V_Pilihan);
                    if(V_Pilihan=='y')
                    {
                        if ((V_TabPemain.T[V_GiliranX].Uang-V_TabTempat.T[V_LokasiPemain].HargaBeli)>=0)//kalo Uangnya cukup bisa beli
                        {
                            printf("%s membeli Gedung %s seharga Rp %d\n", V_TabPemain.T[V_GiliranX].Nama, V_TabTempat.T[V_LokasiPemain].Nama, V_TabTempat.T[V_LokasiPemain].HargaBeli);
                            V_TabPemain.T[V_GiliranX].Uang=V_TabPemain.T[V_GiliranX].Uang-V_TabTempat.T[V_LokasiPemain].HargaBeli;
                            V_TabPemain.T[V_GiliranX].Aset=V_TabPemain.T[V_GiliranX].Uang+(V_TabTempat.T[V_LokasiPemain].HargaBeli/2);
                            V_TabTempat.T[V_LokasiPemain].Pemilik=V_GiliranX;
                        }
                        else //kalo Uang nya tidak cukup ga bisa beli
                        {
                            printf("%s tidak bisa membeli gedung, karena Uang anda tidak mencukupi!\n", V_TabPemain.T[V_GiliranX].Nama);
                        }
                        P_Delay(2000);
                    }
                }
                else//gedung sudah ada yang punya
                {
                    printf("%s berada pada Gedung %s yang dimiliki oleh %s\n", V_TabPemain.T[V_GiliranX].Nama, V_TabTempat.T[V_LokasiPemain].Nama, V_TabPemain.T[V_TabTempat.T[V_LokasiPemain].Pemilik].Nama);
                    V_HargaSewa=V_TabTempat.T[V_LokasiPemain].HargaBeli*30/100;
                    do
                    {
                        if((V_TabPemain.T[V_GiliranX].Uang-V_HargaSewa)<0)//kalo ga cukup bayar sewa, jual gedung yang sudah dimiliki
                        {
                            if(V_TabPemain.T[V_GiliranX].Uang==V_TabPemain.T[V_GiliranX].Aset)
                            {
                                printf("%s tidak dapat membayar sewa gedung dan T_Pemain tidak memiliki gedung untuk di jual\n",V_TabPemain.T[V_GiliranX].Nama);
                                printf("%s kalah!\n", V_TabPemain.T[V_GiliranX].Nama);
                                V_TabPemain.T[V_GiliranX].Kalah=true;
                                P_Del(&V_Giliran, &V_PemainTerhapus);
                            }
                            else
                            {
                                printf("%s tidak memiliki Uang yang cukup untuk membayar Uang sewa.\n", V_TabPemain.T[V_GiliranX].Nama);
                                printf("Sebutkan gedung yang ingin dijual! ");
                                scanf(" %s", &V_NamaGedung);
                                V_IsAdaGedung=false;
                                for (i=0;i<=19;i++)
                                {
                                    if((strcmp(V_NamaGedung, V_TabTempat.T[i].Nama)==0) && (V_TabTempat.T[i].Pemilik==V_GiliranX))//cek ada apa tidak gedung tersebut
                                    {
                                        V_IsAdaGedung=true;
                                        V_HargaJual=V_TabTempat.T[i].HargaBeli*50/100;
                                        V_TabPemain.T[V_GiliranX].Uang=V_TabPemain.T[V_GiliranX].Uang+V_HargaJual;
                                        V_TabTempat.T[i].Pemilik=0;
                                    }
                                }
                                if(!V_IsAdaGedung)//gedung tidak ada dan T_Pemain tersebut bukan yang punya
                                {
                                    printf("Gedung %s tidak ada atau dimiliki orang lain\n", V_NamaGedung);
                                }
                            }
                        }
                    }while((V_TabPemain.T[V_GiliranX].Uang-V_HargaSewa)<0);
                 //Uang dan Aset T_Pemain berkurang
                    V_TabPemain.T[V_GiliranX].Uang=V_TabPemain.T[V_GiliranX].Uang-V_HargaSewa;
                    V_TabPemain.T[V_GiliranX].Aset=V_TabPemain.T[V_GiliranX].Aset-V_HargaSewa;
                    //Uang Pemilik gedung bertambah
                    V_TabPemain.T[V_TabTempat.T[V_LokasiPemain].Pemilik].Uang=V_TabPemain.T[V_TabTempat.T[V_LokasiPemain].Pemilik].Uang+V_HargaSewa;
                    V_TabPemain.T[V_TabTempat.T[V_LokasiPemain].Pemilik].Aset=V_TabPemain.T[V_TabTempat.T[V_LokasiPemain].Pemilik].Aset+V_HargaSewa;
                    printf("%s membayar Uang sewa ke %s sebesar Rp %d.\n", V_TabPemain.T[V_GiliranX].Nama, V_TabPemain.T[V_TabTempat.T[V_LokasiPemain].Pemilik].Nama, V_HargaSewa);
                    P_Delay(2000);

                }
            }
            //JIKA YANG DI MASUKI LOKASI UNDIAN
            else if(V_LokasiPemain==10)
            {
                printf("%s mendapatkan kesempatan Undian.\n", V_TabPemain.T[V_GiliranX].Nama);
                V_IsKalah=false;

                printf("Apakah Anda ingin bermain? ");
                scanf(" %c", &V_Pilihan);
                if((V_Pilihan=='y')&&((V_TabPemain.T[V_GiliranX].Uang-1500000)>=0))
                {
                    printf("%s membayar 1,5 juta untuk melakukan taruhan.\n", V_TabPemain.T[V_GiliranX].Nama);
                    V_TabPemain.T[V_GiliranX].Uang=V_TabPemain.T[V_GiliranX].Uang-1500000;
                    V_TabPemain.T[V_GiliranX].Aset=V_TabPemain.T[V_GiliranX].Aset-1500000;
                    V_Taruhan=1500000;
                    do
                    {
                        printf("Taruhan Anda (Head/Tail) : ");
                        scanf(" %s", &V_PilihanKoin);
                        V_NilaiKoin=rand() %2 +1;
                        if (V_NilaiKoin==1)
                        {
                            printf("Hasil Undian : Head\n");
                            if(strcmp(V_PilihanKoin, "Head")==0)
                            {
                                printf("Anda Menang! ");
                                V_Taruhan=V_Taruhan*2;
                            }
                            else
                            {
                                V_IsKalah=true;
                            }
                        }
                        else if (V_NilaiKoin==2)
                        {
                            printf("Hasil Undian : Tail\n");
                            if(strcmp(V_PilihanKoin, "Tail")==0)
                            {
                                printf("Anda Menang! ");
                                V_Taruhan=V_Taruhan*2;
                            }
                            else
                            {
                                V_IsKalah=true;
                            }
                        }
                        if (!V_IsKalah)
                        {
                            printf("Apakah Anda ingin bermain? ");
                            scanf(" %c", &V_Pilihan);
                        }
                        else
                        {
                            printf("Anda Kalah! Anda tidak mendapatkan apapun.\n");
                            V_Taruhan=0;
                            P_Delay(2000);
                        }
                    }while((!V_IsKalah)&&(V_Pilihan=='y'));

                    V_TabPemain.T[V_GiliranX].Uang=V_TabPemain.T[V_GiliranX].Uang+V_Taruhan;
                    V_TabPemain.T[V_GiliranX].Aset=V_TabPemain.T[V_GiliranX].Aset+V_Taruhan;
                }
                else if((V_TabPemain.T[V_GiliranX].Uang-1500000)<0)
                {
                    printf("Uang anda tidak cukup! \n");
                }
            }
            else if(V_LokasiPemain==5)
            {
                P_MasukPenjara(&V_TabPemain, V_GiliranX);
                V_IsJalanLagi=false;
            }
            else if((V_LokasiPemain==7)||(V_LokasiPemain==13)||(V_LokasiPemain==16)){
                printf("%s mendapatkan kartu kesempatan: ", V_TabPemain.T[V_GiliranX].Nama);
                V_Kesempatan = rand() % 3 + 1;
                switch(V_Kesempatan){
                    case 1:{
                        printf("Masuk Penjara\n");
                        printf("%s masuk penjara\n",V_TabPemain.T[V_GiliranX].Nama);
                        P_MasukPenjara(&V_TabPemain, V_GiliranX);
                        P_UrutanToPixel(V_TabPemain.T[V_GiliranX].Urutan, 4, (1+(2*V_GiliranX)), &V_Pixel); //menyimpan koordinat dari Logo T_Pemain
                        V_BoardPixels.T[V_Pixel.y][V_Pixel.x]=' '; //koordinat yang sebelumnya didapat, di reT_TabTempat menjadi ' ' (kosong)
                        V_TabPemain.T[V_GiliranX].Urutan=5;
                        P_UrutanToPixel(V_TabPemain.T[V_GiliranX].Urutan, 4, (1+(2*V_GiliranX)), &V_Pixel); //ambil V_Koordinat sebagai koordinat baru Logo nya
                        V_BoardPixels.T[V_Pixel.y][V_Pixel.x]=V_TabPemain.T[V_GiliranX].Logo;//isi koordinat baru tersebut dengan Logo nya
                        break;
                    }
                    case 2:{
                        printf("Tiket Bus ITB\n");
                        printf("Apakah anda ingin menggunakan Tiket Bus ITB? ");scanf(" %c",&V_Pilihan);
                        if(V_Pilihan=='y'){
                            do{
                                printf("Sebutkan lokasi yang ingin anda tuju : ");scanf("%s",&tempatt);
                                i = 0;
                                do{
                                    i = i + 1;
                                    adagedung = tempatt==tempat.tmpt[i].name;
                                }while(!adagedung && (i < 20));
                                if(!adagedung)
                                    printf("gedung tidak ada!\n");
                            }while(!adagedung);
                            majuke(&p.pem[giliran], giliran, i);
                            printf("%s maju ke %s\n",p.pem[giliran].nama,tempatt);
                        }
                        break;
                    }
                    case 3:{
                        printf("Tukar Gedung\n");
                        printf("Apakah anda ingin menukar gedung? ");scanf(" %c",&pilihan);
                        if(pilihan=='y'){
                            tempat.tmpt[].pemilik=giliran;
                        }
                    }
                }
            }
        }

        //mengecek dadu kembar atau tidak
        if(!V_IsJalanLagi)
        {
            Turns++;
            P_ChangeTurn(&V_Giliran);
        }
    }while(Turns<=20);
    return 0;
}

void P_MasukPenjara(T_TabPemain *V_TabPemain, int V_GiliranX)
{
    (*V_TabPemain).LamaPenjara[V_GiliranX] = 2;
    printf("%s tidak dapat bermain selama 3 putaran kecuali mendapatkan angka dadu yang sama.\n", (*V_TabPemain).T[V_GiliranX].Nama);
    P_Delay(1000);
}




/* *** FUNGSI PENGECEKAN *** */
boolean F_IsGedung(T_Tempat V_Tempat) //cek apakah gedung atau bukan
{
    return (V_Tempat.Kompleks!='0'); //kalo bukan komplek '0' berarti gedung
}

boolean F_IsPointSama(T_Point P1, T_Point P2)
{
    //mencek apakah T_Point 1 dan 2 sama
    return ((P1.x==P2.x)&&(P1.y==P2.y));
}

/* *** MENGGERAKAN PEMAIN *** */
void P_MajuSelangkah(T_Pemain *V_Pemain, int V_GiliranX)
{
    int i, j, urut, kolomorang;
    T_Point V_Pixel;

    P_UrutanToPixel((*V_Pemain).Urutan, 4, (1+(2*V_GiliranX)), &V_Pixel); //menyimpan koordinat dari Logo T_Pemain
    V_BoardPixels.T[V_Pixel.y][V_Pixel.x]=' '; //koordinat yang sebelumnya didapat, di reT_TabTempat menjadi ' ' (kosong)
    (*V_Pemain).Urutan=((*V_Pemain).Urutan+1)%20; //Urutan nya maju satu, tapi harus di mod 20, karena Urutan cuma dari 0 sampe 19
    P_UrutanToPixel((*V_Pemain).Urutan, 4, (1+(2*V_GiliranX)), &V_Pixel); //ambil V_Koordinat sebagai koordinat baru Logo nya
    V_BoardPixels.T[V_Pixel.y][V_Pixel.x]=(*V_Pemain).Logo;//isi koordinat baru tersebut dengan Logo nya
}

/* *** PRINT KE LAYAR *** */
void P_PrintGame(T_TabTempat V_TabTempat, T_TabPemain V_TabPemain)
{
    //print kelayar
    //kamus
    int i, j, urut, kolomorang;
    T_Point V_Koordinat, smb;
    T_Point sumbu[5];
    //algoritma
    for(i=1;i<=4;i++)//untuk setiap orang, posisi Logo nya berada pada kolom kolomorang, dan baris 4 (untuk di P_Kotak besar)
    {
        kolomorang=1+(2*i);
        P_UrutanToPixel(V_TabPemain.T[i].Urutan, 4, kolomorang, &V_Koordinat); //merubah Urutan nya menjadi koordinat P_Kotak kecil/ koordinat T_Pixels (1..72, 1..36)
        sumbu[i]=V_Koordinat;
    }

    system("cls"); //clear screen
    for(i=C_UAtas;i<=(C_IMax-1);i++)
    {
        for(j=C_UKiri;j<=(C_JMax-1);j++)
        {
            smb.x=j; //ubah j ke T_Point
            smb.y=i; //i di masukan ke T_Point
            V_Koordinat.y=F_GetOrdinatKotak(i); //V_Koordinat dalam kotk besar nya
            V_Koordinat.x=F_GetAbsisKotak(j); //V_Koordinat dalam P_Kotak besar nya
            urut=F_KoordinatToUrutan(V_Koordinat); //merubah ke Urutan(0..19)
            if (urut!=C_Mark) //kalo antara 0..19
            {
                if((F_IsPointSama(smb, sumbu[1]))||(F_IsPointSama(smb, sumbu[4]))||(F_IsPointSama(smb, sumbu[2]))||(F_IsPointSama(smb, sumbu[3])))
                    //melakukan pengecekan apakah yang akan di print merupakan Logo, karena jika Logo warnanya harus sesuai.
                {
                    if(F_IsPointSama(smb, sumbu[1]))
                    {
                        P_SetColor(1);
                        printf("%c", V_BoardPixels.T[i][j]);
                    }
                    else if (F_IsPointSama(smb, sumbu[2]))
                    {
                        P_SetColor(2);
                        printf("%c", V_BoardPixels.T[i][j]);
                    }
                    else if (F_IsPointSama(smb, sumbu[3]))
                    {
                        P_SetColor(3);
                        printf("%c", V_BoardPixels.T[i][j]);
                    }
                    else if (F_IsPointSama(smb, sumbu[4]))
                    {
                        P_SetColor(4);
                        printf("%c", V_BoardPixels.T[i][j]);
                    }
                }
                else
                {
                    //mengeprint warna setiap P_Kotak sesuai Pemiliknya
                    if (V_TabTempat.T[urut].Pemilik==1) //jika Pemiliknya si 1
                    {
                        P_SetColor(1);
                        printf("%c", V_BoardPixels.T[i][j]);
                    }
                    else if (V_TabTempat.T[urut].Pemilik==2) //jika Pemiliknya si 2
                    {
                        P_SetColor(2);
                        printf("%c", V_BoardPixels.T[i][j]);
                    }
                    else if (V_TabTempat.T[urut].Pemilik==3) //jika Pemiliknya si 3
                    {
                        P_SetColor(3);
                        printf("%c", V_BoardPixels.T[i][j]);
                    }
                    else if (V_TabTempat.T[urut].Pemilik==4) //jika Pemiliknya si 4
                    {
                        P_SetColor(4);
                        printf("%c", V_BoardPixels.T[i][j]);
                    }
                    else
                    {
                        P_SetColor(7);
                        printf("%c", V_BoardPixels.T[i][j]);
                    }
                }
            }
            else
            {
                P_SetColor(7);
                printf("%c", V_BoardPixels.T[i][j]);
            }
        }
        P_SetColor(7);
        printf("\n");
    }
}


/* *** FUNGSI CONVERT ****/
void P_UrutanToPixel (int V_UrutanGedung, int V_Baris, int V_Kolom, T_Point *V_Pixel)
{
    //merubah Urutan (0 sampai 19) jadi koordinat(1..72, 1..36)
    T_Point V_Koordinat;//sumbu dalam P_Kotak besar
    V_Koordinat=F_UrutanToKoordinat(V_UrutanGedung);//merubah Urutan/Urutan menjadi sumbu dalam P_Kotak besar
    (*V_Pixel).x=V_Kolom+(12*(V_Koordinat.x-1));
    (*V_Pixel).y=V_Baris+(6*(V_Koordinat.y-1));
}

int F_KoordinatToUrutan(T_Point V_Koordinat) //merubah T_Point P_Kotak besar(1..6, 1..6) menjadi Urutan(0..19)
{
    if((V_Koordinat.y==6)||(V_Koordinat.x==1))
    {
        return (6-V_Koordinat.y)+(6-V_Koordinat.x);
    }
    else if ((V_Koordinat.x==6)||(V_Koordinat.y==1))
    {
        return 20-((6-V_Koordinat.y)+(6-V_Koordinat.x));
    }
    else
    {
        return C_Mark;
    }
}
int F_GetOrdinatKotak(int i) //merubah baris pada T_Pixels(1..72, 1..36) ke P_Kotak yang besar (1..6, 1..6)
{
    int barmin, hasil; //baris paling atas(1), hasil baris nya

    hasil=1;
    barmin=1;

    do{
        if((i>=barmin)&&(i<=(barmin+5)))
        {
            return hasil;
        }
        barmin=barmin+6;//tambah 6 baris, berarti kalo di P_Kotak besar setara dengan nambah satu baris
        hasil++;
    }while(i<=C_UBawah);
    return 0;
}

int F_GetAbsisKotak(int j) //merubah kolom pada T_Pixels(1..72, 1..36) ke P_Kotak yang besar (1..6, 1..6)
{
    int kolmin, hasil; //kolom paling atas(1), hasil kolom nya

    hasil=1;
    kolmin=1;
    do{
        if((j>=kolmin)&&(j<=(kolmin+11)))
        {
            return hasil;
        }
        kolmin=kolmin+12;//tambah 12 kolom, berarti kalo di P_Kotak besar setara dengan nambah satu kolom
        hasil++;
    }while(j<=C_UKanan);//kalo belum sampe ujung board
    return 0;
}

T_Point F_UrutanToKoordinat(int V_UrutanGedung) //mengubah Urutan(0..19) menjadi T_Point dalam P_Kotak besar (1..6, 1..6)
{
    T_Point V_Koordinat;

    if((V_UrutanGedung>=0)&&(V_UrutanGedung<=5))
    {
        V_Koordinat.x=6-V_UrutanGedung;
        V_Koordinat.y=6;
    }
    else if((V_UrutanGedung>=5)&&(V_UrutanGedung<=10))
    {
        V_Koordinat.x=1;
        V_Koordinat.y=1+(10-V_UrutanGedung);
    }
    else if ((V_UrutanGedung>=10)&&(V_UrutanGedung<=15))
    {
        V_Koordinat.x=V_UrutanGedung-9;
        V_Koordinat.y=1;
    }
    else if ((V_UrutanGedung>=15)&&(V_UrutanGedung<=20))
    {
        V_Koordinat.y=V_UrutanGedung-14;
        V_Koordinat.x=6;
    }
    else
    {
        V_Koordinat.x=C_Mark;
        V_Koordinat.y=C_Mark;
    }
    return V_Koordinat;
}



/* *** MENAMPILKAN KETERANGAN TENTANG PEMAIN *** */
void P_Turn(T_TabPemain V_TabPemain, int *V_Dadu1, int *V_Dadu2, boolean *V_IsSudahKocok, int i)//T_Pemainnya, nilai dadu1, nilai dadu2, udah pernah ngocok belum
{   //melakukan P_Turn, seperti mengocok dadu
    //kamus
    int V_GiliranX, tdadu; //V_GiliranX siapa sekarang(orang), total dadu(dadu1 + dadu2)
    char V_Pilihan;
    //algoritma
    printf("-----Turn %d-----\n", i);
    V_GiliranX=((i-1)%V_TabPemain.JmlPemain)+1; //mencari V_GiliranX siapa
    printf("Giliran : %s\n", V_TabPemain.T[V_GiliranX].Nama);
    printf("tekan untuk mengocok dadu!\n");
    if(!(*V_IsSudahKocok)) //jika belum ngocok
    {   // melakukan pengocokan dadu
        scanf(" %c", &V_Pilihan);
        *V_Dadu1 = rand()% 6 + 1;
        *V_Dadu2 = rand()% 6 + 1;
        //(*V_Pemain).T[V_GiliranX].Urutan=((*V_Pemain).T[V_GiliranX].Urutan+*tdadu)%20;
    }
    tdadu=*V_Dadu1+*V_Dadu2;
    //menampilkan dadu
    printf("Dadu 1 : %d\n", *V_Dadu1);
    printf("Dadu 2 : %d\n", *V_Dadu2);
    printf("%s maju sebanyak %d langkah\n", V_TabPemain.T[V_GiliranX].Nama, tdadu);
    printf("tekan untuk melanjutkan\n");
    if(!*V_IsSudahKocok){
        scanf(" %c",&V_Pilihan);
        *V_IsSudahKocok=true;
    }
}

void P_StatusPemain(T_TabPemain V_TabPemain) //menampilkan status T_Pemain
{
    //kamus
    int i;
    //algoritma
    printf("**** STATUS PEMAIN ****\n");
    for(i=1;i<=4;i++)
    {
        if((strcmp("",V_TabPemain.T[i].Nama)!=0)&&(!V_TabPemain.T[i].Kalah))
        {
            P_SetColor(i); //memberi warna sesuai T_Pemainnya
            printf("-----%s-----\n", V_TabPemain.T[i].Nama);
            printf("Jumlah Uang : Rp %d\n", V_TabPemain.T[i].Uang);
            printf("Jumlah Aset : Rp %d\n", V_TabPemain.T[i].Aset);
        }
        P_SetColor(7); //mengembalikan ke warna dasar
    }
}

/* *** FUNGSI-FUNGSI LAIN *** */
void P_SetColor(int ForgC)
{
     WORD wColor;
                          //We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO cV_Koordinati;

                           //We use cV_Koordinati for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &cV_Koordinati))
     {
                     //Mask out all but the background attribute, and add in the forgournd color
          wColor = (cV_Koordinati.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void P_Delay(unsigned int mseconds)
{

    clock_t goal = mseconds + clock();

    while (goal > clock());

}






/* *** INISIALISASI *** */
/* ** PENGESETAN PADA PAPAN MONOPOLY ** */
void P_SetBoard( T_TabTempat *V_TabTempat, T_TabPemain *V_TabPemain) //menset board papan monopoly kosong hanya ada Nama
{
    int i, j;
    T_Point V_Koordinat;

    //tampilan board
    //ukuran board 6x6
    for(i=1;i<=6;i++)
    {
        for(j=1;j<=6;j++)
        {
            if((i==1)||(i==6)||(j==1)||(j==6))//board tuh kan tengahnya bolong jadi cuma sisinya aja 1 dan 6
            {
                V_Koordinat.x=j;
                V_Koordinat.y=i;
                P_Kotak(V_Koordinat, (*V_TabTempat), (*V_TabPemain));//memanggil satu P_Kotak satu P_Kotak
            }
        }
    }
    //P_SetStatusPemain(&m, &(*V_Pemain));
}
void P_Kotak(T_Point V_Koordinat, T_TabTempat V_TabTempat, T_TabPemain V_TabPemain)//untuk satu P_Kotak yang besar
{
    int i, j;

    for(i=1;i<=6;i++)//baris P_Kotak ada enam biji
    {
        for(j=1;j<=12;j++)//kolomnya
        {
            if((i==1)||(i==6))//untuk garis atas sama bawah P_Kotak(sisi2nya)
            {
                V_BoardPixels.T[i+(6*(V_Koordinat.y-1))][j+(12*(V_Koordinat.x-1))]='-';
            }
            else if ((j==1)||(j==12))//untuk sisi kanan kiri
            {
                V_BoardPixels.T[i+(6*(V_Koordinat.y-1))][j+(12*(V_Koordinat.x-1))]='|';
            }
            else if(i==2)//baris kedua P_Kotak diisi Nama V_TabTempat
            {
                if((j-2)<=(strlen(V_TabTempat.T[F_KoordinatToUrutan(V_Koordinat)].Nama)-1))
                V_BoardPixels.T[i+(6*(V_Koordinat.y-1))][j+(12*(V_Koordinat.x-1))]=V_TabTempat.T[F_KoordinatToUrutan(V_Koordinat)].Nama[j-2];
            }
            if (((i==1)||(i==6))&&((j==1)||(j==12)))//untuk pojok2 P_Kotak diisi +
            {
                V_BoardPixels.T[i+(6*(V_Koordinat.y-1))][j+(12*(V_Koordinat.x-1))]='+';
            }
        }
    }
}

void P_InsertJumlahPemain(T_TabPemain *V_TabPemain, T_Giliran *V_Giliran)
{
    int i;
    do{
        printf("Jumlah Pemain : ");
        scanf("%d", &(*V_TabPemain).JmlPemain);
        if(((*V_TabPemain).JmlPemain < 2)||((*V_TabPemain).JmlPemain > 4)){
            printf("Masukan jumlah pemain harus diantara 2~4\n");
        }
    }while(((*V_TabPemain).JmlPemain < 2)||((*V_TabPemain).JmlPemain > 4));
    P_CreateEmpty(&(*V_Giliran), (*V_TabPemain).JmlPemain);
    for(i=1;i<=(*V_TabPemain).JmlPemain;i++)
    {
        printf("Nama Pemain %d : ", i);
        scanf("%s", &(*V_TabPemain).T[i].Nama);
        P_Add(&(*V_Giliran), i);
    }
}

void P_InisiasiPemain(T_TabPemain *V_TabPemain)
{
    int i;
    //T_Pemain saat awal
    for (i=1;i<=4;i++)
    {
        (*V_TabPemain).T[i].Letak.y=6;
        (*V_TabPemain).T[i].Letak.x=6;
        (*V_TabPemain).T[i].Urutan=0;
        strcpy((*V_TabPemain).T[i].Nama, "");
        (*V_TabPemain).T[i].Aset=10000000;
        (*V_TabPemain).T[i].Uang=10000000;
        (*V_TabPemain).T[2].Aset=1000000;
        (*V_TabPemain).T[2].Uang=1000000;
        (*V_TabPemain).LamaPenjara[i]=0;
        (*V_TabPemain).T[i].Kalah=false;
    }
}

void P_IsiLogo(T_TabPemain *V_TabPemain)
{
    int i;
    T_Point V_Koordinat;
    (*V_TabPemain).T[1].Logo='1';
    (*V_TabPemain).T[2].Logo='2';
    (*V_TabPemain).T[3].Logo='3';
    (*V_TabPemain).T[4].Logo='4';
    //mengisi Logo kosong jika tidak di mainkan
    i=(*V_TabPemain).JmlPemain+1;
    while(i<=4)
    {
        (*V_TabPemain).T[i].Logo=' ';
        i++;
    }
    i=1;
    while( (i<=4) && !(F_IsPemainEmpty((*V_TabPemain).T[i])) )
    {
        P_UrutanToPixel((*V_TabPemain).T[i].Urutan, 4, (1+(2*i)), &V_Koordinat);
        V_BoardPixels.T[V_Koordinat.y][V_Koordinat.x]=(*V_TabPemain).T[i].Logo;
        i++;
    }
}

void P_BlankAll()
{
    int i,j;

    for(i=0;i<=C_IMax-1;i++)
    {
        for(j=0;j<=C_JMax-1;j++)
        {
            V_BoardPixels.T[i][j]=' ';
        }
    }
}
void P_Inisiasi(T_TabTempat *V_TabTempat, T_TabPemain *V_TabPemain)
{
    int i;
    for(i=0;i<=19;i++)
    {
        strcpy((*V_TabTempat).T[i].Nama,"");
        (*V_TabTempat).T[i].HargaBeli=0;
        (*V_TabTempat).T[i].Kompleks='0';
        (*V_TabTempat).T[i].Pemilik=0;
    }
    strcpy((*V_TabTempat).T[0].Nama, "START");
    strcpy((*V_TabTempat).T[1].Nama, "OKTAGON");
    (*V_TabTempat).T[1].HargaBeli=500000;
    (*V_TabTempat).T[1].Kompleks='1';
    strcpy((*V_TabTempat).T[2].Nama, "COMLABS");
    (*V_TabTempat).T[2].HargaBeli=750000;
    (*V_TabTempat).T[2].Kompleks='1';
    strcpy((*V_TabTempat).T[3].Nama, "TVST");
    (*V_TabTempat).T[3].HargaBeli=1200000;
    (*V_TabTempat).T[3].Kompleks='2';
    strcpy((*V_TabTempat).T[4].Nama, "TELKOM");
    (*V_TabTempat).T[4].HargaBeli=1500000;
    (*V_TabTempat).T[4].Kompleks='2';
    strcpy((*V_TabTempat).T[5].Nama, "PENJARA");
    strcpy((*V_TabTempat).T[6].Nama, "K_BENGKOK");
    (*V_TabTempat).T[6].HargaBeli=3500000;
    (*V_TabTempat).T[6].Kompleks='K';
    strcpy((*V_TabTempat).T[7].Nama, "KESEMPATAN");
    strcpy((*V_TabTempat).T[8].Nama, "GKU_BARAT");
    (*V_TabTempat).T[8].HargaBeli=1900000;
    (*V_TabTempat).T[8].Kompleks='3';
    strcpy((*V_TabTempat).T[9].Nama, "GKU_TIMUR");
    (*V_TabTempat).T[9].HargaBeli=2300000;
    (*V_TabTempat).T[9].Kompleks='3';
    strcpy((*V_TabTempat).T[10].Nama, "UNDIAN");
    strcpy((*V_TabTempat).T[11].Nama, "AULA_BARAT");
    (*V_TabTempat).T[11].HargaBeli=2700000;
    (*V_TabTempat).T[11].Kompleks='4';
    strcpy((*V_TabTempat).T[12].Nama, "AULA_TIMUR");
    (*V_TabTempat).T[12].HargaBeli=3100000;
    (*V_TabTempat).T[12].Kompleks='4';
    strcpy((*V_TabTempat).T[13].Nama, "KESEMPATAN");
    strcpy((*V_TabTempat).T[14].Nama, "K_BARRACK");
    (*V_TabTempat).T[14].HargaBeli=3500000;
    (*V_TabTempat).T[14].Kompleks='K';
    strcpy((*V_TabTempat).T[15].Nama, "BUS_ITB");
    strcpy((*V_TabTempat).T[16].Nama, "KESEMPATAN");
    strcpy((*V_TabTempat).T[17].Nama, "K_BORJU");
    (*V_TabTempat).T[17].HargaBeli=3500000;
    (*V_TabTempat).T[17].Kompleks='K';
    strcpy((*V_TabTempat).T[18].Nama, "LABTEK_VIII");
    (*V_TabTempat).T[18].HargaBeli=3500000;
    (*V_TabTempat).T[18].Kompleks='6';
    strcpy((*V_TabTempat).T[19].Nama, "LABTEK_V");
    (*V_TabTempat).T[19].HargaBeli=4000000;
    (*V_TabTempat).T[19].Kompleks='6';
    for(i=0;i<=19;i++)
    {
        (*V_TabTempat).T[i].Letak=F_UrutanToKoordinat(i);
    }
    P_InisiasiPemain(&(*V_TabPemain));
    P_BlankAll();
}




/* *** FUNGSI-FUNGSI BUAT V_GiliranUEUE *** */
/* *** Predikat Pemeriksaan Kondisi T_Giliran *** */
boolean F_IsEmpty (T_Giliran V_Giliran)/*Mengirim true jika V_Giliran kosong */
{
    return ((F_Head(V_Giliran)==C_Nil)&&(F_Tail(V_Giliran)==C_Nil));
}


/* *** Konstruktor *** */
void P_CreateEmpty (T_Giliran *V_Giliran, int V_Max)
/* I.S. Max terdefinisi */
/* F.S. Sebuah V_Giliran kosong terbentuk dan salah satu kondisi V_Koordinatb :       */
/*      Jika aUrutan berhasil, tabel memori diaUrutan berukuran Max  */
/*      atau : jika aUrutan gagal, V_Giliran kosong dg Maksimum elemen=0     */
/* Proses : Melakukan aUrutan memori dan membuat sebuah V_Giliran kosong     */
{
    (*V_Giliran).T = (T_Info *) malloc((V_Max+1)*sizeof(T_Info));
    if ((*V_Giliran).T != C_Nil)
    {
        F_MaxEl(*V_Giliran) = V_Max;
        F_Head(*V_Giliran) = C_Nil;
        F_Tail(*V_Giliran) = C_Nil;
    }
    else /* aUrutan gagal */
    {
        F_MaxEl(*V_Giliran)=C_Nil;
    }
}

/* *** Destruktor *** */
void P_DeAlokasi (T_Giliran *V_Giliran)
/* Proses : Mengembalikan memori V_Giliran */
/* I.S. V_Giliran pernah diaUrutan */
/* F.S. V_Giliran menjadi tidak terdefinisi lagi, MaxEl(V_Giliran) diset 0 */
{
    F_MaxEl(*V_Giliran) = C_Nil;
    free((*V_Giliran).T);
}

/* *** Operator-Operator Dasar T_Giliran *** */
void P_Add (T_Giliran *V_Giliran, T_Info V_Info)
/* Proses : Menambahkan  X pada V_Giliran dengan aturan FIFO */
/* I.S. V_Giliran mungkin kosong, tabel penampung elemen V_Giliran TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" */
{
    if(F_IsEmpty(*V_Giliran))
    {
        F_Head(*V_Giliran)=1;
    }
    F_Tail(*V_Giliran)++;
    F_InfoTail(*V_Giliran)=V_Info;
}
void P_Del (T_Giliran *V_Giliran, T_Info *V_Info)
/* Proses: Menghapus elemen pertama pada V_Giliran dengan aturan FIFO */
/* I.S. V_Giliran tidak kosong */
/* F.S. X = nilai elemen HEAD pada I.S.,
       Jika T_Giliran masih isi : HEAD diset tetap = 1, elemen-elemen setelah HEAD yang
       lama digeser ke "kiri", TAIL = TAIL – 1;        Jika T_Giliran menjadi kosong, HEAD = TAIL = C_Nil. */
{
    //kamus
    int i;
    //algoritma
    (*V_Info)=F_InfoHead(*V_Giliran);
    if (F_Head(*V_Giliran)==F_Tail(*V_Giliran))
    {
        F_Head(*V_Giliran) = C_Nil;
        F_Tail(*V_Giliran) = C_Nil;
    }
    else
    {
        i=F_Head(*V_Giliran);
        do
        {
            (*V_Giliran).T[i]=(*V_Giliran).T[i+1];
            i++;
        }while(i!=F_Tail(*V_Giliran));
        F_Tail(*V_Giliran)--;
    }
}
void P_ChangeTurn(T_Giliran *V_Giliran)
{
    //kamus
    T_Info X;
    //algoritma
    P_Del(&(*V_Giliran), &X);
    P_Add(&(*V_Giliran), X);
}





boolean F_IsPemainEmpty(T_Pemain V_Pemain)//mengecek apakah T_Pemain ada atau tidak
{
    return (strcmp(V_Pemain.Nama, "")==0);
}
