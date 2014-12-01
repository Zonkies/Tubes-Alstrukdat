#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "boolean.h"

#ifndef MONOPOLY_H_INCLUDED
#define MONOPOLY_H_INCLUDED

#define imax 40 //baris maksimum pada matriks
#define jmax 74 //kolom maksimum pada matriks
#define ukiri 1 //ujung kiri board
#define ukanan 72 //ujung kanan board
#define uatas 1 //ujung atas board
#define ubawah 36 //ujung bawah board
#define mark -999

typedef struct
{
    int x; //absis
    int y; //ordinat
}point;

typedef struct
{
    char t[imax+1][jmax+1];
}matriks;

typedef struct
{
    char name[15];
    int urutan;
    int hargabeli;
    char kompleks;
    int pemilik;
    point letak;
}tempt;

typedef struct
{
    tempt tmpt[20];
}place;

typedef struct
{
    char nama[10];
    char logo;
    int uang;
    int aset;
    point letak;
    int lokasi;
}pemain;

typedef struct
{
    pemain pem[5];
    int jmlpemain;
}player;

extern matriks m;

/* Modul ADT Queue – Alternatif I */
/* *** Deklarasi Queue yang diimplementasi dengan tabel kontigu *** */
/* *** HEAD dan TAIL adalah alamat elemen pertama dan terakhir  *** */
/* *** Queue mampu menampung MaxEl buah elemen *** */

/* *** Konstanta *** */
#define Nil 0

/* *** Akses (selektor) *** */
#define Head(Q) (Q).HEAD
#define Tail(Q) (Q).TAIL
#define InfoHead(Q) (Q).T[(Q).HEAD]
#define InfoTail(Q) (Q).T[(Q).TAIL]
#define MaxEl(Q) (Q).MaxEl



/* *** Definisi elemen dan address *** */
typedef int infotype;
typedef int address; /* indeks tabel */
/* *** Definisi Type Queue *** */
typedef struct
{
    infotype *T; /* tabel penyimpan elemen, tergantung bahasa */
    address HEAD; /* alamat penghapusan */
    address TAIL; /* alamat penambahan  */
    int MaxEl; /* maksimum banyaknya elemen queue */
} Queue;
/* Definisi Queue kosong: Head = Nil; TAIL = Nil. */ /* Catatan implementasi: T[0] tidak pernah dipakai */
/* Definisi akses dengan Selektor : Isilah dengan selektor yang tepat */
/* *** Predikat Pemeriksaan Kondisi Queue *** */
boolean IsEmpty (Queue Q);/*Mengirim true jika Q kosong */
boolean IsFull (Queue Q);
/* Mengirim true jika tabel penampung elemen Q sudah penuh yaitu mengandung MaxEl elemen */
int NBElmt (Queue Q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
/* *** Konstruktor *** */
void CreateEmpty (Queue *Q, int Max);
/* I.S. Max terdefinisi */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb :       */
/*      Jika alokasi berhasil, tabel memori dialokasi berukuran Max  */
/*      atau : jika alokasi gagal, Q kosong dg Maksimum elemen=0     */ /* Proses : Melakukan alokasi memori dan membuat sebuah Q kosong     */
/* *** Destruktor *** */
void DeAlokasi (Queue *Q);
/* Proses : Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */
/* *** Operator-Operator Dasar Queue *** */
void Add (Queue *Q, infotype X);
/* Proses : Menambahkan  X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" */
void Del (Queue *Q, infotype *X); /* Proses: Menghapus elemen pertama pada Q dengan aturan FIFO */
/* I.S. Q tidak kosong */
/* F.S. X = nilai elemen HEAD pada I.S.,
       Jika Queue masih isi : HEAD diset tetap = 1, elemen-elemen setelah HEAD yang         lama digeser ke "kiri", TAIL = TAIL – 1;        Jika Queue menjadi kosong, HEAD = TAIL = Nil. */




boolean isgedung(tempt tmpt);
boolean ispointsama(point p1, point p2);

void insertjumlahpemain(player *p, Queue *Q);
void printgame( place tempat, player p);

int bariskotak(int i);
int kolomkotak(int j);

void delay(unsigned int mseconds);

void majuselangkah(pemain *p, int giliran);


void kotak(point sb,  place tempat, player p);

void setboard( place *tempat, player *p);

void inisialisasi(place *tempat, player *p );
void inisiasipemain(player *p);
void isilogo(player *p);
void blankall();

void setstatus(place *tempat, player *p);
void setstatuspemain (player *p);

point urutantopoint(int urutan);
int pointtourutan(point sb);
boolean ispemainempty(pemain pe);
void statuspemain(player play);
void turn(player p, int *dadu1, int *dadu2, boolean *issudahkocok, int i);
void SetColor(int ForgC);
void lokasitokoordinat (int lokasi, int baris, int kolom, point *sb);
void ChangeTurn(Queue *Q);
#endif // MONOPOLY_H_INCLUDED
