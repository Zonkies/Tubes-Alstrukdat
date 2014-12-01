#include "monopoly.h"

matriks m;


/* *** FUNGSI PENGECEKAN *** */
boolean isgedung(tempt tmpt) //cek apakah gedung atau bukan
{
    return (tmpt.kompleks!='0'); //kalo bukan komplek '0' berarti gedung
}

boolean ispointsama(point p1, point p2)
{
    //mencek apakah point 1 dan 2 sama
    return ((p1.x==p2.x)&&(p1.y==p2.y));
}

/* *** MENGGERAKAN PEMAIN *** */
void majuselangkah(pemain *p, int giliran)
{
    int i, j, urut, kolomorang;
    point sb;

    lokasitokoordinat((*p).lokasi, 4, (1+(2*giliran)), &sb); //menyimpan koordinat dari logo pemain
    m.t[sb.y][sb.x]=' '; //koordinat yang sebelumnya didapat, di replace menjadi ' ' (kosong)
    (*p).lokasi=((*p).lokasi+1)%20; //lokasi nya maju satu, tapi harus di mod 20, karena lokasi cuma dari 0 sampe 19
    lokasitokoordinat((*p).lokasi, 4, (1+(2*giliran)), &sb); //ambil sb sebagai koordinat baru logo nya
    m.t[sb.y][sb.x]=(*p).logo;//isi koordinat baru tersebut dengan logo nya
}

/* *** PRINT KE LAYAR *** */
void printgame(place tempat, player p)
{
    //print kelayar
    //kamus
    int i, j, urut, kolomorang;
    point sb, smb;
    point sumbu[5];
    //algoritma
    for(i=1;i<=4;i++)//untuk setiap orang, posisi logo nya berada pada kolom kolomorang, dan baris 4 (untuk di kotak besar)
    {
        kolomorang=1+(2*i);
        lokasitokoordinat(p.pem[i].lokasi, 4, kolomorang, &sb); //merubah lokasi nya menjadi koordinat kotak kecil/ koordinat matriks (1..72, 1..36)
        sumbu[i]=sb;
    }

    system("cls"); //clear screen
    for(i=uatas;i<=(imax-1);i++)
    {
        for(j=ukiri;j<=(jmax-1);j++)
        {
            smb.x=j; //ubah j ke point
            smb.y=i; //i di masukan ke point
            sb.y=bariskotak(i); //sb dalam kotk besar nya
            sb.x=kolomkotak(j); //sb dalam kotak besar nya
            urut=pointtourutan(sb); //merubah ke urutan(0..19)
            if (urut!=mark) //kalo antara 0..19
            {
                if((ispointsama(smb, sumbu[1]))||(ispointsama(smb, sumbu[4]))||(ispointsama(smb, sumbu[2]))||(ispointsama(smb, sumbu[3])))
                    //melakukan pengecekan apakah yang akan di print merupakan logo, karena jika logo warnanya harus sesuai.
                {
                    if(ispointsama(smb, sumbu[1]))
                    {
                        SetColor(1);
                        printf("%c", m.t[i][j]);
                    }
                    else if (ispointsama(smb, sumbu[2]))
                    {
                        SetColor(2);
                        printf("%c", m.t[i][j]);
                    }
                    else if (ispointsama(smb, sumbu[3]))
                    {
                        SetColor(3);
                        printf("%c", m.t[i][j]);
                    }
                    else if (ispointsama(smb, sumbu[4]))
                    {
                        SetColor(4);
                        printf("%c", m.t[i][j]);
                    }
                }
                else
                {
                    //mengeprint warna setiap kotak sesuai pemiliknya
                    if (tempat.tmpt[urut].pemilik==1) //jika pemiliknya si 1
                    {
                        SetColor(1);
                        printf("%c", m.t[i][j]);
                    }
                    else if (tempat.tmpt[urut].pemilik==2) //jika pemiliknya si 2
                    {
                        SetColor(2);
                        printf("%c", m.t[i][j]);
                    }
                    else if (tempat.tmpt[urut].pemilik==3) //jika pemiliknya si 3
                    {
                        SetColor(3);
                        printf("%c", m.t[i][j]);
                    }
                    else if (tempat.tmpt[urut].pemilik==4) //jika pemiliknya si 4
                    {
                        SetColor(4);
                        printf("%c", m.t[i][j]);
                    }
                    else
                    {
                        SetColor(7);
                        printf("%c", m.t[i][j]);
                    }
                }
            }
            else
            {
                SetColor(7);
                printf("%c", m.t[i][j]);
            }
        }
        SetColor(7);
        printf("\n");
    }
}


/* *** FUNGSI CONVERT ****/
void lokasitokoordinat (int lokasi, int baris, int kolom, point *sb)
{
    //merubah lokasi (0 sampai 19) jadi koordinat(1..72, 1..36)
    point sbbesar;//sumbu dalam kotak besar
    sbbesar=urutantopoint(lokasi);//merubah urutan/lokasi menjadi sumbu dalam kotak besar
    (*sb).x=kolom+(12*(sbbesar.x-1));
    (*sb).y=baris+(6*(sbbesar.y-1));
}

int pointtourutan(point sb) //merubah point kotak besar(1..6, 1..6) menjadi urutan(0..19)
{
    if((sb.y==6)||(sb.x==1))
    {
        return (6-sb.y)+(6-sb.x);
    }
    else if ((sb.x==6)||(sb.y==1))
    {
        return 20-((6-sb.y)+(6-sb.x));
    }
    else
    {
        return mark;
    }
}
int bariskotak(int i) //merubah baris pada matriks(1..72, 1..36) ke kotak yang besar (1..6, 1..6)
{
    int barmin, hasil; //baris paling atas(1), hasil baris nya

    hasil=1;
    barmin=1;

    do{
        if((i>=barmin)&&(i<=(barmin+5)))
        {
            return hasil;
        }
        barmin=barmin+6;//tambah 6 baris, berarti kalo di kotak besar setara dengan nambah satu baris
        hasil++;
    }while(i<=ubawah);
    return 0;
}

int kolomkotak(int j) //merubah kolom pada matriks(1..72, 1..36) ke kotak yang besar (1..6, 1..6)
{
    int kolmin, hasil; //kolom paling atas(1), hasil kolom nya

    hasil=1;
    kolmin=1;
    do{
        if((j>=kolmin)&&(j<=(kolmin+11)))
        {
            return hasil;
        }
        kolmin=kolmin+12;//tambah 12 kolom, berarti kalo di kotak besar setara dengan nambah satu kolom
        hasil++;
    }while(j<=ukanan);//kalo belum sampe ujung board
    return 0;
}

point urutantopoint(int urutan) //mengubah urutan(0..19) menjadi point dalam kotak besar (1..6, 1..6)
{
    point p;

    if((urutan>=0)&&(urutan<=5))
    {
        p.x=6-urutan;
        p.y=6;
    }
    else if((urutan>=5)&&(urutan<=10))
    {
        p.x=1;
        p.y=1+(10-urutan);
    }
    else if ((urutan>=10)&&(urutan<=15))
    {
        p.x=urutan-9;
        p.y=1;
    }
    else if ((urutan>=15)&&(urutan<=20))
    {
        p.y=urutan-14;
        p.x=6;
    }
    else
    {
        p.x=mark;
        p.y=mark;
    }
    return p;
}



/* *** MENAMPILKAN KETERANGAN TENTANG PEMAIN *** */
void turn(player p, int *dadu1, int *dadu2, boolean *issudahkocok, int i)//pemainnya, nilai dadu1, nilai dadu2, udah pernah ngocok belum
{   //melakukan turn, seperti mengocok dadu
    //kamus
    int giliran, tdadu; //giliran siapa sekarang(orang), total dadu(dadu1 + dadu2)
    char pilihan;
    //algoritma
    printf("-----Turn %d-----\n", i);
    giliran=((i-1)%p.jmlpemain)+1; //mencari giliran siapa
    printf("Giliran : %s\n", p.pem[giliran].nama);
    printf("tekan untuk mengocok dadu!");
    if(!(*issudahkocok)) //jika belum ngocok
    {   // melakukan pengocokan dadu
        scanf(" %c", &pilihan);
        *dadu1 = rand()% 6 + 1;
        *dadu2 = rand()% 6 + 1;
        //(*p).pem[giliran].lokasi=((*p).pem[giliran].lokasi+*tdadu)%20;
        *issudahkocok=true;
    }
    tdadu=*dadu1+*dadu2;
    //menampilkan dadu
    printf("\nDadu 1 : %d\n", *dadu1);
    printf("Dadu 2 : %d\n", *dadu2);
    printf("%s maju sebanyak %d langkah\n", p.pem[giliran].nama, tdadu);
}

void statuspemain(player play) //menampilkan status pemain
{
    //kamus
    int i;
    //algoritma
    printf("**** STATUS PEMAIN ****\n");
    for(i=1;i<=4;i++)
    {
        if(strcmp("",play.pem[i].nama)!=0)
        {
            SetColor(i); //memberi warna sesuai pemainnya
            printf("-----%s-----\n", play.pem[i].nama);
            printf("Jumlah Uang : Rp %d\n", play.pem[i].uang);
            printf("Jumlah Aset : Rp %d\n", play.pem[i].aset);
        }
        SetColor(7); //mengembalikan ke warna dasar
    }
}

/* *** FUNGSI-FUNGSI LAIN *** */
void SetColor(int ForgC)
{
     WORD wColor;
                          //We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

                           //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
                     //Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void delay(unsigned int mseconds)
{

    clock_t goal = mseconds + clock();

    while (goal > clock());

}






/* *** INISIALISASI *** */
/* ** PENGESETAN PADA PAPAN MONOPOLY ** */
void setboard( place *tempat, player *p) //menset board papan monopoly kosong hanya ada nama
{
    int i, j;
    point sb;

    //tampilan board
    //ukuran board 6x6
    for(i=1;i<=6;i++)
    {
        for(j=1;j<=6;j++)
        {
            if((i==1)||(i==6)||(j==1)||(j==6))//board tuh kan tengahnya bolong jadi cuma sisinya aja 1 dan 6
            {
                sb.x=j;
                sb.y=i;
                kotak(sb, (*tempat), (*p));//memanggil satu kotak satu kotak
            }
        }
    }
    //setstatuspemain(&m, &(*p));
}
void kotak(point sb, place tempat, player p)//untuk satu kotak yang besar
{
    int i, j;

    for(i=1;i<=6;i++)//baris kotak ada enam biji
    {
        for(j=1;j<=12;j++)//kolomnya
        {
            if((i==1)||(i==6))//untuk garis atas sama bawah kotak(sisi2nya)
            {
                m.t[i+(6*(sb.y-1))][j+(12*(sb.x-1))]='-';
            }
            else if ((j==1)||(j==12))//untuk sisi kanan kiri
            {
                m.t[i+(6*(sb.y-1))][j+(12*(sb.x-1))]='|';
            }
            else if(i==2)//baris kedua kotak diisi nama tempat
            {
                if((j-2)<=(strlen(tempat.tmpt[pointtourutan(sb)].name)-1))
                m.t[i+(6*(sb.y-1))][j+(12*(sb.x-1))]=tempat.tmpt[pointtourutan(sb)].name[j-2];
            }
            if (((i==1)||(i==6))&&((j==1)||(j==12)))//untuk pojok2 kotak diisi +
            {
                m.t[i+(6*(sb.y-1))][j+(12*(sb.x-1))]='+';
            }
        }
    }
}

void insertjumlahpemain(player *p, Queue *Q)
{
    int i;
    printf("Jumlah pemain : ");
    scanf("%d", &(*p).jmlpemain);
    CreateEmpty(&(*Q), (*p).jmlpemain);
    for(i=1;i<=(*p).jmlpemain;i++)
    {
        printf("Nama Pemain %d : ", i);
        scanf("%s", &(*p).pem[i].nama);
        Add(&(*Q), i);
    }
}

void inisiasipemain(player *p)
{
    int i;
    //pemain saat awal
    for (i=1;i<=4;i++)
    {
        (*p).pem[i].letak.y=6;
        (*p).pem[i].letak.x=6;
        (*p).pem[i].lokasi=0;
        strcpy((*p).pem[i].nama, "");
        (*p).pem[i].aset=10000000;
        (*p).pem[i].uang=10000000;
    }
}

void isilogo(player *p)
{
    int i;
    point sb;
    (*p).pem[1].logo='1';
    (*p).pem[2].logo='2';
    (*p).pem[3].logo='3';
    (*p).pem[4].logo='4';
    //mengisi logo kosong jika tidak di mainkan
    i=(*p).jmlpemain+1;
    while(i<=4)
    {
        (*p).pem[i].logo=' ';
        i++;
    }
    i=1;
    while( (i<=4) && !(ispemainempty((*p).pem[i])) )
    {
        lokasitokoordinat((*p).pem[i].lokasi, 4, (1+(2*i)), &sb);
        m.t[sb.y][sb.x]=(*p).pem[i].logo;
        i++;
    }
}

void blankall()
{
    int i,j;

    for(i=0;i<=imax-1;i++)
    {
        for(j=0;j<=jmax-1;j++)
        {
            m.t[i][j]=' ';
        }
    }
}
void inisialisasi(place *tempat, player *p)
{
    int i;
    for(i=0;i<=19;i++)
    {
        strcpy((*tempat).tmpt[i].name,"");
        (*tempat).tmpt[i].hargabeli=0;
        (*tempat).tmpt[i].kompleks='0';
        (*tempat).tmpt[i].pemilik=0;
    }
    strcpy((*tempat).tmpt[0].name, "START");
    strcpy((*tempat).tmpt[1].name, "OKTAGON");
    (*tempat).tmpt[1].hargabeli=500000;
    (*tempat).tmpt[1].kompleks='1';
    strcpy((*tempat).tmpt[2].name, "COMLABS");
    (*tempat).tmpt[2].hargabeli=750000;
    (*tempat).tmpt[2].kompleks='1';
    strcpy((*tempat).tmpt[3].name, "TVST");
    (*tempat).tmpt[3].hargabeli=1200000;
    (*tempat).tmpt[3].kompleks='2';
    strcpy((*tempat).tmpt[4].name, "TELKOM");
    (*tempat).tmpt[4].hargabeli=1500000;
    (*tempat).tmpt[4].kompleks='2';
    strcpy((*tempat).tmpt[5].name, "PENJARA");
    strcpy((*tempat).tmpt[6].name, "K_BENGKOK");
    (*tempat).tmpt[6].hargabeli=3500000;
    (*tempat).tmpt[6].kompleks='K';
    strcpy((*tempat).tmpt[7].name, "KESEMPATAN");
    strcpy((*tempat).tmpt[8].name, "GKU_BARAT");
    (*tempat).tmpt[8].hargabeli=1900000;
    (*tempat).tmpt[8].kompleks='3';
    strcpy((*tempat).tmpt[9].name, "GKU_TIMUR");
    (*tempat).tmpt[9].hargabeli=2300000;
    (*tempat).tmpt[9].kompleks='3';
    strcpy((*tempat).tmpt[10].name, "UNDIAN");
    strcpy((*tempat).tmpt[11].name, "AULA_BARAT");
    (*tempat).tmpt[11].hargabeli=2700000;
    (*tempat).tmpt[11].kompleks='4';
    strcpy((*tempat).tmpt[12].name, "AULA_TIMUR");
    (*tempat).tmpt[12].hargabeli=3100000;
    (*tempat).tmpt[12].kompleks='4';
    strcpy((*tempat).tmpt[13].name, "KESEMPATAN");
    strcpy((*tempat).tmpt[14].name, "K_BARRACK");
    (*tempat).tmpt[14].hargabeli=3500000;
    (*tempat).tmpt[14].kompleks='K';
    strcpy((*tempat).tmpt[15].name, "BUS_ITB");
    strcpy((*tempat).tmpt[16].name, "KESEMPATAN");
    strcpy((*tempat).tmpt[17].name, "K_BORJU");
    (*tempat).tmpt[17].hargabeli=3500000;
    (*tempat).tmpt[17].kompleks='K';
    strcpy((*tempat).tmpt[18].name, "LABTEK_VIII");
    (*tempat).tmpt[18].hargabeli=3500000;
    (*tempat).tmpt[18].kompleks='6';
    strcpy((*tempat).tmpt[19].name, "LABTEK_V");
    (*tempat).tmpt[19].hargabeli=4000000;
    (*tempat).tmpt[19].kompleks='6';
    for(i=0;i<=19;i++)
    {
        (*tempat).tmpt[i].letak=urutantopoint(i);
    }
    inisiasipemain(&(*p));
    blankall(&(m));
}




/* *** FUNGSI-FUNGSI BUAT QUEUE *** */
/* *** Predikat Pemeriksaan Kondisi Queue *** */
boolean IsEmpty (Queue Q)/*Mengirim true jika Q kosong */
{
    return ((Head(Q)==Nil)&&(Tail(Q)==Nil));
}
boolean IsFull (Queue Q)
/* Mengirim true jika tabel penampung elemen Q sudah penuh yaitu mengandung MaxEl elemen */
{
    return (Tail(Q)==MaxEl(Q));
}
int NBElmt (Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
{
    if (IsEmpty(Q))
    {
        return (0);
    }
    else
    {
        return Tail(Q);
    }
}

/* *** Konstruktor *** */
void CreateEmpty (Queue *Q, int Max)
/* I.S. Max terdefinisi */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb :       */
/*      Jika alokasi berhasil, tabel memori dialokasi berukuran Max  */
/*      atau : jika alokasi gagal, Q kosong dg Maksimum elemen=0     */
/* Proses : Melakukan alokasi memori dan membuat sebuah Q kosong     */
{
    (*Q).T = (infotype *) malloc((Max+1)*sizeof(infotype));
    if ((*Q).T != Nil)
    {
        MaxEl(*Q) = Max;
        Head(*Q) = Nil;
        Tail(*Q) = Nil;
    }
    else /* alokasi gagal */
    {
        MaxEl(*Q)=Nil;
    }
}

/* *** Destruktor *** */
void DeAlokasi (Queue *Q)
/* Proses : Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */
{
    MaxEl(*Q) = Nil;
    free((*Q).T);
}

/* *** Operator-Operator Dasar Queue *** */
void Add (Queue *Q, infotype X)
/* Proses : Menambahkan  X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" */
{
    if(IsEmpty(*Q))
    {
        Head(*Q)=1;
    }
    Tail(*Q)++;
    InfoTail(*Q)=X;
}
void Del (Queue *Q, infotype *X)
/* Proses: Menghapus elemen pertama pada Q dengan aturan FIFO */
/* I.S. Q tidak kosong */
/* F.S. X = nilai elemen HEAD pada I.S.,
       Jika Queue masih isi : HEAD diset tetap = 1, elemen-elemen setelah HEAD yang
       lama digeser ke "kiri", TAIL = TAIL – 1;        Jika Queue menjadi kosong, HEAD = TAIL = Nil. */
{
    //kamus
    int i;
    //algoritma
    (*X)=InfoHead(*Q);
    if (Head(*Q)==Tail(*Q))
    {
        Head(*Q) = Nil;
        Tail(*Q) = Nil;
    }
    else
    {
        i=Head(*Q);
        do
        {
            (*Q).T[i]=(*Q).T[i+1];
            i++;
        }while(i!=Tail(*Q));
        Tail(*Q)--;
    }
}
void ChangeTurn(Queue *Q)
{
	//kamus
	infotype X;
	//algoritma
	Del(&(*Q), &X);
	Add(&(*Q), X);
}




/* *** FUNGSI GA KEPAKE *** */
void setstatuspemain (player *p)
{
    int i,j, panjang, ujungkiri;

    char statpem[18]="**STATUS PEMAIN**";
    char jmluang[14]="Jumlah Uang : ";
    char jmlaset[14]="Jumlah Aset : ";

    for (i=1;i<=imax;i++)
    {
        for(j=1;j<=jmax;j++)
        {
            if((i>=7)&&(j>=14))
            {
                ujungkiri=j-14;
                if((ujungkiri<strlen(statpem))&&(i==8))
                {
                    m.t[i][j]=statpem[ujungkiri];
                }
                if(((i==9)||(i==12)||(i==15)||(i==18)))
                {
                    panjang=strlen((*p).pem[((i-9)/3)+1].nama);
                    if((j-18)<=panjang)
                    {
                        m.t[i][j]=(*p).pem[((i-9)/3)+1].nama[j-18];
                    }
                    if( ((ujungkiri<=3) || ((j>=14+panjang+4)&&(j<=14+panjang+4+3)) ) && (!ispemainempty((*p).pem[((i-9)/3)+1])) )
                    {
                        m.t[i][j]='-';
                    }
                }
                if( ((i==10)||(i==13)||(i==16)||(i==19)) && (!ispemainempty((*p).pem[((i-10)/3)+1])) )
                {
                    if ((ujungkiri<=14) )
                    m.t[i][j]=jmluang[ujungkiri];
                }
                if( ((i==11)||(i==14)||(i==17)||(i==20)) && (!ispemainempty((*p).pem[((i-10)/3)+1])) )
                {
                    if ((ujungkiri<=14) )
                    m.t[i][j]=jmlaset[ujungkiri];
                }
            }
        }
    }
}

void setstatus(place *tempat, player *p)
{
    int i, j;
    int batasu, batasd, batasl, batasr;

    batasu=ubawah+2;
    batasd=imax-1;
    batasl=ukiri;
    batasr=jmax-1;
    for (i=(batasu);i<=batasd;i++)
    {
        for(j=batasl;j<=batasr;j++)
        {
            if((i==(batasu))||(i==(batasd)))
            {
                m.t[i][j]='-';
            }
            else if ((j==(batasl))||(j==(batasr)))
            {
                m.t[i][j]='|';
            }
            if (((i==(batasu))||(i==(batasd)))&&((j==(batasl))||(j==(batasr))))
            {
                m.t[i][j]='+';
            }
        }
    }
}

boolean ispemainempty(pemain pe)//mengecek apakah pemain ada atau tidak
{
    return (strcmp(pe.nama, "")==0);
}

