#include "monopoly.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    //kamus
    int i, j, dadu1, dadu2, tdadu, turns, giliran, location, hargasewa, hargajual, koin, taruhan, gilir;
    place tempat;
    tempt tmpt;
    player p;
    point sb;
    boolean issudahkocok, kalah, adagedung, menang;
    boolean nginjekstart, lewatstart;
    char pilihan;
    char pilihankoin[4], jualgedung[15];
    Queue Q;

    //algoritma

    srand(time(NULL));
    //inisialisasi
    inisialisasi(&tempat, &p );
    insertjumlahpemain(&p, &Q);
    isilogo(&p);

    setboard( &tempat,&p);


    //setstatus(, &tempat, &p);
    //printgame(game, tempat, p);

    turns=1;//turn pertama
    do
    {
        giliran= InfoHead(Q);//((turns-1)%p.jmlpemain)+1; pada turn sekian, yang mainnya giliran orang keberapa
        printgame(tempat, p);//print boardnya
        statuspemain(p);
        issudahkocok=false;//awalnya belum ngocok
        turn(p, &dadu1, &dadu2, &issudahkocok, turns);//nampilin keterangan di bawah tentang dadu dan sebagainya, dadu disini berarti output
        tdadu=dadu1+dadu2;//total dua dadu
        nginjekstart=false;//tidak menginjak start
        lewatstart=false;//tidak melewati start

        /* *** KONDISI SAAT PEMAIN MAJU *** */
        for(i=1;i<=tdadu;i++)//pemain maju sebanyak tdadu, tetapi satu2 agar user experience lebih terasa
        {
            delay(250);
            majuselangkah(&(p.pem[giliran]), giliran);//maju satu langkah
            if((p.pem[giliran].lokasi==0) && (turns>p.jmlpemain))//saat menginjek start, tetapi tentu saja bukan saat awal permainan
            {
                nginjekstart=true;
            }
            else if(nginjekstart)//jika sudah pernah nginjek start, otomatis pemain berarti melewati start
            {
                lewatstart=true;
            }
            printgame(tempat, p);
            statuspemain(p);
            turn(p, &dadu1, &dadu2, &issudahkocok, turns);
        }

        /* *** KONDISI MELEWATI START *** */
        if((nginjekstart)&&(!lewatstart))//kalo cuma nginjek start tapi ga lewat
        {
            printf("%s menempati posisi Start.\n", p.pem[giliran].nama);
            printf("%s tidak mendapatkan gaji apapun.\n", p.pem[giliran].nama);
        }
        else if (lewatstart)//pemain melewati start
        {
            printf("%s melewati posisi Start.\n", p.pem[giliran].nama);
            printf("%s mendapatkan gaji sebesar Rp 1,500,000.\n", p.pem[giliran].nama);
            p.pem[giliran].uang=p.pem[giliran].uang+1500000;
            p.pem[giliran].aset=p.pem[giliran].aset+1500000;
        }
        delay(1000);

        /* *** KONDISI PEMAIN SAAT MEMASUKI LOKASI/ TEMPAT TERTENTU *** */
        location=p.pem[giliran].lokasi;//lokasi pemain saat ini (0..19)
        tmpt=tempat.tmpt[location];
        //kalo yang di tempati gedung
        if (isgedung(tmpt))
        {
            if(tempat.tmpt[location].pemilik==0)//jika tidak ada pemiliknya berarti pilihan untuk membeli gedung atau tidak
            {
                printf("beli gedung?\n");
                scanf(" %c", &pilihan);
                if(pilihan=='y')
                {
                    if ((p.pem[giliran].uang-tempat.tmpt[location].hargabeli)>=0)//kalo uangnya cukup bisa beli
                    {
                        printf("%s membeli Gedung %s seharga Rp %d\n", p.pem[giliran].nama, tempat.tmpt[location].name, tempat.tmpt[location].hargabeli);
                        p.pem[giliran].uang=p.pem[giliran].uang-tempat.tmpt[location].hargabeli;
                        p.pem[giliran].aset=p.pem[giliran].uang+(tempat.tmpt[location].hargabeli/2);
                        tempat.tmpt[location].pemilik=giliran;
                    }
                    else //kalo uang nya tidak cukup ga bisa beli
                    {
                        printf("%s tidak bisa membeli gedung, karena uang anda tidak mencukupi!\n", p.pem[giliran].nama);
                    }
                    delay(2000);
                }
            }
            else//gedung sudah ada yang punya
            {
                printf("%s berada pada Gedung %s yang dimiliki oleh %s\n", p.pem[giliran].nama, tempat.tmpt[location].name, p.pem[tempat.tmpt[location].pemilik].nama);
                hargasewa=tempat.tmpt[location].hargabeli*30/100;
                do
                {
                    if((p.pem[giliran].uang-hargasewa)<0)//kalo ga cukup bayar sewa, jual gedung yang sudah dimiliki
                    {
                        if(p.pem[giliran].uang==p.pem[giliran].aset)
                        {
                            printf("%s tidak dapat membayar sewa gedung dan pemain tidak memiliki gedung untuk di jual\n",p.pem[giliran].nama);
                            printf("%s kalah!\n", p.pem[giliran].nama);
                            Del(&Q, &gilir);
                        }
                        else
                        {
                            printf("%s tidak memiliki uang yang cukup untuk membayar uang sewa.\n", p.pem[giliran].nama);
                            printf("Sebutkan gedung yang ingin dijual! ");
                            scanf(" %s", &jualgedung);
                            adagedung=false;
                            for (i=0;i<=19;i++)
                            {
                                if((strcmp(jualgedung, tempat.tmpt[i].name)==0) && (tempat.tmpt[i].pemilik==giliran))//cek ada apa tidak gedung tersebut
                                {
                                    adagedung=true;
                                    hargajual=tempat.tmpt[i].hargabeli*50/100;
                                    p.pem[giliran].uang=p.pem[giliran].uang+hargajual;
                                    tempat.tmpt[i].pemilik=0;
                                }
                            }
                            if(!adagedung)//gedung tidak ada dan pemain tersebut bukan yang punya
                            {
                                printf("Gedung %s tidak ada atau dimiliki orang lain\n", jualgedung);
                            }
                        }
                    }
                }while((p.pem[giliran].uang-hargasewa)<0);
             //uang dan aset pemain berkurang
                p.pem[giliran].uang=p.pem[giliran].uang-hargasewa;
                p.pem[giliran].aset=p.pem[giliran].aset-hargasewa;
                //uang pemilik gedung bertambah
                p.pem[tempat.tmpt[location].pemilik].uang=p.pem[tempat.tmpt[location].pemilik].uang+hargasewa;
                p.pem[tempat.tmpt[location].pemilik].aset=p.pem[tempat.tmpt[location].pemilik].aset+hargasewa;
                printf("%s membayar uang sewa ke %s sebesar Rp %d.\n", p.pem[giliran].nama, p.pem[tempat.tmpt[location].pemilik].nama, hargasewa);
                delay(2000);

            }
        }
        //JIKA YANG DI MASUKI LOKASI UNDIAN
        else if(location==10)
        {
            printf("%s mendapatkan kesempatan Undian.\n", p.pem[giliran].nama);
            kalah=false;

            printf("Apakah Anda ingin bermain? ");
            scanf(" %c", &pilihan);
            if((pilihan=='y')&&((p.pem[giliran].uang-1500000)>=0))
            {
                printf("%s membayar 1,5 juta untuk melakukan taruhan.\n", p.pem[giliran].nama);
                p.pem[giliran].uang=p.pem[giliran].uang-1500000;
                p.pem[giliran].aset=p.pem[giliran].aset-1500000;
                taruhan=1500000;
                do
                {
                    printf("Taruhan Anda (Head/Tail) : ");
                    scanf(" %s", &pilihankoin);
                    koin=rand() %2 +1;
                    if (koin==1)
                    {
                        printf("Hasil Undian : Head\n");
                        if(strcmp(pilihankoin, "Head")==0)
                        {
                            printf("Anda Menang! ");
                            taruhan=taruhan*2;
                        }
                        else
                        {
                            kalah=true;
                        }
                    }
                    else if (koin==2)
                    {
                        printf("Hasil Undian : Tail\n");
                        if(strcmp(pilihankoin, "Tail")==0)
                        {
                            printf("Anda Menang! ");
                            taruhan=taruhan*2;
                        }
                        else
                        {
                            kalah=true;
                        }
                    }
                    if (!kalah)
                    {
                        printf("Apakah Anda ingin bermain? ");
                        scanf(" %c", &pilihan);
                    }
                    else
                    {
                        printf("Anda Kalah! Anda tidak mendapatkan apapun.\n");
                        taruhan=0;
                        delay(2000);
                    }
                }while((!kalah)&&(pilihan=='y'));

                p.pem[giliran].uang=p.pem[giliran].uang+taruhan;
                p.pem[giliran].aset=p.pem[giliran].aset+taruhan;
            }
            else if((p.pem[giliran].uang-1500000)<0)
            {
                printf("Uang anda tidak cukup! \n");
            }
        }
        turns++;
        ChangeTurn(&Q);
    }while(turns<=20);
    return 0;
}
