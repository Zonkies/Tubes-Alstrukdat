/* No Kelompok : 05 */
/* Nama file : game_05.h */
/* Deskripsi : Header */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "boolean.h"

#define Nmax 100
#define MaxFileName 50
#define MaxName 10

/* KAMUS GLOBAL */
FILE *Daftar_Pemain;
FILE *High_Score;

typedef char T_Nama[MaxName];
typedef struct{
	T_Nama T;
} infotype;
typedef struct{
	int Score;
	T_Nama Nama;
} T_HighScore;
typedef struct{
	T_HighScore T[10];
	int NEff;
} T_TabHighScore;

#include "boolean.h"
#define Nil NULL

typedef struct to *address;
typedef struct to{
	infotype Info;
	address Next;
} ElmtList;
typedef struct{
	address First;
} List;

/* Selektor */
#define Info(P) (P)->Info
#define Next(P) (P)->Next
#define First(L) ((L).First)

boolean IsListEmpty(List L);
void CreateList(List *L);
address Alokasi(infotype X);
void Dealokasi(address *P);
address Search(List L, infotype X);
boolean FSearch(List L, address P);
void InsertLast(List *L, address P);
void PrintInfo(List L);

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
    boolean Menang;
}T_Pemain;

typedef struct
{
    T_Pemain T[5];
    int JmlPemain;
    int LamaPenjara[5];
}T_TabPemain;

T_BoardPixels V_BoardPixels;

/* Modul ADT Queue – Alternatif I */
/* *** Deklarasi Queue yang diimplementasi dengan tabel kontigu *** */
/* *** HEAD dan TAIL adalah alamat elemen pertama dan terakhir  *** */
/* *** Queue mampu menampung MaxEl buah elemen *** */

/* *** Konstanta *** */
#define C_Nil 0

/* *** Akses (selektor) *** */
#define F_Head(V_Giliran) (V_Giliran).HEAD
#define F_Tail(V_Giliran) (V_Giliran).TAIL
#define F_InfoHead(V_Giliran) (V_Giliran).T[(V_Giliran).HEAD]
#define F_InfoTail(V_Giliran) (V_Giliran).T[(V_Giliran).TAIL]
#define F_MaxEl(V_Giliran) (V_Giliran).MaxEl

/* *** Definisi elemen dan Adress *** */
typedef int T_Info;
typedef int T_Address; // indeks tabel

/* *** Definisi Type Queue *** */
typedef struct
{
    T_Info *T; /* tabel penyimpan elemen, tergantung bahasa */
    T_Address HEAD; /* alamat penghapusan */
    T_Address TAIL; /* alamat penambahan  */
    int MaxEl; /* maksimum banyaknya elemen queue */
} T_Giliran;
/* Definisi T_Giliran kosong: Head = C_Nil; TAIL = C_Nil. */
/* Catatan implementasi: T[0] tidak pernah dipakai */
/* Definisi akses dengan Selektor : Isilah dengan selektor yang tepat */

/* *** Predikat Pemeriksaan Kondisi T_Giliran *** */
boolean F_IsEmpty (T_Giliran V_Giliran);/*Mengirim true jika V_Giliran kosong */

/* *** Konstruktor *** */
void P_CreateEmpty (T_Giliran *V_Giliran, int V_Max);
/* I.S. Max terdefinisi */
/* F.S. Sebuah V_Giliran kosong terbentuk dan salah satu kondisi V_Koordinatb :       */
/*      Jika aUrutan berhasil, tabel memori diaUrutan berukuran Max  */
/*      atau : jika aUrutan gagal, V_Giliran kosong dg Maksimum elemen=0     */
/* Proses : Melakukan aUrutan memori dan membuat sebuah V_Giliran kosong     */

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

void P_Del (T_Giliran *V_Giliran, T_Info *V_Info); 
/* Proses: Menghapus elemen pertama pada V_Giliran dengan aturan FIFO */
/* I.S. V_Giliran tidak kosong */
/* F.S. X = nilai elemen HEAD pada I.S.,
Jika T_Giliran masih isi : HEAD diset tetap = 1,
elemen-elemen setelah HEAD yang lama digeser ke "kiri", TAIL = TAIL – 1;
Jika T_Giliran menjadi kosong, HEAD = TAIL = C_Nil. */


/*********************/
/*     ADT GAME      */
/*********************/
/* Mengimplementasikan semua ADT yang pernah dipelajari*/

/*** FUNGSI INISIASI GAME ***/

void P_SetBoard(T_TabTempat *V_TabTempat, T_TabPemain *V_TabPemain);
/* Menghasilkan Board kosong yang hanya memiliki nama Gedung / Keterangan lainnya */
void P_Inisiasi(T_TabTempat *V_TabTempat, T_TabPemain *V_TabPemain );
/* Prosedur yang mengeset semua inisiasi board di game */
/* Semua Kotak Board masih Kosong tidak memiliki pemilik */
void P_InisiasiPemain(T_TabPemain *V_TabPemain);
/* Prosedur yang mengeset semua inisiasi pemain */
/* Pemain memulai uang dengan uang 1000000 */
void P_IsiLogo(T_TabPemain *V_TabPemain);
/* Prosedur untuk mengeset bentuk Avatar Pemain */


/*****************************/

/*** FUNGSI TERKAIT BOARD ***/

boolean F_IsPointSama(T_Point P1, T_Point P2);
/* Mengembalikan true jika kordinat P1 = kordinat P2 */
void P_PrintGame(T_TabTempat V_TabTempat, T_TabPemain V_TabPemain);
/* Prosedur untuk menampilkan Board Game pada layar */
void P_SetColor(int ForgC);
/* Untuk membantu mengubah warna dari board */
void P_Kotak(T_Point V_Point, T_TabTempat V_TabTempat, T_TabPemain V_TabPemain);
/* Membuat pola board secara besar */
void P_BlankAll();
/* Membuat Board menjadi kosong */
int F_GetOrdinatKotak(int i);
/* Merubah baris pada T_Pixels(1..72, 1..36) ke P_Kotak yang besar (1..6, 1..6) */
int F_GetAbsisKotak(int j);
/* Merubah kolom pada T_Pixels(1..72, 1..36) ke P_Kotak yang besar (1..6, 1..6) */
void P_UrutanToPixel (int V_UrutanGedung, int V_Baris, int V_Kolom, T_Point *V_Pixel);
/* Mengubah Urutan (0 sampai 19) jadi koordinat(1..72, 1..36) */
T_Point F_UrutanToKoordinat(int V_UrutanGedung);
/* Mengubah urutan (0..19) menjadi T_Point dalam P_Kotak (1..6) */
int F_KoordinatToUrutan(T_Point V_Koordinat);
/* Mengubah T_Point P_Kotak besar(1..6, 1..6) menjadi Urutan(0..19) */
void P_Delay(unsigned int mseconds);
/* Prosedur Delay agar P_PrintGame tidak terjadi secara tiba-tiba
User bisa membaca dahulu hasil permainannya */

/*****************************/

/*** Fungsi terkait Permainan ***/

boolean F_IsGedung(T_Tempat V_Tempat);
/* Mengembalikan true jika posisi pemain berada diatas kotak Gedung */
void P_InsertJumlahPemain(T_TabPemain *V_TabPemain, T_Giliran *V_Giliran);
/* Prosedur untuk memasukan berapa banyak jumlah pemain */
/* Akan memvalidasi jika jumlah pemain belum minimal 2*/
boolean F_IsPemainEmpty(T_Pemain V_Pemain);
/* Mengembalikan true jika Nama Pemain tidak ada */
void P_MajuSelangkah(T_Pemain *V_Pemain, int V_GiliranX);
/* Prosedur agar Pion-pion pemain dapat terlihat maju selangkah demi selangkah */
void P_ChangeTurn(T_Giliran *V_Giliran);
/* Prosedur untuk membuat pemain selanjutnya bermain */
/* Pemain yang sudah bermain akan mundur kebelakang */
void P_Turn(T_TabPemain V_TabPemain, int *V_Dadu1, int *V_Dadu2, boolean *V_IsSudahKocok, int i, int V_GiliranX);
/* Menampilkan pemain berada pada putaran berapa */
void P_SetStatus(T_TabTempat *V_TabTempat, T_TabPemain *V_TabPemain);
void P_SetStatusPemain (T_TabPemain *V_TabPemain);
void P_StatusPemain(T_TabPemain V_TabPemain);
/* Menampilkan Status Pemain */
/* Status berupa Uang dan Aset */
void P_MasukPenjara(T_TabPemain *V_TabPemain, int V_GiliranX);
void P_IsAdaGedung(T_TabTempat V_TabTempat, char V_TempatTujuan[15], int *V_Urutan, boolean *V_IsAdaGedung);P

/*****************************/
