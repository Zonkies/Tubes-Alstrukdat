int main(){
	/* KAMUS */
		    //kamus
    int V_Pemenang, V_Dadu1, V_Dadu2, V_SumDadu, Turns, V_GiliranX, V_LokasiPemain, V_HargaSewa, V_HargaJual, V_NilaiKoin, V_Taruhan, V_PemainTerhapus, V_Kesempatan, V_Urutan, V_TotalMaju, V_Temp, V_Urutan1, V_Urutan2;
    int V_TabPemilikKomplek[7];
    T_TabTempat V_TabTempat;
    T_Tempat V_Tempat;
    T_TabPemain V_TabPemain;
    boolean V_IsSudahKocok, V_IsKalah, V_IsAdaGedung, V_IsMenang, V_IsInjakStart, V_IsLewatStart, V_IsJalanLagi, V_IsMusuhPunyaGedung;
    char V_Pilihan;
    char V_PilihanKoin[4], V_NamaGedung[15], V_TempatTujuan[15];
    T_Point V_Pixel;
    T_Giliran V_Giliran;
	boolean ToPreparationMenu = false;
	boolean ToGame = false;
	boolean IsBack = true;
	int i,j,menu; // i,j untuk looping; menu untuk transisi menu
	infotype input; // input untuk menerima masukan nama pemain dari user
	boolean found; // found untuk skema searching dengan boolean
	char YT; // YT untuk menerima masukan 'Y' atau 'T' dari user
	List List_Nama; // Tab_Nama untuk menyimpan nama-nama pemain yang terdaftar
	T_TabHighScore Tab_HighScore;
	address P;
	/* ALGORITMA */
	CreateList(&List_Nama);
    printf("** Save/Load File Eksternal **\n");
	do{
		FLoad(&List_Nama,&Tab_HighScore); // Buka Daftar_Pemain
		printf("\n--------------------------------------------------------------------------\n\n XXXXXXX    XXXXXXXX   XX XXXXX    XXXXXX   XXXXX   XXXXXXXX   -----------\nXXXXXXXX   XXXXXXXXXX  XXXXXXXXX  XXXX     XXXXXX  XXXXXXXXXX  [1] LOGIN\nXXXX       XXXX  XXXX  XXX   XXX  XXXX     XXXX    XXXX  XXXX  -----------\nXXXX XXXX  XXXX  XXXX  XXX   XXX  XXXXXXX  XXXX    XXXX  XXXX  [2] REGISTER\nXXXX XXXX  XXXX  XXXX  XXX   XXX  XXXXXXX  XXXX    XXXX  XXXX  -----------\nXXXX  XXX  XXXXXXXXXX  XXX   XXX  XXXX     XXXX    XXXXXXXXXX  [3] ABOUT\nXXXX  XXX  XXXX  XXXX  XXX   XXX  XXXX     XXXX    XXXX  XXXX  -----------\nXXXXXXXXX  XXXX  XXXX  XXX   XXX  XXXXXXX  XXXXXX  XXXX  XXXX  [4] EXIT\n XXXXXXXX  XXXX  XXXX  XXX   XXX   XXXXXX   XXXXX  XXXX  XXXX  -----------\n\n--------------------------------------------------------------------------\n--------------------------------------------------------------------------\n     ====================     LETS GET RICH!     ====================     \n--------------------------------------------------------------------------\n");
		do{
			printf("Input : ");scanf("%d",&menu);
			switch(menu){
				case 1:{
						if(First(List_Nama)==Nil){
						printf("File kosong! Register terlebih dahulu!\n"); // Kasus kosong
					}
					else{
						printf("Nama : ");scanf("%s",&input);
						/* Cek apakah nama sudah terdaftar atau belum */
						if(Search(List_Nama,input)==Nil){
							printf("Login Gagal. Nama tidak terdaftar. Silakan daftarkan terlebih dahulu\n");
						}
						else{
							printf("Login berhasil.\n");
							printf("Selamat datang %s\n",input.T);
							printf("\nTeman bermain anda :\n");
							P = First(List_Nama);
							while(P != Nil){
								if(strcmp(Info(P).T,input.T)!= 0)
									printf("%s\n",Info(P).T);
								P = Next(P);
							}
							ToPreparationMenu = true;
						}
					}
					break;
				}
				case 2:{
					do{
						printf("--------------------------------------------------------------------------\n");
						printf("     ====================        REGISTER        ====================     \n");
						printf("--------------------------------------------------------------------------\n");
						printf("\n");
						/* Input nama sampai benar */
						do{
							printf("Nama : ");scanf("%s",&input.T);
							if(strlen(input.T) < 3){
								printf("Masukan nama minimal 3 karakter\n");
							}
						}while(strlen(input.T) < 3);
						/* Cek apakah nama sudah terdaftar atau belum */
						
						if(Search(List_Nama,input)!=Nil){
							printf("Pendaftaran gagal. %s telah terdaftar.\n",input.T);
						}
						else{
							/* Menyimpan kedalam list */
							InsertLast(&List_Nama,Alokasi(input));
							printf("Pendaftaran Berhasil. %s terdaftar.\n",input.T);
						}
						/* Input YT sampai benar */
						do{
							printf("Ingin mendaftar lagi (Y/T) : ");scanf(" %c",&YT);
						}while((YT != 'Y')&&(YT != 'T'));
					}while(YT == 'Y');
					break;
				}

				case 3 :
				{
					 printf("===============================================================\n");
					 printf("                         o ABOUT US o                         \n");
					 printf("                 TAK KENAL MAKA TAK SAYANG :)  \n");
					 printf("===============================================================\n");
					 printf("      XXXXXXXXXXXXXXXX\n");
					 printf("   XXXXXXXXXXXXXXXXXXXXXX\n");
					 printf(" XXXXXXXX          XXXXXXXX > 50 CENT\n");
					 printf(" XXXXX                XXXXX ===================================\n");
					 printf("  XXX     XXXXXXXX     XXX   18213001 - Fikriansyah Adzaka\n");
					 printf("  XXX     XXX          XXX   18213002 - Nurizka Fitrianingrum\n");
					 printf("  XXX     XXXXXXXX     XXX   18213030 - Muhammad Irfan\n");
					 printf("  XXX          XXX     XXX  \n");
					 printf("  XXX     XXXXXXXX     XXX   IF2111 Algoritma Struktur Data\n");
					 printf(" XXXXX                XXXXX  STI 2013, K01\n");
					 printf(" XXXXXXXX          XXXXXXXX ===================================\n");
					 printf("   XXXXXXXXXXXXXXXXXXXXXX\n");
					 printf("      XXXXXXXXXXXXXXXX\n");
					 printf("===============================================================\n");
					break;

				}
				case 4:{
						printf("--------------------------------------------------------------------------\n");
						printf("     ====================          BYE!          ====================     \n");
						printf("--------------------------------------------------------------------------\n");
					FSave(List_Nama,Tab_HighScore); // Simpan Daftar_Pemain
					abort();
					break;
				}
				default:{
					printf("Masukan menu tidak valid. Ulangi!\n");
				}
			}
		}while(!ToPreparationMenu);
		
		/** TRANSISI **/
		do{
			printf("--------------------------------------------------------------------------\n");
			printf("     ====================         LOGIN          ====================     \n");
			printf("--------------------------------------------------------------------------\n");
			printf("\n");
			printf("             [1] NEW GAME [2] HIGH SCORE BOARD [3] LOG OUT\n");
			printf("                                    ");

			printf("Input : ");scanf("%d",&menu);

			switch (menu)
			{
				case 1 :
				{
					ToGame = true;
					break;
				}
				case 2 :
				{
					int i;
					int j;
					int k;
					T_HighScore Temp;
					for(i=0;i<Tab_HighScore.NEff-1;i++){
						j = i;
						for(k=i+1;k<Tab_HighScore.NEff;k++){
							if(Tab_HighScore.T[j].Score < Tab_HighScore.T[k].Score){
								j = k;
							}
						}
					}		
					Temp = Tab_HighScore.T[j];
					Tab_HighScore.T[j] = Tab_HighScore.T[i];
					Tab_HighScore.T[i] = Temp;
					printf("--------------------------------------------------------------------------\n");
					printf(" =============== HIGH SCORE BOARD =============== \n");
					printf("--------------------------------------------------------------------------\n");
					printf("------------------------------------ -------------------------------------\n");
					printf(" NAMA \t\t\t SCORE \n");
					for(i=0;i<Tab_HighScore.NEff;i++){
						printf(" %s \t\t %d \n",Tab_HighScore.T[i].Nama,Tab_HighScore.T[i].Score);
					}
					printf("------------------------------------ -------------------------------------\n");
					// HIGH SCORE
					break;
				}
				case 3 :
				{
					IsBack = false;
					break;
				}
				default:{
					printf("Masukan menu tidak valid. Ulangi!\n");
				}
			}
		} while (!ToGame && !IsBack);
	} while (!IsBack);


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
    V_Pemenang=0;
    do
    {
        V_GiliranX= F_InfoHead(V_Giliran);//((Turns-1)%V_TabPemain.JmlPemain)+1; pada P_Turn sekian, yang mainnya V_GiliranX orang keberapa
        P_PrintGame(V_TabTempat, V_TabPemain);//print boardnya
        P_StatusPemain(V_TabPemain);
        V_IsSudahKocok=false;//awalnya belum ngocok
        P_Turn(V_TabPemain, &V_Dadu1, &V_Dadu2, &V_IsSudahKocok, Turns, V_GiliranX);//nampilin keterangan di bawah tentang dadu dan sebagainya, dadu disini berarti output
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
            P_Turn(V_TabPemain, &V_Dadu1, &V_Dadu2, &V_IsSudahKocok, Turns, V_GiliranX);

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
                                V_Giliran.MaxEl--;
                            }
                            else if(V_TabTempat.T[V_LokasiPemain].Pemilik!=V_GiliranX)
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
            else if(V_LokasiPemain==15)
            {
                printf("Tiket Bus ITB\n");
                printf("Apakah anda ingin menggunakan Tiket Bus ITB? ");scanf(" %c",&V_Pilihan);
                if(V_Pilihan=='y')
                {
                    do
                    {
                        printf("Sebutkan lokasi yang ingin anda tuju : ");scanf(" %s",&V_TempatTujuan);
                        P_IsAdaGedung(V_TabTempat, V_TempatTujuan, &V_Urutan, &V_IsAdaGedung);
                        if(!V_IsAdaGedung)
                            printf("gedung tidak ada!\n");
                    }while(!V_IsAdaGedung);
                    V_TotalMaju=(20+V_Urutan-V_TabPemain.T[V_GiliranX].Urutan)%20;
                    for(i=1;i<=V_TotalMaju;i++)
                    {
                        P_MajuSelangkah(&V_TabPemain.T[V_GiliranX], V_GiliranX);
                    }
                    printf("%s maju ke %s\n",V_TabPemain.T[V_GiliranX].Nama,V_TempatTujuan);
                    P_Delay(1000);
                    P_PrintGame(V_TabTempat, V_TabPemain);
                }
            }
            else if((V_LokasiPemain==7)||(V_LokasiPemain==13)||(V_LokasiPemain==16)){
                printf("%s mendapatkan kartu kesempatan: ", V_TabPemain.T[V_GiliranX].Nama);
                V_Kesempatan = rand() % 3 + 1;
                switch(V_Kesempatan){
                    case 1:
                    {
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
                    case 2:
                    {
                        printf("Tiket Bus ITB\n");
                        printf("Apakah anda ingin menggunakan Tiket Bus ITB? ");scanf(" %c",&V_Pilihan);
                        if(V_Pilihan=='y')
                        {
                            do
                            {
                                printf("Sebutkan lokasi yang ingin anda tuju : ");scanf(" %s",&V_TempatTujuan);
                                P_IsAdaGedung(V_TabTempat, V_TempatTujuan, &V_Urutan, &V_IsAdaGedung);
                                if(!V_IsAdaGedung)
                                    printf("gedung tidak ada!\n");
                            }while(!V_IsAdaGedung);
                            V_TotalMaju=(20+V_Urutan-V_TabPemain.T[V_GiliranX].Urutan)%20;
                            for(i=1;i<=V_TotalMaju;i++)
                            {
                                P_MajuSelangkah(&V_TabPemain.T[V_GiliranX], V_GiliranX);
                            }
                            printf("%s maju ke %s\n",V_TabPemain.T[V_GiliranX].Nama,V_TempatTujuan);
                            P_Delay(1000);
                            P_PrintGame(V_TabTempat, V_TabPemain);
                        }
                        break;
                    }
                    case 3:
                    {
                        printf("Tukar Gedung\n");
                        V_IsMusuhPunyaGedung=false;
                        i=1;
                        do
                        {
                            if(i!=V_GiliranX)
                            {
                                if(V_TabPemain.T[V_GiliranX].Uang==V_TabPemain.T[V_GiliranX].Aset)
                                    V_IsMusuhPunyaGedung=true;
                            }
                            i++;
                        }while((i<=V_TabPemain.JmlPemain)&&(!V_IsMusuhPunyaGedung));

                        if(V_TabPemain.T[V_GiliranX].Uang==V_TabPemain.T[V_GiliranX].Aset)
                        {
                            printf("Anda tidak memiliki gedung!\n");
                        }
                        else if(!V_IsMusuhPunyaGedung)
                        {
                            printf("Lawan anda tidak ada yang memiliki gedung!\n");
                        }
                        else
                        {
                            printf("Apakah anda ingin menukar gedung? ");scanf(" %c",&V_Pilihan);
                            if(V_Pilihan=='y')
                            {
                                do
                                {
                                    printf("Sebutkan gedung yang ingin ditukar : ");scanf(" %s",&V_NamaGedung);
                                    P_IsAdaGedung(V_TabTempat, V_NamaGedung, &V_Urutan1, &V_IsAdaGedung);
                                    if(!V_IsAdaGedung)
                                        printf("gedung tidak ada!\n");
                                    else
                                    {
                                        if(V_TabTempat.T[V_Urutan1].Pemilik!=V_GiliranX)
                                        {
                                            printf("Gedung Tersebut bukan milik anda!\n");
                                        }
                                    }
                                }while((!V_IsAdaGedung)|| (V_TabTempat.T[V_Urutan1].Pemilik!=V_GiliranX));
                                do
                                {
                                    printf("Sebutkan gedung lawan yang ingin ditukar : ");scanf(" %s",&V_NamaGedung);
                                    P_IsAdaGedung(V_TabTempat, V_NamaGedung, &V_Urutan2, &V_IsAdaGedung);
                                    if(!V_IsAdaGedung)
                                        printf("gedung tidak ada!\n");
                                    else
                                    {
                                        if((V_TabTempat.T[V_Urutan2].Pemilik==0)||(V_TabTempat.T[V_Urutan2].Pemilik!=V_GiliranX))
                                        {
                                            printf("Gedung Tersebut Belum ada yang punya atau anda sudah punya!\n");
                                        }
                                    }
                                }while((V_TabTempat.T[V_Urutan2].Pemilik==0)||(V_TabTempat.T[V_Urutan2].Pemilik!=V_GiliranX));
                                V_Temp=V_TabTempat.T[V_Urutan1].Pemilik;
                                V_TabTempat.T[V_Urutan1].Pemilik=V_TabTempat.T[V_Urutan2].Pemilik;
                                V_TabTempat.T[V_Urutan2].Pemilik=V_Temp;
                            }
                        }
                        break;
                        P_Delay(2000);
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
        //cek Kondisi Menang
        if(V_TabTempat.T[1].Pemilik==V_TabTempat.T[2].Pemilik)
            V_TabPemilikKomplek[1]=V_TabTempat.T[1].Pemilik;
        if(V_TabTempat.T[3].Pemilik==V_TabTempat.T[4].Pemilik)
            V_TabPemilikKomplek[2]=V_TabTempat.T[3].Pemilik;
        if(V_TabTempat.T[8].Pemilik==V_TabTempat.T[9].Pemilik)
            V_TabPemilikKomplek[3]=V_TabTempat.T[9].Pemilik;
        if(V_TabTempat.T[11].Pemilik==V_TabTempat.T[12].Pemilik)
            V_TabPemilikKomplek[4]=V_TabTempat.T[11].Pemilik;
        if(V_TabTempat.T[18].Pemilik==V_TabTempat.T[19].Pemilik)
            V_TabPemilikKomplek[6]=V_TabTempat.T[18].Pemilik;
        //komplek K asumsi komplek ke 5
        if((V_TabTempat.T[6].Pemilik==V_TabTempat.T[14].Pemilik)&&(V_TabTempat.T[14].Pemilik==V_TabTempat.T[17].Pemilik))
            V_TabPemilikKomplek[5]=V_TabTempat.T[6].Pemilik;

        V_TabPemain.T[V_TabPemilikKomplek[5]].Menang=true;
        V_Pemenang=V_TabPemilikKomplek[5];

        for(i=1;i<=6;i++)
        {
            for(j=1;j<=6;j++)
            {
                if(i!=j)
                {
                    if(V_TabPemilikKomplek[i]==V_TabPemilikKomplek[j])
                    {
                        V_TabPemain.T[V_TabPemilikKomplek[i]].Menang=true;
                        V_Pemenang=V_TabPemilikKomplek[i];
                    }
                }
            }
        }
        if(V_Giliran.MaxEl==1)
        {
            V_TabPemain.T[V_GiliranX].Menang=true;
            V_Pemenang=V_GiliranX;
        }

    }while(V_Pemenang==0);
    printf("Selamat %s telah memenangkan permainan!\n", V_TabPemain.T[V_Pemenang].Nama);
	return 0;
}
