// sipus.h - definisi tipe data dan prototipe fungsi
#ifndef SIPUS_H
#define SIPUS_H

#include <string>
using namespace std;

// ---------- Konstanta ----------
const int JML_KATEGORI = 5;    // Ukuran baris rekap
const int JML_BULAN    = 12;   // Ukuran kolom rekap
const int MAKS_PINJAM  = 3;    // Batas buku per anggota
const int LAMA_PINJAM  = 7;    // Hari (tambahan)
const int DENDA_HARIAN = 1000; // Rupiah per hari

// ---------- Tipe data ----------
struct Tanggal {
    int hari, bulan, tahun;
};

struct Buku {
    string kode;        // Format "BK-001"
    string judul;
    string penulis;
    int kategori;       // 0..JML_KATEGORI-1
    int tahun;
    int stok;           // Eksemplar tersedia
    int totalDipinjam;  // Untuk statistik
};

struct Anggota {
    string id;          // Format "AG-001"
    string nama;
    string prodi;
    int sedangPinjam;   // Maksimum MAKS_PINJAM
};

struct Transaksi {
    int nomor;
    string idAnggota;
    string kodeBuku;
    Tanggal tglPinjam;
    Tanggal tglKembali; // Diisi saat buku kembali
    bool selesai;
    int denda;
};

// Pembungkus array dinamis: alamat, isi, kapasitas
struct DaftarBuku      { Buku* data;      int n, kapasitas; };
struct DaftarAnggota   { Anggota* data;   int n, kapasitas; };
struct DaftarTransaksi { Transaksi* data; int n, kapasitas; };

// ---------- Modul Buku (Mahasiswa A) ----------
void inisialisasi(DaftarBuku& d, int kapasitasAwal);
void bebaskan(DaftarBuku& d);
bool tambahBuku(DaftarBuku& d, const Buku& b);
bool ubahBuku(DaftarBuku& d, const string& kode,
              const Buku& baru);                       // (tambahan)
bool hapusBuku(DaftarBuku& d, const string& kode);
void tampilBuku(const DaftarBuku& d);                  // (tambahan)
Buku* cariKode(DaftarBuku& d, const string& kode);
void cariJudul(const DaftarBuku& d, const string& kata);
void urutkanKode(DaftarBuku& d);
void urutkanJudul(DaftarBuku& d);                      // (tambahan)
void urutkanDipinjam(DaftarBuku& d);                   // (tambahan)
int binarySearchKode(const Buku arr[], int kiri,
                     int kanan, const string& kode);

// ---------- Modul Anggota & Transaksi (Mahasiswa B) ----------
void inisialisasi(DaftarAnggota& d, int kapasitasAwal);   // (tambahan)
void bebaskan(DaftarAnggota& d);                          // (tambahan)
bool tambahAnggota(DaftarAnggota& d, const Anggota& a);   // (tambahan)
bool ubahAnggota(DaftarAnggota& d, const string& id,
                 const Anggota& baru);                    // (tambahan)
void tampilAnggota(const DaftarAnggota& d);               // (tambahan)
Anggota* cariAnggota(DaftarAnggota& d, const string& id); // (tambahan)

void inisialisasi(DaftarTransaksi& t, int kapasitasAwal); // (tambahan)
void bebaskan(DaftarTransaksi& t);                        // (tambahan)
bool tambahTransaksi(DaftarTransaksi& t, const Transaksi& tr); // (tambahan)

bool pinjamBuku(DaftarTransaksi& t, DaftarBuku& b,
                DaftarAnggota& a, const string& idAg,
                const string& kodeBk, const Tanggal& tgl);
bool kembalikanBuku(DaftarTransaksi& t, DaftarBuku& b,
                    DaftarAnggota& a, int nomor,
                    const Tanggal& tgl);
int selisihHari(const Tanggal& awal, const Tanggal& akhir);
int totalDendaRekursif(const Transaksi arr[], int n);
void riwayatAnggota(const Transaksi arr[], int n,
                    const string& idAg);                  // (tambahan, rekursif)
bool bukuSedangDipinjam(const DaftarTransaksi& t,
                        const string& kode);              // (tambahan)

// ---------- Modul Laporan (Mahasiswa B) ----------
void isiRekap(const DaftarTransaksi& t, const DaftarBuku& b,
              int rekap[][JML_BULAN]);
void tampilRekap(const int rekap[][JML_BULAN],
                 const string namaKategori[]);
int kategoriTerpopuler(const int rekap[][JML_BULAN]);     // (tambahan)

#endif
