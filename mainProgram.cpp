#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>
using namespace std;

class User {
public:
    string nama;
    int usia; 
    string gender;
    string kategori; 
};

class DetakJantungNormal {
public:
    int anak[4] = {70, 80, 90, 100};
    int remaja[5] = {60, 70, 80, 90, 100}; 
    int dewasa[5] = {60, 70, 80, 90, 100};
    int tua[5] = {50, 60, 70, 80, 90};
    int manula[7] = {40, 50, 60, 70, 80, 90, 100};
};

// Fungsi untuk memeriksa apakah sebuah string berisi hanya huruf
bool isAlphabetic(const string& input) {
    for (char c : input) {
        if (!isalpha(c)) {
            return false;
        }
    }
    return true;
}

// Fungsi untuk menentukan kategori berdasarkan usia
string kategoriUsia(int usia) { 
    if (usia >= 65) {
        return "Manula";
    } else if (usia >= 46) {
        return "Tua";
    } else if (usia >= 26) {
        return "Dewasa";
    } else if (usia >= 12) {
        return "Remaja";
    } else {
        return "Anak-anak";
    }
}

// Fungsi untuk menentukan program yang bisa diakses berdasarkan gender user
string kategoriGender(const string& gender) {
    string jenisKelamin = gender;

    if (jenisKelamin == "Pria" || jenisKelamin == "pria") {
        return "Tracking detak jantung mingguan";
    } else {
        return "Tracking detak jantung & prediksi siklus haid";
    }
}

//Fungsi menghitung total detak jantung
int totalDetakJantung(int* detakJantung, int urutanArray) {

    if (urutanArray == 0) {
        return 0;
    }else {
        return detakJantung[urutanArray - 1] + totalDetakJantung(detakJantung, urutanArray - 1);
    }
}

//Fungsi menghitung rata rata detak jantung
double totalRerataDetak(int* detakJantung, int urutanArray) {
    if (urutanArray == 0) {
        return 0;
    }else {
        return static_cast<double>(totalDetakJantung(detakJantung, urutanArray)) / urutanArray;
    }
}

// Fungsi menampilkan detak jantung abnormal
void detakJantungAbnormal(int* detakJantung, int urutanArray, const string& kategoriUsia) {
    bool adaDetakAbnormal = false;
    DetakJantungNormal detakNormal;

    int* detakJantungNormal = nullptr;
    int jumlahElemen = 0;

    if (kategoriUsia == "Anak-anak") {
        detakJantungNormal = detakNormal.anak;
        jumlahElemen = sizeof(detakNormal.anak) / sizeof(detakNormal.anak[0]);
    } else if (kategoriUsia == "Remaja") {
        detakJantungNormal = detakNormal.remaja;
        jumlahElemen = sizeof(detakNormal.remaja) / sizeof(detakNormal.remaja[0]);
    } else if (kategoriUsia == "Dewasa") {
        detakJantungNormal = detakNormal.dewasa;
        jumlahElemen = sizeof(detakNormal.dewasa) / sizeof(detakNormal.dewasa[0]);
    } else if (kategoriUsia == "Tua") {
        detakJantungNormal = detakNormal.tua;
        jumlahElemen = sizeof(detakNormal.tua) / sizeof(detakNormal.tua[0]);
    } else if (kategoriUsia == "Manula") {
        detakJantungNormal = detakNormal.manula;
        jumlahElemen = sizeof(detakNormal.manula) / sizeof(detakNormal.manula[0]);
    }

    cout << "Detak jantung yang berada di atas batas normal:" << endl;
    for (int i = 0; i < urutanArray; i++) {
        bool detakNormal = false;
        for (int j = 0; j < jumlahElemen; j++) {
            if (*(detakJantung + i) < detakJantungNormal[j]) {
                detakNormal = true;
                break;
            }
        }
        if (!detakNormal) {
            cout << *(detakJantung + i) << " bpm" << endl;
            adaDetakAbnormal = true;
        }
    }

    if (!adaDetakAbnormal) {
        cout << "Tidak ada detak jantung abnormal" << endl;
    }
}

void saran(int gejala) {
    switch(gejala){
    	case 1:
    		cout<<"\nZen Said: Yey! Berdasarkan data organ jantung Anda bekerja optimal"<<endl;
    		break;
    	case 2:
    		cout<<"\nZen Said: Tak apa, detak jantung Anda tinggi mungkin karena habis menjalankan kegiatan fisik, tenang aja yaa:)"<<endl;
    		break;
    	case 3:
    		cout<<"\nZen Said: Yahh:( , jika gejala dirasa makin parah tolong segera hubungi dokter"<<endl;
    		break;
    	default:
    		cout<<"\nTidak ada saran untuk ditampilkan"<<endl;
    		break;
	}
}


//Blok fitur haid
// Fungsi untuk menghitung tanggal haid selanjutnya
void hitunganPeriod(int hariTerakhirPeriod, int panjangSiklus, int& periodSelanjutnya, int& fertilityWindowStart, int& fertilityWindowEnd, int& ovulationDay) {
    periodSelanjutnya = ( hariTerakhirPeriod+ panjangSiklus) % 30;
    fertilityWindowStart = periodSelanjutnya - 10;
    fertilityWindowEnd = periodSelanjutnya - 4;
    ovulationDay = periodSelanjutnya - 14;
    if (fertilityWindowStart < 0) {
        fertilityWindowStart += 30;
        fertilityWindowEnd += 30;
        ovulationDay += 30;
    }
}

// Fungsi untuk menampilkan grafik panjang periode
void grafikPeriod(int lamaPeriod) {
    for (int i = 0; i < lamaPeriod ; i++) {
        cout << "*";
    }
    cout << endl;
}

int main() {
    cout << "\n==============================" << endl;
    cout << "\nWelcome to Zen Health Tracker" << endl;
    cout << "\n==============================" << endl;

    cout << "\nSilahkan input data diri Anda" << endl;

	//Masih ada bug, gabisa pake spasi
    User data1;
   	cout << "Nama Anda\t:";
    getline(cin, data1.nama);
    
    bool validInput2 = false;
    while (!validInput2){
        cout << "\nUsiamu saat ini\t:";
        string age;
        getline(cin, age);
        try{
            data1.usia = stoi(age); 
            validInput2 = true;
        } catch(const invalid_argument&){
            cout<<"Input usia tidak valid. Harap masukkan angka." << endl;
        };  
    }

    bool validInput3 = false;
    while (!validInput3) {
        cout << "\nAnda adalah (Pria/Wanita) :";
        getline(cin, data1.gender);

        if (!isAlphabetic(data1.gender)) {
            cout << "Input gender tidak valid. Harap masukkan huruf." << endl;
        } else {
            validInput3 = true;
        }
    }
   
    User data2;
    data2.gender = data1.gender;

    data1.kategori = kategoriUsia(data1.usia); // Menentukan kategori usia
    data2.gender = kategoriGender(data2.gender); // Menentukan program yang bisa diakses berdasarkan gender
    
    // Menampilkan data user
    cout << "\nResume Data Diri Anda"<<endl;
    cout << "_______________________________" << endl;

    cout << "\nNama\t: " << data1.nama << endl;
    cout << "Usia\t: " << data1.usia <<" Tahun"<< endl;
    cout << "Gender\t: " << data1.gender << endl;
    cout << "Kategori: " << data1.kategori << endl;
    cout << "\nHai, "<<data1.nama<<"!"<<endl;
    cout << "Program untuk Anda adalah: " << data2.gender << endl;


    // Ini blok kode jika gender user = Pria||pria
    string dataGender = data1.gender;
    if (dataGender == "Pria" || dataGender == "pria") {
        const int memoArray = 7;
        int detakJantung[memoArray];
        cout<<"\n_______________________________________";
        cout<<"\nProgram: Tracking detak jantung";
        cout<<"\n_______________________________________";
    
        // Memasukkan detak jantung harian ke dalam array
        cout<<endl;
        cout << "\nMasukkan detak jantung harian (bpm) selama " << memoArray << " hari:" << endl;
        for (int i = 0; i < memoArray; i++) {
            cout << "Hari " << i + 1 << ": ";
            cin >> *(detakJantung + i);
        }
        
        cout << "\nResume Kondisi Detak Jantung Anda" <<", "<<data1.nama<<" : "<< endl;
    	cout << "_______________________________________" << endl;

        // Menghitung rata-rata detak jantung
        double averageHeartRate = totalRerataDetak(detakJantung, memoArray);
        cout << "\nRata-rata detak jantung: " << averageHeartRate << " bpm"<<endl;
        cout<< endl;

        // Menampilkan detak jantung yang berada di atas batas normal
        detakJantungAbnormal(detakJantung, memoArray, data1.kategori); 
        
        int gejala;
        cout<<endl;
        cout<<"---------------------------------------------------------------------------------------------------------";
        cout<<endl;
        cout<<"\nPilih kondisi terkini agar Zen bisa menyimpulkan"<<endl;
        cout<<endl;
        cout<<"Tolong isi berdasarkan yang Anda rasakan saat ini"<<endl;
        cout<<"Input angka 1 jika \t: hasil analisis detak jantung normal dan tidak merasakan gejala apapun";
        cout<<"\nInput angka 2 jika \t: analisis detak jantung normal namun Anda merasakan gejala tertentu";
        cout<<"\nInput angka 3 jika \t: analisis detak jantung ada yang tidak normal dan Anda merasakan gejala tertentu";
        
        cout<<"\nPilihan : ";
		cin>>gejala;
        saran(gejala);
        
        cout << "\n=================================================" << endl;
    	cout << "\nTerimakasih Telah Menggunakan Zen Health Tracker!" << endl;
    	cout << "\n=================================================" << endl;
    }else{
    	const int memoArray = 7;
        int detakJantung[memoArray];
        
        cout<<"\n_______________________________________";
        cout<<"\nProgram Pertama: Tracking detak jantung";
        cout<<"\n_______________________________________";
    
        // Memasukkan detak jantung harian ke dalam array
        cout<<endl;
        cout << "\nMasukkan detak jantung harian (bpm) selama " << memoArray << " hari:" << endl;
        for (int i = 0; i < memoArray; i++) {
            cout << "Hari " << i + 1 << ": ";
            cin >> *(detakJantung + i);
        }
        
        cout << "\nResume Kondisi Detak Jantung Anda" <<", "<<data1.nama<<" : "<< endl;
    	cout << "_______________________________________" << endl;

        // Menghitung rata-rata detak jantung
        double averageHeartRate = totalRerataDetak(detakJantung, memoArray);
        cout << "\nRata-rata detak jantung: " << averageHeartRate << " bpm"<<endl;
        cout<<endl;

        // Menampilkan detak jantung yang berada di atas batas normal
        detakJantungAbnormal(detakJantung, memoArray, data1.kategori); 
        
        int gejala;
        cout<<endl;
        cout<<"---------------------------------------------------------------------------------------------------------";
        cout<<endl;
       	cout<<"\nPilih kondisi terkini agar Zen bisa menyimpulkan > | <"<<endl;
        cout<<endl;
        cout<<"Tolong isi berdasarkan yang Anda rasakan saat ini"<<endl;
        cout<<"Input angka 1 jika \t: hasil analisis detak jantung normal dan tidak merasakan gejala apapun";
        cout<<"\nInput angka 2 jika \t: analisis detak jantung normal namun Anda merasakan gejala tertentu";
        cout<<"\nInput angka 3 jika \t: analisis detak jantung ada yang tidak normal dan Anda merasakan gejala tertentu";
        
        cout<<"\nPilihan : ";
		cin>>gejala;
        saran(gejala);
        
        
        cout<<"\n__________________________________";
        cout<<"\nProgram Kedua: Prediksi siklus haid";
        cout<<"\n___________________________________";
        cout<<endl;
        
        int numMonths;
	    cout << "\nMasukan berapa bulan yang ingin kamu prediksi : ";
	    cin >> numMonths;
	    cout<<endl;
	
	    int* lamaPeriod = new int[numMonths];
	    int* panjangSiklus = new int[numMonths];
	    int* hariTerakhirPeriod = new int[numMonths];
	    int* periodSelanjutnya = new int[numMonths];
	    int* fertilityWindowStart = new int[numMonths];
	    int* fertilityWindowEnd = new int[numMonths];
	    int* ovulationDay = new int[numMonths];
	    double averageLamaPeriod = 0.0;
	
	    for (int i = 0; i < numMonths; i++) {
	        cout << "Bulan " << i + 1 << ":" << endl;
	        cout << "Masukan berapa hari kamu haid = ";
	        cin >> lamaPeriod[i];
	        cout<<"lama haid kamu adalah "<<lamaPeriod[i]<<" hari"<<endl;
	        averageLamaPeriod += lamaPeriod[i]; // Menambahkan panjang periode ke total rata-rata
	        cout << "\nMasukan berapa hari jarak antar periode haid kamu sebelumnya = ";
	        cin >> panjangSiklus[i];
	        cout<< "siklus haid kamu adalah "<<panjangSiklus[i]<<" hari"<<endl;
	        cout << "\nMasukan tanggal terkahir kamu haid = ";
	        cin >> hariTerakhirPeriod[i];
	        cout << "tanggal haid terakhir kamu adalah tanggal "<<hariTerakhirPeriod[i]<<endl;
	        cout << endl;
	
	        hitunganPeriod(hariTerakhirPeriod[i], panjangSiklus[i], periodSelanjutnya[i], fertilityWindowStart[i], fertilityWindowEnd[i], ovulationDay[i]);
	    }
	
	    averageLamaPeriod /= numMonths; // Menghitung rata-rata panjang periode
	
	    cout << "\n====================" << endl;
	    cout << "  Hasil Prediksi Kamu " << endl;
	    cout << "======================" << endl;
	    cout << endl;
	
	    for (int i = 0; i < numMonths; i++) {
	        cout << "Prediksi untuk bulan " << i + 2 << ":" << endl;
	        cout << "\nHaid kamu selanjutkan jatuh pada tanggal : " << periodSelanjutnya[i] << endl;
	        cout << "Fertility window: " << fertilityWindowStart[i] << " - " << fertilityWindowEnd[i] << endl;
	        cout << "(medium chance to getting pregnant)" << endl;
	        cout << "Ovulation day: " << ovulationDay[i] << endl;
	        cout << "(high chance to getting pregnant)" << endl;
	        cout << endl;
	    }
	
	    // Grafik untuk menunjukkan panjang periode
	    cout << "Grafik Lama Haid Kamu" << endl;
	    for (int i = 0; i < numMonths; i++) {
	        cout << "Bulan " << i + 1 << ": ";
	        grafikPeriod(lamaPeriod[i]);
	    }
	
	    cout << "\nAverage length of period: " << averageLamaPeriod<< endl;
	
	    delete[] lamaPeriod;
	    delete[] panjangSiklus;
	    delete[] hariTerakhirPeriod;
	    delete[] periodSelanjutnya;
	    delete[] fertilityWindowStart;
	    delete[] fertilityWindowEnd;
	    delete[] ovulationDay;
	    
	    cout << "\n=================================================" << endl;
    	cout << "\nTerimakasih Telah Menggunakan Zen Health Tracker!" << endl;
    	cout << "\n=================================================" << endl;

	}

    return 0;
}
